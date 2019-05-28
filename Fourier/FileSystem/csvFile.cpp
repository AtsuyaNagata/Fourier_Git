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

void csvFile::csvWrite(const char* filename, Array2D<double> data)
{
	ofstream out(filename, ofstream::binary);
	if (out) {
		for (int i = 0; i < data.getHeight(); ++i) {
			for (int j = 0; j < data.getWidth(); ++j) {
				//�f�[�^����������
				out << data(j, i);
				if (j < data.getWidth()) {
					out << ",";
				}
			}
			out << "\n";
		}
	}
	else {
		//CRT_ERROR : �_�C�A���O�܂ŏo���B�ʏ��_CRT_WARN���w��
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
		//CRT_ERROR : �_�C�A���O�܂ŏo���B�ʏ��_CRT_WARN���w��
		_RPT0(_CRT_ERROR, "can't open file.\n");
		return;
	}
}