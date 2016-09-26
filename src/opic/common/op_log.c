#include <stdbool.h>
#include "config.h"
#include "op_log.h"

static bool _log4c_initialized;

void opic_log4c_init()
{
  if (!_log4c_initialized)
    {
      log4c_init();
      _log4c_initialized = true;
    }
}
