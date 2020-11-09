#! /bin/bash

############################################################################################
#
# Project       : EARTH OBSERVATION CFI
#
# Module        : example_compilation.sh
# Purpose       : This script run the Earth Observation CFI examples.
#		  USAGE: ./example_compilation.sh platform
#
# History       +------------------------------------------------------------------------+
#               | Version | Date     | Name         | Change                             |
#               |---------|----------|--------------|------------------------------------|
#               |    1.0  | 09/12/11 | Deimos-Space | First creation                     |
#               +------------------------------------------------------------------------+
#
############################################################################################
# -------------------------------------------------------------------------
# Function: Usage
# Purpose:  To show a usage notice
# -------------------------------------------------------------------------

usage ()
{
	echo "-------------------------------------"
	echo "example_compilation.sh Error: Insufficient arguments"
	echo "USAGE: ./example_compilation.sh platform"
	echo "       where"
	echo "       platform     can be one of {LINUX64_LEGACY, LINUX64, MACIN64}"
	echo "-------------------------------------"
}

# -------------------------------------------------------------------------
# Main script
# -------------------------------------------------------------------------

#   Getting input parameters 

if [ -z "$1" ]
then
  usage
	exit 0
fi

if [ "$1" != LINUX64_LEGACY ] && 
   [ "$1" != WINDOWS ] && [ "$1" != MACIN64 ] && 
   [ "$1" != LINUX64 ]
then
	echo "-------------------------------------"
	echo "Error: platform not allowed"
	echo "Allowed values: LINUX64_LEGACY, LINUX64, MACIN64"
	echo "-------------------------------------"
	exit 0
fi


SYSTEM=$1

if [ "$2" != "ref" ] && [ "$2" != "comp" ] && [ "$2" != "" ]
then
  echo "-------------------------------------"
	echo "Error: invalid option argument"
	echo "Allowed values: ref, comp or blank (\"\")"
	echo "-------------------------------------"
  exit 0
fi

REF="$2"


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

#Makefile name
MAKEFILE=make.$SYSTEM
MAKEFILERUN=makerun.$SYSTEM

#---------------------------------
# Write log file and check results
# Only for ordinary compilations, no when reference is being generated
#---------------------------------
if [[ $REF == "comp" ||  $REF == "" ]]; then
  # Remove previous log file
  LOG_FILE="$EXPCFI_DIR"/example_${SYSTEM}_log.txt
  `rm -f $LOG_FILE`

  echo                     > $LOG_FILE
  echo "Example log:"     >> $LOG_FILE
  echo "---------------"  >> $LOG_FILE
  echo                    >> $LOG_FILE
  echo "SYSTEM = $SYSTEM" >> $LOG_FILE
  echo "DATE = "`date`    >> $LOG_FILE
  echo ""                 >> $LOG_FILE
  echo "---------------"  >> $LOG_FILE
  echo ""                 >> $LOG_FILE
fi

#COMPILE

for cfi in ${lib[*]}
do
  export CFI=explorer_$cfi
  cd $EXPCFI_DIR/explorer_$cfi/example/c

  ## Note: a new reference file is generated for every system,
  ## since there can accuracy differences
  if [[ $REF == "ref" ]];
  then
    OUTFILE=outref.example_${cfi}_${SYSTEM}
    mv $OUTFILE old_$OUTFILE_${SYSTEM}
  else
    OUTFILE=stdout.example_${cfi}_$SYSTEM
    OUTFILERUN=stdout.example_${cfi}_run_$SYSTEM
  fi

  OUTFILE_ERR=stderr.example_${cfi}_$SYSTEM
  OUTFILERUN_ERR=stderr.example_${cfi}_run_$SYSTEM
  
  if [[ $REF == "ref" ]]; then
    echo "------------------------------------------"
    echo "compiling example for Earth Observation $cfi"
    echo "------------------------------------------"
    make -f $MAKEFILE clean example
  else
    echo "------------------------------------------"   | tee -a $LOG_FILE
    echo "compiling example for Earth Observation $cfi" | tee -a $LOG_FILE
    echo "------------------------------------------"   | tee -a $LOG_FILE
    make -f $MAKEFILE clean example                     | tee -a $LOG_FILE

    if [ $cfi != file_handling ] && [ $cfi != data_handling ]
    then
      echo "------------------------------------------"               | tee -a $LOG_FILE
      echo "compiling example with RUN_ID for Earth Observation $cfi" | tee -a $LOG_FILE
      echo "------------------------------------------"               | tee -a $LOG_FILE
      make -f $MAKEFILERUN clean example                              | tee -a $LOG_FILE
    fi
  fi

  echo "------------------------------------------"   | tee -a $LOG_FILE
  echo "Running example for Earth Observation $cfi"   | tee -a $LOG_FILE
  echo "------------------------------------------"   | tee -a $LOG_FILE
  ./explorer_"$cfi"_c > $OUTFILE 2> $OUTFILE_ERR


  if [[ $REF == "comp" || $REF == "" ]]; then
    if [ $cfi != file_handling ] && [ $cfi != data_handling ]
    then
      echo "------------------------------------------"             | tee -a $LOG_FILE
      echo "Running example with RUN_ID for Earth Observation $cfi" | tee -a $LOG_FILE
      echo "------------------------------------------"             | tee -a $LOG_FILE
      ./explorer_"$cfi"_run_c > $OUTFILERUN 2> $OUTFILERUN_ERR
    fi
  fi
