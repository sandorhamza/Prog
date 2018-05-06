#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

int beolvasas_1(int* count, int* max_mutat, int* max_hossz);
double tavolsag(double* PR, double* PRs, int size);

int main(){
    int count = 0, max_mutat = 0, max_hossz = 0;
    if(!beolvasas_1(&count, &max_mutat, &max_hossz)){
	printf("Nincs meg a fajl...\n");
	return 0;
    }
    double d = 0.98;
    char nev[count][max_hossz];			
    int mutat_size[count];			
    char mutat[count][max_mutat][max_hossz];	
						
    printf("Adja meg a d erteket: ");
    scanf("%lf", &d);

    FILE* f;
    f = fopen("adatok.txt", "r");
    char temp[max_hossz];
    
    for(int i = 0; i < count; i++){

	fgets(temp, max_hossz+1, f);
	temp[strlen(temp)-1] = '\0';
	strcpy(nev[i], temp);

	int j = 0;
	while(fgets(temp, max_hossz+1, f) != NULL && strlen(temp) != 1){
	    temp[strlen(temp)-1] = '\0';
	    strcpy(mutat[i][j], temp);

	    j++;
	}
	mutat_size[i] = j;
    }
    fclose(f);
						
    for(int i = 0; i < count; i++){
	printf("%s: ", nev[i]);
	for(int j = 0; j < mutat_size[i]; j++){
	    printf(" %s", mutat[i][j]);
	}
	printf("\n");
    }
						
    double link[count][count];
    double PR[count];
    double PRs[count];
						
    for(int i = 0; i < count; i++){
	PR[i] = 0.0;
    	PRs[i] = 1.0 / count;
	for(int j = 0; j < count; j++){
	    int benne_van = 0;
	    for(int k = 0; k < mutat_size[j]; k++){
		if(strcmp(nev[i], mutat[j][k]) == 0){
		    benne_van = 1;
		    link[i][j] = 1.0 / mutat_size[j];
		    break;
		}
	    }
	    if(!benne_van){
		link[i][j] = 0;
	    }
	    printf("%.2f \t",  link[i][j]);
	}
	printf("\n");
    }
						//PR számolása
    for(;;){
	for(int i = 0; i < count; i++){
	    double temp = 0.0;
	    for(int j = 0; j < count; j++){
		temp += link[i][j]*PRs[j];
	    }
	    PR[i] = d*temp+(1-d)/count;
	}
	if(tavolsag(PR, PRs, count) < 0.000000001){
	    break;
	}
	for(int i = 0; i < count; i++){
	    PRs[i] = PR[i];
	}
    }
    double sum = 0;
    for(int i = 0; i < count; i++){
  	printf("%d.: %.8f\n", i+1, PR[i]);
	sum += PR[i];
    }
    printf("Osszeg: %.4f\n", sum);

    return 0;
}

int beolvasas_1(int* count, int* max_mutat, int* max_hossz){
    FILE* f;
    f = fopen("adatok.txt", "r");
    if(f == NULL){
	return 0;
    }
    int mutat_count = 0;
    char temp[100];
    
    while(fgets(temp, 100, f)){
	*count += 1;
	mutat_count = 0;
	if(strlen(temp) > *max_hossz){
	    *max_hossz = strlen(temp);	
	}
	while(fgets(temp, 100, f) && strlen(temp) != 1){
	    mutat_count++;
	}
	if(mutat_count > *max_mutat){
	    *max_mutat = mutat_count;
	}
    }
    fclose(f);
    return 1;
}

double tavolsag(double* PR, double* PRs, int size){

    double osszeg = 0;
    for(int i = 0; i < size; i++){
	osszeg += (PR[i]-PRs[i])*(PR[i]-PRs[i]);
    }
    return sqrt(osszeg);
}