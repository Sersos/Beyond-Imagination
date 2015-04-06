#include "Transform.h"
#include "FileOutputManager.h"

Transform::Transform(D3DXVECTOR3& position, D3DXVECTOR3& rotation, D3DXVECTOR3& scale)
{
	D3DXMatrixIdentity(&m_positionMatrix);
	m_position_X = &m_positionMatrix._41;
	m_position_Y = &m_positionMatrix._42;
	m_position_Z = &m_positionMatrix._43;

	out = new FileOutputManager();
	out->createFile("MatrixTest.txt");
	out->save("Position X: ", *m_position_X, true);
	out->save("Matrix X: ", m_positionMatrix._41, true);
	translate(D3DXVECTOR3(1,0,0));
	out->save("Position X: ", *m_position_X, true);
	out->save("Matrix X: ", m_positionMatrix._41, true);
	out->save("Changed Position Value to 50", NULL, true);
	*m_position_X = 50;
	out->save("Position X: ", *m_position_X, true);
	out->save("Matrix X: ", m_positionMatrix._41, true);
}

D3DXMATRIX Transform::translate(D3DXVECTOR3& offset)
{
	return *D3DXMatrixTranslation(&m_positionMatrix, offset.x, offset.y, offset.z);

	out->save("Position X: ", *m_position_X, true);
	out->save("Matrix X: ", m_positionMatrix._41, true);

}

D3DXMATRIX Transform::rotate(D3DXMATRIX* world, D3DXVECTOR3& rotation)
{
	return m_rotationMatrix;

}

D3DXMATRIX Transform::scale(D3DXMATRIX* world, D3DXVECTOR3& scale)
{
	return m_scaleMatix;
}