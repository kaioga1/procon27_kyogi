#include <iostream>
#include <stdlib.h>
#include <vector>
#include <algorithm>
#include <map>
#include <cmath>

using namespace std;

void sankaku(){
	vector<pair<double,double> > pairs(10);
	pairs[0] = make_pair(10,0);
	pairs[1] = make_pair(4,5);
	pairs[2] = make_pair(12,4);

	pairs[3] = make_pair((pairs[0].first + pairs[1].first + pairs[2].first)/3
						,(pairs[0].second + pairs[1].second + pairs[2].second)/3);
	cout << "(" << pairs[3].first << "," << pairs[3].second << ")" << endl;
}

void sikaku(){
	vector<pair<double,double> > pairs(10);
	pairs[0] = make_pair(10,0);
	pairs[1] = make_pair(4,5);
	pairs[2] = make_pair(12,4);
	pairs[3] = make_pair(16,5);

	pairs[4] = make_pair((pairs[0].first + pairs[1].first + pairs[2].first)/3
						,(pairs[0].second + pairs[1].second + pairs[2].second)/3);
	cout << pairs[4].first << pairs[4].second << endl;
	pairs[5] = make_pair((pairs[0].first + pairs[2].first + pairs[3].first)/3
						,(pairs[0].second + pairs[2].second + pairs[3].second)/3);
	cout << pairs[5].first << pairs[5].second << endl;

	cout << "(" << (pairs[4].first + pairs[5].first)/2 << "," << 
		 (pairs[4].second + pairs[5].second) << ")" << endl;
}

void gokaku(){
	vector<pair<double,double> > pairs(10);
	pairs[0] = make_pair(10,0);
	pairs[1] = make_pair(4,5);
	pairs[2] = make_pair(12,4);
	pairs[3] = make_pair(16,5);
	pairs[4] = make_pair(14,0);


	pairs[5] = make_pair((pairs[0].first + pairs[1].first + pairs[2].first)/3
						,(pairs[0].second + pairs[1].second + pairs[2].second)/3);
	cout << pairs[5].first << pairs[5].second << endl;
	pairs[6] = make_pair((pairs[0].first + pairs[2].first + pairs[3].first)/3
						,(pairs[0].second + pairs[2].second + pairs[3].second)/3);
	cout << pairs[6].first << pairs[6].second << endl;
	pairs[7] = make_pair((pairs[0].first + pairs[3].first + pairs[4].first)/3
						,(pairs[0].second + pairs[3].second + pairs[4].second)/3);
	cout << pairs[7].first << pairs[7].second << endl;

	
	pairs[8] = make_pair((pairs[5].first + pairs[6].first + pairs[7].first)/3
						,(pairs[5].second + pairs[6].second + pairs[7].second)/3);
	cout << "(" << pairs[8].first << "," << pairs[8].second << ")" << endl;
}

void rokkaku(){
	vector<pair<double,double> > pairs(15);
	pairs[0] = make_pair(10,2);
	pairs[1] = make_pair(4,5);
	pairs[2] = make_pair(9,8);
	pairs[3] = make_pair(12,9);
	pairs[4] = make_pair(14,4);
	pairs[5] = make_pair(12,3);


	pairs[6] = make_pair((pairs[0].first + pairs[1].first + pairs[2].first)/3
						,(pairs[0].second + pairs[1].second + pairs[2].second)/3);
	cout << pairs[6].first << pairs[6].second << endl;
	pairs[7] = make_pair((pairs[0].first + pairs[2].first + pairs[3].first)/3
						,(pairs[0].second + pairs[2].second + pairs[3].second)/3);
	cout << pairs[7].first << pairs[7].second << endl;
	pairs[8] = make_pair((pairs[0].first + pairs[3].first + pairs[4].first)/3
						,(pairs[0].second + pairs[3].second + pairs[4].second)/3);
	cout << pairs[8].first << pairs[8].second << endl;
	pairs[9] = make_pair((pairs[0].first + pairs[4].first + pairs[5].first)/3
						,(pairs[0].second + pairs[4].second + pairs[5].second)/3);
	cout << pairs[9].first << pairs[9].second << endl;



	pairs[10] = make_pair((pairs[6].first + pairs[7].first + pairs[8].first)/3
						,(pairs[6].second + pairs[7].second + pairs[8].second)/3);
	cout << pairs[10].first << pairs[10].second << endl;
	pairs[11] = make_pair((pairs[6].first + pairs[8].first + pairs[9].first)/3
						,(pairs[6].second + pairs[8].second + pairs[9].second)/3);
	cout << pairs[11].first << pairs[11].second << endl;
	
	cout << "(" << (pairs[10].first + pairs[11].first)/2 << "," << 
		 (pairs[10].second + pairs[11].second) << ")" << endl;
}


int main(){
	int hantei;

	cout << "How much have the corner?" << endl;
	cin >> hantei;

	switch(hantei){
		case 3:
			sankaku();
			break;
		case 4:
			sikaku();
			break;
		case 5:
			gokaku();
			break;
		case 6:
			rokkaku();
			break;
	}

	return 0;
}