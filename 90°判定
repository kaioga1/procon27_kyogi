#include <iostream>
#include <string.h>
#include <stdlib.h>
#define N 10

using namespace std;

int main(){
	int i,j,k=0,tetsu[100],kuzu[100],kaku[N] = {21,34,67,28,42,19,30,71,19,20};
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

	for(i=0; i < N; i++){
		for(j=0; j < k; j++){
			if(kaku[i] + tetsu[j] + kuzu[j] == 90){
				cout << "kaku" << kaku[i] << " & " << tetsu[j] << " & " << kuzu[j]  << " DEATH " << endl;
			}
		}
	}

	return 0;
}

//まだ3つまでの分しか出来てません
