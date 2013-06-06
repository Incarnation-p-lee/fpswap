/*-----------------------------------------*/
/* AUTHOR:    Incarnation-p-lee            */
/* DATE:      2013/05/31                   */
/* REVISION:                               */
/* 20130531   Created                      */
/*-----------------------------------------*/

void
init_socket()
{
#ifdef __linux__
  pthread_t rev_thread = 0;
#endif

  sock_clt = socket(AF_INET, SOCK_STREAM, 0);
  sock_srv = socket(AF_INET, SOCK_STREAM, 0);
  assert(-1 != sock_clt && 
    -1 != sock_srv);

  bzero(&addr_rmt, sizeof(addr_rmt));
  bzero(&addr_loc, sizeof(addr_loc));

  addr_rmt.sin_family = AF_INET;
  addr_rmt.sin_addr.s_addr = 
    inet_addr(REMOTE_IP);
  addr_rmt.sin_port = htons(RMT_PORT);

  addr_loc.sin_family = AF_INET;
  addr_loc.sin_addr.s_addr = 
    inet_addr(LOCAL_IP);
  addr_loc.sin_port = htons(LOC_PORT);

  if(-1 == bind(sock_srv,
    (const struct sockaddr *)&addr_loc,
    sizeof(addr_loc)))
    error_handle("bind");

  if(connect(sock_clt, 
    (const struct sockaddr*)&addr_rmt,
    sizeof(addr_rmt)))
    error_handle("connect"); 

#ifdef __linux__
  if(0 != pthread_create(&rev_thread, NULL,
       server_start, &sock_srv))
    error_handle("pthread");
  
#endif

  return;
}

static void *
server_start(void *sock)
{
  struct sockaddr_in addr_tmp;
  socklen_t len;
  int sock_tmp;

  while(1)
  {
    if(-1 == listen(*(int*)sock, 
      LISTEN_COUNT))
      error_handle("listen");
       
    len = (socklen_t)sizeof(addr_tmp);
    sock_tmp = accept(*(int*)sock, 
      (struct sockaddr*)&addr_tmp,
      &len);

    if(-1 == sock_tmp)
      error_handle("accept");
   
    data_recv(sock_tmp, rev_buf); 
  }
  
  return sock;   
}
