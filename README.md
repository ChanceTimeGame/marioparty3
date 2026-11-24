# Mario Party 3 (US) decompilation

A matching decompilation of Mario Party 3 (N64, US). Built with the original compiler, it produces a
ROM byte-identical to the retail game.

**Progress:** 10,906 of 11,753 functions match (92.8%), 75.2% of code bytes. Everything else is
either decompiled C that does not yet compile to identical code, or assembly that has not been
decompiled. [OPEN_FUNCTIONS.md](OPEN_FUNCTIONS.md) lists every one of them.

This repository is a fork of [mariopartyrd/marioparty3](https://github.com/mariopartyrd/marioparty3).
Thanks to everyone who worked on it.

## Why this fork exists: Chance Time

This fork is the source of truth for Mario Party 3 in **Chance Time**, a native PC port of the
N64 and GameCube Mario Party games. Chance Time ships no game data: players supply their own ROM
or disc.

How the two fit together:

- **This repository is a pure matching decompilation.** It holds decompiled game code only, with
  no PC-port code, no `#ifdef` for a PC build and no host types. Every commit builds the retail ROM
  exactly.
- **Chance Time uses it as a submodule** and keeps its own changes (64-bit fixes, rendering and
  audio adapters) as a patch series applied on top. So the port is always built from code that is
  provably the original game logic, and the decompilation never carries port changes.
- **Non-matching C must still be correct.** The PC port compiles the `NON_MATCHING` C, so before a
  function goes behind `NON_MATCHING` its remaining difference from the original is checked to be
  register allocation or instruction order only: same calls, same constants, same stores. A
  `NON_MATCHING` function here is a finished port of the logic that is not yet byte-exact.
- **The Mario Party games share an engine.** Mario Party 1 and 2 were decompiled alongside this one
  ([ChanceTimeGame/marioparty](https://github.com/ChanceTimeGame/marioparty),
  [ChanceTimeGame/marioparty2](https://github.com/ChanceTimeGame/marioparty2)), and a matched
  function in one game is often the starting point for its twin in another.

Once Mario Party 3 reaches 100% this repository is finished: it takes genuine decompilation fixes
only.

## Contributing

The last 9% is the hard part. See [CONTRIBUTING.md](CONTRIBUTING.md) for the workflow, the checks
a change must pass and the compiler details that matter, and [OPEN_FUNCTIONS.md](OPEN_FUNCTIONS.md)
for where to start. Pull requests are welcome.

## Building

Tested on Ubuntu (WSL 2). On Windows, clone into the WSL filesystem, not `/mnt/c`: builds
there are very slow.

1. `git clone https://github.com/ChanceTimeGame/marioparty3`.
2. Run `./tools/install.sh` for the system packages and a Python virtual environment, then
   `cd tools && make` for the remaining tools.
3. Put your own US Mario Party 3 ROM, big-endian (`.z64`), in the repository root as `baserom.us.z64`
   (SHA-1 `6beb80ff822b96bcf85dcdb512e8b2b7969d8259`).
4. `source venv/bin/activate`, then `make setup` (splits the ROM into assembly and assets).
5. `make -j$(nproc)`. The build ends with `OK` when the ROM is identical to the original.
