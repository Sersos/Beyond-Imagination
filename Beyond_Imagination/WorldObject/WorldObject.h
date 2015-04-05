#ifndef WORLDOBJECT_H
#define WORLDOBJECT_H

#include "DirectxManager.h"
#include "Object.h"

namespace World
{
	class WorldObject : public Object
	{
	public:
		WorldObject();

		virtual void Initialize(const char* filename, ID3D11Device* device,
			ID3D11DeviceContext* deviceContext,
			D3DXVECTOR3& position,
			D3DXVECTOR3& rotation, D3DXVECTOR3& scale) { };
		
		virtual void Update() { };
		virtual void Render(ID3D11DeviceContext* deviceContext) { };		

	private:



	};
}


#endif





