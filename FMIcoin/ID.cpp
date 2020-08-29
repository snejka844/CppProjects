#include <iostream>
#include <stdlib.h>
#include <time.h>
#include "ID.h"

using std::cin;
using std::cout;
using std::endl;
using std::ofstream;
using std::ifstream;
using std::cerr;
using std::ios;

static unsigned int currentFreeID;
static const char* IDFileName = "ID.dat";

bool doFileExist() {
	ifstream file(IDFileName, ios::binary);
	if (file.good()) {
		file.close();
		return true;
	}
	return false;
}

void initilizeID() {
	if (!doFileExist()) {
		currentFreeID = 1;
	}
	else {
		ifstream file(IDFileName, ios::binary);
		if (!file.good()) {
			cerr << IDFileName << " file read stream failed!" << endl;
			return;
		}
		file.read((char*)&currentFreeID, sizeof(currentFreeID));
		if (file.gcount() != sizeof(currentFreeID)) {
			cerr << "Error occurred while reading file: "
				<< IDFileName << "\n";
			currentFreeID = 0;
		}
		file.close();
	}
}

void saveLastID() {
	ofstream file(IDFileName, ios::binary | ios::trunc);
	if (!file.good()) {
		cerr << IDFileName << " file write stream failed!!!" << endl;
		return;
	}
	//std::cout << currentFreeID << endl;
	file.write((char*)&currentFreeID, sizeof(currentFreeID));
	file.close();
}

unsigned int getAndIncrementID() {
	/*srand(time(NULL));
	for (unsigned int i = 0; i < 10; ++i) {
		return rand() % (1 << 31);
	}
	*/
	return currentFreeID++;
}