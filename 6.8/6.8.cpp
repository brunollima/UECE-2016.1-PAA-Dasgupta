#include <iostream>
#include <stdio.h>
#include <string>

using namespace std;

int main(){
	int equal = 0, max = 0, aux = 0;
	int smp;  
	string string1, string2;

	getline(cin, string1);
	scanf("\n");
	getline(cin, string2);
	//scanf("\n");

	while (!cin.eof()){
		max = 0;

		for(int i = 0; string1[i] != '\0'; i++){
			for(int j = 0; string2[j] != '\0'; j++){
				if(string1[i] == string2[j]){
					equal++;
					aux++;
					i++;
					if(equal > max){
						max = equal;
						smp = i;
					}
				}
				else{
					equal = 0;
					i -= aux;
					aux = 0;
				}
			}
			equal = 0;
			aux = 0;
			i-= aux;
		}
		cout << max << endl;
		
		for (int i = (smp - max); i < smp; ++i)
			cout << string1[i];
		cout << endl;

		getline(cin, string1);
		scanf("\n");
		getline(cin, string2);
		//scanf("\n");
	}
}