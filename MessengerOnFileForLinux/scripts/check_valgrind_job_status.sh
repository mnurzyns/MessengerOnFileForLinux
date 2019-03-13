#!/bin/bash

VALGRIND_OUTPUT_FILE=$1
VALGRIND_ERROR_SUMARY=$(cat $VALGRIND_OUTPUT_FILE | grep "ERROR SUMMARY")
ERROR_NUMBER_POSITION_IN_ERROR_SUMARY=25
ERROR_NUMBER=${VALGRIND_ERROR_SUMARY:$ERROR_NUMBER_POSITION_IN_ERROR_SUMARY:1}
echo $ERROR_NUMBER
if [ $ERROR_NUMBER -ne 0 ] ; then
    exit 1
fi
