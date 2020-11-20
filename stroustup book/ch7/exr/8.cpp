#include <iostream>


#define N 4
using namespace std;

void swap(int* a, int* b) {
	*a = *a ^ *b;
	*b = *a ^ *b;
	*a = *a ^ *b;
}



void transpose(int m[][N]) {
	for(int i = 0; i < N; i++) {
		for(int j = i+1; j < N; j++) {
			//cout << "swap " << m[i][j] << ", " << m[j][i] << endl;
			// char cha; cin >> cha;
			swap(m[i][j], m[j][i]);
		}
	}
	
}


int main(int argc, char** argv) {
	
	int m[N][N];

	cout << "original\n";
	for(int i = 0; i < 4; i++) {
		for(int j = 0; j < 4; j++) {
			m[i][j] = rand() % 50;
			cout << m[i][j] << '\t';
		}
		cout << endl;
	}
	cout << endl;

	transpose(m);

	cout << "transposed: \n";	
	for(int i = 0; i < 4; i++) {
		for(int j = 0; j < 4; j++) {
			cout << m[i][j]<< '\t';
		}
		cout << endl;
	}
	cout << endl;



	return 0;
}
