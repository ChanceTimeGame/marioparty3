#include "common.h"
#include "PR/os_internal.h"
#include "PR/rcp.h"
#include "PR/R4300.h"
#include "PR/os_version.h"

typedef struct {
    /* 0x0 */ unsigned int inst1;
    /* 0x4 */ unsigned int inst2;
    /* 0x8 */ unsigned int inst3;
    /* 0xC */ unsigned int inst4;
} __osExceptionVector;

extern __osExceptionVector __osExceptionPreamble[];

extern OSPiHandle D_800D09C0_main; // __Dom1SpeedParam
extern OSPiHandle D_800CCEB0_main; // __Dom2SpeedParam
extern OSTime D_800A3FA0_main;     // osClockRate

extern s32 osViClock;
extern void __osSetWatchLo(u32);
extern int __checkHardware_msp(void);
extern int __checkHardware_kmc(void);
extern int __checkHardware_isv(void);
extern void __osInitialize_msp(void);
extern void __osInitialize_kmc(void);
extern void __osInitialize_isv(void);
extern void __osInitialize_emu(void);

#define __Dom1SpeedParam D_800D09C0_main
#define __Dom2SpeedParam D_800CCEB0_main
#define osClockRate D_800A3FA0_main

void __createSpeedParam(void) {
    __Dom1SpeedParam.type = 7;
    __Dom1SpeedParam.latency = IO_READ(PI_BSD_DOM1_LAT_REG);
    __Dom1SpeedParam.pulse = IO_READ(PI_BSD_DOM1_PWD_REG);
    __Dom1SpeedParam.pageSize = IO_READ(PI_BSD_DOM1_PGS_REG);
    __Dom1SpeedParam.relDuration = IO_READ(PI_BSD_DOM1_RLS_REG);

    __Dom2SpeedParam.type = 7;
    __Dom2SpeedParam.latency = IO_READ(PI_BSD_DOM2_LAT_REG);
    __Dom2SpeedParam.pulse = IO_READ(PI_BSD_DOM2_PWD_REG);
    __Dom2SpeedParam.pageSize = IO_READ(PI_BSD_DOM2_PGS_REG);
    __Dom2SpeedParam.relDuration = IO_READ(PI_BSD_DOM2_RLS_REG);
}

void __osInitialize_common(void) {
    u32 pifdata;

    __osSetSR(__osGetSR() | SR_CU1);
    __osSetFpcCsr(FPCSR_FS | FPCSR_EV | FPCSR_RM_RN);
    __osSetWatchLo(0x4900000);

    while (__osSiRawReadIo(PIF_RAM_END - 3, &pifdata)) {
        ;
    }
    while (__osSiRawWriteIo(PIF_RAM_END - 3, pifdata | 8)) {
        ;
    }
    *(__osExceptionVector *)UT_VEC = *__osExceptionPreamble;
    *(__osExceptionVector *)XUT_VEC = *__osExceptionPreamble;
    *(__osExceptionVector *)ECC_VEC = *__osExceptionPreamble;
    *(__osExceptionVector *)E_VEC = *__osExceptionPreamble;
    osWritebackDCache((void *)UT_VEC, E_VEC - UT_VEC + sizeof(__osExceptionVector));
    osInvalICache((void *)UT_VEC, E_VEC - UT_VEC + sizeof(__osExceptionVector));
    __createSpeedParam();
    osUnmapTLBAll();
    osMapTLBRdb();
    osClockRate = osClockRate * 3 / 4;

    if (osResetType == 0) {
        bzero(osAppNMIBuffer, OS_APP_NMI_BUFSIZE);
    }

    if (osTvType == OS_TV_PAL) {
        osViClock = VI_PAL_CLOCK;
    } else if (osTvType == OS_TV_MPAL) {
        osViClock = VI_MPAL_CLOCK;
    } else {
        osViClock = VI_NTSC_CLOCK;
    }

    if (__osGetCause() & CAUSE_IP5) {
        while (TRUE) {
            ;
        }
    }

    IO_WRITE(AI_CONTROL_REG, AI_CONTROL_DMA_ON);
    IO_WRITE(AI_DACRATE_REG, AI_MAX_DAC_RATE - 1);
    IO_WRITE(AI_BITRATE_REG, AI_MAX_BIT_RATE - 1);
}

void __osInitialize_autodetect(void) {
    if (__checkHardware_msp()) {
        __osInitialize_msp();
    } else if (__checkHardware_kmc()) {
        __osInitialize_kmc();
    } else if (__checkHardware_isv()) {
        __osInitialize_isv();
    } else {
        __osInitialize_emu();
    }
}
