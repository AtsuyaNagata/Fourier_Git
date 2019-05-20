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
		}
	}

	//�����ƒႳ�̃f�[�^���i�[
	mWidth = maxWidth;
	mHeight = height;

	//�����͈������l�ԓI�ɕ�����Ղ�
	mDouble.setSize(mWidth, mHeight);

	char text[11]; int j = 0;	//�ꎞ�I�ɕ��������߂Ă����̂ɕK�v�ȕϐ�
	string str;					//�������ĕ�����double��string�ɔC���悤�Ƃ������_
	int x = 0, y = 0;			//�G�N�Z���̃f�[�^��2�����ň��������̂ŁA�ʒu�����߂�̂ɕK�v�ȕϐ���p��
	for (int i = 0; i < mSize; ++i) {
		if (j == 0) {
			for (int k = 0; k < 10; ++k) {
				//�S�āu0�v�̕����Ŗ��߂�
				text[k] = '0';
			}
			//�Ō���𖾎�
			text[10] = '\0';
		}

		if (mData[i] == ',') {
			str = text;
			//�e�L�X�g��double�ɕϊ�
			mDouble(x, y) = std::stod(str);
			x++;
			j = 0;
		}
		else if (mData[i] == '\n') {
			str = text;
			//�e�L�X�g��double�ɕϊ�
			mDouble(x, y) = std::stod(str);
			//\r\n�I�ȏ���
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
