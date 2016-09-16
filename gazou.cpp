#include <iostream>
#include <string.h>
#include <stdlib.h>
#define N 10

using namespace std;

int main(){
	int i,j,omake[100],make[100],ake[100],g=0,k=0,tetsu[100],kuzu[100],kaku[N] = {21,34,67,28,42,19,30,71,19,20};
	for(i=0; i < N; i++){
		for(j=0; j < N; j++){
			if(kaku[i] + kaku[j] == 90){
				cout << "kaku " << kaku[i] << " & " << kaku[j] << " DEATH" << endl;
			}else if(kaku[i] + kaku[j] < 90){
				tetsu[k] = kaku[i];
				kuzu[k] = kaku[j];
				k++;
			}
		}
	}

	if(k > 0){
		for(i=0; i < N; i++){
			for(j=0; j < k; j++){
				if(kaku[i] + tetsu[j] + kuzu[j] == 90){
					cout << "kaku" << kaku[i] << " & " << tetsu[j] << " & " << kuzu[j]  << " DEATH " << endl;
				}else if(kaku[i] + tetsu[j] + kuzu[j] < 90){
					omake[g] = kaku[i];
					make[g] = tetsu[j];
					ake[g] = kuzu[j];
					g++;
				}
			}
		}
	}

	if(g > 0){
		for(i=0; i < N; i++){
			for(j=0; j < g; j++){
				if(kaku[i] + omake[j] + make[j] + ake[j] == 90){
					cout << "kaku" << kaku[i] << " & " << omake[j] << " & " << make[j] << " & " << ake[j] << "DEATH" << endl;
				}
			}
		}
	}

	return 0;
}

//まだ4つまでの分しか出来てません
