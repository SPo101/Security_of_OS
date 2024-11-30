#include <stdio.h>
#include <stdlib.h>
#include <getopt.h>
#include <dlfcn.h>
#include <stddef.h>


#define CNT_OPTIONS 5


void Usage();
int check_args(char **);
int mysyslog(const char *msg, int level, int driver, int format, const char *path);

int main(int argc, char *argv[]){
	
	if(argc < 2){
		Usage();
		fprintf(stderr, "Not all parameters were given\n");
		exit(EXIT_FAILURE);
	}

	int Option = 0; 
	int Option_index = 0;
	char *args[CNT_OPTIONS]; 

	static struct option Long_options[] = {
		{"message", 	required_argument, 0, 'm'},
		{"level", 	required_argument, 0, 'l'},
		{"driver",  	required_argument, 0, 'd'},
		{"format", 	required_argument, 0, 'f'},
		{"path", 	required_argument, 0, 'p'}
	};
	static char *Short_options = "m:l:d:f:p:";	//msg | lvl | driv | form | path

	while(1){
		Option = getopt_long(argc, argv, Short_options, Long_options, &Option_index);
		if(Option == -1)
			break;
		
		switch(Option){
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

	mysyslog(args[0], atoi(args[1]), atoi(args[2]), atoi(args[3]), args[4]);
	exit(EXIT_SUCCESS);
}

void Usage(){
	printf("Usage\n");
	printf("\tuse all of options:\n");
	printf("-m --message Message to log\n");
	printf("-l --level   Level of importance: 1-DEBUG 2-INFO 3-WARN 4-ERR 5-CRIT\n");
	printf("-d --driver  Driver: 0-text 1-json\n");
	printf("-f --format  Format\n");
	printf("-p --path    File to log or 'default'\n");
}
	
int check_args(char **args){
	for(int i=0; i<CNT_OPTIONS; i++)
		if(*(args+i) == NULL)
			return -1;
	return 0;
}
