#include "DiplayMessage.h"


void DiplayMessage(const char * szMessage)
{
  #ifdef _SYSTEM_LINUX
    printf("%s", szMessage);
  #elif _SYSTEM_WINDOWS
    MessageBox(szMessage):
  #endif
}
