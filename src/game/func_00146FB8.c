
typedef struct
{
  char pad0[0x14];
  short f14;
  short f16;
} St;
extern St *D_001ED3C8;
extern short D_001ED3D0;
extern short D_001ED3D2;
extern int D_001ED3D8;
void func_0011AA88(int a, int b, int c);
void func_0012E390(int a, int b);
void func_00113C18(void);
volatile char func_00138468(int a, int b, int c, short *p);
int func_0012DED8(int a, int b);
void func_00139EB8(int a);
void func_00146FB8(void)
{
  short *new_var;
  switch (D_001ED3C8->f14)
  {
    case 0:
      func_0011AA88(1, 1, 0);
      func_0012E390(1, -1);
      func_00113C18();
      D_001ED3D0 = 0;
      D_001ED3D2 = 9;
      func_00138468(0x20, 0, 1, &D_001ED3D0);
      (*((St * volatile *) (&D_001ED3C8)))->f16 = 0x78;
      (*((St * volatile *) (&D_001ED3C8)))->f14++;
      break;

    case 1:
      if (((*D_001ED3C8).f16--) < 0)
    {
      if (func_0012DED8(1, 0) == 0)
      {
        D_001ED3D0 = 0;
        func_00138468(0x1B, 0, 1, new_var = &D_001ED3D0);
        func_00139EB8(D_001ED3D8);
      }
      else
      {
        D_001ED3D0 = 0;
        D_001ED3D2 = 0;
        func_00138468(0x20, 0, 1, &D_001ED3D0);
        func_00139EB8(D_001ED3D8);
      }
    }
      break;

  }

}
