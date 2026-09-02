/* Authentic Sony/newlib soft-float helper names used by dtoa.c. */
dpadd = 0x00185CB8;
dpsub = 0x00185D10;
dpmul = 0x00185D78;
dpdiv = 0x00186020;
dpcmp = 0x001862A0;
litodp = 0x001862F0;
dptoli = 0x001863A8;

/* Sony EE compiler runtime helpers emitted by 64-bit integer operations. */
__muldi3 = 0x00187180;
__udivdi3 = 0x001A24E8;
__umoddi3 = 0x001A2AB8;

/* Single-precision sqrt fallback. gcc expands the sqrtf builtin to a hardware
   sqrt.s plus a NaN check that calls this helper by its declared name, so the
   reference cannot be spelled as an address-named symbol. 0x0018B5F8 carries
   mov.s/lwc1/swc1, i.e. genuine single-precision work, and is reached from 22
   call sites. The double wrapper at 0x0018B3E8 is a DIFFERENT function with no
   FPU instructions at all; do not alias sqrtf onto it. */
sqrtf = 0x0018B5F8;
