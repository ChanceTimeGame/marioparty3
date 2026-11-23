# Open functions: Mario Party 3 (US)

Generated from a build of this repository. Every function here is either decompiled C that does
not yet produce identical code (kept behind `#ifdef NON_MATCHING`, the original assembly is what
builds) or still assembly only. Regenerate rather than edit by hand.

**Columns.** *instr*: instructions in the original. *masked*: differing lines with register names
masked out; 0 means only register allocation or instruction order differs, which is where
[decomp-permuter](https://github.com/simonlindholm/decomp-permuter) most often finishes the job.
*raw*: differing lines including registers. *note*: the comment in the source, when there is one.

**Summary:** 921 functions with C behind `NON_MATCHING` (masked 0: 161, masked 1-10: 281, masked over 10: 479); 63 functions still assembly only.

## C behind NON_MATCHING

| function | file | instr | masked | raw | note |
|---|---|--:|--:|--:|---|
| `func_801125E8_filesel` | `src/overlays/filesel/516AE0.c` | 18 | 0 | 3 | Terminates a two-byte-character string after at most 5 characters; returns its length. register allocation of i/len (raw only) |
| `func_80114034_duel06` | `src/overlays/duel06/436E50.c` | 31 | 0 | 4 | register allocation only (masked 0, the second player struct in a0, retail a1; twin of func_80114940_duel10) |
| `func_80114940_duel10` | `src/overlays/duel10/4461E0.c` | 31 | 0 | 4 | board ec3: register allocation only (the second player struct in a0, retail a1; masked 0) |
| `func_80112508_filesel` | `src/overlays/filesel/516AE0.c` | 35 | 0 | 5 | register allocation of the name-pair test (raw only) |
| `func_8010F43C_msetup` | `src/overlays/msetup/506F20.c` | 45 | 0 | 0 | identical code, but retail pads it with a nop to 0x8010F4E0: a TU boundary (506F20.c needs a split there); asm keeps the pad |
| `func_801126C0_filesel` | `src/overlays/filesel/516AE0.c` | 46 | 0 | 23 | callee-saved register choice for the three arguments (raw only) |
| `func_800D90D0_name_81` | `src/overlays/ovl_81_name/BFB40.c` | 50 | 0 | 2 | masked 0; raw: retail copies arg1 to a3 after saving arg0 in s0 |
| `func_8010BFD0_spotlight_swim` | `src/overlays/ovl_03_spotlight_swim/1263E0.c` | 54 | 0 | 16 | regalloc only (masked 0): retail x0/y0/i in t3/t6/t5, mine t6/t7/t4. Stamps the 32 x 32 spotlight mask (alpha = mask * 16, capped at D_8010D47C_spotlight_swim) ... |
| `func_8010AAEC_hand_line_sinker` | `src/overlays/ovl_01_hand_line_sinker/11A480.c` | 56 | 0 | 6 | Newton's method: the catenary parameter whose arc length matches the line (func_8010ABD4 = 0). |
| `func_8010A4B4_marios_puzzle_party` | `src/overlays/ovl_1F_marios_puzzle_party/1F3B90.c` | 59 | 0 | 16 | register allocation (masked 0, raw 16: the /14 and /7 magic shares a1 in retail) |
| `func_80108A18_inst` | `src/overlays/inst/4E1510.c` | 62 | 0 | 0 | Starts texture animation anim of model at frame (frame -1: plays it as it is). |
| `func_8010EDF8_duel10` | `src/overlays/duel10/4461E0.c` | 63 | 0 | 20 | board ec2: slide the guide from its x position to x over 14 frames, then idle. board ec2: masked 0; raw residue is the register allocation (guide s1, x - start ... |
| `func_80106850_mgresultduel` | `src/overlays/mgresultduel/4F01F0.c` | 67 | 0 | 0 | duelres A: Instruction-identical, but retail pads it with two nops to 0x80106930: a TU boundary (the unit's .data also pads to 0x80108E80 there); asm keeps the ... |
| `func_80106918_mgresultbattle` | `src/overlays/mgresultbattle/4F3780.c` | 72 | 0 | 9 | battleres A: masked 0, raw 12 (s0/s1 swapped between i and motion). Plays each figure's win (coins earned) or lose motion, then hands figure 0's hook to the wai... |
| `func_801063F4_stacked_deck` | `src/overlays/ovl_2A_stacked_deck/240A10.c` | 76 | 0 | 10 |  |
| `func_8010642C_three_door_monty` | `src/overlays/ovl_2B_three_door_monty/24A760.c` | 76 | 0 | 10 |  |
| `func_80109A58_modesel` | `src/overlays/modesel/4F7E90.c` | 88 | 0 | 12 | Stick direction of controller `pad` as a button mask (0x100 right, 0x200 left, 0x800 up, 0x400 down and their diagonals), reported once each time the stick leav... |
| `func_801130E8_option` | `src/overlays/option/5334D0.c` | 88 | 0 | 12 |  |
| `func_8010B0E8_aces_high` | `src/overlays/ovl_17_aces_high/1C4280.c` | 93 | 0 | 4 | register allocation only (masked 0): retail multiplies sindf(rot.y) * 30 into f0, here into f20 |
| `func_80107734_awful_tower` | `src/overlays/ovl_25_awful_tower/21E010.c` | 94 | 0 | 3 | Stage object update: runs the players' logic and lowers the tower top in the winner scene. |
| `func_80105CB4_staff` | `src/overlays/staff/542220.c` | 100 | 0 | 0 | Instruction-identical to retail; only .rodata differs: retail pads this jump table with a zero word because the next file (text 0x80106E20, rodata 0x80111208) s... |
| `func_8010A5C4_storyresult` | `src/overlays/storyresult/54F360.c` | 105 | 0 | 11 | Register allocation only (masked 0): retail computes the star difference in a0 and the result in v1. Party rank of player: 4 two or more stars ahead, 3 one ahea... |
| `func_80108480_game_guys_roulette` | `src/overlays/ovl_42_game_guys_roulette/2FC270.c` | 112 | 0 | 2 | The result: the win jingle and message, or "<name> LOST!" raw 2: retail sign-extends the message id through v0 (sll v0 / sra a0), register choice only |
| `func_8010876C_mstory2` | `src/overlays/mstory2/49DF30.c` | 114 | 0 | 3 | register residue only: retail keeps the partner in v0, KMC picks a0 (masked 0) |
| `func_80109BF4_hide_and_sneak` | `src/overlays/ovl_06_hide_and_sneak/137C00.c` | 114 | 0 | 3 |  |
| `func_8010CE8C_msetup` | `src/overlays/msetup/506F20.c` | 114 | 0 | 0 | Instruction-identical, but retail pads 12 bytes (nops) after it so func_8010D060_msetup starts 16-aligned: func_8010D060_msetup probably begins another retail o... |
| `func_80108130_mgresultbattle` | `src/overlays/mgresultbattle/4F5AF0.c` | 115 | 0 | 7 | battleres A: masked 0, raw 13 (s0/s1 swapped between i and the icon sprite file). Creates the coin icon and three digit sprites per figure and runs the sprite h... |
| `func_8010B528_game_guys_lucky_7` | `src/overlays/ovl_43_game_guys_lucky_7/3010E0.c` | 115 | 0 | 4 | masked 0: retail swaps $f0/$f2 around the pos.x add |
| `func_80110C04_opening` | `src/overlays/opening/523FD0.c` | 119 | 0 | 10 |  |
| `func_801084A0_curtain_call` | `src/overlays/ovl_22_curtain_call/20BFA0.c` | 125 | 0 | 1 | The four players, each on a random seat. |
| `func_8010BA6C_msetup` | `src/overlays/msetup/506F20.c` | 125 | 0 | 1 | one operand order: retail `addu v0,v0,s5` (index + table) for &pos[i], GCC here `addu v0,s5,v0` (tried pos + i, i + pos, a direct struct copy, per-field copy). |
| `func_80000650_main` | `src/1140.c` | 130 | 0 | 39 | MP3 adds the func_80001134_main(0, 0x20) call. Register allocation (MP2 too): st/buf/rom take s2/s0/s1 instead of retail's s0/s1/s2. MP2 tried st-> for the fxd ... |
| `func_80109D6C_fridged_bridges` | `src/overlays/ovl_24_fridged_bridges/216670.c` | 133 | 0 | 2 | Is (x, z) inside the face? (minigame func_800DA540 without its surface filter) |
| `func_80106C50_staff` | `src/overlays/staff/542220.c` | 134 | 0 | 0 | Instruction-identical to retail; only the file-end padding differs: retail has a file boundary at 0x80106E20 (three nops after this function), which the unit ca... |
| `func_801081E4_picture_imperfect` | `src/overlays/ovl_1E_picture_imperfect/1EF420.c` | 134 | 0 | 12 | masked 0: pw and ex swap $s3/$s4 (registers only); logic checked |
| `func_801096BC_water_whirled` | `src/overlays/ovl_23_water_whirled/211AB0.c` | 134 | 0 | 44 | Masked 0, raw 44: $f22/$f24 swapped between a and b. Steering offset: the angle between the course direction at the rider (along the straights, round the half c... |
| `func_801091F8_fridged_bridges` | `src/overlays/ovl_24_fridged_bridges/216670.c` | 135 | 0 | 5 | Game end: every player lets go, wipe, then wait for the finish |
| `func_8003A81C_main` | `src/gamemes.c` | 141 | 0 | 7 | The font sprite (high half, loaded on first use) and frame (low half) for the character at str; flag bit 0 is the large font. register allocation (masked 0): fl... |
| `func_800571C8_main` | `src/sprman.c` | 141 | 0 | 6 | Steps a sprite's palette animation; when a frame changes, rebuilds the palette in the next of three buffers (MP2 func_800841B8_84DB8). register allocation, as i... |
| `func_8010CFF8_aces_high` | `src/overlays/ovl_17_aces_high/1C4280.c` | 145 | 0 | 27 | masked 12: retail keeps the counter in a1 and the index in a0 (here the reverse) and copies the lives value through a temporary before best; same operations oth... |
| `func_80108C04_game_guys_magic_boxes` | `src/overlays/ovl_44_game_guys_magic_boxes/308D10.c` | 152 | 0 | 2 | register allocation only: the message id is sign-extended in v0 before the GMesMaxTimeGet call, here in a0 The result: "You won N coins!" or the loss message, w... |
| `func_8010E868_marios_puzzle_party` | `src/overlays/ovl_1F_marios_puzzle_party/1F3B90.c` | 156 | 0 | 36 | Show a time in frames as m'ss"cc on the clock group (members 1-7; 2 and 5 are the separators). |
| `func_80107508_staff` | `src/overlays/staff/542220.c` | 158 | 0 | 6 | masked 0; raw: v0/v1 swap in the table index. Retail also has a file boundary at 0x80107740 (three nops after this function), which the unit cannot express with... |
| `func_8010E494_mgmode` | `src/overlays/mgmode/473130.c` | 161 | 0 | 9 | masked 0; register allocation only (n in t1 for t0, g's zero not copied from k's). |
| `func_80106B40_filesel` | `src/overlays/filesel/516AE0.c` | 170 | 0 | 48 |  |
| `func_80106BA0_modesel` | `src/overlays/modesel/4F7E90.c` | 170 | 0 | 48 |  |
| `func_80107140_opening` | `src/overlays/opening/523FD0.c` | 170 | 0 | 48 |  |
| `func_80107238_treadmill_grill` | `src/overlays/ovl_15_treadmill_grill/1B4F10.c` | 170 | 0 | 1 | masked 0: retail ORs the two flags into a temporary, this C into hit (raw 1) |
| `func_801110C0_option` | `src/overlays/option/5334D0.c` | 170 | 0 | 48 |  |
| `func_80006A8C_main` | `src/1140.c` | 183 | 0 | 2 | scheduling (masked 0, raw 2): the parameter copies come out in another order (retail copies st after heap and numDefs). Tried: info assigned as a statement, dec... |
| `func_8010749C_pump_pump_away` | `src/overlays/ovl_0D_pump_pump_away/16F670.c` | 186 | 0 | 17 |  |
| `func_8010858C_bowser_toss` | `src/overlays/ovl_34_bowser_toss/291020.c` | 194 | 0 | 2 | register allocation of the model id sign extension before Hu3DModelScaleSet. |
| `func_8010E9FC_baby_bowser_broadside` | `src/overlays/ovl_0C_baby_bowser_broadside/169540.c` | 198 | 0 | 60 |  |
| `func_8010FEC0_puddle_paddle` | `src/overlays/ovl_11_puddle_paddle/191240.c` | 198 | 0 | 60 |  |
| `func_8010A174_motor_rooter` | `src/overlays/ovl_36_motor_rooter/main.c` | 202 | 0 | 6 | <func_8010A174_motor_rooter> |
| `func_8010E03C_stardust_battle` | `src/overlays/ovl_41_stardust_battle/2ED2D0.c` | 203 | 0 | 18 | register allocation only: retail keeps the item pool in s4 and the work in s5, mine the reverse |
| `func_801076D4_parasol_plummet` | `src/overlays/ovl_1C_parasol_plummet/1DE610.c` | 204 | 0 | 5 | register allocation in the sort (f0/f2 swapped; masked 0). CPU parasol button: open or close to meet the nearest item's height, then wait a difficulty-dependent... |
| `func_801065C8_bobbing_bow_loons` | `src/overlays/ovl_3D_bobbing_bow_loons/2D8370.c` | 206 | 0 | 8 | masked 0; i and j swap saved registers (s5/s2) |
| `func_80109108_treadmill_grill` | `src/overlays/ovl_15_treadmill_grill/1B4F10.c` | 215 | 0 | 6 | Grill path: corners round the treadmill, then grill positions spaced along it. Masked 0 (raw 6): retail divides into the spacing register from a temporary, this... |
| `func_8011A5DC_w04` | `src/overlays/w04/367960.c` | 215 | 0 | 0 | board q4: masked 1; retail reuses the a0 = 0x3D set in the case-1 branch delay slot before calling func_80106AB0_w04 (void) |
| `func_8010A7AC_spotlight_swim` | `src/overlays/ovl_03_spotlight_swim/1263E0.c` | 225 | 0 | 16 | regalloc only: body and mot swap s1/s2 A chaser's lamp tracks its chaser; the chaser's end model turns to face it. |
| `func_8010D288_rockin_raceway` | `src/overlays/ovl_2C_rockin_raceway/251FF0.c` | 226 | 0 | 8 | Projects pos through camera cam: screen position and depth into screen, viewport-relative into rel. |
| `func_801095E4_staff` | `src/overlays/staff/542220.c` | 227 | 0 | 16 | masked 0; raw: s1/s2 swap (prev and path) and f0/f2 in the cos term. |
| `func_8010F348_mgmode` | `src/overlays/mgmode/473130.c` | 233 | 0 | 1 | one register (list[] indexed through prev's copy of sel). |
| `func_8010BE78_inst` | `src/overlays/inst/4E4B50.c` | 237 | 0 | 2 | retail loads the 1 stored to D_8010D440_inst into v1, this into v0; logic matches. * Retail reads the low half of D_8010D5B8_inst through its own label (D_8010D... |
| `func_80108178_mpiq` | `src/overlays/ovl_21_mpiq/204F90.c` | 238 | 0 | 1 | The four score columns (three blocks each). |
| `func_8010724C_fowl_play` | `src/overlays/ovl_3A_fowl_play/2C5B50.c` | 239 | 0 | 0 | masked 0; n and &seg swap saved registers (s5/s6) Stops a move from prev to pos at the first pen wall it crosses, r + 20 short of it. |
| `func_8010A51C_aces_high` | `src/overlays/ovl_17_aces_high/1C4280.c` | 246 | 0 | 12 | register allocation only (masked 0): retail multiplies sindf(rot.y) * 300 into f0, here straight into f22 |
| `func_80108738_chancetime` | `src/overlays/chancetime/4832D0.c` | 250 | 0 | 6 | the f32->s16 frame argument of func_80016B00_main truncates through $f0/$f2 * swapped (register allocation only); logic matches. |
| `func_8010951C_aces_high` | `src/overlays/ovl_17_aces_high/1C4280.c` | 253 | 0 | 26 | register allocation only (masked 0): retail keeps the angle difference in f4 and the stick value in f6, here the reverse |
| `func_8010A938_cheep_cheep_chase` | `src/overlays/ovl_26_cheep_cheep_chase/225740.c` | 261 | 0 | 16 | Register allocation as func_8010A57C (object/player swapped between s2 and s3, f0/f2 swapped in the threshold). |
| `func_800FCF50_name_81` | `src/overlays/ovl_81_name/E3CD0.c` | 264 | 0 | 15 | masked 0: player and shareSpace swap s2/s3 |
| `func_800072A4_main` | `src/1140.c` | 268 | 0 | 69 | register allocation (masked 0, raw 69): m, def and mask get t4/t5/a1 where retail has t5/t6/t2 (retail allocates the scan loop's locals first). The shift amount... |
| `func_80106664_mpiq` | `src/overlays/ovl_21_mpiq/204F90.c` | 271 | 0 | 22 | CPU plan for a question: buzz delay, answer time, and a right or wrong answer by difficulty. |
| `func_8003C644_main` | `src/gamemes.c` | 274 | 0 | 35 | "FINISH" letters gathering in: register allocation (masked 0: chr and i + 1 swap s1/s2 in case 0) |
| `func_8010A384_snowball_summit` | `src/overlays/ovl_28_snowball_summit/232A10.c` | 275 | 0 | 33 | Standing: settle the motion, stop, and turn toward the stick when it is pushed. register allocation only (masked 0: obj/pl swap s0/s1) |
| `func_8010D6D0_msetup` | `src/overlays/msetup/506F20.c` | 277 | 0 | 0 | retail passes work->prio with lh (called unprototyped?), lhu here (masked 1); s7/s8 swapped |
| `func_8010F910_mstory4` | `src/overlays/mstory4/4C8050.c` | 283 | 0 | 5 | register allocation: retail builds the sprite slot address in s0, KMC in a temp (raw 10) |
| `func_8006E910_main` | `src/6F470.c` | 285 | 0 | 0 | Matches, but this unit is two source files (drvrnew-like, then reverb-like from func_8006F140_main): the first one's .rodata is padded to 0x10, so func_8006E910... |
| `func_80108000_boulder_ball` | `src/overlays/ovl_04_boulder_ball/12DD30.c` | 302 | 0 | 6 | masked 0; raw: the target index and the hoisted runner count swap a1/a2 (register allocation only) |
| `func_8010677C_mgenter` | `src/overlays/mgenter/468AC0.c` | 305 | 0 | 9 | FPU register allocation (masked 0): the float-to-s16 slide positions land in other $f registers the three option names (0x4608..), slid sideways when D_80109B30... |
| `func_8010614C_slot_synch` | `src/overlays/ovl_14_slot_synch/1AC970.c` | 313 | 0 | 46 |  |
| `func_80109180_tidal_toss` | `src/overlays/ovl_0A_tidal_toss/15C310.c` | 326 | 0 | 1 | masked 0, raw 1: retail tests flags & 0x20 on $v0 (the call result) instead of its copy in $s3. unk36 is u16 but retail converts with a signed trunc.w.d: the (s... |
| `func_801090C4_coconut_conk` | `src/overlays/ovl_02_coconut_conk/120BC0.c` | 335 | 0 | 5 | A team player's CPU: chases the solo player near the end and presses A/B; steers the stick through unk08. |
| `func_80119610_w05` | `src/overlays/w05/37FFB0.c` | 336 | 0 | 19 |  |
| `func_80111220_mstory1` | `src/overlays/mstory1/496990.c` | 339 | 0 | 0 | masked 0 at the right count once functions.us.h declares func_80017AD8_main as returning s16, as 14EA0.c defines it (the header's u8 adds an andi before each st... |
| `func_801081E0_mstory1` | `src/overlays/mstory1/48D950.c` | 340 | 0 | 0 | masked 0 when func_80017AD8_main returns s16 (functions.us.h says u8: an andi 0xFF per call; s1A.header.patch) |
| `func_80105FF8_option` | `src/overlays/option/5334D0.c` | 352 | 0 | 2 | The followed model camera's eye and target, and an up vector square to the view direction (modesel func_80108AE0_modesel); the stored camera when none is follow... |
| `func_8010674C_staff` | `src/overlays/staff/542220.c` | 358 | 0 | 6 | Residue: two hazard nops after cosdf() (W2DC_BLANKSTRIP) and f2/f12 swapped in the distance sum. |
| `func_80106780_storyresult` | `src/overlays/storyresult/54DD10.c` | 358 | 0 | 6 | Residue: two hazard nops after cosdf() (W2DC_BLANKSTRIP) and f2/f12 swapped in the distance sum. |
| `func_801068F4_msetup` | `src/overlays/msetup/501C00.c` | 358 | 0 | 6 | Flies the camera along a path of keys (ended by zoom 0) at speed units per frame (MP2 name_4E's func_8010BCB8): each key's arrival time goes in unk20 (speed 0: ... |
| `func_801065D0_mgresultdealer` | `src/overlays/mgresultdealer/4ECDE0.c` | 361 | 0 | 0 | masked 0 at the right count when func_80017AD8_main returns s16 (include/functions.us.h says u8; see src/14EA0.c and ~/repos/mp3-wt/k2A.header.patch): with u8 t... |
| `func_80105ED4_etch_n_catch` | `src/overlays/ovl_12_etch_n_catch/19CEF0.c` | 379 | 0 | 9 |  |
| `func_80106CFC_opboard` | `src/overlays/opboard/3CA800.c` | 382 | 0 | 5 | register allocation and store order in the roll sort (masked 0) |
| `func_801080C8_all_fired_up` | `src/overlays/ovl_29_all_fired_up/23C8F0.c` | 390 | 0 | 8 | masked 0: the burnt-player counters get $a1 where retail has $v1 (registers only); logic checked |
| `func_80106668_dorrie_dip` | `src/overlays/ovl_3E_dorrie_dip/2DC4D0.c` | 401 | 0 | 5 | masked 0; retail keeps `found` in v1 and the D_8010A220 load in a0 (raw 5) |
| `func_80105D04_bobbing_bow_loons` | `src/overlays/ovl_3D_bobbing_bow_loons/2D8370.c` | 403 | 0 | 0 | masked 0 with func_80017AD8_main returning s16 (header says u8: an extra andi 0xFF) |
| `func_8010D13C_filesel` | `src/overlays/filesel/516AE0.c` | 414 | 0 | 23 | register allocation in the digit splits (masked 0) |
| `func_8010AD40_messy_memory` | `src/overlays/ovl_1D_messy_memory/1E37C0.c` | 417 | 0 | 6 | A player's hand object: grows in, a CPU decides how many items it remembers, then runs the brain or the pad. |
| `func_80023AF8_main` | `src/22EB0.c` | 420 | 0 | 6 | Register allocation only: list and the matrix index swap s3/s4 |
| `func_8010D424_duel01` | `src/overlays/duel01/3D8AC0.c` | 423 | 0 | 25 | duel b2: masked 0, raw 28: partner and obj swap s3/s4. |
| `func_8010D428_duel02` | `src/overlays/duel02/3EC590.c` | 423 | 0 | 25 | duel b2: masked 0, raw 28: partner and obj swap s3/s4. |
| `func_8010D428_duel03` | `src/overlays/duel03/3FE1F0.c` | 423 | 0 | 25 | board db2: func_8010D424_duel01's twin (same instructions), same residue. |
| `func_8010D428_duel04` | `src/overlays/duel04/410910.c` | 423 | 0 | 25 | board ea1: duel05 twin, duel04 constants checked against retail (immediates); masked 0, raw 28 here; logic as duel05 duel b2: masked 0, raw 28: partner and obj ... |
| `func_8010D42C_duel06` | `src/overlays/duel06/436E50.c` | 423 | 0 | 25 | duel b2: masked 0, raw 28: partner and obj swap s3/s4. |
| `func_8010D434_duel05` | `src/overlays/duel05/426450.c` | 423 | 0 | 25 | duel b2: masked 0, raw 28: partner and obj swap s3/s4. |
| `func_8010D490_duel10` | `src/overlays/duel10/4461E0.c` | 423 | 0 | 25 | duel b2: masked 0, raw 28: partner and obj swap s3/s4. |
| `func_800EE74C_name_81` | `src/overlays/ovl_81_name/D5B20.c` | 446 | 0 | 0 | Matches (masked and raw 0); kept NON_MATCHING only for .rodata: retail pads this switch's jump table to 0x20 bytes because a retail source file ends here (the n... |
| `func_80107DDC_koopa` | `src/overlays/koopa/3C27C0.c` | 449 | 0 | 3 |  |
| `func_801060A4_mgresultbattle` | `src/overlays/mgresultbattle/4F3780.c` | 450 | 0 | 20 | battleres A: masked 0, raw 20 (register allocation of the counters). Splits the battle pot (D_800CC698_main) by placing; GwPlayer[].bonusCoin holds the placing ... |
| `func_8010F810_marios_puzzle_party` | `src/overlays/ovl_1F_marios_puzzle_party/1FD760.c` | 460 | 0 | 5 | Draw object: one display list per frame with every used entry of every batch as a textured rectangle (batches 0-27 belong to the boards, seven per player, and f... |
| `func_80106990_opboardtutorial` | `src/overlays/opboardtutorial/3CDEC0.c` | 464 | 0 | 11 | board t1: register allocation in the roll sort (masked 0; opboard's twin has the same residue) H0: masked 0; the CALLS line is func_800E210C's label (_minigame ... |
| `func_80105CBC_slapdown` | `src/overlays/ovl_2E_slapdown/264B80.c` | 465 | 0 | 2 |  |
| `func_80105CBC_stacked_deck` | `src/overlays/ovl_2A_stacked_deck/240A10.c` | 465 | 0 | 2 |  |
| `func_80105D14_curtain_call` | `src/overlays/ovl_22_curtain_call/20BFA0.c` | 468 | 0 | 2 |  |
| `func_80109BFC_cosmic_coaster` | `src/overlays/ovl_10_cosmic_coaster/18ABD0.c` | 471 | 0 | 86 | Spawn one track object: link its model into a free slot, add its object, run its init. |
| `func_8010C738_fridged_bridges` | `src/overlays/ovl_24_fridged_bridges/21CAC0.c` | 476 | 0 | 68 | register allocation (masked 0, raw 68): view and model swap saved registers with the grid and loop counters, as in main func_80020E94_main (retail view s2, m s3... |
| `func_80105CBC_three_door_monty` | `src/overlays/ovl_2B_three_door_monty/24A760.c` | 487 | 0 | 2 |  |
| `func_80107F0C_mgenter` | `src/overlays/mgenter/468AC0.c` | 489 | 0 | 23 | FPU register allocation (masked 0): the float-to-s16 arguments land in other $f registers minigame 0x46: the setting's instruction card; zooms out to the top (1... |
| `func_80105EC4_hide_and_sneak` | `src/overlays/ovl_06_hide_and_sneak/137C00.c` | 490 | 0 | 2 |  |
| `func_8010C288_aces_high` | `src/overlays/ovl_17_aces_high/1C4280.c` | 491 | 0 | 36 | register allocation only (masked 0): retail keeps the target yaw in f20 and the yaw difference in f22, here the reverse; len in f4 (here f2) |
| `func_80020E94_main` | `src/20A20.c` | 493 | 0 | 45 | register allocation (masked 0, raw 45): view and model swap saved registers, as in MP1 (retail m s1, view s2, fan s3). Setting fan first fixed the fan[2] load; ... |
| `func_80111004_stardust_battle` | `src/overlays/ovl_41_stardust_battle/2ED2D0.c` | 508 | 0 | 2 | register allocation only (masked 0): in case 4 retail forms sin * t in f0 and takes abs.s into f20, mine multiplies into f20 |
| `func_80106FDC_awful_tower` | `src/overlays/ovl_25_awful_tower/21E010.c` | 533 | 0 | 0 | Stage object setup: sprites, tower pieces, coins, blocks and the background. |
| `func_80107F08_water_whirled` | `src/overlays/ovl_23_water_whirled/211AB0.c` | 535 | 0 | 4 | A rider each frame: take the pad (or the CPU's input), throttle with A, steer, move with the mean of the last moves plus any push, ride the sea, splash, then th... |
| `func_8010BF80_chancetime` | `src/overlays/chancetime/487F50.c` | 535 | 0 | 2 | the sign extension of the sprite id is done in s1 instead of v0; logic checked |
| `func_80106CC4_merry_go_chomp` | `src/overlays/ovl_2D_merry_go_chomp/25E110.c` | 558 | 0 | 4 | masked 0: regalloc only (slot in v1/a0 in the CPU branch) |
| `func_8010D660_filesel` | `src/overlays/filesel/516AE0.c` | 564 | 0 | 46 | register allocation in the digit splits (masked 0), as func_8010D13C_filesel |
| `func_8010AF54_option` | `src/overlays/option/5334D0.c` | 581 | 0 | 8 | Matches except s3/s4 swapped (ret and the hoisted constant 2). |
| `func_80106100_hand_line_sinker` | `src/overlays/ovl_01_hand_line_sinker/11A480.c` | 583 | 0 | 8 | regalloc only: retail keeps the angle in $f20 (reused for z) and the distance in $f22; the C swaps them |
| `func_80109F68_bounce_n_trounce` | `src/overlays/ovl_18_bounce_n_trounce/1CC730.c` | 588 | 0 | 7 | masked 0: two register-allocation residues (the case 2 player pointer, the 360 - diff constant) The finish: decides the winner (or a draw), turns and zooms on t... |
| `func_8010C094_modesel` | `src/overlays/modesel/4F7E90.c` | 630 | 0 | 66 | masked 0, register allocation only (retail keeps i in s1 and the summary base in s2); logic checked against the asm. Build the two save summaries' sprites (0xA-... |
| `func_80107C10_spotlight_swim` | `src/overlays/ovl_03_spotlight_swim/1263E0.c` | 631 | 0 | 14 | The spotlight's steering: picks a target and heading (D_8010D328_spotlight_swim.heading). |
| `func_80106064_puddle_paddle` | `src/overlays/ovl_11_puddle_paddle/191240.c` | 662 | 0 | 9 | The pond: the raft, coins, effects and score sprites. NON_MATCHING: masked 0, spr and first swap s5/s6. |
| `func_80108B08_fowl_play` | `src/overlays/ovl_3A_fowl_play/2C5B50.c` | 666 | 0 | 2 | masked 0; raw 2: retail converts the waypoint distance to double in place ($f20), mine in $f2 CPU input: chases the chick (aiming ahead of it), roams between pe... |
| `func_80107B64_game_guys_magic_boxes` | `src/overlays/ovl_44_game_guys_magic_boxes/308D10.c` | 671 | 0 | 1 | register allocation only: retail ORs the A press with the timer test into a fresh register (or v0,s0,v0), this keeps it in s0 Choose a box: the player with the ... |
| `func_8010A260_storm_chasers` | `src/overlays/ovl_2F_storm_chasers/269BF0.c` | 713 | 0 | 39 | CPU after the storm: walk to its goal point, sidestepping other players. |
| `func_80004D4C_main` | `src/1140.c` | 743 | 0 | 17 | MP3 adds the null-script check (flag 0x40000). Register allocation (masked 0, raw 17 as in MP2): i (the note-on loop counter, one variable with the 0x15/0x17 op... |
| `func_800FA120_name_81` | `src/overlays/ovl_81_name/DFD60.c` | 744 | 0 | 4 | masked 0: two temporaries swap (a0/v1) at the sprite id store |
| `func_8010643C_mstory3` | `src/overlays/mstory3/4B29E0.c` | 745 | 0 | 0 | masked 0 but for a nop KMC puts after each of the cosdf/sindf calls that retail does not have (2 instructions) |
| `func_80022660_main` | `src/22EB0.c` | 756 | 0 | 3 | Register allocation only: the allocation size is built in v0, not a0 |
| `func_8010B5C8_messy_memory` | `src/overlays/ovl_1D_messy_memory/1E37C0.c` | 791 | 0 | 6 | A player's model object (work[0] the player; D_80113B18[player] its state), per game phase. |
| `func_80105CB0_duelresult2` | `src/overlays/duelresult2/45D380.c` | 894 | 0 | 40 | masked 0; register allocation only (the member index j and the &D_80108DB4[i] pointer take s5/s4 the other way round), as in boardresult2's twin. |
| `func_80105CB0_boardresult2` | `src/overlays/boardresult2/3CFC80.c` | 977 | 0 | 40 | Builds the ranking: place badges, the results banner, and per place its badges, portrait and star and coin digits (sprite group D_801099B0[place], members 1-9).... |
| `func_80112200_mgmode` | `src/overlays/mgmode/479470.c` | 1008 | 0 | 7 | The minigame shop: opens the coin-spend window, runs the round (or the door-opening entry from event 3), then loops on the two camera stops: at stop 2, A asks a... |
| `func_800DA768_minigame` | `src/overlays/minigame/AB1C0.c` | 1051 | 0 | 79 | The player's step against the item actors (D_800EBE70_minigame: hazards, bouncing actors, coins) and the other players. Returns 2 when the player stomped or bum... |
| `func_80108550_duel01` | `src/overlays/duel01/3D8AC0.c` | 1063 | 0 | 8 | duel b1: a partner rears up and slams down on the target (level 2: three slams, then a wobble) |
| `func_80108554_duel02` | `src/overlays/duel02/3EC590.c` | 1063 | 0 | 8 | duel b1: a partner rears up and slams down on the target (level 2: three slams, then a wobble) |
| `func_80108554_duel03` | `src/overlays/duel03/3FE1F0.c` | 1063 | 0 | 8 |  |
| `func_80108554_duel04` | `src/overlays/duel04/410910.c` | 1063 | 0 | 8 | board ea1: duel05 twin, duel04 constants checked against retail (immediates); masked 0, raw 8 here; logic as duel05 |
| `func_80108558_duel06` | `src/overlays/duel06/436E50.c` | 1063 | 0 | 8 |  |
| `func_80108560_duel05` | `src/overlays/duel05/426450.c` | 1063 | 0 | 8 |  |
| `func_801085BC_duel10` | `src/overlays/duel10/4461E0.c` | 1063 | 0 | 8 |  |
| `func_80109170_storm_chasers` | `src/overlays/ovl_2F_storm_chasers/269BF0.c` | 1074 | 0 | 36 | CPU: chase the storm (re-aimed with a random delay when it is further than the CPU's radius). |
| `func_80109844_fowl_play` | `src/overlays/ovl_3A_fowl_play/2C5B50.c` | 1082 | 0 | 4 | masked 0; raw 4: the pan computation's FPU registers (retail keeps the sum in $f2, the 128.0 in $f4) The chick: runs from the nearer player, flaps when one is c... |
| `func_8002B2AC_main` | `src/22EB0.c` | 1091 | 0 | 15 | Register allocation only: the cms argument and the display-list pointer swap t1/t2 |
| `func_80108378_boardresult` | `src/overlays/boardresult/3B9670.c` | 1101 | 0 | 0 | The bonus stars: for each award (minigame, coin, happening) the tied leaders' names fill the message, the host plays its animation and the winners walk up with ... |
| `func_80118480_w02` | `src/overlays/w02/335610.c` | 1110 | 0 | 68 | Masked 0, raw 74 (1110 instructions): register allocation only (model/from in s6/s4 swapped, the loop's float constants in other registers, win/i in s2/s0). Log... |
| `func_800DDD94_minigame` | `src/overlays/minigame/AB1C0.c` | 2239 | 0 | 3 | A minigame player's step (MP2 func_80007790_8390, MP1 func_80005A28): stick and buttons, then one branch per motion state (func_800E4A90_minigame's flags), then... |
| `func_80109754_boardresult` | `src/overlays/boardresult/3B9670.c` | 2817 | 0 | 0 | only because functions.us.h declares func_80017AD8_main as returning u8 (src/14EA0.c defines it s16): one extra andi 0xFF. With the call made through an s16 pro... |
| `func_8010856C_duelresult` | `src/overlays/duelresult/4554C0.c` | 2949 | 0 | 0 | masked 0 at the right count when func_80017AD8_main returns s16 (functions.us.h says u8: one extra andi 0xFF); the full ROM build with the header fixed was not ... |
| `func_80107168_mpiq` | `src/overlays/ovl_21_mpiq/204F90.c` | 45 | 1 | 1 | Title sign pulse. |
| `func_8010D620_pump_pump_away` | `src/overlays/ovl_0D_pump_pump_away/16F670.c` | 52 | 1 | 1 |  |
| `func_8001FBFC_main` | `src/hmfman.c` | 69 | 1 | 2 | the lights' direction: (x, y, z) normalised, scaled to 120. Register allocation, as in MP2: retail loads unkB4 into v0 and copies it to s0 after the NULL test (... |
| `func_80111A08_filesel` | `src/overlays/filesel/516AE0.c` | 84 | 1 | 20 | Stick direction as a d-pad mask, repeated every 9 frames while held. branch-likely on the first test and the load order of the stick bytes (masked 1) |
| `func_80108AC0_storyresult` | `src/overlays/storyresult/54F360.c` | 130 | 1 | 24 | Residue (masked 2): the per-rank count local gets an andi and the saved registers rotate (as minigame func_800E7BCC_minigame). func_80108884_storyresult with th... |
| `func_80109420_merry_go_chomp` | `src/overlays/ovl_2D_merry_go_chomp/25E110.c` | 130 | 1 | 2 | masked 0: one store goes through s1 instead of v0 |
| `func_800E7BCC_minigame` | `src/overlays/minigame/BA4B0.c` | 154 | 1 | 24 | register allocation; the per-rank count local gets a redundant andi (masked 1) |
| `func_80108884_storyresult` | `src/overlays/storyresult/54F360.c` | 154 | 1 | 24 |  |
| `func_80106278_mgresultduel` | `src/overlays/mgresultduel/4F01F0.c` | 215 | 1 | 25 | duelres A: Masked 0, raw residue: arg0 and i swap s0/s1. The bell is rung: squash and stretch, then the loser reacts and the coins fly. |
| `func_8010BB9C_cheep_cheep_chase` | `src/overlays/ovl_26_cheep_cheep_chase/225740.c` | 216 | 1 | 4 | Register allocation only (masked 0): the /dz/ temporary is in v1 where retail uses v0. |
| `func_80106A34_bobbing_bow_loons` | `src/overlays/ovl_3D_bobbing_bow_loons/2D8370.c` | 222 | 1 | 1 | only differs by retail passing obj to func_800E6F40_minigame (declared (void)) |
| `func_8010DAC4_msetup` | `src/overlays/msetup/506F20.c` | 222 | 1 | 22 | register allocation only (masked 0): work/slot/y in s4/s3/s2 |
| `func_80105B94_parasol_plummet` | `src/overlays/ovl_1C_parasol_plummet/1DE610.c` | 236 | 1 | 1 | only differs by retail passing obj to func_800E6F40_minigame (declared (void)); with that call it is identical. The main loop: framework state, the finish ranki... |
| `func_80119BC4_w05` | `src/overlays/w05/37FFB0.c` | 241 | 1 | 8 |  |
| `func_8010BD40_hide_and_sneak` | `src/overlays/ovl_06_hide_and_sneak/137C00.c` | 250 | 1 | 9 |  |
| `func_801079E8_motor_rooter` | `src/overlays/ovl_36_motor_rooter/main.c` | 254 | 1 | 5 | <func_801079E8_motor_rooter> |
| `func_8010D580_staff` | `src/overlays/staff/542220.c` | 279 | 1 | 24 | masked 0, raw 23: the two int temporaries swap s0/s1. Logic checked. |
| `func_801178E0_mgmode` | `src/overlays/mgmode/47DD90.c` | 342 | 1 | 8 | Look-at vectors for a camera orbiting center at rot, zoom away: eye, target and the up vector turned rot->z degrees about the view direction (Rodrigues). |
| `func_8010CADC_river_raiders` | `src/overlays/ovl_09_river_raiders/1542E0.c` | 371 | 1 | 6 | The minigame's flow (D_80110D90_river_raiders): 0 intro, 1 start message, 2 race (timer D_80110DE2), 3 finish, * 4 result (coins: team 0 D_80110D84, team 1 D_80... |
| `func_80106410_boulder_ball` | `src/overlays/ovl_04_boulder_ball/12DD30.c` | 621 | 1 | 3 | The slope: runs the minigame's states. masked 0; raw: the finish loop that slows the three runners (unk3C *= 0.8f) loads the object into a0, GCC here into v0 (r... |
| `func_801088A4_aces_high` | `src/overlays/ovl_17_aces_high/1C4280.c` | 807 | 1 | 22 | register allocation only (masked 0): retail keeps stickX in s5 and stickY in s4, here the reverse; abs.s source register |
| `func_80107954_swinging_with_sharks` | `src/overlays/ovl_3F_swinging_with_sharks/2E0D20.c` | 808 | 1 | 31 | register allocation only (the landed-shark index, its HmfModel and &D_8010B8F0 permute s3/s4/s5) |
| `func_800EF3B4_name_81` | `src/overlays/ovl_81_name/D5B20.c` | 8 | 2 | 2 | retail takes an s32 window id (no sign extension); ovl_81.h declares s16, which DFD60's caller needs to match (see n6.header.patch) |
| `func_8008A730_main` | `src/8B1C0.c` | 46 | 2 | 2 | guTranslate by v NON_MATCHING: scheduling only, retail emits lui 0x1 (m[0][0]) before the loads (raw 1) |
| `func_800E2250_minigame` | `src/overlays/minigame/B3CE0.c` | 46 | 2 | 18 | register allocation (masked 2, raw 18), as MP1 func_80009C90 and MP2 func_8000CDC8_D9C8: retail keeps sx in a0 and i in a1 (ours swapped). |
| `func_80109F68_bowser_toss` | `src/overlays/ovl_34_bowser_toss/291020.c` | 52 | 2 | 2 | retail converts y to double before the ground-height add (scheduling only). |
| `func_80109E4C_bowser_toss` | `src/overlays/ovl_34_bowser_toss/291020.c` | 56 | 2 | 6 | register allocation of the second key-frame index. |
| `func_80108B74_slot_synch` | `src/overlays/ovl_14_slot_synch/1AC970.c` | 66 | 2 | 8 |  |
| `func_8010A904_hand_line_sinker` | `src/overlays/ovl_01_hand_line_sinker/11A480.c` | 68 | 2 | 16 | A splash: follows its object and ends with its animation. |
| `func_8010A9F8_hand_line_sinker` | `src/overlays/ovl_01_hand_line_sinker/11A480.c` | 68 | 2 | 16 | The same, for the second splash type. |
| `func_801078E4_hide_and_sneak` | `src/overlays/ovl_06_hide_and_sneak/137C00.c` | 80 | 2 | 6 | H0: masked 2: retail copies omAddObj's result to v1 (same as spotlight_swim func_8010A670); tried a chained store and declaration order. |
| `func_8010D450_staff` | `src/overlays/staff/542220.c` | 80 | 2 | 19 | masked 0, raw 11: FPU registers of the two double products. Logic checked. |
| `func_80111B34_mstory3` | `src/overlays/mstory3/4B9A30.c` | 88 | 2 | 2 |  |
| `func_80107B58_snowball_summit` | `src/overlays/ovl_28_snowball_summit/232A10.c` | 94 | 2 | 13 | Speed from the stick distance (stick.x; a snowball slows its roller by its size) and the next position. scheduling of the 0.4/0.6 blend (retail multiplies by 0.... |
| `func_800F0208_name_81` | `src/overlays/ovl_81_name/D5B20.c` | 97 | 2 | 2 | Matches (masked and raw 0); kept NON_MATCHING only for .rodata: retail pads its two u32->f32 constants to 16 bytes (D_80102590 ends with 8 zero bytes) because a... |
| `func_80111CB8_mstory3` | `src/overlays/mstory3/4B9A30.c` | 103 | 2 | 2 |  |
| `func_8010B900_mpiq` | `src/overlays/ovl_21_mpiq/204F90.c` | 109 | 2 | 3 | Buzz-in process: whoever presses A first (random among ties) answers. |
| `func_8010A260_swinging_with_sharks` | `src/overlays/ovl_3F_swinging_with_sharks/2E0D20.c` | 117 | 2 | 10 | register allocation: model/m swap s1/s2, and the light products use f2/f6 instead of f6/f0 |
| `func_8010B1F4_msetup` | `src/overlays/msetup/506F20.c` | 122 | 2 | 10 | register allocation only: model and shadow swap s2/s3 (tried declaration and assignment order, an s32 model). |
| `func_80108B0C_pump_pump_away` | `src/overlays/ovl_0D_pump_pump_away/16F670.c` | 128 | 2 | 8 |  |
| `func_8010F678_marios_puzzle_party` | `src/overlays/ovl_1F_marios_puzzle_party/1FD760.c` | 128 | 2 | 16 |  |
| `func_80108EC4_stardust_battle` | `src/overlays/ovl_41_stardust_battle/2ED2D0.c` | 146 | 2 | 8 | scheduling only: retail loads hmf->unk60 before sign-extending the material index |
| `func_801087C0_motor_rooter` | `src/overlays/ovl_36_motor_rooter/main.c` | 151 | 2 | 20 | <func_801087C0_motor_rooter> |
| `func_80105CDC_swing_n_swipe` | `src/overlays/ovl_40_swing_n_swipe/2E6BE0.c` | 158 | 2 | 4 | masked 2: retail schedules the stack-array address before the u8 draw's andi (as Hey, Batter, Batter!'s twin) |
| `func_80107EB8_pump_pump_away` | `src/overlays/ovl_0D_pump_pump_away/16F670.c` | 176 | 2 | 12 |  |
| `func_8010D6F4_pump_pump_away` | `src/overlays/ovl_0D_pump_pump_away/16F670.c` | 178 | 2 | 2 |  |
| `func_80107E84_bowser_toss` | `src/overlays/ovl_34_bowser_toss/291020.c` | 180 | 2 | 4 | retail computes the pad index shift before the first store. |
| `func_8010F1F8_chancetime` | `src/overlays/chancetime/487F50.c` | 187 | 2 | 2 | matches with the header fix in e3A.header.patch (func_80060EA8_main takes an s32 window id); logic checked |
| `func_80105DE0_hey_batter_batter` | `src/overlays/ovl_3C_hey_batter_batter/2D3E70.c` | 192 | 2 | 4 | The pitch count: a weighted draw over D_800A11DC_main; CPU batters get a few more or fewer. masked 2: retail schedules the stack-array address before the u8 dra... |
| `func_8010DFA4_chancetime` | `src/overlays/chancetime/487F50.c` | 196 | 2 | 2 | matches with the header fix in e3A.header.patch (func_80060EA8_main takes an s32 window id, as window.c defines it; the s16 prototype truncates the argument); l... |
| `func_80106DAC_boulder_ball` | `src/overlays/ovl_04_boulder_ball/12DD30.c` | 219 | 2 | 3 | A player: models, motions and hooks. masked 2: retail loads both stack constants (0xAC9, 0xA99) before storing them, GCC here interleaves (scheduling only) |
| `func_8010D95C_pump_pump_away` | `src/overlays/ovl_0D_pump_pump_away/16F670.c` | 229 | 2 | 2 |  |
| `func_80106560_slot_synch` | `src/overlays/ovl_14_slot_synch/1AC970.c` | 248 | 2 | 2 |  |
| `func_8010A57C_cheep_cheep_chase` | `src/overlays/ovl_26_cheep_cheep_chase/225740.c` | 273 | 2 | 19 | Register allocation: object/player swapped between s2 and s3, f0/f2 swapped in the threshold sum (trans.z loaded before the add.d). |
| `func_80108ACC_river_raiders` | `src/overlays/ovl_09_river_raiders/1542E0.c` | 301 | 2 | 8 | Resolves the team-1 rafts' collisions: pushes rafts apart, shares drift, clamps them to their lanes and the * banks; repeats (at most 21 passes) until nothing c... |
| `func_8010F268_pump_pump_away` | `src/overlays/ovl_0D_pump_pump_away/16F670.c` | 307 | 2 | 2 |  |
| `func_801067B0_bowser_toss` | `src/overlays/ovl_34_bowser_toss/291020.c` | 319 | 2 | 2 | only the voice-table index shift is scheduled one instruction earlier (as in Bonkers). |
| `func_80107D50_motor_rooter` | `src/overlays/ovl_36_motor_rooter/main.c` | 323 | 2 | 50 | <func_80107D50_motor_rooter> |
| `func_8010EBC4_pump_pump_away` | `src/overlays/ovl_0D_pump_pump_away/16F670.c` | 324 | 2 | 2 |  |
| `func_8010B7B8_three_door_monty` | `src/overlays/ovl_2B_three_door_monty/24A760.c` | 330 | 2 | 38 |  |
| `func_80107470_inst` | `src/overlays/inst/4E0630.c` | 383 | 2 | 11 | Process: builds the instruction board object (model 0 the board, 2 the text page, 4 the title, 6 the cursor, 8 the frame), marks the parts named by the type's p... |
| `func_80106EB0_stardust_battle` | `src/overlays/ovl_41_stardust_battle/2ED2D0.c` | 410 | 2 | 2 | scheduling only: retail puts the sll of the rand8() index after the lui/addiu of D_80113E1C |
| `func_80108570_mgresultdealer` | `src/overlays/mgresultdealer/4EDCB0.c` | 425 | 2 | 10 | masked 24: the digit file id and its sign-extended copy swap s4/s5 the score board's process |
| `func_801076B0_mgmode` | `src/overlays/mgmode/46CC10.c` | 467 | 2 | 53 | register allocation in the face centroid loop (i/j/vtx/count swap registers); otherwise identical |
| `func_8010EB94_msetup` | `src/overlays/msetup/506F20.c` | 490 | 2 | 9 | float registers: 0.8f and -1/7 hoisted into f24/f22 swapped (masked 2) |
| `func_80105E14_mpiq` | `src/overlays/ovl_21_mpiq/204F90.c` | 533 | 2 | 5 | A player (podium contestant): model, motions, position. |
| `func_8010664C_picking_panic` | `src/overlays/ovl_0F_picking_panic/181950.c` | 584 | 2 | 2 |  |
| `func_8010DA64_messy_memory` | `src/overlays/ovl_1D_messy_memory/1E37C0.c` | 595 | 2 | 25 | An item's shadow object (work[0] the item, work[1] its board). Retail's slot loops read one past their table. |
| `func_80108E1C_boardresult2` | `src/overlays/boardresult2/3CFC80.c` | 716 | 2 | 2 | (see func_80108C70_boardresult2). |
| `func_80109444_w10` | `src/overlays/w10/3B3620.c` | 2338 | 2 | 2 | The tutorial script: the guide walks through the board, spaces, items, the minigame, the Boo, Star and Bowser stops, then fades out and leaves the board. NON_MA... |
| `func_80106534_slapdown` | `src/overlays/ovl_2E_slapdown/264B80.c` | 43 | 3 | 3 |  |
| `func_801099C0_inst` | `src/overlays/inst/4E1510.c` | 57 | 3 | 4 | Retail indexes HmfModelData with the motion id (obj->motion[3]) for the blend length. |
| `func_80108958_all_fired_up` | `src/overlays/ovl_29_all_fired_up/23C8F0.c` | 91 | 3 | 3 | masked 3: scheduling only (retail sets i = 0 between the row load and its address); logic checked |
| `func_8010AF10_the_beat_goes_on` | `src/overlays/ovl_20_the_beat_goes_on/1FE4D0.c` | 91 | 3 | 3 | All Fired Up's func_80108958 (exact twin, same C and nop strip) matches there; here the move s1,zero schedules before the unk59 load Hit puffs (one model per pl... |
| `func_8010A060_game_guys_roulette` | `src/overlays/ovl_42_game_guys_roulette/2FF5F0.c` | 92 | 3 | 6 | Clear a ring's square from this frame's buffers masked 6: retail's strength-reduced row pointers come from C not found (this C writes them out; same bytes clear... |
| `func_8010BC00_game_guys_magic_boxes` | `src/overlays/ovl_44_game_guys_magic_boxes/30DC30.c` | 92 | 3 | 6 | Clear a ring's square from this frame's buffers masked 6: retail's strength-reduced row pointers come from C not found (this C writes them out; same bytes clear... |
| `func_8010C590_game_guys_sweet_surprise` | `src/overlays/ovl_45_game_guys_sweet_surprise/3151F0.c` | 92 | 3 | 6 | Clear a ring's square from this frame's buffers masked 6: retail's strength-reduced row pointers come from C not found (this C writes them out; same bytes clear... |
| `func_8010CB70_game_guys_lucky_7` | `src/overlays/ovl_43_game_guys_lucky_7/306F70.c` | 92 | 3 | 6 | Clear a ring's square from this frame's buffers masked 6: retail's strength-reduced row pointers come from C not found (this C writes them out; same bytes clear... |
| `func_80107FCC_mpiq` | `src/overlays/ovl_21_mpiq/204F90.c` | 102 | 3 | 3 | Show the effect over a player's head (height by character). |
| `func_80108C64_treadmill_grill` | `src/overlays/ovl_15_treadmill_grill/1B4F10.c` | 102 | 3 | 3 | Landing puffs (All Fired Up func_80108958 twin). Masked 3: retail sets i = 0 after the row load; logic checked. |
| `func_8010BC08_three_door_monty` | `src/overlays/ovl_2B_three_door_monty/24A760.c` | 111 | 3 | 3 | scheduling (masked 2): the sll of the position-table index is placed before the table base lui |
| `func_8005B238_main` | `src/window.c` | 129 | 3 | 46 | register allocation (masked 3): retail loads the third byte into the result register (beql) |
| `func_8010A258_rockin_raceway` | `src/overlays/ovl_2C_rockin_raceway/251FF0.c` | 136 | 3 | 10 |  |
| `func_8010E29C_messy_memory` | `src/overlays/ovl_1D_messy_memory/1E37C0.c` | 175 | 3 | 29 | An item's shadow (D_80111700[48 + board * 10 + item]): shown under items of the shown room that sit on a slot. |
| `func_80031B30_main` | `src/32160.c` | 191 | 3 | 54 | Register allocation (masked 3, 190 vs 191): s1/s2 swapped for arg0/tex, and retail keeps the RGB24 red byte as a u8 with an extra andi 0xff before the shifts. |
| `func_8010EBB0_messy_memory` | `src/overlays/ovl_1D_messy_memory/1E37C0.c` | 210 | 3 | 3 | Sets up intro mover work[0]: the first loads the model and its motions, the others link to it; a shadow model. |
| `func_8010A5FC_the_beat_goes_on` | `src/overlays/ovl_20_the_beat_goes_on/1FE4D0.c` | 215 | 3 | 14 | masked 3: the difficulty switch puts case 3 and default in the other order; chance in a0 (retail v1) A player's buttons: the pad, or for a CPU the current note,... |
| `func_8010EA04_stardust_battle` | `src/overlays/ovl_41_stardust_battle/2ED2D0.c` | 230 | 3 | 23 | register allocation (f4/f6 swapped between the push ratio and dy) and the D_80114B2C copy scheduled after the second null test in retail; ops equal |
| `func_8010BDA4_duelresult` | `src/overlays/duelresult/45A700.c` | 238 | 3 | 3 | duel r2: masked 3: retail stores scale in rand8's delay slot with 3.0f still hoisted; only the source order that hoists it (scale before vel.z) fills the slot w... |
| `func_8010CEF4_boardresult` | `src/overlays/boardresult/3BFA00.c` | 238 | 3 | 3 | event e8: masked 3: retail stores scale in rand8's delay slot with 3.0f still hoisted; only the source order that hoists it (scale before vel.z) fills the slot ... |
| `func_8010F04C_staff` | `src/overlays/staff/542220.c` | 238 | 3 | 3 | masked 3: retail stores scale in rand8's delay slot with 3.0f still hoisted; only the source order that hoists it (scale before vel.z) fills the slot with vel.z... |
| `func_8010C03C_messy_memory` | `src/overlays/ovl_1D_messy_memory/1E37C0.c` | 253 | 3 | 3 | A player's model: character model, shadow, motions, start position. |
| `func_8010C44C_motor_rooter` | `src/overlays/ovl_36_motor_rooter/main.c` | 271 | 3 | 21 | <func_8010C44C_motor_rooter> |
| `func_8010A67C_crazy_cogs` | `src/overlays/ovl_05_crazy_cogs/131C10.c` | 287 | 3 | 4 | Spawns hazards while playing: one of 0..6 every 30..39 frames (the next free one), and 7, 8 and 9 at random * on their own beats. |
| `func_8010660C_baby_bowser_bonkers` | `src/overlays/ovl_35_baby_bowser_bonkers/29B1D0.c` | 359 | 3 | 3 | only the voice-table index shift is scheduled one instruction earlier than retail. |
| `func_80107580_opboard` | `src/overlays/opboard/3CA800.c` | 580 | 3 | 81 | register allocation in the closed-path neighbour loads (masked 3) |
| `func_801077C4_mstory1` | `src/overlays/mstory1/48D950.c` | 580 | 3 | 81 | the point at t (0..1) along a path: a spline through the four points around the segment t falls in |
| `func_801078B4_mstory4` | `src/overlays/mstory4/4C47E0.c` | 580 | 3 | 81 | the point at t (0..1) along a path: a spline through the four points around the segment t falls in |
| `func_80107B54_mstory5` | `src/overlays/mstory5/4D1200.c` | 580 | 3 | 81 | the point at t (0..1) along a path: a spline through the four points around the segment t falls in |
| `func_80107E94_mstory2` | `src/overlays/mstory2/49DF30.c` | 580 | 3 | 81 | the point at t (0..1) along a path: a spline through the four points around the segment t falls in |
| `func_80108084_mstory3` | `src/overlays/mstory3/4B29E0.c` | 580 | 3 | 81 | register allocation only (masked 0), as mstory1's func_801077C4 |
| `func_801088F4_staff` | `src/overlays/staff/542220.c` | 580 | 3 | 81 | the point at t (0..1) along a path: a spline through the four points around the segment t falls in |
| `func_8010B124_mstory4` | `src/overlays/mstory4/4C8050.c` | 580 | 3 | 81 | the point at t (0..1) along a path: a spline through the four points around the segment t falls in |
| `func_8010C0C4_mstory1` | `src/overlays/mstory1/492250.c` | 580 | 3 | 81 | register allocation in the closed-path neighbour loads (as opboard's twin) |
| `func_8010C814_mstory2` | `src/overlays/mstory2/4A28B0.c` | 580 | 3 | 81 | as mstory1's func_801077C4_mstory1 (same code) |
| `func_8010CCF4_mstory3` | `src/overlays/mstory3/4B9A30.c` | 580 | 3 | 81 | the point at t (0..1) along a path: a spline through the four points around the segment t falls in |
| `func_8010F7D4_mstory5` | `src/overlays/mstory5/4D8E80.c` | 580 | 3 | 81 | the point at t (0..1) along a path: a spline through the four points around the segment t falls in |
| `func_80110804_mstory1` | `src/overlays/mstory1/496990.c` | 580 | 3 | 81 | register allocation in the closed-path neighbour loads (masked 3) |
| `func_801114A4_mstory2` | `src/overlays/mstory2/4A7540.c` | 580 | 3 | 81 | the point at t (0..1) along a path: a spline through the four points around the segment t falls in |
| `func_80116164_mstory2` | `src/overlays/mstory2/4AC200.c` | 580 | 3 | 81 | the point at t (0..1) along a path: a spline through the four points around the segment t falls in |
| `func_8010B640_end_of_the_line` | `src/overlays/ovl_33_end_of_the_line/28A290.c` | 601 | 3 | 50 | Register allocation: p/hud/pw2/scissor land in s2/s1/s3/s0 instead of s3/s2/s0/s1, and the camera byte is masked at its first use instead of once. |
| `HuVecDistance` | `src/libhmath/vecdist.c` | 21 | 4 | 4 | scheduling: retail moves the prologue after the subtractions and multiplies, which KMC GCC 2.7.2 never does (its prologue is emitted as text, not scheduled RTL)... |
| `func_80105FCC_marios_puzzle_party` | `src/overlays/ovl_1F_marios_puzzle_party/1F3B90.c` | 41 | 4 | 18 |  |
| `func_8008D130_main` | `src/8D8C0.c` | 47 | 4 | 9 | loop counters, retail keeps the row loop's i as its own counter where GCC reduces it to i*16 (masked 4-6; MP2 has the same residue) |
| `func_8008CCC0_main` | `src/8D8C0.c` | 51 | 4 | 18 | loop counters, retail keeps the row loop's i as its own counter where GCC reduces it to i*16 (masked 4-6; MP2 has the same residue) |
| `func_80105C98_hide_and_sneak` | `src/overlays/ovl_06_hide_and_sneak/137C00.c` | 51 | 4 | 5 |  |
| `func_80106704_messy_memory` | `src/overlays/ovl_1D_messy_memory/1E37C0.c` | 51 | 4 | 5 |  |
| `func_80105BB4_hide_and_sneak` | `src/overlays/ovl_06_hide_and_sneak/137C00.c` | 57 | 4 | 5 |  |
| `func_80106620_messy_memory` | `src/overlays/ovl_1D_messy_memory/1E37C0.c` | 57 | 4 | 5 |  |
| `func_8010D484_mstory5` | `src/overlays/mstory5/4D1200.c` | 67 | 4 | 9 | actor 7 turns, walks 1000 units off along x and hides its models |
| `func_8011249C_mstory3` | `src/overlays/mstory3/4B9A30.c` | 82 | 4 | 4 |  |
| `func_8010C1E4_mstory2` | `src/overlays/mstory2/49DF30.c` | 91 | 4 | 4 | scheduling only; retail computes ofs + 25 before the wrap test (in its branch delay slot) and the mul right after the call |
| `func_8008A7F0_main` | `src/8B3F0.c` | 92 | 4 | 4 | guRotateRPYF (as 89510.c's func_80088910_main) with the angles, in degrees, taken from a Vec NON_MATCHING: prologue scheduling only, the first angle load sits a... |
| `func_801059F8_w03` | `src/overlays/w03/34E840.c` | 97 | 4 | 4 | board p1: li s0,7 scheduled into the MBRand delay slot (retail: before the lui) |
| `func_80106568_mgenter` | `src/overlays/mgenter/468AC0.c` | 126 | 4 | 4 | the minigame's name, dropped in from the top |
| `func_80045D38_main` | `src/pause.c` | 132 | 4 | 38 | Load order (masked 4): retail sums each sound's base id as lh unk00 + lbu unk06, GCC here loads unk06 first and narrows unk00 to lhu. |
| `func_80017790_main` | `src/14EA0.c` | 137 | 4 | 34 | Replaces texture animation arg2 of set arg1 on model arg0 with data file arg3; returns the new animation's first frame (MP2 func_80025384_25F84). register alloc... |
| `func_80109B60_game_guys_roulette` | `src/overlays/ovl_42_game_guys_roulette/2FF5F0.c` | 137 | 4 | 4 | Another ending of the effect (not called in this overlay): fade the mask layer in, then draw lines falling from above x; returns 1 when done masked 4: retail co... |
| `func_8010B700_game_guys_magic_boxes` | `src/overlays/ovl_44_game_guys_magic_boxes/30DC30.c` | 137 | 4 | 4 | Another ending of the effect (not called in this overlay): fade the mask layer in, then draw lines falling from above x; returns 1 when done masked 4: retail co... |
| `func_8010C090_game_guys_sweet_surprise` | `src/overlays/ovl_45_game_guys_sweet_surprise/3151F0.c` | 137 | 4 | 4 | Another ending of the effect (not called in this overlay): fade the mask layer in, then draw lines falling from above x; returns 1 when done masked 4: retail co... |
| `func_8010C670_game_guys_lucky_7` | `src/overlays/ovl_43_game_guys_lucky_7/306F70.c` | 137 | 4 | 4 | Another ending of the effect (not called in this overlay): fade the mask layer in, then draw lines falling from above x; returns 1 when done masked 4: retail co... |
| `func_80108C60_fridged_bridges` | `src/overlays/ovl_24_fridged_bridges/216670.c` | 165 | 4 | 10 | Released hook: falls into the water, then the next bridge piece rises |
| `func_80105B94_baby_bowser_broadside` | `src/overlays/ovl_0C_baby_bowser_broadside/165010.c` | 166 | 4 | 12 | <func_80105B94_baby_bowser_broadside> |
| `func_80112514_mstory5` | `src/overlays/mstory5/4D8E80.c` | 181 | 4 | 9 | only the HmfModelData load is scheduled differently |
| `func_80114404_mgmode` | `src/overlays/mgmode/479470.c` | 189 | 4 | 10 | Counts the bonus coins into the total, then plays the win or lose motion and voice. |
| `func_80105DAC_cosmic_coaster` | `src/overlays/ovl_10_cosmic_coaster/18ABD0.c` | 197 | 4 | 7 | Main state: start the race, pick the winning car, pay the bonus, fade out. |
| `func_8010AC80_end_of_the_line` | `src/overlays/ovl_33_end_of_the_line/28A290.c` | 200 | 4 | 4 | Two "(rand8() >> 7) & 1": retail emits srl 7 + andi 1, this C andi 0xff + srl 7 (same value). |
| `func_8010ACC4_hide_and_sneak` | `src/overlays/ovl_06_hide_and_sneak/137C00.c` | 203 | 4 | 14 |  |
| `func_801089E0_treadmill_grill` | `src/overlays/ovl_15_treadmill_grill/1B4F10.c` | 213 | 4 | 20 | Loads the 16 player-skin models (D_8010B310). Masked 4: retail keeps the model number unextended in a second register for the store; logic checked. |
| `func_8010F6E8_messy_memory` | `src/overlays/ovl_1D_messy_memory/1E37C0.c` | 246 | 4 | 33 | The result score digits (D_80111700[74 + board * 3 + k]): count up, shown, then shrink away (D_80115D7C). |
| `func_801095C8_coconut_conk` | `src/overlays/ovl_02_coconut_conk/120BC0.c` | 248 | 4 | 4 | A team player hits a palm tree: the nearest tree shakes and drops one of its three coconuts. |
| `func_801098A0_marios_puzzle_party` | `src/overlays/ovl_1F_marios_puzzle_party/1F3B90.c` | 249 | 4 | 6 | Score display (five digits, clamped to 0..99999). |
| `func_8010A160_parasol_plummet` | `src/overlays/ovl_1C_parasol_plummet/1DE610.c` | 249 | 4 | 13 | register allocation and the digit x (this hoists x + 0x20 out of the loop; masked 3). Creates the coin counter sprites and starts their process. |
| `func_80109988_fridged_bridges` | `src/overlays/ovl_24_fridged_bridges/216670.c` | 268 | 4 | 7 | Ground under 8 points around the player and its centre; returns how many have none |
| `func_80108720_fridged_bridges` | `src/overlays/ovl_24_fridged_bridges/216670.c` | 293 | 4 | 4 | Bridge pieces: models and falling objects |
| `func_801109BC_messy_memory` | `src/overlays/ovl_1D_messy_memory/1E37C0.c` | 299 | 4 | 6 | The minigame's start: resets the overlay state, creates every object, fades in, then runs func_8010FDF0. |
| `func_801094CC_pump_pump_away` | `src/overlays/ovl_0D_pump_pump_away/16F670.c` | 303 | 4 | 31 |  |
| `func_80108368_puddle_paddle` | `src/overlays/ovl_11_puddle_paddle/191240.c` | 305 | 4 | 7 | Throws 2 to 4 coins at angles at least 45 degrees apart when the throw motion reaches frame 30. NON_MATCHING: masked 0, chance and the angles pointer swap s3/s4... |
| `func_80109A90_inst` | `src/overlays/inst/4E2C50.c` | 319 | 4 | 7 | retail reads the low half of D_8010DC40_inst through its own label (D_8010DC42) at * each use; the endian-neutral (s16) read here makes GCC keep &D_8010DC40_ins... |
| `func_80118850_duel04` | `src/overlays/duel04/410910.c` | 397 | 4 | 4 | board ea3: masked 4: retail tests the loop count with blez where this C gets beqz (combine knows the count is 0..2 here); logic checked case by case. |
| `func_8010DB98_marios_puzzle_party` | `src/overlays/ovl_1F_marios_puzzle_party/1F3B90.c` | 421 | 4 | 6 | Per frame: bob each board until its player is out, add the shake and drop offsets, and move the frame, panels and cursor with it. |
| `func_80110E3C_mstory4` | `src/overlays/mstory4/4C8050.c` | 437 | 4 | 9 | scheduling: retail reads the sindf results without a nop and keeps the face-table load earlier (raw 18, masked 13) |
| `func_80107888_mgresultdealer` | `src/overlays/mgresultdealer/4EDCB0.c` | 457 | 4 | 9 | masked 4: retail loads D_800D408C_main after the bank index arithmetic drop coins (one, or with 20+ to go one or two, every D_80109924 frames) and let them fall... |
| `func_80107760_stardust_battle` | `src/overlays/ovl_41_stardust_battle/2ED2D0.c` | 468 | 4 | 9 | scheduling only: in the "no item yet" case retail loads HmfModelData into a0 before the model-index multiply, mine into v1 after it |
| `func_80109390_fridged_bridges` | `src/overlays/ovl_24_fridged_bridges/216670.c` | 509 | 4 | 5 | Winner: walk to the goal, camera move, win pose |
| `func_801059A0_swinging_with_sharks` | `src/overlays/ovl_3F_swinging_with_sharks/2E0D20.c` | 550 | 4 | 10 | the CPU shark pick: retail computes (rand8() * 5) >> 8 into v0 and indexes through v1, not at |
| `func_801073AC_game_guys_roulette` | `src/overlays/ovl_42_game_guys_roulette/2FC270.c` | 582 | 4 | 4 | The bet: move the cursor (the player's face) over the six prizes with the stick, A or the timer ends it; the CPU steps down to its guess. The chosen prize pulse... |
| `func_8010689C_hand_line_sinker` | `src/overlays/ovl_01_hand_line_sinker/11A480.c` | 808 | 4 | 21 | regalloc only: retail puts fabsf's result and the case-3 rod angle in other float registers |
| `func_8001B0B4_main` | `src/hmfman.c` | 999 | 4 | 63 | MP2 func_800286FC_292FC (NON_MATCHING too): draw every model, camera by camera, and send the list. Register allocation (masked 6, 997 vs 999): GCC keeps the cam... |
| `func_80105C1C_filesel` | `src/overlays/filesel/516AE0.c` | 50 | 5 | 10 | Same as opening's func_8010621C_opening: GCC hoists &D_801135D0_filesel into a register (retail addresses it through $at each iteration). |
| `func_80105C7C_modesel` | `src/overlays/modesel/4F7E90.c` | 50 | 5 | 10 | masked 5: GCC hoists &D_8010FE10 into t0, retail indexes it from %hi/%lo each pass (twins in filesel, opening, option; H0 tried a chained store and &D_8010F710[... |
| `func_8010621C_opening` | `src/overlays/opening/523FD0.c` | 50 | 5 | 10 |  |
| `func_8011019C_option` | `src/overlays/option/5334D0.c` | 50 | 5 | 10 |  |
| `func_80113874_mstory3` | `src/overlays/mstory3/4B9A30.c` | 63 | 5 | 10 |  |
| `func_8010CDE4_fridged_bridges` | `src/overlays/ovl_24_fridged_bridges/21CAC0.c` | 75 | 5 | 6 | (masked 5, raw 6): retail indexes the count as (view + list * 2)->0x18 in the second test; this C forms &view->cnt[list] first. Without the pointer GCC threads ... |
| `func_80108E48_eatsa_pizza` | `src/overlays/ovl_0B_eatsa_pizza/161750.c` | 77 | 5 | 9 | A bite mark at the player, tinted with an RGBA5551 colour. |
| `func_80106FD8_pipe_cleaners` | `src/overlays/ovl_27_pipe_cleaners/22E100.c` | 85 | 5 | 5 | Shadow scale follows the pull motion. control flow (masked 5): retail repeats the obj->model load in the frame < 20 arm and jumps past the join's copy (tried: t... |
| `func_80115A9C_mgmode` | `src/overlays/mgmode/479470.c` | 87 | 5 | 19 | Places the coin counter (label, icon, four digits) at (x, y) showing coins. |
| `func_8010DB30_mstory5` | `src/overlays/mstory5/4D1200.c` | 94 | 5 | 10 | actor 7 bobs up and down (a process; never ends while D_80114774_mstory5 is set) register allocation (masked 5): retail loads model with its own lhu; here it is... |
| `func_80107960_chip_shot_challenge` | `src/overlays/ovl_1B_chip_shot_challenge/1D9550.c` | 170 | 5 | 14 | show the ball's distance to the hole masked 5, one instruction short: retail keeps dist and the thousands digit in two registers (s3, s1) where this C shares on... |
| `func_80108514_motor_rooter` | `src/overlays/ovl_36_motor_rooter/main.c` | 202 | 5 | 42 | <func_80108514_motor_rooter> |
| `func_801059A0_bounce_n_trounce` | `src/overlays/ovl_18_bounce_n_trounce/1CC730.c` | 233 | 5 | 5 | retail masks the random slot twice (andi 3, andi 0xFF); everything else matches |
| `func_801094A4_fowl_play` | `src/overlays/ovl_3A_fowl_play/2C5B50.c` | 277 | 5 | 7 | one instruction long: retail sign-extends the billboard id before storing its low byte to boards[i] |
| `func_8010A9D0_merry_go_chomp` | `src/overlays/ovl_2D_merry_go_chomp/25E110.c` | 312 | 5 | 5 | masked 5: retail sign-extends the shadow model handle once after storing it |
| `func_80112104_mstory5` | `src/overlays/mstory5/4D8E80.c` | 336 | 5 | 32 | the effect object: 16 puffs (NON_MATCHING: registers s1/s2 swapped, and retail reloads time after the += before comparing it with 40) |
| `func_8010AF0C_motor_rooter` | `src/overlays/ovl_36_motor_rooter/main.c` | 343 | 5 | 8 | <func_8010AF0C_motor_rooter> |
| `func_8010B17C_the_beat_goes_on` | `src/overlays/ovl_20_the_beat_goes_on/1FE4D0.c` | 442 | 5 | 5 | masked 4: retail uses func_8000B838_main's first result unconverted (as from an int function); game/esprite.h declares it s16 The note display (sprites). |
| `func_80108AF0_inst` | `src/overlays/inst/4E1510.c` | 617 | 5 | 57 | Decodes the HVQ image (data, an RGBA5551 128x96 picture) and its 8-bit alpha (alpha, at the offset its header's bytes 0x0A/0x0B give) into an RGBA32 texture, th... |
| `func_80107D0C_mgmode` | `src/overlays/mgmode/46CC10.c` | 800 | 5 | 22 | GCC hoists y - 0x47 out of the window loop where retail adds it per pass, and s0/s1/s2 swap in the unlock check; otherwise identical |
| `func_80106134_mstory4` | `src/overlays/mstory4/4C2BD0.c` | 848 | 5 | 71 | opcode-identical except: retail's cosdf/sindf delay slots were filled by the assembler (no nop after them; KMC GCC fills them itself, and as adds a nop), the sp... |
| `func_8010F2F4_msetup` | `src/overlays/msetup/506F20.c` | 11 | 6 | 8 | retail sign-extends state at entry and loads the old state with lh (masked 6); same logic |
| `HuVecNormalize3F` | `src/libhmath/vecnorm3f.c` | 36 | 6 | 6 | https: decomp.me/scratch/6UMIQ scheduling: retail interleaves the prologue's register saves with the loads, which KMC GCC 2.7.2 never does (its prologue is emit... |
| `func_8010B038_popgun_pickoff` | `src/overlays/ovl_32_popgun_pickoff/283060.c` | 41 | 6 | 10 | control flow (masked 6): retail copies id before sign-extending it twice (compare, index) and keeps w in a1 (tried s32 parameters with s16 casts, a K&R definiti... |
| `func_800F38DC_name_81` | `src/overlays/ovl_81_name/D5B20.c` | 45 | 6 | 26 | Retail passes attr to func_800F89D0 zero-extended (that call saw no s16 prototype); ovl_81.h's s16 arg3 adds a sign extension. The callee narrows it to s16 eith... |
| `func_8008CFA0_main` | `src/8D8C0.c` | 51 | 6 | 14 | loop counters, retail keeps the row loop's i as its own counter where GCC reduces it to i*16 (masked 4-6; MP2 has the same residue) |
| `func_8008CE00_main` | `src/8D8C0.c` | 55 | 6 | 14 | loop counters, retail keeps the row loop's i as its own counter where GCC reduces it to i*16 (masked 4-6; MP2 has the same residue) |
| `func_80108AA8_slot_synch` | `src/overlays/ovl_14_slot_synch/1AC970.c` | 55 | 6 | 7 |  |
| `func_8010ACA8_modesel` | `src/overlays/modesel/4F7E90.c` | 57 | 6 | 19 | masked 6: retail keeps no = 10 in s2 and passes it in a0 to func_8010AC3C too (GCC folds the constant) |
| `func_80111490_opening` | `src/overlays/opening/523FD0.c` | 58 | 6 | 14 |  |
| `func_8010CCBC_pump_pump_away` | `src/overlays/ovl_0D_pump_pump_away/16F670.c` | 91 | 6 | 10 | masked 6: retail shares the second branch's "return 0" and call blocks with the first; tried an if/else with one shared return 0 (masked 11) and a (u16) on eith... |
| `func_80111E78_filesel` | `src/overlays/filesel/516AE0.c` | 134 | 6 | 12 | the 99 clamps branch the other way (bnez/move vs beqz/li) and use other registers; logic checked |
| `func_80111FFC_filesel` | `src/overlays/filesel/516AE0.c` | 135 | 6 | 12 | the 99 clamps branch the other way (bnez/move vs beqz/li) and use other registers; logic checked |
| `func_8010AD98_bowser_toss` | `src/overlays/ovl_34_bowser_toss/291020.c` | 136 | 6 | 5 | retail sign-extends the new sprite group before storing it (one instruction moved). |
| `func_80108318_mgresultduel` | `src/overlays/mgresultduel/4F01F0.c` | 137 | 6 | 13 | duelres A: Masked 5: retail sign-extends the winner twice (s8 for the first call, s16 for the second). Show the coins won over the winner's head and add them. |
| `func_8010D9AC_marios_puzzle_party` | `src/overlays/ovl_1F_marios_puzzle_party/1F3B90.c` | 151 | 6 | 9 | Hide the pieces and cursors while paused (or once a player is out). |
| `opTitleMain` | `src/overlays/opening/523FD0.c` | 152 | 6 | 7 |  |
| `func_80111CBC_filesel` | `src/overlays/filesel/516AE0.c` | 157 | 6 | 12 | the 99 clamps branch the other way (bnez/move vs beqz/li) and use other registers; logic checked |
| `func_8010AE30_aces_high` | `src/overlays/ovl_17_aces_high/1C4280.c` | 200 | 6 | 107 | masked 6: retail computes the centre y (trans.y + 100) in both paths, here once after the join; registers of ry/rx/cx differ; same operations otherwise |
| `func_8010FC58_filesel` | `src/overlays/filesel/516AE0.c` | 200 | 6 | 22 | float register allocation of the 0.9/0.1 constants (masked 4) |
| `func_801072C4_spotlight_swim` | `src/overlays/ovl_03_spotlight_swim/1263E0.c` | 205 | 6 | 15 | retail reloads D_8010D58E_spotlight_swim for the model index after the z store; mine reuses it (regalloc follows) |
| `func_8010A66C_option` | `src/overlays/option/5334D0.c` | 210 | 6 | 7 | Only difference: retail sets sel = 9 then copies it to mode in the default case (li s1,9; move s0,s1); this C gives li s0,9. |
| `func_801149F4_mgmode` | `src/overlays/mgmode/479470.c` | 210 | 6 | 9 | Fades in the minigame picture, spins through the four categories' minigames for 30 frames and lands on this round's; returns it. |
| `func_801059A0_ridiculous_relay` | `src/overlays/ovl_07_ridiculous_relay/13E9C0.c` | 290 | 6 | 7 |  |
| `func_80109D88_hide_and_sneak` | `src/overlays/ovl_06_hide_and_sneak/137C00.c` | 357 | 6 | 18 |  |
| `func_800EAE7C_minigame` | `src/overlays/minigame/BD210.c` | 361 | 6 | 9 | register choice and scheduling (masked 6), as MP1 func_8006C058: f2/f6 for the spilled grow/shrink step, and the obj->model load is scheduled before the multipl... |
| `func_8010A610_mstory1` | `src/overlays/mstory1/48D950.c` | 375 | 6 | 13 | retail loads model[1] twice (lhu and lh); KMC merges the loads here |
| `func_8010AC40_mstory1` | `src/overlays/mstory1/48D950.c` | 395 | 6 | 40 | retail loads model[1] twice (lhu and lh); KMC merges the loads here |
| `func_80108DF8_water_whirled` | `src/overlays/ovl_23_water_whirled/211AB0.c` | 401 | 6 | 10 | The HUD: centre sprite, then per player a panel, the character face, three marks and a 3-digit number. |
| `func_801085F4_dizzy_dinghies` | `src/overlays/ovl_46_dizzy_dinghies/316DF0.c` | 630 | 6 | 33 | Differs only in f20/f22 allocation (speed and y). The player's dinghy: paddle with A, steer with the stick; the sea and pushes move it. |
| `func_8010CC38_modesel` | `src/overlays/modesel/4F7E90.c` | 63 | 7 | 7 | The two-choice prompt (NON_MATCHING: retail enters the loop with a0 = 14 as a constant and lays the B branch out with a j instead of branch-likely; logic checke... |
| `func_800E7E08_minigame` | `src/overlays/minigame/BA4B0.c` | 105 | 7 | 9 | delay-slot filling in the page 2 branch (masked 9) |
| `func_8010FA38_messy_memory` | `src/overlays/ovl_1D_messy_memory/1E37C0.c` | 110 | 7 | 28 | Sets up result digit k of board work[1] (two number digits and a sign), placed from D_801112B8. |
| `func_8010A420_modesel` | `src/overlays/modesel/4F7E90.c` | 152 | 7 | 23 | Bob part of model `no` jumps to (0, 200, 300) on an arc. |
| `func_800EC99C_name_81` | `src/overlays/ovl_81_name/D3450.c` | 159 | 7 | 24 | block layout of the two rev & 4 tests and s-register allocation the back partner follows the player to the next space |
| `func_800EC6F4_name_81` | `src/overlays/ovl_81_name/D3450.c` | 163 | 7 | 14 | block layout of the two rev & 4 tests and s-register allocation the front partner follows the player to the next space |
| `func_8010BA6C_spotlight_swim` | `src/overlays/ovl_03_spotlight_swim/1263E0.c` | 173 | 7 | 24 | regalloc/constant hoisting: retail keeps the constant 4 in t1 (y + 4 as addu) and builds 0x27C004 as * 0x27C000 / 4; mine hoists 0xE4500000 instead. Same DL wor... |
| `func_80106868_three_door_monty` | `src/overlays/ovl_2B_three_door_monty/24A760.c` | 208 | 7 | 32 |  |
| `func_8010AE10_fowl_play` | `src/overlays/ovl_3A_fowl_play/2C5B50.c` | 211 | 7 | 59 | The parameter along d1 where the line p1 + t * d1 meets the line p2 + s * d2, or -1. |
| `func_801059A0_marios_puzzle_party` | `src/overlays/ovl_1F_marios_puzzle_party/1F3B90.c` | 257 | 7 | 10 | ObjectSetup: camera, the per-player games, board placement, sparkles, setup, pause watcher. |
| `func_8010EE84_mgmode` | `src/overlays/mgmode/473130.c` | 345 | 7 | 17 | masked 7; register allocation and the shadow-model address formed differently. |
| `func_8010615C_staff` | `src/overlays/staff/542220.c` | 424 | 7 | 18 | Residue (masked 11): retail schedules the &Center load before the first mul.s, and f2/f12 swap in the distance sum (as msetup func_801068F4_msetup). |
| `func_80106190_storyresult` | `src/overlays/storyresult/54DD10.c` | 424 | 7 | 18 | msetup func_80106320_msetup without its loop; the camera process func_80106754_storyresult calls it. |
| `func_8010FC98_mstory4` | `src/overlays/mstory4/4C8050.c` | 464 | 7 | 12 |  |
| `func_80106CE4_puddle_paddle` | `src/overlays/ovl_11_puddle_paddle/191240.c` | 506 | 7 | 7 | A player object. NON_MATCHING: the two D_800A178C/D_800A1790 loads for func_800E1BA8_minigame are scheduled after the a3 and stack arguments instead of before (... |
| `func_801089B4_thwomp_pull` | `src/overlays/ovl_08_thwomp_pull/14A810.c` | 1055 | 7 | 35 |  |
| `func_8008CBF0_main` | `src/8D7F0.c` | 25 | 8 | 8 | scheduling only, two add.s placed after the counter updates in retail (masked 8) |
| `func_80107778_crazy_cogs` | `src/overlays/ovl_05_crazy_cogs/131C10.c` | 80 | 8 | 12 | Creates the player object for the one player in group 0. |
| `func_8010A370_storyresult` | `src/overlays/storyresult/54F360.c` | 91 | 8 | 9 | Residue (masked 8): retail keeps a raw copy of slot and does not thread the slot >= 6 jump (as minigame func_800E905C_minigame). Rank (0-4) of a story record: s... |
| `func_80108F34_hyper_hydrants` | `src/overlays/ovl_0E_hyper_hydrants/17B3B0.c` | 193 | 8 | 11 | masked residue: retail selects the camera with a branch (li 1/0) where this C gets sltu, and schedules the model move later (logic checked) |
| `func_80109C90_swinging_with_sharks` | `src/overlays/ovl_3F_swinging_with_sharks/2E0D20.c` | 286 | 8 | 12 | scheduling: the 10.0f for end, path + i operand order, HmfModelData reloaded after the sindf products |
| `func_8005A968_main` | `src/window.c` | 496 | 8 | 14 | register allocation (masked 15): retail keeps (s16)w, (s16)h in s6/s5 from the HuMemFree call on and reuses them for func_8005B238_main; declaration order does ... |
| `func_801072D0_swing_n_swipe` | `src/overlays/ovl_40_swing_n_swipe/2E6BE0.c` | 846 | 8 | 18 | masked 8: retail loads HmfModelData before scaling the model index (both thief-distance tests); register choice |
| `func_8010FE0C_duel10` | `src/overlays/duel10/4461E0.c` | 2785 | 8 | 163 | board ec4: the tutorial script: the guide explains a duel turn by turn (44 messages 0x250D..0x2539; 0x2524 is func_8010FDC0_duel10's). board ec4: NON_MATCHING: ... |
| `func_8010ADA0_pump_pump_away` | `src/overlays/ovl_0D_pump_pump_away/16F670.c` | 44 | 9 | 19 |  |
| `func_8010E268_duel10` | `src/overlays/duel10/4461E0.c` | 57 | 9 | 14 | board ec2: the turn passes to the other player; both stand idle facing the camera. referent (masked 9, 52 vs 57): retail reads GwSystem.current_player_index as ... |
| `func_80105C4C_msetup` | `src/overlays/msetup/501C00.c` | 134 | 9 | 14 | D_8011AA48_msetup: retail stores it and reloads it (lh) before the >= 0 test; this keeps the register. |
| `func_80106D80_mstory1` | `src/overlays/mstory1/48C120.c` | 138 | 9 | 28 | register allocation; retail converts frames separately for the divide (masked 9) |
| `func_80106DB4_mstory5` | `src/overlays/mstory5/4CF350.c` | 138 | 9 | 28 | as func_80106B64_mstory5, but the second model follows in 3D |
| `func_8010700C_mstory4` | `src/overlays/mstory4/4C2BD0.c` | 138 | 9 | 28 | as func_80106DBC_mstory4, but the second model follows in 3D |
| `func_8010BB74_mpiq` | `src/overlays/ovl_21_mpiq/204F90.c` | 144 | 9 | 15 | Open the question window: "Qn" header, the question text and its name insert. |
| `func_8010B7A0_popgun_pickoff` | `src/overlays/ovl_32_popgun_pickoff/283060.c` | 178 | 9 | 21 | Sorts the visible billboards by view depth into the opaque (D_8010DE00) and translucent (D_8010DE68) lists. |
| `func_8010B8A8_crowd_cover` | `src/overlays/ovl_38_crowd_cover/2B5830.c` | 178 | 9 | 21 | Sorts the visible billboards by view depth into the opaque (D_8010DE00) and translucent (D_8010DE68) lists. |
| `func_8010D970_fowl_play` | `src/overlays/ovl_3A_fowl_play/2C5B50.c` | 182 | 9 | 21 | Sorts the visible, unhidden billboards near the camera by view depth into the opaque (D_8010F360) and translucent (D_8010F3C8) lists. |
| `func_8010961C_marios_puzzle_party` | `src/overlays/ovl_1F_marios_puzzle_party/1F3B90.c` | 194 | 9 | 10 | The special piece has landed between two columns: squash them until neither has a two-block piece left to squash, then clear matches; returns whether anything w... |
| `func_8010B164_fridged_bridges` | `src/overlays/ovl_24_fridged_bridges/216670.c` | 194 | 9 | 12 | The four hazards, one per bridge |
| `func_80119680_w02` | `src/overlays/w02/335610.c` | 215 | 9 | 19 | Masked 9 (216 vs 215): the two "scale = 0" stores (not live, too close to the centre) are a shared `sw zero` in retail and len is kept in a second register; the... |
| `func_8010CA6C_aces_high` | `src/overlays/ovl_17_aces_high/1C4280.c` | 222 | 9 | 17 | masked 14: retail sign-extends the first sprite coordinate after both truncations (here right after the first), computes the priority as (i - 0x7FFB) & 0xFFFF (... |
| `func_80107144_hey_batter_batter` | `src/overlays/ovl_3C_hey_batter_batter/2D3E70.c` | 258 | 9 | 14 | The batter: character model, bat and shadow, motions. masked 7: retail keeps the character in one register and copies it once; GCC 2.7.2 here re-zero-extends th... |
| `func_80105B8C_meschk` | `src/overlays/meschk/4F69F0.c` | 555 | 9 | 10 |  |
| `MB1Ev_TuruturuMain` | `src/overlays/ovl_48_ChillyWaters/31B9F0.c` | 581 | 9 | 12 | chilly B: NON_MATCHING: masked 9 (raw 12): retail reloads the spilled `slip` (lw t0,0x3C(sp)) before the first test, and fills the 0x47 beq's delay slot with `l... |
| `func_80109DE4_game_guys_sweet_surprise` | `src/overlays/ovl_45_game_guys_sweet_surprise/30F940.c` | 652 | 9 | 11 | The right character (as func_801092F0, mirrored) |
| `func_80109B9C_hand_line_sinker` | `src/overlays/ovl_01_hand_line_sinker/11A480.c` | 738 | 9 | 24 | Finish otherwise: the line goes slack, the fish still free jump out of the water and win. |
| `func_801090C4_mgmode` | `src/overlays/mgmode/46CC10.c` | 910 | 9 | 60 | register allocation only (s3/s4 and s6/s7 swap; retail spills the window id to the stack) |
| `func_80106D94_selmenu2` | `src/overlays/selmenu2/116320.c` | 1005 | 9 | 23 | selmenu func_80106DEC_selmenu (the same code). NON_MATCHING: register allocation only (the display loop's invariants i % 2, (i / 2) * 7 and the two i * 7), as i... |
| `func_80106DEC_selmenu` | `src/overlays/selmenu/552F50.c` | 1005 | 9 | 23 | register allocation only (the display loop's invariants i % 2, (i / 2) * 7 and the two i * 7, and the final cursor x/y); logic checked block by block against th... |
| `func_800F3A04_name_81` | `src/overlays/ovl_81_name/D5B20.c` | 65 | 10 | 23 | Retail calls func_800F8AEC with no prototype in scope (arg3 and attr go through as ints, with no s16 -> u16 conversion); with DFD60's prototype the C adds that ... |
| `func_8010E09C_msetup` | `src/overlays/msetup/506F20.c` | 102 | 10 | 13 | retail loads model[0] straight into a0 and copies it to s1 (one instruction fewer); otherwise the same |
| `func_801087C0_mgenter` | `src/overlays/mgenter/468AC0.c` | 110 | 10 | 10 | player groups for a 1-vs-3 (type 1) or 2-vs-2 (type 2) minigame |
| `func_8011A6E8_w05` | `src/overlays/w05/37FFB0.c` | 139 | 10 | 23 |  |
| `func_80106B30_mstory1` | `src/overlays/mstory1/48C120.c` | 147 | 10 | 30 | register allocation; retail converts frames separately for the divide (masked 10) |
| `func_80106B64_mstory5` | `src/overlays/mstory5/4CF350.c` | 147 | 10 | 30 | walks obj's model (and its shadow, kept on the ground) to `to` in `frames` frames, turning it to face the way first when `turn` is set |
| `func_80106DBC_mstory4` | `src/overlays/mstory4/4C2BD0.c` | 147 | 10 | 30 | walks obj's model (and its shadow, kept on the ground) to `to` in `frames` frames, turning it to face the way first when `turn` is set |
| `func_80106DE0_mstory3` | `src/overlays/mstory3/4B29E0.c` | 147 | 10 | 30 | register allocation; retail converts frames separately for the divide (masked 8, as mstory1's func_80106B30) |
| `func_80106E48_mstory2` | `src/overlays/mstory2/49BD40.c` | 147 | 10 | 30 | walks obj's model (and its shadow, kept on the ground) to `to` in `frames` frames, turning it to face the way first when `turn` is set |
| `func_8010C04C_option` | `src/overlays/option/5334D0.c` | 154 | 10 | 10 | Matches except that this C hoists the constant -1 (the A-press result test) out of the loop into s5. |
| `func_801077BC_mstory3` | `src/overlays/mstory3/4B29E0.c` | 157 | 10 | 45 | register allocation; retail converts frames separately for the divide and the loop (masked 10, as mstory1's func_80106D80) |
| `func_80107090_game_guys_lucky_7` | `src/overlays/ovl_43_game_guys_lucky_7/3010E0.c` | 159 | 10 | 10 | Lucky 7 result: rolls the win chance for the reached level (D_8010D774; reaching past D_8010D776 always wins), * shows the win/lose message and sets D_8010D77C ... |
| `func_80108590_mgenter` | `src/overlays/mgenter/468AC0.c` | 182 | 10 | 10 | the two cursor arrows: fade in or out with D_80109B22_mgenter, move on D_80109B20_mgenter |
| `func_8010EE7C_stardust_battle` | `src/overlays/ovl_41_stardust_battle/2ED2D0.c` | 195 | 10 | 11 | retail sign-extends the HuSprGrpCreate result (its declaration there returned int; sprite.h says s16), so mine skips one sll/sra and re-extends the group at two... |
| `func_800F76F8_name_81` | `src/overlays/ovl_81_name/DC4E0.c` | 211 | 10 | 27 |  |
| `func_8010D1B8_pump_pump_away` | `src/overlays/ovl_0D_pump_pump_away/16F670.c` | 218 | 10 | 14 |  |
| `func_8010F4E0_msetup` | `src/overlays/msetup/506F20.c` | 248 | 10 | 75 | retail calls Hu3DModelRotSet in both branches (cross-jumped, 0 args set per branch) and keeps lift/from in s0/s1 (masked 10); same logic |
| `opTitleSprMain` | `src/overlays/opening/523FD0.c` | 302 | 10 | 16 | Register allocation (masked 10): the first fade loop's clamp is copy-propagated and 1/60 is held in a GPR; the logo/press-start reads relocate against D_80114EB... |
| `func_80108678_river_raiders` | `src/overlays/ovl_09_river_raiders/1542E0.c` | 304 | 10 | 10 | Collision flags for one of the three team-1 rafts (work[1]): D_80110D98_river_raiders[raft][other] for the * other rafts, [3] the lane edge (1 left, 2 right of ... |
| `func_80107270_game_guys_lucky_7` | `src/overlays/ovl_43_game_guys_lucky_7/3010E0.c` | 341 | 10 | 31 | regalloc: retail keeps 'done' in s0 and copies it to s4 before the window loop (one move more); ops, branches, calls and fields equal |
| `func_80107140_baby_bowser_broadside` | `src/overlays/ovl_0C_baby_bowser_broadside/165010.c` | 362 | 10 | 11 | <func_80107140_baby_bowser_broadside> |
| `func_80106E14_dorrie_dip` | `src/overlays/ovl_3E_dorrie_dip/2DC4D0.c` | 401 | 10 | 10 | masked 10; retail loads the two 0x20A99 stack arguments after the table loads (scheduling) |
| `func_8010F44C_chancetime` | `src/overlays/chancetime/487F50.c` | 459 | 10 | 20 | matches with the header fix in e3A.header.patch (func_80060EA8_main takes an s32 window id); logic checked |
| `func_80111C30_duel03` | `src/overlays/duel03/3FE1F0.c` | 512 | 10 | 11 | duel b4: logic checked; masked 8: the turn if-chain, where retail keeps buf's address out of s0 and leaves a j/nop pair (509 vs 512 instructions) duel b4: bell ... |
| `func_80111DFC_duel01` | `src/overlays/duel01/3D8AC0.c` | 512 | 10 | 11 | duel b4: logic checked; masked 8: the turn if-chain, where retail keeps buf's address out of s0 and leaves a j/nop pair (509 vs 512 instructions) duel b4: bell ... |
| `func_80119290_w03` | `src/overlays/w03/34E840.c` | 1302 | 10 | 125 | masked-equal at 1302 instructions except the frame (retail reserves 8 more bytes of spill space, 0x80 vs 0x78) and the register allocation that follows from it. |
| `func_8010B140_crowd_cover` | `src/overlays/ovl_38_crowd_cover/2B5830.c` | 41 | 11 | 15 | H0: masked 11: retail copies id and sign-extends it twice, stores w/h unextended and tc as (s16)w << 6 kept as sll 16/sra 10; tried w/h directly (10) and s32 pa... |
| `func_8010D208_fowl_play` | `src/overlays/ovl_3A_fowl_play/2C5B50.c` | 41 | 11 | 15 | masked 11: retail never sign-extends w/h at entry (sll 16, sra 10 at the tc stores) and extends id twice; H0 tried s32 w/h with s16 locals, a K&R definition, an... |
| `func_8008D5D0_main` | `src/8E1D0.c` | 90 | 11 | 11 | guPerspectiveF with the scale folded into each element; fovy in degrees. perspNorm may be NULL. NON_MATCHING: prologue scheduling only; retail interleaves the r... |
| `func_8010D48C_pump_pump_away` | `src/overlays/ovl_0D_pump_pump_away/16F670.c` | 116 | 11 | 11 | masked 11: retail converts dist to double in each arm (bc1tl with the cvt in its delay slot); tried an f64 dist (masked 11, j-shaped) and dist = t->dist before ... |
| `func_8010B32C_messy_memory` | `src/overlays/ovl_1D_messy_memory/1E37C0.c` | 128 | 11 | 20 | A player's hand: its sprite group by character, placed on its board; player 3's also adds the hand drawer. |
| `func_80111580_opening` | `src/overlays/opening/523FD0.c` | 165 | 11 | 34 |  |
| `func_8003AE9C_main` | `src/gamemes.c` | 195 | 11 | 11 | The font sprite for character c, loaded on first use: upper case, lower case, kana and symbols each have a cache of sprite ids; flag bit 0 is the large font. ma... |
| `func_8010628C_pump_pump_away` | `src/overlays/ovl_0D_pump_pump_away/16F670.c` | 199 | 11 | 17 |  |
| `func_8010F0E8_stardust_battle` | `src/overlays/ovl_41_stardust_battle/2ED2D0.c` | 221 | 11 | 17 | scheduling and loop-invariant hoisting: retail hoists &D_80113ED8 into s3 for the digit loop and clears the loop counter before the mtc1; ops equal |
| `func_8010C9B4_filesel` | `src/overlays/filesel/516AE0.c` | 279 | 11 | 29 | struct base register choice (the stores and the loop index from D_80114490/D_8011447C in retail) and s-register order (masked 22) |
| `func_8010F168_filesel` | `src/overlays/filesel/516AE0.c` | 346 | 11 | 21 | the window width is kept in a register for the first window's stack argument, float register choice (masked ~20) |
| `func_801060E8_popgun_pickoff` | `src/overlays/ovl_32_popgun_pickoff/283060.c` | 614 | 11 | 14 |  |
| `func_8010FB88_staff` | `src/overlays/staff/542220.c` | 669 | 11 | 12 | masked 17 (670 vs 669): four extra nops after calls, the colour index (retail re-masks it with 0xFF and addresses splat's split labels D_8010D6C1/D_8010D6C2; th... |
| `func_8010A7EC_storyresult` | `src/overlays/storyresult/54F360.c` | 88 | 12 | 31 | H0: masked 12: register allocation (kind in t0, GwStory.unk1 copied a2->a3); tried s32 chr (16) and no local (23). |
| `func_801084B4_treadmill_grill` | `src/overlays/ovl_15_treadmill_grill/1B4F10.c` | 91 | 12 | 25 | Player objects 0..3. Masked 12 each: retail loads the two D_800A178C_main arguments before it stores the stack arguments; this C loads them after (no other diff... |
| `func_80105B38_mchar` | `src/overlays/mchar/3D3C80.c` | 92 | 12 | 38 |  |
| `func_80105B7C_mchar2` | `src/overlays/mchar2/3D5C30.c` | 92 | 12 | 38 |  |
| `func_801085D8_treadmill_grill` | `src/overlays/ovl_15_treadmill_grill/1B4F10.c` | 104 | 12 | 25 |  |
| `func_80108730_treadmill_grill` | `src/overlays/ovl_15_treadmill_grill/1B4F10.c` | 104 | 12 | 25 |  |
| `func_80108888_treadmill_grill` | `src/overlays/ovl_15_treadmill_grill/1B4F10.c` | 104 | 12 | 25 |  |
| `func_8010811C_pump_pump_away` | `src/overlays/ovl_0D_pump_pump_away/16F670.c` | 111 | 12 | 18 |  |
| `func_80108E74_pump_pump_away` | `src/overlays/ovl_0D_pump_pump_away/16F670.c` | 117 | 12 | 24 |  |
| `func_8011124C_opening` | `src/overlays/opening/523FD0.c` | 131 | 12 | 19 |  |
| `func_80106CC0_bobbing_bow_loons` | `src/overlays/ovl_3D_bobbing_bow_loons/2D8370.c` | 181 | 12 | 58 | retail recomputes &work[i] after the rand8 calls; this keeps it in a saved register (masked 12) |
| `func_80108F74_msetup` | `src/overlays/msetup/501C00.c` | 230 | 12 | 18 | Story Mode: the board, turns and four players from GwStory (chapter unk0, character unk1, COM level unk2); the other two or three characters are shuffled. |
| `func_80105D3C_picking_panic` | `src/overlays/ovl_0F_picking_panic/181950.c` | 243 | 12 | 39 |  |
| `m255_ExecCameraIntro` | `src/overlays/ovl_37_silly_screws/main.c` | 260 | 12 | 37 | TODO: only works with -Wa,--vr4300mul-off. |
| `func_8010D998_staff` | `src/overlays/staff/542220.c` | 357 | 12 | 21 | masked 12 (356 vs 357): retail keeps sp+0x10 in a register to index the sprite ids (one addiu more); the rest is register allocation. Logic checked. |
| `func_80106398_swinging_with_sharks` | `src/overlays/ovl_3F_swinging_with_sharks/2E0D20.c` | 388 | 12 | 16 | float register allocation in the fall-time loop (0.0f and 4.0f swap f0/f6) |
| `func_801078CC_selmenu2` | `src/overlays/selmenu2/116320.c` | 431 | 12 | 20 | selmenu func_80107924_selmenu (the same code). NON_MATCHING: as in selmenu, retail does not fold textY (6) into the sparkle y (+ 8); register allocation of the ... |
| `func_80107924_selmenu` | `src/overlays/selmenu/552F50.c` | 431 | 12 | 20 | retail does not fold textY (6) into the sparkle y (+ 8); register allocation of the two offsets. |
| `func_80109BD4_puddle_paddle` | `src/overlays/ovl_11_puddle_paddle/191240.c` | 431 | 12 | 24 | masked 36 (count 434 vs 431): splash flag tests and the 2x offset differ in register use and scheduling; logic checked against the asm |
| `func_80108CCC_awful_tower` | `src/overlays/ovl_25_awful_tower/21E010.c` | 37 | 13 | 17 | Player 0 object setup. |
| `func_80108D3C_awful_tower` | `src/overlays/ovl_25_awful_tower/21E010.c` | 37 | 13 | 17 | Player 1 object setup. |
| `func_80108DAC_awful_tower` | `src/overlays/ovl_25_awful_tower/21E010.c` | 37 | 13 | 17 | Player 2 object setup. |
| `func_80108E1C_awful_tower` | `src/overlays/ovl_25_awful_tower/21E010.c` | 37 | 13 | 17 | Player 3 object setup. |
| `func_80118328_duel01` | `src/overlays/duel01/3D8AC0.c` | 65 | 13 | 22 | control flow (66 vs 65, masked 13): retail keeps cur->nidx in a1 from the opening compare for the first rev&1 arm; ours reloads it (tried early returns, nested ... |
| `func_801063D4_slapdown` | `src/overlays/ovl_2E_slapdown/264B80.c` | 76 | 13 | 29 | Moves (x0, z0) toward (x1, z1): the longer axis at full speed, the other in proportion. |
| `func_8010B920_swing_n_swipe` | `src/overlays/ovl_40_swing_n_swipe/2E6BE0.c` | 79 | 13 | 21 | retail keeps an unused 3 in s1 across the loop (a dead local?) and so allocates the floats differently H0: loading pos.x/pos.z into locals before the subtractio... |
| `func_801075AC_fridged_bridges` | `src/overlays/ovl_24_fridged_bridges/216670.c` | 111 | 13 | 26 |  |
| `func_8010A674_modesel` | `src/overlays/modesel/4F7E90.c` | 126 | 13 | 32 | Model `no` bobs at its position while model 10 turns towards the camera, 2 degrees a frame. |
| `func_80108EE8_crazy_cogs` | `src/overlays/ovl_05_crazy_cogs/131C10.c` | 127 | 13 | 42 | Creates the three team players' framework objects. |
| `func_800ECF1C_name_81` | `src/overlays/ovl_81_name/D3450.c` | 145 | 13 | 40 | f20/f22/f24 allocation (the 0.0f constant) and the shared tail call offsets of the front and back partners from the player |
| `osCreatePiManager` | `src/2.0L/io/pimgr.c` | 166 | 13 | 69 | Matches except register allocation (the piEventQueue/piThread/pri registers come out in a different order). |
| `func_80033694_main` | `src/32160.c` | 185 | 13 | 25 | register allocation and scheduling of the animation-slot lookup (masked 25), as in MP1/MP2; testing unk09 directly or a u8 slot does not fix it |
| `func_801083A4_storyresult` | `src/overlays/storyresult/54F360.c` | 186 | 13 | 43 | Residue (masked ~10): retail reloads D_800CDA7C_main for each button test and sets the first bit with andi/sltu (this: srl/andi on one load); loop counters swap... |
| `func_80108F44_hand_line_sinker` | `src/overlays/ovl_01_hand_line_sinker/11A480.c` | 231 | 13 | 35 | Intro: a fish turns toward the middle and swims in until it is near the centre or bumps a fish that has arrived. |
| `func_8011AD8C_mstory2` | `src/overlays/mstory2/4B0E80.c` | 243 | 13 | 21 | choice 0: both fly off NON_MATCHING: retail does not hoist the 500.0f of the rise loop's exit test out of the loop (one instruction more); the rest is the same |
| `func_80109E2C_water_whirled` | `src/overlays/ovl_23_water_whirled/211AB0.c` | 254 | 13 | 13 | Masked 37 (two instructions short): retail recomputes player * 4 before each of the two stores after the crossing test; the rest differs only by that shift. Lap... |
| `func_801075B0_fowl_play` | `src/overlays/ovl_3A_fowl_play/2C5B50.c` | 287 | 13 | 15 | two instructions long: retail moves dist to $f24 before angle to $f20 and has no nop after each sindf/cosdf call; the rest matches Bounces a move of dist along ... |
| `func_80106800_messy_memory` | `src/overlays/ovl_1D_messy_memory/1E37C0.c` | 296 | 13 | 28 | Draws the players' hand cursors (D_80111700[0..3]): open or holding (D_80111640), dimmed while blocked (D_80115D72). |
| `func_80107400_marios_puzzle_party` | `src/overlays/ovl_1F_marios_puzzle_party/1F3B90.c` | 331 | 13 | 46 | Flood fill: record (col, row) in the match list, then recurse into same-coloured neighbours. |
| `func_80108820_mgresultduel` | `src/overlays/mgresultduel/4F01F0.c` | 372 | 13 | 21 | duelres A: Masked 12: retail keeps (j >= 2) & (rung ^ 1) as an and, and orders the sin product before pos.y. The host flies in along the path, lands, hops and r... |
| `func_801079B4_mgenter` | `src/overlays/mgenter/468AC0.c` | 374 | 13 | 15 | the A/B tests: retail loads the button word once (lhu and lh), this reloads it for B (masked 15) minigame 0x1E: the instruction card, then a target number (100.... |
| `func_80114588_mstory2` | `src/overlays/mstory2/4A7540.c` | 414 | 13 | 26 | register allocation: retail keeps a second copy of the chr == 5 flag (s0 and s3), masked 13 |
| `func_80106968_log_jam` | `src/overlays/ovl_13_log_jam/1A3D80.c` | 458 | 13 | 34 | Differs: the character-table loads for func_800E1BA8_minigame and the voice pointer take other registers/slots. |
| `func_80111DCC_duel05` | `src/overlays/duel05/426450.c` | 512 | 13 | 13 | duel b4: logic checked; masked 8: the turn if-chain, where retail keeps buf's address out of s0 and leaves a j/nop pair (509 vs 512 instructions) duel b4: bell ... |
| `func_80111FC4_duel06` | `src/overlays/duel06/436E50.c` | 512 | 13 | 13 | duel b4: logic checked; masked 8: the turn if-chain, where retail keeps buf's address out of s0 and leaves a j/nop pair (509 vs 512 instructions) duel b4: bell ... |
| `func_8010B574_mgmode` | `src/overlays/mgmode/46CC10.c` | 636 | 13 | 52 | float regalloc (rx and speed swap f22/f24); retail also keeps &Center in s0 in the 0x800/0x400 branches |
| `func_80107FF4_thwomp_pull` | `src/overlays/ovl_08_thwomp_pull/14A810.c` | 702 | 13 | 20 |  |
| `func_8010CADC_rockin_raceway` | `src/overlays/ovl_2C_rockin_raceway/251FF0.c` | 44 | 14 | 24 |  |
| `func_80105BB4_pipe_cleaners` | `src/overlays/ovl_27_pipe_cleaners/22E100.c` | 53 | 14 | 27 |  |
| `func_80109A44_crazy_cogs` | `src/overlays/ovl_05_crazy_cogs/131C10.c` | 75 | 14 | 14 | Whether a hazard has left its area (1) or is still inside it (0). |
| `func_80107A18_snowball_summit` | `src/overlays/ovl_28_snowball_summit/232A10.c` | 83 | 14 | 23 | Turns obj toward the stick heading (stick.z) by at most rate degrees (only in motions 0, 1, 3 and 4). retail shares rate * dir + rot between the < 0 test and it... |
| `func_80110D90_rockin_raceway` | `src/overlays/ovl_2C_rockin_raceway/251FF0.c` | 98 | 14 | 23 | retail hoists the 40.0 double into f22 before the loop (frame 8 bytes larger); otherwise identical Shows the twelve digit models (frames 0-9, clamped). |
| `func_801075D4_slot_synch` | `src/overlays/ovl_14_slot_synch/1AC970.c` | 144 | 14 | 18 |  |
| `func_801134C0_mgmode` | `src/overlays/mgmode/479470.c` | 159 | 14 | 18 | Draws the eight rounds' minigame categories: no category twice in a row, each at most D_801195C4[c] times, first and last different; after 100 failed draws take... |
| `func_8010A838_cosmic_coaster` | `src/overlays/ovl_10_cosmic_coaster/18ABD0.c` | 241 | 14 | 15 | Track object type 4 (glowing star): light the nearby objects of its side, vanish when hit or passed. |
| `func_80107710_mgresultduel` | `src/overlays/mgresultduel/4F01F0.c` | 327 | 14 | 33 | duelres A: Masked 18: retail rematerialises &D_80108F30_mgresultduel after each call; this keeps it in a saved register. |
| `func_801074A0_mgresultdealer` | `src/overlays/mgresultdealer/4EDCB0.c` | 331 | 14 | 33 | masked 34, 7 short: retail rematerialises &D_80109A70_mgresultdealer after each call (the same residue as mgresultduel func_80107710) the coins' process: 40 coi... |
| `func_80119234_mstory2` | `src/overlays/mstory2/4AC200.c` | 401 | 14 | 25 | actor 1: the partner (character 2 when the player is 1, else 1) NON_MATCHING: register allocation: retail keeps the character test and the table index in two re... |
| `func_80109AD0_curtain_call` | `src/overlays/ovl_22_curtain_call/20BFA0.c` | 1016 | 14 | 42 | One curtain round: deal the panels, shuffle, the host walks on, countdown, reveal, next round. |
| `func_800E905C_minigame` | `src/overlays/minigame/BA4B0.c` | 80 | 15 | 16 | retail keeps a raw copy of slot and does not thread the slot >= 6 jump (one extra instruction, masked 15) |
| `func_8010E3A4_modesel` | `src/overlays/modesel/4F7E90.c` | 100 | 15 | 20 | masked 15: retail loads 1.0f before the mul.s (H0 tried 1.0f + x, scale = 1.0f; scale += x) |
| `func_801100F0_pump_pump_away` | `src/overlays/ovl_0D_pump_pump_away/16F670.c` | 112 | 15 | 28 | masked 15: the loop's sum and the two zero stores take other registers/bases (retail: beqzl with t1's store in the slot); chained and D_80111978_pump_pump_away[... |
| `func_80117480_duel01` | `src/overlays/duel01/3D8AC0.c` | 123 | 15 | 19 | duel b5: masked 13 (retail reloads the table entry after the equality test) |
| `func_80107AB8_crazy_cogs` | `src/overlays/ovl_05_crazy_cogs/131C10.c` | 134 | 15 | 25 | Creates the three team players (group != 0), each at a random free slot. |
| `func_8010A6D0_hand_line_sinker` | `src/overlays/ovl_01_hand_line_sinker/11A480.c` | 162 | 15 | 66 | Starts a splash of a type at pos (relative to obj when it is not NULL). |
| `guLookAtF` | `src/88E10.c` | 168 | 15 | 16 | guLookAtF: Hudson's copy, from MP2 src/B24A0.c func_800B1960_B2560 (MP1 src/9CE40.c HuGuLookAtF, NON_MATCHING in both). Retail inlines HuVecNormalize (src/libhm... |
| `func_8010EAA0_marios_puzzle_party` | `src/overlays/ovl_1F_marios_puzzle_party/1F3B90.c` | 184 | 15 | 17 | Game clock: 5400 frames, counted down while player 0's game runs. |
| `func_80107824_mstory2` | `src/overlays/mstory2/49BD40.c` | 227 | 15 | 26 | the frame count is converted once and kept (retail converts it again for the first loop test), as func_80106E48_mstory2: register/scheduling residue only |
| `func_80107A18_mstory3` | `src/overlays/mstory3/4B29E0.c` | 227 | 15 | 26 | retail converts frames again for the loop test instead of reusing the divide's (masked 15: that, then shifted branches) |
| `func_801074E8_mstory5` | `src/overlays/mstory5/4CF350.c` | 228 | 15 | 26 | masked 15: retail converts frames again for the loop test (its f20 holds the divisor, then t) |
| `func_8010B154_mstory3` | `src/overlays/mstory3/4B29E0.c` | 398 | 15 | 15 | retail branches on i for the model file (bnez with the 0x300A0 load in the delay slot); KMC GCC turns every form tried into a negu/and/or select (masked 14, sam... |
| `func_8010F7D0_duel03` | `src/overlays/duel03/3FE1F0.c` | 553 | 15 | 42 | board db2: func_8010F99C_duel01's twin (same instructions), same residue: register allocation (the -1, walk target and partner/bell registers) and one branch-li... |
| `func_8010F96C_duel05` | `src/overlays/duel05/426450.c` | 553 | 15 | 42 |  |
| `func_8010F99C_duel01` | `src/overlays/duel01/3D8AC0.c` | 553 | 15 | 42 | register allocation (the -1, walk target and partner/bell registers) and one branch-likely (masked 14) |
| `func_8010F9DC_duel02` | `src/overlays/duel02/3EC590.c` | 553 | 15 | 42 |  |
| `func_8010FA58_duel04` | `src/overlays/duel04/410910.c` | 553 | 15 | 42 | board ea1: duel05 twin, duel04 constants checked against retail (immediates); masked 14 (552 vs 553) here; logic as duel05 |
| `func_8010FB64_duel06` | `src/overlays/duel06/436E50.c` | 553 | 15 | 42 |  |
| `func_8010DAB8_mgmode` | `src/overlays/mgmode/473130.c` | 588 | 15 | 85 | masked 0 except register allocation and a frame 8 bytes smaller than retail's. |
| `func_8010CF4C_marios_puzzle_party` | `src/overlays/ovl_1F_marios_puzzle_party/1F3B90.c` | 51 | 16 | 22 | masked 16: retail keeps player * 4 and the array base in s1/s2 and re-adds them each pass (tried a pointer, do-while, while/break) |
| `func_8010D4DC_msetup` | `src/overlays/msetup/506F20.c` | 75 | 16 | 26 | register allocation: retail copies arg0 to t3 and loads pad into a0 (masked 16, same blocks) |
| `func_80109E08_spotlight_swim` | `src/overlays/ovl_03_spotlight_swim/1263E0.c` | 102 | 16 | 25 | regalloc: GCC hoists the case constant 1 into s4 (+1 saved reg, the extra sw/lw). That frees the * delay slot of the group test, so retail's `beqz v0,.L80109F28... |
| `func_80108CFC_pump_pump_away` | `src/overlays/ovl_0D_pump_pump_away/16F670.c` | 109 | 16 | 59 |  |
| `func_80111740_mstory4` | `src/overlays/mstory4/4C8050.c` | 116 | 16 | 31 | retail keeps the three colour-table bytes' addresses in registers across the loop (masked 16) |
| `func_8010ABD4_hand_line_sinker` | `src/overlays/ovl_01_hand_line_sinker/11A480.c` | 123 | 16 | 21 | Arc length of the parabola-like curve through the two ends for parameter a, minus the line length. |
| `func_80109F7C_parasol_plummet` | `src/overlays/ovl_1C_parasol_plummet/1DE610.c` | 124 | 16 | 39 | retail rematerialises the 0.0f offsets at each use where this hoists them into f24 (masked 19, one instruction long). Nearest player (0x10 / index) within 100, ... |
| `func_8001D638_main` | `src/hmfman.c` | 155 | 16 | 21 | MP1 func_80026C6C (src/24740.c): retail keeps a second copy of arg4 (s2) for the switch, as MP1 and MP2 do (register allocation); NON_MATCHING in both |
| `func_801094C4_puddle_paddle` | `src/overlays/ovl_11_puddle_paddle/191240.c` | 155 | 16 | 24 | A player's paddling: each press adds power, which decays; the stick steers (flags 2 right, 4 left). NON_MATCHING: retail reads the stick with lbu and sign-exten... |
| `func_801096A8_cosmic_coaster` | `src/overlays/ovl_10_cosmic_coaster/18ABD0.c` | 157 | 16 | 16 | One shooting star: fly, point the trail along the motion, vanish off its half of the screen. |
| `func_80038D78_main` | `src/gamemes.c` | 363 | 16 | 77 | "START" letters spinning in: register allocation (masked 16: i and chr swap registers; the flip loop keeps i + 1 in s0) |
| `func_80106FC0_ice_rink_risk` | `src/overlays/ovl_19_ice_rink_risk/1D1C40.c` | 450 | 16 | 19 | Player hook 0: save the pad, then steer a CPU player away from the nearest puck and the edge. register allocation residue (masked 16): GCC adds a nop after each... |
| `func_80106254_sldebug` | `src/overlays/sldebug/3D76C0.c` | 477 | 16 | 55 | the debug camera: pad 1 C up/down zoom, the stick turns, D-pad moves the centre (Z: faster), L resets; pad 1 START toggles the text |
| `func_8010B23C_swing_n_swipe` | `src/overlays/ovl_40_swing_n_swipe/2E6BE0.c` | 511 | 16 | 49 | masked 16: register allocation (retail computes each puff's address late and numbers the loop registers differently) |
| `func_80109020_swinging_with_sharks` | `src/overlays/ovl_3F_swinging_with_sharks/2E0D20.c` | 530 | 16 | 55 | sldebug's func_80106254_sldebug plus field-of-view keys; the same residue as that twin: float register allocation (rx and speed swap f22/f24) and retail loads &... |
| `func_8010CE5C_stardust_battle` | `src/overlays/ovl_41_stardust_battle/2ED2D0.c` | 882 | 16 | 38 | loop-invariant hoisting only: retail keeps 100.0 (the random-step scale) in s6/s7 and reloads 0.01 from the pool at each use; mine keeps 0.01 in s6/s7 and reloa... |
| `func_80110554_mgmode` | `src/overlays/mgmode/473130.c` | 1105 | 16 | 164 | register allocation only (the loop counters i and j take each other's * registers) and a frame 8 bytes smaller than retail's. |
| `func_80115850_duel01` | `src/overlays/duel01/3D8AC0.c` | 124 | 17 | 19 | duel b5: masked 17 (retail reloads cidx and the table entry after the equality test) |
| `func_8010914C_etch_n_catch` | `src/overlays/ovl_12_etch_n_catch/19CEF0.c` | 146 | 17 | 21 | Sets cell (x, y) to `v`, its 4 neighbours to v * 2 and its diagonal neighbours to v * 4, unless already set. |
| `func_8010A328_spotlight_swim` | `src/overlays/ovl_03_spotlight_swim/1263E0.c` | 259 | 17 | 60 | retail keeps work[1] (lb) and a copy in two saved registers (frame 0x30); mine loads lbu and extends at the use Chaser setup for the end sequence. |
| `func_80107234_mgresultboard` | `src/overlays/mgresultboard/4E6DC0.c` | 328 | 17 | 85 | Masked 17: retail reloads sc[] from the stack and recomputes j * 12 before the tie-break test. |
| `func_80107210_motor_rooter` | `src/overlays/ovl_36_motor_rooter/main.c` | 343 | 17 | 96 | <func_80107210_motor_rooter> |
| `func_80106BAC_motor_rooter` | `src/overlays/ovl_36_motor_rooter/main.c` | 389 | 17 | 36 | <func_80106BAC_motor_rooter> |
| `func_801127A8_duel10` | `src/overlays/duel10/4461E0.c` | 553 | 17 | 44 | board ec3: duel01/duel05 twin; register allocation (the -1, walk target and partner/bell registers) and one branch-likely (masked 15) |
| `func_8005E348_main` | `src/window.c` | 742 | 17 | 27 | register allocation (one instruction short, the rest register renaming; MP1 func_8006FE4C and MP2 have the same residue): the new entry's index reuses the compa... |
| `func_8010A670_spotlight_swim` | `src/overlays/ovl_03_spotlight_swim/1263E0.c` | 88 | 18 | 33 | H0: masked 18: retail does not hoist &D_8010D798_spotlight_swim out of the loop and copies omAddObj's result to v1; a chained ent->obj store did not help. |
| `func_8010D290_marios_puzzle_party` | `src/overlays/ovl_1F_marios_puzzle_party/1F3B90.c` | 131 | 18 | 62 | Break the block at (col, row) into four debris pieces. |
| `func_80106D54_crazy_cogs` | `src/overlays/ovl_05_crazy_cogs/131C10.c` | 164 | 18 | 27 | CPU: turn the plan step's cog until one of entities 5..7 lines up with it. |
| `func_801089B8_motor_rooter` | `src/overlays/ovl_36_motor_rooter/main.c` | 168 | 18 | 24 | <func_801089B8_motor_rooter> |
| `func_80108E5C_boulder_ball` | `src/overlays/ovl_04_boulder_ball/12DD30.c` | 416 | 18 | 18 | masked: one instruction; retail schedules D_80109744[idx]'s index shift into the mfc1 delay slot of the pan argument, GCC here computes it before (an extra nop ... |
| `func_8010A740_bounce_n_trounce` | `src/overlays/ovl_18_bounce_n_trounce/1CC730.c` | 105 | 19 | 26 | the loop increment and the tile height load are scheduled differently, frame 8 bytes larger; logic checked The spin effect's particles (the vertex-scatter model... |
| `func_80108708_pipe_cleaners` | `src/overlays/ovl_27_pipe_cleaners/22E100.c` | 115 | 19 | 41 | Raises the pipes the schedule names, every 15 frames. |
| `func_80109804_bounce_n_trounce` | `src/overlays/ovl_18_bounce_n_trounce/1CC730.c` | 140 | 19 | 101 | CPU: when the target stands two tiles away in a line, first walks to the tile between (if it is not shaking), then goes to state next. |
| `func_80116168_duel04` | `src/overlays/duel04/410910.c` | 179 | 19 | 25 | board ea2: logic checked against the asm case by case; masked 19: the cur/rev tails (retail computes the result into $v0 around a branch-likely; this C keeps it... |
| `func_8010AE98_fridged_bridges` | `src/overlays/ovl_24_fridged_bridges/216670.c` | 221 | 19 | 33 | Cameras run back along the bridge paths and zoom out; 1 when all are done |
| `func_80109DBC_mgmode` | `src/overlays/mgmode/46CC10.c` | 263 | 19 | 47 | float register allocation: retail keeps the end point in f22/s4/s3 and the start point in f30/f28/f26 |
| `func_80106708_the_beat_goes_on` | `src/overlays/ovl_20_the_beat_goes_on/1FE4D0.c` | 401 | 19 | 22 | masked 37: the sprite id ternaries convert to s16 in each branch (retail: once at the join) |
| `func_8010C8E0_duelresult` | `src/overlays/duelresult/45A700.c` | 669 | 19 | 20 | duel r2: NON_MATCHING, masked 17 (670 vs 669): four extra nops after calls, the colour index (retail re-masks it with 0xFF and addresses splat's split labels D_... |
| `func_8010DA30_boardresult` | `src/overlays/boardresult/3BFA00.c` | 669 | 19 | 20 | event e8: NON_MATCHING, masked 17 (670 vs 669): four extra nops after calls, the colour index (retail re-masks it with 0xFF and addresses splat's split labels D... |
| `func_8010882C_bowser_toss` | `src/overlays/ovl_34_bowser_toss/291020.c` | 1593 | 19 | 19 | The two thrown Bowsers: held, spun, flying, landing, sliding to rest. NON_MATCHING: case 8 schedules the bw->unk30.x load before the 100.0f constant (retail aft... |
| `func_8010EB58_duel05` | `src/overlays/duel05/426450.c` | 72 | 20 | 44 | referent (masked 20-23): retail reads GwSystem.current_player_index as a scalar global; with a scalar extern only register allocation remains (masked 17); with ... |
| `func_8010EB88_duel01` | `src/overlays/duel01/3D8AC0.c` | 72 | 20 | 44 | referent (masked 20-23): retail reads GwSystem.current_player_index as a scalar global; with a scalar extern only register allocation remains (masked 17); with ... |
| `func_80107044_swinging_with_sharks` | `src/overlays/ovl_3F_swinging_with_sharks/2E0D20.c` | 112 | 20 | 39 | register allocation: retail keeps the player model in s2 until the Hu3DModelPosSet call (one more saved register) |
| `func_80107F58_ice_rink_risk` | `src/overlays/ovl_19_ice_rink_risk/1D1C40.c` | 134 | 20 | 54 | Pucks hitting each other bounce off. register allocation (masked 20): retail hoists 0.0f into f24 and keeps 1000.0f in a GPR (one more saved register), as in mi... |
| `func_80115B3C_duel04` | `src/overlays/duel04/410910.c` | 185 | 20 | 26 | board ea2: logic checked against the asm case by case; masked 20: the cur/rev tails (retail computes the result into $v0 around a branch-likely; this C keeps it... |
| `func_800E3A0C_name_81` | `src/overlays/ovl_81_name/CA640.c` | 201 | 20 | 29 | masked 2: retail loads data->idx after D_80102CCC (scheduling) and has 8 more bytes of frame; logic checked |
| `func_8010B38C_hyper_hydrants` | `src/overlays/ovl_0E_hyper_hydrants/17B3B0.c` | 211 | 20 | 29 | masked residue: retail re-reads the mask height for the loop bound into another register and hoists the 255/2^31 constants differently (registers/scheduling; lo... |
| `func_80107740_staff` | `src/overlays/staff/542220.c` | 241 | 20 | 44 | Register allocation (masked 20): retail keeps count in s3 and spills the vel pointer to the stack; this spills count instead. Logic checked against the asm. |
| `func_8003D4DC_main` | `src/gamemes.c` | 254 | 20 | 42 | register allocation and loop shape in the i + 1 loops (masked 20), as func_8003CE20_main |
| `func_8010E8F4_duel10` | `src/overlays/duel10/4461E0.c` | 256 | 20 | 25 | board ec2: the space the current player landed on: an event space, or a character space (11..18) that pays the owner, or with a coin partner prize takes coins f... |
| `func_80037878_main` | `src/gamemes.c` | 271 | 20 | 33 | "START" bouncing in: register allocation in the i + 1 loops (masked 20), as MP2 func_80069C20_6A820; logic follows MP3 |
| `func_80106508_motor_rooter` | `src/overlays/ovl_36_motor_rooter/main.c` | 314 | 20 | 54 | <func_80106508_motor_rooter> |
| `func_8010A08C_cheep_cheep_chase` | `src/overlays/ovl_26_cheep_cheep_chase/225740.c` | 374 | 20 | 27 | Register allocation (ctx/object/player in other saved registers). |
| `func_80037C44_main` | `src/gamemes.c` | 396 | 20 | 38 | "START" dropping in: register allocation in the i + 1 loop (masked 20), as MP2 func_8006A018_6AC18; logic follows MP3 |
| `func_800329B4_main` | `src/32160.c` | 401 | 20 | 25 | register allocation: retail keeps nframes on the stack and data in s4 (masked ~297 words from the first frame on, 2 instructions short), as in MP2; u16 nframes ... |
| `func_801094D8_chip_shot_challenge` | `src/overlays/ovl_1B_chip_shot_challenge/1D9550.c` | 473 | 20 | 20 | the ball: roll, bounce, drop into the hole, then show where it stopped three instructions short: after a bounce retail tests a constant (li v0,1; beqz v0) befor... |
| `func_80107920_storyresult` | `src/overlays/storyresult/54F360.c` | 662 | 20 | 71 | Residue (masked ~20): scheduling only (the arrow sindf product, message ids loaded before the sign extension, delay slots). Event 1 process: shows the story rec... |
| `func_8010ABA0_river_raiders` | `src/overlays/ovl_09_river_raiders/1542E0.c` | 87 | 21 | 47 | Creates the team-1 rafts (players in group 1). |
| `func_8000B880_main` | `src/esprite.c` | 94 | 21 | 41 | Scales each RGBA5551 entry of a sprite's palette by (r, g, b); alpha is kept. From MP2 src/1AE60.c func_8001A340_1AF40, NON_MATCHING there: retail reloads *pal ... |
| `func_8010AA78_snowball_summit` | `src/overlays/ovl_28_snowball_summit/232A10.c` | 169 | 21 | 27 | A human's controls. scheduling/CSE: retail reloads obj->work[0] for the first pad lookup and fills delay slots differently; same ops |
| `func_80119A30_duel04` | `src/overlays/duel04/410910.c` | 184 | 21 | 24 | board ea3: masked 24 (185 vs 184): retail keeps the third tree's count as a branch (count = 2 in the call's delay slot, bnezl count = 3, blez before the loop); ... |
| `func_8010E6B8_pump_pump_away` | `src/overlays/ovl_0D_pump_pump_away/16F670.c` | 200 | 21 | 21 |  |
| `func_80037574_main` | `src/gamemes.c` | 221 | 21 | 43 | "START": register allocation in the i + 1 loops (masked 21), as MP2 func_800698F0_6A4F0; logic follows MP3 |
| `func_8003D134_main` | `src/gamemes.c` | 251 | 21 | 43 | register allocation and loop shape in the i + 1 loops (masked 21), as func_8003CE20_main |
| `func_8003D890_main` | `src/gamemes.c` | 271 | 21 | 56 | register allocation and loop shape in the i + 1 loops (masked 25), as func_8003CE20_main |
| `func_80106ABC_hide_and_sneak` | `src/overlays/ovl_06_hide_and_sneak/137C00.c` | 176 | 22 | 29 |  |
| `func_80106428_mchar2` | `src/overlays/mchar2/3D5C30.c` | 177 | 22 | 36 | loads characters 6 and 7's two models and their motion 0 (set is unused) |
| `func_800F08BC_name_81` | `src/overlays/ovl_81_name/D5B20.c` | 291 | 22 | 66 | Register allocation only: the C keeps the constant 20 in a saved register across the second and third total_turns checks (retail rematerialises it), adding s3 t... |
| `func_8003A3C4_main` | `src/gamemes.c` | 300 | 22 | 24 | A sprite group with one member per character of str, as MP2 func_8006A67C_6B27C with an x scale (sy is unused); flag bit 0 picks the large font, x0 == -1 centre... |
| `func_8010869C_cosmic_coaster` | `src/overlays/ovl_10_cosmic_coaster/18ABD0.c` | 574 | 22 | 43 | Opening: fade in, then move both cameras through the two keys, start the music. |
| `func_80106D10_cosmic_coaster` | `src/overlays/ovl_10_cosmic_coaster/18ABD0.c` | 849 | 22 | 24 | Car per frame while racing: steer the riders, speed up or brake, hit or collect, sounds. |
| `func_8010EBC8_duel02` | `src/overlays/duel02/3EC590.c` | 72 | 23 | 44 | referent (masked 20-23): retail reads GwSystem.current_player_index as a scalar global; with a scalar extern only register allocation remains (masked 17); with ... |
| `func_8010AF70_pump_pump_away` | `src/overlays/ovl_0D_pump_pump_away/16F670.c` | 207 | 23 | 27 |  |
| `func_8010E0F4_pump_pump_away` | `src/overlays/ovl_0D_pump_pump_away/16F670.c` | 239 | 23 | 23 |  |
| `func_800E989C_minigame` | `src/overlays/minigame/BA4B0.c` | 273 | 23 | 49 | register allocation: retail spills the player count, this spills the overlay status |
| `func_80108EB8_filesel` | `src/overlays/filesel/516AE0.c` | 552 | 23 | 32 | 255 - alpha is folded to ~alpha (retail keeps 255 in a register), shifting s3/s4 (masked 23); logic checked |
| `func_8010D2E4_motor_rooter` | `src/overlays/ovl_36_motor_rooter/main.c` | 670 | 23 | 35 | <func_8010D2E4_motor_rooter> |
| `func_8010EDF0_duel03` | `src/overlays/duel03/3FE1F0.c` | 97 | 24 | 50 | board db2: func_8010EFBC_duel01's twin (same instructions), same residue: retail keeps 64.0f and 3.0f out of registers (loop hoisting), frame 8 bytes larger (ma... |
| `func_8010EF8C_duel05` | `src/overlays/duel05/426450.c` | 97 | 24 | 50 |  |
| `func_8010EFBC_duel01` | `src/overlays/duel01/3D8AC0.c` | 97 | 24 | 50 | float constants: retail keeps 64.0f and 3.0f out of registers (loop hoisting), frame 8 bytes larger (masked 24) |
| `func_8010EFFC_duel02` | `src/overlays/duel02/3EC590.c` | 97 | 24 | 50 |  |
| `func_8010F078_duel04` | `src/overlays/duel04/410910.c` | 97 | 24 | 50 | board ea1: duel05 twin, duel04 constants checked against retail (immediates); masked 24 here; logic as duel05 |
| `func_8010F184_duel06` | `src/overlays/duel06/436E50.c` | 97 | 24 | 50 |  |
| `func_80111E6C_duel10` | `src/overlays/duel10/4461E0.c` | 97 | 24 | 50 | board ec3: duel01/duel05 twin; float constants: retail keeps 64.0f and 3.0f out of registers (loop hoisting), frame 8 bytes larger (masked 24) |
| `func_8010BDE0_spotlight_swim` | `src/overlays/ovl_03_spotlight_swim/1263E0.c` | 131 | 24 | 88 | regalloc: retail spills D_8010D47C_spotlight_swim (hoisted) to sp+4 and keeps the row end in s1; mine * spills the row end and keeps the global in a3. Same ops ... |
| `func_801074CC_parasol_plummet` | `src/overlays/ovl_1C_parasol_plummet/1DE610.c` | 133 | 24 | 40 | (masked 24): separate case 0/1/2 labels give retail's dispatch tree, but GCC still merges case 3's rand8 test into theirs (retail keeps two calls; tried: case 3... |
| `func_8010D234_msetup` | `src/overlays/msetup/506F20.c` | 167 | 24 | 57 | logic checked; retail keeps dx/dy as words (lw, then sll/sra at each use) where GCC here reads the stack halfword, which changes the frame and register allocati... |
| `func_8010654C_mchar` | `src/overlays/mchar/3D3C80.c` | 181 | 24 | 40 | loads the eight characters' two models from set `set` and their motion 0 |
| `func_80106E8C_slot_synch` | `src/overlays/ovl_14_slot_synch/1AC970.c` | 200 | 24 | 38 |  |
| `func_8003CE20_main` | `src/gamemes.c` | 208 | 24 | 42 | register allocation and loop shape in the i + 1 loops (masked 24), as func_80037574_main |
| `func_80108568_marios_puzzle_party` | `src/overlays/ovl_1F_marios_puzzle_party/1F3B90.c` | 261 | 24 | 66 | Clear every group of matching blocks, let the blocks above fall, and repeat while chains form. |
| `func_80106C98_toadstool_titan` | `src/overlays/ovl_16_toadstool_titan/1BA850.c` | 487 | 24 | 29 | register allocation: retail keeps 0.5f/0.875f in FPU registers and loads HmfModelData after the index; logic checked |
| `func_8010A398_puddle_paddle` | `src/overlays/ovl_11_puddle_paddle/191240.c` | 543 | 24 | 42 | masked 24 (542 vs 543): the drift-decay blocks keep the drag in another register (a copy for the compare) and the stun shake allocates differently; logic checke... |
| `func_80116FE0_msetup` | `src/overlays/msetup/506F20.c` | 600 | 24 | 28 | State: per-team handicap board (MsConfig.star) for two players in turn: left/right turns the sign through D_80119FE4_msetup, A stores it and moves on, B goes ba... |
| `func_80107A90_hyper_hydrants` | `src/overlays/ovl_0E_hyper_hydrants/17B3B0.c` | 637 | 24 | 34 | masked residue: $a0/$v1 for the pressure limit and the 110/55 jet distance multiply not duplicated into both arms (scheduling only); logic checked |
| `func_8010A210_duel01` | `src/overlays/duel01/3D8AC0.c` | 655 | 24 | 24 | duel b2: masked 24 of 655: register choice around the &sp98/&sp78 arguments of HuVecSubtract (retail recomputes them per arm); logic checked block by block. |
| `func_8010A214_duel03` | `src/overlays/duel03/3FE1F0.c` | 655 | 24 | 24 | duel b2: masked 24 of 655: register choice around the &sp98/&sp78 arguments of HuVecSubtract (retail recomputes them per arm); logic checked block by block. |
| `func_801096E4_slapdown` | `src/overlays/ovl_2E_slapdown/264B80.c` | 187 | 25 | 29 | Ranks the players by slap order (unk0A: frame of the slap, -1 slapped the wrong card, -2 never slapped). |
| `func_80109BFC_baby_bowser_bonkers` | `src/overlays/ovl_35_baby_bowser_bonkers/29B1D0.c` | 193 | 25 | 15 | Builds player `idx`'s score counter: two digits, the character face and a backing. NON_MATCHING: retail sign-extends HuSprGrpCreate's result before storing it (... |
| `func_8010981C_puddle_paddle` | `src/overlays/ovl_11_puddle_paddle/191240.c` | 252 | 25 | 54 | masked 28; retail keeps best in a stack slot (frame 0x78, s0-s4), ours gives it s5; logic checked against the asm |
| `func_80039A6C_main` | `src/gamemes.c` | 280 | 25 | 35 | "START" letters rising and bouncing: register allocation (masked 25: the case 0 j + 1 loop increments in place) |
| `func_8010D490_marios_puzzle_party` | `src/overlays/ovl_1F_marios_puzzle_party/1F3B90.c` | 300 | 25 | 25 | Background sparkle: wait a random time, appear near its spot, drift and shrink. |
| `func_8010A0C0_swinging_with_sharks` | `src/overlays/ovl_3F_swinging_with_sharks/2E0D20.c` | 133 | 26 | 39 | retail frame is 8 bytes larger and keeps the head model in s2 re-sign-extended (sll/sra) after the branch |
| `func_801122B0_filesel` | `src/overlays/filesel/516AE0.c` | 153 | 26 | 78 | register choice for no/mask and the name-terminator addressing (masked 28, logic checked) |
| `func_80116DA0_duel04` | `src/overlays/duel04/410910.c` | 182 | 26 | 30 | board ea3: logic checked against the asm case by case; masked 26: the same store-flag (case 7) and rev-in-v1 (case 1/2 tails) differences as func_8011678C_duel0... |
| `func_8003C248_main` | `src/gamemes.c` | 272 | 26 | 65 | "FINISH" letters flipping: register allocation (masked 30: i and chr swap registers, the flip loop extends i + 1 per call) |
| `func_8003CA24_main` | `src/gamemes.c` | 272 | 26 | 65 | "FINISH" letters flipping and dropping: register allocation (masked 30, as func_8003C248_main) |
| `func_80105AD8_koopa` | `src/overlays/koopa/3C27C0.c` | 1083 | 26 | 47 | masked 30 of 1083: block placement around the CPU/A-button check and the second wrap of the stop slot, and the hoisted D_801093A8 base in the last loop; logic c... |
| `func_8010A88C_hide_and_sneak` | `src/overlays/ovl_06_hide_and_sneak/137C00.c` | 182 | 27 | 27 |  |
| `func_801085FC_cheep_cheep_chase` | `src/overlays/ovl_26_cheep_cheep_chase/225740.c` | 222 | 27 | 50 | Register allocation: GCC hoists func_8010A08C_cheep_cheep_chase out of the second loop (one more saved register). |
| `func_8010B658_toadstool_titan` | `src/overlays/ovl_16_toadstool_titan/1BA850.c` | 237 | 27 | 42 | register allocation and frame (retail 0xD0, two more saved registers, one base pointer into the tables); logic checked |
| `func_801152C4_msetup` | `src/overlays/msetup/506F20.c` | 375 | 27 | 37 | Turn count dial on model `model`: four labelled parts (20/35/50 turns, ?), the selected one pulses; the hand ("hari", base matrix `hand`) turns to D_80119F4C_ms... |
| `func_801098AC_water_whirled` | `src/overlays/ovl_23_water_whirled/211AB0.c` | 416 | 27 | 54 | Masked 27: retail keeps one more float in a callee-saved register ($f20-$f28; frame 0x50, here 0x48), so the float registers and stack offsets differ; the instr... |
| `func_8008A1B0_main` | `src/8ADB0.c` | 59 | 28 | 31 | guRotateX (degrees) straight into the fixed-point Mtx: the s15.16 cosine, sine and -sine are parked in m[1][1], m[0][3] and m[3][0] while the integer and fracti... |
| `func_8008A330_main` | `src/8AF30.c` | 64 | 28 | 40 | guRotateY (degrees) straight into the fixed-point Mtx: the s15.16 cosine, -sine and sine are parked in m[0][0], m[0][1] and m[1][0] while the integer and fracti... |
| `func_8010AB34_hyper_hydrants` | `src/overlays/ovl_0E_hyper_hydrants/17B3B0.c` | 200 | 28 | 46 | masked residue: as func_8010A68C, plus 80.0f kept in a saved register here (registers/scheduling; logic checked) |
| `func_8010B644_cosmic_coaster` | `src/overlays/ovl_10_cosmic_coaster/18ABD0.c` | 202 | 28 | 47 | Riders' boxes against this side's track objects (types 0, 1, 4): result per rider in a half. |
| `func_80108810_pump_pump_away` | `src/overlays/ovl_0D_pump_pump_away/16F670.c` | 205 | 28 | 148 |  |
| `func_801073F4_stardust_battle` | `src/overlays/ovl_41_stardust_battle/2ED2D0.c` | 266 | 28 | 64 | register allocation, and retail sign-extends the two saved stick bytes (lbu/sll/sra) where mine keeps lb; they are only stored back as bytes |
| `func_801083A8_hyper_hydrants` | `src/overlays/ovl_0E_hyper_hydrants/17B3B0.c` | 266 | 28 | 51 | masked residue: retail converts -half after the spread's rand8() call (evaluation order; logic checked) |
| `func_80106190_log_jam` | `src/overlays/ovl_13_log_jam/1A3D80.c` | 331 | 28 | 77 | Differs: the group switch keeps one register copy fewer (retail moves the group into v1). |
| `func_80114C80_mgmode` | `src/overlays/mgmode/479470.c` | 179 | 29 | 33 | Lets the player pick how many coins to spend (D-pad: +-10, +-1); A confirms a non-zero amount, B returns -1. |
| `func_8003966C_main` | `src/gamemes.c` | 275 | 29 | 44 | "START" letters dropping and bouncing: register allocation (masked 33: the case 0 j + 1 loop increments in place, case 1 keeps D_800B1BC0_main in a register) |
| `func_80106198_ice_rink_risk` | `src/overlays/ovl_19_ice_rink_risk/1D1C40.c` | 311 | 29 | 41 | The rink: runs the minigame's states. masked 1 instruction: retail compares the alive flags against 1 kept in a register (xor), GCC 2.7.2 here emits xori; the r... |
| `func_80111380_mgmode` | `src/overlays/mgmode/473130.c` | 625 | 29 | 75 | masked 29: GCC forms the sound id with a store-flag sequence where retail branches, * and case 4 shares the spr[n] address (retail computes it twice); register ... |
| `func_80105C50_pipe_cleaners` | `src/overlays/ovl_27_pipe_cleaners/22E100.c` | 117 | 30 | 50 |  |
| `func_800605A4_main` | `src/window.c` | 210 | 30 | 74 | register allocation (masked 100 of 169): the text pointer and the character width swap a0/a1, and GCC keeps D_800CD2A4_main and D_800BDA6A_main in registers (u8... |
| `func_80109670_merry_go_chomp` | `src/overlays/ovl_2D_merry_go_chomp/25E110.c` | 256 | 30 | 74 | masked 43: retail stores link 0 by absolute address and loads 5.0f later; scheduling only |
| `func_80039E80_main` | `src/gamemes.c` | 307 | 30 | 34 | "START" tracing a path in: register allocation (masked 30: the case 0 j + 1 loop increments in place) |
| `func_8010E4B4_duel10` | `src/overlays/duel10/4461E0.c` | 312 | 30 | 36 | board ec2: walk the current player: `steps` spaces at most (-1: no limit), `walkNum` counted spaces (0: the dice roll); func_80114940_duel10 may stop the walk f... |
| `func_80013390_main` | `src/13F90.c` | 372 | 30 | 50 | Masked 19 (374 vs 372): retail calls rand8 as if it returned int (no andi 0xff after the call; include/functions.h declares u8), so the shuffle's index arithmet... |
| `func_801059A0_mgresultduel` | `src/overlays/mgresultduel/4F01F0.c` | 431 | 30 | 92 | duelres A: Masked 21: retail loads the coin index with lbu + sign extension and schedules it before the result store. |
| `func_8010A588_marios_puzzle_party` | `src/overlays/ovl_1F_marios_puzzle_party/1F3B90.c` | 293 | 31 | 76 | Game over for a player: shake the frame, swap in the game-over panel, then bob it. |
| `func_8010A958_marios_puzzle_party` | `src/overlays/ovl_1F_marios_puzzle_party/1F3B90.c` | 301 | 31 | 48 | Destructor of a player's game process (game over, or the minigame ending). |
| `func_80108880_awful_tower` | `src/overlays/ovl_25_awful_tower/21E010.c` | 318 | 31 | 75 | Sets up one player's object: models, motions and the team's tower. |
| `func_8010A68C_hyper_hydrants` | `src/overlays/ovl_0E_hyper_hydrants/17B3B0.c` | 345 | 31 | 78 | masked residue: retail selects the pumper/hose objects into one register before the loads and keeps the segment base differently (registers/scheduling; logic ch... |
| `func_80107108_slot_synch` | `src/overlays/ovl_14_slot_synch/1AC970.c` | 349 | 31 | 36 |  |
| `func_8011035C_msetup` | `src/overlays/msetup/506F20.c` | 451 | 31 | 54 | register allocation and operand order around the D_80119C10 rows (masked 28, 3 fewer instructions: retail re-extends cur for the second row); same logic |
| `func_8010C570_bowser_toss` | `src/overlays/ovl_34_bowser_toss/291020.c` | 726 | 31 | 33 | Debug camera test mode (Log Jam's func_8010B17C with one camera per screen). NON_MATCHING: retail loads the camera index into v1 and copies it to s4 in a branch... |
| `func_8010A1FC_game_guys_roulette` | `src/overlays/ovl_42_game_guys_roulette/2FF5F0.c` | 133 | 32 | 73 | Draw a filled ring of radius r in a colour (a 4-bit pixel pair per byte) into this frame's buffers, the mask layer gets the colour and the colour layer a 1 mask... |
| `func_8010BD9C_game_guys_magic_boxes` | `src/overlays/ovl_44_game_guys_magic_boxes/30DC30.c` | 133 | 32 | 73 | Draw a filled ring of radius r in a colour (a 4-bit pixel pair per byte) into this frame's buffers, the mask layer gets the colour and the colour layer a 1 mask... |
| `func_8010C72C_game_guys_sweet_surprise` | `src/overlays/ovl_45_game_guys_sweet_surprise/3151F0.c` | 133 | 32 | 73 | Draw a filled ring of radius r in a colour (a 4-bit pixel pair per byte) into this frame's buffers, the mask layer gets the colour and the colour layer a 1 mask... |
| `func_8010CD0C_game_guys_lucky_7` | `src/overlays/ovl_43_game_guys_lucky_7/306F70.c` | 133 | 32 | 73 | Draw a filled ring of radius r in a colour (a 4-bit pixel pair per byte) into this frame's buffers, the mask layer gets the colour and the colour layer a 1 mask... |
| `func_800392AC_main` | `src/gamemes.c` | 262 | 32 | 36 | "START" letters zooming in: register allocation (masked 32: the case 0 j + 1 loop increments in place) |
| `func_80108BD4_mgresultdealer` | `src/overlays/mgresultdealer/4EDCB0.c` | 357 | 32 | 83 | masked 62, 5 short: retail keeps &totalSpr[0] in s0 for the show/hide calls and schedules the digit divisions differently count the total up over 28 frames, tic... |
| `func_8010A570_pump_pump_away` | `src/overlays/ovl_0D_pump_pump_away/16F670.c` | 554 | 32 | 45 |  |
| `func_80106E74_majinlamp` | `src/overlays/majinlamp/3C7EC0.c` | 741 | 32 | 32 | event e5: NON_MATCHING. With func_80017AD8_main returning s16 (functions.us.h says u8: one extra andi 0xFF) only stack offsets differ: retail lays the four Vecs... |
| `func_80110A70_duel03` | `src/overlays/duel03/3FE1F0.c` | 1390 | 32 | 162 | board db2: func_80110C3C_duel01's twin (same instructions), same residue. |
| `func_80110C3C_duel01` | `src/overlays/duel01/3D8AC0.c` | 1390 | 32 | 162 | Turn start: on the first turn both players pick their starting partners; partner 6 may hand over 2-4 coins; from the second turn the player pays the partners' u... |
| `func_80110CF8_duel04` | `src/overlays/duel04/410910.c` | 1390 | 32 | 162 | Turn start: on the first turn both players pick their starting partners; partner 6 may hand over 2-4 coins; from the second turn the player pays the partners' u... |
| `func_80106C98_marios_puzzle_party` | `src/overlays/ovl_1F_marios_puzzle_party/1F3B90.c` | 113 | 33 | 44 | Move a piece down by dy; undo and return TRUE if it hits something. |
| `func_80109690_spotlight_swim` | `src/overlays/ovl_03_spotlight_swim/1263E0.c` | 172 | 33 | 52 | retail loads D_8010D2F4_spotlight_swim with lbu and sign-extends it twice for the bit tests (mine: one lb); one sll scheduled earlier CPU decision for a chasing... |
| `func_8010A360_fridged_bridges` | `src/overlays/ovl_24_fridged_bridges/216670.c` | 746 | 33 | 33 | The bird that lifts a player out of the water and drops them back on their last safe spot |
| `func_8010ED04_duel06` | `src/overlays/duel06/436E50.c` | 99 | 34 | 85 | control flow (masked 34): retail repeats the walk test in each of the four arms (two cross-jumped into one tail) and keeps &GwSystem in $s0 for the first arm's ... |
| `func_80115848_mgmode` | `src/overlays/mgmode/479470.c` | 166 | 34 | 52 | The player turns round and walks back to the door. |
| `func_801067C4_mchar2` | `src/overlays/mchar2/3D5C30.c` | 381 | 34 | 82 | masked 37: as mgenter func_80108A60_mgenter, retail addresses Center through a base register (one more $f register here) debug camera on the first controller (a... |
| `func_80106898_mchar` | `src/overlays/mchar/3D3C80.c` | 381 | 34 | 82 | masked 37: as mgenter func_80108A60_mgenter, retail addresses Center through a base register (one more $f register here) debug camera on the first controller (a... |
| `func_80108A60_mgenter` | `src/overlays/mgenter/46BB50.c` | 469 | 34 | 82 | masked 34: retail addresses Center through a base register and shares the D-pad move tails (one more $f register here) debug camera on the second controller: C ... |
| `func_80107298_boulder_ball` | `src/overlays/ovl_04_boulder_ball/12DD30.c` | 478 | 34 | 63 | masked ~30: retail recomputes GwPlayer[player]'s offset for cpu_difficulty and keeps diff in s7 where GCC here CSEs the offset and spills diff, which shifts the... |
| `func_80107554_crowd_cover` | `src/overlays/ovl_38_crowd_cover/2B5830.c` | 548 | 34 | 39 | Player object: CPU decision, picking a card (Z/B/A), the flip and the result motion. |
| `func_8010683C_eye_sore` | `src/overlays/ovl_30_eye_sore/270EF0.c` | 582 | 34 | 53 |  |
| `func_80108A28_mstory5` | `src/overlays/mstory5/4D1200.c` | 1050 | 34 | 35 | masked 49: CharFXPlay's s16 prototype (retail truncates its result at the assignment), and the stores to actors 1/7/10 and the wait for actor 1 (retail does not... |
| `func_8010A3F4_game_guys_roulette` | `src/overlays/ovl_42_game_guys_roulette/2FF5F0.c` | 158 | 35 | 113 | Draw a line in colour 7 into this frame's mask buffer (Bresenham, stepping in y) masked 39: two y-stepping Bresenham loops, register allocation and loop layout ... |
| `func_8010BF94_game_guys_magic_boxes` | `src/overlays/ovl_44_game_guys_magic_boxes/30DC30.c` | 158 | 35 | 113 | Draw a line in colour 7 into this frame's mask buffer (Bresenham, stepping in y) masked 39: two y-stepping Bresenham loops, register allocation and loop layout ... |
| `func_8010C924_game_guys_sweet_surprise` | `src/overlays/ovl_45_game_guys_sweet_surprise/3151F0.c` | 158 | 35 | 113 | Draw a line in colour 7 into this frame's mask buffer (Bresenham, stepping in y) masked 39: two y-stepping Bresenham loops, register allocation and loop layout ... |
| `func_8010CF04_game_guys_lucky_7` | `src/overlays/ovl_43_game_guys_lucky_7/306F70.c` | 158 | 35 | 113 | Draw a line in colour 7 into this frame's mask buffer (Bresenham, stepping in y) masked 39: two y-stepping Bresenham loops, register allocation and loop layout ... |
| `func_801068F8_all_fired_up` | `src/overlays/ovl_29_all_fired_up/23C8F0.c` | 235 | 35 | 38 | masked 37: retail keeps the counter in $a0 for one shared increment block and has a 0x38 frame (0x20 unused locals); the logic is checked against the asm |
| `func_80038934_main` | `src/gamemes.c` | 302 | 35 | 78 | "START" letters flying in: register allocation (masked 39: the i + 1 loops, and case 0 keeps D_800B1BC0_main in a register) |
| `func_8003843C_main` | `src/gamemes.c` | 352 | 35 | 78 | "START" flipping in: register allocation in the i + 1 loops (masked 35: i and i + 1 swap registers, one move per loop) |
| `func_801092F0_game_guys_sweet_surprise` | `src/overlays/ovl_45_game_guys_sweet_surprise/30F940.c` | 610 | 35 | 41 | The left character eats and sways; its plates follow; it wins or loses |
| `func_8010C478_messy_memory` | `src/overlays/ovl_1D_messy_memory/1E37C0.c` | 1271 | 35 | 266 | An item's object (work[0] the item, work[1] its board: 0-3 a player's, 4 the shown room), per game phase. |
| `func_80109870_hide_and_sneak` | `src/overlays/ovl_06_hide_and_sneak/137C00.c` | 247 | 36 | 53 |  |
| `func_80109290_cosmic_coaster` | `src/overlays/ovl_10_cosmic_coaster/18ABD0.c` | 265 | 36 | 57 | Shooting star spawner per frame: launch a star on each side when its delay runs out. |
| `func_801084C8_merry_go_chomp` | `src/overlays/ovl_2D_merry_go_chomp/25E110.c` | 384 | 36 | 82 | masked 63: retail does not hoist the D_8010C420 base out of the first loop, and hoists the float constants instead |
| `func_80116F0C_mstory2` | `src/overlays/mstory2/4AC200.c` | 1715 | 36 | 51 | masked 38: two counters are allocated to swapped registers, and retail puts the exit of the first wait loop (i = 0) in a stub after the if branch; logic checked... |
| `func_80112250_mstory2` | `src/overlays/mstory2/4A7540.c` | 1719 | 36 | 36 | the second scene's cutscene (actor 5's action): actor 4 flies in along a path, the actors talk (two rounds when the player is character 5), actor 4 flies off al... |
| `func_8008D450_main` | `src/8E050.c` | 101 | 37 | 71 | guLookAtF from a LookAtCam: look = normalize(eye - at), right = normalize(up x look), up = normalize(look x right); basis is the caller's work area NON_MATCHING... |
| `func_8003AC9C_main` | `src/gamemes.c` | 116 | 37 | 41 | As func_8003A9C8_main, but returns the character's advance width in *width; flag bit 0 is the large font. Unused. masked 37 (5 instructions short): retail keeps... |
| `func_8010BE84_etch_n_catch` | `src/overlays/ovl_12_etch_n_catch/19CEF0.c` | 369 | 37 | 48 | The drawing board: two sprite layers, the 8-bit grid (the second layer's texels) and its palette, the walls, the flood-fill lists, and the framework ground bloc... |
| `func_80001E10_main` | `src/1140.c` | 387 | 37 | 83 | register allocation: heap spilled instead of kept in fp (retail then reuses fp for the -1), frame 8 bytes larger and one reload more (masked 47) |
| `func_80106E78_thwomp_pull` | `src/overlays/ovl_08_thwomp_pull/14A810.c` | 1239 | 37 | 130 |  |
| `func_80106E40_marios_puzzle_party` | `src/overlays/ovl_1F_marios_puzzle_party/1F3B90.c` | 121 | 38 | 56 | The same for the special piece, which spans two columns. |
| `func_80115590_mgmode` | `src/overlays/mgmode/479470.c` | 197 | 38 | 60 | The player walks from the door to the block spot and turns to face the camera. |
| `func_800F5834_name_81` | `src/overlays/ovl_81_name/DC4E0.c` | 256 | 38 | 80 |  |
| `func_801169EC_duel04` | `src/overlays/duel04/410910.c` | 280 | 38 | 46 | board ea3: logic checked against the asm case by case; masked 38: as func_801163C0_duel04 (frame 0x20 larger, rev tested in v1 in the case 1/2 tails, shared ret... |
| `func_80108560_pump_pump_away` | `src/overlays/ovl_0D_pump_pump_away/16F670.c` | 186 | 39 | 180 |  |
| `func_801096BC_parasol_plummet` | `src/overlays/ovl_1C_parasol_plummet/1DE610.c` | 196 | 40 | 83 | register allocation and block order (masked 40, one instruction short). After a thrower throws, draw two items from the bag (at most one five-coin bag and one h... |
| `func_80106BEC_chancetime` | `src/overlays/chancetime/4822F0.c` | 246 | 40 | 44 | H0: calls match retail (CALLS was block order); masked 40: retail lays the rand-sleep arm first in the pad-wait loop; tried breaks and a goto loop (worse). |
| `func_8010972C_motor_rooter` | `src/overlays/ovl_36_motor_rooter/main.c` | 374 | 40 | 71 | <func_8010972C_motor_rooter> |
| `func_8010980C_treadmill_grill` | `src/overlays/ovl_15_treadmill_grill/1B4F10.c` | 567 | 40 | 166 | Moves the three grill-riding hazards along the belt loop (D_8010AFE0[i].x is the distance along it) and places their models. Logic checked block by block; retai... |
| `func_801076AC_motor_rooter` | `src/overlays/ovl_36_motor_rooter/main.c` | 242 | 41 | 54 | <func_801076AC_motor_rooter> |
| `func_80109B18_stardust_battle` | `src/overlays/ovl_41_stardust_battle/2ED2D0.c` | 291 | 41 | 122 | register allocation: retail keeps the best weight in s3 (mfc1/mtc1) and schedules 1.0f - ny into the sqrtf delay slot; mine keeps it in an FPR |
| `func_8010A734_crowd_cover` | `src/overlays/ovl_38_crowd_cover/2B5830.c` | 377 | 41 | 92 | Gives billboard id sprite tex: rebuilds its strip and display list. |
| `func_8010C7FC_fowl_play` | `src/overlays/ovl_3A_fowl_play/2C5B50.c` | 377 | 41 | 92 | Gives billboard id sprite tex: rebuilds its strip and display list. |
| `func_80114630_duel02` | `src/overlays/duel02/3EC590.c` | 381 | 41 | 65 | board da3: logic checked block by block against the asm; masked 41 (382 vs 381 instructions): the bool tails (frontPower/backID tests) become store-flag sequenc... |
| `func_801154DC_duel02` | `src/overlays/duel02/3EC590.c` | 387 | 41 | 65 | board da3: logic checked against the asm; masked 41 (388 vs 387 instructions), the same residue as func_80114630_duel02 board da3: func_80114630_duel02's decisi... |
| `func_80107204_storyresult` | `src/overlays/storyresult/54F360.c` | 604 | 41 | 50 | Residue (masked ~10): retail keeps the 160/120 screen centre in saved registers and derives 204/48/187 from them (GCC constant CSE); otherwise identical. Event ... |
| `func_80110C0C_duel05` | `src/overlays/duel05/426450.c` | 1390 | 41 | 171 | Turn start: on the first turn both players pick their starting partners; partner 6 may hand over 2-4 coins; from the second turn the player pays the partners' u... |
| `func_80110C7C_duel02` | `src/overlays/duel02/3EC590.c` | 1390 | 41 | 171 | Turn start: on the first turn both players pick their starting partners; partner 6 may hand over 2-4 coins; from the second turn the player pays the partners' u... |
| `func_80110E04_duel06` | `src/overlays/duel06/436E50.c` | 1390 | 41 | 171 | Turn start: on the first turn both players pick their starting partners; partner 6 may hand over 2-4 coins; from the second turn the player pays the partners' u... |
| `func_8010B1E4_hand_line_sinker` | `src/overlays/ovl_01_hand_line_sinker/11A480.c` | 261 | 42 | 115 | Moves a fish forward, keeping its two body circles apart from the other fish and inside the pond. |
| `func_8010A0D8_marios_puzzle_party` | `src/overlays/ovl_1F_marios_puzzle_party/1F3B90.c` | 289 | 42 | 39 | Result rank flying in from the distance over a player's board (player 4: the centre). |
| `func_801076D8_baby_bowser_bonkers` | `src/overlays/ovl_35_baby_bowser_bonkers/29B1D0.c` | 360 | 42 | 44 | Pushes two players apart (the moving or higher one moves) and keeps both in the arena; once more with the roles swapped when the push hit the wall. NON_MATCHING... |
| `func_80107CA4_mgresultduel` | `src/overlays/mgresultduel/4F01F0.c` | 521 | 42 | 69 | duelres A: Masked 39: retail duplicates the coin index (sll s0) into both arms of the burst choice; register allocation follows. Throw the coins from the loser ... |
| `func_8010A48C_hide_and_sneak` | `src/overlays/ovl_06_hide_and_sneak/137C00.c` | 156 | 43 | 88 |  |
| `func_8010622C_messy_memory` | `src/overlays/ovl_1D_messy_memory/1E37C0.c` | 157 | 43 | 68 | The title sign (D_80111700[4]): appears, shrinks away when the room is shown, grows back for scoring. |
| `func_8010A12C_crowd_cover` | `src/overlays/ovl_38_crowd_cover/2B5830.c` | 415 | 43 | 83 | Creates a billboard from sprite tex: a strip of quads sized to fit TMEM, then its display list. |
| `func_8010C1F4_fowl_play` | `src/overlays/ovl_3A_fowl_play/2C5B50.c` | 415 | 43 | 83 | Creates a billboard from sprite tex: a strip of quads sized to fit TMEM, then its display list. |
| `func_80108860_baby_bowser_broadside` | `src/overlays/ovl_0C_baby_bowser_broadside/165010.c` | 550 | 43 | 44 | <func_80108860_baby_bowser_broadside> |
| `func_8008ABA0_main` | `src/8B560.c` | 113 | 44 | 90 | Float matrix of guRotateRPYF (degrees) with each column scaled by scale and pos in the last row: scale, then rotate, then translate. scheduling: masked 44 at 11... |
| `func_80106A54_selmenu2` | `src/overlays/selmenu2/116320.c` | 293 | 44 | 65 | selmenu func_80106A10_selmenu: the page list and its input (no mode line). NON_MATCHING: as in selmenu, retail keeps the x of 64 in a0 and masks it after the tw... |
| `func_8005D30C_main` | `src/window.c` | 348 | 44 | 73 | register allocation (masked 44, all from one spill): retail keeps shadowHi in a stack slot (sb/lbu 0x1F(sp), frame 0x48); here it gets s5. Tried computing it fr... |
| `func_80111B14_filesel` | `src/overlays/filesel/516AE0.c` | 88 | 45 | 66 | Stick direction as a d-pad mask, once per push. retail keeps the two diagonal blocks separate; this C cross-jumps them (masked 45, logic checked) |
| `func_80109688_hide_and_sneak` | `src/overlays/ovl_06_hide_and_sneak/137C00.c` | 143 | 45 | 58 |  |
| `func_8010D55C_messy_memory` | `src/overlays/ovl_1D_messy_memory/1E37C0.c` | 270 | 45 | 62 | Item k of a board (work[1] board, work[0] item): load its image, place it in its slot (the shuffled room: a free random slot), then run func_8010C478. |
| `func_80107DA4_selmenu2` | `src/overlays/selmenu2/116320.c` | 775 | 45 | 52 | selmenu func_80107DFC_selmenu, with selmenu2's own boot: the entry's unk2 is the minigame, its overlay goes to D_800A12B0_main, and below overlay 0x47 the minig... |
| `func_8011678C_duel04` | `src/overlays/duel04/410910.c` | 182 | 46 | 50 | board ea3: logic checked against the asm case by case; masked 46: retail keeps branches where this C gets store-flag (case 6's front-power test) and tests rev i... |
| `func_80119F7C_w05` | `src/overlays/w05/37FFB0.c` | 537 | 46 | 46 |  |
| `func_80108298_fowl_play` | `src/overlays/ovl_3A_fowl_play/2C5B50.c` | 597 | 46 | 51 | 8 instructions long, scheduling only: a nop after each of six sindf/cosdf calls, and pad * 2 for &D_800D5558_main[pad] is hoisted into the switch cases' delay s... |
| `func_8010980C_crowd_cover` | `src/overlays/ovl_38_crowd_cover/2B5830.c` | 614 | 46 | 85 | Builds a billboard's display list: palette, then one texture load and two triangles per strip. |
| `func_8010B8D4_fowl_play` | `src/overlays/ovl_3A_fowl_play/2C5B50.c` | 614 | 46 | 85 | Builds a billboard's display list: palette, then one texture load and two triangles per strip. |
| `func_8010897C_swing_n_swipe` | `src/overlays/ovl_40_swing_n_swipe/2E6BE0.c` | 662 | 46 | 54 | masked 46: register allocation only (retail keeps 360.0f in $f30 and 270.0f in $s7; here they swap) |
| `MB1Ev_SnowmanRoll` | `src/overlays/ovl_48_ChillyWaters/31B9F0.c` | 795 | 46 | 52 | chilly B: NON_MATCHING: masked 46 (raw 61), 789 of 795 instructions: retail keeps the 50.0f/40.0f if/else unscheduled (bc1f + j; bc1fl here) and computes the /o... |
| `func_8010A484_parasol_plummet` | `src/overlays/ovl_1C_parasol_plummet/1DE610.c` | 212 | 47 | 91 | register allocation (retail keeps y in a stack slot; frame 16 bytes smaller; masked 77). The coin counters: icon, coin, "x" and three digits per player, leading... |
| `func_801192AC_w05` | `src/overlays/w05/37FFB0.c` | 267 | 47 | 84 |  |
| `func_80106A10_selmenu` | `src/overlays/selmenu/552F50.c` | 353 | 47 | 68 | retail keeps the x of 64 in a0 and masks it after the two print calls merge; the rest matches. |
| `func_80106334_etch_n_catch` | `src/overlays/ovl_12_etch_n_catch/19CEF0.c` | 566 | 47 | 94 | A player object: places the player at its team's start, loads its pen and models. |
| `func_80105C0C_baby_bowser_bonkers` | `src/overlays/ovl_35_baby_bowser_bonkers/29B1D0.c` | 622 | 47 | 72 | retail reloads D_8010BC48 for each level threshold and D_800EC598_minigame for the winner (no CSE across those blocks); this C keeps them in registers, so one m... |
| `func_8010A62C_popgun_pickoff` | `src/overlays/ovl_32_popgun_pickoff/283060.c` | 377 | 48 | 112 | Gives billboard id sprite tex: rebuilds its strip and display list. |
| `func_8010AA90_chancetime` | `src/overlays/chancetime/4832D0.c` | 416 | 48 | 70 | as func_80108EDC_chancetime (retail also copies the position into an unused Vec * before the hop and splits the landing test's index); logic matches. |
| `func_8010B124_chancetime` | `src/overlays/chancetime/4832D0.c` | 429 | 48 | 106 | as func_80108EDC_chancetime (retail also copies the position into an unused Vec * before the hop and splits the landing test's index); logic matches. |
| `func_8010B7AC_bowser_toss` | `src/overlays/ovl_34_bowser_toss/291020.c` | 734 | 48 | 71 | The three score counters: fade in, count up, pop, slide away. NON_MATCHING: float registers t/sum swapped (f20/f22), and retail converts the state-19 loop count... |
| `func_8010D1A0_mstory4` | `src/overlays/mstory4/4C8050.c` | 1608 | 48 | 62 | retail's frame is 72 bytes larger (unused stack after the spill of the actor 0 model), and register allocation / constant-load order differ in the lift loop, th... |
| `func_80108EDC_chancetime` | `src/overlays/chancetime/4832D0.c` | 439 | 49 | 71 | in the final hop loop retail keeps model*3 and model*192 in separate registers * for the landing test and reloads 0.0f each pass (4 instructions); logic matches... |
| `func_80109EB8_etch_n_catch` | `src/overlays/ovl_12_etch_n_catch/19CEF0.c` | 906 | 49 | 52 | A catcher. work[0]: 0 start at its cage; 1 swing its pointer; 2 pulse; 3 pick a heading that stays in its team's area and turn to it; 4 walk; 5 jump up (first t... |
| `func_801183D4_w04` | `src/overlays/w04/367960.c` | 1062 | 49 | 50 | board q4: masked 30; retail keeps -1 in s8 for the second choice loop, this C hoists 2.0f into $f24 instead |
| `func_80107224_marios_puzzle_party` | `src/overlays/ovl_1F_marios_puzzle_party/1F3B90.c` | 131 | 50 | 64 |  |
| `func_80106F7C_duelresult2` | `src/overlays/duelresult2/45D380.c` | 387 | 51 | 65 | masked 71; retail hoists k * 16, k * 11 and the lead bit into stack slots (a 0x78 frame) and differs in register allocation, as in boardresult2's twin func_8010... |
| `func_80106AF8_river_raiders` | `src/overlays/ovl_09_river_raiders/1542E0.c` | 406 | 51 | 59 | CPU steering for a raft: picks the nearest target ahead and steers toward it (D_8010DE94: the raft's * entity; unk04 the chosen direction 0 none, 1 left, 2 righ... |
| `func_801066E4_pipe_cleaners` | `src/overlays/ovl_27_pipe_cleaners/22E100.c` | 180 | 52 | 52 | CPU player input. control flow (masked 52, 132 of 180): GCC cross-jumps the last else branch into the identical tail of the aim branch (random pipe, pull roll, ... |
| `func_80108DD0_etch_n_catch` | `src/overlays/ovl_12_etch_n_catch/19CEF0.c` | 227 | 52 | 170 | Flood-fills the empty area around grid cell (2x, 2y). Returns 0 if it reaches a 0x22 cell, otherwise whether the walls it meets belong to one team only (region ... |
| `func_80115A9C_msetup` | `src/overlays/msetup/506F20.c` | 285 | 52 | 97 | Two-way choice on the board model: the chosen part ("20turn" / "mugen") pulses, the "hari" needle turns to D_80119F60_msetup[sel]. Returns the choice, -1 on B. |
| `func_80107CF8_filesel` | `src/overlays/filesel/516AE0.c` | 580 | 52 | 76 | Differs only in scheduling and register use: retail hoists 0.0f and 31.0f into FPRs out of the retry loop, keeps &D_800D09A9_main in s0, and builds the omovlhis... |
| `func_801191B8_w04` | `src/overlays/w04/367960.c` | 1076 | 53 | 55 | board q4: masked 53; the same 2.0f/-1 hoisting residue as func_801183D4_w04, and GCC turns the 0x906/0x907 message choice into a store-flag sequence where retai... |
| `func_801074B4_boardresult2` | `src/overlays/boardresult2/3CFC80.c` | 370 | 54 | 113 | loop-invariant placement and register allocation (retail hoists k * 16 and k * 11 into stack slots, keeps the value in a2); the "" after "%4d" in retail .rodata... |
| `func_80109750_cheep_cheep_chase` | `src/overlays/ovl_26_cheep_cheep_chase/225740.c` | 386 | 54 | 125 | Register allocation and scheduling (one more saved register; retail computes the inner loop bound in the loop). |
| `func_80107DFC_selmenu` | `src/overlays/selmenu/552F50.c` | 814 | 54 | 63 | scheduling only (the instruction-skip call's a1, the CPU loop's first k, the random pick's address). |
| `func_8011A704_w03` | `src/overlays/w03/34E840.c` | 886 | 54 | 58 |  |
| `func_80108A50_marios_puzzle_party` | `src/overlays/ovl_1F_marios_puzzle_party/1F3B90.c` | 93 | 55 | 125 | masked 55: retail folds the -1/+1 column and row offsets into the base address (D_8010FFC0 = cell[-1][0]) and recomputes each sum; tried plain array indexing (6... |
| `func_8011580C_duel03` | `src/overlays/duel03/3FE1F0.c` | 213 | 55 | 79 | board db3: logic checked against the asm (func_8011454C_duel03 with the regions moved: same residue, masked 55) board db3: COM decision, the variant for cidx 22... |
| `func_8011454C_duel03` | `src/overlays/duel03/3FE1F0.c` | 214 | 55 | 79 | board db3: logic checked against the asm; masked 55: register choice for the roll and the branch layout of the 'same space' test (as func_80113AE0_duel03) board... |
| `func_80107654_aces_high` | `src/overlays/ovl_17_aces_high/1C4280.c` | 640 | 55 | 59 | masked 0 apart from one instruction: retail copies mode to a0 (move a0,s2) before the mode == 3 test of the input select; the same operations otherwise |
| `func_8010A010_mpiq` | `src/overlays/ovl_21_mpiq/204F90.c` | 118 | 56 | 88 | masked 56: retail computes q * 2 in every case and puts default after the shared store (H0 tried per-case stores, s32 ref, a goto to a shared store inside the s... |
| `func_80115DA8_duel04` | `src/overlays/duel04/410910.c` | 285 | 56 | 62 | board ea2: logic checked against the asm case by case; masked 56: the cur/rev tails (retail computes the result into $v0 around a branch-likely; this C keeps it... |
| `func_80107858_awful_tower` | `src/overlays/ovl_25_awful_tower/21E010.c` | 1195 | 56 | 121 | Draws the four players' tower backgrounds as textured strips; the winner's view zooms out. |
| `func_8010E12C_marios_puzzle_party` | `src/overlays/ovl_1F_marios_puzzle_party/1F3B90.c` | 512 | 57 | 120 | Record panel: the saved record (four digits, leading zeros hidden), replaced by player 0's score with a pulse when the game ends on a new record. |
| `func_80115EE0_msetup` | `src/overlays/msetup/506F20.c` | 675 | 57 | 64 | State: the game-length board. Lifts bring the board model up; step 0 picks the length (func_801152C4_msetup), step 1 the custom turn count (func_801157B8_msetup... |
| `func_80109F34_staff` | `src/overlays/staff/542220.c` | 722 | 57 | 72 | Register allocation: retail keeps attach in fp and spills sub; logic checked block by block. |
| `func_800DF594_name_81` | `src/overlays/ovl_81_name/C5770.c` | 506 | 58 | 86 | logic checked against the asm; differs only in which loop invariants are hoisted (&D_80100E88_name_81[pool] vs the recent-minigame row base) and the register al... |
| `func_8010D9C4_rockin_raceway` | `src/overlays/ovl_2C_rockin_raceway/251FF0.c` | 501 | 59 | 123 | Plays recorded frame `frame` back, blending from the frame before over 4.5 ticks. |
| `func_800DFBF4_name_81` | `src/overlays/ovl_81_name/C5770.c` | 541 | 59 | 86 | same body as func_800DF594_name_81 run as a process; same loop-invariant hoisting difference. |
| `func_8010FDF0_messy_memory` | `src/overlays/ovl_1D_messy_memory/1E37C0.c` | 1047 | 59 | 115 | The minigame's phase controller (D_80115D8C the phase, D_80115D8E its timer). |
| `func_801084BC_slapdown` | `src/overlays/ovl_2E_slapdown/264B80.c` | 547 | 60 | 62 | One card: obj->rot.z is its flip angle, card->unk04 1 = face up, unk06 its face, unk08 the flip step. |
| `func_80108454_baby_bowser_bonkers` | `src/overlays/ovl_35_baby_bowser_bonkers/29B1D0.c` | 385 | 61 | 116 | A player landing on top of the block: bounce, score, and the player index; -1 none. NON_MATCHING: retail sign-extends the stick bytes from lbu and masks the dea... |
| `func_80106F18_coconut_conk` | `src/overlays/ovl_02_coconut_conk/120BC0.c` | 477 | 61 | 107 | The solo player's CPU: picks a direction (D_8010BCC4_coconut_conk[0].unk04: 1 left, 2 right). |
| `func_8010604C_marios_puzzle_party` | `src/overlays/ovl_1F_marios_puzzle_party/1F3B90.c` | 843 | 64 | 129 | Mode, sprite data, block batches, empty boards with walls, the piece colour sequence and the shuffled board positions; the Mode 2 boards start with four rows of... |
| `func_8008C450_main` | `src/8CB20.c` | 100 | 65 | 95 | dst = src rotated by angle degrees about z (rows 0 and 1 mixed, rows 2 and 3 copied), float matrices; src and dst may be the same. scheduling: retail schedules ... |
| `func_80108788_hyper_hydrants` | `src/overlays/ovl_0E_hyper_hydrants/17B3B0.c` | 525 | 65 | 121 | masked residue: retail keeps 0.0f in $f12 for the drop resets and hoists the constant 1 (registers/scheduling; logic checked) |
| `func_80118D48_msetup` | `src/overlays/msetup/506F20.c` | 588 | 65 | 79 | Story-mode setup process: three func_80117A3C_msetup page processes (one MsStoryWork each, ids 0-2) driven through a message window; on confirm it seeds GwStory... |
| `func_801162B4_mgmode` | `src/overlays/mgmode/479470.c` | 235 | 66 | 90 | Draws the iris mask into this frame's buffer: a wedge centred on cx, open by angle, with a two-pixel rim. |
| `LeoBootGame` | `src/72750.c` | 87 | 67 | 83 |  |
| `func_80106CEC_baby_bowser_bonkers` | `src/overlays/ovl_35_baby_bowser_bonkers/29B1D0.c` | 644 | 67 | 146 | CPU player: picks a rising block away from the opponent, walks to it and jumps on it. NON_MATCHING: masked 77, register allocation and scheduling (one more stac... |
| `func_80107EA4_etch_n_catch` | `src/overlays/ovl_12_etch_n_catch/19CEF0.c` | 661 | 67 | 126 | CPU player input: chases a point beside its team's catcher, then circles the catcher (D_8010C6E4 state 0 approach, 1 turn to face along the pen, 2 circle); radi... |
| `func_8008BD90_main` | `src/8C440.c` | 100 | 68 | 106 | dst = src rotated by angle degrees about y (rows 0 and 2 mixed, rows 1 and 3 copied), float matrices; src and dst may be the same. scheduling: retail schedules ... |
| `func_80113AE0_duel03` | `src/overlays/duel03/3FE1F0.c` | 373 | 68 | 93 | board db3: logic checked branch by branch against the asm; masked 68: region 7-13 keeps a second roll < 8 test and reloads cidx, and operand load order in the p... |
| `func_80114D80_duel03` | `src/overlays/duel03/3FE1F0.c` | 377 | 68 | 96 | board db3: logic checked against the asm; masked 68: the same residue as func_80113AE0_duel03 (second roll test, operand order) board db3: COM decision, the var... |
| `func_8008B6B0_main` | `src/8C2B0.c` | 100 | 69 | 113 | dst = guRotateXF(angle) * src: rows 1 and 2 of src rotated into each other (angle in degrees); dst may be src NON_MATCHING: retail reads every element before th... |
| `func_80107EB8_staff` | `src/overlays/staff/542220.c` | 513 | 70 | 120 | Register allocation only (same instructions otherwise): retail keeps nameT in s7 and spills the layers pointer. Retail also has a file boundary at 0x801085F0 (o... |
| `func_8008A960_main` | `src/8B560.c` | 147 | 71 | 133 | guRotateRPY (degrees) straight into the fixed-point Mtx: each s15.16 element's integer half goes to the first 16 halfwords and its fraction half to the last 16.... |
| `func_80109414_mpiq` | `src/overlays/ovl_21_mpiq/204F90.c` | 201 | 71 | 120 | Draw the ten questions: no repeats, then shuffle each question's three answers. |
| `func_80109754_slot_synch` | `src/overlays/ovl_14_slot_synch/1AC970.c` | 606 | 73 | 81 |  |
| `func_8010AAC4_stardust_battle` | `src/overlays/ovl_41_stardust_battle/2ED2D0.c` | 1526 | 73 | 91 | register allocation (f20/f22 for the case-2 scale and the case-3 deltas), the trail-distance loads and one andi before func_80110758; ops, calls and fields equa... |
| `func_80108398_popgun_pickoff` | `src/overlays/ovl_32_popgun_pickoff/283060.c` | 353 | 74 | 169 |  |
| `func_8010B220_picking_panic` | `src/overlays/ovl_0F_picking_panic/181950.c` | 489 | 74 | 153 |  |
| `func_8002EAC0_main` | `src/22EB0.c` | 739 | 74 | 74 | MP2 func_8003A4B8_3B0B8 is NON_MATCHING the same way: retail loads -180.0f before *dst in the second wrap test, GCC the reverse (plus a nop); the rest follows M... |
| `func_80106BC4_bowser_toss` | `src/overlays/ovl_34_bowser_toss/291020.c` | 1264 | 74 | 104 | register allocation in the spin-target and pitch arithmetic; retail reloads p->unk10 for the * HuAudFXPitchSet argument where this keeps the tested value. |
| `func_801163C0_duel04` | `src/overlays/duel04/410910.c` | 289 | 77 | 81 | COM decision at a junction (a decision tree's leaf): from where the opponent stands (clink, cidx) against the roll (mbWalkNum), weigh the partners' front power. |
| `func_8010BF84_staff` | `src/overlays/staff/542220.c` | 505 | 77 | 85 | Branch layout of the scroll switch and register choice differ; logic checked block by block. |
| `func_8010ADB0_vine_with_me` | `src/overlays/ovl_31_vine_with_me/276470.c` | 2514 | 77 | 77 | TODO: only works with -Wa,--vr4300mul-off. |
| `func_80117004_duel04` | `src/overlays/duel04/410910.c` | 286 | 78 | 82 | board ea3: logic checked against the asm case by case; masked 78: as func_801163C0_duel04 (frame 0x20 larger, rev tested in v1 in the case 2/3 tails, shared ret... |
| `func_8008B0E0_main` | `src/8B960.c` | 137 | 79 | 149 | Rotation of angle degrees whose local z axis is turned onto the direction dir (normalised here); nothing is written when dir is zero. scheduling: retail schedul... |
| `func_8010B3B4_etch_n_catch` | `src/overlays/ovl_12_etch_n_catch/19CEF0.c` | 573 | 79 | 98 | A cage: state 0 picks a spot away from the team's players and drops onto it (landing burst at frame 45, sound at 50); 1 waits for its catcher (work[0] == 10) an... |
| `PutSprite` | `src/sprput.c` | 1016 | 84 | 90 | register allocation (as in MP2): tstep and sx swap f30/s8 and the zero for the initialisers is f30 instead of f20; the code is otherwise retail's. |
| `func_8010F87C_msetup` | `src/overlays/msetup/506F20.c` | 787 | 86 | 217 | Register allocation and scheduling only (masked ~93): retail keeps the lift count in s7 and spills its copy for the move loop, and reads D_8011AA44/D_8011AA40 t... |
| `func_8010A024_popgun_pickoff` | `src/overlays/ovl_32_popgun_pickoff/283060.c` | 415 | 87 | 139 | Creates a billboard from sprite tex: a strip of quads sized to fit TMEM, then its display list. |
| `func_8010E4D0_chancetime` | `src/overlays/chancetime/487F50.c` | 973 | 87 | 197 | instruction-for-instruction except the order of the two prize-table loads, the amount test (branch layout), one model-index computation and an 8-byte larger fra... |
| `func_80107E6C_eatsa_pizza` | `src/overlays/ovl_0B_eatsa_pizza/161750.c` | 361 | 91 | 125 | A bite: subtract the bite shape (D_80109282, 32x32, 4 bits per pixel) from the team's pizza mask in front of the player; every 2x2 block eaten down to nothing c... |
| `func_8010BA30_staff` | `src/overlays/staff/542220.c` | 275 | 92 | 161 | mes is either a message id or a string pointer (> 0x80000000, KSEG0): retail keeps both in one 32-bit word, as the matching form does. Host hazard: a 64-bit poi... |
| `func_80114030_duel03` | `src/overlays/duel03/3FE1F0.c` | 358 | 93 | 117 | board db3: logic checked against the asm (func_80113AE0_duel03's tests with the outcomes this one reverses); same residue as func_80113AE0_duel03 board db3: the... |
| `func_801152E0_duel03` | `src/overlays/duel03/3FE1F0.c` | 362 | 93 | 120 | board db3: logic checked against the asm (func_80114D80_duel03's tests with the outcomes this one reverses); same residue board db3: the companion COM decision ... |
| `func_8008AD60_main` | `src/8B960.c` | 227 | 95 | 206 | func_8008ABA0_main's scale-rotate-translate matrix built straight into the fixed-point Mtx: the twelve s15.16 elements of the upper 4x3 are computed first, then... |
| `func_8010AB44_mpiq` | `src/overlays/ovl_21_mpiq/204F90.c` | 281 | 97 | 117 | Answer slot of question q: slot 0 the right answer, else a wrong one near it. |
| `MB1Ev_SnowmanStart` | `src/overlays/ovl_48_ChillyWaters/31B9F0.c` | 1351 | 97 | 282 | Logic checked against the asm: same call sequence; masked residue is register allocation, the 20.0f * the retail build hoists into $f22 in the second placement ... |
| `func_8010BC6C_popgun_pickoff` | `src/overlays/ovl_32_popgun_pickoff/283060.c` | 471 | 98 | 99 | Draws one billboard: render state, its matrix, then a copy of its vertices and display list. |
| `func_80107CBC_marios_puzzle_party` | `src/overlays/ovl_1F_marios_puzzle_party/1F3B90.c` | 660 | 100 | 224 | Chain counter: "N chain" digits above the board while the chain lasts, then grow and fade out; each new chain step adds the cleared count to the player's score. |
| `func_800257BC_main` | `src/22EB0.c` | 713 | 100 | 197 | MP2 func_800329E8_335E8 (NON_MATCHING the same way): batch a part's faces and their vertices. MP3 adds a flush after a texture with flag bit 0 and records the f... |
| `func_8010B0CC_mpiq` | `src/overlays/ovl_21_mpiq/204F90.c` | 718 | 100 | 178 | Main process: ten questions (endless: repeats), first to three right answers wins. |
| `func_80108C80_marios_puzzle_party` | `src/overlays/ovl_1F_marios_puzzle_party/1F3B90.c` | 336 | 101 | 239 | A block (or a two-block piece) falls down its column until it rests on something. |
| `func_8010CE68_duel01` | `src/overlays/duel01/3D8AC0.c` | 463 | 102 | 206 | duel b2: masked 84 of 463: register/stack allocation (retail frame 8 bytes larger, 5.0f kept in $f20, extra1/extra2 slots swapped); logic checked block by block... |
| `func_8010CE6C_duel02` | `src/overlays/duel02/3EC590.c` | 463 | 102 | 206 | duel b2: masked 84 of 463: register/stack allocation (retail frame 8 bytes larger, 5.0f kept in $f20, extra1/extra2 slots swapped); logic checked block by block... |
| `func_8010CE6C_duel03` | `src/overlays/duel03/3FE1F0.c` | 463 | 102 | 206 | board db2: func_8010CE68_duel01's twin (same instructions), same residue. |
| `func_8010CE6C_duel04` | `src/overlays/duel04/410910.c` | 463 | 102 | 206 | board ea1: duel05 twin, duel04 constants checked against retail (immediates); masked 84 (472 vs 463) here; logic as duel05 duel b2: masked 84 of 463: register/s... |
| `func_8010CE70_duel06` | `src/overlays/duel06/436E50.c` | 463 | 102 | 206 | duel b2: masked 84 of 463: register/stack allocation (retail frame 8 bytes larger, 5.0f kept in $f20, extra1/extra2 slots swapped); logic checked block by block... |
| `func_8010CE78_duel05` | `src/overlays/duel05/426450.c` | 463 | 102 | 206 | duel b2: masked 84 of 463: register/stack allocation (retail frame 8 bytes larger, 5.0f kept in $f20, extra1/extra2 slots swapped); logic checked block by block... |
| `func_8010CED4_duel10` | `src/overlays/duel10/4461E0.c` | 463 | 102 | 206 | duel b2: masked 84 of 463: register/stack allocation (retail frame 8 bytes larger, 5.0f kept in $f20, extra1/extra2 slots swapped); logic checked block by block... |
| `func_801070E8_eatsa_pizza` | `src/overlays/ovl_0B_eatsa_pizza/161750.c` | 533 | 103 | 170 | CPU player: returns the bite button (bit 15) and steers ep->cpuHeading at the nearest slice pixel of its target cell, or at the nearest non-empty cell around it... |
| `func_8010E6F0_mgmode` | `src/overlays/mgmode/473130.c` | 539 | 103 | 183 | register allocation (retail spills n and keeps the model-array bases in s7/s8), 5 instructions over. |
| `func_80106BD0_mgenter` | `src/overlays/mgenter/468AC0.c` | 983 | 103 | 320 | register allocation (masked 103): retail keeps prev in $fp, this spills it to the stack (frame +8) minigame 0x46: three character models on a turntable and the ... |
| `func_8010D1D8_aces_high` | `src/overlays/ovl_17_aces_high/1C4280.c` | 391 | 104 | 188 | 17 instructions longer than here: retail reloads the goal entry and addresses the scissor table as %lo(table+offset) for each store (here one base, +offset; sam... |
| `func_80108A4C_pipe_cleaners` | `src/overlays/ovl_27_pipe_cleaners/22E100.c` | 396 | 108 | 132 | Score display: grows in, rolls random digits, shows the score, fades. |
| `func_80106A6C_pump_pump_away` | `src/overlays/ovl_0D_pump_pump_away/16F670.c` | 682 | 110 | 515 |  |
| `func_8011485C_duel03` | `src/overlays/duel03/3FE1F0.c` | 357 | 112 | 160 | board db3: logic checked against the asm; masked 112 (357 vs 342 instructions): the shared tails (same space, roll 3/7/9 power test, front partner 10) are laid ... |
| `func_80119DB0_w02` | `src/overlays/w02/335610.c` | 1422 | 113 | 207 | Reads a player motion id from the resident motion table: the u16 low half of word `n` of D_80101734_shared_board[0]. |
| `func_8010C994_chancetime` | `src/overlays/chancetime/487F50.c` | 387 | 115 | 174 | retail reads the position and size as u16 and keeps the clipped bounds in a stack array; the display list and clipping were checked word by word against the asm |
| `func_80115B18_duel03` | `src/overlays/duel03/3FE1F0.c` | 342 | 117 | 158 | board db3: logic checked against the asm (func_8011485C_duel03 with the regions moved; the 7-13 region has no HP or power test): same residue family, masked 117... |
| `func_80113CEC_duel02` | `src/overlays/duel02/3EC590.c` | 650 | 119 | 136 | board da4: logic checked block by block against the asm; 579 vs 592 instructions: GCC store-flags and cross-jumps some bool tails (case 1 turn test and roll, ca... |
| `func_80114B94_duel02` | `src/overlays/duel02/3EC590.c` | 651 | 119 | 136 | board da4: func_80113CEC_duel02's decision with the links' roles exchanged (0<->1, 2<->3) and roll limits of 6; logic checked block by block against the asm (m2... |
| `func_8002A358_main` | `src/22EB0.c` | 730 | 121 | 200 | MP2 func_80035FBC_36BBC is NON_MATCHING the same way: GCC turns the 64-bit combine if/else pairs into default-then-override and shares render-mode tails that re... |
| `func_8010BD1C_mpiq` | `src/overlays/ovl_21_mpiq/204F90.c` | 475 | 123 | 252 | Open the answers window ("A/B/C"): numbers, times and distances are printed into the inserts. |
| `func_800308C0_main` | `src/30C40.c` | 692 | 126 | 462 | Logic checked against the asm block by block. Not matching (masked 126, 672 vs 692): retail saves s0 to hold -0x100 (frame 8) and ORs the nibble/byte sign masks... |
| `func_8010A184_mpiq` | `src/overlays/ovl_21_mpiq/204F90.c` | 798 | 128 | 257 | The right answer of question q (D_8010D010_mpiq) and its answer-format flags. |
| `func_8010BEF8_msetup` | `src/overlays/msetup/506F20.c` | 906 | 129 | 171 | Register allocation only: retail keeps the model and character in s1/s2 across the first calls (GCC here reloads them from their spill slots, 8 bytes higher), a... |
| `func_801167B8_msetup` | `src/overlays/msetup/506F20.c` | 597 | 131 | 220 | State: the 1P/2P team choice on two lifts (only offered with 2+ players): work->unk4 is the choice, D_8011A0B8_msetup[choice] the human count it stands for; B a... |
| `func_80109160_marios_puzzle_party` | `src/overlays/ovl_1F_marios_puzzle_party/1F3B90.c` | 336 | 132 | 196 | The special piece lands on a column: squash the first two-block piece under it, push the blocks above down, then turn it into a single block and close the gap. |
| `func_80107A48_picking_panic` | `src/overlays/ovl_0F_picking_panic/181950.c` | 2491 | 137 | 384 |  |
| `func_80109370_etch_n_catch` | `src/overlays/ovl_12_etch_n_catch/19CEF0.c` | 297 | 141 | 121 | Removes trail node `node` (drawn with value v) from the grid: unlinks it from its trail, then re-derives the marks of its 8 neighbours (v * 2 next to a v cell, ... |
| `func_80106A64_etch_n_catch` | `src/overlays/ovl_12_etch_n_catch/19CEF0.c` | 1445 | 143 | 191 | A player each frame: drop-in during the intro; then pen input (CPU or stick, turn-limited), collisions with the pen tips pushed out, pen model, and in play the ... |
| `func_80107880_marios_puzzle_party` | `src/overlays/ovl_1F_marios_puzzle_party/1F3B90.c` | 225 | 147 | 237 | Clear the garbage blocks (colour 6) next to a cleared block. |
| `func_80106D24_tidal_toss` | `src/overlays/ovl_0A_tidal_toss/15C310.c` | 1606 | 148 | 287 | Draw hook of the water model. The first three calls build it: the faces sorted front to back, their vertices merged into one buffer, then one display list of gS... |
| `func_80108BE0_hide_and_sneak` | `src/overlays/ovl_06_hide_and_sneak/137C00.c` | 663 | 152 | 152 |  |
| `func_80107798_treadmill_grill` | `src/overlays/ovl_15_treadmill_grill/1B4F10.c` | 993 | 152 | 319 | CPU control hook (slot 0). Logic checked against the asm (branch counts equal; n64nmcmp FIELDS differ only by label offset). 31 instructions long: retail keeps ... |
| `func_80106900_slapdown` | `src/overlays/ovl_2E_slapdown/264B80.c` | 1151 | 153 | 216 | One player. ent->unk04 its current motion, unk06 slap order (0 none, 1.. waiting, 99 slapped, * 100 done), unk08 arrival order, unk0A slap time (-1 slapped too ... |
| `func_80111650_msetup` | `src/overlays/msetup/506F20.c` | 1300 | 153 | 302 | Character select lift (state of func_80117820_msetup): the board's eight character slots, one func_80110954_msetup cursor process per human player (then one for... |
| `func_8010ACD8_river_raiders` | `src/overlays/ovl_09_river_raiders/1542E0.c` | 1132 | 159 | 202 | A released river object (work[1]: 0 a coin, 1 a coin bag, 2 a whirlpool) moving downstream: coins and bags * steer around the objects ahead of them and go faste... |
| `func_8010A8E4_mgmode` | `src/overlays/mgmode/46CC10.c` | 538 | 163 | 161 | retail re-sign-extends the minigame type at every use and orders the counter loops differently; logic checked against the asm |
| `func_8010811C_snowball_summit` | `src/overlays/ovl_28_snowball_summit/232A10.c` | 2212 | 163 | 170 | The CPU's stick and buttons: dodge snowballs, roll at the players, wander. scheduling: retail loads 348100.0f before the x*x + z*z sum (one nop more here), then... |
| `func_80108DE8_ridiculous_relay` | `src/overlays/ovl_07_ridiculous_relay/13E9C0.c` | 2457 | 165 | 584 |  |
| `func_8010A908_bowser_toss` | `src/overlays/ovl_34_bowser_toss/291020.c` | 320 | 169 | 174 | retail keeps only 500.0 and 0.0f in registers and reloads the other double constants per use; * its frame spills the row index (it re-indexes D_8010F324 in the ... |
| `func_80106E84_picking_panic` | `src/overlays/ovl_0F_picking_panic/181950.c` | 925 | 176 | 299 |  |
| `func_8008B300_main` | `src/8BF00.c` | 237 | 184 | 220 | func_8008B0E0_main built straight into the fixed-point Mtx: rotation of angle degrees whose local z axis is turned onto dir (normalised here); the nine s15.16 e... |
| `func_80106C60_messy_memory` | `src/overlays/ovl_1D_messy_memory/1E37C0.c` | 1097 | 205 | 343 | A human player's hand in the putting-back phase: Z toggles the board, A picks up or puts down, the stick moves. |
| `func_801097AC_thwomp_pull` | `src/overlays/ovl_08_thwomp_pull/14A810.c` | 1740 | 216 | 505 |  |
| `func_8010C3E4_option` | `src/overlays/option/5334D0.c` | 1330 | 231 | 355 | Records board: per-page counts and one record per character, paged with left/right until B. |
| `func_800E7F60_minigame` | `src/overlays/minigame/BA4B0.c` | 1104 | 232 | 473 | register allocation and stack layout (frame 16 bytes larger); the command switch compiles to a compare tree without retail's case 0 test |
| `func_8010D5B0_option` | `src/overlays/option/5334D0.c` | 1330 | 232 | 356 | The second records board (func_8010C3E4_option with the table at GwCommon.unk_1D + 0x38). |
| `func_80109718_popgun_pickoff` | `src/overlays/ovl_32_popgun_pickoff/283060.c` | 609 | 239 | 314 | Builds a billboard's display list: palette, then one texture load and two triangles per strip. |
| `func_80113C7C_duel05` | `src/overlays/duel05/426450.c` | 543 | 240 | 273 | board dc3: logic checked against the asm case by case; masked ~240: retail cross-jumps the repeated partner tests between cases and keeps branches where this C ... |
| `func_80114428_duel05` | `src/overlays/duel05/426450.c` | 543 | 240 | 273 | board dc3: logic checked against the asm case by case; masked ~240: retail cross-jumps the repeated partner tests between cases and keeps branches where this C ... |
| `func_80113CAC_duel01` | `src/overlays/duel01/3D8AC0.c` | 779 | 242 | 292 | duel b4: logic checked branch by branch against the asm; masked ~240: operand load order and register choice in the repeated power-vs-HP tests (759 vs 779 instr... |
| `func_801096C0_mpiq` | `src/overlays/ovl_21_mpiq/204F90.c` | 714 | 244 | 344 | Can question idx be asked (for question q)? Checks the save's unlocks and records and the board state; picks the boards a board question names. |
| `func_801097D4_stacked_deck` | `src/overlays/ovl_2A_stacked_deck/240A10.c` | 3022 | 254 | 650 |  |
| `func_80117A3C_msetup` | `src/overlays/msetup/506F20.c` | 1369 | 256 | 488 | Story-mode setup page process (user_data a MsStoryWork from func_80118D48_msetup; id 0-2): two sprite groups (and a shadow group on page 0) and two models that ... |
| `opDemoEvent` | `src/overlays/opening/523FD0.c` | 10450 | 261 | 878 |  |
| `func_80108AA0_all_fired_up` | `src/overlays/ovl_29_all_fired_up/23C8F0.c` | 836 | 263 | 316 | masked 234 of 836: retail keeps the nearest flame (a Vec at sp+0x14), the try count and the stick speed in the frame (0x98) and hoists the player position out o... |
| `func_80107C88_messy_memory` | `src/overlays/ovl_1D_messy_memory/1E37C0.c` | 3403 | 267 | 460 | A CPU player's brain in the putting-back phase: walks to items and slots on its board (D_80111700[p]). |
| `func_8010CD00_modesel` | `src/overlays/modesel/4F7E90.c` | 987 | 269 | 293 | 909 of 987 instructions: GCC cross-jumps the identical prompt tails of cases 7 and 8 and keeps the refusal message in a variable, where retail keeps separate co... |
| `func_80109C00_picking_panic` | `src/overlays/ovl_0F_picking_panic/181950.c` | 1616 | 296 | 487 |  |
| `func_80108F0C_storyresult` | `src/overlays/storyresult/54F360.c` | 1482 | 303 | 543 | register allocation (retail keeps `color` in s8 and spills `info` and `page`, reloading them at every use; this C keeps `page` in s8), so the ROM differs in raw... |
| `func_801087BC_vine_with_me` | `src/overlays/ovl_31_vine_with_me/276470.c` | 2689 | 331 | 567 | https: decomp.me/scratch/mEGSE m1 lf1: draws the vine layers (tiled CI textures scrolled by D_801155D8) and the two players' end tiles. Layer arrays are indexed... |
| `func_8008B840_main` | `src/8C440.c` | 341 | 344 | 427 | dst = src rotated by angle degrees about x (rows 1 and 2 mixed, row 0 kept, the translation row copied as is), all in fixed point. src and dst may be the same m... |
| `func_8010ACC4_duelresult` | `src/overlays/duelresult/45A700.c` | 1172 | 344 | 722 | duel r2: NON_MATCHING, masked 341 (1227 vs 1172): retail computes the spark arguments in a different order and keeps work in s4 (spilled here). Call sequence an... |
| `func_8010BE14_boardresult` | `src/overlays/boardresult/3BFA00.c` | 1172 | 344 | 722 | event e8: NON_MATCHING, masked 341 (1227 vs 1172): retail computes the spark arguments in a different order and keeps work in s4 (spilled here). Call sequence a... |
| `func_8008BF20_main` | `src/8CB20.c` | 333 | 347 | 364 | dst = src rotated by angle degrees about y (rows 0 and 2 mixed, row 1 kept, the translation row copied as is), all in fixed point. src and dst may be the same m... |
| `func_8008C5E0_main` | `src/8D1E0.c` | 339 | 362 | 423 | dst = src rotated by angle degrees about z (rows 0 and 1 mixed, row 2 kept, the translation row copied as is), all in fixed point. src and dst may be the same m... |
| `func_8010DF34_staff` | `src/overlays/staff/542220.c` | 1191 | 380 | 833 | masked 380 (1245 vs 1191), duelresult's func_8010ACC4 with a different wait and an exit: retail computes the spark arguments in a different order and keeps work... |
| `func_80106D4C_ridiculous_relay` | `src/overlays/ovl_07_ridiculous_relay/13E9C0.c` | 2397 | 387 | 1303 |  |
| `func_8010AF08_merry_go_chomp` | `src/overlays/ovl_2D_merry_go_chomp/25E110.c` | 1060 | 428 | 653 | same ops and calls; retail lays the cases out with different cross-jumps (case 2 shares case 6's tail) |
| `func_80106BC8_stacked_deck` | `src/overlays/ovl_2A_stacked_deck/240A10.c` | 2527 | 458 | 719 |  |
| `func_80108E8C_awful_tower` | `src/overlays/ovl_25_awful_tower/21E010.c` | 4644 | 501 | 894 |  |
| `func_80107360_toadstool_titan` | `src/overlays/ovl_16_toadstool_titan/1BA850.c` | 4825 | 510 | 1139 | register allocation, stack layout and scheduling (frame 0x130, obj spilled); logic checked block by block |
| `func_8010AF88_thwomp_pull` | `src/overlays/ovl_08_thwomp_pull/14A810.c` | 4789 | 590 | 1575 |  |
| `func_8010AD20_marios_puzzle_party` | `src/overlays/ovl_1F_marios_puzzle_party/1F3B90.c` | 2532 | 633 | 1090 | One player's game: show the next piece, drop garbage rows sent by the others, move the next piece into the well, then let the player (or the CPU) steer and drop... |
| `func_8010B908_picking_panic` | `src/overlays/ovl_0F_picking_panic/181950.c` | 3462 | 678 | 1093 |  |
| `func_8010BD2C_toadstool_titan` | `src/overlays/ovl_16_toadstool_titan/1BA850.c` | 3651 | 782 | 1457 | register allocation and stack layout (frame 0x178, more spills in retail); logic checked block by block |
| `func_801159F8_duel01` | `src/overlays/duel01/3D8AC0.c` | 729 | 970 | 1096 | duel b5: COM decision: which route-3 gate to take (m2c structure; logic checked against the asm) |
| `func_8010B4A8_ridiculous_relay` | `src/overlays/ovl_07_ridiculous_relay/13E9C0.c` | 7106 | 1152 | 2046 |  |
| `func_801147FC_duel01` | `src/overlays/duel01/3D8AC0.c` | 1147 | 1429 | 1578 | duel b7: m2c-derived, block order differs from retail (masked ~1450 of 1147). Logic checked by running retail and this build in a MIPS interpreter on 15000 rand... |
| `func_80116484_duel01` | `src/overlays/duel01/3D8AC0.c` | 1124 | 1431 | 1681 | duel b5: COM decision (m2c structure; logic checked against the asm) |

## Assembly only (not decompiled yet)

| function | file | instr |
|---|---|--:|
| `__osDevMgrMain` | `src/737E0.c` | 0 |
| `__osPiCrateAccessQueue` | `src/737E0.c` | 0 |
| `__osPiGetAccess` | `src/737E0.c` | 0 |
| `__osPiRelAccess` | `src/737E0.c` | 0 |
| `_decodeChunk` | `src/73F40.c` | 0 |
| `_init_lpfilter` | `src/73F40.c` | 0 |
| `alAdpcmPull` | `src/73F40.c` | 0 |
| `alAuxBusNew` | `src/73F40.c` | 0 |
| `alEnvmixerNew` | `src/73F40.c` | 0 |
| `alFxNew` | `src/73F40.c` | 0 |
| `alLoadNew` | `src/73F40.c` | 0 |
| `alLoadParam` | `src/73F40.c` | 0 |
| `alMainBusNew` | `src/73F40.c` | 0 |
| `alRaw16Pull` | `src/73F40.c` | 0 |
| `alResampleNew` | `src/73F40.c` | 0 |
| `alSaveNew` | `src/73F40.c` | 0 |
| `osAiGetLength` | `src/73E10.c` | 0 |
| `osAiSetFrequency` | `src/73E10.c` | 0 |
| `osAiSetNextBuffer` | `src/73F40.c` | 0 |
| `osCartRomInit` | `src/737E0.c` | 0 |
| `__rmonHitCpuFault` | `src/2.0L/rmon/rmonbrk.c` | 11 |
| `__rmonCopyWords` | `src/2.0L/rmon/rmonmem.c` | 12 |
| `__rmonMemcpy` | `src/2.0L/rmon/rmonmem.c` | 12 |
| `osWritebackDCacheAll` | `src/2.0L/os/writebackdcacheall.c` | 12 |
| `__rmonGetExceptionStatus` | `src/2.0L/rmon/rmonbrk.c` | 15 |
| `__rmonReadWordAt` | `src/2.0L/rmon/rmonmem.c` | 16 |
| `__rmonWriteWordTo` | `src/2.0L/rmon/rmonmem.c` | 16 |
| `__rmonGetRegionCount` | `src/2.0L/rmon/rmonmem.c` | 21 |
| `__rmonListProcesses` | `src/2.0L/rmon/rmonmem.c` | 22 |
| `__rmonThreadStatus` | `src/2.0L/rmon/rmontask.c` | 22 |
| `__rmonGetTCB` | `src/2.0L/rmon/rmontask.c` | 25 |
| `__rmonMaskIdleThreadInts` | `src/2.0L/rmon/rmontask.c` | 26 |
| `__rmonGetRegisterContents` | `src/2.0L/rmon/rmonregs.c` | 31 |
| `__rmonExecute` | `src/2.0L/rmon/rmoncmds.c` | 32 |
| `osInvalICache` | `src/2.0L/os/invalicache.c` | 32 |
| `osWritebackDCache` | `src/2.0L/os/writebackdcache.c` | 32 |
| `__rmonGetFRegisters` | `src/2.0L/rmon/rmonregs.c` | 35 |
| `__rmonHitSpBreak` | `src/2.0L/rmon/rmonbrk.c` | 35 |
| `__rmonSetFRegisters` | `src/2.0L/rmon/rmonregs.c` | 35 |
| `osInvalDCache` | `src/2.0L/os/invaldcache.c` | 44 |
| `__rmonGetExeName` | `src/2.0L/rmon/rmonmem.c` | 47 |
| `rmonGetRcpRegister` | `src/2.0L/rmon/rmonregs.c` | 53 |
| `__rmonGetGRegisters` | `src/2.0L/rmon/rmonregs.c` | 54 |
| `__rmonHitBreak` | `src/2.0L/rmon/rmonbrk.c` | 55 |
| `__rmonStopUserThreads` | `src/2.0L/rmon/rmontask.c` | 58 |
| `__rmonSetGRegisters` | `src/2.0L/rmon/rmonregs.c` | 60 |
| `__rmonListThreads` | `src/2.0L/rmon/rmontask.c` | 63 |
| `__rmonClearBreak` | `src/2.0L/rmon/rmonbrk.c` | 71 |
| `__rmonSetSRegs` | `src/2.0L/rmon/rmonregs.c` | 91 |
| `__rmonReadMem` | `src/2.0L/rmon/rmonmem.c` | 92 |
| `__rmonSetBreak` | `src/2.0L/rmon/rmonbrk.c` | 94 |
| `__rmonGetRegions` | `src/2.0L/rmon/rmonmem.c` | 99 |
| `__rmonGetSRegs` | `src/2.0L/rmon/rmonregs.c` | 102 |
| `__rmonSetSingleStep` | `src/2.0L/rmon/rmonbrk.c` | 107 |
| `__rmonSetVRegs` | `src/2.0L/rmon/rmonregs.c` | 109 |
| `__rmonStopThread` | `src/2.0L/rmon/rmontask.c` | 109 |
| `__rmonGetThreadStatus` | `src/2.0L/rmon/rmontask.c` | 118 |
| `__rmonGetVRegs` | `src/2.0L/rmon/rmonregs.c` | 118 |
| `__rmonGetBranchTarget` | `src/2.0L/rmon/rmonbrk.c` | 120 |
| `rmonFindFaultedThreads` | `src/2.0L/rmon/rmonbrk.c` | 130 |
| `__rmonWriteMem` | `src/2.0L/rmon/rmonmem.c` | 137 |
| `__rmonRunThread` | `src/2.0L/rmon/rmontask.c` | 143 |
| `__LeoBootGame2` | `src/72750.c` | 229 |
