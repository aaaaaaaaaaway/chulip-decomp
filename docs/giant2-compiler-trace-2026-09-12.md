# Giant2: progress beyond the permutation plateau

This investigation starts from main `8d1a18fb4041ceed47df9d387437cb58d059efdd`.
The saved second giant, `func_00168D78`, has a 72.8607% aligned-word score,
consistent with the reported plateau. It is the provisional target; a newer
candidate and Fable's specific solver proposal have not been identified.

Three retail-backed source changes improve that draft to **75.7685%**. The
function remains unmatched. No functions or bytes are added to the verified
ledger by these experiments.

## Frozen experiment

- Source: `work/campaign/packets/func_00168D78/candidates/parallel_library_returns_context.c`.
- Source SHA-256: `31a1d2cf14778d9fe9601c847db6b1078fbc1fa7ae2a86b373256b7e471f3a76`.
- Retail range: `[0x168D78, 0x16C5E4)`, 14,444 bytes / 3,611 words.
- Profile: `ee-gcc2.95.3-136-O2-G8-ps2as`; no extra object flags.
- Baseline native sections: 14,400 bytes text, 1,136 bytes rodata, 392 bytes sdata.
- Score: exact four-byte-word SequenceMatcher alignment, candidate to retail,
  `autojunk=False`. This is similarity, not positional equality or completion.

Adding `-da` to the historical driver produces 16 compiler-pass dumps. Separate
baseline and diagnostic compilations have identical assembly for the frozen
giant, the lifetime experiment, and the nested-conditions experiment. The flag
is used for observation; it is not added to the matching profile. This was first
calibrated on already verified function 00131780.

Local reproduction scripts and command/hash manifests are under
`work/astra_solver_review/`: `capture_giant.py`, `capture_lifetime.py`,
`capture_nested_flags.py`, and the respective `dump-capability.json` files.
Native object inventories and complete-text results are in
`variants/{results,guard-results,nested-flags-results}.json`.

## 1. Correct the real loop-index lifetime

In case 0x20FD, retail initializes the signed-short loop index `si` in the delay
slot of the call to 0015EE08. The command argument `c` remains live after the
call. The draft instead initialized `si` in its later for initializer.

The compiler trace explains the consequence: c/pseudo125 and si/pseudo135 had
no interference edge and both occupied s1. Moving the existing `si = 0` before
the call, and leaving the for initializer empty, creates the missing overlap.
The new trace assigns c to s5, si to s1, and pc to s6. All six scalar entry roles
then agree with retail, and the actual call delay slot is recovered.

These pseudo identities were checked in this controlled pair; their numbers
must not be assumed stable across arbitrary source changes. This correction
adds no dummy operation, storage, register constraint, or artificial lifetime.

## 2. Retain one loop guard

The same case had `if (b != 0)` around `for (; si < b; si++)`. With the existing
initialization to zero and unsigned-short b, the loop condition already handles
zero. Retail has one guard. Removing only the outer if preserves the loop body,
counter type, calls and stores and recovers that control-flow structure.

## 3. Preserve separate flag conditions

The draft's `(flags & 1) && (flags & 0x200)` becomes a combined mask/comparison
against 0x201 in **initial RTL**. Thus this discrepancy predates register
allocation, scheduling and the RTL combine pass. Retail tests the two bits
separately. Replacing that one condition with ordinary nested if statements,
keeping its body inside both, produces separate masks 1 and 512 and zero
branches in initial RTL.

Independent inspection finds all 80 bytes at retail `[0x1691FC, 0x16924C)`
identical to the resulting draft's `[0x1691EC, 0x16923C)`. This includes both
branches to the post-body join, their delay slots, and the call with its actual
buffer-store delay slot. The extern/plain variant reproduces the same block at
`[0x1691E4, 0x169234)`. Local equality at displaced addresses is diagnostic;
it does not earn partial-function matching credit.

## Results and source holds

