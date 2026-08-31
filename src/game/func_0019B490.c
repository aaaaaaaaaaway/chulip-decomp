typedef struct Node { int key; int pad[13]; struct Node *next; } Node;
typedef struct Bucket { int pad[2]; Node *list; int pad2[2]; struct Bucket *next; } Bucket;
typedef struct { int pad[10]; Bucket *buckets; } Root;
Node *func_0019B490(int key, Root *r)
{
    Bucket *b;
    Node *n;

    for (b = r->buckets; b != 0; b = b->next) {
        for (n = b->list; n != 0; n = n->next) {
            if (n->key == key) return n;
        }
    }
    return 0;
}
