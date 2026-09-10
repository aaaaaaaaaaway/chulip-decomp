typedef float Vector[4] __attribute__((aligned(16)));
typedef struct {
    Vector position, velocity;
} Particle;
typedef struct {
    int color[4] __attribute__((aligned(16)));
    int active;
    int timers[40];
    int unknownB4[3];
    Vector trails[40][6];
    Particle particles[200];
    float height[26][23], velocity[26][23];
    Vector normals[26][23];
    Vector columns[5][7];
} Environment;
/* One four-byte pointer slot; the original declaration is unknown. */
extern Environment *D_001ED258[1];
typedef struct {
    long lo, hi;
} Qword;
typedef int IntVector[4] __attribute__((aligned(16)));
typedef struct {
    int u, v, unused, reserved, x, y, z, control;
} Vertex;
typedef struct {
    int r, g, b, a;
    Vertex vertex[4];
} Quad;
extern float D_001EDCC0[];
extern int func_00120BE0(IntVector, float *, Vector);
int func_001230E8(Qword *packet) {
    float origin[3];
    Vector p0, p1, p2, p3;
    IntVector s0, s1, s2, s3;
    int i, j, total;
    Quad *quad;
    packet[0].lo = 0x1000000000008001L;
    packet[0].hi = 14;
    packet[1].hi = 8;
    packet[1].lo = 0x1003f1003ffL;
    packet += 2;
    total = 2;
    origin[0] = 9181.85f;
    origin[1] = 50.0f;
    origin[2] = 2650.77f;
    p0[3] = 1.0f;
    p1[3] = 1.0f;
    p2[3] = 1.0f;
    p3[3] = 1.0f;
    for (i = 0; i < 25; i++) {
        for (j = 0; j < 22; j++) {
            p0[0] = origin[0] + (j - 18) * 48.0f;
            p0[1] = origin[1] + D_001ED258[0]->height[i][j];
            p0[2] = origin[2] + (i - 13) * 48.0f;
            if (func_00120BE0(s0, D_001EDCC0, p0))
                continue;
            p1[0] = origin[0] + (j - 17) * 48.0f;
            p1[1] = origin[1] + D_001ED258[0]->height[i][j + 1];
            p1[2] = origin[2] + (i - 13) * 48.0f;
            if (func_00120BE0(s1, D_001EDCC0, p1))
                continue;
            p2[0] = origin[0] + (j - 18) * 48.0f;
            p2[1] = origin[1] + D_001ED258[0]->height[i + 1][j];
            p2[2] = origin[2] + (i - 12) * 48.0f;
            if (func_00120BE0(s2, D_001EDCC0, p2))
                continue;
            p3[0] = origin[0] + (j - 17) * 48.0f;
            p3[1] = origin[1] + D_001ED258[0]->height[i + 1][j + 1];
            p3[2] = origin[2] + (i - 12) * 48.0f;
            if (func_00120BE0(s3, D_001EDCC0, p3))
                continue;
            packet[0].lo = 0x1000000000008001L;
            packet[0].hi = 14;
            packet[1].hi = 0x42;
            packet[1].lo = 0x8000000048L;
            packet += 2;
            packet[0].lo = 0x90aa400000008001L;
            packet[0].hi = 0x434343431L;
            packet++;
            quad = (Quad *)packet;
            quad->r = 140;
            quad->g = 180;
            quad->b = 200;
            quad->a = 32;
            total += 12;
            quad->vertex[0].u = D_001ED258[0]->normals[i][j][0] + 512.0f;
            quad->vertex[0].v = D_001ED258[0]->normals[i][j][1] + 512.0f;
            quad->vertex[0].unused = 0;
            quad->vertex[0].reserved = 0;
            quad->vertex[1].u = D_001ED258[0]->normals[i][j + 1][0] + 512.0f;
            quad->vertex[1].v = D_001ED258[0]->normals[i][j + 1][1] + 512.0f;
            quad->vertex[1].unused = 0;
            quad->vertex[1].reserved = 0;
            quad->vertex[2].u = D_001ED258[0]->normals[i + 1][j][0] + 512.0f;
            quad->vertex[2].v = D_001ED258[0]->normals[i + 1][j][1] + 512.0f;
            quad->vertex[2].unused = 0;
            quad->vertex[2].reserved = 0;
            quad->vertex[3].u = D_001ED258[0]->normals[i + 1][j + 1][0] + 512.0f;
            quad->vertex[3].v = D_001ED258[0]->normals[i + 1][j + 1][1] + 512.0f;
            quad->vertex[3].unused = 0;
            quad->vertex[3].reserved = 0;
            quad->vertex[0].x = s0[0];
            quad->vertex[0].y = s0[1] + 16;
            quad->vertex[0].z = s0[2];
            quad->vertex[0].control = 0x8000;
            quad->vertex[1].x = s1[0];
            quad->vertex[1].y = s1[1] + 16;
            quad->vertex[1].z = s1[2];
            quad->vertex[1].control = 0x8000;
            quad->vertex[2].x = s2[0];
            quad->vertex[2].y = s2[1] + 16;
            quad->vertex[2].z = s2[2];
            quad->vertex[2].control = 0;
            quad->vertex[3].x = s3[0];
            quad->vertex[3].y = s3[1] + 16;
            quad->vertex[3].z = s3[2];
            quad->vertex[3].control = 0;
            packet = (Qword *)(quad + 1);
        }
    }
    return total;
}
