#include "ModelLoader.h"
#include "FileOutputManager.h"

ModelLoader::ModelLoader()
{
	m_indexCount = 0;
	m_vertexCount = 0;
	m_faceCount = 0;
}

void ModelLoader::loadObject(const char* filename, bool texture)
{
	//for control input values
	FileOutputManager* out = new FileOutputManager();
	out->createFile("Logs/log.txt"); 
	std::ifstream in; 

	in.open(filename);	

	//is file available?
	if (!in)
	{
		MessageBox(0, L"Cant load file", 0, MB_OK);
	}			

	/*------------------------ new --------------------------*/
	char buffer[256]; //only as buffer
	std::vector<std::string*> line; //vector filled with each line	
	std::vector<D3DXVECTOR3> normals;
	int normalCounter = 0;
	
	while (!in.eof())
	{
		in.getline(buffer, 256);
		line.push_back(new std::string(buffer));
	}

	//go through all lines
	for (int i = 0; i < line.size(); i++)
	{
		if (line[i]->c_str()[0] /* first letter*/ == '#')
		{ 
			continue; //ignore this line
		}
		//vertex Position
		else if (line[i]->c_str()[0] /* first letter*/ == 'v' && line[i]->c_str()[1] == ' ')
		{
			float x, y, z;
			sscanf(line[i]->c_str(), "v %f %f %f", &x, &y, &z); //load in x, y and z value

			//put it in vector
			ModelData modelData;
			modelData.Position = D3DXVECTOR3(x, y, z * -1.0f);
			modelData.Normal = D3DXVECTOR3(0, 1, 0);
			m_vertices.push_back(modelData);

			out->save("Position x: ", x, false);
			out->save("y: ", y, false);
			out->save("z: ", z, true);

		}
		else if (line[i]->c_str()[0] /* first letter*/ == 'v' && line[i]->c_str()[1] == 'n')
		{
			float x, y, z;
			sscanf(line[i]->c_str(), "vn %f %f %f", &x, &y, &z); //load in x, y and z value		
			
			//put normals in "normals"-vector
			normals.push_back(D3DXVECTOR3(x, y, z * -1.0f));			

			//simple output of input data
			out->save("normal x: ", x, false);
			out->save("y: ", y, false);
			out->save("z: ", z, true);
		}
		else if (line[i]->c_str()[0] /* first letter*/ == 'f')
		{
			int a, b, c; //3 for triangle
			int skip;

			if (texture) //texture enabled in blender export
			{
				sscanf(line[i]->c_str(), "f %d/%d/%d %d/%d/%d %d/%d/%d", &a, &skip/* texture point */, &skip/* normal point */,
																		 &b, &skip/* texture point */, &skip/* normal point */,
																		 &c, &skip/* texture point */, &skip/* normal point */); 
			}
			else
			{
				sscanf(line[i]->c_str(), "f %d//%d %d//%d %d//%d", &a, &skip/* normal point */,
																   &b, &skip/* normal point */,
																   &c, &skip/* normal point */);
			}

			
			//put it in vector
			Face face;
			face.a = a;
			face.b = b;
			face.c = c;
			m_indices.push_back(face);

			//simple output of input data
			out->save("i1: ", a, false);
			out->save("i2: ", b, false);
			out->save("i3: ", c, true);
		}	
		//put normal to his position
		

	}		

	m_indexCount = m_indices.size() * 3;
	m_faceCount = m_indices.size();
	m_vertexCount = m_vertices.size();

	out->save("vertexCount: ", m_vertexCount, true);
	out->save("indexCount: ", m_indexCount, true);

	in.close();
	out->close();	
}

int ModelLoader::getIndexCount()
{
	return m_indexCount;
}

int ModelLoader::getFaceCount()
{
	return m_faceCount;
}

int ModelLoader::getVertexCount()
{
	return m_vertexCount;
}

