#ifndef FILEOUTPUTMANAGER_H
#define FILEOUTPUTMANAGER_H

#include "Global.h"
#include <fstream>

class FileOutputManager
{
public:
	FileOutputManager();

	void createFile(const char* filename);

	/* for int value*/	
	void save(const char* objectInfo, int value, bool addNextLine);

	/* for float value*/	
	void save(const char* objectInfo, float value, bool addNextLine);

	void close();

private:
	std::ofstream m_file;
	bool m_isOpen;
};

#endif