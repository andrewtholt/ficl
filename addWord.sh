#!/bin/bash

# set -x

if [ $# -ne 2 ]; then
    echo "ficl name, function name"
    exit 0
fi

# This goes into athExtras.h
FICL_NAME=$1
FUNC_NAME=$2

echo "Creating the function $FUNC_NAME, ficl name $FICL_NAME in:"
echo "athExtras.h"
echo "athExtras.cpp"
echo "extras.c"

echo "void $FUNC_NAME(ficlVm *vm);" >> athExtras.h

# extern "C" void plcVerbose(ficlVm *vm) {

# This goes into athExtras.cpp
echo "extern \"C\" void $FUNC_NAME(ficlVm *vm) {" >> athExtras.cpp
echo "}" >> athExtras.cpp
echo "" >> athExtras.cpp


TMP=$(grep -n ATH_OBJ extras.c | tail -1 | cut -f1 -d":")

let "LINE=TMP+1"

echo "See extras.c:$LINE"

cp extras.c extras.c.bak
# addPrimitive(dictionary, "plc-verbose",  plcVerbose );
NEW=$(echo "    addPrimitive(dictionary, \"${FICL_NAME}\", ${FUNC_NAME});")

sed -i "${LINE}i$NEW" extras.c
