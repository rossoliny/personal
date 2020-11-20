#include <iostream>
#include <cstring>

using namespace std;
int main(int argc, char** argv) {
	if(argc < 2) {
		cout << "no key provided\n";
		exit(1);
	}
	if(argc > 2 ) {
		cout << "too much keys provided\n";
		exit(1);
	}
	
	char input[256];
	char output[256];
	int key_len = strlen(argv[1]);

	while(!feof(stdin)) {

		int i = 0;
		cout << "enter text to encode(max len 256):\t";
		cin.clear();
		cin.getline(input, 256);
		int len = strlen(input);
		

		if(len == 0) {
			cout << "no text provided\n";
			continue;
		}

		for(int j = 0; j < len; j++) {
			output[j] = (input[j] ^ argv[1][i]);
			//cout << char(c) ^ argv[1][i];
			i++;
			i = i % key_len;
		}
		output[len] = '\0';
		cout << "here is your encoded result: \t\t\"" << output << '\"' << endl;
		
		for(int j = 0; j < len; j++) {
			output[j] = (output[j] ^ argv[1][i]);
			//cout << char(c) ^ argv[1][i];
			i++;
			i = i % key_len;
		}
		
		cout << "and decode encoded result: \t\t\"" << output << '\"' << endl;
		cout << endl;
	}


	return 0;
}
