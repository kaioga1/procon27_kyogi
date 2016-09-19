#include <iostream>
#include <string.h>
#include <stdlib.h>
#define N 5
#define M 11

using namespace std;

class piece{
private:

public:
	int kaku1[N];
	int kaku2[N];
	piece(){
		kaku1[5] = {1,3,5,7,9};
		kaku2[5] = {2,4,6,8,10};
	}
};

int hantei(int sum[],int k){
	piece piece;
	if(sum[0] == 0){
		for(int i = 0; i < N; i++){
			for(int j = 0; j < N; j++){
				if(piece.kaku1[i] + piece.kaku2[j] == M){
					cout << "kaku " << piece.kaku1[i] << " , " << piece.kaku2[j] << endl;
				}else if(piece.kaku1[i] + piece.kaku2[j] < M){
					sum[k] = piece.kaku1[i] + piece.kaku2[j];
					k++;
				}
			}
		}
	}else if(sum != 0){
		for(int i = 0; i < N; i++){
			for(int j = 0;j < k; j++){
				if(piece.kaku1[i] + sum[j] == M){
					cout << "kaku " << piece.kaku1[i] << " , " << sum[j] << endl;
				}else if(piece.kaku2[i] + sum[j] == M){
					cout << "kaku " << piece.kaku2[i] << " , " << sum[j] << endl;
				}else if(piece.kaku1[i] + sum[j] < M){
					sum[k] += piece.kaku1[i];
					k++;
				}else if(piece.kaku2[i] + sum[j] < M){
					sum[k] += piece.kaku2[i];
					k++;
				}
			}
		}
	}
	if(k > 10){
		return k;
	}

	return hantei(sum,k);
}

int main(){
	int j=0,k=0;
	cout << hantei(*j,k) << endl;

	return 0;
}