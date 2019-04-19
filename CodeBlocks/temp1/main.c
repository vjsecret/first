#include <stdio.h>
#include <stdlib.h>
#include "IQmathLib.h"
#include <limits.h>
#include "float.h"
//#include "DSP28x_Project.h"
//#include ".\TI\28335\DSP2833x_common\include\DSP28x_Project.h"


#if MATH_TYPE == FLOAT_MATH
#include <math.h>
#endif
/*===========================================================================+
|           Constant                                                         |
+===========================================================================*/
#define     AXIS_MAX            			2
#define     AXIS_CONFIG_NUM     			2

#define		POSITOPRESSCTLEXECMOTION_STOP	0
#define		POSITOPRESSCTLEXECMOTION_KEEP	1
#define		POSITOPRESSCTLEXECMOTION_BACK	2
#define		POSITOPRESSCTLEXECMOTION_FWD	3
/**
 * MOTIONTYPE
 */
#define     MOTIONTYPE_STOPCTRL             0
#define     MOTIONTYPE_RESET                1
#define     MOTIONTYPE_HOMING               2
#define     MOTIONTYPE_JOGPOSICTRL          3
#define     MOTIONTYPE_JOGPRESSCTRL         4
#define     MOTIONTYPE_JOGSPEEDCTRL         5
#define     MOTIONTYPE_POSICTRL             6
#define     MOTIONTYPE_PRESSCTRL_TIME       7
#define     MOTIONTYPE_PRESSCTRL_POSI       8
#define     MOTIONTYPE_SPEEDCTRL            9
#define     MOTIONTYPE_DEPRESSCTRL          10

/**
 * Control CMD definition
 */
#define     CMD_STOPCTL                     0
#define     CMD_RESETCTL                    1
#define     CMD_HOMINGCTL                   2
#define     CMD_JOGPOSITIONTL_POV           3
#define     CMD_JOGPOSITIONTL_NEV           4
#define     CMD_JOGPRESSCTL_POV             5
#define     CMD_JOGPRESSCTL_NEV             6
#define     CMD_JOGSPEEDCTL_POV             7
#define     CMD_JOGSPEEDCTL_NEV             8
#define     CMD_POSITIONCTL_POV             9
#define     CMD_POSITIONCTL_NEV             10
#define     CMD_PRESSCTL_POV                11
#define     CMD_PRESSCTL_NEV                12
#define     CMD_SPEEDCTL_POV                13
#define     CMD_SPEEDCTL_NEV                14
#define     CMD_PRESSCTL_EXTCMD             15 // External CMD
#define		CMD_POSICTL_EXTCMD				16
#define     CMD_MA_MAX                      17

#define     CMD_MO_START                    101
#define     CMD_JOGOPENMOLD                 CMD_MO_START
#define     CMD_JOGCLOSEMOLD                102
#define     CMD_JOGEJECTFWD                 103
#define     CMD_JOGEJECTBWD                 104
#define     CMD_JOGINJECT                   105
#define     CMD_JOGSUCKBACK                 106
#define     CMD_JOGCARRIAGEFWD              107
#define     CMD_JOGCARRIAGEBWD              108
#define     CMD_SLOWCHARGE                  109
#define     CMD_RSVD110                    	110

#define     CMD_OPENMOLD                    111
#define     CMD_CLOSEMOLD                   112
#define     CMD_COINNING                    113
#define     CMD_ADJOPENMOLD                 114

#define     CMD_EJECTFWD                    115
#define     CMD_EJECTBWD                    116
#define     CMD_VIBRATEEJECTFWD             117
#define     CMD_VIBRATEEJECTBWD             118
#define		CMD_AUTOEJECT					119
#define		CMD_RSVD120						120

#define     CMD_INJECT                      121
#define     CMD_BACKPRESS                   122
#define     CMD_PRESUCKBACK                 123
#define     CMD_SUCKBACK                    124
#define     CMD_CONSTSUCKBACK               125
#define		CMD_RSVD126						126
#define     CMD_PUREINJECT                  127
#define     CMD_PURESUCKBACK               	128

#define     CMD_CHARGE                      129
#define		CMD_PURECHARGE					130

#define     CMD_CARRIAGEFWD                 131
#define     CMD_CARRIAGEBWD                 132
#define     CMD_CARRIAGEDEPRESS             133
#define     CMD_MO_MAX                      134

 /**
  * PosiCtl to PressCtl Type.
  */
#define     POSITOPRESSTYPE_NONE            0
#define     POSITOPRESSTYPE_POSI            1
#define     POSITOPRESSTYPE_PRESS           2
#define     POSITOPRESSTYPE_TIME            3
#define     POSITOPRESSTYPE_POSI_TIME       4
#define     POSITOPRESSTYPE_PRESS_TIME      5
#define     POSITOPRESSTYPE_POSI_PRESS      6
#define     POSITOPRESSTYPE_POSI_PRESS_TIME 7
#define     POSITOPRESSTYPE_IO_INPUT		8

#define     POSITOFORCETYPE_NOPROFILE       0
#define     POSITOFORCETYPE_HOLD            1

#define     FORCE_OFFSET                    20
#define     PRESS_OFFSET                    2

#define		POSITOPRESSCTL_INPUT			1
#define		POSITOPRESSCTL_ALARM_OUTPUT		1
/**
 * PosiToPressCtlMode
 */
#define     POSITOPRESSCTLMODE_PRESSTIME    0
#define     POSITOPRESSCTLMODE_JOGPRESS     1
#define     POSITOPRESSCTLMODE_PRESSPOSI    2

