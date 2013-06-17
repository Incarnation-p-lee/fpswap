/*-----------------------------------------*/
/* AUTHOR:    Incarnation-p-lee            */
/* DATE:      2013/06/03                   */
/* REVISION:                               */
/* 20130603   Created                      */
/*-----------------------------------------*/

void
error_handle(const char *mesg)
{
  assert(NULL != mesg);
  fprintf(stdout, "broken at %s.\n", mesg);
  fprintf(stdout, "NO. %d, MSG: %s\n",
    errno, strerror(errno));
  getchar();
  exit(EXIT_FAILURE);
}

