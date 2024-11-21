/*

structure of json log file
{"timestamp": ..., "log_level": ..., "process": ..., "message": ...}
{	      int, 		str, 		str, 		str}

*/
#include "yyjson.c"
#include <stdio.h>
#include <unistd.h>
#include <fcntl.h>
#include <time.h>

int mysyslog(const char* msg, int level, int driver, int format, const char* path){

	if(strcmp(path, "default") == 0)
		path = "/var/log/syslog";

	int fd = open(path, O_WRONLY|O_CREAT|O_APPEND, S_IWUSR|S_IRUSR|S_IRGRP|S_IROTH);

	yyjson_mut_doc *doc = yyjson_mut_doc_new(NULL);
	yyjson_mut_val *root = yyjson_mut_obj(doc);
	yyjson_mut_doc_set_root(doc, root);

	yyjson_mut_obj_add_int(doc, root, "timestamp", time(NULL));
	switch(level){
	case 1:
		yyjson_mut_obj_add_str(doc, root, "log_level", "DEBUG");
		break;
	case 2:
		yyjson_mut_obj_add_str(doc, root, "log_level", "INFO");
		break;
	case 3:
		yyjson_mut_obj_add_str(doc, root, "log_level", "WARINNG");
		break;
	case 4:
		yyjson_mut_obj_add_str(doc, root, "log_level", "ERROR");
		break;
	case 5:
		yyjson_mut_obj_add_str(doc, root, "log_level", "CRITICAL");
		break;
	default: 
		break;
	}

	yyjson_mut_obj_add_str(doc, root, "process", "My_syslog");
	yyjson_mut_obj_add_str(doc, root, "message", msg);


	const char *json = yyjson_mut_write(doc, 0, NULL);

	if (json) {
		write(fd, json, 1024);
		write(fd, "\n", 1);
		free((void *)json);
	}

	yyjson_mut_doc_free(doc);
	close(fd);
	return 0;
}
