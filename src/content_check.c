/*-----------------------------------------*/
/* AUTHOR:    Incarnation-p-lee            */
/* DATE:      2013/05/31                   */
/* REVISION:                               */
/* 20130531   Created                      */
/*-----------------------------------------*/
int
input_check(char *fname)
{
  char *item, *skip;

  assert(NULL != fname);
  
  ignore_space(&fname);
  skip = strtok(fname, SPACE);
  item = skip;
  skip = strtok(NULL, SPACE);

  /* Now only has put operation */
  if(!strcmp(item, "get"))
  {
    ignore_space(&skip);
    cpy_filename(get_filename, skip);
    return 0;
  }

  if(!strcmp(item, "put"))
  {
    ignore_space(&skip);
    cpy_filename(put_filename, skip);
    return 0;
  }
  
  return 1;
}


static void
ignore_space(char **ch)
{
  assert(NULL != ch);
  while(isspace(**ch) && NUL != **ch)
    (*ch)++;
  
  return;
}

static void
cpy_filename(char *fname, char *cp)
{
  assert(NULL != cp);
  while(!isspace(*cp) && NUL != *cp)
    *fname++ = *cp++;

  return;
}