| Complete variant | Text bytes | Aligned words / 3611 | Similarity |
| --- | ---: | ---: | ---: |
| Frozen inherited draft | 14400 | 2631 | 72.8607% |
| Corrected index lifetime | 14392 | 2700 | 74.7715% |
| Plus single loop guard | 14384 | 2708 | 74.9931% |
| Plus nested flag conditions | 14384 | 2736 | 75.7685% |
| Extern globals, plain pending, no body changes | 14440 | 2608 | 72.2238% |
| Extern/plain with all three body changes | 14440 | 2711 | 75.0762% |
| Extern/plain, scalar actor pointer, no body changes | 14304 | 2536 | 70.2299% |
| Extern/plain, scalar actor pointer, all three changes | 14296 | 2640 | 73.1099% |

The best inherited draft has only 149 positional equal words. Every complete
variant remains a MISS. All retain their complete 1,136-byte rodata section;
neither its equality nor ownership has been established here.

The inherited source defines 98 unproved globals spanning 392 bytes and has an
unproved volatile pending field. A separate audit removes every definition and
89 unused declarations, retaining nine referenced externs with access-width
evidence. These extern variants emit no mutable data. Removing the pending
qualifier is a separately recorded alternative: its complete writer lifecycle
has not been established. Aggregate organization and cross-unit interfaces also
remain review obligations. The source audit is not semantic approval.

Best inherited source SHA-256:
`7798d0f96eb0f2092f8921b468f4bbef5978285cf13a6661bafd8bc9fa498e5a`.
Local candidate: `work/astra_solver_review/variants/lifetime_single_guard_nested_flags.c`.
The parallel extern/plain source and full hashes are in the result manifest.

An additional storage audit supports replacing the one-member ActorsRef union
with an ordinary Actor pointer. Matched 00171D10 already uses a plain pointer
under this exact profile and reproduces both GP-relative and absolute loads of
the same global. The allocator return is stored directly into that pointer at
16380C. Mixed addressing therefore does not require a union. The scalar form
lowers the score, but retains the independently supported storage interface;
do not restore the wrapper just to recover similarity. In this more conservative
extern/plain/scalar context the three body changes still improve similarity
from 70.2299% to 73.1099%. Remaining type/interface holds still apply.

Evidence is in `work/parallel_giant2_semantic_review/actor_pointer_review.md`
and `variants/{scalar-actor-results,scalar-actor-baseline-results}.json`.

## Workflow to transfer to other large functions

1. Freeze the whole source, profile, object sections, linked bytes and score.
2. Locate a meaningful block discrepancy, including branch edges and delay
   slots. A normalized alignment only helps locate it; it is not proof.
3. Trace the relevant values back to the earliest compiler stage that differs.
   Distinguish frontend folding, lifetime, allocation, scheduling and aliasing.
4. Change one ordinary-C construct supported by retail and verify the predicted
   trace effect before interpreting its whole-function score.
5. Reuse the explained pattern only where another function has the same
   evidence. Keep unsuccessful experiments and compiled hashes to avoid repeats.
6. Run the full existing promotion gates only when the complete candidate is
   eligible. No fabricated providers, forced registers, padding or byte patches.

Next unresolved regions include buf allocation (candidate s1 versus retail s7),
the pending-label block's address reuse and narrowing, and later structural
differences. A desired buf register alone is no reason to invent an overlap.
Historical narrow pending-local experiments already exist and should not be
repeated without new causal evidence.

A solver is appropriate for a bounded expression-equivalence or interference
question with a faithful width, signedness, definedness and memory model. It
does not make GCC choose an assignment merely by finding it feasible. No solver
was installed or run in this investigation; direct compiler evidence already
produced the three improvements above.

