#include <iostream>
#include <stdlib.h>
#include <vector>
#include <algorithm>
#include <map>
#include <cmath>
#define N 5

using namespace std;

/*正確さには欠けるが回転させるだけならこれで良いはず*/
int main(){
	int i;
	vector<pair<double,double> > pairs(100);
	pairs[N+1].first = 0;
	pairs[N+1].second = 0;

	cout << "Please enter vertices." << endl;
	for(i = 0; i < N; i++){
		cout << "Vertices " << i+1 << ": ";
		cin >> pairs[i].first;
		cin >> pairs[i].second;
	}

	for(i = 0; i < N; i++)
	{
		pairs[N+1].first += pairs[i].first;
		pairs[N+1].second += pairs[i].second;
	}

	cout << "Center of gravity is (" << pairs[N+1].first/N << "," << 
	pairs[N+1].second/N << ")." << endl;

	return 0;
}