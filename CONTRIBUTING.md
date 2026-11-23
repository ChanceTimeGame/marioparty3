# Contributing

Thanks for helping finish Mario Party 3. This page covers how a function goes from assembly to
matching C, what a pull request has to pass, and the compiler behaviour that decides most of the
hard cases. [OPEN_FUNCTIONS.md](OPEN_FUNCTIONS.md) lists what is left.

## Ground rules

- **The ROM must match.** Every commit builds `build/marioparty3.z64` identical to the retail ROM:
  `make` ends with `OK`.
- **Decompiled code only.** No PC-port code, no `#ifdef` for other platforms. (Chance Time keeps its
  port changes in its own repository; see the README.)
- **Non-matching C must be correct C.** A function may stay behind `NON_MATCHING` (below), but only
  once its remaining difference from the original is register allocation or instruction order.
  Ports compile that C, so a wrong constant, stride, comparison or call is a bug, not residue.
- **Real names over guessed ones.** Rename a function, struct or field when you know what it does;
  leave `func_XXXXXXXX` / `D_XXXXXXXX` otherwise.

## Setup

After the build in the README matches, keep a copy of the matching objects to compare against:

```sh
python3 tools/make_expected.py     # copies build/ to expected/build/
```

Redo it after pulling, so the comparison is against the current tree.

## Decompiling a function

1. Find the function's assembly in `asm/nonmatchings/<unit>/<func>.s` and its
   `INCLUDE_ASM(...)` line in `src/<unit>.c`.
2. **Look for a twin first.** Mario Party 1 and 2 share the engine and the compiler, and many
   board, menu and minigame functions exist in two or three games. Grep
   [marioparty](https://github.com/ChanceTimeGame/marioparty) and
   [marioparty2](https://github.com/ChanceTimeGame/marioparty2) for the function's callees or
   constants: a matched twin is usually the best start.
3. Otherwise start from [m2c](https://github.com/matt-kempster/m2c):
   ```sh
   python3 tools/m2ctx.py src/<unit>.c                       # writes ctx.c
   m2c -t mips-gcc-c --context ctx.c asm/nonmatchings/<unit>/<func>.s
   ```
   [decomp.me](https://decomp.me) (compiler: KMC GCC 2.7.2, flags `-O1 -mips3`) is a good place to iterate.
4. Replace the `INCLUDE_ASM` line with your C, `make`, and compare:
   ```sh
   python3 tools/diff.py -mwo <func>                   # asm-differ, live
   ```
5. When `make` prints `OK`, it matches.

## When it will not match

Work the differences in this order; a later kind is usually caused by an earlier one:

1. **A wrong symbol, field or callee** (masked code equal, a relocation differs). Fix the
   identity; this is not a code-generation problem.
2. **A different set of calls or memory accesses.** Finish the body, or look for an inline helper or
   a macro.
3. **Different control flow** (branch, block or return counts). Change the source structure: loop
   form, early return, condition order.
4. **Registers and scheduling only.** Check variable widths and lifetimes, then hand it to the
   permuter.

If you stop at step 4, keep the C behind the repository's convention, with one line saying what
differs:

```c
// register allocation: v0/v1 swapped in the final test (masked 0)
#ifdef NON_MATCHING
void func_8010674C_staff(void) {
    ...
}
#else
INCLUDE_ASM("asm/nonmatchings/overlays/staff/542220", func_8010674C_staff);
#endif
```

and make sure that C compiles: `touch` the file, take the `-fsyntax-only` command `make -n` prints
for it, add `-DNON_MATCHING` and run it.

### decomp-permuter

[decomp-permuter](https://github.com/simonlindholm/decomp-permuter) finishes most
register-allocation residue. `permuter_settings.toml` is set up for this repository:

```sh
python3 path/to/decomp-permuter/import.py src/<unit>.c asm/nonmatchings/<unit>/<func>.s
python3 path/to/decomp-permuter/permuter.py nonmatchings/<func> -j8 --stop-on-zero
```

Small functions often finish in minutes; large ones can take hours. A score of 0 is a candidate,
not a match: paste the result **verbatim** (tidying it has broken matches before), rebuild, and only
`make` `OK` counts. The settings compile with the default flags; a unit with its own flags or
build steps in the `Makefile` (below) needs them in `compiler_command` too.

### Fakematches

A form that matches only because of what it does to the compiler (a stray `volatile`, a dummy
local, a self-assignment, an empty `do {} while (0)`) is a fakematch. It is better than assembly,
so keep it, but say so in a comment: it usually points at a wrong type, a missing helper or a
macro, and someone may find the real source later.

## Compiler notes (KMC GCC 2.7.2)

Most units build with `-O1 -G0 -mips3`. Some are different, and the difference shows up as
near-misses no source change can fix:

- **Per-unit flags.** Several SDK units build with `-O3 -funsigned-char`, `libhmath` with
  `-O2 -ffast-math`, and `libm` with IDO 5.3, not GCC. The assembler's multiply fix (a `nop` near some `mult`s) is on everywhere. Some units
  are compiled to assembly, stripped of blank lines and then assembled (the `W2DC_BLANKSTRIP` list):
  the original build evidently did this, and it changes where the assembler puts `nop`s after calls.
  If a function is "one `nop` short", try its unit in that list. After changing a unit's flags,
  `touch` its source: `make` does not notice.
- **Parameter types show at entry:** `andi aN,aN,0xffff` means a `u16` parameter, `sll 16; sra 16` an
  `s16`, `andi 0xff` a `u8`. A float after an integer argument arrives in `a1`-`a3` and is moved
  with `mtc1`.
- **Load order follows source order.** An index computed before the array base means a local
  pointer was taken first (`T *p = &arr[i]; f(p->x);`). Comparisons load their left operand first.
- **Chained stores** (`a = b = c = 0`) store in reverse order from one base; separate statements
  through a global reload the base each time.
- **Shift signedness:** a `u16` field read into an `s32` local shifts with `sra`; reading through
  the pointer each time keeps `srl`.
- **Check every pointer stride** in m2c's output against the `addiu` step; m2c sometimes counts
  bytes.
- **Identical string literals** in one unit share one `.rodata` label.
- **Branch senses from m2c's gotos are easy to invert**; reread them before trusting a near-match.

## Pull requests

Before opening one:

- `make` prints `OK` from a clean build (`make clean && make -j$(nproc)`).
- Every `NON_MATCHING` function you added or changed compiles with `-DNON_MATCHING` and has its
  one-line note.
- No unrelated reformatting.

Small pull requests (one unit or a handful of functions) are easiest to review.
