#! /bin/bash

func_for_users () {
	return 
}
func_for_processes () {
#for processes ps command
	return 
}
func_for_help () {
	return 
}
func_for_logintofile () {
	return
}
func_for_errintofile () {
	return 
}

#getopt/getopts обрaботка командной строки
#программа должна проверять доступ к пути и выводить соответствующие сообщения об ошибках
#программа должна фильтровать или обрабатывать выводы используемых команд в stderr


while getopts ":uph-:" option; do
case ${option} in
	u) func_for_users
	;;
	p) func_for_processes
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
