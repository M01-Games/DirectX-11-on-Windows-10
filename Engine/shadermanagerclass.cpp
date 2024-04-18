//Filename: shadermanagerclass.cpp

#include "shadermanagerclass.h"


ShaderManagerClass::ShaderManagerClass()
{
	m_TextureShader = 0;
	m_LightShader = 0;
	m_BumpMapShader = 0;
	m_FireShader = 0;
	m_MultiTextureShader = 0;
	m_SpecMapShader = 0;
	m_LightMapShader = 0;
	m_PointLightShader = 0;
	m_GlassShader = 0;
	m_ParticleShader = 0;
	m_ShadowShader = 0;
	m_DepthShader = 0;
}


ShaderManagerClass::ShaderManagerClass(const ShaderManagerClass& other)
{
}


ShaderManagerClass::~ShaderManagerClass()
{
}


bool ShaderManagerClass::Initialize(ID3D11Device* device, HWND hwnd)
{
	bool result;


	//Create the texture shader object.
	m_TextureShader = new TextureShaderClass;
	if (!m_TextureShader)
	{
		return false;
	}

	//Initialize the texture shader object.
	result = m_TextureShader->Initialize(device, hwnd);
	if (!result)
	{
		MessageBox(hwnd, L"Could not initialize the texture shader object.", L"Error", MB_OK);
		return false;
	}

	//Create the light shader object.
	m_LightShader = new LightShaderClass;
	if (!m_LightShader)
	{
		return false;
	}

	//Initialize the light shader object.
	result = m_LightShader->Initialize(device, hwnd);
	if (!result)
	{
		MessageBox(hwnd, L"Could not initialize the light shader object.", L"Error", MB_OK);
		return false;
	}

	//Create the bump map shader object.
	m_BumpMapShader = new BumpMapShaderClass;
	if (!m_BumpMapShader)
	{
		return false;
	}

	//Initialize the bump map shader object.
	result = m_BumpMapShader->Initialize(device, hwnd);
	if (!result)
	{
		MessageBox(hwnd, L"Could not initialize the bump map shader object.", L"Error", MB_OK);
		return false;
	}

	//Create the Fire shader object.
	m_FireShader = new FireShaderClass;
	if (!m_FireShader)
	{
		return false;
	}

	//Initialize the bump map shader object.
	result = m_FireShader->Initialize(device, hwnd);
	if (!result)
	{
		MessageBox(hwnd, L"Could not initialize the Fire shader object.", L"Error", MB_OK);
		return false;
	}

	//Create the multi texture shader object.
	m_MultiTextureShader = new MultiTextureShaderClass;
	if (!m_MultiTextureShader)
	{
		return false;
	}

	//Initialize the multi texture shader object.
	result = m_MultiTextureShader->Initialize(device, hwnd);
	if (!result)
	{
		MessageBox(hwnd, L"Could not initialize the Multi Texture shader object.", L"Error", MB_OK);
		return false;
	}

	//Create the light map shader object.
	m_LightMapShader = new LightMapShaderClass;
	if (!m_LightMapShader)
	{
		return false;
	}

	//Initialize the light map shader object.
	result = m_LightMapShader->Initialize(device, hwnd);
	if (!result)
	{
		MessageBox(hwnd, L"Could not initialize the m_LightMapShader shader object.", L"Error", MB_OK);
		return false;
	}

	//Create the spec map shader object.
	m_SpecMapShader = new SpecMapShaderClass;
	if (!m_SpecMapShader)
	{
		return false;
	}

	//Initialize the spec map shader object.
	result = m_SpecMapShader->Initialize(device, hwnd);
	if (!result)
	{
		MessageBox(hwnd, L"Could not initialize the spec map shader object.", L"Error", MB_OK);
		return false;
	}

	//Create the point light shader object.
	m_PointLightShader = new PointLightShaderClass;
	if (!m_PointLightShader)
	{
		return false;
	}

	//Initialize the point light shader object.
	result = m_PointLightShader->Initialize(device, hwnd);
	if (!result)
	{
		MessageBox(hwnd, L"Could not initialize the point light shader object.", L"Error", MB_OK);
		return false;
	}

	//Create the glass shader object.
	m_GlassShader = new GlassShaderClass;
	if (!m_GlassShader)
	{
		return false;
	}

	//Initialize the glass shader object.
	result = m_GlassShader->Initialize(device, hwnd);
	if (!result)
	{
		MessageBox(hwnd, L"Could not initialize the glass shader object.", L"Error", MB_OK);
		return false;
	}

	//Create the particle shader object.
	m_ParticleShader = new ParticleShaderClass;
	if (!m_ParticleShader)
	{
		return false;
	}

	//Initialize the particle shader object.
	result = m_ParticleShader->Initialize(device, hwnd);
	if (!result)
	{
		MessageBox(hwnd, L"Could not initialize the particle shader object.", L"Error", MB_OK);
		return false;
	}

	//Create the shadow shader object.
	m_ShadowShader = new ShadowShaderClass;
	if (!m_ShadowShader)
	{
		return false;
	}

	//Initialize the particle shader object.
	result = m_ShadowShader->Initialize(device, hwnd);
	if (!result)
	{
		MessageBox(hwnd, L"Could not initialize the shadow shader object.", L"Error", MB_OK);
		return false;
	}

	//Create the depth shader object.
	m_DepthShader = new DepthShaderClass;
	if (!m_DepthShader)
	{
		return false;
	}

	//Initialize the particle shader object.
	result = m_DepthShader->Initialize(device, hwnd);
	if (!result)
	{
		MessageBox(hwnd, L"Could not initialize the depth shader object.", L"Error", MB_OK);
		return false;
	}

	return true;
}


