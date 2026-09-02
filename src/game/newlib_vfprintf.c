/*
 * newlib vfprintf.o from commit b0ba0ac21747fef4f150f2632aedf0f59e0ae03a.
 * Sony's EE ABI advances variadic arguments in eight-byte slots.
 */

#include <stdio.h>
#include <stdarg.h>

#undef va_arg
#define va_arg(ap, type) \
    (*(type *)((char *)((ap) = (char *)(ap) + 8) - 8))

#define WANT_PRINTF_LONG_LONG
#define __sprint func_00193030
#define __sbprintf func_00193078
#define vfprintf func_00193130
#define _vfprintf_r func_001931A8
#define cvt func_001946C0
#define exponent func_00194870
#define _impure_ptr D_001E4EB4
#define __mb_cur_max D_001E5310
#define __sinit func_00196118
#define __swsetup func_00194950
#define __sfvwrite func_00196638
#define fflush func_00195E48
#define localeconv func_00196B70
#define _mbtowc_r func_00196CE8
#define isinf func_00197F28
#define isnan func_0018E5D0
#define memchr func_00196D24
#define strlen func_00192A54
#define _dtoa_r func_00194C78

extern struct _reent *D_001E4EB4;

#include "tools/vendor/newlib-20000221/stdio/vfprintf.c"
