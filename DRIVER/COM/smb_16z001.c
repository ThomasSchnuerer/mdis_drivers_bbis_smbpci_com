/*********************  P r o g r a m  -  M o d u l e ***********************/
/*!
 *        \file  smb_16z001.c
 *
 *      \author  dieter.pfeuffer@men.de
 *        $Date: 2010/12/20 13:31:54 $
 *    $Revision: 1.3 $
 *
 *      \brief   SMBPCI BBIS - SMBPCI_16Z001 variant specific functions
 *
 *     Required: ---
 *
 *     \switches DBG 
 * */
 /*
 *---------------------------------------------------------------------------
 * (c) Copyright by MEN Mikro Elektronik GmbH, Nuremberg, Germany
 ******************************************************************************/
/*
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 2 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
 */

#include "smbpci_int.h"		/* internal header file */

/****************************** SmbInitLib **********************************/
/** Initialize the SMB library
 *
 *  \param brdHdl     \IN  Bbis handle
 *
 *  \return           \c 0 On success or error code
 */
extern int32 __SMBPCI_InitLib(
	BBIS_HANDLE *brdH
)
{
    int32				error;
	SMB_DESC_MENZ001	descSmb;

	DBGWRT_1((DBH, "%s baseAddr %08x\n", __FUNCTION__, brdH->virtCtrlBase ));

	OSS_MemFill( brdH->osH, sizeof(descSmb), (char*)&descSmb, 0x00 );

	descSmb.baseAddr = brdH->virtCtrlBase;
	descSmb.dbgLevel = brdH->dbgLev;
	descSmb.alertPollFreq = (int32)brdH->alertPollFreq;
	descSmb.busyWait = (int32)brdH->busyWait;
	descSmb.timeOut = 20;

#ifdef MAC_IO_MAPPED
    error = SMB_MENZ001_IO_Init( &descSmb, brdH->osH, &brdH->smbH );
#else
    error = SMB_MENZ001_Init( &descSmb, brdH->osH, &brdH->smbH );
#endif
    if( error ){
	    DBGWRT_ERR((DBH,"*** %s\n", __FUNCTION__));
    }

	return ( error );
}




