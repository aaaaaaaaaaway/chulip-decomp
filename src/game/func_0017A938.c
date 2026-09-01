
typedef struct 
{
  int first;
  int slot;
  char pad08[4];
  int count;
} Grp0017A938;
void func_0018A680();
void func_0017A938(Grp0017A938 *grp, int unused, char **bufs, char *verts, int *indices)
{
  int i;
  for (i = 0; i < grp->count; i++)
  {
    func_0018A680(bufs[grp->slot] + (i * 16), verts + (indices[grp->first + i] * 16));
  }

}
