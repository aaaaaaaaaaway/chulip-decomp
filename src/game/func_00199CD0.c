/* Read queued DECI2 TTY bytes, stopping after a newline or carriage return. */
typedef struct Queue {
    int capacity;
    volatile int count;
    char *read;
    char *write;
} Queue;
typedef struct Tty {
    int socket, write_length, read_length, writing;
    char *write_buffer, *read_buffer;
    Queue *queue;
} Tty;
extern Tty D_002E0B10;
extern Queue *D_002E0B28[];
extern void func_001999A8(Queue *);

int func_00199CD0(char *buffer, int length) {
    int i;
    for (i = 0; i < length; ++i) {
        while (!D_002E0B28[0]->count) {
        }
        buffer[i] = *D_002E0B10.queue->read;
        func_001999A8(D_002E0B10.queue);
        if (buffer[i] == '\n' || buffer[i] == '\r')
            return i + 1;
    }
    return i;
}
