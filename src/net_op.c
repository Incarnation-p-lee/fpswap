/*-----------------------------------------*/
/* AUTHOR:    Incarnation-p-lee            */
/* DATE:      2013/06/04                   */
/* REVISION:                               */
/* 20130604   Created                      */
/*-----------------------------------------*/
void
data_send(int sock, char *buf, int len)
{
  int index;
  assert(NULL != buf && len > 0);

  net_send(sock, put_filename,
    FILENAME_LEN);

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

  return;
}

void
data_recv(int sock, char *buf)
{
  int len, fsize, index;
  FILE *wfile;
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
    
    wfile = file_create(buf);
    memset(buf, 0, FILENAME_LEN);
    index = fsize % SEND_LEN; 
    if(0 != index)
    {
      len = recv(sock, buf, 
        index, MSG_WAITALL);
      if(-1 == len)
        error_handle("recv");
      file_write(&wfile, buf, index);
    }
    while(fsize != index)
    {
      len = recv(sock, buf + index, 
        SEND_LEN, MSG_WAITALL);
      if(-1 == len)
        error_handle("recv");
      file_write(&wfile,
        buf + index, SEND_LEN);
      index += SEND_LEN;
    }
   
    fprintf(stdout, "%s\n", buf);
    fclose(wfile);
  }while(1);
  return;
}
