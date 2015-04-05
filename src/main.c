/*
 ============================================================================
 Name        : Autor.c
 Author      : zakp2
 Version     :
 Copyright   : Your copyright notice
 Description : Hello World in C, Ansi-style
 ============================================================================
 */


#include <stdio.h>
#include <stdlib.h>
#include "struktury.h"

int main(int argc,char **argv) {

	parameters *param;
	param=new_parameters();
	param->b_in_v[1001]='a';
	int i=1;

	while(i<argc){
		if(strcmp(argv[i],"-in")==0){
			param->in++;
			while(argv[++i][0]!='-'){
				if( (sizeof(argv[i])/4) < MAX_DN){
					add_to_in_vector(param->in_v,argv[i]);
				}
				else
					printf("Ścierzka do pliku zbyt duża: %s \n",argv[i]);
			}
		}
		if(strcmp(argv[i],"-n_gram")==0){
			param->n_gram=atoi(argv[++i]);
			}
		if(strcmp(argv[i],"-out")==0){
			if(argv[++i][0]!='-'){
				if( ( (sizeof(argv[i])/4) < MAX_DN )){
					param->out++;
					strcpy(param->out_v,argv[i]);
				}
				else
					printf("Ścierzka do pliku zbyt duża: %s \n",argv[i]);
			}
			else
				printf("Domyślna wartość zapisu pliku z wygenerowanym tekstem \n");
		}
		if(strcmp(argv[i],"-b_in")==0){
			param->b_in++;
			if(argv[++i][0]!='-'){
				if( ( (sizeof(argv[i])/4) < MAX_DN )){
					strcpy(param->b_in_v,argv[i]);
				}
				else
					printf("Ścierzka do pliku zbyt duża: %s \n",argv[i]);
				}
			else
				printf("Domyślna wartość ścierzki do wczytywanej bazy \n");
		}
		if(strcmp(argv[i],"-b_out")==0){
			param->b_out++;
			if(argv[++i][0]!='-'){
				if( ( (sizeof(argv[i])/4) < MAX_DN )){
					strcpy(param->b_out_v,argv[i]);
					}
				else
					printf("Ścierzka do pliku zbyt duża: %s \n",argv[i]);
			}
			else
				printf("Domyślna wartość ścierzki do zapisu bazy\n");

		}
		if(strcmp(argv[i],"-par")==0){
			if(atoi(argv[++i]))
				param->par=atoi(argv[++i]);
			else
				printf("Żła wartość -par : %s \n",argv[i]);
		}
		if(strcmp(argv[i],"-wrd")==0){
			if(atoi(argv[++i]))
				param->wrd=atoi(argv[++i]);
			else
				printf("Żła wartość -wrd : %s \n",argv[i]);
		}
		if(strcmp(argv[i],"-stat")==0){
			if(argv[++i][0]!='-'){
				if( ( (sizeof(argv[i])/4) < MAX_DN )){
					param->stat++;
					strcpy(param->stat_out_v,argv[i]);
				}
				else
					printf("Ścierzka do pliku zbyt duża: %s \n",argv[i]);
				}
			else
				printf("Domyślna wartość zapisu pliku z wygenerowanymi statystykami \n");
		}
	}

	return 0;
}
