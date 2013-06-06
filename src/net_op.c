/*-----------------------------------------*/
/* AUTHOR:    Incarnation-p-lee            */
/* DATE:      2013/06/04                   */
/* REVISION:                               */
/* 20130604   Created                      */
/*-----------------------------------------*/
void
data_send(int sock, char *buf, int len)
{
  assert(NULL != buf && len > 0);
  
  net_send(sock, buf, len);
  
  return;
}

static void
net_send(int sock, char *buf, int len)
{
  int index, padding;
  assert(NULL != buf && len > 0);

  padding = len % SEND_LEN;
  if(0 != padding)
  {
    send(sock, buf, padding,
#ifdef __linux__
      MSG_MORE);
#endif
#ifdef WIN32
      0); 
#endif
    printf("%s\n",strerror(errno));
    fflush(stdout);
  }
  
  index = 0;
  while(len != padding + index)
  {
    if(SEND_LEN != send(sock, 
		buf + index, SEND_LEN, 
#ifdef __linux__
	  MSG_MORE))
#endif
#ifdef WIN32
	  0))
#endif
      error_handle("send");
      
    index += SEND_LEN;
  }
  
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
