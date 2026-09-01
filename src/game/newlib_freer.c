/* newlib freer.o from commit b0ba0ac21747fef4f150f2632aedf0f59e0ae03a. */

#define _free_r func_001961A8
#define _malloc_trim_r func_001964C8

#define __malloc_lock func_001924B8
#define __malloc_unlock func_001924C0
#define _sbrk_r func_00192598

#define __malloc_av_ D_001E4EB8
#define __malloc_trim_threshold D_001E52C0
#define __malloc_top_pad D_001E52C8
#define __malloc_sbrk_base D_001E52D0
#define __malloc_current_mallinfo D_001E52E8

#define INTERNAL_NEWLIB
#define DEFINE_FREE
#include "tools/vendor/newlib-20000221/stdlib/mallocr.c"
