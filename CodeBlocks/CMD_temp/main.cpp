#include <iostream>

using namespace std;

int main()
{
    cout << "Hello world!" << endl;
    return 0;
TSortedPosiProfile *pSortedPosiProfile = &cthis->pMOCtlData->MOData_Inject.SortedPosiProfile_Inject;
STC_INJECTFWD *pInjectFwd = &cthis->pMOCtlData->MOData_Inject.InjectData;
TAxisController * pAxisController = &cthis->InheritMAController;
STC_INJECTPARAMS *pParams = &TMOAxisController->pMOCtlData->MOData_Inject.FwdParams;
WORD wMachineType = pAxisController->CtlData.MachMotorParam[0].wMachineType; //設定射出機種類:油還電
FLOAT fCurrentPosition = pAxisController->CtlData.ActualData[0].fActualPosition * UPLOAD_POSI;
TTransHoldPressInfo *pInjTransHPInfo = &cthis->pMOCtlData->MOData_Inject.InjectData.TransHoldPressInfo;
TPosiToPressCtlMode PosiToPressCtlMode;
//pAxisController->wPrepare
	if(  pAxisController->wPrepare == PREPARE_INIT )
	{
		CheckPosition_Inject(cthis); // Anders 2013-7-31,add.
		pAxisController->wPrepare = PREPARE_BUSY;

		// Move MO Data to DB.
		for (i=0; i<pSortedPosiProfile->wMax; i++)
		{
			if(  fCurrentPosition > pSortedPosiProfile->Profile[i].fPosition  )
			{
				nStartStep = i;	// nStartStep From 0 to wMax-1.
				break;
			}
		}

		if(  nStartStep > -1 )
		{
			if(  pSortedPosiProfile->Profile[nStartStep].bStopFlag && fCurrentPosition >= pSortedPosiProfile->Profile[nStartStep].fMinPosiLimit && fCurrentPosition <= pSortedPosiProfile->Profile[nStartStep].fMaxPosiLimit )
				bFirstStopDone = TRUE;

			DBValue.dwData = 0;	// BackPress  Option.
			SetDBValueByIndex( AXIS_OFFSET + AXIS1_GENERAL_PRESSCONTROL_BYPOSITION_BACKPRESSOPTION, DBValue.dwData );//094C:壓力控制（位置）背壓選項   直接填 0
			SetDBValueByIndex( AXIS_OFFSET + AXIS1_GENERAL_PRESSCONTROL_BYPOSITION_WFUNDONEHLODPRESSOPTION, DBValue.dwData );// FuncDone Do PressCtl.//0954:壓力控制（位置）位置到達保持壓力選項 直接填 0
			if( wMachineType == MACHINETYPE_HYBI )
			{
				DBValue.dwData = PRESS_RAMPOPTION_TIMERAMP; // PressRamp by Time.
				SetDBValueByIndex( AXIS_OFFSET + AXIS1_SETPOINTS_POSITION_PRESSCONTROL_RAMPOPTION, DBValue.dwData );

				DBValue.fData = HYB_THEORETICALMAXVELOCITY; // Vmax = 100.
				SetDBValueByIndex( AXIS_OFFSET + AXIS1_SETPOINTS_POSITION_PRESSCONTROL_FMOVEMAXVELOCITY, DBValue.dwData );
			}
			else
			{
				DBValue.dwData = PRESS_RAMPOPTION_STDRAMP; // PressRamp by Time.
				SetDBValueByIndex( AXIS_OFFSET + AXIS1_SETPOINTS_POSITION_PRESSCONTROL_RAMPOPTION, DBValue.dwData );
			}
			iIndex = 0;
			for ( i=nStartStep; i<pSortedPosiProfile->wMax; i++ )
			{
				DBValue.fData = pSortedPosiProfile->Profile[i].fPress;
				SetDBValueByIndex( AXIS_OFFSET + AXIS1_SETPOINTS_POSITION_PRESSCONTROL_SETPOINTS1_PRESS + iIndex*SP_POSIPRESSCTL_ITEMS_NUM, DBValue.dwData );

				DBValue.fData = pSortedPosiProfile->Profile[i].fPosition;
				SetDBValueByIndex( AXIS_OFFSET + AXIS1_SETPOINTS_POSITION_PRESSCONTROL_SETPOINTS1_POSITION + iIndex*SP_POSIPRESSCTL_ITEMS_NUM, DBValue.dwData );

				DBValue.fData = pSortedPosiProfile->Profile[i].fVelocity;
				SetDBValueByIndex( AXIS_OFFSET + AXIS1_SETPOINTS_POSITION_PRESSCONTROL_SETPOINTS1_VELOCITY + iIndex*SP_POSIPRESSCTL_ITEMS_NUM, DBValue.dwData );

				DBValue.fData = pSortedPosiProfile->Profile[i].fPressRampUp;
				SetDBValueByIndex( AXIS_OFFSET + AXIS1_SETPOINTS_POSITION_PRESSCONTROL_SETPOINTS1_PRESSUPRAMP + iIndex*SP_POSIPRESSCTL_ITEMS_NUM, DBValue.dwData );
				DBValue.fData = pSortedPosiProfile->Profile[i].fPressRampDown;
				SetDBValueByIndex( AXIS_OFFSET + AXIS1_SETPOINTS_POSITION_PRESSCONTROL_SETPOINTS1_PRESSDOWNRAMP + iIndex*SP_POSIPRESSCTL_ITEMS_NUM, DBValue.dwData );
				if( wMachineType == MACHINETYPE_HYBI )
				{
					if ( pSortedPosiProfile->Profile[i].fAccel == 0 )
						DBValue.dwData = 0;
					else
						DBValue.fData = HYB_THEORETICALMAXVELOCITY / pSortedPosiProfile->Profile[i].fAccel;
					SetDBValueByIndex( AXIS_OFFSET + AXIS1_SETPOINTS_POSITION_PRESSCONTROL_SETPOINTS1_ACCEL + iIndex*SP_POSIPRESSCTL_ITEMS_NUM, DBValue.dwData );
					if ( pSortedPosiProfile->Profile[i].fDecel == 0 )
						DBValue.dwData = 0;
					else
						DBValue.fData = HYB_THEORETICALMAXVELOCITY / pSortedPosiProfile->Profile[i].fDecel;
					SetDBValueByIndex( AXIS_OFFSET + AXIS1_SETPOINTS_POSITION_PRESSCONTROL_SETPOINTS1_DECEL + iIndex*SP_POSIPRESSCTL_ITEMS_NUM, DBValue.dwData );
				}
				else
				{
					DBValue.fData = pSortedPosiProfile->Profile[i].fAccel;
					SetDBValueByIndex( AXIS_OFFSET + AXIS1_SETPOINTS_POSITION_PRESSCONTROL_SETPOINTS1_ACCEL + iIndex*SP_POSIPRESSCTL_ITEMS_NUM, DBValue.dwData );
					DBValue.fData = pSortedPosiProfile->Profile[i].fDecel;
					SetDBValueByIndex( AXIS_OFFSET + AXIS1_SETPOINTS_POSITION_PRESSCONTROL_SETPOINTS1_DECEL + iIndex*SP_POSIPRESSCTL_ITEMS_NUM, DBValue.dwData );
				}

				iIndex = iIndex + 1;

				if(  !(i == nStartStep && bFirstStopDone) && pSortedPosiProfile->Profile[i].bStopFlag )
					break;
			}

			DBValue.dwData = iIndex;
			SetDBValueByIndex( AXIS_OFFSET + AXIS1_SETPOINTS_POSITION_PRESSCONTROL_NUMBEROFSETPOINTS, DBValue.dwData );
		}
		else
		{
			DBValue.dwData = 0;
			SetDBValueByIndex( AXIS_OFFSET + AXIS1_SETPOINTS_POSITION_PRESSCONTROL_NUMBEROFSETPOINTS, DBValue.dwData );
		}
		/**
		 * Inject Trans HoldPress
		 */
		pInjTransHPInfo = &cthis->pMOCtlData->MOData_Inject.InjectData.TransHoldPressInfo;
		PosiToPressCtlMode.bit.bTransType = pInjTransHPInfo->wTransHoldPressMode & 0xFF;
		if ( PosiToPressCtlMode.bit.bTransType == POSITOPRESSTYPE_NONE )
			PosiToPressCtlMode.bit.bTransType = POSITOPRESSTYPE_POSI_TIME;	//POSITOPRESSTYPE_POSI; // Andes 2013-4-28, add; 2013-12-09 modified as P&T.
		PosiToPressCtlMode.bit.bPressCtlType = POSITOPRESSCTLMODE_PRESSTIME;
		DBValue.dwData = PosiToPressCtlMode.wAll;
		SetDBValueByIndex( AXIS_OFFSET + AXIS1_SETPOINTS_POSITIONCONTROL_TOPRESSCTLMODE, DBValue.dwData );
		// Inject KeepPress Fwd Option. Anders 20130501.
		DBValue.dwData = pInjTransHPInfo->wInjectKeepPressFwdOption;
		SetDBValueByIndex( AXIS_OFFSET + AXIS1_SETPOINTS_POSITIONCONTROL_CHECKPRESSLIMITCTLMODE, DBValue.dwData );

		if ( iIndex > 0 && PosiToPressCtlMode.bit.bTransType != POSITOPRESSTYPE_NONE && wMachineType == MACHINETYPE_HYBI)
		{
			DBValue.fData = 0; //pSortedPosiProfile->Profile[i].fPosition;
			SetDBValueByIndex( AXIS_OFFSET + AXIS1_SETPOINTS_POSITION_PRESSCONTROL_SETPOINTS1_POSITION+ (iIndex-1)*SP_POSIPRESSCTL_ITEMS_NUM, DBValue.dwData );
		}
		else if ( iIndex == 0 && PosiToPressCtlMode.bit.bTransType != POSITOPRESSTYPE_NONE && pSortedPosiProfile->wMax > 0 )
		{
			DBValue.dwData = 1;
			SetDBValueByIndex( AXIS_OFFSET + AXIS1_SETPOINTS_POSITION_PRESSCONTROL_NUMBEROFSETPOINTS, DBValue.dwData );
			i = pSortedPosiProfile->wMax - 1;
			DBValue.fData = pSortedPosiProfile->Profile[i].fPress;
			SetDBValueByIndex( AXIS_OFFSET + AXIS1_SETPOINTS_POSITION_PRESSCONTROL_SETPOINTS1_PRESS, DBValue.dwData );

			DBValue.fData = 0; //pSortedPosiProfile->Profile[i].fPosition;
			SetDBValueByIndex( AXIS_OFFSET + AXIS1_SETPOINTS_POSITION_PRESSCONTROL_SETPOINTS1_POSITION, DBValue.dwData );

			DBValue.fData = pSortedPosiProfile->Profile[i].fVelocity;
			SetDBValueByIndex( AXIS_OFFSET + AXIS1_SETPOINTS_POSITION_PRESSCONTROL_SETPOINTS1_VELOCITY, DBValue.dwData );

			DBValue.fData = pSortedPosiProfile->Profile[i].fPressRampUp;
			SetDBValueByIndex( AXIS_OFFSET + AXIS1_SETPOINTS_POSITION_PRESSCONTROL_SETPOINTS1_PRESSUPRAMP, DBValue.dwData );
			DBValue.fData = pSortedPosiProfile->Profile[i].fPressRampDown;
			SetDBValueByIndex( AXIS_OFFSET + AXIS1_SETPOINTS_POSITION_PRESSCONTROL_SETPOINTS1_PRESSDOWNRAMP, DBValue.dwData );
			if( wMachineType == MACHINETYPE_HYBI )
			{
				if ( pSortedPosiProfile->Profile[i].fAccel == 0 )
					DBValue.dwData = 0;
				else
					DBValue.fData = HYB_THEORETICALMAXVELOCITY / pSortedPosiProfile->Profile[i].fAccel;
				SetDBValueByIndex( AXIS_OFFSET + AXIS1_SETPOINTS_POSITION_PRESSCONTROL_SETPOINTS1_ACCEL, DBValue.dwData );
				if ( pSortedPosiProfile->Profile[i].fDecel == 0 )
					DBValue.dwData = 0;
				else
					DBValue.fData = HYB_THEORETICALMAXVELOCITY / pSortedPosiProfile->Profile[i].fDecel;
				SetDBValueByIndex( AXIS_OFFSET + AXIS1_SETPOINTS_POSITION_PRESSCONTROL_SETPOINTS1_DECEL, DBValue.dwData );
			}
			else
			{
				DBValue.fData = pSortedPosiProfile->Profile[i].fAccel;
				SetDBValueByIndex( AXIS_OFFSET + AXIS1_SETPOINTS_POSITION_PRESSCONTROL_SETPOINTS1_ACCEL, DBValue.dwData );
				DBValue.fData = pSortedPosiProfile->Profile[i].fDecel;
				SetDBValueByIndex( AXIS_OFFSET + AXIS1_SETPOINTS_POSITION_PRESSCONTROL_SETPOINTS1_DECEL, DBValue.dwData );
			}
		}

		DBValue.fData = pInjTransHPInfo->fTransTime;
		SetDBValueByIndex( AXIS_OFFSET + AXIS1_SETPOINTS_POSITIONCONTROL_TOPRESSCTLTIME, DBValue.dwData );
		DBValue.fData = pInjTransHPInfo->fTransPress;
		SetDBValueByIndex( AXIS_OFFSET + AXIS1_SETPOINTS_POSITIONCONTROL_TOPRESSCTLPRESS, DBValue.dwData );
		DBValue.fData = pInjTransHPInfo->fTransPosition;
		SetDBValueByIndex( AXIS_OFFSET + AXIS1_SETPOINTS_POSITIONCONTROL_TOPRESSCTLPOSITION, DBValue.dwData );
		DBValue.fData = pInjTransHPInfo->fTransVelocity;
		SetDBValueByIndex( AXIS_OFFSET + AXIS1_SETPOINTS_POSITIONCONTROL_TOPRESSCTLVELOCITY, DBValue.dwData );
		DBValue.dwData = TRANSPROFILEMODE_TOTRANSPOSI;//pInjTransHPInfo->wTransProfileMode;	// Anders 20130301.
		SetDBValueByIndex( AXIS_OFFSET + AXIS1_SETPOINTS_POSITIONCONTROL_TOPRESSCTLPROFILEOPTION, DBValue.dwData );

		// Anders 2013-6-21, Test.
		DBValue.fData = pInjTransHPInfo->fTransDecel;
		SetDBValueByIndex( AXIS_OFFSET + AXIS1_SETPOINTS_POSITIONCONTROL_TOPRESSCTLDECEL, DBValue.dwData );
		DBValue.fData = pInjTransHPInfo->fInjectDoneKeepTime;
		SetDBValueByIndex( AXIS_OFFSET + AXIS1_SETPOINTS_POSITIONCONTROL_TOPRESSCTLPREPAREHOLDTIME, DBValue.dwData );
		DBValue.fData = pInjTransHPInfo->fInjectDoneSuckbackVelocity;
		SetDBValueByIndex( AXIS_OFFSET + AXIS1_SETPOINTS_POSITIONCONTROL_TOPRESSCTLBACKVELOCITY, DBValue.dwData );
		DBValue.dwData = pInjTransHPInfo->wInjectDoneSuckbackOption;
		SetDBValueByIndex( AXIS_OFFSET + AXIS1_SETPOINTS_POSITIONCONTROL_TOPRESSCTLBACKOPTION, DBValue.dwData );

		// Inject Check PressLimit
		DBValue.dwData = 0x003F;
		SetDBValueByIndex( AXIS_OFFSET + AXIS1_SETPOINTS_POSITIONCONTROL_CHECKPRESSLIMITCONFIG, DBValue.dwData );

		DBValue.dwData = 0;	// BackPress  Option.
		SetDBValueByIndex( AXIS_OFFSET + AXIS1_GENERAL_PRESSCONTROL_BYPOSITION_BACKPRESSOPTION, DBValue.dwData );

		// Inject PID.
		DBValue.fData = pParams->fInjetPressKp;
		SetDBValueByIndex( AXIS_OFFSET + AXIS1_GENERAL_PRESSCONTROL_BYPOSITION_KP, DBValue.dwData );
		DBValue.fData = pParams->fInjetPressKi;
		SetDBValueByIndex( AXIS_OFFSET + AXIS1_GENERAL_PRESSCONTROL_BYPOSITION_KI, DBValue.dwData );
		DBValue.fData = pParams->fInjetPressKd;
		SetDBValueByIndex( AXIS_OFFSET + AXIS1_GENERAL_PRESSCONTROL_BYPOSITION_KD, DBValue.dwData ); // Anders Test

		// HoldPress PID.
		DBValue.fData = pParams->fHoldPressKp;
		SetDBValueByIndex( AXIS_OFFSET + AXIS1_GENERAL_PRESSCONTROL_BYTIME_KP, DBValue.dwData );
		DBValue.fData = pParams->fHoldPressKi;
		SetDBValueByIndex( AXIS_OFFSET + AXIS1_GENERAL_PRESSCONTROL_BYTIME_KI, DBValue.dwData );
		DBValue.fData = pParams->fHoldPressKd;
		SetDBValueByIndex( AXIS_OFFSET + AXIS1_GENERAL_PRESSCONTROL_BYTIME_KD, DBValue.dwData );
		/**
		 * Move HoldPress Data.
		 */
		pInjectFwd = &cthis->pMOCtlData->MOData_Inject.InjectData;

		if( wMachineType == MACHINETYPE_HYBI )
		{
			DBValue.dwData = PRESS_BUFFERMODE_BLENDINGPREVIOUS;	// PressCtl BufferMode.
			SetDBValueByIndex( AXIS_OFFSET + AXIS1_GENERAL_PRESSCONTROL_BYTIME_BUFFERMODE, DBValue.dwData );
			DBValue.dwData = PRESS_RAMPOPTION_TIMERAMP;
		}
		else
		{
			DBValue.dwData = PRESS_BUFFERMODE_BLENDINGLOW;	// PressCtl BufferMode.
			SetDBValueByIndex( AXIS_OFFSET + AXIS1_GENERAL_PRESSCONTROL_BYTIME_BUFFERMODE, DBValue.dwData );
			DBValue.dwData = PRESS_RAMPOPTION_STDRAMP;
		}
		SetDBValueByIndex( AXIS_OFFSET + AXIS1_SETPOINTS_PRESSCONTROL_BYTIME_RAMPOPTION, DBValue.dwData );

		DBValue.fData = pInjectFwd->fCamRampFromPress;
		SetDBValueByIndex( AXIS_OFFSET + AXIS1_SETPOINTS_PRESSCONTROL_BYTIME_CAMRAMPFROMPRESS, DBValue.dwData );
		DBValue.fData = pInjectFwd->fCamRampToPress;
		SetDBValueByIndex( AXIS_OFFSET + AXIS1_SETPOINTS_PRESSCONTROL_BYTIME_CAMRAMPTOPRESS, DBValue.dwData );

		//wMax = GetNumOfProfile(cthis->pMOCtlData->MOData_Inject.InjectData.wEnabledHoldPressProfile);
		iIndex = 0;
		for ( i=0; i<MAX_HOLDPRESS_PROFILE; i++ )
		{
			if ( !(pInjectFwd->wEnabledHoldPressProfile & (1<<i)) )
				continue;
			DBValue.fData = pInjectFwd->HoldPressProfile[i].fPress;
			SetDBValueByIndex( AXIS_OFFSET + AXIS1_SETPOINTS_PRESSCONTROL_BYTIME_SETPOINTS1_PRESS + iIndex*SP_PRESSCTL_BYTIME_ITEMS_NUM, DBValue.dwData );

			DBValue.fData = pInjectFwd->HoldPressProfile[i].fVelocity;
			SetDBValueByIndex( AXIS_OFFSET + AXIS1_SETPOINTS_PRESSCONTROL_BYTIME_SETPOINTS1_VELOCITY + iIndex*SP_PRESSCTL_BYTIME_ITEMS_NUM, DBValue.dwData );

			DBValue.fData = pInjectFwd->HoldPressProfile[i].fTime;
			SetDBValueByIndex( AXIS_OFFSET + AXIS1_SETPOINTS_PRESSCONTROL_BYTIME_SETPOINTS1_TIME + iIndex*SP_PRESSCTL_BYTIME_ITEMS_NUM, DBValue.dwData );

			if( wMachineType == MACHINETYPE_HYBI )
			{
				if ( pInjectFwd->HoldPressProfile[i].fAccel == 0 )
					DBValue.dwData = 0;
				else
					DBValue.fData = HYB_THEORETICALMAXVELOCITY / pInjectFwd->HoldPressProfile[i].fAccel;
				SetDBValueByIndex( AXIS_OFFSET + AXIS1_SETPOINTS_PRESSCONTROL_BYTIME_SETPOINTS1_ACCEL + iIndex*SP_PRESSCTL_BYTIME_ITEMS_NUM, DBValue.dwData );
				if ( pInjectFwd->HoldPressProfile[i].fDecel == 0 )
					DBValue.dwData = 0;
				else
					DBValue.fData = HYB_THEORETICALMAXVELOCITY / pInjectFwd->HoldPressProfile[i].fDecel;
				SetDBValueByIndex( AXIS_OFFSET + AXIS1_SETPOINTS_PRESSCONTROL_BYTIME_SETPOINTS1_DECEL + iIndex*SP_PRESSCTL_BYTIME_ITEMS_NUM, DBValue.dwData );
			}
			else
			{
				DBValue.fData = pInjectFwd->HoldPressProfile[i].fAccel;
				SetDBValueByIndex( AXIS_OFFSET + AXIS1_SETPOINTS_PRESSCONTROL_BYTIME_SETPOINTS1_ACCEL + iIndex*SP_PRESSCTL_BYTIME_ITEMS_NUM, DBValue.dwData );
				DBValue.fData = pInjectFwd->HoldPressProfile[i].fDecel;
				SetDBValueByIndex( AXIS_OFFSET + AXIS1_SETPOINTS_PRESSCONTROL_BYTIME_SETPOINTS1_DECEL + iIndex*SP_PRESSCTL_BYTIME_ITEMS_NUM, DBValue.dwData );
			}

			DBValue.fData = pInjectFwd->HoldPressProfile[i].fPressRampUp;
			SetDBValueByIndex( AXIS_OFFSET + AXIS1_SETPOINTS_PRESSCONTROL_BYTIME_SETPOINTS1_PRESSUPRAMP + iIndex*SP_PRESSCTL_BYTIME_ITEMS_NUM, DBValue.dwData );
			DBValue.fData = pInjectFwd->HoldPressProfile[i].fPressRampDown;
			SetDBValueByIndex( AXIS_OFFSET + AXIS1_SETPOINTS_PRESSCONTROL_BYTIME_SETPOINTS1_PRESSDOWNRAMP + iIndex*SP_PRESSCTL_BYTIME_ITEMS_NUM, DBValue.dwData );
			iIndex++;
		}

		if ( PosiToPressCtlMode.bit.bTransType == POSITOPRESSTYPE_NONE )	// Anders 2014-4-7,protect.
			DBValue.dwData = 0;
		else
			DBValue.dwData = iIndex;
		SetDBValueByIndex( AXIS_OFFSET + AXIS1_SETPOINTS_PRESSCONTROL_BYTIME_NUMBEROFSETPOINTS, DBValue.dwData );
	}
	if(  pAxisController->wPrepare == PREPARE_BUSY )//&& !pAxisController->bCriticalControl )
	{
		pAxisController->UpdateFlag.bit.bSpeedCtlSetpoint = FALSE;
		CalculateAxisCtlData( pAxisController );
		Destroy_WhileloopTask(MoveData_Inject, cthis);
		pAxisController->wPrepare = PREPARE_DONE;
	}

//*******************************************************************
/*
	if(  pAxisController->wPrepare == PREPARE_INIT )
	{
		CheckPosition_Inject(cthis); // Anders 2013-7-31,add.
		pAxisController->wPrepare = PREPARE_BUSY;
		pSortedPosiProfile = &cthis->pMOCtlData->MOData_Inject.SortedPosiProfile_Inject;
		fCurrentPosition = pAxisController->CtlData.ActualData[0].fActualPosition * UPLOAD_POSI;
		// Move MO Data to DB.
		for (i=0; i<pSortedPosiProfile->wMax; i++)
		{
			if(  fCurrentPosition > pSortedPosiProfile->Profile[i].fPosition  )
			{
				nStartStep = i;	// nStartStep From 0 to wMax-1.
				break;
			}
		}

		if(  nStartStep > -1 )
		{
			if(  pSortedPosiProfile->Profile[nStartStep].bStopFlag && fCurrentPosition >= pSortedPosiProfile->Profile[nStartStep].fMinPosiLimit && fCurrentPosition <= pSortedPosiProfile->Profile[nStartStep].fMaxPosiLimit )
				bFirstStopDone = TRUE;

				DBValue.dwData = 0;// BackPress  Option.
				SetDBValueByIndex( AXIS_OFFSET + AXIS1_GENERAL_PRESSCONTROL_BYPOSITION_BACKPRESSOPTION, DBValue.dwData );						094C:压力控制（位置）背压选项   直接填 0
				SetDBValueByIndex( AXIS_OFFSET + AXIS1_GENERAL_PRESSCONTROL_BYPOSITION_WFUNDONEHLODPRESSOPTION, DBValue.dwData );// FuncDone Do PressCtl.						0954:压力控制（位置）位置到達保持壓力选项 直接填 0

				//****看一下怎麼填
				SetDBValueByIndex( AXIS_OFFSET + AXIS1_SETPOINTS_POSITION_PRESSCONTROL_RAMPOPTION, DBValue.dwData );						0B03:位置_压力控制压力斜率选项   0 or 1
				SetDBValueByIndex( AXIS_OFFSET + AXIS1_SETPOINTS_POSITION_PRESSCONTROL_FMOVEMAXVELOCITY, DBValue.dwData );						0BFF:位置_压力控制運動最大速度   直接填

				iIndex = 0;
				for ( i=nStartStep; i<pSortedPosiProfile->wMax; i++ )
                {
					SetDBValueByIndex( AXIS_OFFSET + AXIS1_SETPOINTS_POSITION_PRESSCONTROL_SETPOINTS1_PRESS + iIndex*SP_POSIPRESSCTL_ITEMS_NUM, 0 );					//0B0B:位置_壓力控制一段壓力(bar)   pSortedPosiProfile->Profile[i].fPress;
					SetDBValueByIndex( AXIS_OFFSET + AXIS1_SETPOINTS_POSITION_PRESSCONTROL_SETPOINTS1_POSITION + iIndex*SP_POSIPRESSCTL_ITEMS_NUM, DBValue.dwData );				//0B08:位置_壓力控制一段位置(mm)   pSortedPosiProfile->Profile[i].fPosition;
					SetDBValueByIndex( AXIS_OFFSET + AXIS1_SETPOINTS_POSITION_PRESSCONTROL_SETPOINTS1_VELOCITY + iIndex*SP_POSIPRESSCTL_ITEMS_NUM, DBValue.dwData );				//0B07:位置_壓力控制一段速度(mm/s)   pSortedPosiProfile->Profile[i].fVelocity;
					SetDBValueByIndex( AXIS_OFFSET + AXIS1_SETPOINTS_POSITION_PRESSCONTROL_SETPOINTS1_PRESSUPRAMP + iIndex*SP_POSIPRESSCTL_ITEMS_NUM, 0 );				//0B0C:位置_壓力控制一段壓力上升ramp(s)   pSortedPosiProfile->Profile[i].fPressRampUp;
					SetDBValueByIndex( AXIS_OFFSET + AXIS1_SETPOINTS_POSITION_PRESSCONTROL_SETPOINTS1_PRESSDOWNRAMP + iIndex*SP_POSIPRESSCTL_ITEMS_NUM, 0 );			//0B0D:位置_壓力控制一段壓力下降ramp(s)   pSortedPosiProfile->Profile[i].fPressRampDown;
					//****看一下怎麼填
					SetDBValueByIndex( AXIS_OFFSET + AXIS1_SETPOINTS_POSITION_PRESSCONTROL_SETPOINTS1_ACCEL + iIndex*SP_POSIPRESSCTL_ITEMS_NUM, 0 );
					SetDBValueByIndex( AXIS_OFFSET + AXIS1_SETPOINTS_POSITION_PRESSCONTROL_SETPOINTS1_DECEL + iIndex*SP_POSIPRESSCTL_ITEMS_NUM, 0 );
					iIndex = iIndex + 1;

					if(  !(i == nStartStep && bFirstStopDone) && pSortedPosiProfile->Profile[i].bStopFlag )
						break;
                }
				DBValue.dwData = iIndex;
				SetDBValueByIndex( AXIS_OFFSET + AXIS1_SETPOINTS_POSITION_PRESSCONTROL_NUMBEROFSETPOINTS, 1);

                //Inject Trans HoldPress
                pInjTransHPInfo = &cthis->pMOCtlData->MOData_Inject.InjectData.TransHoldPressInfo;
                PosiToPressCtlMode.bit.bTransType = pInjTransHPInfo->wTransHoldPressMode & 0xFF;
                if ( PosiToPressCtlMode.bit.bTransType == POSITOPRESSTYPE_NONE )
                        PosiToPressCtlMode.bit.bTransType = POSITOPRESSTYPE_POSI_TIME;	//POSITOPRESSTYPE_POSI; // Andes 2013-4-28, add; 2013-12-09 modified as P&T.
                PosiToPressCtlMode.bit.bPressCtlType = POSITOPRESSCTLMODE_PRESSTIME;
                DBValue.dwData = PosiToPressCtlMode.wAll;
                SetDBValueByIndex( AXIS_OFFSET + AXIS1_SETPOINTS_POSITIONCONTROL_TOPRESSCTLMODE, DBValue.dwData );//0B4F:位置控制转压力控制模式   PosiToPressCtlMode.wAll;
                // Inject KeepPress Fwd Option. Anders 20130501.
                DBValue.dwData = pInjTransHPInfo->wInjectKeepPressFwdOption;
                SetDBValueByIndex( AXIS_OFFSET + AXIS1_SETPOINTS_POSITIONCONTROL_CHECKPRESSLIMITCTLMODE, DBValue.dwData );//0B4E:位置控制到达压力上限控制模式   pInjTransHPInfo->wInjectKeepPressFwdOption;
                if ( iIndex > 0 && PosiToPressCtlMode.bit.bTransType != POSITOPRESSTYPE_NONE && wMachineType == MACHINETYPE_HYBI)
                {
                DBValue.fData = 0; //pSortedPosiProfile->Profile[i].fPosition;
                SetDBValueByIndex( AXIS_OFFSET + AXIS1_SETPOINTS_POSITION_PRESSCONTROL_SETPOINTS1_POSITION+ (iIndex-1)*SP_POSIPRESSCTL_ITEMS_NUM, DBValue.dwData );
                }
                else if ( iIndex == 0 && PosiToPressCtlMode.bit.bTransType != POSITOPRESSTYPE_NONE && pSortedPosiProfile->wMax > 0 )
                {
                DBValue.dwData = 1;
                SetDBValueByIndex( AXIS_OFFSET + AXIS1_SETPOINTS_POSITION_PRESSCONTROL_NUMBEROFSETPOINTS, 1 );
                i = pSortedPosiProfile->wMax - 1;
                DBValue.fData = pSortedPosiProfile->Profile[i].fPress;
                SetDBValueByIndex( AXIS_OFFSET + AXIS1_SETPOINTS_POSITION_PRESSCONTROL_SETPOINTS1_PRESS, 0 );

                DBValue.fData = 0; //pSortedPosiProfile->Profile[i].fPosition;
                SetDBValueByIndex( AXIS_OFFSET + AXIS1_SETPOINTS_POSITION_PRESSCONTROL_SETPOINTS1_POSITION, 0 );

                DBValue.fData = pSortedPosiProfile->Profile[i].fVelocity;
                SetDBValueByIndex( AXIS_OFFSET + AXIS1_SETPOINTS_POSITION_PRESSCONTROL_SETPOINTS1_VELOCITY, DBValue.dwData );

                SetDBValueByIndex( AXIS_OFFSET + AXIS1_SETPOINTS_POSITION_PRESSCONTROL_SETPOINTS1_PRESSUPRAMP, 0 );
                SetDBValueByIndex( AXIS_OFFSET + AXIS1_SETPOINTS_POSITION_PRESSCONTROL_SETPOINTS1_PRESSDOWNRAMP, 0 );

                SetDBValueByIndex( AXIS_OFFSET + AXIS1_SETPOINTS_POSITION_PRESSCONTROL_SETPOINTS1_ACCEL, 0 );
                SetDBValueByIndex( AXIS_OFFSET + AXIS1_SETPOINTS_POSITION_PRESSCONTROL_SETPOINTS1_DECEL, 0 );
                }
                /*SetDBValueByIndex( AXIS_OFFSET + AXIS1_SETPOINTS_POSITIONCONTROL_TOPRESSCTLTIME, DBValue.dwData );				//0B50:位置控制转压力控制时间   pInjTransHPInfo->fTransTime;
                SetDBValueByIndex( AXIS_OFFSET + AXIS1_SETPOINTS_POSITIONCONTROL_TOPRESSCTLPRESS, DBValue.dwData );					//0B51:位置控制转压力控制压力   pInjTransHPInfo->fTransPress;
                SetDBValueByIndex( AXIS_OFFSET + AXIS1_SETPOINTS_POSITIONCONTROL_TOPRESSCTLPOSITION, DBValue.dwData );				//0B52:位置控制转压力控制位置   pInjTransHPInfo->fTransPosition;
                SetDBValueByIndex( AXIS_OFFSET + AXIS1_SETPOINTS_POSITIONCONTROL_TOPRESSCTLVELOCITY, DBValue.dwData );				//0B53:位置控制转压力控制速度   pInjTransHPInfo->fTransVelocity;
                SetDBValueByIndex( AXIS_OFFSET + AXIS1_SETPOINTS_POSITIONCONTROL_TOPRESSCTLPROFILEOPTION, DBValue.dwData );			//0B54:位置控制转压力控制规划方式   0 or 1

                // Anders 2013-6-21, Test.
                SetDBValueByIndex( AXIS_OFFSET + AXIS1_SETPOINTS_POSITIONCONTROL_TOPRESSCTLDECEL, DBValue.dwData );					//0B55:位置控制转压力控制減速度   pInjTransHPInfo->fTransDecel;
                SetDBValueByIndex( AXIS_OFFSET + AXIS1_SETPOINTS_POSITIONCONTROL_TOPRESSCTLPREPAREHOLDTIME, DBValue.dwData );		//0B56:位置控制转压力控制前保持時間   pInjTransHPInfo->fInjectDoneKeepTime;
                SetDBValueByIndex( AXIS_OFFSET + AXIS1_SETPOINTS_POSITIONCONTROL_TOPRESSCTLBACKVELOCITY, DBValue.dwData );			//0B57:位置控制转压力控制后退速度   pInjTransHPInfo->fInjectDoneSuckbackVelocity;
                SetDBValueByIndex( AXIS_OFFSET + AXIS1_SETPOINTS_POSITIONCONTROL_TOPRESSCTLBACKOPTION, DBValue.dwData );			//0B58:位置控制转压力控制后退选项   pInjTransHPInfo->wInjectDoneSuckbackOption;

                // Inject Check PressLimit
                SetDBValueByIndex( AXIS_OFFSET + AXIS1_SETPOINTS_POSITIONCONTROL_CHECKPRESSLIMITCONFIG, DBValue.dwData );			//0B4D:位置控制压力检查配置   0x003F
                SetDBValueByIndex( AXIS_OFFSET + AXIS1_GENERAL_PRESSCONTROL_BYPOSITION_BACKPRESSOPTION, DBValue.dwData );			//094C:压力控制（位置）背压选项   0

                // Inject PID.
                SetDBValueByIndex( AXIS_OFFSET + AXIS1_GENERAL_PRESSCONTROL_BYPOSITION_KP, DBValue.dwData );						//0946:压力控制（位置）KP   TMOAxisController->pMOCtlData->MOData_Inject.FwdParams->fInjetPressKp;
                SetDBValueByIndex( AXIS_OFFSET + AXIS1_GENERAL_PRESSCONTROL_BYPOSITION_KI, DBValue.dwData );						//0947:压力控制（位置）KI   TMOAxisController->pMOCtlData->MOData_Inject.FwdParams->fInjetPressKi;
                SetDBValueByIndex( AXIS_OFFSET + AXIS1_GENERAL_PRESSCONTROL_BYPOSITION_KD, DBValue.dwData ); // Anders Test			//0948:压力控制（位置）KD   TMOAxisController->pMOCtlData->MOData_Inject.FwdParams->fInjetPressKd;

                // HoldPress PID.
                SetDBValueByIndex( AXIS_OFFSET + AXIS1_GENERAL_PRESSCONTROL_BYTIME_KP, DBValue.dwData );						//0940:压力控制（时间）KP    TMOAxisController->pMOCtlData->MOData_Inject.FwdParams->->fHoldPressKp;
                SetDBValueByIndex( AXIS_OFFSET + AXIS1_GENERAL_PRESSCONTROL_BYTIME_KI, DBValue.dwData );						//0941:压力控制（时间）KI    TMOAxisController->pMOCtlData->MOData_Inject.FwdParams->->fHoldPressKi;
                SetDBValueByIndex( AXIS_OFFSET + AXIS1_GENERAL_PRESSCONTROL_BYTIME_KD, DBValue.dwData );						//0942:压力控制（时间）KD   TMOAxisController->pMOCtlData->MOData_Inject.FwdParams->->fHoldPressKd;

                //Move HoldPress Data.
                pInjectFwd = &cthis->pMOCtlData->MOData_Inject.InjectData;
                SetDBValueByIndex( AXIS_OFFSET + AXIS1_GENERAL_PRESSCONTROL_BYTIME_BUFFERMODE, DBValue.dwData );
                SetDBValueByIndex( AXIS_OFFSET + AXIS1_SETPOINTS_PRESSCONTROL_BYTIME_RAMPOPTION, DBValue.dwData );					//0C06:压力控制（时间）压力斜率选项    0 or 1
                SetDBValueByIndex( AXIS_OFFSET + AXIS1_SETPOINTS_PRESSCONTROL_BYTIME_CAMRAMPFROMPRESS, DBValue.dwData );			//0C07:压力控制（时间）起始压力    pMOCtlData->MOData_Inject.InjectData->fCamRampFromPress;
                SetDBValueByIndex( AXIS_OFFSET + AXIS1_SETPOINTS_PRESSCONTROL_BYTIME_CAMRAMPTOPRESS, DBValue.dwData );			    //0C08:压力控制（时间）终止压力    pMOCtlData->MOData_Inject.InjectData->fCamRampToPress;

                //wMax = GetNumOfProfile(cthis->pMOCtlData->MOData_Inject.InjectData.wEnabledHoldPressProfile);
                iIndex = 0;
                for ( i=0; i<MAX_HOLDPRESS_PROFILE; i++ )
                {
                    if ( !(pInjectFwd->wEnabledHoldPressProfile & (1<<i)) )
                        continue;
                    DBValue.fData = pInjectFwd->HoldPressProfile[i].fPress;
                    SetDBValueByIndex( AXIS_OFFSET + AXIS1_SETPOINTS_PRESSCONTROL_BYTIME_SETPOINTS1_PRESS + iIndex*SP_PRESSCTL_BYTIME_ITEMS_NUM, DBValue.dwData );

                    DBValue.fData = pInjectFwd->HoldPressProfile[i].fVelocity;
                    SetDBValueByIndex( AXIS_OFFSET + AXIS1_SETPOINTS_PRESSCONTROL_BYTIME_SETPOINTS1_VELOCITY + iIndex*SP_PRESSCTL_BYTIME_ITEMS_NUM, DBValue.dwData );

                    DBValue.fData = pInjectFwd->HoldPressProfile[i].fTime;
                    SetDBValueByIndex( AXIS_OFFSET + AXIS1_SETPOINTS_PRESSCONTROL_BYTIME_SETPOINTS1_TIME + iIndex*SP_PRESSCTL_BYTIME_ITEMS_NUM, DBValue.dwData );

                    if( wMachineType == MACHINETYPE_HYBI )
                    {
                        if ( pInjectFwd->HoldPressProfile[i].fAccel == 0 )
                            DBValue.dwData = 0;
                        else
                            DBValue.fData = HYB_THEORETICALMAXVELOCITY / pInjectFwd->HoldPressProfile[i].fAccel;
                        SetDBValueByIndex( AXIS_OFFSET + AXIS1_SETPOINTS_PRESSCONTROL_BYTIME_SETPOINTS1_ACCEL + iIndex*SP_PRESSCTL_BYTIME_ITEMS_NUM, DBValue.dwData );
                        if ( pInjectFwd->HoldPressProfile[i].fDecel == 0 )
                            DBValue.dwData = 0;
                        else
                            DBValue.fData = HYB_THEORETICALMAXVELOCITY / pInjectFwd->HoldPressProfile[i].fDecel;
                        SetDBValueByIndex( AXIS_OFFSET + AXIS1_SETPOINTS_PRESSCONTROL_BYTIME_SETPOINTS1_DECEL + iIndex*SP_PRESSCTL_BYTIME_ITEMS_NUM, DBValue.dwData );
                    }
                    else
                    {
                        DBValue.fData = pInjectFwd->HoldPressProfile[i].fAccel;
                        SetDBValueByIndex( AXIS_OFFSET + AXIS1_SETPOINTS_PRESSCONTROL_BYTIME_SETPOINTS1_ACCEL + iIndex*SP_PRESSCTL_BYTIME_ITEMS_NUM, DBValue.dwData );
                        DBValue.fData = pInjectFwd->HoldPressProfile[i].fDecel;
                        SetDBValueByIndex( AXIS_OFFSET + AXIS1_SETPOINTS_PRESSCONTROL_BYTIME_SETPOINTS1_DECEL + iIndex*SP_PRESSCTL_BYTIME_ITEMS_NUM, DBValue.dwData );
                    }

                    DBValue.fData = pInjectFwd->HoldPressProfile[i].fPressRampUp;
                    SetDBValueByIndex( AXIS_OFFSET + AXIS1_SETPOINTS_PRESSCONTROL_BYTIME_SETPOINTS1_PRESSUPRAMP + iIndex*SP_PRESSCTL_BYTIME_ITEMS_NUM, DBValue.dwData );
                    DBValue.fData = pInjectFwd->HoldPressProfile[i].fPressRampDown;
                    SetDBValueByIndex( AXIS_OFFSET + AXIS1_SETPOINTS_PRESSCONTROL_BYTIME_SETPOINTS1_PRESSDOWNRAMP + iIndex*SP_PRESSCTL_BYTIME_ITEMS_NUM, DBValue.dwData );
                    iIndex++;
                } //   //*

                if ( PosiToPressCtlMode.bit.bTransType == POSITOPRESSTYPE_NONE )	// Anders 2014-4-7,protect.
                    DBValue.dwData = 0;
                else
                    DBValue.dwData = iIndex;
                SetDBValueByIndex( AXIS_OFFSET + AXIS1_SETPOINTS_PRESSCONTROL_BYTIME_NUMBEROFSETPOINTS, DBValue.dwData );
            }
            if(  pAxisController->wPrepare == PREPARE_BUSY )//&& !pAxisController->bCriticalControl )
            {
                pAxisController->UpdateFlag.bit.bSpeedCtlSetpoint = FALSE;
                //CalculateAxisCtlData( pAxisController );
                SOURCE_ACTDATA			*pSrcInputParam = &pAxisController->CtlData.SrcInputParam[0];
                SOURCE_OUTPUT			*pSrcOutputParam = &pAxisController->CtlData.SrcOutputParam[0];
                if(pAxisController->UpdateFlag.bit.bInputOutputParam)
                {
                    // Must First Do it here.
                    ResetPositioning_Standstill(pAxisController);
                }



                Destroy_WhileloopTask(MoveData_Inject, cthis);
                pAxisController->wPrepare = PREPARE_DONE;
            }
        }
*/
}
