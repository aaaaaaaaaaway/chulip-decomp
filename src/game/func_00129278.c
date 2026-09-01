
extern char D_001E6F78[];
extern char D_001E6F90[];
extern char D_001EC920[];
extern char D_001EC928[];
extern void func_0017C9C0(void);
extern int func_00137F98(void);
extern void func_00192660(char *buffer, const char *format, int value);
extern void func_0017C970(char *path);
extern void func_00192940(char *dst, const char *src);
extern void func_001926D0(char *buffer, const char *suffix);
extern void func_0017C830(int a, int b, char *first, char *second);
void func_00129278(void)
{
  char primary[0x20];
  char secondary[0x20];
  char path[0x20];
  func_0017C9C0();
 do { func_00192660(path, D_001E6F78, func_00137F98()); func_0017C970(path); func_00192660(primary, D_001E6F90, func_00137F98()); func_00192940(secondary, primary); func_001926D0(secondary, D_001EC920); } while (0);
  func_001926D0(primary, D_001EC928);
  func_0017C830(1, 1, primary, secondary);
}
