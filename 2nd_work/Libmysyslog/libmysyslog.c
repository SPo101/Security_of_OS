#include <syslog.h>
#include <dlfcn.h>
#include <stddef.h>
#include <stdlib.h>

#define JSON "libmysyslog-json.so"
#define TEXT "libmysyslog-text.so"

int mysyslog(const char *msg, int level, int driver, int format, const char* path){
	void *library;
	void (*log_func)(const char*, int, int, int, const char*);
	
	if(driver)
		library = dlopen(JSON, RTLD_LAZY|RTLD_GLOBAL);
	else
		library = dlopen(TEXT, RTLD_LAZY|RTLD_GLOBAL);
	
	if(library == NULL)	
		return 1;
		
	log_func = dlsym(library, "mysyslog");
	log_func(msg, level, driver, format, path);

	if(dlclose(library) != 0)
		return 1;

	return 0;
}
