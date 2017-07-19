/****************************************************************************
 ************                                                    ************
 ************               M _ E R R S T R I N G                ************
 ************                                                    ************
 ****************************************************************************
 *
 *       Author: see
 *        $Date: 2009/04/01 14:36:15 $
 *    $Revision: 1.6 $
 *
 *  Description: Testing M_errstring()
 *
 *     Required: usr_utl.l
 *     Switches: -
 *
 *-------------------------------[ History ]---------------------------------
 *
 * $Log: m_errstr.c,v $
 * Revision 1.6  2009/04/01 14:36:15  ufranke
 * cosmetics
 *
 * Revision 1.5  2006/10/18 13:45:53  cs
 * added:
 *   + include "string.h", avoid warnings
 *
 * Revision 1.4  2004/07/20 13:44:30  ufranke
 * added
 *  + include usr_oss.h for VxWorks main() function replacement
 *
 * Revision 1.3  2004/03/19 15:10:18  ub
 * added #include <stdlib.h> to remove compiler warning
 *
 * Revision 1.2  1999/04/20 14:54:36  kp
 * declare usage() as static, main() as int
 * eliminate compiler warnings
 *
 * Revision 1.1  1998/08/11 09:53:04  see
 * Added by mcvs
 *
 *---------------------------------------------------------------------------
 * (c) Copyright 1998..2009 by MEN mikro elektronik GmbH, Nuremberg, Germany
 ******************************************************************************/
/*
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
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

static const char RCSid[]="$Id: m_errstr.c,v 1.6 2009/04/01 14:36:15 ufranke Exp $";

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
	printf("Usage: m_errstr [<opts>] <errcode> [<opts>]\n");
	printf("Function: Testing M_errstring function\n");
	printf("Options:\n");
	printf("    errcode     start error code (hex)        [none]\n");
	printf("    -n=<n>      nr of error codes             [1]\n");
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

