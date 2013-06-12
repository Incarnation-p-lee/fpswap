/*-----------------------------------------*/
/* AUTHOR:    Incarnation-p-lee            */
/* DATE:      2013/06/04                   */
/* REVISION:                               */
/* 20130604   Created                      */
/*-----------------------------------------*/
int
file_buf(char *fname)
{
  FILE *filep;
  int length;
  int padding;
  assert(NULL != fname);
  
  filep = fopen(fname, "rb");
  fseek(filep, 0, SEEK_END);
  length = (int)ftell(filep);
  *(int*)(fname + LENGTH_INDEX) = length;
  rewind(filep);
  send_buf = (char*)malloc(length);
  
  padding = length % READ_LEN;
  if(0 != padding)
    fread(send_buf, length, 1, filep);
  fread(send_buf + padding, READ_LEN, 
    length / READ_LEN, filep);

  fclose(filep);
  
  return length;
}

FILE *
file_create(char *fname)
{
  FILE *wfname;
  assert(NULL != fname);
  
  wfname = fopen(fname, "w");
  if(NULL == wfname)
    error_handle("fopen");
  
  return wfname;
}

void
file_write(FILE *wfile, char *buf, int len)
{
  assert(NULL != buf && NULL != wfile);
  
  if(1 != fwrite(buf, len, 1, wfile))
    error_handle("fwrite");

  return;
}
