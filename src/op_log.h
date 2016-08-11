#ifndef OP_LOG_H
#define OP_LOG_H 1
#include "op_macros.h"
#include <log4c.h>

OP_BEGIN_DECLS
extern void opic_log4c_init();
OP_END_DECLS

#define OP_LOGGER_FACTORY(logger, catName) \
static const log4c_category_t* logger; \
__attribute__((constructor)) \
static void init_##logger() \
{ \
  opic_log4c_init(); \
  logger = log4c_category_get(catName); \
}

#endif
