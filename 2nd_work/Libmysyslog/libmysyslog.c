#include <syslog.h>

#define JSON "libmysyslog-json.so"
#define NSTR "libmysyslog-text.so"

int mysyslog(const char *msg, int level, int driver, int format, const char* path){
	openlog("My_syslog_client", LOG_CONS, LOG_USER);
	syslog(LOG_INFO,"%s", msg);
	closelog();
	return 0;
}