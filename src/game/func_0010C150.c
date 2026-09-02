typedef unsigned int u32;
typedef unsigned long u64;

/* sin() and cos() over a full-circle angle in radians. */
float func_0018B210(float angle);
float func_0018B2F8(float angle);

/* Build a GS GIF packet that draws an ellipse outline as one gouraud,
 * alpha-blended LINE_STRIP.  The packet is a GIFtag (NLOOP = segments + 2,
 * EOP, PRE, PRIM = LINE_STRIP|IIP|ABE, NREG = 2) followed by RGBAQ/XYZ2
 * register pairs.  The first vertex carries the colour and the centre
 * position with its ADC bit set, so it only seeds the strip; the loop then
 * emits segments + 1 points around the ellipse.  Returns the packet size in
 * quadwords.
 */
int func_0010C150(u32 *packet, int cx, int cy, int z,
                  int r, int g, int b, int a,
                  float rx, float ry, int segments)
{
    u32 *p;
    int i;
    int qwords;

    *(u64 *)packet = ((segments + 2) | 0x8000) | ((u64)0x809B << 46);
    *((u64 *)packet + 1) = 0x41;

    p = packet;
    p += 4;
    p[0] = r;
    p[1] = g;
    p[2] = b;
    p[3] = a;
    p[7] = 0x8000;
    p[4] = cx;
    p[5] = cy;
    p[6] = z;
    p += 8;
    qwords = 3;

    for (i = 0; i <= segments; i++) {
        float t = i * 2 * 3.1415926f / segments;
        float fx = cx;
        float fy = cy;

        p[0] = 0;
        p[1] = 0;
        p[2] = 0;
        p[3] = 0;
        p[4] = (int)(fx + rx * func_0018B210(t));
        fy += ry * func_0018B2F8(t);
        p[5] = (int)fy;
        p[6] = z;
        p[7] = 0;
        p += 8;
        qwords += 2;
    }

    return qwords;
}
