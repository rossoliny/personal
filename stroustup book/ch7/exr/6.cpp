#include <iostream>
using namespace std;


// not working as i was trying to optimpize copies, failed and gave up

void printarr(int** arr, int l, int r) {
	int i = l;
	cout << "[ ";
	while(i < r) {
		cout << (*arr)[i] << ' ';
		i++;
	}
	cout << "]" << endl;
}

void merge(int** from, int** to, int l, int m, int r) {
//	int left[m - l + 1];
//	int right[r - m];

	// optimize copies
//	for(int i = 0; i < (m - l + 1); ++i) {
//		left[i] = base[l + i];
//	}
//
//	for(int i = 0; i < r - m; ++i) {
//		right[i] = base[m + 1 + i];
//	}
	cout << "merge called\n";
	cout << "left: l = " << l << ", m = " << m << "\n\t";
	printarr(from, l, m+1);
	cout << "right: m = " << m << ", r = " << r << "\n\t";
	printarr(from, m+1, r+1);
	//int* base = *from;
	//int* temp = *to;

	char fa; cin >> fa;

	int i = 0;
	int li = l, ri = m+1;
	while(li <= m && ri <= r) {
		if((*from)[li] < (*from)[ri]) {
			cout << "left[" << li << "] = " << (*from)[li] << ", put into res\n";
			*(to)[i++] = (*from)[li++];
		} else {
			cout << "right[" << ri << "] = " << (*from)[ri] << ", put into res\n";
			*(to)[i++] = (*from)[ri++];
		}
	}

	while(li <= m) {
		cout << "left[" << li << "] = " << (*from)[li] << ", put into res\n";
		(*to)[i++] = (*from)[li++];
	}

	while(ri <= r) {
		cout << "right[" << ri << "] = " << (*from)[ri] << ", put into res\n";
		(*to)[i++] = (*from)[ri++];
	}

	
	cout << "merge done: \n\tres: ";
	printarr(to, l, r+1);
	

	//return *to;
	
	cout << "to before swap: \n\t";
	printarr(to, l, r+1);
	cout << "from before swap: \n\t";
	printarr(from, l, r+1);

	int* temp = *from;
	*from = *to;
	*to = temp;

	cout << "to after SWAP: \n\t";
	printarr(to, l, r+1);
	cout << "from after SWAP: \n\t";
	printarr(from, l, r+1);
	
}

void msort(int** base, int** temp, int l, int r) {
	if(l < r) {
		int m = ((l + r) / 2);
	
		cout << "left before: ";
		printarr(base, l, m+1);
		char c1; cin >> c1;
		msort(base, temp, l, m, l, m); //
		cout << "left after(base): ";
		printarr(base, l, m+1);
		cout << "left after(temp): ";
		printarr(temp, l, m+1);
		cin >> c1;

		cout << "right before: ";
		printarr(temp, m+1, r+1);
		cin >> c1;
		msort(temp, base, m+1, r); //
		cout << "right after: (temp)";
		printarr(temp, m+1, r+1);
		cout << "right after: (base)";
		printarr(base, m+1, r);
		cin >> c1;

		merge(temp, base, l, m, r); //
	}
}


void msort(int* base, int l, int r) {
	int* res = new int[l+r+1];
	for(int i = 0; i < l + r + 1; i++) res[i] = -228;
	int** pres = &res;
	msort(&base, pres, l, r);
	
	int i = 0;
	while(i < l+r+1) {
		base[i] = res[i];
		i++;
	}
}

typedef int (*CFT)(const void*, const void*);
void ssort(void* base, size_t n, size_t sz, CFT cmp) {
//	mergesort(base, n, sz, cmp);
}

int main(int argc, char** argv) {

	int arr[] = {5, 4, 3}; 

	cout << "before sort\n";
	for(int i : arr) {
		cout << i << ' ';
	}
	cout << endl; 

	int sz = (sizeof(arr) / sizeof(arr[0])) - 1;
	cout << "last = " << sz << endl;
	char s;
	cin >> s;
	msort(arr, 0, sz);

	cout << "after sort" << endl;
	for(int i : arr) {
                cout << i << ' ';
        }
        cout << endl;


	return 0;
}

