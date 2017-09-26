#include <iostream>

#ifdef _SYSTEM_LINUX
  #include <stdio.h>
#elif _SYSTEM_WINDOWS
  #include <windows.h>
#endif

#include "dll/DiplayMessage.h"


int main (void)
{

  DiplayMessage("Hello world\n");

  return 0;
}