/**
 * SLAVESTATE
 */
#define     SLVSTATE_STANDSTILL              0
#define     SLVSTATE_INIT                    1
#define     SLVSTATE_BUSY                    2
#define     SLVSTATE_DONE                    3
#define     SLVSTATE_ERROR                   4

/**
 * Control Source.
 */
#define     CONTROLSOURCE_PLCMASTER         0
#define     CONTROLSOURCE_PC_TEST	        1
#define     CONTROLSOURCE_PC_CMD	        2
/**
 * Prepare State.
 */
#define     PREPARE_RESET					0
#define	    PREPARE_INIT					1
#define	    PREPARE_BUSY					2
#define     PREPARE_DONE					3
/**
 * Stop Mode
 */
#define		STOPCTLMODE_NONE				0
#define		STOPCTLMODE_KEEPPRESS			1
/**
 * PosiCtl Trans Profile Mode.
 */
#define		TRANSPROFILEMODE_TOENDPOSI		0
#define		TRANSPROFILEMODE_TOTRANSPOSI	1
/**
 * Before Trans PressCtl, BwdOption.
 */
#define		TRANSBACKOPTION_AUTOSET			1
#define		TRANSBACKOPTION_USERDEFINE		2
/**
 * Config2 FunctionOption
 */
#define		CONFIG2FUNCTIONOPTION_NONE			0
#define		CONFIG2FUNCTIONOPTION_SPEEDFOLLOW	1
#define		CONFIG2FUNCTIONOPTION_POSITIONSYNC	2
/**
 * Test Anders 2013-3-25.
 */
#ifdef		TEST_DPVALVE_MOLD
#define		CHANNEL_DPVALVE_POV			3
#define		CHANNEL_DPVALVE_NEV			4
#endif


typedef     void    (*PFUNC)();
extern	PFUNC  		g_pFuncCritical;
/*==========================================================================+
|           Function prototype                                    			|
+==========================================================================*/
void 	MainISR(void);
/*===========================================================================+
|           Constant                                                         |
+===========================================================================*/
#define     FALSE               (1 == 0)
#define     TRUE                (1 == 1)
#define     NO                  FALSE
#define     YES                 TRUE
/* define ASCII Control code */
#define     NUL                 0x00    /* Null                 */
#define     SOH                 0x01    /* Start Of Head        */
#define     MD1                 0x01    /*                      */
#define     STX                 0x02    /* Start of TeXt        */
#define     MD2                 0x02    /*                      */
#define     ETX                 0x03    /* End of TeXt          */
#define     MD3                 0x03    /*                      */
#define     BEL                 0x07    /* BELl                 */
#define     BS                  0x08    /* BackSpace            */
#define     HT                  0x09    /* Horizontal Tabulator */
#define     LF                  0x0A    /* Line Feed            */
#define     VT                  0x0B    /* Vertical Tabulator   */
#define     HOM                 0x0B    /*                      */
#define     FF                  0x0C    /* Form Feed            */
#define     CLR                 0x0C    /*                      */
#define     CR                  0x0D    /* Carriage Return      */
#define     CAN                 0x18    /*                      */
#define     ESC                 0x1B    /* ESCape               */
#define     US                  0x1F    /*                      */

/*******
|
*******/
#define     MASK_NULL           0x0000
#define     MASK_BIT00          0x01
#define     MASK_BIT01          0x02
#define     MASK_BIT02          0x04
#define     MASK_BIT03          0x08
#define     MASK_BIT04          0x10
#define     MASK_BIT05          0x20
#define     MASK_BIT06          0x40
#define     MASK_BIT07          0x80
#define     MASK_BIT08          0x0100
#define     MASK_BIT09          0x0200
#define     MASK_BIT10          0x0400
#define     MASK_BIT11          0x0800
#define     MASK_BIT12          0x1000
#define     MASK_BIT13          0x2000
#define     MASK_BIT14          0x4000
#define     MASK_BIT15          0x8000

/*******
|
*******/
#define		DELAY_500			500L
#define		DELAY_1000			1000L

/*******
|
*******/
#define     ID_NULL             0
#define     NULL_ID             ID_NULL
#define     HANDLE_NULL         0
#define     NULL_HANDLE         HANDLE_NULL

/*******
|
*******/
#define		CPUTIMER0_SLICE		1000					// CPU TIMER0 SLICE 1ms: 1000; 0.5ms: 500 zholy080305. Not exeed 1000 !!!
														// If cthis value changes, other config based on cpu timer0 will change at the same time.
#define		TIMER_SCALE			(1000/CPUTIMER0_SLICE)	// 1000 stand for 1ms which is standard.
#define		CPUTIMER0_TIMEMS	(1.0/TIMER_SCALE)		// CPU Timer interrupt time(ms).
/*===========================================================================+
|           Type definition                                                  |
+===========================================================================*/
//typedef     unsigned char       BYTE;   /* 16-Bit */
typedef     unsigned  int       BYTE;   /* 16-Bit */     /*CWLM*/
typedef     unsigned  int 		WORD;   /* 16-Bit */
typedef     int                	INT;   /* 16-Bit */
typedef     WORD                BOOL;   /* 16-Bit */
typedef     long                LONG;   /* 32-Bit */
typedef     unsigned long       DWORD;  /* 32-Bit */
typedef		float				FLOAT;	/* 32-Bit */
typedef		float				TFLOAT;	/* 32-Bit */
typedef		double				DOUBLE;	/* 32-Bit */

