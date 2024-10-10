#! /bin/bash


func_for_users () {
	if [ "$1" == "" ]; then
	    echo $'\t\tList of all users'
	    awk -F: '{ printf "User - %-15s \t home dir - %s\n", $1, $6}' /etc/passwd | sort | grep -v "User - #"
	else
	    echo $'\t\tList of all users' > "$1"
	    awk -F: '{ printf "User - %-15s \t home dir - %s\n", $1, $6}' /etc/passwd | sort | grep -v "User - #" >> "$1"
	fi
}

func_for_processes () {
	if [ "$1" == "" ]; then
	    echo $'\t\tList of all processes'
	    ps -A | grep -v PID | awk '{printf "PID - %-7%s \t CMD - %s\n",$1, $4}' | sort -n
	else
	    echo $'\t\tList of all processes' > "$1"
	    ps -A | grep -v PID | awk '{printf "PID - %-7%s \t CMD - %s\n",$1, $4}' | sort -n >> "$1"
	fi
}

func_for_help () {
	echo "Usage: $0 [arguments] [file]"
	echo $'\nArguments:'
	echo $'-h --help\t\tShow instructions of how to use program'
	echo $'-u --users\t\tShow all users and their home dirrectory'
	echo $'-p --processes\t\tShow all processes running at the moment\n'
	echo $'-l --log [PATH]\t\tLogs all output into file on the PATH'
	return 
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
        *)
	    echo "Wrong option"
	    func_for_help
	    exit 1
            ;;
    esac
done

#make a check of file
if [ log_file == "" ]; then
	if [ $usr == 1 ]; then func_for_users; fi
	if [ $proc == 1 ]; then func_for_processes; fi
else
	if [ $usr == 1 ]; then func_for_users "${log_file}"; fi
	if [ $proc == 1 ]; then func_for_processes "${log_file}"; fi
fi

