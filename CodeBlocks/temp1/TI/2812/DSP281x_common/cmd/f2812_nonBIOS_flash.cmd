/**********************************************************************
* File: f2812.cmd -- Linker command file for Boot to Flash bootmode.
* History: 09/08/03 - original (based on DSP28 header files v1.00, D. Alter)
*          02/14/05 - made consistent with DSP/BIOS linkage allocation (D. Alter)
**********************************************************************/

MEMORY
{
PAGE 0:    /* Program Memory */
   ZONE0       : origin = 0x002000, length = 0x002000     /* XINTF zone 0 */
   ZONE1       : origin = 0x004000, length = 0x002000     /* XINTF zone 1 */
   /*ZONE2       : origin = 0x080000, length = 0x080000     /* XINTF zone 2 */
   ZONE6       : origin = 0x100000, length = 0x080000     /* XINTF zone 6 */
   OTP         : origin = 0x3D7800, length = 0x000400     /* on-chip OTP */
   /*FLASH_IJ    : origin = 0x3D8000, length = 0x002000     /* on-chip FLASH */
   /*FLASH_GH    : origin = 0x3DA000, length = 0x012000	  /*length = 0x008000     /* on-chip FLASH */
   /*FLASH_EF    : origin = 0x3E4000, length = 0x008000   /* on-chip FLASH */
   /*FLASH_EJ    : origin = 0x3D8000, length = 0x014000   /* on-chip FLASH */
   /*FLASH_CD    : origin = 0x3EC000, length = 0x007FFE     /* on-chip FLASH */
   FLASH_CJ    : origin = 0x3D8000, length = 0x01BD00     /* on-chip FLASH */
   CODE_START1 : origin = 0x3F3FFE, length = 0x000002	  /* App Program Start Addr */ 
   FLASH_AB    : origin = 0x3F4000, length = 0x003F00     /* on-chip FLASH, Reserved for boot program 2010-12-21 */	
   JUDGE       : origin = 0x3F7F00, length = 0x00007E
   BOOT_START  : origin = 0x3F7F7E, length = 0x000002	  /* Boot Program Code Start */		 
   CSM_RSVD    : origin = 0x3F7F80, length = 0x000076     /* Part of FLASHA.  Reserved when CSM is in use. */
   BEGIN_FLASH : origin = 0x3F7FF6, length = 0x000002     /* Part of FLASHA.  Used for "boot to flash" bootloader mode. */
 
   PASSWORDS   : origin = 0x3F7FF8, length = 0x000008     /* Part of FLASHA.  CSM password locations. */
/* BEGIN_H0    : origin = 0x3F8000, length = 0x000002        Part of H0.  Used for "boot to H0" bootloader mode. */
   L0SARAM_1   : origin = 0x008000, length = 0x000400     /* 4Kw L0 SARAM. */
/* ZONE7       : origin = 0x3FC000, length = 0x003FC0     /* XINTF zone 7 available if MP/MCn=1 */ 
   BOOTROM     : origin = 0x3FF000, length = 0x000FC0     /* boot ROM available if MP/MCn=0 */
   RESET       : origin = 0x3FFFC0, length = 0x000002     /* part of boot ROM (MP/MCn=0) or XINTF zone 7 (MP/MCn=1) */
   VECTORS     : origin = 0x3FFFC2, length = 0x00003E     /* part of boot ROM (MP/MCn=0) or XINTF zone 7 (MP/MCn=1) */

   SYSTEM      : origin = 0x3F3D00, length = 0x000200

PAGE 1 :   /* Data Memory */
   M0SARAM     : origin = 0x000000, length = 0x000400     /* 1Kw M0 SARAM */
   M1SARAM     : origin = 0x000400, length = 0x000400     /* 1Kw M1 SARAM */
   H0SARAM     : origin = 0x3F8000, length = 0x002000     /* 8Kw H0 SARAM */
   
   /*L0SARAM_2   : origin = 0x008400, length = 0x000800     /* 4Kw L0 SARAM */
   /*L0SARAM_3   : origin = 0x008E00, length = 0x000A00     /* 4Kw L0 SARAM */
   /*L1SARAM	   : origin = 0x009800, length = 0x000800     /* 4Kw L1 SARAM */
   L1SARAM	   : origin = 0x008400, length = 0x001C00     /* 4Kw L1 SARAM */
   ZONE2_1     : origin = 0x080000, length = 0x002000     /* 4/256Kw XINTF zone 2 */
   ZONE2_2     : origin = 0x082000, length = 0x002000     /* 4/256Kw XINTF zone 2 */
   ZONE2_3     : origin = 0x084000, length = 0x002000     /* 32/256Kw XINTF zone 2 */
   ZONE2_4     : origin = 0x086000, length = 0x004000     /* 32/256Kw XINTF zone 2 */
   ZONE2_5     : origin = 0x08A000, length = 0x002000     /* 32/256Kw XINTF zone 2 */
}

