#include <dlfcn.h>
#include <fcntl.h>
#include <getopt.h>
#include <signal.h>
#include <stdio.h>
#include <stdlib.h>
#include <stddef.h>
#include <string.h>
#include <time.h>
#include <unistd.h>
#include <stdint.h>

#define CNT_OPTIONS 5
#define CONFIG "/etc/mysyslog/mysyslog.cfg"
#define PIDFile "/usr/run/mysyslog-daemon.pid"

void daemonize();	
void interrupt_handler();
void terminate_handler();
void info_handler();
int read_config();
int mysyslog(const char *msg, int level, int driver, int format, const char *path);

char *args[CNT_OPTIONS];

int main(int argc, char *argv[]){
	daemonize();
	
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

	int fd = open(PIDFile, O_WRONLY|O_CREAT);
	dprintf(fd, "%d\n", pid);
	close(fd);

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
