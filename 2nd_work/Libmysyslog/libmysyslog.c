#include <syslog.h>
#include <dlfcn.h>
#include <stddef.h>
#include <stdlib.h>
#include <stdio.h>

#define JSON "Libmysyslog/libmysyslog-json.so"
#define TEXT "Libmysyslog/libmysyslog-text.so"

#define FUNC "mysyslog"

int mysyslog(const char *msg, int level, int driver, int format, const char* path){
	
	void *library;
	void (*log_func)(const char*, int, int, int, const char*);

	if(driver)
		library = dlopen(JSON, RTLD_LAZY|RTLD_GLOBAL);
	else
		library = dlopen(TEXT, RTLD_LAZY|RTLD_GLOBAL);

	if(library == NULL){
		fprintf(stderr, "Opening lib: %s", dlerror());
		return 1;
	}
	dlerror();
		
	log_func = dlsym(library, FUNC);
	if(log_func == NULL){
		fprintf(stderr, "Calling func: %s", dlerror());
		return 1;
	}
	dlerror();

	log_func(msg, level, driver, format, path);

	if(dlclose(library) != 0){
		fprintf(stderr, "Closing lib: %s", dlerror());
		return 1;
	}
	dlerror();

	return 0;
}
