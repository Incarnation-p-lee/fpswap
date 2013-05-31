/*-----------------------------------------*/
/* AUTHOR:    Incarnation-p-lee            */
/* DATE:      2013/05/07                   */
/* REVISION:                               */
/* 20130507   Created                      */
/*-----------------------------------------*/

#include "include.h"
#include "defs.h"
#include "externals.h"
#include "vars.h"


int
main(int argc, char **argv)
{
  while(1)
  {
    fprintf(stdout, "Welcome to fswap, type"
      "your operation [put].\n");
 
    if(!input_check(gets(command_line)))
    {
    }

  }
  return EXIT_SUCCESS;
}
