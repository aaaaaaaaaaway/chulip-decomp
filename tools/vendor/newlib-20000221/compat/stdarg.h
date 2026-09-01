#ifndef _STDARG_H
#define _STDARG_H

typedef void *__gnuc_va_list;
typedef __gnuc_va_list va_list;

#define va_start(ap, last) __builtin_stdarg_start((ap), (last))
#define va_end(ap) ((void)0)
#define va_arg(ap, type) __builtin_va_arg((ap), type)

#endif
