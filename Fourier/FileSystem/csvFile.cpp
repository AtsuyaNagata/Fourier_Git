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
	//�C���f�b�N�X���w�肷�邽�߂̕ϐ�
	int i, count;

	//�X�e�[�W1 : �����_�ȉ����l�����ɏ���
	for (count = 0; isNumber(name[count]); ++count);

	for (i = 0; i < count; ++i) {
		sum *= 10;
		sum += name[i] - '0';
	}

	//�����A��؂�ꕶ�����u'.'�v�̎��A�����ȉ��̉\������
	if (name[count] == '.') {
		//�X�e�[�W2 : �����_�̒l�̊l��
		i = count + 1;
		for (count = i; isNumber(name[count]); ++count);

		//�W��k��p���ď�����\��
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
	//��̓f�[�^�����鎖��ۏ؂���
	if (mSize == 0) {
		return;
	}
	//width�̊J�n�n�_��1�����A'\n'�́A�t�@�C���̍Ō�ɂ����݂���̂�0����J�n����
	int width = 1, height = 0;
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
			if (width > maxWidth) {
				maxWidth = width;
			}
			width = 1;
		}
	}

	//�����ƒႳ�̃f�[�^���i�[
	mWidth = maxWidth;
	mHeight = height;

	//�����͈������l�ԓI�ɕ�����Ղ�
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
		//�_�u���N�H�[�e�[�V������������A���̃_�u���N�H�[�e�[�V�����܂Ŗ���
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

	//char text[TEXT_MAX + 1]; int j = TEXT_MAX;	//�ꎞ�I�ɕ��������߂Ă����̂ɕK�v�ȕϐ�
	//string str;								//�������ĕ�����double��string�ɔC���悤�Ƃ������_
	/*int x = 0, y = 0;							//�G�N�Z���̃f�[�^��2�����ň��������̂ŁA�ʒu�����߂�̂ɕK�v�ȕϐ���p��
	for (int i = 0; i < mSize; ++i) {
		if (j == TEXT_MAX) {
			for (int k = 0; k <= TEXT_MAX; ++k) {
				//�S�āua�v�̕����Ŗ��߂�
				text[k] = 'a';
			}
			text[TEXT_MAX] = '\0';
		}

		if (mData[i] == ',') {
			//�e�L�X�g��double�ɕϊ�
			swapText(text);
			mDouble(x, y) = CharacterToNumber(text);
			x++;
			j = TEXT_MAX;
		}
		else if (mData[i] == '\n') {
			//�e�L�X�g��double�ɕϊ�
			swapText(text);
			mDouble(x, y) = CharacterToNumber(text);
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

void csvFile::csvWrite(const char* filename, Array2D<double>& data)
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
		//CRT_ERROR : �_�C�A���O�܂ŏo���B�ʏ��_CRT_WARN���w��
		_RPT0(_CRT_ERROR, "can't open file.\n");
		return;
	}
}