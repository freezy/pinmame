#ifndef INC_DESOUND
#define INC_DESOUND

#define DE1S_CPUNO 1
#define DE1S_CPUREGION (REGION_CPU1+DE1S_CPUNO)
#define DE1S_ROMREGION (REGION_SOUND1)

extern MACHINE_DRIVER_EXTERN(de1s);

/*-- Sound rom macros --*/
/*-- 32K Sound CPU Rom, 2 X 64K Voice Roms --*/
#define DE1S_SOUNDROM244(n1,chk1,n2,chk2,n3,chk3) \
  SOUNDREGION(0x10000, DE1S_CPUREGION) \
    ROM_LOAD(n1, 0x8000,  0x8000, chk1) \
	SOUNDREGION(0x40000, DE1S_ROMREGION) \
    ROM_LOAD(n2, 0x00000, 0x10000, chk2) \
      ROM_RELOAD(  0x10000, 0x10000) \
    ROM_LOAD(n3, 0x20000, 0x10000, chk3) \
      ROM_RELOAD(  0x30000, 0x10000)

/*-- 32K Sound CPU Rom, 2 X 128K Voice Roms --*/
#define DE1S_SOUNDROM288(n1,chk1,n2,chk2,n3,chk3) \
  SOUNDREGION(0x10000, DE1S_CPUREGION) \
    ROM_LOAD(n1, 0x8000, 0x8000, chk1) \
  SOUNDREGION(0x40000, DE1S_ROMREGION) \
    ROM_LOAD(n2, 0x0000,  0x20000, chk2) \
    ROM_LOAD(n3, 0x20000, 0x20000, chk3)

#define DE2S_CPUNO 1
#define DE2S_CPUREGION (REGION_CPU1+DE2S_CPUNO)
#define DE2S_ROMREGION (REGION_SOUND1)

extern MACHINE_DRIVER_EXTERN(de2as);
extern MACHINE_DRIVER_EXTERN(de2bs);
extern MACHINE_DRIVER_EXTERN(de2cs);
extern MACHINE_DRIVER_EXTERN(de3as);

/*-- Sound rom macros --*/
/* Load 1Mb Rom(128K) to fit into 1Meg Rom Space */
#define DE2S_ROMLOAD2(start, n, chk) \
  ROM_LOAD(n,  start,  0x20000, chk) \
    ROM_RELOAD(start + 0x20000, 0x20000) \
    ROM_RELOAD(start + 0x40000, 0x20000) \
    ROM_RELOAD(start + 0x60000, 0x20000) \
    ROM_RELOAD(start + 0x80000, 0x20000) \
    ROM_RELOAD(start + 0xa0000, 0x20000) \
    ROM_RELOAD(start + 0xc0000, 0x20000) \
    ROM_RELOAD(start + 0xe0000, 0x20000)

/* Load 2Mb Rom(256K) to fit into 1Meg Rom Space  */
#define DE2S_ROMLOAD4(start, n, chk) \
  ROM_LOAD(n,  start,  0x40000, chk) \
    ROM_RELOAD(start + 0x40000, 0x40000)\
    ROM_RELOAD(start + 0x80000, 0x40000)\
    ROM_RELOAD(start + 0xc0000, 0x40000)

/* Load 4Mb Rom(512K) to fit into 1Meg Rom Space */
#define DE2S_ROMLOAD8(start, n, chk) \
  ROM_LOAD(n,  start, 0x80000, chk) \
    ROM_RELOAD(start + 0x80000, 0x80000)

/* Load 8Mb Rom(1024K) */
#define DE2S_ROMLOAD0(start, n, chk) \
  ROM_LOAD(n,  start, 0x100000, chk)

/* 1 X 256Kb(32K) CPU ROM & 2 X 1Mb(128K) SOUND ROM @ U17, U21 */
#define DE2S_SOUNDROM011(u7,chk7, u17,chk17,u21,chk21) \
  SOUNDREGION(0x010000, DE2S_CPUREGION) \
    ROM_LOAD(u7, 0x8000, 0x8000, chk7) \
  SOUNDREGION(0x200000, DE2S_ROMREGION) \
    DE2S_ROMLOAD2(0x000000, u17, chk17) \
    DE2S_ROMLOAD2(0x100000, u21, chk21)

/* 1 X 256Kb(32K) CPU ROM & 1 X 2Mb(256K) SOUND ROM @ U17 &
                            1 X 1Mb(128K) SOUND ROM @ U21    */
