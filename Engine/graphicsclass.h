#ifndef _GRAPHICSCLASS_H_
#define _GRAPHICSCLASS_H_


//INCLUDES 
#include "inputclass.h"
#include "d3dclass.h"
#include "timerclass.h"
#include "positionclass.h"
#include "cameraclass.h"
#include "lightclass.h"
#include "terrainclass.h"
#include "terrainshaderclass.h"
#include "skydomeclass.h"
#include "skydomeshaderclass.h"
#include "skyplaneclass.h"
#include "skyplaneshaderclass.h"
#include "fpsclass.h"
#include "cpuclass.h"
#include "fontshaderclass.h"
#include "textclass.h"
#include "rendertextureclass.h"
#include "reflectionshaderclass.h"
#include "waterclass.h"
#include "watershaderclass.h"
#include "modelclass.h"
#include "multitexturemodelclass.h"
#include "bumpmodelclass.h"
#include "firemodelclass.h"
#include "shadermanagerclass.h"
#include "pointlightclass.h"
#include "particlesystemclass.h"


//GLOBALS
const bool FULL_SCREEN = false;
const bool VSYNC_ENABLED = false;
const float SCREEN_DEPTH = 10000.0f;
const float SCREEN_NEAR = 0.1f;
const int SHADOWMAP_WIDTH = 4096;
const int SHADOWMAP_HEIGHT = 4096;

class GraphicsClass
{
public:
	//Constructors
	GraphicsClass();
	GraphicsClass(const GraphicsClass&);

	//Destructor
	~GraphicsClass();

	//Init
	bool Initialize(HINSTANCE, HWND, int, int);

	//Invokes neccessary destructors
	void Shutdown();

	//Occurs each frame (Typically 60 times per second)
	bool Frame();

private:
	//Takes input from mouse and keyboard each frame
	bool HandleMovementInput(float);

	//Renders the basic scene
	bool Render();

	//Creates a texture for refractions in water
	void RenderRefractionToTexture();

	//Creates a texture for reflections in water
	void RenderReflectionToTexture();

	//Creates a texture for refractions in glass
	bool RenderGlassRefractionToTexture();

	//Creates a texture for shadows
	bool RenderShadowToTexture();

	bool ToggleTime;

	bool m_wireFrame;

private:
	//Pointers To Important Class Instances
	InputClass* m_Input;
	D3DClass* m_Direct3D;
	TimerClass* m_Timer;
	PositionClass* m_Position;
	CameraClass* m_Camera;
	LightClass* m_DirectionalLight;
	TerrainClass* m_Terrain;
	TerrainShaderClass* m_TerrainShader;
	SkyDomeClass* m_SkyDome;
	SkyDomeShaderClass* m_SkyDomeShader;
	SkyPlaneClass* m_SkyPlane;
	SkyPlaneShaderClass* m_SkyPlaneShader;
	FpsClass* m_Fps;
	CpuClass* m_Cpu;
	FontShaderClass* m_FontShader;
	TextClass* m_Text;
	RenderTextureClass* m_RefractionTexture, * m_ReflectionTexture, * m_ShadowTexture, * m_GlassRenderTexture;
	ReflectionShaderClass* m_ReflectionShader;
	WaterClass* m_Water;
	WaterShaderClass* m_WaterShader;
	ShaderManagerClass* m_ShaderManager;
	int mLastMousePosx, mLastMousePosy;

	//Point Lights
	PointLightClass* m_PointLight1, * m_PointLight2, * m_PointLight3, * m_PointLight4;

	//Models
	ModelClass* m_Model1;
	BumpModelClass* m_Bridge;
	BumpModelClass* m_Boat;
	BumpModelClass* m_House;


	ModelClass* m_Lantens;
	BumpModelClass* m_Campfire;
	FireModelClass* m_FireModel;
	ParticleSystemClass* m_ParticleSystem;

};

#endif