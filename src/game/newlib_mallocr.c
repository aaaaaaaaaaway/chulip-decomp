/* newlib mallocr.o from commit b0ba0ac21747fef4f150f2632aedf0f59e0ae03a. */

#define malloc_extend_top func_001918E0
#define _malloc_r func_00191B38

#define __malloc_lock func_001924B8
#define __malloc_unlock func_001924C0
#define _sbrk_r func_00192598
#define _free_r func_001961A8

#define __malloc_av_ D_001E4EB8
#define __malloc_trim_threshold D_001E52C0
#define __malloc_top_pad D_001E52C8
#define __malloc_sbrk_base D_001E52D0
#define __malloc_max_sbrked_mem D_001E52D8
#define __malloc_max_total_mem D_001E52E0
#define __malloc_current_mallinfo D_001E52E8

#define MALLOC_ALIGNMENT 16
#define SIZE_T_SMALLER_THAN_LONG
#define INTERNAL_NEWLIB
#define DEFINE_MALLOC
#include "tools/vendor/newlib-20000221/stdlib/mallocr.c"
