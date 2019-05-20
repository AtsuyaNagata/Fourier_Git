#include "csvFile.h"
#include <string>
using namespace std;

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
			if (width > maxWidth) {
				maxWidth = width;
			}
		}
	}

	//高さと低さのデータを格納
	mWidth = maxWidth;
	mHeight = height;

	//効率は悪いが人間的に分かり易い
	mDouble.setSize(mWidth, mHeight);

	char text[11]; int j = 0;	//一時的に文字をためておくのに必要な変数
	string str;					//横着して文字列→doubleをstringに任せようという魂胆
	int x = 0, y = 0;			//エクセルのデータを2次元で扱いたいので、位置を決めるのに必要な変数を用意
	for (int i = 0; i < mSize; ++i) {
		if (j == 0) {
			for (int k = 0; k < 10; ++k) {
				//全て「0」の文字で埋める
				text[k] = '0';
			}
			//最後尾を明示
			text[10] = '\0';
		}

		if (mData[i] == ',') {
			str = text;
			//テキストをdoubleに変換
			mDouble(x, y) = std::stod(str);
			x++;
			j = 0;
		}
		else if (mData[i] == '\n') {
			str = text;
			//テキストをdoubleに変換
			mDouble(x, y) = std::stod(str);
			//\r\n的な処理
			y++;
			x = 0;
			j = 0;
		}
		else {
			text[j] = mData[i];
			if (j < 10) {
				j++;
			}
		}
	}
}


csvFile::~csvFile()
{

}
