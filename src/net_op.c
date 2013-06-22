/*-----------------------------------------*/
/* AUTHOR:    Incarnation-p-lee            */
/* DATE:      2013/06/04                   */
/* REVISION:                               */
/* 20130604   Created                      */
/*-----------------------------------------*/
void
data_send(char *fname, char *buf,
  int sock)
{
  FILE *filep;
  int fsize;
  register int index;
  assert(NULL != fname && NULL == buf);
 
  
  filep = fopen(fname, "r");
  fsize = file_buf(filep);
  *(int*)(fname + LENGTH_INDEX) = fsize;
  net_send(sock, fname, FILENAME_LEN);

  buf = (char*)malloc(FREAD_LEN);
  index = fsize % FREAD_LEN;
  if(0 != index)
  {
    fread(buf, index, 1, filep);
    frame_send(sock, buf, index);
  }
  
  while(fsize != index)
  {
    fread(buf, FREAD_LEN, 1, filep);
    frame_send(sock, buf, FREAD_LEN);
    index += FREAD_LEN;
    fprintf(stdout, ".");
    fflush(stdout);
  }
  
  fprintf(stdout, "\nFile sended %d KB.\n", 
    fsize >> 10);
  fclose(filep);
  free(buf);
  
  return;
}

static void
frame_send(int sock, char *buf, int len)
{
  register int index, cnt;
  assert(NULL != buf && len > 0);
  
  index = len % SEND_LEN;
  if(0 != index)
    net_send(sock, buf, index);
  
  cnt = 0;
  while(len != index)
  {
    net_send(sock, buf + index, SEND_LEN);
    index += SEND_LEN;
    cnt++;
    if(0 == cnt % SEND_CNT)
#ifdef __linux__
      usleep(SEND_DELAY);
#endif

#ifdef _WINDOWS_
      Sleep(SEND_DELAY);
#endif
  }

  return;
}

static void
net_send(int sock, char *buf, int len)
{
  register int send_size = 0;

  while(len > 0)
  {
    send_size = send(sock, buf,
      len, MSG_DONTROUTE);

    if(-1 == send_size)
    {
      if(EINTR == errno)
        send_size = 0;
      else
        error_handle("send");
    }
    else
    {
      len -= send_size;
      buf += send_size;
    }
  }

  if(0 != len)
    error_handle("send");

  return;
}

void
data_recv(int sock, char *buf)
{
  int fsize;
  register int cnt;
  unsigned long long delta_usec;
  assert(NULL != buf);
  
  do
  {
    net_recv(sock, buf, FILENAME_LEN);

    fsize = *(int*)(buf + LENGTH_INDEX);
    fprintf(stdout, "File Name: %s.\n"
	  "File Size: %d[Byte].\n", buf, fsize); 
    
    file_create(buf);
    cnt = fsize % BUFFER_LEN;
    memset(buf, 0, FILENAME_LEN);

    TIME_START;
    if(0 != cnt)
      net_recv_write(sock, buf, cnt);

    while(fsize != cnt)
    {
      net_recv_write(sock, buf, BUFFER_LEN);
      cnt += BUFFER_LEN;
    }
    delta_usec = TIME_END / 1000;   /* milli seconds */

    fprintf(stdout, "\nReceived, %d B, %fMB/s.\n",
      fsize, 
      ((double)fsize / 1000) / (delta_usec));
    fflush(stdout);
    fclose(fwriter);
  }while(1);
  return;
}

static void
net_recv_write(int sock, char *buf, int len)
{
  int padding;

  memset(buf, 0, FILENAME_LEN);
  padding = len % SEND_LEN; 

  if(0 != padding)
  {
    net_recv(sock, buf, padding);
    file_write(buf, padding);
    buf += padding;
    len -= padding;
  }

  while(len != 0)
  {
    net_recv(sock, buf, SEND_LEN);
    file_write(buf, SEND_LEN);
    buf += SEND_LEN;
    len -= SEND_LEN;
  }

  fprintf(stdout, ".");
  fflush(stdout);

  return;
}

static void
net_recv(int sock, char *buf, int len)
{
  register int recv_size = 0;

  while(len > 0)
  {
     recv_size = recv(sock, buf,
       len, MSG_WAITALL);

     if(-1 == recv_size)
     {
       if(EINTR == errno)
         recv_size = 0;
       else
         error_handle("recv");
     }
     else
     {
       len -= recv_size;
       buf += recv_size;
     }
  }
  
  if(0 != len)
    error_handle("recv");

  return;
}
