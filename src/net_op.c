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
  int tmp;
  //if(len != 
  tmp = send(sock, buf, len,
#ifdef __linux__
	  MSG_MORE))
#else 

#ifdef WIN32
	  MSG_DONTROUTE);
#else
#pragma message("UNKNOWN PLATFORM.\n")
    0))
#endif
#endif
 //     error_handle("send");


  return;
}

void
data_recv(int sock, char *buf)
{
  int len, fsize;
  register int cnt;
  unsigned long long delta_usec;
  assert(NULL != buf);
  
  do
  {
    len = recv(sock, buf,
      FILENAME_LEN, MSG_WAITALL);
    if(FILENAME_LEN != len)
      error_handle("recv");

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
    delta_usec = TIME_END >> 10;   /* milli seconds */

    fprintf(stdout, "\nReceived, %d KB, %fMB/s.\n",
      fsize >> 10, 
      (double)(fsize >> 10) / (delta_usec));
    fflush(stdout);
    fclose(fwriter);
  }while(1);
  return;
}

static void
net_recv_write(int sock, char *buf, int len)
{
  int index, tmp;

  memset(buf, 0, FILENAME_LEN);
  index = len % SEND_LEN; 

  if(0 != index)
  {
    tmp = recv(sock, buf, 
      index, MSG_WAITALL);
    if(index != tmp)
      error_handle("recv");
    file_write(buf, index);
  }

  while(len != index)
  {
    tmp = recv(sock, buf + index, 
      SEND_LEN, MSG_WAITALL);
    if(SEND_LEN != tmp)
      error_handle("recv");
    file_write(buf + index, SEND_LEN);
    index += SEND_LEN;
  }
  fprintf(stdout, ".");
  fflush(stdout);

  return;
}
