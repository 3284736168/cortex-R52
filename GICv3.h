//----------------------------------------------------------------
// Copyright (c) 2016-2023 Arm Limited (or its affiliates). All rights reserved.
// Use, modification and redistribution of this file is subject to your possession of a
// valid End User License Agreement for the Arm Product of which these examples are part of
// and your compliance with all applicable terms and conditions of such license agreement.
//----------------------------------------------------------------

#ifndef GICV3_H_
#define GICV3_H_

struct GICv3_dist_if
{
        volatile uint32_t CTLR;              // +0x0000 - RW - Distributor Control Register
  const volatile uint32_t TYPER;             // +0x0004 - RO - Interrupt Controller Type Register
  const volatile uint32_t IIDR;              // +0x0008 - RO - Distributor Implementer Identification Register

  const volatile uint32_t padding0;          // +0x000C - RESERVED

        volatile uint32_t STATUSR;           // +0x0010 - RW - Error Reporting Status Register

  const volatile uint32_t padding1[3];       // +0x0014 - RESERVED

        volatile uint32_t IMP_DEF[8];        // +0x0020 - RW - Implementation defined registers

        volatile uint32_t SETSPI_NSR;        // +0x0040 - WO - Non-Secure Set SPI Pending (Used when SPI is signalled using MSI)
  const volatile uint32_t padding2;          // +0x0044 - RESERVED
        volatile uint32_t CLRSPI_NSR;        // +0x0048 - WO - Non-Secure Clear SPI Pending (Used when SPI is signalled using MSI)
  const volatile uint32_t padding3;          // +0x004C - RESERVED
        volatile uint32_t SETSPI_SR;         // +0x0050 - WO - Secure Set SPI Pending (Used when SPI is signalled using MSI)
  const volatile uint32_t padding4;          // +0x0054 - RESERVED
        volatile uint32_t CLRSPI_SR;         // +0x0058 - WO - Secure Clear SPI Pending (Used when SPI is signalled using MSI)

  const volatile uint32_t padding5[3];       // +0x005C - RESERVED

  const volatile uint32_t pad;               // +0x0068 - RESERVED

  const volatile uint32_t padding6[5];       // +0x006C - RESERVED

        volatile uint32_t IGROUPR[32];       // +0x0080 - RW - Interrupt Group Registers (Security Registers in GICv1)

        volatile uint32_t ISENABLER[32];     // +0x0100 - RW - Interrupt Set-Enable Registers
        volatile uint32_t ICENABLER[32];     // +0x0180 - RW - Interrupt Clear-Enable Registers
        volatile uint32_t ISPENDR[32];       // +0x0200 - RW - Interrupt Set-Pending Registers
        volatile uint32_t ICPENDR[32];       // +0x0280 - RW - Interrupt Clear-Pending Registers
        volatile uint32_t ISACTIVER[32];     // +0x0300 - RW - Interrupt Set-Active Registers
        volatile uint32_t ICACTIVER[32];     // +0x0380 - RW - Interrupt Clear-Active Registers

        volatile uint8_t  IPRIORITYR[1024];  // +0x0400 - RW - Interrupt Priority Registers
        volatile uint32_t ITARGETSR[256];    // +0x0800 - RW - Interrupt Processor Targets Registers
        volatile uint32_t ICFGR[64];         // +0x0C00 - RW - Interrupt Configuration Registers
        volatile uint32_t IGRPMODR[32];      // +0x0D00 - RW - Interrupt Group Modifier Registers
  const volatile uint32_t padding7[32];      // +0x0D80 - RESERVED
        volatile uint32_t NSACR[64];         // +0x0E00 - RW - Non-Secure Access Control Registers

        volatile uint32_t SGIR;              // +0x0F00 - WO - Software Generated Interrupt Register

  const volatile uint32_t padding8[3];       // +0x0F04 - RESERVED

        volatile uint32_t CPENDSGIR[4];      // +0x0F10 - RW - SGI Clear-Pending Registers
        volatile uint32_t SPENDSGIR[4];      // +0x0F20 - RW - SGI Set-Pending Register

  const volatile uint32_t padding9[52];      // +0x0F30 - RESERVED
  const volatile uint32_t padding10[5120];   // +0x1000 - RESERVED

        volatile uint64_t IROUTER[1024];     // +0x6000 - RW - Controls SPI routing when ARE=1
};

