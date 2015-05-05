#include "Material.h"
#include "Renderable.h"

class Visual : public Renderable
{
/*protected:
	DWORD m_numMaterials;
	Material** m_Materials;
	ID3D11InputLayout* m_VertexLayout;

public:
	Visual(ID3D11Device* device);
	~Visual();

	//void CreateVertexLayout();
	virtual void CreateMesh() = 0;
	virtual void DestroyMesh() = 0;
	virtual void RenderMesh(ID3D11DeviceContext* deviceContext) = 0;
	virtual void Create();
	virtual void Destroy();

	virtual void CreateEffectVars(){};
	virtual void DestroyEffectVars(){};
	virtual void SetupEffectVars(const D3DXMATRIX* viewMatrix,const D3DXMATRIX projMatrix){};
	
	virtual void Render(ID3D11DeviceContext* deviceContext, UINT drawOrder, const D3DXMATRIX* viewMatrix, const D3DXMATRIX* projMatrix);

	virtual void CreateMaterials();
	virtual void DestroyMaterials();


*/
};