void ShaderManagerClass::Shutdown()
{
	//Release the depth shader object
	if (m_DepthShader)
	{
		m_DepthShader->Shutdown();
		delete m_DepthShader;
		m_DepthShader = 0;
	}

	//Release the shadow shader object
	if (m_ShadowShader)
	{
		m_ShadowShader->Shutdown();
		delete m_ShadowShader;
		m_ShadowShader = 0;
	}

	//Release the particle shader object
	if (m_ParticleShader)
	{
		m_ParticleShader->Shutdown();
		delete m_ParticleShader;
		m_ParticleShader = 0;
	}

	//Release the glass shader object
	if (m_GlassShader)
	{
		m_GlassShader->Shutdown();
		delete m_GlassShader;
		m_GlassShader = 0;
	}

	//Release the point light shader object
	if (m_PointLightShader)
	{
		m_PointLightShader->Shutdown();
		delete m_PointLightShader;
		m_PointLightShader = 0;
	}

	//Release the spec map shader object.
	if (m_SpecMapShader)
	{
		m_SpecMapShader->Shutdown();
		delete m_SpecMapShader;
		m_SpecMapShader = 0;
	}

	//Release the light map shader object.
	if (m_LightMapShader)
	{
		m_LightMapShader->Shutdown();
		delete m_LightMapShader;
		m_LightMapShader = 0;
	}

	//Release the multi texture shader object.
	if (m_MultiTextureShader)
	{
		m_MultiTextureShader->Shutdown();
		delete m_MultiTextureShader;
		m_MultiTextureShader = 0;
	}

	//Release the fire shader object.
	if (m_FireShader)
	{
		m_FireShader->Shutdown();
		delete m_FireShader;
		m_FireShader = 0;
	}

	//Release the bump map shader object.
	if (m_BumpMapShader)
	{
		m_BumpMapShader->Shutdown();
		delete m_BumpMapShader;
		m_BumpMapShader = 0;
	}

	//Release the light shader object.
	if (m_LightShader)
	{
		m_LightShader->Shutdown();
		delete m_LightShader;
		m_LightShader = 0;
	}

	//Release the texture shader object.
	if (m_TextureShader)
	{
		m_TextureShader->Shutdown();
		delete m_TextureShader;
		m_TextureShader = 0;
	}

	return;
}


