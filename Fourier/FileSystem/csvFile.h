#ifndef _FILE_SYSTEM_CSV_H_
#define _FILE_SYSTEM_CSV_H_

#include "FileSystem/File.h"
#include "Array2D.h"

class csvFile : public File
{
public:
	//コンストラクタ
	csvFile(const char *filename);
	~csvFile();

	Array2D<double> dData() {
		return mDouble;
	}

	int getWidth() { return mWidth; }
	int getHeight() { return mHeight; }

private:
	int mWidth, mHeight;		//最大の高さと横幅の変数
	Array2D<double> mDouble;
};

#endif
