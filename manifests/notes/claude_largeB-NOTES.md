# claude_largeB lane notes

## Matched (16 / 5,004 bytes) -- manifest work/claude/largeB.jsonl

## Parked near-misses (sources in near/), one-line diagnosis each

- func_0017A5B8 (268)  everything matches except retail's leading `daddu $t0,$a1,$zero`:
  retail's second parameter is allocated to $t0, ours stays in $a1. Pure local_alloc
  ordering; 3 extra-arg / register / const-qualifier variants tried.
- func_00115C80 (376)  instruction-for-instruction identical; only the callee-saved
  register *assignment* differs (retail s0-s3 = the four u args, s4/s5 = the two colour
  args; ours interleaves). ~3.5k statement permutations plateau at byte 0x54.
- func_00126490 (296)  ALL words match except the last loop has one nop too many.
  See "short-loop padding" below.
- func_00125CD8 (292)  ALL words match except the do/while loop has one nop too few.
  See "short-loop padding" below.
- func_00137740 (444)  identical modulo 2 nops in the `while (f(0,0)==0)` loop.
  See "short-loop padding" below.
- func_0017FA98 (276)  correct shape; retail coalesces the mutable index with the
  incoming parameter register (s0) and keeps a copy of n in s3, and does not fold
  `n+1` / `n+2`; ours allocates the other way round and folds. 6 spellings tried.
- func_00146FB8 (308)  byte-exact except two adjacent independent `sh` stores to
  D_001ED3D0 / D_001ED3D2 are emitted in the opposite order. Both source orders and a
  4-byte-struct spelling give the identical (wrong) schedule; GCC canonicalises.
- func_00179F70 (548)  frame size and structure right; retail assigns spill slots
  0x30/0x34/0x38 to base/flag/k, ours puts k at 0x34 -- everything downstream shifts.
- func_0012F070 (416)  first 0x24 bytes differ only because retail hoists the switch's
  `li $v0,1` above the 0x40-byte ldl/ldr block copy, shifting the copy temp registers.
  All 24 top-statement permutations plateau there.
- func_0017EAD0 (360)  two instructions short: retail recomputes `addu $v0,$s2,$s0`
  for the `f06` read instead of reusing the record pointer (a base+index operand-order
  effect that `(base+i)->f` did not reproduce).
- func_0015EC38 (268)  BLOCKED: needs `lw $v0,%gp_rel(D_001ECD24)($gp)` outside any
  delay slot. Unreachable -- see below.

## Structural blockers proven in this lane

1. **`%gp_rel` outside a branch delay slot is unreachable.** Ps2EeAs only expands a
   small-data pseudo GP-relatively when it sits in a `.set nomacro` region (i.e. a
   delay slot); everywhere else it emits the absolute `lui`+`%lo` macro. Retail
   functions that reference a small global GP-relatively in ordinary code were
   compiled with the symbol *defined* in that translation unit (`-mgpopt` style
   `%gp_rel` emitted by the compiler itself). No extern spelling, and no local
   definition either, reproduces it under the available profiles.
   `python3 work/lanes/claude_largeB/tri3.py` flags these: 66 of the 237 remaining
   large_B functions.
2. **Short-loop nop padding is off by one.** The retail assembler pads a loop whose
   body (branch target through delay slot) is shorter than 6 instructions up to
   exactly 6 nops-included; the bundled `Ps2EeAs.exe` pads the same loop to 7, and the
   bundled GNU `as` does not pad at all. Every function containing a loop of <6
   instructions is therefore unmatchable by exactly one nop under either assembler.
   Measured on func_00126490 (retail 6 / ps2as 7), func_00125CD8 (retail 6 / gas 5 /
   ps2as 7) and func_00137740 (retail 6 / gas 4 / ps2as 7).
   tri3.py flags 24 more of these.

## Tools left in this lane
- tri3.py       triage/blocker scan over work/claude/large_B.txt
- d.py          retail asm dump by function name
- mm.py         match.py wrapper printing only the differing words
- climb.py      generic hill-climb over statement orderings (score = first differing byte)
- perm*.py      per-function permutation drivers (the 0017FD50 template drove 3 matches)
