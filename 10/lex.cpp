#include <iostream>
#include <fstream>
#include <ctype.h>

using namespace std;

int main(){

	ifstream fin;
	fin.open("üzenet");
	
	char ch;

	int betu = 0;
	int sor = 0;
	int szam = 0;
	int space = 0;
	int spec = 0;

	while(fin.get(ch)){
 		if(ch == ' ' || ch == '\t'){
			space++;
		}	
		if(isalpha(ch)){
			betu++;
		}
		if(isdigit(ch)){
			szam++;
		}
		if(ch == '\n'){
			sor++;
		}
		if(ispunct(ch)){
			spec++;
		}	

	}
	fin.close();
	cout << "Szam: " << szam << "\nBetu: " << betu << "\nSpace: " << space << "\nSor: " << sor << "\nSpec: " << spec << endl;

}