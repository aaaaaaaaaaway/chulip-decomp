/* Create the CDVD callback worker, or update its existing thread priority. */
typedef struct {
    int status;
    void (*entry)(void);
    void *stack;
    int stack_size;
    void *gp;
    int initial_priority, current_priority;
    unsigned int attributes, option;
} Thread;
typedef struct {
    Thread thread;
    unsigned int wait_type, wait_id, wakeup_count;
} ThreadStatus;
extern int D_001E3154[], D_002DE910[];
extern ThreadStatus D_002DE918;
extern Thread D_002DE948;
extern char D_001F4870[];
extern void func_0018EC78(void);
extern int func_00198690(void);
extern int func_001986A0(int, ThreadStatus *);
extern int func_001985A0(Thread *);
extern int func_001985C0(int, void *);
extern int func_00198630(int, int);
int func_0018ED38(int priority, void *stack, int stack_size) {
    int result = 1;
    if (D_001E3154[0] == 0) {
        D_002DE910[0] = func_00198690();
        func_001986A0(D_002DE910[0], &D_002DE918);
        D_002DE948.stack_size = stack_size;
        D_002DE948.gp = D_001F4870;
        D_002DE948.entry = func_0018EC78;
        D_002DE948.stack = stack;
        D_002DE948.initial_priority = priority;
        D_001E3154[0] = func_001985A0(&D_002DE948);
        func_001985C0(D_001E3154[0], 0);
    } else {
        func_00198630(D_001E3154[0], priority);
        result = 0;
    }
    return result;
}
