#include "ModelLoader.h"
#include "FileOutputManager.h"

ModelLoader::ModelLoader()
{
	m_vertexCount = 0;
	m_indexCount = 0;
}

void ModelLoader::loadObject(const char* filename)
{
	//create fstream with filename
	//std::wifstream file(filename);
	//wchar_t currentChar;
	//std::string ignore;
	
	//for control input values
	FileOutputManager* file = new FileOutputManager();
	file->createFile("Logs/log.txt"); //this file will be create 
	std::ifstream fin(filename); //file to load in	

	if (!fin)
		MessageBox(0, L"Cant load file", 0, MB_OK);
	
	std::string ignore;
	int triangleCount = 0;
	
	fin >> ignore >> m_vertexCount;
	file->save("vertexCount: ", m_vertexCount, true);

	fin >> ignore >> triangleCount;
	file->save("triangleCount: ", triangleCount, true);

	fin >> ignore >> ignore >> ignore >> ignore;

	m_vertices.resize(m_vertexCount);
	m_indexCount = 3 * triangleCount;
	file->save("indexCount: ", m_indexCount, true);

	m_indices.resize(m_indexCount);

	for (UINT i = 0; i < m_vertexCount; ++i)
	{
		fin >> m_vertices[i].Position.x >> m_vertices[i].Position.y >> m_vertices[i].Position.z
			>> m_vertices[i].Normal.x >> m_vertices[i].Normal.y >> m_vertices[i].Normal.z;

		file->save("x: ", m_vertices[i].Position.x, false);
		file->save("y: ", m_vertices[i].Position.y, false);
		file->save("z: ", m_vertices[i].Position.z, true);
	}

	fin >> ignore;
	fin >> ignore;
	fin >> ignore;

	for (int i = 0; i < triangleCount; ++i)
	{
		fin >> m_indices[i * 3 + 0] >> m_indices[i * 3 + 1] >> m_indices[i * 3 + 2];
	}

		
	fin.close();
	file->close();
	

	//while (file)
	//{
		
				
	//	currentChar = file.get();

	//	switch (currentChar)
	//	{
	//		case '#': //for blender header
	//			while (currentChar != '\n')
	//				currentChar = file.get();
	//			break;

	//		case 'v': //vertex position
	//			currentChar = file.get();

	//			if (currentChar == ' ')
	//			{
	//				//load vertex positions
	//				float x, y, z;
	//				file >> x >> y >> z;

	//				//check later which handed systems is used

	//				ModelData modelData;
	//				modelData.Position = D3DXVECTOR3(x, y, z);
	//				modelData.Normal = D3DXVECTOR3(0, 0, 0);

	//				m_vertices.push_back(modelData); 
	//			}

	//		case 'f': //indices
	//			currentChar = file.get();

	//			if (currentChar == ' ')
	//			{
	//				int index[8];
	//				wchar_t ignore;
	//				file >> index[0] >> ignore >> index[1] >> ignore >> index[2] //first face
	//					 >> ignore /* whitespace */ 
	//					 >> index[3] >> ignore >> index[4] >> ignore >> index[5] //second face
	//					 >> ignore /* whitespace */
	//					 >> index[6] >> ignore >> index[7] >> ignore >> index[8]; //third face

	//				for (int i = 0; i < sizeof(index); i++)
	//					m_indices.push_back(index[i]);
	//			}

	//		case 'vn': //normals
	//			currentChar = file.get();

	//			if (currentChar == ' ')
	//			{
	//				float x, y, z;
	//				file >> x >> y >> z;

	//				m_vertices.at(normalcounter).Normal = D3DXVECTOR3(x, y, z);
	//				normalcounter++;
	//			}
	//		default:
	//			break;
	//	}
	//}	
	
}