Primary references: [GCC 2.95.3 dump options](https://gcc.gnu.org/onlinedocs/gcc-2.95.3/gcc_2.html),
[decomp-permuter scope and scorer](https://github.com/simonlindholm/decomp-permuter/blob/main/README.md),
and [Z3 fixed-width bit-vector theory](https://microsoft.github.io/z3guide/docs/theories/Bitvectors/).

## Follow-up: address sharing is PRE, not field aliasing

The scalar candidate's full 16-pass trace also preserves assembly exactly.
Its pending block already contains the single narrowing mask seen in retail.
Swapping the current-label comparison into retail operand order changes just
the two register operands at 168F9C; it leaves the 73.1099% aligned-word score
unchanged because the branch displacement still differs. Keep this local
correction separately from claims of a new whole-word match.

GCSE partial redundancy elimination introduces reaching pseudo3389 for
HIGH(D_002D8880), expression45 in the dump: 16 replacements and 13 insertion
sites. CSE2 reuses the entry high address, ultimately held in s7. The buffer's
address is another PRE-created pseudo,3390. It is allocated before3389 and
shares s1 with the nonoverlapping loop index. Therefore high-address sharing
does not itself establish the cause of the buffer's register assignment.

The upstream GCC 2.95.3 implementation accepts HIGH(symbol) expressions, and
ordinary stores through VM fields cannot invalidate an immutable symbol address.
It lists pressure-aware/cheap-expression throttling as unfinished work. This
upstream source explains the algorithm; it is not asserted identical to Sony's
fork. The actual compiler dumps remain authoritative. Source URLs and hashes,
dump line references, and the distinction are preserved in
`work/parallel_giant2_semantic_review/gcse_provenance.md` and
`work/parallel_solver_register_review/scalar-address-pre-review.json`.

A single diagnostic `-fno-gcse` ablation on the scalar/operand-order source
produces 14,264 text bytes and 2,246/3,611 aligned words (62.1988%). It removes
the entry buffer-pointer copy and changes many unrelated allocations, while
still failing to reproduce the complete pending block. It is not an adopted
profile or a promotion candidate. The matching profile and ledger remain
unchanged. Full results: `work/astra_solver_review/variants/no-gcse-results.json`.

One further source probe gives the existing buffer array an explicit pointer,
assigned after the session call and before the existing clear. It preserves
all consumers and the inherited array footprint. This yields 14,240 text bytes
and 2,509/3,611 aligned words (69.4821%); the pointer still occupies s1 and the
entry instructions diverge further. It is a recorded negative, not the preferred
candidate. No earlier explicit-buffer-pointer source was found among 38 drafts
(27 unique contents). Results: `variants/explicit-buffer-results.json`.

The buffer extent still needs an independent audit: 138468's third argument is
flags, not a byte count, and that callee copies four halfwords. Its 0x10 flag
does not prove a 16-byte local array. The explicit-pointer probe preserves the
inherited extent without claiming it is established.

## Further region-family and contract corrections

The buffer extent audit reviews all six event-list consumers and every local
use. Four halfwords suffice; changing buf[8] to buf[4] preserves the complete
linked text and every allocated native PROGBITS section. Evidence and consumer
source hashes are in `work/astra_solver_review/buffer-extent-review.json`.

Cases 0x2079 and 0x20DE repeat the redundant-guard pattern. Retail has one
signed BLEZ product guard, with si=0 in its delay slot; the draft has BLEZL
followed by BLEZ. Removing each outer guard recovers the retail loop entry.
Before that change, the dimensions' product is made explicitly unsigned32,
then interpreted as signed32 for comparison, matching retail low32 MULT and
signed branch behavior. This preserves native bytes and avoids assuming that
two unrestricted unsigned-short dimensions cannot overflow signed int.
Other index/division validity assumptions are not established by this change.

The event-call audit corrects allocator 138468's int result and key/flags types,
uses the actual signed payload views for replacement/search, and supplies the
three missing declarations for 389F8,38B70,38E58. No buffer is enlarged and no
element conversion or copy is added. The source keeps the getter's unsigned
halfword view, including its separate later signed comparison.

An additional caller audit found a missing count argument in case2040:
retail16A7B4 explicitly moves b into a1 before calling12F210, and the callee
captures a1 as unsigned16 at12F22C. The source now supplies it. The related
12F390 contract is a byte-string pointer, two unsigned16 values and a32-bit
mask, consistent with its entry masking/stores. Explicit char-pointer views
preserve the actual script bytes. The packed script offset is assembled with
an unsigned32 shift/OR then converted to signed32 before division by2; retail
uses the corresponding signed rounding sequence. The arithmetic correction
does not change native text.

The script metadata is a real aggregate: allocation stores the entry pointer
at2D8840, message lookup reads the word at+4, and matched actor-list consumers
read count at+0x10. A ScriptTable view describes those fields, replacing the
inherited pointer-array and separate three-int-array declarations. A prior
scalar-only probe fails linking because it wrongly selects out-of-range GP
relocations; that failure is retained, not bypassed with assembler flags.
The aggregate view links under the unchanged native profile and claims no data
ownership. Uninterpreted bytes between known fields remain explicit.

| Successive complete cleaned draft | Text bytes | Aligned words / 3611 |
| --- | ---: | ---: |
| Eight-byte buffer, operand-order correction | 14296 | 2640 |
| Explicit region-product width | 14296 | 2640 |
| Single guards in both region loops | 14280 | 2652 |
| Event-list call contracts | 14280 | 2657 |
| Choice call contracts, including missing count | 14288 | 2651 |
| Defined packed word and script-header view | 14288 | 2651 |

The current source-provenance frontier is
`work/astra_solver_review/variants/scalar_script_header.c`, **73.4146%** aligned
words. Correcting real calls can lower similarity; retain their actual contracts.
Neither this draft nor the higher-scoring inherited draft is a full match.
Results and section inventories are in `variants/region-guards-results.json`,
`event-contract-results.json`, `choice-script-results.json` and
`script-header-results.json`. Disassembly is in `region-loop-disassembly.json`.

## Two existing event-function repairs verified

Getter00138DF0 now returns the actual four-halfword payload from the established
36-byte event record, using its real base D203C20 and values field at+0x14.
It removes the unsupported opaque36-byte wrapper starting at the payload.
Caller0012D4C0 uses the actual int search result and short-pointer parameter
contract and agrees with the getter's int index parameter. Its unsigned handle
and FFFFFFFF sentinel remain: their conversion is defined and their retail
construction is preserved.

The full transactional importer independently replays all four prior getter
profiles and the caller's prior profile. All108 existing function bytes, the
970772-byte rebuilt image, baseline and public gates pass;204 tests pass.
The image SHA-256 remains
`77768f0c5d84a92a6d185499b8bb4bb2205779a81fbdb859b15cc1d9ce28f876`.
The ledger remains1491/2189 functions and272484/663704 function bytes. The
generated treemap changes only its ledger checksum; totals and layout agree.
Transaction evidence: `work/astra_solver_review/event_repairs/promotion.log`.

## Explicit message forwarding and remaining narrow contracts

Case2070 omitted the argument to15ED80. Retail first loads D1ED750 into a0,
checks its first byte, and then calls15ED80 with that pointer still in a0.
The callee copies a0 to a1 and forwards it to15DED8; that routine reads and
advances the source byte pointer until a double-NUL terminator. Both giant
calls now explicitly pass D1ED750, and the wrapper describes a read-only byte
source instead of an integer. This is real argument forwarding, not reliance
on incidental register retention.

The zero-return stub12E5E0 now accepts the unused int argument explicitly
supplied by retail168F68. Its neighbor12E5D8 remains unchanged in their complete
16-byte unit. The wrapper's36 bytes and that full16-byte unit pass all prior
proofs, complete image, baseline and public gates (204 tests). Evidence:
`work/astra_solver_review/forward_repairs/promotion.log`.

The actor lookup73148 declaration now agrees with its unsigned16 input/result
and FFFF sentinel. This retains the complete giant text byte-for-byte, so no
additional caller mask is needed. The missing message argument improves the
cleaned draft to2655/3611 aligned words (73.5253%), still14288/14444 text bytes.
Current candidate: `work/astra_solver_review/variants/scalar_actor_lookup_u16.c`,
SHA-256 `602f2b680f4fb52f1bfecf28298b72278b6515c2155ced1a3bc3b491c8597d48`.

Fresh16-pass dumps under `work/astra_solver_review/contracts-trace/` again
preserve assembly exactly. Use this trace for subsequent allocation analysis:
earlier pseudo IDs must not be assumed valid after the contract/control edits.
The pending and other source holds remain, and no giant has been promoted.
