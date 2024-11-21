/*

levels - DEBUG, INFO, WARN, ERROR, CRITICAL
	 LOG_DEBUG
		LOG_INFO
		      LOG_WARNING
			    LOG_ERR
				   LOG_CRIT

*/
#include <syslog.h>
#include <string.h>
#include <fcntl.h>
#include <time.h>
#include <stdio.h>

int mysyslog(const char *msg, int level, int driver, int format, const char* path){
	if(strcmp(path, "default") == 0){
		openlog("My_syslog", LOG_CONS, LOG_USER);
		switch(level){
		case 1:
			syslog(LOG_DEBUG,"%s", msg);
			break;
		case 2:
			syslog(LOG_INFO,"%s", msg);
			break;
		case 3:
			syslog(LOG_WARNING,"%s", msg);
			break;
		case 4:
			syslog(LOG_ERR,"%s", msg);
			break;
		case 5:
			syslog(LOG_CRIT,"%s", msg);
			break;
		default: 
			closelog();
			break;
		}
		closelog();
	}
	else{
		int fd = open(path, O_WRONLY|O_CREAT|O_APPEND, S_IWUSR|S_IRUSR|S_IRGRP|S_IROTH);
		
		char *time_str = (char*)malloc(32);
		sprintf(time_str, "%ld", time(NULL));
		write(fd, time_str, 32);

		switch(level){
		case 1:
			write(fd, " DEBUG My_syslog ", 17);
			break;
		case 2:
			write(fd, " INFO My_syslog ", 16);
			break;
		case 3:
			write(fd, " WARNING My_syslog ", 19);
			break;
		case 4:
			write(fd, " ERROR My_syslog ", 17);
			break;
		case 5:
			write(fd, " CRITICAL My_syslog ", 20);
			break;
		default: 
			close(fd);
			break;
		}
		write(fd, msg, 1024);
		close(fd);
	}
	return 0;
}
