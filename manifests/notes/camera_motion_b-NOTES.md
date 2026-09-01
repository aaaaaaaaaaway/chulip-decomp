# Camera motion lane B

Compiler profile: `ee-gcc2.95.3-136-O2-G8` (SN Systems GNU C
2.95.3-EE build 1.36, `-O2 -G8`).

## Exact candidates

| Function | Address | Size | Result |
| --- | ---: | ---: | --- |
| `func_00101A00` | `0x00101A00` | 104 | exact |
| `func_00101A68` | `0x00101A68` | 104 | exact |
| `func_00101AD0` | `0x00101AD0` | 36 | exact |

Each result was obtained independently with `tools/match.py --source` against
the complete retail function byte range.

## Layout evidence

- `D_001EDDE0` is at least a three-float vector. `func_00101A00` adds the
  caller's first three floats to it component by component.
- `D_001EDE00` begins with the same three-float layout. Existing camera-state
  evidence makes this the position member of the larger aggregate beginning at
  `D_001EDE00`; `func_00101A68` adds the input vector to that member.
- Both functions then call `func_00136AF8(0, 1)` and
  `func_00136AF8(17, 0)`. The callee edits bits 0 and 17 of the 64-bit state at
  `D_001FFB40`, so these calls mark one state bit and clear another after the
  vector mutation.
- Callers construct inputs in 16-byte slots (`D_00205060`, `D_00205070`, or an
  indexed 16-byte table), while these functions consume only offsets 0, 4, and
  8. The safest current parameter model is therefore a pointer to a three-float
  prefix, without claiming that the caller's full object is only 12 bytes.
- `func_00101AD0` updates `D_001EC884` from input offset 0 and `D_001EC888`
  from input offset 8. A `const float *` parameter is compiler-significant:
  possible float aliasing prevents the second input load from moving above the
  first global store and reproduces the retail schedule exactly. A `Vec3f *`
  parameter does not.

## Discriminating failures

- The first `func_00101AD0` attempt used a `Vec3f *`. It produced 9 words but
  scheduled the offset-8 load first, so it mismatched at byte 0.
- The final `func_00101AD0` source under the otherwise identical `-G0` profile
  emitted 11 words with absolute `lui`-based accesses and mismatched at byte 0.
  Its exact `-G8` result is therefore additional small-data-mode evidence.
