#include "ModelLoader.h"
#include <fstream>

ModelLoader::ModelLoader()
{

}

void ModelLoader::loadObject(const char* filename)
{
	////create fstream with filename
	//std::wifstream file(filename);
	//wchar_t currentChar;
	//std::string ignore;

	//int normalcounter = 0;

	std::ifstream fin("skull.txt");

	if (!fin)
		MessageBox(0, L"Cant load file", 0, MB_OK);
	
	std::string ignore;

	fin >> ignore >> m_vertexCount;
	fin >> ignore >> m_indexCount;
	fin >> ignore >> ignore >> ignore >> ignore;

	m_vertices.resize(m_vertexCount);
	for (UINT i = 0; i < m_vertexCount; i++)
	{
		fin >> m_vertices[i].Position.x >> m_vertices[i].Position.y >> m_vertices[i].Position.z >> m_vertices[i].Normal.x >> m_vertices[i].Normal.y >> m_vertices[i].Normal.z;		
	}

	fin >> ignore;
	fin >> ignore;
	fin >> ignore;

	m_indices.resize(m_indexCount);
	for (UINT i = 0; i < m_indexCount; i++)
	{
		int index[3];
		fin >> index[0] >> index[1] >> index[2];

		for (int x = 0; x < sizeof(index); x++)
			m_indices.push_back(index[x]);
	}

	fin.close();


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