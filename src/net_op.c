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
  }

  fclose(filep);
  free(buf);
  
  return;
}

static void
frame_send(int sock, char *buf, int len)
{
  register int index;
  assert(NULL != buf && len > 0);
  
  index = len % SEND_LEN;
  if(0 != index)
    net_send(sock, buf, index);
  
  while(len != index)
  {
    net_send(sock, buf + index, SEND_LEN);
    index += SEND_LEN;
  }

  return;
}

static void
net_send(int sock, char *buf, int len)
{
  if(len != send(sock, buf, len,
#ifdef __linux__
	  MSG_MORE))
#else 

#ifdef WIN32
	  MSG_OOB))
#else
#pragma message("UNKNOWN PLATFORM.\n")
    0))
#endif
#endif
      error_handle("send");

#ifdef __linux__
    usleep(SEND_DELAY);
#endif

#ifdef _WINDOWS_
    Sleep(SEND_DELAY);
#endif

  return;
}

void
data_recv(int sock, char *buf)
{
  int len, fsize;
  register int cnt;
  assert(NULL != buf);
  
  do
  {
    len = recv(sock, buf,
      FILENAME_LEN, MSG_WAITALL);
    if(-1 == len)
      error_handle("recv");

    fsize = *(int*)(buf + LENGTH_INDEX);
    fprintf(stdout, "File Name: %s.\n"
	  "File Size: %d[Byte].\n", buf, fsize); 
    
    file_create(buf);
    cnt = fsize % BUFFER_LEN;

    if(0 != cnt)
      net_recv_write(sock, buf, cnt);

    while(fsize != cnt)
    {
      net_recv_write(sock, buf, BUFFER_LEN);
      cnt += BUFFER_LEN;
    }
   
    fprintf(stdout, "\nReceived, %d KB.\n",
      fsize >> 10);
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
    if(-1 == tmp)
      error_handle("recv");
    file_write(buf, index);
  }

  while(len != index)
  {
    tmp = recv(sock, buf + index, 
      SEND_LEN, MSG_WAITALL);
    if(-1 == tmp)
      error_handle("recv");
    file_write(buf + index, SEND_LEN);
    index += SEND_LEN;
  }
  fprintf(stdout, ".");

  return;
}
