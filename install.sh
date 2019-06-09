#!/bin/bash


if [ $# -ne 1 ]; then
    echo "Enter either Debug ot Release."
    exit
fi

DEBUG="NO"
RELEASE="NO"
DEST="/usr/local/bin"

case "$1" in 
    Debug)
        RELEASE="NO"
        DEBUG="YES"
        ;;
    Release)
        RELEASE="YES"
        DEBUG="NO"
        ;;
    *)
        echo "What?"
        exit 1
        ;;
esac

if [ "$DEBUG" == "YES" ]; then
    echo "Install debug version."
    cd Debug/
fi

if [ "$RELEASE" == "YES" ]; then
    echo "Install debug version."
    cd Release/
fi

make
if [  $? -eq 0 ]; then
    echo "Build succesful."

    sudo mkdir -p $DEST
    sudo cp ./ficl $DEST
    sudo cp ./ficl++ $DEST
fi


    