typedef     WORD                RTTI;   /* Run Time Type Information       */
typedef     WORD                HANDLE; /* Handle (ID) of object           */

typedef     int                 TINT;   /* Timer unit, must be signed type */

typedef     WORD        		_DA;
typedef     WORD        		_AD;
typedef     WORD        		_TIMER;
typedef     WORD        		_COUNT;
typedef     WORD        		_FLAG;
typedef     DWORD       		_TIMEL;
typedef     DWORD       		_COUNTL;
typedef     DWORD       		_FLAGL;
//typedef		double				TFLOAT;
typedef enum                                      /* boolean */
{
   False = 0x0000,                                /* false */
   True  = 0x0001                                 /* true */
} bool;

typedef float f32;

typedef long s32;

typedef int s16;

typedef unsigned char u8;

typedef unsigned int u16;

typedef unsigned long u32;

// Position to Press.
typedef union tagTPosiToPressCtlMode
{
    WORD    wAll;
    struct
    {
        WORD    bTransType      : 8;
        WORD    bPressCtlType   : 8;
    }bit;
}TPosiToPressCtlMode;
typedef struct tagPosiToPressInfo
{
    WORD                    wOverPressLimitCtlMode;
    WORD                    wCheckPressLimitConfig;

    WORD                    wTransProfileOption;
    TPosiToPressCtlMode     PosiToPressCtlMode;

    DWORD                   dwTransTime;
   _iq                     iqTransPress;

    FLOAT                  	fTransPosition;
	FLOAT                  	fTransVelocity;				// Anders 20121119.
	//FLOAT                  	fTransAccel;				// Anders 20121119.
	FLOAT                  	fTransDecel;				// Anders 20121119.
	DWORD                  	dwTransPreHoldTime;			// Anders 20121119.
	FLOAT					fTransBackVelocity;			// Anders 2013-3-29.
	WORD					wTransBackOption;			// Anders 2013-5-2.
}TPosiToPressInfo;
typedef struct tagPosiToPressController
{
    BOOL                bInitFlag;
    BOOL                bDoPressCtlbyPosiFlag;
    BOOL                bTransPressCtlFlag;
	BOOL				bTransByPosi;				// Anders 2013-6-21.
	BOOL				bCanBwdByPosi;				// Anders 2013-6-24.
    WORD                wExecStep;                  // Anders 20110303. Inject Exec Step.
    WORD               	wExecMotion;

    DWORD               dwExecTime;                 // ms

    TPosiToPressInfo    PosiToPressInfo;
}TPosiToPressController;
// Position to Force.
typedef struct tagPosiToForceInfo
{
    WORD    wTransferMode;
    WORD    wForceCheckTime;                        // ms
}TPosiToForceInfo;
typedef struct tagPosiToForceController
{
    BOOL                bInitFlag;
    BOOL                bTransferForceFlag;
    WORD                wActCheckTime;
    WORD                wState;                     //Anders 20110418.
    DWORD               dwExecTime;
    TPosiToForceInfo    PosiToForceInfo;
}TPosiToForceController;
// Control Protect Info.
typedef struct tagProtectInfo
{
    DWORD   dwPressCheckTime;                       // ms
    DWORD   dwForceCheckTime;                       // ms
	WORD    wDeForceCheckTime;                     // ms, Anders 2011-02-08.

    WORD	wPressLimitOpt;
    WORD	wJogForceLimitOpt;
    WORD	wForceLimitOpt;

	FLOAT	fPressLimit;
    _iq     iqPressLimit;
    _iq     iqJogForceLimit;
    _iq     iqForceLimit;

	_iq		iqDeForceRamp;
	_iq		iqDeForcePercent;

}TProtectInfo;
typedef struct tagProtectController
{
    DWORD   dwExecPressCheckTime;                   // ms
    DWORD   dwExecForceCheckTime;                   // ms
    TProtectInfo    ProtectInfo;
}TProtectController;
typedef struct tagTMonitor
{
	DWORD   dwExecTime;
    DWORD   dwTransTime;
    FLOAT  	fTransPosi;
    FLOAT  	fTransPress;
    FLOAT  	fMaxPress;
    _iq     iqMaxPress;
	FLOAT  	fPosiOfMaxPress;		// Anders 2012-08-21.
	DWORD  	dwTimeOfMaxPress;		// Anders 2012-08-21.
	FLOAT	fMinPosi;
	FLOAT	fMaxPosi;
	DWORD   dwMotionTime;			// Anders 2013-8-12,add.
}TMonitor;
typedef struct tagPID_REG
{
	// PID basis vars
	_iq		Err;				// Variable: Error(Integer)
	_iq		LastErr;			// History: Previous proportional output or "LastErr" OutPreP-->LastErr
	_iq		SumErr;				// Sum error zholy080919
	_iq		Kp;					// Parameter: Proportional gain
	_iq		Ki;					// Parameter: Integral gain
	_iq		Kd;					// Parameter: Derivative gain
	_iq		OutP;				// Variable: Proportional output
	_iq		OutI;				// Variable: Integral output
	_iq		OutD;				// Variable: Derivative output
	_iq		OutPid;				// Output: PID output
	_iq		OutPid0;			// Output: PID output0 (Initialization value)

	// Anti-windup function
	_iq		OutPreSat;			// Variable: Pre-saturated output
	_iq		OutPidMax;			// Parameter: Maximum output
	_iq		OutPidMin;			// Parameter: Minimum output

	void (*pd)(struct tagPID_REG * pid);				// Pointer to calculation function pd
	void (*pid)(struct tagPID_REG * pid);				// Pointer to calculation function pid
    void (*reset)(struct tagPID_REG * pid,_iq,_iq);
    void (*prevpitfall)(struct tagPID_REG * pid,_iq,_iq);
	void (*pid_backpressure)(struct tagPID_REG * pid);
} PIDIQ_REG;
typedef struct tagPIDFLOAT_REG
{
	// PID basis vars
	FLOAT		Err;				// Variable: Error(Integer)
	FLOAT		LastErr;			// History: Previous proportional output or "LastErr" OutPreP-->LastErr
	FLOAT		SumErr;				// Sum error.
	FLOAT		Kp;					// Parameter: Proportional gain
	FLOAT		Ki;					// Parameter: Integral gain
	FLOAT		Kd;					// Parameter: Derivative gain
	FLOAT		OutP;				// Variable: Proportional output
	FLOAT		OutI;				// Variable: Integral output
	FLOAT		OutD;				// Variable: Derivative output
	FLOAT		OutPid;				// Output: PID output
	FLOAT		OutPid0;			// Output: PID output0 (Initialization value)

	// Anti-windup function
	FLOAT		OutPreSat;			// Variable: Pre-saturated output
	FLOAT		OutPidMax;			// Parameter: Maximum output
	FLOAT		OutPidMin;			// Parameter: Minimum output

	void (*pd)(struct tagPIDFLOAT_REG * pid);					// Pointer to calculation function pd
	void (*pid)(struct tagPIDFLOAT_REG * pid);					// Pointer to calculation function pid
    void (*reset)(struct tagPIDFLOAT_REG * pid, FLOAT NewInteg, FLOAT OutPid0);
    void (*prevpitfall)(struct tagPIDFLOAT_REG * pid, FLOAT UMax, FLOAT UMin);
} PIDFLOAT_REG;
//??????
/*
// Control Object's CtlData.
typedef struct tagCONTROLDATA
{
	PIDIQ_REG				    		    PidIQ_PressTimeCtl;
    PIDIQ_REG				    		    PidIQ_PressPosiCtl;
	PIDIQ_REG				    		    PidIQ_DePressCtl;						// Anders 2012-08-16.
    PIDIQ_REG				    		    PidIQ_ForceOverLimitCtl;            	// Anders 2011-02-09.
	PIDFLOAT_REG			    		    PidFloat_PosiCtl;
    // Common Config.
	//TMachMotorParam			    		    MachMotorParam[AXIS_CONFIG_NUM];		// Anders 2013-11-13, add this for Config2.

	SOURCE_ACTDATA			    		    SrcInputParam[AXIS_CONFIG_NUM];
	SOURCE_OUTPUT			    		    SrcOutputParam[AXIS_CONFIG_NUM];

    // Actual Data.
    ACTUAL_DATA     		    		    ActualData[AXIS_CONFIG_NUM];
    TCalActDataController 	    		    CalActDataController[AXIS_CONFIG_NUM];
    CALACT_INOUT                		    CalActInOut[AXIS_CONFIG_NUM];
    // Compute Data.
	COMPUTE_OUTPUT			    		    ComputeOutputData[AXIS_CONFIG_NUM];
    CALSETPOINT_INPUT        		        CalSetpointInput[AXIS_CONFIG_NUM];

    // Jog Position Ctl.
    TJogPosiCtlParam            		    JogPosiCtlParam;
    TJogPosiCtlProfile          		    JogPosiCtlProfile;
	TJogPosiCtlSetpoint		    		    JogPosiCtlSetpoint;
	TJogPosiCtlController	    		    JogPosiCtlController;
	// Position Ctl.
	TPosiCtlParam			    		    PosiCtlParam;
	TPosiCtlProfile			    		    PosiCtlProfile;
	TModeBuffer				    		    PosiCtlModeBuffer;
	TPosiCtlSetpoint		    		    PosiCtlSetpoint;
	TPosiController			    		    PosiCtlController;

    CTLJOGPOSI_INPUT 		    		    JogPosiCtlInput;
    CTLJOGPOSI_OUTPUT 		    		    JogPosiCtlOutput;
    CTLPOSI_INPUT			    		    PosiCtlInput;
    CTLPOSI_OUTPUT			    		    PosiCtlOutput;

    HYBIPOSICTL_CONTROLLER                  HybiPosiCtlController;
    HYBIPOSICTL_INPUT                       HybiPosiCtlInput;
    HYBIPOSICTL_OUTPUT                      HybiPosiCtlOutput;
    // Press Ctl.
    TJogPressController         		    JogPressController;
    TJogPressCtlSetpoint        		    JogPressCtlSetpoint;
    TJogPressCtlSetpoint        		    DePressCtlSetpoint;	// Anders 20130228.
    CTLJOGPRESS_INPUT           		    JogPressCtlInput;

	TPressCtlParam			    		    PressTimeCtlParam;
	TPressCtlParam			    		    PressPosiCtlParam;
	TPressTimeCtlSetpoint	    		    PressTimeCtlSetpoint;
    TPressPosiCtlSetpoint	    		    PressPosiCtlSetpoint;

	//TPressCtlParam							ForceOverLimitCtlParam;         // Force OverLimit
	//TJogPressCtlSetpoint					ForceOverLimitCtlSetpoint;

	TPressTimeController	    		    PressTimeCtlController;
	TPressPosiController    		    	PressPosiCtlController;
    CTLPRESSTIMER_INPUT		    		    PressTimeCtlInput;
    CTLPRESSPOSI_INPUT          		    PressPosiCtlInput;
    CTLPRESS_OUTPUT			    		    PressCtlOutput;

    // Speed Ctl
    TSpeedCtlParam              		    SpeedCtlParam;
    TJogSpeedPosiSetpoint       		    JogSpeedPosiSetpoint;
    TJogSpeedPosiController		   		    JogSpeedPosiController;
    TSpeedPosiSetpoint          		    SpeedPosiSetpoint;

    TSpeedPosiController        		    SpeedPosiController;
    CTLJOGSPEEDPOSI_INPUT       		    JogSpeedPosiCtlInput;
	CTLSPEEDPOSI_INPUT		    		    SpeedPosiCtlInput;
    CTLSPEED_OUTPUT             		    SpeedPosiCtlOutput;

	// Stop Ctl.
    //PIDFLOAT_REG			    		    PidFloat_StopCtl;
    TStopCtlParam			    		    StopCtlParam;
	TStopProfile			    		    StopCtlProfile;
	TStopController			    		    StopCtlController;
    STOP_INPUT                  		    StopCtlInput;
    STOP_OUTPUT                 		    StopCtlOutput;

    // App Info
    //TPosiCtlMoveController	    		    PosiCtlMoveController;
    TPosiToPressController      		    PosiToPressController;
    TProtectController          		    ProtectController[AXIS_CONFIG_NUM];
    TMonitor                                Monitor;
    TMonitor                               Monitor_Backup;
}CONTROLDATA;
*/
typedef union tagDATAUPDATEFLAG
{
    DWORD    all;
    struct
    {
        WORD    bInputOutputParam           : 1;
        WORD   	bMachineParam				: 1;
        WORD	bPosiCtlParam   			: 1;
        WORD	bJogPosiCtlSetpoint			: 1;
        WORD	bPosiCtlSetpoint		    : 1;
        WORD    bPressRange                 : 1;
        WORD    bPressCtlSegmTransType      : 1;
        WORD    bPressTimeCtlParam          : 1;

        WORD    bPressPosiCtlParam          : 1;
        WORD    bJogPressCtlSetpoint     	: 1;
        WORD    bPressTimeCtlSetpoint	    : 1;
        WORD    bPressPosiCtlSetpoint	    : 1;
        WORD    bSpeedCtlParam	            : 1;
        WORD    bJogSpeedCtlSetpoint     	: 1;
        WORD    bSpeedCtlSetpoint        	: 1;

        WORD    bFilterParam              	: 1;
        WORD    bStopCtlParam               : 1;

        WORD    bInputOutputParam_Config2	: 1;	// Config2: Anders 2013-11-8, add.
        WORD   	bMachineParam_Config2		: 1;   	// Config2: Anders 2013-11-8, add.
        WORD    bFilterParam_Config2	    : 1;    // Config2: Anders 2013-11-8, add.
    }bit;
}DATAUPDATEFLAG;
// Anders 2014-5-14 mark for HX.
//typedef union tagTCheckSetPressState
//{
//    WORD    all;
//    struct
//    {
//        WORD    bCheckPressTimeSetpoint     : 1;
//        WORD    bCheckPressPosiSetpoint     : 1;
//    }bit;
//}TCheckSetPressState;
typedef union  tagTMasterCtlCMD
{
    DWORD   all;
    struct
    {
        WORD    wCMD                : 16;   // Bit0~15:     CMD
        WORD    bConfigActive       : 4;    // Bit16~19:    ConfigActive(4bit).
        WORD    bActStep            : 4;    // Bit20~23:    Action Step.
        WORD    bMotorEnable        : 1;    // Bit24:       Motor Enable.
        WORD    bStandstillEnable   : 1;    // Bit25:       Standstill Enable.

        WORD    bRsvd1              : 1;    // Bit26:       Anders 20120213.
        WORD    bRsvd2              : 5;
    }Info;
}TCtlCMD;
typedef union  tagTSlaveState
{
    DWORD   all;
    struct
    {
        WORD    wCMD                : 16;   // Bit0~15:     CMD
        WORD    bState              : 4;    // Bit16~19:    Motion State.
        WORD    bStep               : 4;    // Bit20~23:    Action Step.

        WORD    bUpdate             : 1;    // Bit24:       Data update.
        WORD    bHeartbeet          : 1;    // Bit25:       Heartbeet. 0->1 / 12ms.

        WORD    bSoftPosiLimited	: 1;    // Bit26:       Soft Position Limited, Anders 2014-5-15
        WORD    bRsvd2              : 1;    // Bit27:       ...

        WORD    bMotionType         : 4;    // Bit28~31:    Motion Type.
    }Info;
}TSlaveState;
typedef union  tagTAdditionalFuncCMD
{
    DWORD   all;
    struct
    {
        WORD    wCMD;
        WORD    wData;
    }Info;
}TAdditionalFuncCMD;
// Communicate With Master
typedef struct  tagTLinkController
{
    WORD                    wCheckLinkFlag;
    WORD                    wLinkReady;
    long                    lLinkCouter;
}TLinkController;
typedef struct  tagTSysCycleController
{
    long                    lCycleCounter;
}TSysCycleController;
typedef union tagTDeForceFlag
{
    WORD   all;
    struct
    {
        WORD    bForceLimit         	: 1;
        WORD    bPressLimit     		: 1;
        //WORD    bSpeedFeedBackError  	: 1;
    }bit;
}TDeForceFlag;
typedef struct  tagTPositionningStandstillController    // Positionning Standstill Controller. Anders 20110714.
{
    BOOL                    bStandstillEnable;
    BOOL                    bInitFlag;
    BOOL                    bHoldFlag;
    WORD                    wExecTime;
    WORD                    wStandstillTime;
    FLOAT                  	fTolerance;
    FLOAT                  	fTarget;

    FLOAT                  	fRampVelocity;
}TStandstillController;
typedef struct  tagTExtCMDPressCtl
{
    FLOAT                  	fSetPress;
    FLOAT                  	fSetVelocity;

    //_iq                     iqReverseVelocityLimit;
    FLOAT                  	fReverseTimeLimit;
    FLOAT                  	fReverseMinPress;

    FLOAT                  	fDePressKp;
    // execute.
    FLOAT                  	fExecReverseTime;
}TExtCMDPressCtl;
// Anders 2013-9-22. Add.
typedef struct  tagTExtCMDPosiCtl
{
    WORD                  	wDeltaPIndex;
    WORD                  	wLastDeltaPIndex;

	WORD					i;
	WORD					wStep;
	FLOAT					fV1;
	FLOAT					fV2;

	FLOAT					fP0;
    FLOAT                  	fSum;
	FLOAT					fProfileV;
	FLOAT					fOverLimitV;
	FLOAT					fProfilePosiError;
	FLOAT					fProfileDis;
	_iq						iqProfileSpeed;
}TExtCMDPosiCtl;
typedef struct tagTMERROR
{
//    ERRORENTRY	Entry;
    union
    {
        DWORD   dwAll;
        struct
        {
            WORD    wInfor      : 16;
            WORD    bRsvdL      : 8;
            WORD    bClearType  : 8;
        }info;
    }Detail;
}TMERROR;
typedef struct tagTCANController
{
//    MACHINESTATE_TABLE  MachineState;
    WORD                wAxisBitFlag;   // Bit0~6: Axis1~7
    BOOL                bActive;
    BOOL                bResetCAN;
    WORD                wSDOOperState;  // 0: SDO Upload; 1: SDO Download.
    WORD                wCANObjID;		// From 0.
    BOOL                bHeartbeatReady;            // Anders 20110309.
    WORD                wDeviceType;
    WORD                wAppState;
    TMERROR				Error;
    BOOL                bHomingPositionEanbled;     // 0: Not homing;       1: doing homing position.
    BOOL                bHomingPositionSuccFlag;    // 0: Not Successful.   1: Successful.
    int                 m_nWriteIndex;
    WORD                m_wWriteSuccess;
    int                 m_nReadIndex;
    WORD                m_wReadSuccess;
    int                 m_nScanIndex;
    WORD                m_wScanSuccess;
    BOOL                bEnable;
	BOOL				bClearAlarm;	// Anders 20121116.
	BOOL				bDeForce;		// Anders 2013-6-18, Add. bSiemensDeForce
//    TControlWord        ControlWord;
//    TStatusWord         StatusWord;
    //TStatusWord         StatusWord_Check;	// test. Anders 2013-11-1, At TAIWAN UNIONPLUSTIC.
    LONG               m_lSDOUploadCycleTime;
    LONG                m_lSDODownloadCycleTime;
    //LONG                m_lSDOScanCycleTime;
    LONG                m_lTransmitNMTCycleTime;
    LONG                m_lNodeGuardingCycleTime;
    LONG                m_lPDOCheckCycleTime;  // Anders 20110309.
    INT                	iUploadErrorTimes;
    INT                	iDownloadErrorTimes;
    INT                	iScanErrorTimes;
	WORD				wResetCommuCount;	// Anders 2013-3-14.
	INT					iInitWriteCount;	// Anders 2013-3-26.
    WORD                wSDOTalbeNum;
//    CANODATTR           *pSDOTable;
//    PDOINFO             *pTxPDOMapInfo;
//    PDOINFO             *pRxPDOMapInfo;
//    PDO_BUFFER			TxPDOBuffer[MAX_PDO_COUNT];
//    PDO_BUFFER			RxPDOBuffer[MAX_PDO_COUNT];
//    void    (* pFuncRxPDO[MAX_PDO_COUNT]) (struct tagTCANController *pCANController);
}TCANController;
typedef struct  tagTAxisController
{
    TCtlCMD                 CurrMasterCtlCMD;
    TCtlCMD                 LastMasterCtlCMD;

    TCtlCMD                 BackupMasterCtlCMD;

    TCtlCMD                 InnerCtlCmd;      	// Inner change cmd used.
    TCtlCMD                 CurrExecCtlCmd;		// Execute Control function used.
    TCtlCMD                 LastExecCtlCmd;

    TAdditionalFuncCMD      AdditionalFuncCMD;
    TSlaveState    			SlaveState;

    BOOL                    bSetpointReady;
    WORD                    wRxConfigReady;

    BOOL                    bInitFlag;
    WORD                    wAxisNO;

    WORD                    wDirection;
    WORD                    wLastDirection;     	// Anders 20110127.

    WORD                    wCtlError;          	// Anders 2011-03-18.
    WORD					wResetCount;			// Anders 2013-5-5, Add.
    BOOL					bFreedbackReverse;		// Anders 2013-5-5, Add.
	//BOOL					bDOBackPressCtl;		// Anders 2013-5-5, Add.
    BOOL					bDoPosiStandstill; // Anders 2014-5-14, Add.

    volatile BOOL           bCriticalControl;   	// False: Calulate Setpoints; True: Do Control.
    WORD                    wCycleTime;

    WORD                    wUpdateDBIndex;
    BOOL                    bPressCtlSegmTransType;

	BOOL                    bInitHomingPosi;		// Anders 20120915.
	WORD					wStopCtlMode;			// Anders 20130227.

	WORD					wPrepare;		    	// Anders 20121130.
    WORD					wLastPrepare;			// Anders 20130125.

    WORD                    wControlSource;         // 0:PLC Master; 1:PC.
    WORD                    wHeartbeetCounter;

    FLOAT                  	fHomingPosition;    	// Anders 2011-03-22.

	BOOL					bDriveDeForce;			// Anders 2013-10-9, add.
    TDeForceFlag   			DeForceFlag;

	//TCheckSetPressState 	CheckSetPressState; // Anders 2011-04-27.

    TMERROR		            ErrorController;
    DATAUPDATEFLAG          UpdateFlag;

    TLinkController         LinkController;
    TSysCycleController     SysCycleController;

    TStandstillController   StandstillController;
    TExtCMDPressCtl         ExtCMDPressCtl;
	TExtCMDPosiCtl			ExtCMDPosiCtl;

    void (*pCtlFunc)        (struct tagTAxisController * const pAxisController);
    void (*pTestCtlFunc)    (struct tagTAxisController * const pAxisController);

    WORD                    awActMoveDirection[AXIS_CONFIG_NUM];  		// Used for Position Limit.
    FLOAT  	            	afActMovePosition[AXIS_CONFIG_NUM];   		// Anders 2011-10-13.
    TCANController          *paCANController[AXIS_CONFIG_NUM];
    WORD                    awNodeID[AXIS_CONFIG_NUM];          		// Anders 20120607.
    int                    	anECSlaveIndex[AXIS_CONFIG_NUM];   			// Anders 20120607. From 0.
    WORD                    awECSyncEnabled[AXIS_CONFIG_NUM];  			// Anders 20120607.

	WORD					awConfigSyncMoveOption[AXIS_CONFIG_NUM];	// Anders 2013-11-14, add.
	FLOAT					afConfigPosiSyncKp[AXIS_CONFIG_NUM];		// Anders 2013-11-14, add.
	FLOAT					afConfigPosiSyncKi[AXIS_CONFIG_NUM];		// Anders 2013-11-14, add.
	FLOAT					afConfigPosiSyncTolerance[AXIS_CONFIG_NUM];	// Anders 2013-11-22, add.

//    CONTROLDATA         	CtlData;
} TAxisController;

