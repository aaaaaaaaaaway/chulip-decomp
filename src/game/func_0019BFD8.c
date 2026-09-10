/* Shared file-I/O completion packet, read through its uncached alias. */
typedef struct {
    int first_size;
    int last_size;
    unsigned char *first_destination;
    unsigned char *last_destination;
    unsigned char first_bytes[64];
    unsigned char last_bytes[64];
} ReadFragments;

extern unsigned char D_002E35C0[];
extern unsigned char D_002E35D4[];
extern volatile int D_001E5B00[32];
extern void *func_00192344(void *, const void *, unsigned int);
extern int func_001987D0(int);

#define UNCACHED(address) ((void *)((unsigned int)(address) | 0x20000000))

void func_0019BFD8(void) {
    int semaphore;
    int command;
    void *destination;
    unsigned int length;
    void *extra_destination;
    unsigned int extra_length;
    int index;

    __builtin_memcpy(&semaphore, UNCACHED(D_002E35C0), 4);
    __builtin_memcpy(&command, UNCACHED(D_002E35C0 + 4), 4);
    __builtin_memcpy(&destination, UNCACHED(D_002E35C0 + 8), 4);
    __builtin_memcpy(&length, UNCACHED(D_002E35C0 + 12), 4);
    if (semaphore >= 0)
        func_00192344(destination, UNCACHED(D_002E35C0 + 16), length);

    switch (command) {
    case 2: {
        ReadFragments *fragments = UNCACHED(D_002E35D4);
        unsigned char *output;
        if (fragments->first_size > 0) {
            output = fragments->first_destination;
            for (index = 0; index < fragments->first_size; ++index)
                output[index] = fragments->first_bytes[index];
        }
        if (fragments->last_size > 0) {
            output = fragments->last_destination;
            for (index = 0; index < fragments->last_size; ++index)
                output[index] = fragments->last_bytes[index];
        }
        break;
    }
    case 11:
        __builtin_memcpy(&extra_destination, UNCACHED(D_002E35D4), 4);
        __builtin_memcpy(extra_destination, UNCACHED(D_002E35D4 + 4), 324);
        break;
    case 12:
        __builtin_memcpy(&extra_destination, UNCACHED(D_002E35D4), 4);
        __builtin_memcpy(extra_destination, UNCACHED(D_002E35D4 + 4), 64);
        break;
    case 23:
    case 25:
    case 26:
        __builtin_memcpy(&extra_destination, UNCACHED(D_002E35D4), 4);
        __builtin_memcpy(&extra_length, UNCACHED(D_002E35D4 + 4), 4);
        if (extra_length > 1024)
            extra_length = 1024;
        func_00192344(extra_destination, UNCACHED(D_002E35D4 + 8), extra_length);
        break;
    }
    if (semaphore < 0) {
        semaphore = -semaphore;
        for (index = 0; index < 32; ++index) {
            if (D_001E5B00[index] == semaphore) {
                D_001E5B00[index] = -1;
                break;
            }
        }
    } else {
        func_001987D0(semaphore);
    }
}
