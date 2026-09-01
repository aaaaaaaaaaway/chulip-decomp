# claude_fable_isel — three instruction-selection walls (2026-09-01)

## Wall 1 — 64-bit literal synthesis: SOLVED (4 matches)

Mechanism: SN cc1 emits every 64-bit constant as one `dli $r,CONST` pseudo and the
ASSEMBLER synthesises it. GNU `as` (all five ps2-bundle builds byte-identical here)
synthesises `lui/dsll32 0/ori`; `Ps2EeAs`/`ps2eeas` (both 1.36-bundled and 273a's
1.8.19.316) finds the minimal shifted form: `ori $r,$zero,H / dsll32 $r,N / ori $r,L`
— exactly retail. Proof inputs: `asmtest/dli.s` assembled with 9 assembler builds.
Nothing "selects a strategy": the two assembler families simply differ, and the
existing `ee-gcc2.95.3-136-O2-G8-ps2as` profile is the retail one for this family.
Previous lanes failed because they iterated C spellings under GNU-as profiles.

Matches (manifest work/claude/fable-isel.jsonl, all byte-verified):
- func_0015F0B0, func_0015F4E0, func_00134A08 (identical GS-packet builders):
  key shape = char* parameter reassigned (`packet += 0x10`) with the original
  saved in a Header* local first; store order count,type then body 0,1,3,2.
- func_0017FBB0: same + `long cmd = 0x47;` local hoists that constant.
- ~133 unreconstructed functions contain the same `ori $zero/dsll32` signature
  (list reproducible via ori-zero/dsll32 scan of asm_index). All become approachable
  under the -ps2as profile. (The lqc2/qmtc2 ones among them stay VU0-blocked.)
- Ps2EeAs pads .text to 8: function sizes not divisible by 8 need range_end at the
  next function (retail has the same nop pad there — verified at 0x17FBFC).

## Wall 3 — hazard nop counts: mechanism proven; needs an SN assembler build not on disk

Every case decomposes into exactly TWO assembler rules plus one already-known one:

1. R5900 short-loop erratum pad (the "load;nop;branch" cases are NOT load hazards).
   Ps2EeAs 1.36 (Mips personality, processor hardcoded 0x170C at init 0x405113):
   for a BACKWARDS branch with displacement d insns, if -6 < d < 0 it inserts
   (d+6) nops, i.e. pads the loop body (label..branch exclusive) to 5 instructions.
   Code: 0x404d70 (gate: processor==0x170C, hardcoded) -> 0x404d90; threshold is the
   IMMEDIATES `cmp si,0xfffa` (=-6) at 0x404db6 and `lea esi,[eax+6]` at 0x404de9.
   No option or directive writes them or the processor id (full single-dash and
   double-dash option tables enumerated; `--no-nops` sets write-only global 0x561e48;
   `-divbug-on`/`-imm15`/`-arm` crash the single-dash parser under wibo; `--trap/
   --break/-O0..3/-sn/-Wdivbug-on` verified no effect).
   RETAIL pads the same loops to 4 (func_001263D8: beqz,nop,lhu,nop,bnel = body 4;
   func_00161988 $L11 call-loop: move,jal,addu,nop = body 4). ps2eeas 1.8.19.316
   (273a) has no such rule; every GNU as build has none. God Hand's byte-verified
   reconstruction uses the same constant (_SHORT_LOOP_MIN_PRE = 4).
   Content of the loop is irrelevant (padding fires for addu-only bodies too);
   register hazards are NOT involved (lhu->bnel same-reg at distance >5 gets 0 nops).

2. FDIV setup pad: retail carries `nop;nop` immediately before div.s in ~171 retail
   sites / 84 unreconstructed functions (193 sites in other TUs are unpadded, 19
   have one nop that is the known mtc1 hazard — the pad is per-TU, not per-site;
   exactly the God Hand finding, their rule vocabulary fdiv/div1/bare).
   NO on-disk assembler emits it (Ps2EeAs 1.36, ps2eeas 1.8.19, five GNU as builds,
   Sony ee-as 2.9-990721/991111, 2.12-ee: all 0 nops for cvt.s.w->div.s).
   NO SN cc1 can emit it: 2.95.2/2.95.3 cc1.exe binaries contain only the bare
   `div.s %0,%1,%2` template (strings-proven). Sony ee-gcc 2.96 cc1 contains
   `%(nop\n\tnop\n\tdiv.s %0,%1,%2%)` behind -mhandle-ee-div-pipeline-bug and emits
   retail's exact sequence — but 2.96 codegen diverges elsewhere (register
   allocation/scheduling; ~20 source+flag variants tried on func_0013F468, best
   result one register-pair off) and the SN 2.95.3 profile byte-matches the whole
   function EXCEPT the two nops (branch offset shifts 0x10->0x0E purely from them):
   evidence/match_ev.py run of work/lanes/claude_w1213/func_0013F468.c under
   ee-gcc2.95.3-136-O2-G8-ps2as.

