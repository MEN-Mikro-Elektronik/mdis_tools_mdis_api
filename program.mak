#***************************  M a k e f i l e  *******************************
#
#         Author: see
#          $Date: 1998/08/11 09:53:25 $
#      $Revision: 1.1 $
#
#    Description: Makefile definitions for MDIS_API test programs
#
#---------------------------------[ History ]---------------------------------
#
#   $Log: program.mak,v $
#   Revision 1.1  1998/08/11 09:53:25  see
#   Added by mcvs
#
#-----------------------------------------------------------------------------
#   (c) Copyright 1998 by MEN mikro elektronik GmbH, Nuernberg, Germany
#*****************************************************************************

MAK_NAME1=m_errstr
MAK_NAME2=m_open
MAK_NAME3=m_getstat
MAK_NAME4=m_setstat
MAK_NAME5=m_setstat_blk
MAK_NAME6=m_getstat_blk
MAK_NAME7=m_read
MAK_NAME8=m_write
MAK_NAME9=m_getblock
MAK_NAME10=m_setblock

MAK_NAME=$(MAK_NAME1) $(MAK_NAME2) $(MAK_NAME3) $(MAK_NAME4) \
         $(MAK_NAME5) $(MAK_NAME6) $(MAK_NAME7) $(MAK_NAME8) \
         $(MAK_NAME9) $(MAK_NAME10)

MAK_LIBS=$(LIB_PREFIX)$(MEN_LIB_DIR)/mdis_api$(LIB_SUFFIX) \
         $(LIB_PREFIX)$(MEN_LIB_DIR)/usr_oss$(LIB_SUFFIX) \
         $(LIB_PREFIX)$(MEN_LIB_DIR)/usr_utl$(LIB_SUFFIX)

MAK_INCL=$(MEN_INC_DIR)/men_typs.h    \
         $(MEN_INC_DIR)/usr_utl.h

MAK_OPTIM=$(OPT_1)

MAK_INP1=m_errstr$(INP_SUFFIX)
MAK_INP2=m_open$(INP_SUFFIX)
MAK_INP3=m_getstat$(INP_SUFFIX)
MAK_INP4=m_setstat$(INP_SUFFIX)
MAK_INP5=m_setstat_blk$(INP_SUFFIX)
MAK_INP6=m_getstat_blk$(INP_SUFFIX)
MAK_INP7=m_read$(INP_SUFFIX)
MAK_INP8=m_write$(INP_SUFFIX)
MAK_INP9=m_getblock$(INP_SUFFIX)
MAK_INP10=m_setblock$(INP_SUFFIX)

MAK_INP=$(MAK_INP1) $(MAK_INP2) $(MAK_INP3) $(MAK_INP4) \
        $(MAK_INP5) $(MAK_INP6) $(MAK_INP7) $(MAK_INP8) \
        $(MAK_INP9) $(MAK_INP10) 