SECTIONS
{
/*** Compiler Required Sections ***/
  /* Program memory (PAGE 0) sections */
   .text             : > FLASH_CJ,         PAGE = 0
   .cinit            : > FLASH_CJ,         PAGE = 0
   .const            : > FLASH_CJ,         PAGE = 0
   .econst           : > FLASH_CJ,         PAGE = 0
   .pinit            : > FLASH_CJ,         PAGE = 0
   .reset            : > RESET,            PAGE = 0, TYPE = DSECT  /* We are not using the .reset section */
   .switch           : > FLASH_CJ,         PAGE = 0

  /* Data Memory (PAGE 1) sections */
   .bss              : > H0SARAM,          PAGE = 1
   .ebss             : > H0SARAM,          PAGE = 1
   .cio              : > M0SARAM,          PAGE = 1
   .stack            : > M1SARAM,          PAGE = 1
   .sysmem           : > M0SARAM,          PAGE = 1
   .esysmem          : > M0SARAM,          PAGE = 1

/*** User Defined Sections ***/
   codestart         : > BEGIN_FLASH,      PAGE = 0                /* Used by file CodeStartBranch.asm */
   codestart1        : > CODE_START1,      PAGE = 0
   judge             : > JUDGE,		       PAGE = 0
   csm_rsvd          : > CSM_RSVD,         PAGE = 0                /* Used by file passwords.asm */
   passwords         : > PASSWORDS,        PAGE = 0                /* Used by file passwords.asm */
   system            : > SYSTEM,     	   PAGE = 0  
   ramfuncs          :   LOAD = FLASH_CJ,  PAGE = 0                /* Used by InitFlash() in SysCtrl.c */ 
                         RUN  = L0SARAM_1,   PAGE = 0
                         LOAD_START(_RamFuncs_loadstart),
                         LOAD_END(_RamFuncs_loadend),
                         RUN_START(_RamFuncs_runstart)
   EtherCATBuffer	 : > M0SARAM			PAGE = 1  
   
   /*Database          : > L0SARAM_2          PAGE = 1 
   EthernetBuffer	 : > L0SARAM_3          PAGE = 1  
   CANDatabase		 : > L1SARAM			PAGE = 1*/

   CtlObject		 : > L1SARAM			PAGE = 1
   EthernetBuffer    : > ZONE2_1          	PAGE = 1
   CANDatabase		 : > ZONE2_2			PAGE = 1
   Database			 : > ZONE2_3			PAGE = 1
   ECMaster 	 	 : > ZONE2_4			PAGE = 1
   MotorDriveParam	 : > ZONE2_5			PAGE = 1
      /*==========================================================*/
      /* Tables for IQ math functions:                            */
      /*==========================================================*/
      /* For K1 device (no tables in boot ROM), use this:         */
      /*    
      IQmathTables  : load = BOOTROM, PAGE = 0
      */
      /* For F2810/12 devices (with tables in Boot ROM) use this: */
    
      IQmathTables  : load = BOOTROM, type = NOLOAD, PAGE = 0

      /*==========================================================*/
      /* IQ math functions:                                       */
      /*==========================================================*/
      /*IQmath        : load = FLASH_IJ ,   PAGE = 0*/
      IQmath        load = FLASH_CJ,   PAGE = 0 , RUN =L0SARAM_1                         
      					LOAD_START(_RamFuncs_loadstart1),
                         LOAD_END(_RamFuncs_loadend1),
                         RUN_START(_RamFuncs_runstart1)
}

/******************* end of file ************************/
