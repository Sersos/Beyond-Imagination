#include "Visual.h"
/*
#define SAFE_DELETE(p){if(p) delete p;}; //Could be wrong !!!!!!!!!!!!!!!!

#define SAFE_DELETE_ARRAY(p) {if(p){delete[] (p); (p)=NULL;}}

Visual::Visual(ID3D11Device* device) : Renderable(device)
{
	m_numMaterials = 0;
	m_Materials = NULL;

}


Visual::~Visual()
{
	for (DWORD matNo = 0; matNo < m_numMaterials; ++matNo)
	{
		SAFE_DELETE(m_Materials[matNo]);
	}
	SAFE_DELETE_ARRAY(m_Materials);
}

void Visual::Create()
{
	CreateMesh();
	CreateMaterials();
	CreateEffectVars();
	CreateMesh();
	CreateVertexLayout();
}

void Visual::CreateMaterials()
{
	for (DWORD matNo = 0 ; matNo < m_numMaterials; ++matNo)
	{
		//m_Materials[matNo]->Create();
	}
}
void Visual::Destroy()
{
	DestroyMaterials();
	DestroyEffectVars();
	DestroyMesh();
	m_VertexLayout->Release();

}
void Visual::DestroyMaterials()
{
	for (DWORD matNo = 0; matNo < m_numMaterials; ++matNo)
	{
		//m_Materials[matNo]->Destroy();
	}
	}*/