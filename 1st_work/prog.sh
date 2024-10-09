#! /bin/bash

func_for_users () {
	echo $'\t\tList of all users'
	awk -F: '{ printf "User - %-15s \t home dir - %s\n", $1, $6}' /etc/passwd | sort | grep -v "User - #"
	return 
}
func_for_processes () {
	echo $'\t\tList of all processes'
	ps -A | grep -v PID | awk '{printf "PID - %-7%s \t CMD - %s\n",$1, $4}' | sort -n
	return 
}
func_for_help () {
	echo "Usage: $0 [arguments] [file]"
	echo $'\nArguments:'
	echo $'-h --help\t\tShow instructions of how to use program'
	echo $'-u --users\t\tShow all users and their home dirrectory'
	echo $'-p --processes\t\tShow all processes running at the moment'
	return 
}
func_for_logintofile () {
	return
}
func_for_errintofile () {
	return 
}

#программа должна проверять доступ к пути и выводить соответствующие сообщения об ошибках
#программа должна фильтровать или обрабатывать выводы используемых команд в stderr


while getopts ":uph-:" option; do
case ${option} in
	u) func_for_users $OPTARG
	;;
	p) func_for_processes $OPTARG
	;;
	h) func_for_help
		exit 0
	;;
	-)
	case "${OPTARG}" in
		users) func_for_users
		;;
		processes) func_for_processes
		;;
		help) func_for_help
		      exit 0
		;;
		*) func_for_help
		   exit 1
		;;
	esac
	;;
	?) func_for_help
	   exit 1
	;;
esac
done