struct GICv3_sgiist_if
{
  const volatile uint32_t padding1[32];      // +0x0000 - RESERVED
        volatile uint32_t IGROUPR0;          // +0x0080 - RW - Interrupt Group Registers (Security Registers in GICv1)
  const volatile uint32_t padding2[31];      // +0x0084 - RESERVED
        volatile uint32_t ISENABLER0;        // +0x0100 - RW - Interrupt Set-Enable Registers
  const volatile uint32_t padding3[31];      // +0x0104 - RESERVED
        volatile uint32_t ICENABLER;         // +0x0180 - RW - Interrupt Clear-Enable Registers
  const volatile uint32_t padding4[31];      // +0x0184 - RESERVED
        volatile uint32_t ISPENDR;           // +0x0200 - RW - Interrupt Set-Pending Registers
  const volatile uint32_t padding5[31];      // +0x0204 - RESERVED
        volatile uint32_t ICPENDR;           // +0x0280 - RW - Interrupt Clear-Pending Registers
  const volatile uint32_t padding6[31];      // +0x0284 - RESERVED
        volatile uint32_t ISACTIVER;         // +0x0300 - RW - Interrupt Set-Active Register
  const volatile uint32_t padding7[31];      // +0x0304 - RESERVED
        volatile uint32_t ICACTIVER;         // +0x0380 - RW - Interrupt Clear-Active Register
  const volatile uint32_t padding8[31];      // +0x0184 - RESERVED
        volatile uint8_t  IPRIORITYR[32];    // +0x0400 - RW - Interrupt Priority Registers
  const volatile uint32_t padding9[504];     // +0x0420 - RESERVED
        volatile uint32_t ICFGR[2];          // +0x0C00 - RW - Interrupt Configuration Registers
  const volatile uint32_t padding10[62];     // +0x0C08 - RESERVED
        volatile uint32_t IGRPMODR;          // +0x0D00 - RW - Interrupt Group Modifier Registers
  const volatile uint32_t padding11[63];     // +0x0D04 - RESERVED
        volatile uint32_t NSACR;             // +0x0E00 - RW - Non-Secure Access Control Register
};

struct GICv3_rdist_if
{
        volatile uint32_t CTLR;             // +0x0000 - RW - Redistributor Control Register
  const volatile uint32_t IIDR;             // +0x0004 - RO - Redistributor Implementer Identification Register
  const volatile uint32_t TYPER[2];         // +0x0008 - RO - Redistributor Type Register
        volatile uint32_t STATUSR;          // +0x0010 - RW - Error Reporting Status Register, optional
        volatile uint32_t WAKER;            // +0x0014 - RW - Redistributor Wake Register
  const volatile uint32_t padding1[10];     // +0x0018 - RESERVED
        volatile uint64_t SETLPIR;          // +0x0040 - WO - Set LPI Pending Register
        volatile uint64_t CLRLPIR;          // +0x0048 - WO - Clear LPI Pending Register
  const volatile uint32_t padding2[8];      // +0x0050 - RESERVED
        volatile uint64_t PROPBASER;        // +0x0070 - RW - Redistributor Properties Base Address Register
        volatile uint64_t PENDBASER;        // +0x0078 - RW - Redistributor LPI Pending Table Base Address Register
  const volatile uint32_t padding4[8];      // +0x0080 - RESERVED
        volatile uint64_t INVLPIR;          // +0x00A0 - WO - Redistributor Invalidate LPI Register
  const volatile uint32_t padding5[2];      // +0x00A8 - RESERVED
        volatile uint64_t INVALLR;          // +0x00B0 - WO - Redistributor Invalidate All Register
  const volatile uint32_t padding6[2];      // +0x00B8 - RESERVED
        volatile uint64_t SYNCR;            // +0x00C0 - RO - Redistributor Synchronize Register
  const volatile uint32_t padding7[2];      // +0x00C8 - RESERVED
  const volatile uint32_t padding8[12];     // +0x00D0 - RESERVED
        volatile uint64_t IMPDEF2;          // +0x0100 - WO - IMPLEMENTATION DEFINED
  const volatile uint32_t padding9[2];      // +0x0108 - RESERVED
        volatile uint64_t IMPDEF3;          // +0x0110 - WO - IMPLEMENTATION DEFINED
  const volatile uint32_t padding10[2];     // +0x0118 - RESERVED
};

// +0 from ITS_BASE
struct GICv3_its_ctlr_if
{
        volatile uint32_t CTLR;             // +0x0000 - RW - ITS Control Register
  const volatile uint32_t IIDR;             // +0x0004 - RO - Implementer Identification Register
  const volatile uint64_t TYPER;            // +0x0008 - RO - ITS Type Register
  const volatile uint32_t padding1[4];      // +0x0010 - RESERVED
        volatile uint32_t IMPDEF[8];        // +0x0020 - RW
  const volatile uint32_t padding2[16];     // +0x0040 - RESERVED
        volatile uint64_t CBASER;           // +0x0080 - RW - ITS Command Queue Descriptor
        volatile uint64_t CWRITER;          // +0x0088 - RW - ITS Write Register
        volatile uint64_t CREADR;           // +0x0090 - RW - ITS Read Register
  const volatile uint32_t padding3[2];      // +0x0098 - RESERVED
  const volatile uint32_t padding4[24];     // +0x00A0 - RESERVED
        volatile uint64_t BASER[8];         // +0x0100 - RW - ITS Translation Table Descriptors
};

// +0x010000 from ITS_BASE
struct GICv3_its_int_if
{
  const volatile uint32_t padding1[16];     // +0x0000 - RESERVED
        volatile uint32_t TRANSLATER;       // +0x0040 - RW - ITS Translation Register
};

#define GICD            (*(volatile struct GICv3_dist_if *)     0xAF000000)
#define ITS             (*(volatile struct GICv3_its_ctlr_if *) 0xAF020000)
#define GICR_RD         (*(volatile struct GICv3_rdist_if *)    0xAF100000)
#define GICR_SGI        (*(volatile struct GICv3_sgiist_if *)   0xAF110000)

#endif /* GICV3_H_ */
