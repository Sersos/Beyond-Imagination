//lighthelper.fx

struct DirectionalLight
{
	float4 ambient;
	float4 diffuse;
	float4 specular;
	float3 direction;
};

struct PointLight
{
	float4 ambient;
	float4 diffuse;
	float4 specular;
	float3 position;
	float range;
	float3 att;
};

struct SpotLight
{
	float4 ambient;
	float4 diffuse;
	float4 specular;
	float3 position;
	float range;
	float3 direction;
	float spot;
	float3 att;
};

struct Material
{
	float4 ambient;
	float4 diffuse;
	float4 specular;
};

void computeDirectionalLight(Material material, DirectionalLight directionalLight, 
							float3 normal, float3 toEye, out float4 ambient, out float4 diffuse, out float4 specular)
{
	//initialize variables with 0
	ambient = float4(0.0f, 0.0f, 0.0f, 0.0f);
	diffuse = float4(0.0f, 0.0f, 0.0f, 0.0f);
	specular = float4(0.0f, 0.0f, 0.0f, 0.0f);

	//light vector aims opposite the direction rays travel
	float3 lightVector = -directionalLight.direction;

	//ambient
	ambient = material.ambient * directionalLight.ambient;

	float diffuseFactor = dot(lightVector, normal);

	[flatten]
	if (diffuseFactor > 0.0f)
	{
		float3 v = reflect(-lightVector, normal);
		float specFactor = pow(max(dot(v, toEye), 0.0f), material.specular.w);

		diffuse  = diffuseFactor * material.diffuse * directionalLight.diffuse;
		specular = specFactor * material.specular * directionalLight.specular;
	}
}

void computePointLight(Material material, PointLight pointLight, float3 position,
					  float3 normal, float3 toEye, out float4 ambient, out float4 diffuse, out float4 specular)
{
	//initialize variables with 0
	ambient = float4(0.0f, 0.0f, 0.0f, 0.0f);
	diffuse = float4(0.0f, 0.0f, 0.0f, 0.0f);
	specular = float4(0.0f, 0.0f, 0.0f, 0.0f);

	//check range position and light position
	float3 lightVector = pointLight.position - position;
	float distance = length(lightVector);

	if (distance > pointLight.range) //position is out of range
		return; 

	//normalize the light vector
	lightVector /= distance;

	//ambient
	ambient = material.ambient * pointLight.ambient;

	float diffuseFactor = dot(lightVector, normal);

	[flatten]
	if (diffuseFactor > 0.0f)
	{
		float3 v = reflect(-lightVector, normal);
		float specFactor = pow( max( dot(v, toEye), 0.0f), material.specular.w);

		diffuse  = diffuseFactor * material.diffuse * pointLight.diffuse;
		specular = specFactor * material.specular * pointLight.specular;
	}

	//attenuation
	float att = 1.0f / dot(pointLight.att, float3(1.0f, distance, distance * distance));

	diffuse  *= att;
	specular *= att;
}

void computeSpotLight(Material material, SpotLight spotLight, float3 position,
					float3 normal, float3 toEye, out float4 ambient, out float4 diffuse, out float4 specular)
{
	//initialize variables with 0
	ambient = float4(0.0f, 0.0f, 0.0f, 0.0f);
	diffuse = float4(0.0f, 0.0f, 0.0f, 0.0f);
	specular = float4(0.0f, 0.0f, 0.0f, 0.0f);

	//check range position and light position
	float3 lightVector = spotLight.position - position;
	float distance = length(lightVector);

	if (distance > spotLight.range)
		return;

	lightVector /= distance;

	ambient = material.ambient * spotLight.ambient;

	float diffuseFactor = dot(lightVector, normal);

	[flatten]
	if (diffuseFactor > 0.0f)
	{
		float3 v = reflect(-lightVector, normal);
		float specFactor = pow(max(dot(v, toEye), 0.0f), material.specular.w);

		diffuse = diffuseFactor * material.diffuse * spotLight.diffuse;
		specular = specFactor * material.specular * spotLight.specular;
	}

	float spotFactor = pow( max( dot(-lightVector, spotLight.direction), 0.0f), spotLight.spot);

	float att = spotFactor / dot(spotLight.att, float3(1.0f, distance, distance * distance));

	ambient *= spotFactor;
	diffuse  *= att;
	specular *= att;
}