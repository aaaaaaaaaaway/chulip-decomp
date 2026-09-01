typedef struct {
    char pad00[0x18];
    char *verts0;
    char *verts1;
    int *indices0;
    int *indices1;
    char pad28[8];
    int count0;
    int count1;
    char *groups0;
    char *groups1;
    char pad40[0x10];
    char **bufs0;
    char **bufs1;
} Model0017A888;

int func_0017A938();

void func_0017A888(Model0017A888 *model) {
    int i;

    for (i = 0; i < model->count0; i++) {
        func_0017A938(model->groups0 + i * 16, i, model->bufs0, model->verts0, model->indices0);
    }
    for (i = 0; i < model->count1; i++) {
        func_0017A938(model->groups1 + i * 16, i, model->bufs1, model->verts1, model->indices1);
    }
}
