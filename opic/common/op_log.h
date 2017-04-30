/**
 * @file op_log.h
 * @author Felix Chern
 * @date Sep 3, 2016
 * @copyright 2016-2017 Felix Chern
 */

/* This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU Lesser General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or (at
 * your option) any later version.
 *
 * This program is distributed in the hope that it will be useful, but
 * WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
 * Lesser General Public License for more details.
 *
 * You should have received a copy of the GNU Lesser General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
 */

/* Code: */


#ifndef OPIC_COMMON_OP_LOG_H
#define OPIC_COMMON_OP_LOG_H 1
#include "op_macros.h"
#include <log4c.h>

/**
 * @defgroup log
 */

OP_BEGIN_DECLS
extern void opic_log4c_init();
OP_END_DECLS

/**
 * @ingroup log
 * @brief Creates a logger with namespace.
 *
 * @param logger logger variable name.
 * @param logger_namespace logger namespace
 *
 * Example:
 * @code
 * #include "opic/common/op_log.h"
 *
 * OP_LOGGER_FACTORY(logger, "example.main")
 *
 * int main() {
 *   OP_LOG_INFO(logger, "Hello World");
 *   return 0;
 * }
 * @endcode
 *
 * The code above prints
 * ```
 * [stdout] INFO     example.main - main() Hello World
 * ```
 */
#define OP_LOGGER_FACTORY(logger, logger_namespace) \
static const log4c_category_t* logger; \
__attribute__((constructor)) \
static void init_##logger() \
{ \
  opic_log4c_init(); \
  logger = log4c_category_get(logger_namespace); \
}

#define OP_LOG_ARGS(LOGGER, CATEGORY, MESSAGE, ...) \
  log4c_category_log(LOGGER, CATEGORY, "%s():%d " \
      MESSAGE, __func__, __LINE__, __VA_ARGS__)

#define OP_LOG_NO_ARGS(LOGGER, CATEGORY, MESSAGE) \
  log4c_category_log(LOGGER, CATEGORY, "%s():%d " \
      MESSAGE, __func__, __LINE__)

/**
 * @ingroup log
 * @brief Log fatal messages
 */
#define OP_LOG_FATAL(LOGGER, ...) \
  _OP_GET_MACRO_BY_ARGS(__VA_ARGS__, \
   OP_LOG_ARGS, OP_LOG_ARGS, OP_LOG_ARGS, OP_LOG_ARGS, \
   OP_LOG_ARGS, OP_LOG_ARGS, OP_LOG_ARGS, OP_LOG_ARGS, \
   OP_LOG_ARGS, OP_LOG_ARGS, OP_LOG_ARGS, OP_LOG_ARGS, \
   OP_LOG_ARGS, OP_LOG_ARGS, OP_LOG_ARGS, OP_LOG_ARGS, \
   OP_LOG_ARGS, OP_LOG_ARGS, OP_LOG_ARGS, OP_LOG_ARGS, \
   OP_LOG_ARGS, OP_LOG_ARGS, OP_LOG_ARGS, OP_LOG_ARGS, \
   OP_LOG_ARGS, OP_LOG_ARGS, OP_LOG_ARGS, OP_LOG_ARGS, \
   OP_LOG_ARGS, OP_LOG_ARGS, OP_LOG_ARGS, OP_LOG_ARGS, \
   OP_LOG_ARGS, OP_LOG_ARGS, OP_LOG_ARGS, OP_LOG_NO_ARGS)(LOGGER, LOG4C_PRIORITY_FATAL, __VA_ARGS__)

/**
 * @ingroup log
 * @brief Log assert messages
 */
#define OP_LOG_ALERT(LOGGER, ...) \
  _OP_GET_MACRO_BY_ARGS(__VA_ARGS__, \
   OP_LOG_ARGS, OP_LOG_ARGS, OP_LOG_ARGS, OP_LOG_ARGS, \
   OP_LOG_ARGS, OP_LOG_ARGS, OP_LOG_ARGS, OP_LOG_ARGS, \
   OP_LOG_ARGS, OP_LOG_ARGS, OP_LOG_ARGS, OP_LOG_ARGS, \
   OP_LOG_ARGS, OP_LOG_ARGS, OP_LOG_ARGS, OP_LOG_ARGS, \
   OP_LOG_ARGS, OP_LOG_ARGS, OP_LOG_ARGS, OP_LOG_ARGS, \
   OP_LOG_ARGS, OP_LOG_ARGS, OP_LOG_ARGS, OP_LOG_ARGS, \
   OP_LOG_ARGS, OP_LOG_ARGS, OP_LOG_ARGS, OP_LOG_ARGS, \
   OP_LOG_ARGS, OP_LOG_ARGS, OP_LOG_ARGS, OP_LOG_ARGS, \
   OP_LOG_ARGS, OP_LOG_ARGS, OP_LOG_ARGS, OP_LOG_NO_ARGS)(LOGGER, LOG4C_PRIORITY_ALERT, __VA_ARGS__)

