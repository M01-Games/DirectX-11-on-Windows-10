////////////////////////////////////////////////////////////////////////////////
// Filename: graphicsclass.h
////////////////////////////////////////////////////////////////////////////////
#ifndef _GRAPHICSCLASS_H_
#define _GRAPHICSCLASS_H_


///////////////////////
// MY CLASS INCLUDES //
///////////////////////
#include "inputclass.h"
#include "d3dclass.h"
#include "timerclass.h"
#include "shadermanagerclass.h"
#include "positionclass.h"
#include "cameraclass.h"
#include "lightclass.h"
#include "terrainclass.h"
#include "terrainshaderclass.h"
#include "waterclass.h"
#include "watershaderclass.h"
#include "reflectionshaderclass.h"
#include "rendertextureclass.h"
#include "modelclass.h"
#include "bumpmodelclass.h"


/////////////
// GLOBALS //
/////////////
const bool FULL_SCREEN = false;
const bool VSYNC_ENABLED = false;
const float SCREEN_DEPTH = 10000.0f;
const float SCREEN_NEAR = 0.1f;


////////////////////////////////////////////////////////////////////////////////
// Class name: GraphicsClass
////////////////////////////////////////////////////////////////////////////////
class GraphicsClass
{
public:
	GraphicsClass();
	GraphicsClass(const GraphicsClass&);
	~GraphicsClass();

	bool Initialize(HINSTANCE, HWND, int, int);
	void Shutdown();
	bool Frame();

private:
	bool HandleMovementInput(float);
	bool Render();

private:
	InputClass* m_Input;
	D3DClass* m_D3D;
	TimerClass* m_Timer;
	ShaderManagerClass* m_ShaderManager;
	PositionClass* m_Position;
	CameraClass* m_Camera;
	LightClass* m_Light;
	LightClass* m_DirectionalLight;
	TerrainClass* m_Terrain;
	TerrainShaderClass* m_TerrainShader;
	WaterClass* m_Water;
	WaterShaderClass* m_WaterShader;
	ReflectionShaderClass* m_ReflectionShader;
	RenderTextureClass* m_RefractionTexture, * m_ReflectionTexture, * m_ShadowTexture;
	ModelClass* m_Model1;
	ModelClass* m_Model2;
	ModelClass* m_Model4;
	BumpModelClass* m_Model3;
};

#endif