done

cd $CURRENT_DIR

#---------------------------------
# Complete log file and check results
#---------------------------------
if [[ $REF != "comp" ]];
then
    exit 0
fi

echo "----------------------------"      | tee -a $LOG_FILE
echo "EXAMPLE RESULTS:"                  | tee -a $LOG_FILE
echo ""                                  | tee -a $LOG_FILE

for cfi in ${lib[*]}
do
   EXE_FILE=$EXPCFI_DIR/explorer_"$cfi"/example/c/explorer_"$cfi"_c
   OUT_FILE1=$EXPCFI_DIR/explorer_"$cfi"/example/c/outref.example_${cfi}_$SYSTEM
   OUT_FILE2=$EXPCFI_DIR/explorer_"$cfi"/example/c/stdout.example_${cfi}_$SYSTEM

   if [ ! -e $EXE_FILE ]
   then
      echo "... explorer_"$cfi" LIBRARY EXAMPLE: RESULT = FAILED. Example program not built" | tee -a $LOG_FILE
   else

      if [ ! -e $OUT_FILE1 ]
      then
         echo "... explorer_"$cfi" LIBRARY EXAMPLE: RESULT = FAILED. Reference file not found. ($OUT_FILE1)" | tee -a $LOG_FILE
      fi

      if [ ! -e $OUT_FILE2 ]
      then
         echo "... explorer_"$cfi" LIBRARY EXAMPLE: RESULT = FAILED. Log file not found. ($OUT_FILE2)" | tee -a $LOG_FILE
      fi

      if [ -e $OUT_FILE2 ] && [ -e $OUT_FILE1 ]
      then
         if [ `grep "EXAMPLE COMPLETED SUCCESSFULLY" $OUT_FILE2 | wc -l` = 0 ]
         then
            echo "... explorer_"$cfi" LIBRARY EXAMPLE: RESULT = FAILED. Test incomplete." | tee -a $LOG_FILE
         else
            if [ `diff  $OUT_FILE1 $OUT_FILE2 | wc -l` = 0 ]
            then
                echo "... explorer_"$cfi" LIBRARY EXAMPLE: RESULT = OK"  | tee -a $LOG_FILE;
            else 
                echo "... explorer_"$cfi" LIBRARY EXAMPLE: RESULT = FAILED. Output file differs from the reference file" | tee -a $LOG_FILE
            fi
         fi
      fi
   fi

   EXERUN_FILE=$EXPCFI_DIR/explorer_"$cfi"/example/c/explorer_"$cfi"_run_c
   OUT_FILERUN=$EXPCFI_DIR/explorer_"$cfi"/example/c/stdout.example_${cfi}_run_$SYSTEM

   if [ $cfi != file_handling ] && [ $cfi != data_handling ]
   then
      if [ ! -e $EXERUN_FILE ]
      then
         echo "... explorer_"$cfi" LIBRARY EXAMPLE (run_id test): RESULT = FAILED. Example program not built" | tee -a $LOG_FILE
      else

         if [ ! -e $OUT_FILERUN ]
         then
            echo "... explorer_"$cfi" LIBRARY EXAMPLE (run_id test): RESULT = FAILED. Log file not found ($OUT_FILERUN)" | tee -a $LOG_FILE
         else if [ -e $OUT_FILERUN ]
         then
            if [ `grep "EXAMPLE COMPLETED SUCCESSFULLY" $OUT_FILERUN | wc -l` = 0 ]
            then
               echo "... explorer_"$cfi" LIBRARY EXAMPLE (run_id test): RESULT = FAILED. Test incomplete." | tee -a $LOG_FILE
            else
               echo "... explorer_"$cfi" LIBRARY EXAMPLE (run_id test): RESULT = OK" | tee -a $LOG_FILE;
            fi
         fi
         fi
      fi
   fi
done

echo "----------------------------"      | tee -a $LOG_FILE

# END
