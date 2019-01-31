#!/bin/bash

# set -x

DEST=ficlplatform.h
rm -f $DEST
echo "#define FICL_PLATFORM_OS \"`uname`\"" >> $DEST
echo "#define FICL_PLATFORM_ARCHITECTURE \"`uname -m`\"" >> $DEST

