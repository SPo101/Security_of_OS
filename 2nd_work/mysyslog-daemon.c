/*
Сделать тестовое приложение демон mysyslog-daemon, 
который автоматически запускается во время старта компьютера 
и постоянно выводит в лог данные с разным уровнем. 
Приложение настраивается при помощи конфигурационного файла /etc/mysyslog/mysyslog.cfg. 
В конфигурационном файле задается: путь, формат и драйвер. 
Демон должен корректно обрабатывать получаемые сигналы 
и должен запускаться и останавливаться через systemctl.

int mysyslog(const char* msg, int level, int driver, int format, const char* path);


*/
#include <stdio.h>
#include <stdlib.h>
#include <getopt.h>
#include <dlfcn.h>
#include <stddef.h>
#include <signal.h>
#include <time.h>

#define LIBRARY "Libmysyslog/libmysyslog.so"
#define LOG_FUNC "mysyslog"
#define CONFIG "/etc/mysyslog/mysyslog.cfg"

void daemonize();	
void interrupt_handler();
void terminate_handler();
void info_handler();

int main(int argc, char *argv[]){
	
	void *library;
	void (*mysyslog)(const char*, int, int, int, const char*);


	
	library = dlopen(LIBRARY, RTLD_LAZY | RTLD_GLOBAL);
	if(library == NULL){
		fprintf(stderr, "%s\n", dlerror());
		exit(EXIT_FAILURE);
	}
	dlerror();

	mysyslog = dlsym(library, LOG_FUNC);
	if(mysyslog == NULL){
		fprintf(stderr, "%s\n", dlerror());
		exit(EXIT_FAILURE);
	}
	dlerror();

	daemonize();
	//signal(SIGINT, interrupt_handler);
	//signal(SIGTERM, terminate_handler):
	//signal(SIGINFO, info_handler):
	time_t sec;
	while(1){
		sec = time(NULL);
		if(sec % (10 * 60) == 0)
			//mysyslog(args[0], *(int*) args[1], *(int*) args[2], *(int*) args[3], args[4]);
			sleep(1);
	}

	if(dlclose(library) != 0){
		fprintf(stderr, "%s\n", dlerror());
		exit(EXIT_FAILURE);
	}
	exit(EXIT_SUCCESS);
}


void daemonize(){
	pid_t pid = fork();

	if( pid > 0)// parent process
		exit(EXIT_SUCCESS);

	if(setsid() == -1){
		printf("error");
		exit(EXIT_FAILURE);
	}

	pid = fork();
	if( pid > 0)// parent process
		exit(EXIT_SUCCESS);

	chdir("/");
	
	for(int fd = sysconf(_SC_OPEN_MAX); fd > 0; fd--)
		close(fd);
	
	fclose(stdin);
	fclose(stdout);
	fclose(stderr);

	stdin = fopen("/dev/null", "r");
	stdout = fopen("/dev/null", "w");
	stderr = fopen("/dev/null", "w");
}
