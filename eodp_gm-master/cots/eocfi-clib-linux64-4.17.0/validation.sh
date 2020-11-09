#! /bin/bash

############################################################################################
#
# Project       : EARTH EXPLORER CFI
#
# Module        : example_compilation.sh
# Purpose       : This script run the Earth Explorer CFI examples.
#		  USAGE: .example_compilation.sh platform
#
# History       +------------------------------------------------------------------------+
#               | Version | Date     | Name         | Change                             |
#               |---------|----------|--------------|------------------------------------|
#               |    1.0  | 09/12/11 | Deimos-Space | First creation                     |
#               +------------------------------------------------------------------------+
#
############################################################################################

#   Getting input parameters 

if [ -z "$1" ]
then
	echo "-------------------------------------"
	echo "compile_libraries.sh Error: Insufficient arguments"
	echo "USAGE: ./compile_libraries.sh platform"
	echo "       where"
	echo "       platform     can be one of {LINUX64_LEGACY, LINUX64, MACIN64}"
	echo "-------------------------------------"
	exit 0
fi

if [ "$1" != LINUX32_LEGACY ]   && [ "$1" != LINUX64_LEGACY ] && 
   [ "$1" != WINDOWS ] && [ "$1" != MACIN64 ] &&
   [ "$1" != LINUX64 ]
then
	echo "-------------------------------------"
	echo "Error: platform not allowed"
	echo "Allowed values: MACIN64, LINUX64_LEGACY, LINUX64"
	echo "-------------------------------------"
	exit 0
fi

SYSTEM=$1

#Current directory
CURRENT_DIR=`pwd`

# EXPCFI_DIR internal variable
export EXPCFI_DIR=${CURRENT_DIR}

#Array of lib names to enforce compilation order

lib[0]=file_handling
lib[1]=data_handling
lib[2]=lib
lib[3]=orbit
lib[4]=pointing
lib[5]=visibility

#Remove previous log file
LOG_FILE="$EXPCFI_DIR"/validation_"$SYSTEM"_log.txt
`rm -f $LOG_FILE`

#Makefile name
MAKEFILE=make.$SYSTEM

# WRITE LOG FILE: validation_OS_log.txt

echo                     > $LOG_FILE
echo "Validation log:"  >> $LOG_FILE
echo "---------------"  >> $LOG_FILE
echo ""                 >> $LOG_FILE
echo "SYSTEM = $SYSTEM" >> $LOG_FILE
echo "DATE = "`date`    >> $LOG_FILE
echo ""                 >> $LOG_FILE
echo "---------------"  >> $LOG_FILE
echo ""                 >> $LOG_FILE

#COMPILE

for cfi in ${lib[*]}
do
  export CFI=explorer_$cfi
  cd $EXPCFI_DIR/explorer_$cfi/validation

  echo "------------------------------------------" | tee -a $LOG_FILE
  echo "compiling validation for explorer_$cfi"     | tee -a $LOG_FILE
  echo "------------------------------------------" | tee -a $LOG_FILE
  make -f $MAKEFILE clean default 2>&1              | tee -a $LOG_FILE

done

cd $CURRENT_DIR


# Complete log with results
echo ""                                 >> $LOG_FILE
echo "----------------------------"     >> $LOG_FILE
echo "VALIDATION RESULTS:"              >> $LOG_FILE
`grep RESULT $EXPCFI_DIR/explorer_*/validation/*.out| grep -v PASS >> $LOG_FILE`

for cfi in ${lib[*]}
do
   EXE_FILE=$EXPCFI_DIR/explorer_"$cfi"/validation/explorer_"$cfi"_valid
   OUT_FILE=$EXPCFI_DIR/explorer_"$cfi"/validation/explorer_"$cfi"_valid."$SYSTEM".out
   if [ ! -e $EXE_FILE ]
   then
      echo "... explorer_"$cfi" LIBRARY VALIDATION: RESULT = FAILED. Validation program not built">> $LOG_FILE
   else
      if [ -e $OUT_FILE ]
      then
         if [ `grep "VALIDATION COMPLETED SUCCESSFULLY" $OUT_FILE | wc -l` = 0 ]
         then
            echo "... explorer_"$cfi" LIBRARY VALIDATION: RESULT = FAILED. Test incomplete">> $LOG_FILE
         else
            if [ `grep "FAIL" $OUT_FILE | wc -l` = 0 ]
            then
               echo "... explorer_"$cfi" LIBRARY VALIDATION: RESULT = OK" >> $LOG_FILE; \
               else echo "... explorer_"$cfi" LIBRARY VALIDATION: RESULT = FAILED. Some tests failed">> $LOG_FILE
            fi
         fi
      else
         echo "... explorer_"$cfi" LIBRARY VALIDATION: RESULT = FAILED. Log file not found">> $LOG_FILE
      fi
   fi
done

echo "----------------------------"     >> $LOG_FILE

# END

