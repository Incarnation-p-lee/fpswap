/*-----------------------------------------*/
/* AUTHOR:    Incarnation-p-lee            */
/* DATE:      2013/06/06                   */
/* REVISION:                               */
/* 20130606   Created                      */
/*-----------------------------------------*/
void
env_reset()
{
  buffer_clearup();
}

static void
buffer_clearup()
{
  memset(get_filename, 0, FILENAME_LEN);
  memset(put_filename, 0, FILENAME_LEN);
  memset(rev_buf, 0, BUFFER_LEN);
  memset(command_line, 0, COMMAND_LEN);

  if(NULL != send_buf)
  {
    free(send_buf);
    send_buf = NULL;
  }

  return;
}

