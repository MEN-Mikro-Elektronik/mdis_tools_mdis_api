/****************************************************************************
 ************                                                    ************
 ************               M _ M O D _ I D                      ************
 ************                                                    ************
 ****************************************************************************
 *  
 *       Author: see
 *
 *  Description: Print module id
 *                      
 *     Required: mdis_api.l, usr_utl.l
 *     Switches: -
 *
 *
 *---------------------------------------------------------------------------
 * Copyright 1998-2019, MEN Mikro Elektronik GmbH
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
	printf("Usage: Show:    m_mod_id [<opts>] <device>\n");
	printf("Usage: Program: m_mod_id [<opts>] <device> <prgspec>\n");
	printf("Function: Print or program module id\n");
	printf("Options:\n");
	printf("    device       device name           [none]\n");
	printf("    progspec     programming specification file\n");
	printf("\n");
	printf("Copyright 1998-2019, MEN Mikro Elektronik GmbH\n%s\n\n",IdentString);
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
	char *device,*errstr,strbuf[100], *progfile=NULL;
	FILE *fp=NULL;

	/*--------------------+
    |  check arguments    |
    +--------------------*/
	if ((errstr = UTL_ILLIOPT("?", strbuf))) {	/* check args */
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
	if( argc > 2 )
		progfile = argv[2];

	/* open device */
	if ((path = M_open(device)) < 0) {
		printf("*** can't open: %s\n",M_errstring(UOS_ErrnoGet()));
		goto abort;
	}

	/* get required buffer size */
	if (M_getstat(path,M_LL_ID_SIZE,&size) < 0) {
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

	if( progfile == NULL ){
		/*--------+
		|  Show   |
		+--------*/

		/* get id prom data */
		if (M_getstat(path,M_LL_BLK_ID_DATA,(int32*)&blk) < 0) {
			printf("*** can't getstat: %s\n",M_errstring(UOS_ErrnoGet()));
			goto abort;
		}

		/* print id prom data */
		UTL_Memdump("id prom data",blk.data, blk.size, 2);
	}
	else {
		int nwords=0;
		int val;
		u_int16 *bufp = (u_int16 *)buf;

		/*----------+
		|  Program  |
		+----------*/
		fp = fopen(progfile, "r");
		
		if( fp == NULL ){
			perror("Can't open program file");
			goto abort;
		}

		while( fgets( strbuf, sizeof(strbuf), fp )){

			if( strbuf[0] == '*' ) /* check for comment */
				printf("%s", strbuf );

			else {
				char *s = strbuf;
				
				while( *s ){
					/* skip white space */
					while( *s == ' ' || *s == '\t' || *s == '\n' || 
						   *s == '\r'  )
						s++;

					if( *s == '\n' || *s == '\r' || *s == '\0' )
						break;

					if( sscanf( s, "%x", &val ) != 1){
						printf("Error scanning <%s>\n", s );
						goto abort;
					}
					*bufp++ = (u_int16)val;
					nwords++;

					/* skip until white space */
					while( *s && (*s != ' ') && (*s != '\t') )
						s++;
				}
			}
		}

		printf("\nProgramming %d words into IDPROM...\n", nwords);
		blk.size = nwords * 2;
		/* get id prom data */

		if (M_setstat(path,M_LL_BLK_ID_DATA,(INT32_OR_64)&blk) < 0) {
			printf("*** Error while programming %s\n",
				   M_errstring(UOS_ErrnoGet()));
			goto abort;
		}
		printf("Programming done.\n");
	}
	abort:

	if( fp ) 
		fclose(fp);

	if (buf)
		free(buf);

	if( path != -1 )
		M_close(path);

	return(0);
}

