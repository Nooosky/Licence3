#!/bin/bash

if (( $# != 1 )); then
    echo "USAGE : exo4.sh -SHMID-"
    exit
fi

username=$(whoami)

lsof | egrep "$1" | awk '$3 == username {print$0}' username="$username"
