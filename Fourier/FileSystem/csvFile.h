#ifndef _FILE_SYSTEM_CSV_H_
#define _FILE_SYSTEM_CSV_H_

#include "File.h"
#include "Array2D.h"

class csvFile : public File
{
public:
	//�R���X�g���N�^
	csvFile(const char* filename);
	~csvFile();

	Array2D<double> dData() {
		return mDouble;
	}

	int getWidth() { return mWidth; }
	int getHeight() { return mHeight; }

	template<typename T>
	static void csvWrite(const char* filename, Array2D<T>& data);
	static void csvWrite(const char* filename, Array2D<double>& data);
	static void csvWrite(const char* filename, const double* data, int size);

private:
	int mWidth, mHeight;		//�ő�̍����Ɖ����̕ϐ�
	Array2D<double> mDouble;
};

#endif
