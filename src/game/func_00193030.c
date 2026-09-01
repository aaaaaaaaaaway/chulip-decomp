typedef struct {
    int field_0;
    int field_4;
    int field_8;
} Job;

extern int func_00196638(int argument, Job *job);

int func_00193030(int argument, Job *job) {
    int result;

    if (job->field_8 == 0) {
        job->field_4 = 0;
        return 0;
    }
    result = func_00196638(argument, job);
    job->field_8 = 0;
    job->field_4 = 0;
    return result;
}
