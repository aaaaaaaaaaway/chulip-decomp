/* newlib memalignr.o from commit b0ba0ac21747fef4f150f2632aedf0f59e0ae03a. */

#define _memalign_r func_001916D8
#define _malloc_r func_00191B38
#define _free_r func_001961A8
#define __malloc_lock func_001924B8
#define __malloc_unlock func_001924C0

#define MALLOC_ALIGNMENT 16
#define SIZE_T_SMALLER_THAN_LONG
#define INTERNAL_NEWLIB
#define DEFINE_MEMALIGN
#include "tools/vendor/newlib-20000221/stdlib/mallocr.c"
