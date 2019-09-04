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

bool static isNumber(char c) {
	return (c >= '0' && c <= '9');
}
double CharacterToNumber(const char* name) {
	double sum = 0;
	//インデックスを指定するための変数
	int i, count;

	//ステージ1 : 小数点以下を考えずに処理
	for (count = 0; isNumber(name[count]); ++count);

	for (i = 0; i < count; ++i) {
		sum *= 10;
		sum += name[i] - '0';
	}

	//もし、区切られ文字が「'.'」の時、少数以下の可能性あり
	if (name[count] == '.') {
		//ステージ2 : 少数点の値の獲得
		i = count + 1;
		for (count = i; isNumber(name[count]); ++count);

		//係数kを用いて少数を表現
		double k = 0.1;
		for (; i < count; ++i) {
			sum += (name[i] - '0') * k;
			k *= 0.1;
		}
	}
	return sum;
}

csvFile::csvFile(const char* filename) : File(filename),
mWidth(0),
mHeight(0)
{
	//一つはデータがある事を保証する
	if (mSize == 0) {
		return;
	}
	//widthの開始地点は1だが、'\n'は、ファイルの最後にも存在するので0から開始する
	int width = 1, height = 0;
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
			if (width > maxWidth) {
				maxWidth = width;
			}
			width = 1;
		}
	}

	//高さと低さのデータを格納
	mWidth = maxWidth;
	mHeight = height;

	//効率は悪いが人間的に分かり易い
	mDouble.setSize(mWidth, mHeight);
	for (int i = 0; i < mHeight; ++i) {
		for (int j = 0; j < mWidth; ++j) {
			mDouble(j, i) = 0;
		}
	}

	width = 0, height = 0;
	int oldIndexBuff = 0;
	//mDouble(0, 0) = CharacterToNumber(&mData[0]);
	for (int i = 0; i < mSize; ++i) {
		//ダブルクォーテーションが来たら、次のダブルクォーテーションまで無効
		if (mData[i] == '\"') {
			while (mData[i] != '\"') {
				++i;
			}
		}
		if (mData[i] == ',') {
			mDouble(width, height) = CharacterToNumber(&mData[oldIndexBuff]);
			oldIndexBuff = i + 1;
			++width;
		}
		else if (mData[i] == '\n') {
			mDouble(width, height) = CharacterToNumber(&mData[oldIndexBuff]);
			oldIndexBuff = i + 1;
			++height;
			if (width > maxWidth) {
				maxWidth = width;
			}
			width = 0;
		}
	}

	//char text[TEXT_MAX + 1]; int j = TEXT_MAX;	//一時的に文字をためておくのに必要な変数
	//string str;								//横着して文字列→doubleをstringに任せようという魂胆
	/*int x = 0, y = 0;							//エクセルのデータを2次元で扱いたいので、位置を決めるのに必要な変数を用意
	for (int i = 0; i < mSize; ++i) {
		if (j == TEXT_MAX) {
			for (int k = 0; k <= TEXT_MAX; ++k) {
				//全て「a」の文字で埋める
				text[k] = 'a';
			}
			text[TEXT_MAX] = '\0';
		}

		if (mData[i] == ',') {
			//テキストをdoubleに変換
			swapText(text);
			mDouble(x, y) = CharacterToNumber(text);
			x++;
			j = TEXT_MAX;
		}
		else if (mData[i] == '\n') {
			//テキストをdoubleに変換
			swapText(text);
			mDouble(x, y) = CharacterToNumber(text);
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
	}*/
}

csvFile::~csvFile()
{

}

template<typename T>
void csvFile::csvWrite(const char* filename, Array2D<T>& data)
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

void csvFile::csvWrite(const char* filename, Array2D<double>& data)
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

void csvFile::csvWrite(const char* filename, const double* data, int size)
{
	ofstream out(filename, ofstream::binary);
	if (out) {
		for (int i = 0; i < size; ++i) {
			out << data[i] << "\n";
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