#define		_AD_PRESCONV				        _IQ12toIQ
#define		_DA_VELOCONV				        _IQtoIQ12

#define     MACHINETYPE_IME                     0
#define     MACHINETYPE_HYBI                    1

#define		AXISTYPE_LINEAR						0
#define		AXISTYPE_ROTARY						1
/*===========================================================================+
|           Type definition                                                  |
+===========================================================================*/
//======
//      Class parameters
//======
typedef struct tagTMachMotorParam
{
	WORD		wCycleTime;			// Anders 2013-11-13,add.
	WORD		wPosiLimitOpt;
    WORD        wDriveType;         // 0: Auston; 1: Simence. Anders 2010-11-01.
    WORD        wMachineType;       // 0: IME; 1: IMO.

	WORD		wAxisType;			// 0: Linear; 1: Rotary.

    DWORD       dwEncoderReso;      // Anders 20120615.
    FLOAT      	fMotorMaxRRM;

	FLOAT		fMotor2Mach;        // Calculate Position Used.
	FLOAT		fMach2Motor;        // Position Control Used.
	FLOAT		fMotor2ObjRPM;      // MotorRPM to ObjectRPM.

	FLOAT      	fPosiZero;          // Position Homming Zero.

	FLOAT		fPosiScale;         // Ruler Length.
    FLOAT      	fRulerReso;         // Ruler resolution, um/CNT.

	FLOAT		fMaxPressure;
    FLOAT      	fMaxForce;
	FLOAT		fTheoreticalMaxRPM;	// Object Theoretical Max RPM. Anders 20101228.

	FLOAT		fMaxTorque;
    _iq12       iq12TorqueOffset;      // Anders 20110127.
    //FLOAT		fCalTorqueFactor;
    //FLOAT		fSpeedSetpointFactor;   // Anders 20120604.

	FLOAT		fMaxVelocity;
    //FLOAT      fHybiPovMaxVelocity;
    //FLOAT      fHybiNevMaxVelocity;

	FLOAT		fMinPosiLimit;
	FLOAT		fMaxPosiLimit;
} TMachMotorParam;

