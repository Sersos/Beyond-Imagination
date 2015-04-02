#include "DirectxManager.h"
#include "LightHelper.h"

/*
	Notices:

	Diffuse		= Zerstreuung
	Beispiel:
		D = Lichtfarbe/Lichtintensität * Reflection Material der 3 Farben RGB

	Ambient		= Umgebungsfarbe5
	Specular	= Spiegelung

	Lamberts Cosine Law, maximale Lichtreflexion bei 90° Lichteinstrahlung,

	Lightcolor = l * m (Ambient) + (Diffuse)

*/

struct DirectionalLight //example sun
{
	D3DXVECTOR4 diffuse; //4th component later
	D3DXVECTOR4 ambient;
	D3DXVECTOR4 specular;	
	
	D3DXVECTOR3 direction; //direction 
};

struct PointLight //licht in alle richtungen
{
	D3DXVECTOR4 diffuse; //4th component later
	D3DXVECTOR4 ambient;
	D3DXVECTOR4 specular;

	//attenuation = Schwächung
	D3DXVECTOR3 att;

	//position and range = Vector4	
	D3DXVECTOR3 position;
	float range;
};

struct SpotLight
{
	D3DXVECTOR4 diffuse; //4th component later
	D3DXVECTOR4 ambient;
	D3DXVECTOR4 specular;
	 
	//position and range = Vector4	
	D3DXVECTOR3 position;
	float range;

	D3DXVECTOR3 direction;
	//to control spotlight cone (Kegel)
	float spot;

	//attenuation = Schwächung
	D3DXVECTOR3 att;
	
};

