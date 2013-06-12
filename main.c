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
  int fsize;
  fprintf(stdout, "Welcome to fswap, type"
    " your operation [put].\n");
 
  init_socket();
  while(1)
  {
    switch(input_check(gets(command_line)))
    {
      case NA:
        error_handle("Unknown operation");
        break;
      case PUT:
        fsize = file_buf(put_filename);
        data_send(sock_clt, send_buf, fsize);
        env_reset();
        break;
      case GET:
        break;
      case CONT:
        fprintf(stdout, "Your operation,"
          "PLEASE!\n");
        break;
      case EXIT:
        fprintf(stdout, "Bye!\n");
        exit(EXIT_SUCCESS);
    }
  }
  return EXIT_SUCCESS;
}
