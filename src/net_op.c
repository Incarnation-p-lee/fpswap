/*-----------------------------------------*/
/* AUTHOR:    Incarnation-p-lee            */
/* DATE:      2013/06/04                   */
/* REVISION:                               */
/* 20130604   Created                      */
/*-----------------------------------------*/
void
data_send(int sock, char *buf, int len)
{
  int index, padding;
  assert(NULL != buf && len > 0);

  net_send(sock, put_filename,
    FILENAME_LEN);

  padding = len % SEND_LEN;
  if(0 != padding)
    net_send(sock, buf, padding);
  
  index = padding;
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
  int len;
  assert(NULL != buf);

  len = recv(sock, buf,
    BUFFER_LEN, MSG_WAITALL);
  if(-1 == len)
    error_handle("recv");
  fprintf(stdout, "recv =>%d \n", len);
 
  fprintf(stdout, "%s\n", buf);
  return;
}
