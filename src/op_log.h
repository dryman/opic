#ifndef OP_LOG_H
#define OP_LOG_H 1
#include <log4c.h>

#define OP_LOGGER_FACTORY(logger, catName) \
static const log4c_category_t* logger; \
__attribute__((constructor (5))) \
static void init_##logger() \
{ \
  logger = log4c_category_get(catName) \
}

#endif