#define DE2S_SOUNDROM021(u7,chk7, u17,chk17,u21,chk21) \
  SOUNDREGION(0x010000, DE2S_CPUREGION) \
    ROM_LOAD(u7, 0x8000, 0x8000, chk7) \
  SOUNDREGION(0x200000, DE2S_ROMREGION) \
    DE2S_ROMLOAD4(0x000000, u17, chk17) \
    DE2S_ROMLOAD2(0x100000, u21, chk21)

/* 1 X 256Kb(32K) CPU ROM & 2 X 2Mb(256K) SOUNDS ROM @ U17, U21 */
#define DE2S_SOUNDROM022(u7,chk7, u17,chk17,u21,chk21) \
  SOUNDREGION(0x010000, DE2S_CPUREGION) \
    ROM_LOAD(u7, 0x8000, 0x8000, chk7) \
  SOUNDREGION(0x200000, DE2S_ROMREGION) \
    DE2S_ROMLOAD4(0x000000, u17, chk17) \
    DE2S_ROMLOAD4(0x100000, u21, chk21)

/* 1 X 256Kb(32K) CPU ROM & 1 X 4Mb(512K) SOUND ROM @ U17 &
                            1 X 2Mb(256K) SOUND ROM @ U21    */
#define DE2S_SOUNDROM042(u7,chk7, u17,chk17,u21,chk21) \
  SOUNDREGION(0x010000, DE2S_CPUREGION) \
    ROM_LOAD(u7, 0x8000, 0x8000, chk7) \
  SOUNDREGION(0x200000, DE2S_ROMREGION) \
    DE2S_ROMLOAD8(0x000000, u17, chk17) \
    DE2S_ROMLOAD4(0x100000, u21, chk21)

/* 1 X 512Kb(64K) CPU ROM & 1 X 4Mb(512K) SOUND ROM @ U17 &
                            1 X 2Mb(256K) SOUND ROM @ U21    */
#define DE2S_SOUNDROM142(u7,chk7, u17,chk17,u21,chk21) \
  SOUNDREGION(0x010000, DE2S_CPUREGION) \
    ROM_LOAD(u7, 0x0000, 0x10000, chk7) \
  SOUNDREGION(0x200000, DE2S_ROMREGION) \
    DE2S_ROMLOAD8(0x000000, u17, chk17) \
    DE2S_ROMLOAD4(0x100000, u21, chk21)

/* 1 X 512Kb(64K) CPU ROM & 2 X 4Mb(512K) SOUND ROMS @ U17,U21 */
#define DE2S_SOUNDROM144(u7,chk7, u17,chk17,u21,chk21) \
  SOUNDREGION(0x010000, DE2S_CPUREGION) \
    ROM_LOAD(u7, 0x0000, 0x10000, chk7) \
  SOUNDREGION(0x200000, DE2S_ROMREGION) \
    DE2S_ROMLOAD8(0x000000, u17, chk17) \
    DE2S_ROMLOAD8(0x100000, u21, chk21)

/* 1 X 512Kb(64K) CPU ROM & 3 X 4Mb(512K) SOUND ROMS @ U17,U21,U36 */
#define DE2S_SOUNDROM1444(u7,chk7, u17,chk17,u21,chk21,u36,chk36) \
  SOUNDREGION(0x010000, DE2S_CPUREGION) \
    ROM_LOAD(u7, 0x0000, 0x10000, chk7) \
  SOUNDREGION(0x400000, DE2S_ROMREGION) \
    DE2S_ROMLOAD8(0x000000, u17, chk17) \
    DE2S_ROMLOAD8(0x100000, u21, chk21) \
    DE2S_ROMLOAD8(0x200000, u36, chk36)

/* 1 X 512Kb(64K) CPU ROM & 4 X 4Mb(512K) SOUND ROMS @ U17,U21,U36,U37 */
#define DE2S_SOUNDROM14444(u7,chk7, u17,chk17,u21,chk21,u36,chk36,u37,chk37) \
  SOUNDREGION(0x010000, DE2S_CPUREGION) \
    ROM_LOAD(u7, 0x0000, 0x10000, chk7) \
  SOUNDREGION(0x400000, DE2S_ROMREGION) \
    DE2S_ROMLOAD8(0x000000, u17, chk17) \
    DE2S_ROMLOAD8(0x100000, u21, chk21) \
    DE2S_ROMLOAD8(0x200000, u36, chk36) \
    DE2S_ROMLOAD8(0x300000, u37, chk37)

