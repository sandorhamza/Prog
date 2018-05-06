#include <iostream>
#include <cmath>
#include <stdlib.h>
#include <fstream>
#include <vector>

using namespace std;

struct link{
    string nev;
    vector<string> mutat;
    
    link(string str){
	nev = str;
    }
};

double tavolsag(double PR[], double PRs[], int n);
double osszeg(double PR[], int n);
bool beolvas(vector<link>& vec);

int main(){
    vector<link> linkek;
    double d; 						
							
    if(!beolvas(linkek)){
    	cerr << "Nem sikerult beolvasni a fajlt..." << endl;
	return 0;
    }
    cout << "Add meg a 'd' erteket: ";
    cin >> d;
    cout << "---------------------------------------------------------------" << endl;
    for(int i = 0; i < linkek.size(); i++){
	cout << linkek[i].nev << " : ";
	for(int j = 0; j < linkek[i].mutat.size(); j++){
	    cout << linkek[i].mutat[j] << ", ";
	}
	cout << endl;

    }
						
    double link[linkek.size()][linkek.size()];
    double PR[linkek.size()];	
    double PRs[linkek.size()];	
    cout << "---------------------------------------------------------------" << endl;
    for(int i = 0; i < linkek.size(); i++){		
	PR[i] = 0.0;
	PRs[i] = 1.0 / linkek.size();
	for(int j = 0; j < linkek.size(); j++){
	    bool benne_van = false;
	    for(int k = 0; k < linkek[j].mutat.size(); k++){
		if(linkek[j].mutat[k].compare(linkek[i].nev) == 0){
		    benne_van = true;
		    link[i][j] = 1.0 / linkek[j].mutat.size();
		    break;
		}
	    }
	    if(!benne_van){
		link[i][j] = 0;
	    }
	    cout << link[i][j] << "\t";
	}
	cout << endl ;
    }
    cout << "---------------------------------------------------------------" << endl;
		

    while(true){
							
	for(int i = 0; i < linkek.size(); i++){
	    double temp = 0;					
     	    for(int j = 0; j < linkek.size(); j++){
		temp += link[i][j]*PRs[j]; 
	    }
	    PR[i] = d*temp+(1-d)/linkek.size();
	}

	if(tavolsag(PR, PRs, linkek.size()) < 0.000000001){
	    break;
	}

	for(int i = 0; i < linkek.size(); i++){
	    PRs[i] = PR[i];				
	}
    }
								
    cout << "Osszeg: " << osszeg(PR, linkek.size()) << endl;
    cout << "---------------------------------------------------------------" << endl;
    return 0;
}

double tavolsag(double PR[], double PRs[], int n){
								
    double sum = 0;			

    for(int i = 0; i < n; i++){
	sum += abs(PR[i]-PRs[i]);
    }
    return sum;
}

double osszeg(double PR[], int n){
   
    double sum = 0;
    
    for(int i = 0; i < n; i++){
	cout << i+1 << ".: " << PR[i] << endl;		
    	sum += PR[i];
   }
   return sum;
}

bool beolvas(vector<link>& vec){
    
    ifstream input;
    input.open("adatok.txt");
    if(!input.is_open()){
	return false;
    }
    string temp;
    while(getline(input, temp)){
	vec.push_back(link(temp));
	while(getline(input, temp) && temp.length() != 0){
	    vec[vec.size()-1].mutat.push_back(temp);
	}
    }
    
    input.close();
    return true;
}