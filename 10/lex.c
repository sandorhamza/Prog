#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <ctype.h>

int main(){

	char ch[1];

	int betu = 0;
	int sor = 0;
	int szam = 0;
	int space = 0;
	int spec = 0;

	while(read(0, (void*) ch, sizeof(char))){
 		if(ch[0] == ' ' || ch[0] == '\t'){
			space++;
		}	
		if(isalpha(ch[0])){
			betu++;
		}
		if(isdigit(ch[0])){
			szam++;
		}
		if(ch[0] == '\n'){
			sor++;
		}
		if(ispunct(ch[0])){
			spec++;
		}	

	}
	printf("Betu: %d\nSzam: %d\nSor: %d\nSpec: %d\nSpace: %d\n", betu, szam, sor, spec, space);

}