/**
 * @ingroup log
 * @brief Log critcal messages
 */
#define OP_LOG_CRIT(LOGGER, ...) \
  _OP_GET_MACRO_BY_ARGS(__VA_ARGS__, \
   OP_LOG_ARGS, OP_LOG_ARGS, OP_LOG_ARGS, OP_LOG_ARGS, \
   OP_LOG_ARGS, OP_LOG_ARGS, OP_LOG_ARGS, OP_LOG_ARGS, \
   OP_LOG_ARGS, OP_LOG_ARGS, OP_LOG_ARGS, OP_LOG_ARGS, \
   OP_LOG_ARGS, OP_LOG_ARGS, OP_LOG_ARGS, OP_LOG_ARGS, \
   OP_LOG_ARGS, OP_LOG_ARGS, OP_LOG_ARGS, OP_LOG_ARGS, \
   OP_LOG_ARGS, OP_LOG_ARGS, OP_LOG_ARGS, OP_LOG_ARGS, \
   OP_LOG_ARGS, OP_LOG_ARGS, OP_LOG_ARGS, OP_LOG_ARGS, \
   OP_LOG_ARGS, OP_LOG_ARGS, OP_LOG_ARGS, OP_LOG_ARGS, \
   OP_LOG_ARGS, OP_LOG_ARGS, OP_LOG_ARGS, OP_LOG_NO_ARGS)(LOGGER, LOG4C_PRIORITY_CRIT, __VA_ARGS__)

/**
 * @ingroup log
 * @brief Log error messages
 */
#define OP_LOG_ERROR(LOGGER, ...) \
  _OP_GET_MACRO_BY_ARGS(__VA_ARGS__, \
   OP_LOG_ARGS, OP_LOG_ARGS, OP_LOG_ARGS, OP_LOG_ARGS, \
   OP_LOG_ARGS, OP_LOG_ARGS, OP_LOG_ARGS, OP_LOG_ARGS, \
   OP_LOG_ARGS, OP_LOG_ARGS, OP_LOG_ARGS, OP_LOG_ARGS, \
   OP_LOG_ARGS, OP_LOG_ARGS, OP_LOG_ARGS, OP_LOG_ARGS, \
   OP_LOG_ARGS, OP_LOG_ARGS, OP_LOG_ARGS, OP_LOG_ARGS, \
   OP_LOG_ARGS, OP_LOG_ARGS, OP_LOG_ARGS, OP_LOG_ARGS, \
   OP_LOG_ARGS, OP_LOG_ARGS, OP_LOG_ARGS, OP_LOG_ARGS, \
   OP_LOG_ARGS, OP_LOG_ARGS, OP_LOG_ARGS, OP_LOG_ARGS, \
   OP_LOG_ARGS, OP_LOG_ARGS, OP_LOG_ARGS, OP_LOG_NO_ARGS)(LOGGER, LOG4C_PRIORITY_ERROR, __VA_ARGS__)

/**
 * @ingroup log
 * @brief Log warning messages
 */
