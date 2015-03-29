#ifndef OBJECT_H
#define OBJECT_H

#include "DirectxManager.h"

struct Vertex
{
	D3DXVECTOR3 Position;
	D3DXVECTOR4 Color;	
};

class Object
{
public:
	Object();

	void initialize(ID3D11Device* device,ID3D11DeviceContext* deviceContext);
	void update();
	void render(ID3D11DeviceContext* deviceContext, ShaderManager* shaderManager, D3DXMATRIX view, D3DXMATRIX projection);	

	//rotate object on every axis: x, y and z
	void rotate(D3DXVECTOR3& rotation) { };

	//scale object on every axis: x, y and z
	//void scale(D3DXVECTOR3& scale) { };

	//scale object with one factor for all axis
	//void scale(float factor) { };

	//return world matrix
	D3DXMATRIX getWorldMatrix();

private:
	//buffers for vertices and indices
	ID3D11Buffer* vertexBuffer;
	ID3D11Buffer* indexBuffer;	

	//world matrix, manipulate in "update-funtion"
	D3DXMATRIX world;

	float scale;
	
};

#endif