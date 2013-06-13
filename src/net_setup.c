/*-----------------------------------------*/
/* AUTHOR:    Incarnation-p-lee            */
/* DATE:      2013/05/31                   */
/* REVISION:                               */
/* 20130531   Created                      */
/*-----------------------------------------*/
void
net_setup()
{
  FILE *conf;
  const int len = 64;
  char buf[len];

  conf = fopen(FILE_CONFIG, "r");
  if(NULL == conf)
    error_handle("fopen");
  
  memset(local_ip, 0, IP_LENGTH);
  memset(remote_ip, 0, IP_LENGTH);
  
  local_port = net_setup_handle(buf,
    len, conf);
  remote_port = net_setup_handle(buf,
    len, conf);

}

static int
net_setup_handle(char *buf,
  int len, FILE *file)
{
  int port = 0;
  char *offset;
  assert(NULL != buf && NULL != file);
  
  memset(buf, 0, len);
  fgets(buf, len, file);
  offset = strtok(buf, SPLITER);

  if(!strcmp(offset, "local"))
  {
     offset = strtok(NULL, SPLITER);
     strcpy(local_ip, offset);
     offset = strtok(NULL, SPLITER);
     port = atoi(offset);
  }

  if(!strcmp(offset, "remote"))
  {
     offset = strtok(NULL, SPLITER);
     strcpy(remote_ip, offset);
     offset = strtok(NULL, SPLITER);
     port = atoi(offset);
  }
  return port;
}

