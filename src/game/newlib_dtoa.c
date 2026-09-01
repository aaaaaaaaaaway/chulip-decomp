/*
 * Chulip uses the newlib dtoa.c revision at b0ba0ac21747fef4f150f2632aedf0f59e0ae03a.
 * The included upstream source retains its original David M. Gay license.
 */

#define quorem func_00194A60
#define _dtoa_r func_00194C78

#define _Balloc func_00196F08
#define _Bfree func_00196FB0
#define _multadd func_00196FE0
#define _hi0bits func_00197240
#define _i2b func_00197388
#define _multiply func_001973C0
#define _pow5mult func_001975F0
#define _lshift func_001976F0
#define __mcmp func_00197868
#define __mdiff func_001978D0
#define _d2b func_00197C78
#define memcpy func_00192344

#define __mprec_tens D_001EBFE0
#define __mprec_bigtens D_001EC0A8

#include "tools/vendor/newlib-20000221/stdlib/dtoa.c"
