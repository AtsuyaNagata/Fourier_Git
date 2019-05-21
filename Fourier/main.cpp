#include <iostream>
#include <string>
#include "FileSystem/csvFile.h"
using namespace std;

int main()
{
	csvFile f("SampleCsv.csv");

	if (!f.data()) {
		return 1;
	}

	for (int i = 0; i < f.getHeight(); ++i) {
		for (int j = 0; j < f.getWidth(); ++j) {
			cout << "(" << j << "," <<  i << ")" << f.dData()(j, i) << "   ";
		}
		cout << endl;
	}

	csvFile::csvWrite("outPut.csv", f.dData());

	return 0;
}
