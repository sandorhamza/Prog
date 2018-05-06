#include <iostream>

using namespace std;

int main(){

    int count = 0;
    int szo = 1;

    while(szo){
	
	count++;
	szo <<=  1;  			
				
    }

    std::cout << "A szohossz: " << count << std::endl;

    return 0;
}