#include <stdio.h>
#include <stdlib.h>
#include <getopt.h>
#include <errno.h>

static int dem;
static int flag;

static struct option Long_options[] = {
	/*These opts set a flag. */
	{"demonize", 	no_argument, &dem,  1},
	{"flag_on", 	no_argument, &flag, 1},
	{"flag_off", 	no_argument, &flag, 0},
	
	/* These opts doesn't set a flag. */
	{"error", 	no_argument, 	   0, 'e'},
	{"file", 	required_argument, 0, 'f'},
	{"descriptor",  required_argument, 0, 'd'}
};


	
	

int main(int argc, char *argv[]){
	int Option = 0; 
	int Option_index = 0;
	char Short_options[16] = "d:ef:";	//demonize | error | file

	while(1){
		Option = getopt_long(argc, argv, Short_options, Long_options, &Option_index);
		if(Option == -1)
			break;
		
		switch(Option){
			/* If opt has flag. */
			case '0':
				if(Long_options[Option_index].flag != 0)
					break;
				printf("Option %s", Long_options[Option_index].name);
				if(optarg)
					printf(" with args %s", optarg);
				printf("\n");
				break;
			/* If opt has NOT flag. */
			case 'e':
				printf("Option e without args\n");
				break;
			case 'd':
				printf("Option f with args %s\n", optarg);
				break;
			case 'f':
				printf("Option f with args %s\n", optarg);
				break;
			case '?':
				break;
		}
	}

	printf("Flags:\n");
	printf("Demonize - %d\n", dem);
	printf("Flag - %d\n", flag);
}