3. mtc1->cvt 1 nop: already known, both ps2eeas builds and Sony 2.9 as emit it.

Conclusion: retail was assembled by a LATER SN ps2eeas than either on-disk build —
same rule engine, with short-loop threshold 4 (not 5) and an added unconditional
2-nop FDIV pad. Both constants are code immediates in 1.36; there is no dial.
Blocked until such a build is found (ProDG 2001/2002 era) or the project sanctions
a byte-verified assembler post-pass like God Hand's (fp_hazard_nops/call_loop_pad
in /tmp/chulip-god-hand-anchor/scripts/ee-cc-wrap.py — their retail is also
non-mechanical per-TU, so they gate it per TU and re-verify bytes).
Affected inventory: 84 (fdiv) + 42 (short-loop) unreconstructed functions, overlap 2.
NOTE the flip side: TUs with unpadded div.s or natural body-4 loops must AVOID the
future padding toolchain — per-TU toolchain flavor selection is real in this binary.

## Wall 2 — quadword copy helpers: not producible by any available compiler

func_00161328/001613D8 (lq $a2,0($a1); sq $a2,0($a0); jr; nop) and
func_0018A680 (same but sq in the delay slot) / func_0018A690 (4x lq a2,a3,t0,t1
then 4x sq, last in delay slot).

Survey of every compiler on disk with 16/64-byte copies (long long deref, struct
assign, __builtin_memcpy, mode(TI), aligned+unaligned, -O1/2/3/s, -fno-regmove,
-fno-schedule-insns, return-dst variants):
- SN 2.95.2-273a/274: ld/sd pairs, temps $2/$3 (no lq for this shape)
- SN 2.95.3-136:      lq/sq interleaved, temps $2/$3
- SN 2.95.3-114:      lq/sq interleaved, temps $2/$3
- SN 2.95.3-107:      RETAIL GROUPING for memcpy(64) (4 lq then 4 sq) but temps
                      $2,$3,$6,$7; return-dst shifts to $3,$6,$7,$8 (v0 live)
- Sony 2.9-990721/991111, 2.96: lq $2 (TImode); long long is 8 bytes there
- Sony gcc 3.2-ee: lq $15/$14
- MWCC 3.0b22: ld/sd $3
The scratch registers come from the block-move expander's pseudos, colored v0-first;
no natural-C shape can exclude BOTH v0 and v1 in a function this small (any use that
keeps them live emits an instruction retail does not have). The 5 SN builds give 3
different block-move shapes, so the expander churned per build; retail's a2..t1 set
means its build either used fixed scratch or a different coloring — not on disk.
Decisive extra evidence for handwritten origin: the SAME 3-instruction body appears
BOTH with the sq in the jr delay slot (0x18A680, SDK band) and with an unfilled
slot (0x161328/13D8, game band); no single toolchain configuration produces both,
while hand-written .s reproduces each verbatim (`lq $6.. sq $6.. jr` assembles
byte-exact through BOTH bundled assemblers, asmtest/hand.s). Recommend catalog
`handwritten: true` for all four; a register-pinned C source would match but is the
banned anti-pattern.

## Evidence files
- asmtest/: dli.s + per-assembler objects, fpu.s (mtc1/cvt/div), hand.s
- evidence/: match_ev.py (match.py + EXTRA_CC1_FLAGS/EV_TOOLCHAINS override, evidence
  only, never for manifests), toolchains_ev.json (2.96+Ps2EeAs profiles),
  func_0013F468 variants
- scratchpad ps2eeas136.dis: full Ps2EeAs 1.36 disassembly used for the option-table
  and hazard-logic proofs (option parser 0x403dd9..404796; .set handler 0x4164xx;
  nop machinery 0x404e20/30/40, per-insn counters 0x439164/090/120/124/128,
  last-writer 0x43916c; divbug 0x40bcf0 with hardcoded thresholds, -Wdivbug-on gates
  warnings only at 0x561e04; short-loop pad 0x404d70/404d90)
