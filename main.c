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
  fprintf(stdout, "Welcome to fswap, type"
    "your operation [put].\n");
 
  while(1)
  {
    if(!input_check(gets(command_line)))
    {
      init_socket();
    }

  }
  return EXIT_SUCCESS;
}
