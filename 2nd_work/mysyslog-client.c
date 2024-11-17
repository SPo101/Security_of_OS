/*
Сделать тестовое приложение на языке Си mysyslog-client, 
которое использует библиотеку libmysyslog 
и позволяет в аргументах командной строки задавать выводимый через библиотеку libmysyslog текст, 
уровень записи журнала, используемый драйвер и формат и путь к файлу. 
Аргументы командной строки обрабатывать через getopt.


int mysyslog(const char* msg, int level, int driver, int format, const char* path);


*/
#include <stdio.h>
#include <stdlib.h>
#include <getopt.h>
#include <dlfcn.h>
#include <stddef.h>


#define CNT_OPTIONS 5
#define LIBRARY "libmysyslog.so"
#define LOG_FUNC "mysyslog"

static struct option Long_options[] = {
	{"message", 	required_argument, 0, 0},
	{"level", 	required_argument, 0, 0},
	{"driver",  	required_argument, 0, 0},
	{"format", 	required_argument, 0, 0},
	{"path", 	required_argument, 0, 0}
};
static char *Short_options = "m:l:d:f:p:";	//msg | lvl | driv | form | path

void Usage(){
	printf("Usage\n");
	printf("\tuse all of options:\n");
	printf("-m --message Message to log\n");
	printf("-l --level   Level of importance\n");
	printf("-d --driver  \n");
	printf("-f --format  \n");
	printf("-p --path    \n");
}
	
int check_args(char **args){
	for(int i=0; i<CNT_OPTIONS; i++)
		if(*(args+i) == NULL)
			return -1;
	return 0;
}

int main(int argc, char *argv[]){
	
	if(argc < 2)
		Usage();

	int Option = 0; 
	int Option_index = 0;
	char *args[CNT_OPTIONS]; 
	void *library;
	void (*mysyslog)(const char*, int, int, int, const char*);

	while(1){
		Option = getopt_long(argc, argv, Short_options, Long_options, &Option_index);
		if(Option == -1)
			break;
		
		switch(Option){
			case 0:
				args[Option_index] = optarg;
				break;
			case 'm':
				args[0] = optarg;
				break;
			case 'l':
				args[1] = optarg;
				break;
			case 'd':
				args[2] = optarg;
				break;
			case 'f':
				args[3] = optarg;
				break;
			case 'p':
				args[4] = optarg;
				break;
			case '?':
				break;
		}
	}

	if(check_args(args) == -1){
		fprintf(stderr, "Not all parameters were given\n");
		exit(EXIT_FAILURE);
	}
	
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

	mysyslog(args[0], *(int*) args[1], *(int*) args[2], *(int*) args[3], args[4]);

	if(dlclose(library) != 0){
		fprintf(stderr, "%s\n", dlerror());
		exit(EXIT_FAILURE);
	}
	exit(EXIT_SUCCESS);
}
