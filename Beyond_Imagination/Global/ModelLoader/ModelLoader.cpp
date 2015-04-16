#include "ModelLoader.h"
#include "FileOutputManager.h"

ModelLoader::ModelLoader()
{
	m_vertexCount = 0;
	m_indexCount = 0;
}

void ModelLoader::loadObject(const char* filename)
{
	//for control input values
	FileOutputManager* out = new FileOutputManager();
	out->createFile("Logs/log.txt"); //this file will be create 
	std::ifstream in; //file to load in	

	in.open(filename);	

	//variables
	char input, input2 /* for / */;	

	m_vertices.resize(100);
	//m_indices.resize(100);

	//is file available?
	if (!in)
	{
		MessageBox(0, L"Cant load file", 0, MB_OK);
	}		

	in.get(input);

	/*------------------------ new --------------------------*/
	char buffer[256]; //only as buffer
	std::vector<std::string*> line; //vector filled with each line
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
			modelData.Normal = D3DXVECTOR3(0, 0, 0);
			m_vertices.push_back(modelData);

			out->save("Position x: ", x, false);
			out->save("y: ", y, false);
			out->save("z: ", z, true);

		}
		else if (line[i]->c_str()[0] /* first letter*/ == 'v' && line[i]->c_str()[1] == 'n')
		{
			float x, y, z;
			sscanf(line[i]->c_str(), "vn %f %f %f", &x, &y, &z); //load in x, y and z value
			
			//put it in vector
			m_vertices.at(normalCounter).Normal = D3DXVECTOR3(x, y, z * -1.0f);
			normalCounter++;

			out->save("normal x: ", x, false);
			out->save("y: ", y, false);
			out->save("z: ", z, true);
		}
		else if (line[i]->c_str()[0] /* first letter*/ == 'f')
		{
			int a, b, c; //3 for triangle
			int skip;
			sscanf(line[i]->c_str(), "f %d/%d/%d %d/%d/%d %d/%d/%d", &a, &skip/* texture point */, &skip/* normal point */,
																	 &b, &skip/* texture point */, &skip/* normal point */,
																	 &c, &skip/* texture point */, &skip/* normal point */); //load in x, y and z value

			//put it in vector
			Face face;
			face.a = a;
			face.b = b;
			face.c = c;

			m_indices.push_back(face);

			out->save("i1: ", a, false);
			out->save("i2: ", b, false);
			out->save("i3: ", c, true);
		}	
	}

	/* old
	
	while (!in.eof())
	{
		in.get(input);
		
		//for vertex position with beginning 'v'
		if (input == 'v') //first point for vertex position
		{
			in.get(input); //get next letter

			if (input == ' ') //it is a vertex position
			{
				float x, y, z;
				in >> x >> y >> z;
				
				ModelData modelData;
				modelData.Position = D3DXVECTOR3((float)x, (float)y, (float)z * -1.0f);
				modelData.Normal = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
				
				m_vertices.push_back(modelData);

				out->save("Position x: ", x, false);
				out->save("y: ", y, false);
				out->save("z: ", z, true);				
			}

			if (input == 'n') //it is a normal vector
			{
				float x, y, z;
				in >> x >> y >> z;

				m_vertices.at(normalCounter).Normal = D3DXVECTOR3(x, y, z * -1.0f);
				normalCounter++;

				out->save("normal x: ", x, false);
				out->save("y: ", y, false);
				out->save("z: ", z, true);				
			}
		}

		if (input == 'f') //for faces
		{
			
			
			for (int i = 0; i < string->size; i++) //go through all letters
			{
				int a, b, c, d, e, f;
				sscanf(string[i].c_str(), "f %d/%d/%d %d/%d/%d %d/%d/%d", &a, &b, &c, &d, &e, &f);
			}

			//in.get(input);

			if (input == ' ') //next step to indices
			{
				long indexArray[3];

				in >> indexArray[0] >> input >> input >> input >> input
					>> indexArray[1] >> input >> input >> input >> input
					>> indexArray[2] >> input >> input >> input >> input;

				for (int i = 0; i < 3; i++)
				{
					m_indices.push_back(indexArray[i]);
				}

				for (int i = 0; i < 3; i++)
				{
					out->save("i: ", indexArray[i], true);					
				}				
			}
		}

		while (input != '\n')
		{
			in.get(input);			
		}			
	}*/

	out->save("vertexCount: ", (int) m_vertices.size(), true);
	out->save("indexCount: ", (int) m_indices.size() * 3, true);

	m_indexCount = (int) m_indices.size() * 3;
	m_vertexCount = (int) m_vertices.size();

	in.close();
	out->close();
	
	/*
	
	fin >> ignore >> m_vertexCount;
	out->save("vertexCount: ", m_vertexCount, true);

	fin >> ignore >> triangleCount;
	out->save("triangleCount: ", triangleCount, true);

	fin >> ignore >> ignore >> ignore >> ignore;

	m_vertices.resize(m_vertexCount);
	m_indexCount = 3 * triangleCount;
	out->save("indexCount: ", m_indexCount, true);

	m_indices.resize(m_indexCount);

	for (UINT i = 0; i < m_vertexCount; ++i)
	{
		fin >> m_vertices[i].Position.x >> m_vertices[i].Position.y >> m_vertices[i].Position.z
			>> m_vertices[i].Normal.x >> m_vertices[i].Normal.y >> m_vertices[i].Normal.z;

		out->save("x: ", m_vertices[i].Position.x, false);
		out->save("y: ", m_vertices[i].Position.y, false);
		out->save("z: ", m_vertices[i].Position.z, true);
	}

	fin >> ignore;
	fin >> ignore;
	fin >> ignore;

	for (int i = 0; i < triangleCount; ++i)
	{
		fin >> m_indices[i * 3 + 0] >> m_indices[i * 3 + 1] >> m_indices[i * 3 + 2];
	}

		
	fin.close();*/
	

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

