#! /bin/bash


func_for_users () {
	if [ "$1" != "" ]; then
	    awk -F: '{ printf "User - %-15s \t home dir - %s\n", $1, $6}' /etc/passwd | sort | grep -v "User - #" > "$1"
	elif [ "$2" != "" ]; then
	    awk -F: '{ printf "User - %-15s \t home dir - %s\n", $1, $6}' /etc/passwd | sort | grep -v "User - #" 2> "$1"
	else
	    echo $'\t\tList of all users'
	    awk -F: '{ printf "User - %-15s \t home dir - %s\n", $1, $6}' /etc/passwd | sort | grep -v "User - #"
	fi
}

func_for_processes () {
	if [ "$1" != "" ]; then
	    ps -A | sort -n | grep -v TTY | awk '{printf "PID - %-7%s \t CMD - %s\n",$1, $4}'  > "$1"
	elif [ "$2" != "" ]; then
	    ps -A | sort -n | grep -v TTY | awk '{printf "PID - %-7%s \t CMD - %s\n",$1, $4}'  2> "$1"
	else
	    echo $'\t\tList of all processes'
	    ps -A | sort -n | grep -v TTY | awk '{printf "PID - %-7%s \t CMD - %s\n",$1, $4}' 
	fi
}

func_for_help () {
	echo "Usage: $0 [arguments] [file]"
	echo $'\nArguments:'
	echo $'-h --help\t\tShow instructions of how to use program'
	echo $'-u --users\t\tShow all users and their home dirrectory'
	echo $'-p --processes\t\tShow all processes running at the moment\n'
	echo $'-l --log [PATH]\t\tLogs all output into file on the PATH'
	echo $'-e --errors [PATH]\tLogs all errors into file on the PATH'
	return 
}

func_for_canwriteinfile () {
	[ -w "$1" ] && canwrite=1 || canwrite=0
}

usr=0
proc=0

args=":uphl:e:-:"
while getopts "$args" options; do
    case "${options}" in
        -)
            case "${OPTARG}" in
                users)
		    usr=1
                    ;;
                processes)
		    proc=1
                    ;;
                help)
		    func_for_help
		    exit 0
                    ;;
                log)
		    log_file="${!OPTIND}"; OPTIND=$(( $OPTIND + 1 ))
                    ;;
                log=*)
                    log_file=${OPTARG#*=}
                    ;;
                errors)
		    err_file="${!OPTIND}"; OPTIND=$(( $OPTIND + 1 ))
                    ;;
                errors=*)
                    err_file=${OPTARG#*=}
                    ;;
                *)
	    	    echo "Wrong option"
		    func_for_help
		    exit 1
                    ;;
            esac
	    ;;
        u)
	    usr=1
            ;;
        p)
	    proc=1
            ;;
        h)
	    func_for_help
	    exit 0
            ;;
	l)
	    log_file="${OPTARG}"
	    ;;
	e)
	    err_file="${OPTARG}"
	    ;;
        *)
	    echo "Wrong option"
	    func_for_help
	    exit 1
            ;;
    esac
done

if [ "$log_file" != "" ]; then
	func_for_canwriteinfile $log_file
	if [ $canwrite == 0 ]; then
	    echo "Can't log in file, few priviledges"
	    exit 1
	fi
	if [ $usr == 1 ]; then func_for_users "${log_file}" ""; fi
	if [ $proc == 1 ]; then func_for_processes "${log_file}" ""; fi
fi
if [ "$err_file" != "" ]; then
	func_for_canwriteinfile $err_file
	if [ $canwrite == 0 ]; then
	    echo "Can't write err in file, few priviledges"
	    exit 1
	fi
	if [ $usr == 1 ]; then func_for_users "" "${err_file}"; fi
	if [ $proc == 1 ]; then func_for_processes "" "${err_file}"; fi
fi
#if [ "$log_file" == ""] && ["$err_file" == ""]; then
if [ "$log_file" == "" ]; then
	if [ "$err_file" == "" ]; then
		if [ $usr == 1 ]; then func_for_users; fi
		if [ $proc == 1 ]; then func_for_processes; fi
	fi
fi

