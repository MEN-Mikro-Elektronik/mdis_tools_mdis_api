/****************************************************************************
 ************                                                    ************
 ************               MDIS_CREATEDEV                       ************
 ************                                                    ************
 ****************************************************************************
 *
 *       Author: kp
 *        $Date: 2012/05/14 11:50:32 $
 *    $Revision: 1.2 $
 *
 *  Description: Linux native tool to instanciate MDIS/BBIS devices
 *
 *	Mainly used to create devices for use with RTAI or for BBIS devoce
 *
 *     Required: mdis_api.l, usr_utl.l
 *     Switches: -
 *
 *-------------------------------[ History ]---------------------------------
 *
 * $Log: mdis_createdev.c,v $
 * Revision 1.2  2012/05/14 11:50:32  ts
 * R: build warning on SC24 (SuSE 12.1) occured: rv set but not used
 * M: fixed return value oo program to return rv, not 0
 *
 * Revision 1.1  2003/02/21 13:34:55  kp
 * Initial Revision
 *
 *---------------------------------------------------------------------------
 * (c) Copyright 2003 by MEN mikro elektronik GmbH, Nuremberg, Germany
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

#include <stdio.h>
#include <MEN/men_typs.h>
#include <MEN/mdis_api.h>
#include <MEN/usr_oss.h>
#include <MEN/usr_utl.h>
#include <MEN/mdis_mk.h>

/*--------------------------------------+
|   DEFINES                             |
+--------------------------------------*/
#define REV "V1.1"      /* program revision */

/********************************* usage ************************************
 *
 *  Description: Print program usage and revision
 *			
 *---------------------------------------------------------------------------
 *  Input......: -
 *  Output.....: -
 *  Globals....: -
 ****************************************************************************/
static void usage(void)
{
	printf("Usage: mdis_createdev [<opts>] <device> <device> ... [<opts>]\n");
	printf("Function: Tool to instanciate MDIS/BBIS devices\n");
	printf("Options:\n");
	printf("    device       device name                     [none]\n");
	printf("    -d           delete instead of create\n");
	printf("    -b           create/remove BBIS device (ignores -r)\n");
	printf("\n");
	printf("(c) 2003 by MEN mikro elektronik GmbH, %s\n\n",REV);
}

/********************************* main *************************************
 *
 *  Description: Program main function
 *			
 *---------------------------------------------------------------------------
 *  Input......: argc,argv	argument counter, data ..
 *  Output.....: return		success (0) or error (1)
 *  Globals....: -
 ****************************************************************************/
int main( int argc, char *argv[])
{
	int32 path,bbMode,n,rv=0,delete;
	char *device,*errstr,errbuf[40];

	/*--------------------+
    |  check arguments    |
    +--------------------*/
	if ((errstr = UTL_ILLIOPT("rdb?", errbuf))) {	/* check args */
		printf("*** %s\n", errstr);
		return(1);
	}

	if (UTL_TSTOPT("?")) {						/* help requested ? */
		usage();
		return(1);
	}

	/*--------------------+
    |  get arguments      |
    +--------------------*/

	bbMode = (UTL_TSTOPT("b") ? 1 : 0);
	delete = (UTL_TSTOPT("d") ? 1 : 0);

	/*--------------------+
    |  process ..         |
    +--------------------*/
	for (device=NULL, n=1; n<argc; n++)	{		/* search for name */
		if (*argv[n] != '-') {
			device = argv[n];

			if( !delete ){
				if( ! bbMode ){
					printf("create device %s for standard Linux\n", device);

					if ((path = MDIS_CreateDevice( device, 0, TRUE ))<0){
						printf("*** can't open \"%s\": %s\n",
							   device, M_errstring(UOS_ErrnoGet()));
						rv = 1;
					}
				}
				else {
					printf("create BBIS device %s \n", device);

					if (MDIS_OpenBoard( device )<0){
						printf("*** can't open \"%s\": %s\n",
							   device, M_errstring(UOS_ErrnoGet()));
						rv = 1;
					}
				}
			}
			else {
				if( ! bbMode ){
					printf("deleting device %s\n", device );

					/* delete */
					if( MDIS_RemoveDevice( device ) < 0 ){
						printf("*** can't delete \"%s\": %s\n",
							   device, M_errstring(UOS_ErrnoGet()));
						rv = 1;
					}					
				}
				else {
					printf("deleting BBIS device %s\n", device );

					/* delete */
					if( MDIS_RemoveBoard( device ) < 0 ){
						printf("*** can't delete \"%s\": %s\n",
							   device, M_errstring(UOS_ErrnoGet()));
						rv = 1;
					}					
				}
			}
		}
	}

	return(rv);
}



