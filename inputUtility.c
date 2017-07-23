#include "inputUtility.h"

int validatFiles(char ** params, int count, int hhLocation);
int validatOptions(char ** params, int count, int hhLocation);

//Executes all validations to make sure that the input matches the right format
int verifyInput(char ** params, int count){
	int valid, i=-1,hhLocation=-1;

	for(i=0; i<count; i++){
		if(strcmp("--", params[i])==0){
			hhLocation=i;
			break;
		}
	}
	if(hhLocation<0){
		printf("Incorrect Format, -- is missing\n");
		return 0;
	}
	if(hhLocation==0){
		printf("Incorrect Format, Options are missing\n");
		return 0;
	}
	if(hhLocation==count-1){
		printf("Incorrect Format, Please provide file(s) name(s)\n");
		return 0;
	}
	if(params[hhLocation-1][0]=='-' || params[hhLocation-2][0]=='-'){
		printf("Incorrect Format, Please provide <from> and <to> inputs!\n");
		return 0;
	}
	valid=validatFiles(params, count, hhLocation);
	if(!valid) return 0;
	valid=validatOptions(params, count, hhLocation);
	if(!valid) return 0;
	
	return hhLocation;
}
//Validates input files for wrong naming
int validatFiles(char ** params, int count, int hhLocation){
	int i;
	for(i=hhLocation+1;i<count; i++){
		if(strcmp(".txt", &params[i][strlen(params[i])-4])!=0){
			printf("Incorrect Parameter Format, File %s 's extensin is not correct!\n", params[i]);
			return 0;;
		} 
	}
	return 1;
}
//Validates input options for wrong inputs
int validatOptions(char ** params, int count, int hhLocation){
	int i;
	char temp;
	for(i=0;i<hhLocation-2; i++){
		if(strlen(params[i])!=2){
			printf("Incorrect Parameter Format, Parameter %i is not correct!\n", i+1);
			return 0;
		}
		switch(params[i][1]){		
			case 'b':
				break;
			case 'f':
				break;
			case 'i':
				break;
			case 'l':
				break;
			default:
				printf("Incorrect Parameter Format, Parameter %i is not correctt!\n", i+1);
				return 0;	
		}
	}
	return 1;
}
//Extracts all input options and filter redundancy
char * getOptions(char ** params, int hhLocation){
	int i;
	char *options=(char *)calloc(4,sizeof(int));
	options[3]=1;
	for(i=0;i<hhLocation-2; i++){
		switch(params[i][1]){	
			case 'b':
				options[0]='b';
				break;
			case 'f':
				options[1]='f';
				break;
			case 'l':
				options[2]='l';
				break;
			case 'i':
				options[3]=0;
				break;
			default:
				break;	
		}
	}

	return options;
}