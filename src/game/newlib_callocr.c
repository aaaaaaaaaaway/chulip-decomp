/* newlib callocr.o from commit b0ba0ac21747fef4f150f2632aedf0f59e0ae03a. */

#define _calloc_r func_00198140
#define _malloc_r func_00191B38
#define memset func_001923F4

#define MORECORE_CLEARS 0
#define INTERNAL_NEWLIB
#define DEFINE_CALLOC
#include "tools/vendor/newlib-20000221/stdlib/mallocr.c"