#define OP_LOG_WARN(LOGGER, ...) \
  _OP_GET_MACRO_BY_ARGS(__VA_ARGS__, \
   OP_LOG_ARGS, OP_LOG_ARGS, OP_LOG_ARGS, OP_LOG_ARGS, \
   OP_LOG_ARGS, OP_LOG_ARGS, OP_LOG_ARGS, OP_LOG_ARGS, \
   OP_LOG_ARGS, OP_LOG_ARGS, OP_LOG_ARGS, OP_LOG_ARGS, \
   OP_LOG_ARGS, OP_LOG_ARGS, OP_LOG_ARGS, OP_LOG_ARGS, \
   OP_LOG_ARGS, OP_LOG_ARGS, OP_LOG_ARGS, OP_LOG_ARGS, \
   OP_LOG_ARGS, OP_LOG_ARGS, OP_LOG_ARGS, OP_LOG_ARGS, \
   OP_LOG_ARGS, OP_LOG_ARGS, OP_LOG_ARGS, OP_LOG_ARGS, \
   OP_LOG_ARGS, OP_LOG_ARGS, OP_LOG_ARGS, OP_LOG_ARGS, \
   OP_LOG_ARGS, OP_LOG_ARGS, OP_LOG_ARGS, OP_LOG_NO_ARGS)(LOGGER, LOG4C_PRIORITY_WARN, __VA_ARGS__)

/**
 * @ingroup log
 * @brief Log notice messages
 */
#define OP_LOG_NOTICE(LOGGER, ...) \
  _OP_GET_MACRO_BY_ARGS(__VA_ARGS__, \
   OP_LOG_ARGS, OP_LOG_ARGS, OP_LOG_ARGS, OP_LOG_ARGS, \
   OP_LOG_ARGS, OP_LOG_ARGS, OP_LOG_ARGS, OP_LOG_ARGS, \
   OP_LOG_ARGS, OP_LOG_ARGS, OP_LOG_ARGS, OP_LOG_ARGS, \
   OP_LOG_ARGS, OP_LOG_ARGS, OP_LOG_ARGS, OP_LOG_ARGS, \
   OP_LOG_ARGS, OP_LOG_ARGS, OP_LOG_ARGS, OP_LOG_ARGS, \
   OP_LOG_ARGS, OP_LOG_ARGS, OP_LOG_ARGS, OP_LOG_ARGS, \
   OP_LOG_ARGS, OP_LOG_ARGS, OP_LOG_ARGS, OP_LOG_ARGS, \
   OP_LOG_ARGS, OP_LOG_ARGS, OP_LOG_ARGS, OP_LOG_ARGS, \
   OP_LOG_ARGS, OP_LOG_ARGS, OP_LOG_ARGS, OP_LOG_NO_ARGS)(LOGGER, LOG4C_PRIORITY_NOTICE, __VA_ARGS__)

/**
 * @ingroup log
 * @brief Log info messages
 */
#define OP_LOG_INFO(LOGGER, ...) \
  _OP_GET_MACRO_BY_ARGS(__VA_ARGS__, \
   OP_LOG_ARGS, OP_LOG_ARGS, OP_LOG_ARGS, OP_LOG_ARGS, \
   OP_LOG_ARGS, OP_LOG_ARGS, OP_LOG_ARGS, OP_LOG_ARGS, \
   OP_LOG_ARGS, OP_LOG_ARGS, OP_LOG_ARGS, OP_LOG_ARGS, \
   OP_LOG_ARGS, OP_LOG_ARGS, OP_LOG_ARGS, OP_LOG_ARGS, \
   OP_LOG_ARGS, OP_LOG_ARGS, OP_LOG_ARGS, OP_LOG_ARGS, \
   OP_LOG_ARGS, OP_LOG_ARGS, OP_LOG_ARGS, OP_LOG_ARGS, \
   OP_LOG_ARGS, OP_LOG_ARGS, OP_LOG_ARGS, OP_LOG_ARGS, \
   OP_LOG_ARGS, OP_LOG_ARGS, OP_LOG_ARGS, OP_LOG_ARGS, \
   OP_LOG_ARGS, OP_LOG_ARGS, OP_LOG_ARGS, OP_LOG_NO_ARGS)(LOGGER, LOG4C_PRIORITY_INFO, __VA_ARGS__)

#ifndef NDEBUG

/**
 * @ingroup log
 * @brief Log debug messages.
 *
 * If the flag `-DNDEBUG` is defined, this logger would not
 * print anything.
 */