bool ShaderManagerClass::RenderTextureShader(ID3D11DeviceContext* device, int indexCount, const XMMATRIX& worldMatrix, const XMMATRIX& viewMatrix, const XMMATRIX& projectionMatrix,
	ID3D11ShaderResourceView* texture)
{
	bool result;


	//Render the model using the texture shader.
	result = m_TextureShader->Render(device, indexCount, worldMatrix, viewMatrix, projectionMatrix, texture);
	if (!result)
	{
		return false;
	}

	return true;
}


bool ShaderManagerClass::RenderLightShader(ID3D11DeviceContext* deviceContext, int indexCount, const XMMATRIX& worldMatrix, const XMMATRIX& viewMatrix, const XMMATRIX& projectionMatrix,
	ID3D11ShaderResourceView* texture, XMFLOAT3 lightDirection, XMFLOAT4 ambient, XMFLOAT4 diffuse,
	XMFLOAT3 cameraPosition, XMFLOAT4 specular, float specularPower)
{
	bool result;


	//Render the model using the light shader.
	result = m_LightShader->Render(deviceContext, indexCount, worldMatrix, viewMatrix, projectionMatrix, texture, lightDirection, ambient, diffuse, cameraPosition,
		specular, specularPower);
	if (!result)
	{
		return false;
	}

	return true;
}


bool ShaderManagerClass::RenderBumpMapShader(ID3D11DeviceContext* deviceContext, int indexCount, const XMMATRIX& worldMatrix, const XMMATRIX& viewMatrix, const XMMATRIX& projectionMatrix,
	ID3D11ShaderResourceView* colorTexture, ID3D11ShaderResourceView* normalTexture, XMFLOAT3 lightDirection,
	XMFLOAT4 diffuse)
{
	bool result;


	//Render the model using the bump map shader.
	result = m_BumpMapShader->Render(deviceContext, indexCount, worldMatrix, viewMatrix, projectionMatrix, colorTexture, normalTexture, lightDirection, diffuse);
	if (!result)
	{
		return false;
	}

	return true;
}

bool ShaderManagerClass::RenderFireShader(ID3D11DeviceContext* deviceContext, int indexCount, const XMMATRIX& worldMatrix, const XMMATRIX& viewMatrix,
	const XMMATRIX& projectionMatrix, ID3D11ShaderResourceView* fireTexture,
	ID3D11ShaderResourceView* noiseTexture, ID3D11ShaderResourceView* alphaTexture, float frameTime,
	XMFLOAT3 scrollSpeeds, XMFLOAT3 scales, XMFLOAT2 distortion1, XMFLOAT2 distortion2,
	XMFLOAT2 distortion3, float distortionScale, float distortionBias)
{
	bool result;


	//Render the model using the fire shader.
	result = m_FireShader->Render(deviceContext, indexCount, worldMatrix, viewMatrix, projectionMatrix, fireTexture, noiseTexture, alphaTexture, frameTime, scrollSpeeds, scales, distortion1, distortion2,
		distortion3, distortionScale, distortionBias);

	if (!result)
	{
		return false;
	}

	return true;
}

bool ShaderManagerClass::RenderMultiTextureShader(ID3D11DeviceContext* deviceContext, int indexCount, XMMATRIX worldMatrix, XMMATRIX viewMatrix, XMMATRIX projectionMatrix, ID3D11ShaderResourceView** textureArray)
{
	bool result;


	//Render the model using the multi-texture map shader.
	result = m_MultiTextureShader->Render(deviceContext, indexCount, worldMatrix, viewMatrix, projectionMatrix, textureArray);
	if (!result)
	{
		return false;
	}

	return true;
}

bool ShaderManagerClass::RenderLightMapShader(ID3D11DeviceContext* deviceContext, int indexCount, XMMATRIX worldMatrix, XMMATRIX viewMatrix, XMMATRIX projectionMatrix, ID3D11ShaderResourceView** textureArray)
{
	bool result;


	//Render the model using the light map shader.
	result = m_LightMapShader->Render(deviceContext, indexCount, worldMatrix, viewMatrix, projectionMatrix, textureArray);
	if (!result)
	{
		return false;
	}

	return true;
}

