/* DMA-controller environment configuration. Hardware accesses are volatile;
 * lookup tables and saved environment remain owned by their existing data. */
typedef struct {
    unsigned char stall_source;
    unsigned char stall_drain;
    unsigned char memory_drain;
    unsigned char release_cycle;
    unsigned short priority_high;
    unsigned short priority_low;
    unsigned short skip_qwords;
    unsigned short transfer_qwords;
    void *ring_base;
    unsigned int ring_size;
} DmaEnvironment;

extern unsigned char D_001E3048[];
extern unsigned char D_001E3058[];
extern unsigned char D_001E3068[];
extern DmaEnvironment D_001E3078;

#define DMA_CONTROL (*(volatile unsigned int *)0x1000E000)
#define DMA_PRIORITY (*(volatile unsigned int *)0x1000E020)
#define DMA_SKIP (*(volatile unsigned int *)0x1000E030)
#define DMA_RING_BASE (*(volatile unsigned int *)0x1000E050)
#define DMA_RING_SIZE (*(volatile unsigned int *)0x1000E040)

int func_001886B8(DmaEnvironment *environment)
{
    unsigned int control = DMA_CONTROL;
    unsigned int priority = DMA_PRIORITY;
    unsigned int skip = DMA_SKIP;
    unsigned int ring_base = DMA_RING_BASE;
    unsigned int ring_size = DMA_RING_SIZE;

    if (environment->stall_source >= 10) {
        return -1;
    }
    if (environment->stall_drain >= 10) {
        return -2;
    }
    if (environment->memory_drain >= 10) {
        return -3;
    }
    if (environment->release_cycle >= 7) {
        return -4;
    }

    control = (control & ~0x30) | (D_001E3048[environment->stall_source] << 4);
    control = (control & ~0xC0) | (D_001E3058[environment->stall_drain] << 6);
    control = (control & ~0x0C) | (D_001E3068[environment->memory_drain] << 2);
    if (environment->release_cycle != 0) {
        control |= 2;
        control = (control & ~0x300) | ((environment->release_cycle - 1) << 8);
    } else {
        control &= ~2;
    }
    priority = (environment->priority_high << 16) | environment->priority_low;
    skip = (environment->transfer_qwords << 16) | environment->skip_qwords;
    ring_base = (unsigned int)environment->ring_base;
    ring_size = environment->ring_size;

    DMA_CONTROL = control;
    DMA_PRIORITY = priority;
    DMA_SKIP = skip;
    DMA_RING_BASE = ring_base;
    DMA_RING_SIZE = ring_size;
    D_001E3078 = *environment;
    return 0;
}
