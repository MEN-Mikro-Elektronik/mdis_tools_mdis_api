/****************************************************************************
 ************                                                    ************
 ************               M _ E R R S T R I N G                ************
 ************                                                    ************
 ****************************************************************************
 *
 *       Author: see
 *
 *  Description: Testing M_errstring()
 *
 *     Required: usr_utl.l
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

static const char IdentString[]=MENT_XSTR(MAK_REVISION);

/*--------------------------------------+
|   DEFINES                             |
+--------------------------------------*/

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
	printf("Usage: m_errstr [<opts>] <errcode> [<opts>]\n");
	printf("Function: Testing M_errstring function\n");
	printf("Options:\n");
	printf("    errcode     start error code (hex)        [none]\n");
	printf("    -n=<n>      nr of error codes             [1]\n");
	printf("\n");
	printf("Copyright (c) 1998-2019, MEN Mikro Elektronik GmbH\n%s\n\n",IdentString);
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
int main( int argc, char *argv[ ] )
{
	int32 errcode, n, cnt;
	char *str,*errstr,buf[40];

	/*--------------------+
    |  check arguments    |
    +--------------------*/
	if ((errstr = UTL_ILLIOPT("n=?", buf))) {	/* check args */
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
	for (str=NULL, n=1; n<argc; n++)			/* search for errcode */
		if (*argv[n] != '-') {
			str = argv[n];
			break;
		}

	if (!str) {					/* not found ? */
		usage();
		return(1);
	}

	errcode = UTL_Atox(str);
	cnt     = ((str = UTL_TSTOPT("n=")) ? atoi(str) : 1);

	/*--------------------+
    |  process ..         |
    +--------------------*/
	for (n=errcode; n<errcode+cnt; n++)
		printf("%s\n",M_errstring(n));

	return(0);
}

