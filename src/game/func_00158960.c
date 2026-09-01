
typedef struct Item
{
  unsigned char b[0x30];
} Item;
typedef struct Node
{
  unsigned char pad[0x10];
  Item *item;
} Node;
typedef union Slot
{
  long flags;
  struct 
  {
    int lo;
    Node *owner;
  } p;
} Slot;
typedef struct Entry
{
  unsigned char pad[0x20];
  Slot u;
  unsigned char tail[0x18];
} Entry;
extern Entry D_002ABA40[];
int func_00154398(unsigned short index);
int func_0015CA60(unsigned short index, unsigned char kind);
void func_001335B8(Item *item, unsigned short handle, void *arg);
void func_00158868(unsigned short index, void *arg);
int func_00158960(unsigned short index, unsigned char kind, void *arg)
{
  unsigned short handle;
  if (index == 0xFFFF)
  {
    return 0;
  }
  if (func_00154398(index) != 0)
  {
    handle = func_0015CA60(index, kind);
    if (handle != 0)
    {
      func_001335B8((D_002ABA40 + index)->u.p.owner->item, handle, arg);
      return 0;
    }
  }
 do { func_00158868(index, arg); } while (0);
  return -1;
}
