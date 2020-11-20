#include <iostream>
#include <fstream>
#include <string>

using namespace std;
int main(int argc, char** argv) {
	if(argc > 1) {
		int i = 0;
		while(++i < argc) {
			fstream file(argv[i]); 
			string line;
			while(std::getline(file, line)) {
				cout << line << '\n';
			}
			file.close();
		}

	}

	

	return 0;
}
