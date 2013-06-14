/*-----------------------------------------*/
/* AUTHOR:    Incarnation-p-lee            */
/* DATE:      2013/06/04                   */
/* REVISION:                               */
/* 20130604   Created                      */
/*-----------------------------------------*/
int
file_buf(FILE *sfile)
{
  int length;
  assert(NULL != sfile);
  
  fseek(sfile, 0, SEEK_END);
  length = (int)ftell(sfile);
  rewind(sfile);

  return length;
}

void
file_create(char *fname)
{
  assert(NULL != fname);
  
  fwriter = fopen(fname, "w");
  if(NULL == fwriter)
    error_handle("fopen");
  
  return;
}

void
file_write(char *buf, int len)
{
  assert(NULL != buf);
  
  if(1 != fwrite(buf, len, 1, fwriter))
    error_handle("fwrite");

  return;
}
