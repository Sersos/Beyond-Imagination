#ifndef WORLD_H
#define WORLD_H

#include "DirectxManager.h"
#include "Global.h"
#include <vector>
#include "WorldObject.h"

struct Vertex
{
	D3DXVECTOR3 Position;
	D3DXVECTOR3 Normal;
};

namespace World
{
	class World
	{
	public:
		World();

		void initialize(ID3D11Device* device, ID3D11DeviceContext* deviceContext, uint8 width, uint8 depth);
		void update();
		void render(ID3D11DeviceContext* deviceContext);

		uint8 getWidth() { return m_width; }
		uint8 getDepth() { return m_depth; }

	private:
		ID3D11Buffer* m_vertexBuffer;
		ID3D11Buffer* m_indexBuffer;

		std::vector<Vertex> m_vertices;
		std::vector<uint8>  m_indices;

		uint8 m_width;
		uint8 m_depth;

		//World::WorldObject m_worldObject[5];
	};
}

#endif