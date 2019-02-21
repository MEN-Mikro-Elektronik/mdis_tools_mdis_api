/****************************************************************************
 ************                                                    ************
 ************               M _ R E V _ I D                      ************
 ************                                                    ************
 ****************************************************************************
 *  
 *       Author: see
 *        $Date: 2009/04/01 14:36:31 $
 *    $Revision: 1.6 $
 *
 *  Description: Print revision id
 *                      
 *     Required: mdis_api.l, usr_utl.l
 *     Switches: -
 *
 *
 *---------------------------------------------------------------------------
 * Copyright (c) 1998-2019, MEN Mikro Elektronik GmbH
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
 
#include <MEN/men_typs.h>

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include <MEN/mdis_api.h>
#include <MEN/usr_oss.h>
#include <MEN/usr_utl.h>

/*--------------------------------------+
|   DEFINES                             |
+--------------------------------------*/
#define REV "V1.0"      /* program revision */

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
	printf("Usage: m_rev_id <device>\n");
	printf("Function: Print revision id\n");
	printf("Options:\n");
	printf("    device       device name           [none]\n");
	printf("\n");
	printf("(c) 1998 by MEN mikro elektronik GmbH, %s\n\n",REV);
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
int main(argc,argv)
int  argc;
char *argv[];
{
	int32 path,size;
	M_SG_BLOCK blk;
	char *buf = NULL;
	char *device,*errstr,errbuf[40];

	/*--------------------+
    |  check arguments    |
    +--------------------*/
	if ((errstr = UTL_ILLIOPT("?", errbuf))) {	/* check args */
		printf("*** %s\n", errstr);
		return(1);
	}

	if (argc<2 || UTL_TSTOPT("?")) {			/* help requested ? */
		usage();
		return(1);
	}

	/*--------------------+
    |  get arguments      |
    +--------------------*/
	device = argv[1];

	/*--------------------+
    |  process ..         |
    +--------------------*/
	/* open device */
	if ((path = M_open(device)) < 0) {
		printf("*** can't open: %s\n",M_errstring(UOS_ErrnoGet()));
		goto abort;
	}

	/* get required buffer size */
	if (M_getstat(path,M_MK_REV_SIZE,&size) < 0) {
		printf("*** can't getstat: %s\n",M_errstring(UOS_ErrnoGet()));
		goto abort;
	}

	/* alloc buffer */
	if ((buf = malloc(size)) == NULL) {
		printf("*** can't alloc %ld bytes\n",size);
		goto abort;
	}

	blk.size = size;
	blk.data = (void*)buf;

	/* get revision string */
	if (M_getstat(path,M_MK_BLK_REV_ID,(int32*)&blk) < 0) {
		printf("*** can't getstat: %s\n",M_errstring(UOS_ErrnoGet()));
		goto abort;
	}

	/* print string */
	printf("%s",buf);

	abort:

	if (buf)
		free(buf);

	if( path != -1 )
		M_close(path);

	return(0);
}