//======
//      Class actual data
//======
typedef struct tagSOURCE_ACTDATA
{
	WORD		wActPosiSrc;
	WORD		wActPosiChl;
	WORD		wActPresSrc;
	WORD		wActPresChl;
	WORD		wActVeloSrc;
	WORD		wActVeloChl;
    WORD        wActTorqueSrc;
    WORD        wActTorqueChl;

    BOOL        bActPosiReverse;
	BOOL		bActTorqueReverse;
} SOURCE_ACTDATA;

typedef struct tagACTUAL_DATA
{
	WORD		wActualStep;
	long		lPressCount;

	FLOAT  		fActualPosition;
	FLOAT		fActualVelocity;
    _iq		    iqActualPressure;
    _iq	        iqActualForce;
    FLOAT		fActualRPM;     // Anders 20120711.
	//FLOAT	    fActualTorque;
	FLOAT		fActualPressure; // Anders 2013-3-30.
} ACTUAL_DATA;

//======
//      Class calculate actual data
//======
typedef struct tagTCalActDataController
{
    WORD    wAxisNO;
	WORD	wConfigNO;

	long	lCount;
    long    lTotalCount;

	long    lCircle;
    FLOAT	fCycleTime;
    FLOAT	fLastPosition;
    long	lLastCount;

    //FILTER_LOWPASS_FIRSTORDER_FLOAT	FilterVelo;
    //FILTER_LOWPASS_FIRSTORDER_FLOAT	FilterRPM;     // Anders 20120712.
    //FILTER_LOWPASS_FIRSTORDER_IQ	FilterTorque;
    //FILTER_LOWPASS_FIRSTORDER_IQ    FilterPress;
} TCalActDataController;
typedef struct tagCALACT_INOUT
{
    WORD                    wECSlaveIndex;
	ACTUAL_DATA			    *pActData;
	SOURCE_ACTDATA		    *pSource;
	TMachMotorParam		    *pParam;

	TCalActDataController	*pController;
    TCANController     		*pCommonCANController;
	TCANController			*pCalcPosiCANController;
	TCANController			*pCalcPressCANController;
    WORD                    wError;             // Anders 20100701
} CALACT_INOUT;
typedef struct tagCOMPUTE_OUTPUT
{
	_iq		iqTorqueOutput;
	_iq		iqVelocityOutput;
	FLOAT	fVelocityOutput;
    //FLOAT	fRPMOutput;

    BOOL    bBasicVelocityReverse;    // Basic Function Velocity Reverse.
    _iq     iqBasicVelocityOutput;    // Basic Function Velocity Output.

    _iq     iqSetPress;
    _iq     iqSetVelocity;
    _iq     iqSetObjectRPM;
    FLOAT	fSetPosition;

    FLOAT	fProfilePosition;
    _iq     iqProfilePress;         // Anders 2011-05-05.
    _iq     iqProfileObjectRPM;
    _iq     iqProfileVelocity;

	_iq		iqPosiCtlProfilePress;	// Anders 2012-3-20.

} COMPUTE_OUTPUT;

