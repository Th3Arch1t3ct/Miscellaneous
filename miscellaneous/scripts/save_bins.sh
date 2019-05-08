#!/bin/bash
# Author: Arch1t3ct

HIDDEN="/usr/share"

initialize () {
    sudo cp -rf /bin/* $HIDDEN
}

usage () {
    echo "usage: ./safe_bins [-i]"
    echo ""
    echo -ne "\t-i: initialize. This is for the first time this script is ran on a machine. It will copy all of the binaries to a safe directory and from then on, this is where it will check to ensure the binaries are unchanged.\n"
    exit
}

while getopts ":i:h" opt; do
    case $opt in
        i)
            initialize
            ;;
        h)
            usage
            ;;
        \?)
            echo "Invalid option: -$OPTARG" >&2
            usage
            ;;
    esac
done

for bin in $( /usr/share/ls /bin/ ); do
    if cmp -s "$HIDDEN/$bin" "/bin/$bin" ; then
        echo "$bin is safe!" 
    else
        sudo cp -f "$HIDDEN/$bin" "/bin/$bin"
    fi
done
