#include "replaceUtility.h"

char * replace(char *original, char *from, char *to, char option, int sensitive);
char ** wordsLocation(char * input, int wordsCount, char *word, char option , int sensitive);
int numOfWords(char *str, char *subStr, char option, int sensitive);

//Parses the input parameters and take actions based on them
void handler(char ** params, int numOfParams){
	int i,valid=0, numOfFiles, hhLocation;
	char *from, *to, * options, * tempFileContent;

	valid=verifyInput(params, numOfParams);
	if(!valid)exit(1);
	hhLocation = valid;
	
	from = params[hhLocation-2];
	to = params[hhLocation -1];
	options= getOptions(params, hhLocation);
	numOfFiles = numOfParams-hhLocation-1;
	
	for(i=0; i<numOfFiles; i++){
		//printf("File %s\n", params[hhLocation+i+1]);
		tempFileContent=readFile(params[hhLocation+i+1]);
		if(options[0]=='b') createBackup(params[hhLocation+i+1]);
		if(options[1]=='f') tempFileContent=replace(tempFileContent, from, to, 'f', options[3]);
		if(options[2]=='l') tempFileContent=replace(tempFileContent, from, to, 'l', options[3]); 
		if(options[1]!='f' && options[2]!='l') tempFileContent=replace(tempFileContent, from, to, 'a', options[3]);		
		writeFile(params[hhLocation+i+1], tempFileContent);
	}
	free(options);
	printf("All words are replaced successfully!\n");
}
//Writes string to a file
void writeFile(char *location, char *fileData){
	FILE *pFile = fopen(location, "w");
	fputs(fileData, pFile);
	fclose(pFile);
	return;
}
//Reads a file
char * readFile(char *location){
	char *fileContent=NULL;
	int fileSize=0;
	FILE *pFile = fopen(location, "r");
	fseek(pFile, 0L, SEEK_END);
	fileSize = ftell(pFile)+1;
	rewind(pFile);
	fileContent=(char *)malloc(sizeof(char)*fileSize);
	fgets(fileContent, fileSize, pFile);
	fclose(pFile);
	return fileContent;
}
//Creates backup files
void createBackup(char *fName){
	char bfName[strlen(fName)+1];
	char * temp;
	bfName[0]='_';
	strcat(bfName, fName);
	temp =readFile(fName);
	writeFile(bfName, temp);
	free(temp);
	return;
}
//Replaces all "from"s with all "to"s
char * replace(char *original, char *from, char *to, char option, int sensitive){
	int i,j,length=0,countOld=0, countNew=0;
	int fromLen =strlen(from);
	int toLen = strlen(to);
	int newStringSize=0;
	int nOfWords= numOfWords(original,from, option, sensitive);
	if(nOfWords==0){
		printf("No %s found!\n", from);
		return original;
	}
	newStringSize=strlen(original)+nOfWords*(strlen(to)-strlen(from)+1);
	char *newString=(char *)calloc(newStringSize,sizeof(char));
	char **locations= wordsLocation(original, nOfWords, from, option, sensitive);
	newString[newStringSize-1]='\0';

	length=(locations[1]-locations[0]);
	for(j=0;j<length;j++){
			newString[countNew]=original[countOld];
			countNew++; countOld++;
	}
	for(i=0;i<nOfWords;i++){
		for(j=0;j<toLen;j++){
			newString[countNew]=to[j];
			countNew++;
		}
		countOld+=fromLen;
		length=locations[i+2]-locations[i+1]-fromLen;
		for(j=0;j<length;j++){
			newString[countNew]=original[countOld];
			countNew++; countOld++;
		}	
	}
	free(locations);
	return newString;
}
//Returns locations of "from" words in the String buffer of the targeted file
char ** wordsLocation(char * input, int wordsCount, char *word, char option , int sensitive){
	int i=1;
	char *tempLocation=NULL, *sStartPos=NULL;
	int subString_length = strlen(word);
	char **locations=(char**)calloc(wordsCount+2, sizeof(char*));
	char *sInput=(char *)malloc(strlen(input));
	char *sWord=(char *)malloc(strlen(word));

	if(!sensitive){
		for(i = 0 ; (sInput[i] = tolower(input[i])) != '\0' ; i++);
		for(i = 0 ; (sWord[i] = tolower(word[i])) != '\0' ; i++);
	}else{
		for(i = 0 ; (sInput[i] = input[i]) != '\0' ; i++);
		for(i = 0 ; (sWord[i] = word[i]) != '\0' ; i++);
	}
	sStartPos=sInput;
	locations[0]=input;
	locations[wordsCount+1]=locations[0]+strlen(input);
	switch(option){
		case 'f':
			locations[1]=input+(strstr(sInput, sWord)-sInput);
			break;
		case 'l':
			while(1){	
				tempLocation= strstr(sInput, sWord);
				if(tempLocation == NULL) break;
				locations[1]=tempLocation;
				sInput=locations[1]+subString_length;
			}
			locations[1]=input+(locations[1]-sStartPos);
			break;
		default:
			i=1;
			sStartPos=sInput;
			while(i<wordsCount+1){	
				locations[i]= strstr(sInput, sWord);
				sInput=locations[i]+subString_length;
				locations[i]=input+(locations[i]-sStartPos);
				i++;
			}
	}
	free(sInput); free(sWord);
	return locations;
}
//Counts how many of "from" words are in the file.
int numOfWords(char *str, char *subStr, char option, int sensitive){
	int num=0, i=0;
	char *pfound=NULL;
	int subString_length = strlen(subStr);
	char *sStr=(char *)malloc(strlen(str));
	char *sSubStr=(char *)malloc(strlen(subStr));

	if(!sensitive){
		for(i = 0 ; (sStr[i] = tolower(str[i])) != '\0' ; i++);
		for(i = 0 ; (sSubStr[i] = tolower(subStr[i])) != '\0' ; i++);
	}else{
		for(i = 0 ; (sStr[i] = str[i]) != '\0' ; i++);
		for(i = 0 ; (sSubStr[i] = subStr[i]) != '\0' ; i++);
	}
	switch(option){
		case 'f':
			pfound =strstr(sStr, sSubStr);	
			if(pfound ==NULL){
				free(sStr); free(sSubStr);
				return 0;
			} else {
				free(sStr); free(sSubStr);
				return 1;
			}
		case 'l':
			pfound =strstr(sStr, sSubStr);	
			if(pfound ==NULL){
				free(sStr); free(sSubStr);
				return 0;
			} else {
				free(sStr); free(sSubStr);
				return 1;
			}
		default:		
			while(1){			
				pfound =strstr(sStr, sSubStr);	
				if(pfound ==NULL){
					free(sStr); free(sSubStr);
					return num;
				}
				sStr=pfound+subString_length;
				num++;
			}
	}
}