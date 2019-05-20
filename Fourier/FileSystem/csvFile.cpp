#include "csvFile.h"
#include <string>
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
					d += text[i] - '0';
				}
			}
			else if (flag == true) {
				if (text[i] <= '9' && text[i] >= '0') {
					md *= 10;
					count++;
					md += text[i] - '0';
				}
				else {
					return d + md * pow(0.1, count);
				}
			}
		}
	}
}

csvFile::csvFile(const char *filename) : File(filename),
	mWidth(0),
	mHeight(0)
{
	int width = 0, height = 0;
	int maxWidth = 0;
	for (int i = 0; i < mSize; ++i) {
		//�_�u���N�H�[�e�[�V������������A���̃_�u���N�H�[�e�[�V�����܂Ŗ���
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

	//�����ƒႳ�̃f�[�^���i�[
	mWidth = maxWidth;
	mHeight = height;

	//�����͈������l�ԓI�ɕ�����Ղ�
	mDouble.setSize(mWidth, mHeight);

	char text[TEXT_MAX + 1]; int j = TEXT_MAX;	//�ꎞ�I�ɕ��������߂Ă����̂ɕK�v�ȕϐ�
	//string str;									//�������ĕ�����double��string�ɔC���悤�Ƃ������_
	int x = 0, y = 0;							//�G�N�Z���̃f�[�^��2�����ň��������̂ŁA�ʒu�����߂�̂ɕK�v�ȕϐ���p��
	for (int i = 0; i < mSize; ++i) {
		if (j == TEXT_MAX) {
			for (int k = 0; k <= TEXT_MAX; ++k) {
				//�S�āu0�v�̕����Ŗ��߂�
				text[k] = 'a';
			}
			text[TEXT_MAX] = '0';
		}

		if (mData[i] == ',') {
			//�e�L�X�g��double�ɕϊ�
			swapText(text);
			mDouble(x, y) = textToDouble(text);
			x++;
			j = TEXT_MAX;
		}
		else if (mData[i] == '\n') {
			//�e�L�X�g��double�ɕϊ�
			swapText(text);
			mDouble(x, y) = textToDouble(text);
			//\r\n�I�ȏ���
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


