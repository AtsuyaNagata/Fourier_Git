#include <iostream>
#include <string>
#include "FileSystem/csvFile.h"
using namespace std;

double *charTOdouble(const char *data,int size, int *length) {
	//必ず一つはデータがあると考える
	int count = 1;
	for (int i = 0; data[i] != '\0'; ++i) {
		if (data[i] == ',' || data[i] == '\n') {
			count++;
		}
	}

	*length = count;

	//多用するからスタティック宣言
	static char text[11];

	cout << count << endl;
	double* dData = new double[count];
	string str;
	int j = 0, k = 0;
	for (int i = 0; i < size; ++i) {
		if (data[i] == ',' || data[i] == '\n') {
			text[10] = 0;
			str = text;
			//テキストをdoubleに変換
			dData[k] = std::stod(str);
			k++;
			j = 0;
		}
		else {
			text[j] = data[i];
			if (j < 10) {
				j++;
			}
		}
	}

	return dData;
}

int main()
{
	csvFile f("SampleCsv.csv");

	if (!f.data()) {
		return 1;
	}

	for (int i = 0; i < 10; ++i) {
		cout << "(1, 2)" << f.dData()(1, 2) << endl;
	}

	return 0;
}