/* 1 X 512Kb(64K) CPU ROM & 3 X 8Mb(1024K) SOUNDS ROM @ U17, U21, U36 */
#define DE2S_SOUNDROM1888(u7,chk7, u17,chk17,u21,chk21,u36,chk36) \
  SOUNDREGION(0x010000, DE2S_CPUREGION) \
    ROM_LOAD(u7,0x0000,0x10000,chk7) \
  SOUNDREGION(0x400000, DE2S_ROMREGION) \
    DE2S_ROMLOAD0(0x000000,u17,chk17) \
    DE2S_ROMLOAD0(0x100000,u21,chk21) \
    DE2S_ROMLOAD0(0x200000,u36,chk36)

/* AT91 CPU/SND - 1 X 512Kb(64K) CPU ROM & 3 X 8Mb(1024K) SOUNDS ROM @ U17, U21, U36 */
#define DE3S_SOUNDROM1888(u7,chk7, u17,chk17,u21,chk21,u36,chk36) \
  ROM_REGION32_LE(0x600000, DE2S_CPUREGION, ROMREGION_ERASEMASK | ROMREGION_SOUNDONLY) \
    ROM_LOAD("bios.u8", 0x400000, 0x200000, CRC(c049bf99) SHA1(89e76760e8010fe642ed4312732de81c8a25f548))\
	ROM_RELOAD(0x0,0x100000)\
  SOUNDREGION(0x10000, REGION_SOUND1) \
    ROM_LOAD(u7,0x0000,0x10000,chk7) \
  SOUNDREGION(0x400000,REGION_SOUND2) \
    DE2S_ROMLOAD0(0x000000,u17,chk17) \
    DE2S_ROMLOAD0(0x100000,u21,chk21) \
    DE2S_ROMLOAD0(0x200000,u36,chk36)

/* 1 X 512Kb(64K) CPU ROM & 3 X 8Mb(1024K) SOUNDS ROM @ U17, U21, U36 & */
/*                          1 X 4Mb(512K) SOUNDS ROM @ U37 */
#define DE2S_SOUNDROM18884(u7,chk7, u17,chk17,u21,chk21,u36,chk36,u37,chk37) \
  SOUNDREGION(0x010000, DE2S_CPUREGION) \
    ROM_LOAD(u7,0x0000,0x10000,chk7) \
  SOUNDREGION(0x400000, DE2S_ROMREGION) \
    DE2S_ROMLOAD0(0x000000,u17,chk17) \
    DE2S_ROMLOAD0(0x100000,u21,chk21) \
    DE2S_ROMLOAD0(0x200000,u36,chk36) \
    DE2S_ROMLOAD8(0x300000,u37,chk37)

/* 1 X 512Kb(64K) CPU ROM & 4 X 8Mb(1024K) SOUNDS ROM @ U17, U21, U36, U37 */
#define DE2S_SOUNDROM18888(u7,chk7, u17,chk17,u21,chk21,u36,chk36,u37,chk37) \
  SOUNDREGION(0x010000, DE2S_CPUREGION) \
    ROM_LOAD(u7,0x0000,0x10000,chk7) \
  SOUNDREGION(0x400000, DE2S_ROMREGION) \
    DE2S_ROMLOAD0(0x000000,u17,chk17) \
    DE2S_ROMLOAD0(0x100000,u21,chk21) \
    DE2S_ROMLOAD0(0x200000,u36,chk36) \
    DE2S_ROMLOAD0(0x300000,u37,chk37)

//ROM_REGION32_LE(0x600000, DE2S_CPUREGION, ROMREGION_ERASEMASK | ROMREGION_SOUNDONLY)

/* AT91 CPU/SND - 1 X 512Kb(64K) CPU ROM & 4 X 8Mb(1024K) SOUNDS ROM @ U17, U21, U36, U37 */
#define DE3S_SOUNDROM18888(u7,chk7, u17,chk17,u21,chk21,u36,chk36,u37,chk37) \
  ROM_REGION(0x600000, DE2S_CPUREGION, ROMREGION_ERASEMASK | ROMREGION_SOUNDONLY) \
    ROM_LOAD("bios.u8", 0x400000, 0x200000, CRC(c049bf99) SHA1(89e76760e8010fe642ed4312732de81c8a25f548))\
	ROM_RELOAD(0x0,0x100000)\
  SOUNDREGION(0x10000, REGION_SOUND1) \
    ROM_LOAD(u7,0x0000,0x10000,chk7) \
  SOUNDREGION(0x400000,REGION_SOUND2) \
    DE2S_ROMLOAD0(0x000000,u17,chk17) \
    DE2S_ROMLOAD0(0x100000,u21,chk21) \
    DE2S_ROMLOAD0(0x200000,u36,chk36) \
    DE2S_ROMLOAD0(0x300000,u37,chk37)

#endif /* INC_DESOUND */
