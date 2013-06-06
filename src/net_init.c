/*-----------------------------------------*/
/* AUTHOR:    Incarnation-p-lee            */
/* DATE:      2013/05/31                   */
/* REVISION:                               */
/* 20130531   Created                      */
/*-----------------------------------------*/
void init_socket()
{
  init_socket_parms();

  return;
}

#ifdef WIN32
static void
init_socket_parms()
{
  unsigned short wVersionRequest;
  unsigned long threadid;
  WSADATA wdata;

  wVersionRequest = MAKEWORD(2,2);
  if(WSAStartup(wVersionRequest, &wdata))
    error_handle("WSAStartup");

  sock_loc = socket(AF_INET, 
	SOCK_STREAM, IPPROTO_TCP);
  sock_rmt = socket(AF_INET, 
	SOCK_STREAM, IPPROTO_TCP);
  assert(-1 != sock_loc && 
    -1 != sock_rmt);

  memset(&addr_rmt, 0, sizeof(addr_rmt));
  memset(&addr_loc, 0, sizeof(addr_loc));

  addr_rmt.sin_family = AF_INET;
  addr_rmt.sin_addr.s_addr = 
    inet_addr(REMOTE_IP);
  addr_rmt.sin_port = htons(RMT_PORT);

  addr_loc.sin_family = AF_INET;
  addr_loc.sin_addr.s_addr = 
    inet_addr(LOCAL_IP);
  addr_loc.sin_port = htons(LOC_PORT);

  if(-1 == bind(sock_loc,
    (const struct sockaddr *)&addr_loc,
    sizeof(addr_loc)))
    error_handle("bind");

  if(!CreateThread(NULL, 0, 
    (LPTHREAD_START_ROUTINE)server_start, 
	0, 0, &threadid))
    error_handle("CreateThread");

  return;
}
#endif

#ifdef __linux__
static void
init_socket_parms()
{
  pthread_t rev_thread = 0;

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

  if(0 != pthread_create(&rev_thread, NULL,
       server_start, &sock_srv))
    error_handle("pthread");
  
  return;
}
#endif

static void *
server_start(void *sock)
{
  struct sockaddr_in addr_tmp;
  int sock_tmp;
#ifdef WIN32
  int len;
#endif
#ifdef __linux__
  socklen_t len;
#endif

  while(1)
  {
    if(-1 == listen(*(int*)sock, 
      LISTEN_COUNT))
      error_handle("listen");
       
    len = sizeof(addr_tmp);
    sock_tmp = accept(*(int*)sock, 
      (struct sockaddr*)&addr_tmp,
      &len);

    if(-1 == sock_tmp)
      error_handle("accept");
   
    data_recv(sock_tmp, rev_buf); 
  }
  
  return sock;   
}
