#!/bin/bash

ps -aux | awk '{print$2} {print$11}'> commandpid.txt


pid_file="commandpid.txt"
oldIFS=$IFS
IFS=$'\n'

counter=0

ccommand="TT"

echo -e "COMMAND \t\t PID\t\t SUPROCESSES">result.txt

for ligne in $(<$pid_file)
do
    if [ "$ligne" != "COMMAND" ] && [ "$ligne" != "PID" ]
    then
        counter=$((counter + 1))
        if ! ((counter % 2));
        #COMMAND
        then
            ccommand=$ligne
        else
        #PID
            subs="$(find /proc/$ligne/task/ -mindepth 1 -type d | wc -l | grep -v 'No such')"
            case "$subs" in
			"0")
    			echo "Not ok"
    		;;
			*)
    			echo -e "$ccommand\t\t $ligne\t\t $subs">>result.txt
    		;;
			esac		
        fi
    fi
done

rm commandpid.txt
clear
less result.txt
rm result.txt