bool ShaderManagerClass::RenderSpecMapShader(ID3D11DeviceContext* deviceContext, int indexCount, XMMATRIX worldMatrix, XMMATRIX viewMatrix,
	XMMATRIX projectionMatrix, ID3D11ShaderResourceView** textureArray, XMFLOAT3 lightDirection,
	XMFLOAT4 diffuseColor, XMFLOAT3 cameraPosition, XMFLOAT4 specularColor,
	float specularPower)
{
	bool result;


	//Render the model using the spec map shader.
	result = m_SpecMapShader->Render(deviceContext, indexCount, worldMatrix, viewMatrix, projectionMatrix, textureArray, lightDirection,
		diffuseColor, cameraPosition, specularColor, specularPower);
	if (!result)
	{
		return false;
	}

	return true;
}

bool ShaderManagerClass::RenderPointLightShader(ID3D11DeviceContext* deviceContext, int indexCount, XMMATRIX worldMatrix, XMMATRIX viewMatrix,
	XMMATRIX projectionMatrix, ID3D11ShaderResourceView* texture, XMFLOAT4 diffuseColor[], XMFLOAT4 lightPosition[])
{
	bool result;


	//Render the model using the point light shader.
	result = m_PointLightShader->Render(deviceContext, indexCount, worldMatrix, viewMatrix, projectionMatrix, texture, diffuseColor, lightPosition);
	if (!result)
	{
		return false;
	}

	return true;
}

bool ShaderManagerClass::RenderGlassShader(ID3D11DeviceContext* deviceContext, int indexCount, XMMATRIX worldMatrix, XMMATRIX viewMatrix, XMMATRIX projectionMatrix,
	ID3D11ShaderResourceView* colorTexture, ID3D11ShaderResourceView* normalTexture, ID3D11ShaderResourceView* refractionTexture, float refractionScale)
{
	bool result;


	//Render the model using the glass shader.
	result = m_GlassShader->Render(deviceContext, indexCount, worldMatrix, viewMatrix, projectionMatrix, colorTexture, normalTexture, refractionTexture, refractionScale);
	if (!result)
	{
		return false;
	}

	return true;
}

bool ShaderManagerClass::RenderParticleShader(ID3D11DeviceContext* deviceContext, int indexCount, XMMATRIX worldMatrix, XMMATRIX viewMatrix, XMMATRIX projectionMatrix, ID3D11ShaderResourceView* texture)
{
	bool result;


	//Render the model using the particle shader.
	result = m_ParticleShader->Render(deviceContext, indexCount, worldMatrix, viewMatrix, projectionMatrix, texture);
	if (!result)
	{
		return false;
	}

	return true;
}

bool ShaderManagerClass::RenderShadowShader(ID3D11DeviceContext* deviceContext, int indexCount, XMMATRIX worldMatrix, XMMATRIX viewMatrix, XMMATRIX projectionMatrix, XMMATRIX lightViewMatrix, XMMATRIX lightProjectionMatrix, ID3D11ShaderResourceView* texture, ID3D11ShaderResourceView* depthMapTexture, XMFLOAT3 lightPosition, XMFLOAT4 ambientColor, XMFLOAT4 diffuseColor)
{
	bool result;


	//Render the model using the shadow shader.
	result = m_ShadowShader->Render(deviceContext, indexCount, worldMatrix, viewMatrix, projectionMatrix, lightViewMatrix, lightProjectionMatrix, texture, depthMapTexture, lightPosition, ambientColor, diffuseColor);
	if (!result)
	{
		return false;
	}

	return true;
}

bool ShaderManagerClass::RenderDepthShader(ID3D11DeviceContext* deviceContext, int indexCount, XMMATRIX worldMatrix, XMMATRIX viewMatrix, XMMATRIX projectionMatrix)
{
	bool result;


	//Render the model using the depth shader.
	result = m_DepthShader->Render(deviceContext, indexCount, worldMatrix, viewMatrix, projectionMatrix);
	if (!result)
	{
		return false;
	}

	return true;
}
