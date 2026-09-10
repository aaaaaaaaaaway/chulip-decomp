typedef float Vec4[4] __attribute__((aligned(16)));
typedef struct {
    int active, width, depth;
    float height[10][10], velocity[10][10];
    Vec4 normal[10][10];
    float origin[3], phase;
    int color[4];
} Board;
extern Board *D_001ED188[1];
extern int D_001ED190;
extern float D_001EDCC0[];
extern int func_00113228(void *, int);
extern void func_00111DF0(Board *);
extern int func_00120BE0(int *, float *, float *);
int func_001114F8(unsigned char *packet, int count, int unused) {
    Vec4 p0, p1, p2, p3;
    int s0[4], s1[4], s2[4], s3[4];
    unsigned char *head;
    int n, total, i, j;
    float force;
    Board *board;
    if (D_001ED190 != 0)
        return 0;
    head = packet;
    packet += 16;
    head[3] = 0x10;
    total = func_00113228(packet, 0x1018);
    packet += total * 16;
    *(unsigned long *)(packet + 0) = 0x1000000000008001UL;
    *(unsigned long *)(packet + 8) = 14;
    *(unsigned long *)(packet + 24) = 8;
    *(unsigned long *)(packet + 16) = 5;
    packet += 32;
    *(unsigned long *)(packet + 0) = 0x1000000000008001UL;
    *(unsigned long *)(packet + 8) = 14;
    *(unsigned long *)(packet + 16) = 0x8000000048UL;
    *(unsigned long *)(packet + 24) = 0x42;
    packet += 32;
    *(unsigned long *)(packet + 0) = 0x1000000000008001UL;
    *(unsigned long *)(packet + 8) = 14;
    *(unsigned long *)(packet + 24) = 0x42;
    *(unsigned long *)(packet + 16) = 0x8000000044UL;
    packet += 32;
    total += 6;
    p0[3] = 1.0f;
    p1[3] = 1.0f;
    p2[3] = 1.0f;
    p3[3] = 1.0f;
    for (n = 0; n < count; n++) {
        board = &D_001ED188[0][n];
        if (board->active != 1)
            continue;
        if (board->phase == 0.0f)
            board->height[5][5] = 50.0f;
        board->phase = (float)((int)(board->phase + 1.0f) % 40);
        func_00111DF0(board);
        for (i = 1; i < 9; i++) {
            for (j = 1; j < 9; j++) {
                force = 0.0f;
                force += board->height[i][j] - board->height[i][j - 1];
                force += board->height[i][j] - board->height[i][j + 1];
                force += board->height[i][j] - board->height[i - 1][j];
                force += board->height[i][j] - board->height[i + 1][j];
                force += (board->height[i][j] - board->height[i - 1][j - 1]) * 0.5f;
                force += (board->height[i][j] - board->height[i - 1][j + 1]) * 0.5f;
                force += (board->height[i][j] - board->height[i + 1][j - 1]) * 0.5f;
                force += (board->height[i][j] - board->height[i + 1][j + 1]) * 0.5f;
                board->velocity[i][j] += force / 6.0f * 0.45f;
                board->velocity[i][j] -= board->height[i][j] * 0.6f;
                board->velocity[i][j] *= 0.985f;
            }
        }
        for (i = 0; i < 10; i++)
            for (j = 0; j < 10; j++)
                board->height[i][j] += board->velocity[i][j];
        for (i = 0; i < 9; i++) {
            for (j = 0; j < 9; j++) {
                p0[0] = board->origin[0] + (float)((j)*board->width / 10);
                p0[1] = board->origin[1] + board->height[i][j];
                p0[2] = board->origin[2] + (float)((i)*board->depth / 10);
                if (func_00120BE0(s0, D_001EDCC0, p0) != 0)
                    continue;
                p1[0] = board->origin[0] + (float)((j + 1) * board->width / 10);
                p1[1] = board->origin[1] + board->height[i][j + 1];
                p1[2] = board->origin[2] + (float)((i)*board->depth / 10);
                if (func_00120BE0(s1, D_001EDCC0, p1) != 0)
                    continue;
                p2[0] = board->origin[0] + (float)((j)*board->width / 10);
                p2[1] = board->origin[1] + board->height[i + 1][j];
                p2[2] = board->origin[2] + (float)((i + 1) * board->depth / 10);
                if (func_00120BE0(s2, D_001EDCC0, p2) != 0)
                    continue;
                p3[0] = board->origin[0] + (float)((j + 1) * board->width / 10);
                p3[1] = board->origin[1] + board->height[i + 1][j + 1];
                p3[2] = board->origin[2] + (float)((i + 1) * board->depth / 10);
                if (func_00120BE0(s3, D_001EDCC0, p3) != 0)
                    continue;
                *(unsigned long *)(packet + 0) = 0x5022400000008001UL;
                *(unsigned long *)(packet + 8) = 0x44441;
                packet += 16;
                *(int *)(packet + 0) = board->color[0];
                *(int *)(packet + 4) = board->color[1];
                *(int *)(packet + 8) = board->color[2];
                *(int *)(packet + 12) = board->color[3];
                *(int *)(packet + 16) = s0[0];
                *(int *)(packet + 20) = s0[1];
                *(int *)(packet + 24) = s0[2];
                *(int *)(packet + 28) = 0x8000;
                *(int *)(packet + 32) = s1[0];
                *(int *)(packet + 36) = s1[1];
                *(int *)(packet + 40) = s1[2];
                *(int *)(packet + 44) = 0x8000;
                *(int *)(packet + 48) = s2[0];
                *(int *)(packet + 52) = s2[1];
                *(int *)(packet + 56) = s2[2];
                *(int *)(packet + 60) = 0;
                *(int *)(packet + 64) = s3[0];
                *(int *)(packet + 68) = s3[1];
                *(int *)(packet + 72) = s3[2];
                *(int *)(packet + 76) = 0;
                packet += 80;
                *(unsigned long *)(packet + 0) = 0x90AA400000008001UL;
                *(unsigned long *)(packet + 8) = 0x434343431UL;
                packet += 16;
                *(int *)(packet + 0) = board->color[0];
                *(int *)(packet + 4) = board->color[1];
                *(int *)(packet + 8) = board->color[2];
                *(int *)(packet + 12) = board->color[3];
                *(int *)(packet + 16) = (int)(board->normal[i][j][0] + 512.0f);
                *(int *)(packet + 20) = (int)(board->normal[i][j][1] + 768.0f);
                *(int *)(packet + 24) = 0;
                *(int *)(packet + 28) = 0;
                *(int *)(packet + 48) = (int)(board->normal[i][j + 1][0] + 512.0f);
                *(int *)(packet + 52) = (int)(board->normal[i][j + 1][1] + 768.0f);
                *(int *)(packet + 56) = 0;
                *(int *)(packet + 60) = 0;
                *(int *)(packet + 80) = (int)(board->normal[i + 1][j][0] + 512.0f);
                *(int *)(packet + 84) = (int)(board->normal[i + 1][j][1] + 768.0f);
                *(int *)(packet + 88) = 0;
                *(int *)(packet + 92) = 0;
                *(int *)(packet + 112) = (int)(board->normal[i + 1][j + 1][0] + 512.0f);
                *(int *)(packet + 116) = (int)(board->normal[i + 1][j + 1][1] + 768.0f);
                *(int *)(packet + 120) = 0;
                *(int *)(packet + 124) = 0;
                *(int *)(packet + 32) = s0[0];
                *(int *)(packet + 36) = s0[1];
                *(int *)(packet + 40) = s0[2];
                *(int *)(packet + 44) = 0x8000;
                *(int *)(packet + 64) = s1[0];
                *(int *)(packet + 68) = s1[1];
                *(int *)(packet + 72) = s1[2];
                *(int *)(packet + 76) = 0x8000;
                *(int *)(packet + 96) = s2[0];
                *(int *)(packet + 100) = s2[1];
                *(int *)(packet + 104) = s2[2];
                *(int *)(packet + 108) = 0;
                *(int *)(packet + 128) = s3[0];
                *(int *)(packet + 132) = s3[1];
                *(int *)(packet + 136) = s3[2];
                *(int *)(packet + 140) = 0;
                packet += 144;
                total += 16;
            }
        }
    }
    *(unsigned short *)head = total;
    return total + 1;
}