#define OP_LOG_DEBUG(LOGGER, ...) \
  _OP_GET_MACRO_BY_ARGS(__VA_ARGS__, \
   OP_LOG_ARGS, OP_LOG_ARGS, OP_LOG_ARGS, OP_LOG_ARGS, \
   OP_LOG_ARGS, OP_LOG_ARGS, OP_LOG_ARGS, OP_LOG_ARGS, \
   OP_LOG_ARGS, OP_LOG_ARGS, OP_LOG_ARGS, OP_LOG_ARGS, \
   OP_LOG_ARGS, OP_LOG_ARGS, OP_LOG_ARGS, OP_LOG_ARGS, \
   OP_LOG_ARGS, OP_LOG_ARGS, OP_LOG_ARGS, OP_LOG_ARGS, \
   OP_LOG_ARGS, OP_LOG_ARGS, OP_LOG_ARGS, OP_LOG_ARGS, \
   OP_LOG_ARGS, OP_LOG_ARGS, OP_LOG_ARGS, OP_LOG_ARGS, \
   OP_LOG_ARGS, OP_LOG_ARGS, OP_LOG_ARGS, OP_LOG_ARGS, \
   OP_LOG_ARGS, OP_LOG_ARGS, OP_LOG_ARGS, OP_LOG_NO_ARGS)(LOGGER, LOG4C_PRIORITY_DEBUG, __VA_ARGS__)

/**
 * @ingroup log
 * @brief Log trace messages.
 *
 * If the flag `-DNDEBUG` is defined, this logger would not
 * print anything.
 */
#define OP_LOG_TRACE(LOGGER, ...) \
  _OP_GET_MACRO_BY_ARGS(__VA_ARGS__, \
   OP_LOG_ARGS, OP_LOG_ARGS, OP_LOG_ARGS, OP_LOG_ARGS, \
   OP_LOG_ARGS, OP_LOG_ARGS, OP_LOG_ARGS, OP_LOG_ARGS, \
   OP_LOG_ARGS, OP_LOG_ARGS, OP_LOG_ARGS, OP_LOG_ARGS, \
   OP_LOG_ARGS, OP_LOG_ARGS, OP_LOG_ARGS, OP_LOG_ARGS, \
   OP_LOG_ARGS, OP_LOG_ARGS, OP_LOG_ARGS, OP_LOG_ARGS, \
   OP_LOG_ARGS, OP_LOG_ARGS, OP_LOG_ARGS, OP_LOG_ARGS, \
   OP_LOG_ARGS, OP_LOG_ARGS, OP_LOG_ARGS, OP_LOG_ARGS, \
   OP_LOG_ARGS, OP_LOG_ARGS, OP_LOG_ARGS, OP_LOG_ARGS, \
   OP_LOG_ARGS, OP_LOG_ARGS, OP_LOG_ARGS, OP_LOG_NO_ARGS)(LOGGER, LOG4C_PRIORITY_TRACE, __VA_ARGS__)

#else

#define OP_LOG_DEBUG(LOGGER, ...) ((void) 0)
#define OP_LOG_TRACE(LOGGER, ...) ((void) 0)

#endif

#ifndef UNIT_TESTING

/**
 * @ingroup log
 * @brief Log messages only in non unit environment.
 */
#define OP_LOG_NOTEST(LOGGER, ...) \
  _OP_GET_MACRO_BY_ARGS(__VA_ARGS__, \
   OP_LOG_ARGS, OP_LOG_ARGS, OP_LOG_ARGS, OP_LOG_ARGS, \
   OP_LOG_ARGS, OP_LOG_ARGS, OP_LOG_ARGS, OP_LOG_ARGS, \
   OP_LOG_ARGS, OP_LOG_ARGS, OP_LOG_ARGS, OP_LOG_ARGS, \
   OP_LOG_ARGS, OP_LOG_ARGS, OP_LOG_ARGS, OP_LOG_ARGS, \
   OP_LOG_ARGS, OP_LOG_ARGS, OP_LOG_ARGS, OP_LOG_ARGS, \
   OP_LOG_ARGS, OP_LOG_ARGS, OP_LOG_ARGS, OP_LOG_ARGS, \
   OP_LOG_ARGS, OP_LOG_ARGS, OP_LOG_ARGS, OP_LOG_ARGS, \
   OP_LOG_ARGS, OP_LOG_ARGS, OP_LOG_ARGS, OP_LOG_ARGS, \
   OP_LOG_ARGS, OP_LOG_ARGS, OP_LOG_ARGS, OP_LOG_NO_ARGS)(LOGGER, LOG4C_PRIORITY_NOTEST, __VA_ARGS__)

#else

#define OP_LOG_NOTEST(LOGGER, ...) ((void) 0)

#endif

#endif

/* op_log.h ends here */
