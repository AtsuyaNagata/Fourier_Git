#include "csvFile.h"
#include "Array2D.h"
#include <string>
#include <fstream>
#define TEXT_MAX 10
using namespace std;

void swapText(char* text) {
	char swapText[TEXT_MAX + 1];
	for (int i = TEXT_MAX; i >= 0; --i) {
		swapText[TEXT_MAX - i] = text[i];
	}

	for (int i = 0; i <= TEXT_MAX; ++i) {
		text[i] = swapText[i];
	}
}

double textToDouble(char* text) {
	bool flag = false;
	double d = 0, md = 0;
	int count = 0;
	for (int i = 0; i < TEXT_MAX; ++i) {
		if (text[i] == '.') {
			flag = true;
		}
		else {
			if (flag == false) {
				if (text[i] < '0' || text[i] > '9') {
					return d;
				}
				else {
					d *= 10;
					d += (double)(text[i] - '0');
				}
			}
			else if (flag == true) {
				if (text[i] <= '9' && text[i] >= '0') {
					md *= 10;
					count++;
					md += (double)(text[i] - '0');
				}
				else {
					return d + md * pow(0.1, count);
				}
			}
		}
	}
	return d + md * pow(0.1, count);
}

csvFile::csvFile(const char *filename) : File(filename),
	mWidth(0),
	mHeight(0)
{
	int width = 0, height = 0;
	int maxWidth = 0;
	for (int i = 0; i < mSize; ++i) {
		//ダブルクォーテーションが来たら、次のダブルクォーテーションまで無効
		if (mData[i] == '\"') {
			while (mData[i] != '\"') {
				++i;
			}
		}
		if (mData[i] == ',') {
			++width;
		}
		else if (mData[i] == '\n') {
			++height;
			if (width + 1 > maxWidth) {
				maxWidth = width + 1;
			}
			width = 0;
		}
	}

	//高さと低さのデータを格納
	mWidth = maxWidth;
	mHeight = height;

	//効率は悪いが人間的に分かり易い
	mDouble.setSize(mWidth, mHeight);

	char text[TEXT_MAX + 1]; int j = TEXT_MAX;	//一時的に文字をためておくのに必要な変数
	//string str;									//横着して文字列→doubleをstringに任せようという魂胆
	int x = 0, y = 0;							//エクセルのデータを2次元で扱いたいので、位置を決めるのに必要な変数を用意
	for (int i = 0; i < mSize; ++i) {
		if (j == TEXT_MAX) {
			for (int k = 0; k <= TEXT_MAX; ++k) {
				//全て「0」の文字で埋める
				text[k] = 'a';
			}
			text[TEXT_MAX] = '0';
		}

		if (mData[i] == ',') {
			//テキストをdoubleに変換
			swapText(text);
			mDouble(x, y) = textToDouble(text);
			x++;
			j = TEXT_MAX;
		}
		else if (mData[i] == '\n') {
			//テキストをdoubleに変換
			swapText(text);
			mDouble(x, y) = textToDouble(text);
			//\r\n的な処理
			y++;
			x = 0;
			j = TEXT_MAX;
		}
		else {
			text[j] = mData[i];
			if (j > 0) {
				j--;
			}
		}
	}
}

csvFile::~csvFile()
{

}

void csvFile::csvWrite(const char* filename, Array2D<double> data)
{
	ofstream out(filename, ofstream::binary);
	if (out) {
		for (int i = 0; i < data.getHeight(); ++i) {
			for (int j = 0; j < data.getWidth(); ++j) {
				//データを書き込む
				out << data(j, i);
				if (j < data.getWidth()) {
					out << ",";
				}
			}
			out << "\n";
		}
	}
	else {
		//CRT_ERROR : ダイアログまで出す。通常は_CRT_WARNを指定
		_RPT0(_CRT_ERROR, "can't open file.\n");
		return;
	}
}

void csvFile::csvWrite(const char* filename, const double *data, int size)
{
	ofstream out(filename, ofstream::binary);
	if (out) {
		for (int i = 0; i < size; ++i) {
			out << data[i] << ",";
		}
		out << "\n";
		out.close();
	}
	else {
		//CRT_ERROR : ダイアログまで出す。通常は_CRT_WARNを指定
		_RPT0(_CRT_ERROR, "can't open file.\n");
		return;
	}
}