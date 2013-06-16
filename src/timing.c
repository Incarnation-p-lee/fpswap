/*-----------------------------------------*/
/* AUTHOR:    Incarnation-p-lee            */
/* DATE:      2013/06/06                   */
/* REVISION:                               */
/* 20130606   Created                      */
/*-----------------------------------------*/
#ifdef __linux__
void 
get_time_start()
{
  gettimeofday(&start, NULL);
  return;
}

unsigned long long
get_time_end()
{
  unsigned long long delta;
  time_t sec;

  gettimeofday(&end, NULL);
  sec = end.tv_sec - start.tv_sec;
  delta = end.tv_usec - start.tv_usec; 
  if(0 != sec)
    delta += 1000000 * sec; 
    
  return delta;
}
#endif

#ifdef _WINDOWS_
void 
get_time_start()
{
  GetSystemTime(&start);
  return;
}

unsigned long long
get_time_end()
{
  unsigned long long delta;
  time_t sec;

  GetSystemTime(&end);
  sec = end.wSecond - start.wSecond;
  delta = end.wMilliseconds - 
    start.wMilliseconds; 
  if(0 != sec)
    delta += 1000 * sec; 
    
  return delta * 1000;
}

#endif
