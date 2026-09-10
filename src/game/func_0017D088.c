typedef struct {
    int count;
    void *parts;
    int unknown08;
    void *packet;
    float transferred;
} Model;
typedef struct {
    unsigned char unknown00[8];
    void *model_data;
} Template;
void func_0017F7F8(void);
void func_0017F7E8(void);
void *func_00151A20(int);
void *func_00151A00(int);
int func_0017D178(Model *, void *, unsigned int);
unsigned char *func_001545B8(unsigned short);
void *func_0017D998(Model *, unsigned char *);

Model *func_0017D088(Template *source, unsigned int id, Model *model) {
    int special = 0;
    if ((id - 0x11cU) < 0x40 || (id - 1U) < 0xfb ||
        (id - 0x3a0U) < 0xb8 || id == 0)
        special = 1;
    func_0017F7F8();
    func_0017F7E8();
    if (model == 0) {
        if (special)
            model = func_00151A20(20);
        else
            model = func_00151A00(20);
    }
    if (!func_0017D178(model, source->model_data, id))
        return 0;
    model->packet = func_0017D998(model, func_001545B8(id));
    return model;
}
