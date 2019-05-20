#ifndef _FILE_SYSTEM_CSV_H_
#define _FILE_SYSTEM_CSV_H_

#include "FileSystem/File.h"
#include "Array2D.h"

class csvFile : public File
{
public:
	//�R���X�g���N�^
	csvFile(const char *filename);
	~csvFile();

	Array2D<double> dData() {
		return mDouble;
	}

	int getWidth() { return mWidth; }
	int getHeight() { return mHeight; }

private:
	int mWidth, mHeight;		//�ő�̍����Ɖ����̕ϐ�
	Array2D<double> mDouble;
};

#endif
