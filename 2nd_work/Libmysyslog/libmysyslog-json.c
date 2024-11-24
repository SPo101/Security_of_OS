/*

structure of json log file
{"timestamp": ..., "log_level": ..., "process": ..., "message": ...}
{	      int, 		str, 		str, 		str}

*/
#include <stdio.h>
#include <unistd.h>
#include <fcntl.h>
#include <time.h>
#include <string.h>

int mysyslog(const char* msg, int level, int driver, int format, const char* path){

	if(strcmp(path, "default") == 0)
		path = "/var/log/syslog";

	int fd = open(path, O_WRONLY|O_CREAT|O_APPEND, S_IWUSR|S_IRUSR|S_IRGRP|S_IROTH);

	char *level_str = NULL;
	char *proc = "My_syslog";
	switch(level){
	case 1:
		level_str = "DEBUG";
		break;
	case 2:
		level_str = "INFO";
		break;
	case 3:
		level_str = "WARNING";
		break;
	case 4:
		level_str = "ERROR";
		break;
	case 5:
		level_str = "CRITICAL";
		break;
	default: 
		break;
	}


	dprintf(fd, "{\"timestamp\":%ld, \"log_level\": %s, \"process\": %s, \"message\": %s}\n", time(NULL), level_str, proc, msg);	

	close(fd);
	return 0;
}
