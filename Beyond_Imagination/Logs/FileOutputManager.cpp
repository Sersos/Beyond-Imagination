#include "FileOutputManager.h"
#include <string>

FileOutputManager::FileOutputManager()
{
	m_isOpen = false;
}

void FileOutputManager::createFile(const char* filename)
{
	m_file.open(filename, std::ofstream::out);
	m_isOpen = m_file.is_open();
}

void FileOutputManager::save(const char* objectInfo, int value, bool addNextLine)
{
	if (m_isOpen)
	{
		if (addNextLine)		
			m_file << objectInfo << std::to_string(value) << "\n";		
		else		
			m_file << objectInfo << std::to_string(value) << " ";			
	}
}

void FileOutputManager::save(const char* objectInfo, float value, bool addNextLine)
{
	if (m_isOpen)
	{
		if (addNextLine)
			m_file << objectInfo << std::to_string(value) << "\n";		
		else		
			m_file << objectInfo << std::to_string(value) << " "; 				
	}
}

void FileOutputManager::close()
{
	m_file.close();
	m_isOpen = false;
}