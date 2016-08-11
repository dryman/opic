#include <log4c.h>

__attribute__((constructor(101)))
static void opic_log4c_init()
{
  log4c_init();
}