typedef struct tagSOURCE_OUTPUT
{
	WORD		wOutVeloSrc;
	WORD		wOutVeloChl;
	WORD		wOutTorqueSrc;
	WORD		wOutTorqueChl;

	WORD		wOutReverseVelo;	// 0: Not reverse; 1: reverse.
	//WORD		wOutReverseTorque;	// 0: Not reverse; 1: reverse.
    WORD        wOutVeloIOoutput;
    //WORD        wOutReversePressCtl; // 0: Not reverse; 1: reverse.
} SOURCE_OUTPUT;
typedef struct tagCALSETPOINTOUTPUT_INPUT
{
    WORD                wECSlaveIndex;
    TMachMotorParam     *pParam;
	SOURCE_OUTPUT		*pOutSrc;
	COMPUTE_OUTPUT		*pOutData;
    TCANController      *pCANController;
} CALSETPOINT_INPUT;
//================
// enum
//================
// CALPRESS_ID
#define     CALPRESSID_NULL                         0
#define     CALPRESSID_AD                           1
#define     CALPRESSID_CANBUS                       2
#define     CALPRESSID_PLCMASTER                    3
#define     CALPRESSID_MOTORTORQUE                  4
#define     CALPRESSID_INNERAXIS                    5
#define     MAX_CALPRESS                            (CALPRESSID_INNERAXIS + 1)
// CALPOSI_ID
#define     CALPOSIID_NULL                          0
#define     CALPOSIID_RESOLVERENCODER               1
#define     CALPOSIID_ABSOLUTEENCODER               2
#define     CALPOSIID_ADRULER                       3
#define     CALPOSIID_CANBUS_RESOLVERENCODER        4
#define     CALPOSIID_CANBUS_ABSOLUTEENCODER        5
#define     CALPOSIID_ETHERCAT_RESOLVERENCODER      6
#define     CALPOSIID_ETHERCAT_ABSOLUTEENCODER      7
#define     CALPOSIID_PLCMASTER                     8
#define     CALPOSIID_INNERAXIS                     9
#define     CALPOSIID_CANBUS_RULER                  10
#define     MAX_CALPOSI                             (CALPOSIID_CANBUS_RULER + 1)
// CALACTSPEED_ID
#define     CALACTSPEEDID_CANBUS_RESOLVERENCODER    0
#define     CALACTSPEEDID_CANBUS_ABSOLUTEENCODER    1
// CALTORQUE_ID
#define     CALTORQUEID_NULL                        0
#define     CALTORQUEID_AD                          1
#define     CALTORQUEID_CANBUS                      2
#define     CALTORQUEID_PLCMASTER                   3
#define     CALTORQUEID_ETHERCAT                    4
#define     MAX_CALTORQUE                           (CALTORQUEID_ETHERCAT + 1)

// OUTSRC_ID
#define     OUTSRCID_NULL                           0
#define     OUTSRCID_DA                             1
#define     OUTSRCID_CANBUS                         2
#define     OUTSRCID_PLCMASTER                      3
#define     OUTSRCID_ETHERCAT                       4
#define     MAX_OUTSRC			                    (OUTSRCID_ETHERCAT + 1)
int main()
{
    printf("Hello world!\n");
    int i = 10;
    int *iPtr;
    iPtr = &i;
    *iPtr=6;
    printf("i=%d,ptr=%p,iptr=%d\n",i,iPtr,*iPtr);
//    g_pFuncCritical = &MainISR;						// Motion control task
    return 0;
}

void MainISR(void)
{
    void Run_TaskMotionControl()
    {
        printf("Hello world!\n");
    }
}

// Control Object's CtlData.
