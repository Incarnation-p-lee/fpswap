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
 
  if(connect(sock_loc, 
    (const struct sockaddr*)&addr_rmt,
    sizeof(addr_rmt)))
    error_handle("connect"); 
  
  net_send(sock, buf, len);

  shutdown(sock, SHUT_RDWR);
  
  return;
}

static void
net_send(int sock, char *buf, int len)
{
  int index, padding;
  assert(NULL != buf && len > 0);

  index = 0;
  padding = len % SEND_LEN;
  if(0 != padding)
  {
    send(sock, buf, padding, MSG_MORE);
    printf("%s\n",strerror(errno));
    fflush(stdout);
  }
  
  index += padding;
  while(len != padding + index)
  {
    if(SEND_LEN != send(sock, 
      buf + index, SEND_LEN, MSG_MORE))
      error_handle("send");
      
    index += SEND_LEN;
  }
  
  free(buf);
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
 
  fprintf(stdout, "%s\n", buf);
  return;
}
