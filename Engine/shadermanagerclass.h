#ifndef _SHADERMANAGERCLASS_H_
#define _SHADERMANAGERCLASS_H_

//INCLUDES
#include "d3dclass.h"
#include "textureshaderclass.h"
#include "lightshaderclass.h"
#include "bumpmapshaderclass.h"
#include "fireshaderclass.h"
#include "multitextureshaderclass.h"
#include "lightmapshaderclass.h"
#include "specmapshaderclass.h"
#include "pointlightshaderclass.h"
#include "glassshaderclass.h"
#include "particleshaderclass.h"
#include "shadowshaderclass.h"
#include "depthshaderclass.h"

class ShaderManagerClass
{
public:
	ShaderManagerClass();
	ShaderManagerClass(const ShaderManagerClass&);
	~ShaderManagerClass();

	bool Initialize(ID3D11Device*, HWND);
	void Shutdown();

	bool RenderTextureShader(ID3D11DeviceContext*, int, const XMMATRIX&, const XMMATRIX&, const XMMATRIX&, ID3D11ShaderResourceView*);

	bool RenderLightShader(ID3D11DeviceContext*, int, const XMMATRIX&, const XMMATRIX&, const XMMATRIX&, ID3D11ShaderResourceView*,
		XMFLOAT3, XMFLOAT4, XMFLOAT4, XMFLOAT3, XMFLOAT4, float);

	bool RenderBumpMapShader(ID3D11DeviceContext*, int, const XMMATRIX&, const XMMATRIX&, const XMMATRIX&, ID3D11ShaderResourceView*,
		ID3D11ShaderResourceView*, XMFLOAT3, XMFLOAT4);

	bool RenderFireShader(ID3D11DeviceContext*, int, const XMMATRIX&, const XMMATRIX&, const XMMATRIX&, ID3D11ShaderResourceView*, ID3D11ShaderResourceView*,
		ID3D11ShaderResourceView*, float, XMFLOAT3, XMFLOAT3, XMFLOAT2, XMFLOAT2, XMFLOAT2, float, float);

	bool RenderMultiTextureShader(ID3D11DeviceContext*, int, XMMATRIX, XMMATRIX, XMMATRIX, ID3D11ShaderResourceView**);

	bool RenderLightMapShader(ID3D11DeviceContext*, int, XMMATRIX, XMMATRIX, XMMATRIX, ID3D11ShaderResourceView**);

	bool RenderSpecMapShader(ID3D11DeviceContext*, int, XMMATRIX, XMMATRIX, XMMATRIX, ID3D11ShaderResourceView**, XMFLOAT3, XMFLOAT4, XMFLOAT3, XMFLOAT4, float);

	bool RenderPointLightShader(ID3D11DeviceContext*, int, XMMATRIX, XMMATRIX, XMMATRIX, ID3D11ShaderResourceView*, XMFLOAT4[], XMFLOAT4[]);

	bool RenderGlassShader(ID3D11DeviceContext*, int, XMMATRIX, XMMATRIX, XMMATRIX, ID3D11ShaderResourceView*,
		ID3D11ShaderResourceView*, ID3D11ShaderResourceView*, float);

	bool RenderParticleShader(ID3D11DeviceContext*, int, XMMATRIX, XMMATRIX, XMMATRIX, ID3D11ShaderResourceView*);

	bool RenderShadowShader(ID3D11DeviceContext*, int, XMMATRIX, XMMATRIX, XMMATRIX, XMMATRIX, XMMATRIX, ID3D11ShaderResourceView*, ID3D11ShaderResourceView*, XMFLOAT3, XMFLOAT4, XMFLOAT4);

	bool RenderDepthShader(ID3D11DeviceContext*, int, XMMATRIX, XMMATRIX, XMMATRIX);

private:
	TextureShaderClass* m_TextureShader;
	LightShaderClass* m_LightShader;
	BumpMapShaderClass* m_BumpMapShader;
	FireShaderClass* m_FireShader;
	MultiTextureShaderClass* m_MultiTextureShader;
	LightMapShaderClass* m_LightMapShader;
	SpecMapShaderClass* m_SpecMapShader;
	PointLightShaderClass* m_PointLightShader;
	GlassShaderClass* m_GlassShader;
	ParticleShaderClass* m_ParticleShader;
	ShadowShaderClass* m_ShadowShader;
	DepthShaderClass* m_DepthShader;
};

#endif