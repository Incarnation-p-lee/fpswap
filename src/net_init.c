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
  pid_t pid;
#endif

  sock_loc = socket(AF_INET, SOCK_STREAM, 0);
  sock_rmt = socket(AF_INET, SOCK_STREAM, 0);
  assert(-1 != sock_loc && 
    -1 != sock_rmt);

  bzero(&addr_rmt, sizeof(addr_rmt));
  bzero(&addr_loc, sizeof(addr_loc));

  addr_rmt.sin_family = AF_INET;
  addr_rmt.sin_addr.s_addr = 
    inet_addr(REMOTE_IP);
  addr_rmt.sin_port = htons(NET_PORT);

  addr_loc.sin_family = AF_INET;
  addr_loc.sin_addr.s_addr = 
    inet_addr(REMOTE_IP);
  addr_loc.sin_port = htons(NET_PORT);

  if(-1 == bind(sock_rmt,
    (const struct sockaddr *)&addr_rmt,
    sizeof(addr_rmt)))
    error_handle("bind");

#ifdef __linux__

  if(pid = fork(), 0 == pid)
    server_start(); 
  else if(0 > pid)
    error_handle("fork");
  else
    ;

#endif

  return;
}

static void
server_start()
{
  struct sockaddr_in addr_tmp;
  socklen_t len;
  int sock_tmp;

  while(1)
  {
    if(-1 == listen(sock_rmt, LISTEN_COUNT))
      error_handle("listen");
       
    len = (socklen_t)sizeof(addr_tmp);
    sock_tmp = accept(sock_rmt, 
      (struct sockaddr*)&addr_tmp,
      &len);

    if(-1 == sock_tmp)
      error_handle("accept");
    
    
    
  }
  
  return;   
}
