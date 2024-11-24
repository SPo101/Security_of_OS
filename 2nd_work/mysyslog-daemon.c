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
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <getopt.h>
#include <dlfcn.h>
#include <fcntl.h>
#include <stddef.h>
#include <string.h>
#include <signal.h>
#include <time.h>

#define CNT_OPTIONS 5
#define LIBRARY "Libmysyslog/libmysyslog.so"
#define LOG_FUNC "mysyslog"
#define CONFIG "/etc/mysyslog/mysyslog.cfg"

void daemonize();	
void interrupt_handler();
void terminate_handler();
void info_handler();
int read_config();

char *args[CNT_OPTIONS];

int main(int argc, char *argv[]){
	
	daemonize();
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

	if(read_config()){
		fprintf(stderr, "Error while reading config file\n");
		exit(EXIT_FAILURE);
	}
	signal(SIGINT, interrupt_handler);
	signal(SIGTERM, terminate_handler);
	signal(SIGINFO, info_handler);

	time_t sec;
	while(1){
		sec = time(NULL);
		if(sec % (10 * 1) == 0)
			mysyslog(args[0], atoi(args[1]), atoi(args[2]), atoi(args[3]), args[4]);
			sleep(1);
	}

	if(dlclose(library) != 0){
		fprintf(stderr, "%s\n", dlerror());
		exit(EXIT_FAILURE);
	}
	exit(EXIT_SUCCESS);
}

int read_config(){
	int fd = open(CONFIG, O_RDONLY);

	int offset = lseek(fd, 0, SEEK_END);
	lseek(fd, 0, SEEK_SET);
	
	char *string = malloc(offset);
	read(fd, string, offset);

	size_t place_eq = 0;
	size_t place_end = 0;
	for(int i=0; i<CNT_OPTIONS; i++){
		place_eq += (1 + strcspn(string+place_eq, "="));
		place_end += 1 + strcspn(string+place_end, "\n");

		args[i] = malloc(place_end-place_eq);
		memcpy(args[i], string+place_eq, place_end - place_eq -1);
	}

	free(string);
	close(fd);
	return 0;
}

void interrupt_handler(){
	exit(EXIT_SUCCESS);
}
void terminate_handler(){
	exit(EXIT_FAILURE);
}
void info_handler(){
	printf("Message: %s\n", args[0]);
	printf("Level: %d\n", atoi(args[1]));
	printf("Driver: %d\n", atoi(args[2]));
	printf("Format: %d\n", atoi(args[3]));
	printf("Path: %s\n", args[4]);
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
