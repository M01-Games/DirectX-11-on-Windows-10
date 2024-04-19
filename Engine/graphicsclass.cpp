#include "graphicsclass.h"


GraphicsClass::GraphicsClass()
{
	m_Input = 0;
	m_Direct3D = 0;
	m_Timer = 0;
	m_Position = 0;
	m_Camera = 0;
	m_DirectionalLight = 0;
	m_Terrain = 0;
	m_TerrainShader = 0;
	m_SkyDome = 0;
	m_SkyDomeShader = 0;
	m_SkyPlane = 0;
	m_SkyPlaneShader = 0;
	m_Fps = 0;
	m_Cpu = 0;
	m_FontShader = 0;
	m_Text = 0;
	m_RefractionTexture = 0;
	m_ReflectionTexture = 0;
	m_ReflectionShader = 0;
	m_Water = 0;
	m_WaterShader = 0;
	m_ShaderManager = 0;

	m_PointLight1 = 0;
	m_PointLight2 = 0;
	m_PointLight3 = 0;
	m_PointLight4 = 0;


	mLastMousePosx = 0;
	mLastMousePosy = 0;

	m_Model1 = 0;
	m_Bridge = 0;


	m_Campfire = 0;
	m_FireModel = 0;
	m_ParticleSystem = 0;
}


GraphicsClass::GraphicsClass(const GraphicsClass& other)
{
}


GraphicsClass::~GraphicsClass()
{
}


bool GraphicsClass::Initialize(HINSTANCE hinstance, HWND hwnd, int screenWidth, int screenHeight)
{
	//Used for debugging
	bool result;

	XMMATRIX baseViewMatrix;
	char videoCard[128];
	int videoMemory;


	//Create the Direct3D object.
	m_Direct3D = new D3DClass;
	if (!m_Direct3D)
	{
		return false;
	}

	//Initialize the Direct3D object.
	result = m_Direct3D->Initialize(screenWidth, screenHeight, VSYNC_ENABLED, hwnd, FULL_SCREEN, SCREEN_DEPTH, SCREEN_NEAR);
	if (!result)
	{
		MessageBox(hwnd, L"Could not initialize Direct3D.", L"Error", MB_OK);
		return false;
	}

	//Create the input object.  The input object will be used to handle reading the keyboard and mouse input from the user.
	m_Input = new InputClass;
	if (!m_Input)
	{
		return false;
	}

	//Initialize the input object.
	result = m_Input->Initialize(hinstance, hwnd, screenWidth, screenHeight);
	//if (!result)
	//{
	//	MessageBox(hwnd, L"Could not initialize the input object.", L"Error", MB_OK);
	//	return false;
	//}

	//Retrieve the video card information.
	m_Direct3D->GetVideoCardInfo(videoCard, videoMemory);

	//Create the timer object.
	m_Timer = new TimerClass;
	if (!m_Timer)
	{
		return false;
	}

	//Initialize the timer object.
	result = m_Timer->Initialize();
	if (!result)
	{
		MessageBox(hwnd, L"Could not initialize the timer object.", L"Error", MB_OK);
		return false;
	}

	//Create the position object.
	m_Position = new PositionClass;
	if (!m_Position)
	{
		return false;
	}

	//Set the initial position and rotation of the viewer.
	m_Position->SetPosition(0, 55, -10);
	m_Position->SetRotation(0, 0, 0);

	//Create the camera object.
	m_Camera = new CameraClass;
	if (!m_Camera)
	{
		return false;
	}

	//Set the initial position of the camera.
	m_Camera->SetPosition(0.0f, 50.0f, -10.0f);
	m_Camera->GenerateBaseViewMatrix();
	m_Camera->GetBaseViewMatrix(baseViewMatrix);

	//Create the light object.
	m_DirectionalLight = new LightClass;
	if (!m_DirectionalLight)
	{
		return false;
	}

	//Initialize the light object.
	m_DirectionalLight->SetAmbientColor(0.15f, 0.15f, 0.15f, 1.0f);
	m_DirectionalLight->SetDiffuseColor(1.0f, 1.0f, 1.0f, 1.0f);
	m_DirectionalLight->SetSpecularColor(1.0f, 1.0f, 1.0f, 1.0f);
	m_DirectionalLight->SetSpecularPower(64.0f);
	m_DirectionalLight->SetPosition(0, 0, 0);
	m_DirectionalLight->SetLookAt(0.5f, -0.75f, 0.25f);
	m_DirectionalLight->GenerateProjectionMatrix(SCREEN_DEPTH, SCREEN_NEAR);

	//Night mode
	//m_DirectionalLight->SetDiffuseColor(0.15f, 0.15f, 0.15f, 1.0f);

	//Create the shader manager object.
	m_ShaderManager = new ShaderManagerClass;
	if (!m_ShaderManager)
	{
		return false;
	}

	//Initialize the shader manager object.
	result = m_ShaderManager->Initialize(m_Direct3D->GetDevice(), hwnd);
	if (!result)
	{
		MessageBox(hwnd, L"Could not initialize the shader manager object.", L"Error", MB_OK);
		return false;
	}

	//Create the terrain object.
	m_Terrain = new TerrainClass;
	if (!m_Terrain)
	{
		return false;
	}

	//Initialize the terrain object.
	result = m_Terrain->Initialize(m_Direct3D->GetDevice(), "../Engine/data/HM3.bmp", "../Engine/data/HMC.bmp", 12.5f, L"../Engine/data/grass01.dds",
		L"../Engine/data/grass01_n.dds");
	if (!result)
	{
		MessageBox(hwnd, L"Could not initialize the terrain object.", L"Error", MB_OK);
		return false;
	}

	//Create the terrain shader object.
	m_TerrainShader = new TerrainShaderClass;
	if (!m_TerrainShader)
	{
		return false;
	}

	//Initialize the terrain shader object.
	result = m_TerrainShader->Initialize(m_Direct3D->GetDevice(), hwnd);
	if (!result)
	{
		MessageBox(hwnd, L"Could not initialize the terrain shader object.", L"Error", MB_OK);
		return false;
	}

	//Create the fps object.
	m_Fps = new FpsClass;
	if (!m_Fps)
	{
		return false;
	}

	//Initialize the fps object.
	m_Fps->Initialize();

	//Create the cpu object.
	m_Cpu = new CpuClass;
	if (!m_Cpu)
	{
		return false;
	}

	//Initialize the cpu object.
	m_Cpu->Initialize();

	//Create the font shader object.
	m_FontShader = new FontShaderClass;
	if (!m_FontShader)
	{
		return false;
	}

	//Initialize the font shader object.
	result = m_FontShader->Initialize(m_Direct3D->GetDevice(), hwnd);
	if (!result)
	{
		MessageBox(hwnd, L"Could not initialize the font shader object.", L"Error", MB_OK);
		return false;
	}

	//Create the text object.
	m_Text = new TextClass;
	if (!m_Text)
	{
		return false;
	}

	//Initialize the text object.
	result = m_Text->Initialize(m_Direct3D->GetDevice(), m_Direct3D->GetDeviceContext(), hwnd, screenWidth, screenHeight, baseViewMatrix);
	if (!result)
	{
		MessageBox(hwnd, L"Could not initialize the text object.", L"Error", MB_OK);
		return false;
	}

	//Set the video card information in the text object.
	result = m_Text->SetVideoCardInfo(videoCard, videoMemory, m_Direct3D->GetDeviceContext());
	if (!result)
	{
		MessageBox(hwnd, L"Could not set video card info in the text object.", L"Error", MB_OK);
		return false;
	}

	//Create the render to texture object for water refraction.
	m_RefractionTexture = new RenderTextureClass;
	if (!m_RefractionTexture)
	{
		return false;
	}

	//Initialize the refraction render to texture object.
	result = m_RefractionTexture->Initialize(m_Direct3D->GetDevice(), screenWidth, screenHeight, SCREEN_DEPTH, SCREEN_NEAR);
	if (!result)
	{
		MessageBox(hwnd, L"Could not initialize the refraction render to texture object.", L"Error", MB_OK);
		return false;
	}

	//Create the render to texture object for water reflections.
	m_ReflectionTexture = new RenderTextureClass;
	if (!m_ReflectionTexture)
	{
		return false;
	}

	//Initialize the reflection render to texture object.
	result = m_ReflectionTexture->Initialize(m_Direct3D->GetDevice(), screenWidth, screenHeight, SCREEN_DEPTH, SCREEN_NEAR);
	if (!result)
	{
		MessageBox(hwnd, L"Could not initialize the reflection render to texture object.", L"Error", MB_OK);
		return false;
	}

	//Create the render to texture object for shadows.
	m_ShadowTexture = new RenderTextureClass;
	if (!m_ShadowTexture)
	{
		return false;
	}

	//Initialize the render to texture object.
	result = m_ShadowTexture->Initialize(m_Direct3D->GetDevice(), SHADOWMAP_WIDTH, SHADOWMAP_HEIGHT, SCREEN_DEPTH, SCREEN_NEAR);
	if (!result)
	{
		MessageBox(hwnd, L"Could not initialize the render to texture object.", L"Error", MB_OK);
		return false;
	}

	//Create the reflection shader object.
	m_ReflectionShader = new ReflectionShaderClass;
	if (!m_ReflectionShader)
	{
		return false;
	}

	//Initialize the reflection shader object.
	result = m_ReflectionShader->Initialize(m_Direct3D->GetDevice(), hwnd);
	if (!result)
	{
		MessageBox(hwnd, L"Could not initialize the reflection shader object.", L"Error", MB_OK);
		return false;
	}

	//Create the water object.
	m_Water = new WaterClass;
	if (!m_Water)
	{
		return false;
	}

	//Initialize the water object.
	result = m_Water->Initialize(m_Direct3D->GetDevice(), L"../Engine/data/waternormal.dds", 6.0f, 1000.0f);
	if (!result)
	{
		MessageBox(hwnd, L"Could not initialize the water object.", L"Error", MB_OK);
		return false;
	}

	//Create the water shader object.
	m_WaterShader = new WaterShaderClass;
	if (!m_WaterShader)
	{
		return false;
	}

	//Initialize the water shader object.
	result = m_WaterShader->Initialize(m_Direct3D->GetDevice(), hwnd);
	if (!result)
	{
		MessageBox(hwnd, L"Could not initialize the water shader object.", L"Error", MB_OK);
		return false;
	}

	//Create the sky dome object.
	m_SkyDome = new SkyDomeClass;
	if (!m_SkyDome)
	{
		return false;
	}

	//Initialize the sky dome object.
	result = m_SkyDome->Initialize(m_Direct3D->GetDevice());
	if (!result)
	{
		MessageBox(hwnd, L"Could not initialize the sky dome object.", L"Error", MB_OK);
		return false;
	}

	//Create the sky dome shader object.
	m_SkyDomeShader = new SkyDomeShaderClass;
	if (!m_SkyDomeShader)
	{
		return false;
	}

	//Initialize the sky dome shader object.
	result = m_SkyDomeShader->Initialize(m_Direct3D->GetDevice(), hwnd);
	if (!result)
	{
		MessageBox(hwnd, L"Could not initialize the sky dome shader object.", L"Error", MB_OK);
		return false;
	}

	//Create the sky plane object.
	m_SkyPlane = new SkyPlaneClass;
	if (!m_SkyPlane)
	{
		return false;
	}

	//Initialize the sky plane object.
	result = m_SkyPlane->Initialize(m_Direct3D->GetDevice(), L"../Engine/data/clouds.dds", L"../Engine/data/perturb001.dds");
	if (!result)
	{
		MessageBox(hwnd, L"Could not initialize the sky plane object.", L"Error", MB_OK);
		return false;
	}

	//Create the sky plane shader object.
	m_SkyPlaneShader = new SkyPlaneShaderClass;
	if (!m_SkyPlaneShader)
	{
		return false;
	}

	//Initialize the sky plane shader object.
	result = m_SkyPlaneShader->Initialize(m_Direct3D->GetDevice(), hwnd);
	if (!result)
	{
		MessageBox(hwnd, L"Could not initialize the sky plane shader object.", L"Error", MB_OK);
		return false;
	}

	//Create the first light object.
	m_PointLight1 = new PointLightClass;
	if (!m_PointLight1)
	{
		return false;
	}

	//Initialize the first light object.
	m_PointLight1->SetDiffuseColor(1.0f, 0.0f, 0.0f, 1.0f);
	m_PointLight1->SetPosition(205, 8, 205);

	//Create the second light object.
	m_PointLight2 = new PointLightClass;
	if (!m_PointLight2)
	{
		return false;
	}

	//Initialize the second light object.
	m_PointLight2->SetDiffuseColor(0.0f, 0.0f, 0.0f, 1.0f);
	m_PointLight2->SetPosition(255, 20, 350);

	//Create the third light object.
	m_PointLight3 = new PointLightClass;
	if (!m_PointLight3)
	{
		return false;
	}

	//Initialize the third light object.
	m_PointLight3->SetDiffuseColor(0.0f, 0.0f, 0.0f, 1.0f);
	m_PointLight3->SetPosition(255, 20, 450);

	//Create the fourth light object.
	m_PointLight4 = new PointLightClass;
	if (!m_PointLight4)
	{
		return false;
	}

	//Initialize the fourth light object.
	m_PointLight4->SetDiffuseColor(0.0f, 0.0f, 0.0f, 1.0f);
	m_PointLight4->SetPosition(255, 20, 550);

	//Create the render to texture object.
	m_GlassRenderTexture = new RenderTextureClass;
	if (!m_GlassRenderTexture)
	{
		return false;
	}

	//Initialize the render to texture object.
	result = m_GlassRenderTexture->Initialize(m_Direct3D->GetDevice(), screenWidth, screenHeight, SCREEN_DEPTH, SCREEN_NEAR);
	if (!result)
	{
		return false;
	}


	// Create the model object.
	m_Model1 = new ModelClass;
	if (!m_Model1)
	{
		return false;
	}

	// Initialize the model object.
	result = m_Model1->Initialize(m_Direct3D->GetDevice(), "../Engine/data/Zombie.txt", L"../Engine/data/Zombie-Textured.dds");
	if (!result)
	{
		MessageBox(hwnd, L"Could not initialize the first model object.", L"Error", MB_OK);
		return false;
	}

	//Create a bridge bump model object.
	m_Bridge = new BumpModelClass;
	if (!m_Bridge)
	{
		return false;
	}

	//Initialize the bridge bump model object.
	result = m_Bridge->Initialize(m_Direct3D->GetDevice(), "../Engine/data/Bridge.txt", L"../Engine/data/T_Trim_01_BaseColor.dds", L"../Engine/data/T_Trim_01_Normal.dds");
	if (!result)
	{
		MessageBox(hwnd, L"Could not initialize the bridge model object.", L"Error", MB_OK);
		return false;
	}

	//Create the campfire bump model object for models with normal maps and related vectors.
	m_Campfire = new BumpModelClass;
	if (!m_Campfire)
	{
		return false;
	}

	//Initialize the bump model object.
	result = m_Campfire->Initialize(m_Direct3D->GetDevice(), "../Engine/data/Campfire.txt", L"../Engine/data/Campfire_Base.dds", L"../Engine/data/Campfire_Normal.dds");
	if (!result)
	{
		MessageBox(hwnd, L"Could not initialize the campfire model object.", L"Error", MB_OK);
		return false;
	}

	//Create the fire model object.
	m_FireModel = new FireModelClass;
	if (!m_FireModel)
	{
		return false;
	}

	//Initialize the fire model object.
	result = m_FireModel->Initialize(m_Direct3D->GetDevice(), "../Engine/data/new-ninjaHead.txt", L"../Engine/data/fire01.dds", L"../Engine/data/noise01.dds", L"../Engine/data/alpha01.dds");
	if (!result)
	{
		MessageBox(hwnd, L"Could not initialize the fire model object.", L"Error", MB_OK);
		return false;
	}

	//Create the particle system object.
	m_ParticleSystem = new ParticleSystemClass;
	if (!m_ParticleSystem)
	{
		return false;
	}

	//Initialize the particle system object.
	result = m_ParticleSystem->Initialize(m_Direct3D->GetDevice(), L"../Engine/data/ice.dds");
	if (!result)
	{
		return false;
	}


	return true;
}


void GraphicsClass::Shutdown()
{
	// Release the model objects.
	if (m_Model1)
	{
		m_Model1->Shutdown();
		delete m_Model1;
		m_Model1 = 0;
	}

	//Release the bump object.
	if (m_Bridge)
	{
		m_Bridge->Shutdown();
		delete m_Bridge;
		m_Bridge = 0;
	}

	//Release the campfire object.
	if (m_Campfire)
	{
		m_Campfire->Shutdown();
		delete m_Campfire;
		m_Campfire = 0;
	}

	//Release the fire object.
	if (m_FireModel)
	{
		m_FireModel->Shutdown();
		delete m_FireModel;
		m_FireModel = 0;
	}

	//Release the particle system object.
	if (m_ParticleSystem)
	{
		m_ParticleSystem->Shutdown();
		delete m_ParticleSystem;
		m_ParticleSystem = 0;
	}




	//Release the text object.
	if (m_Text)
	{
		m_Text->Shutdown();
		delete m_Text;
		m_Text = 0;
	}

	//Release the font shader object.
	if (m_FontShader)
	{
		m_FontShader->Shutdown();
		delete m_FontShader;
		m_FontShader = 0;
	}

	//Release the light objects.
	if (m_PointLight1)
	{
		delete m_PointLight1;
		m_PointLight1 = 0;
	}

	if (m_PointLight2)
	{
		delete m_PointLight2;
		m_PointLight2 = 0;
	}

	if (m_PointLight3)
	{
		delete m_PointLight3;
		m_PointLight3 = 0;
	}

	if (m_PointLight4)
	{
		delete m_PointLight4;
		m_PointLight4 = 0;
	}

	//Release the sky plane shader object.
	if (m_SkyPlaneShader)
	{
		m_SkyPlaneShader->Shutdown();
		delete m_SkyPlaneShader;
		m_SkyPlaneShader = 0;
	}

	//Release the sky plane object.
	if (m_SkyPlane)
	{
		m_SkyPlane->Shutdown();
		delete m_SkyPlane;
		m_SkyPlane = 0;
	}

	//Release the sky dome shader object.
	if (m_SkyDomeShader)
	{
		m_SkyDomeShader->Shutdown();
		delete m_SkyDomeShader;
		m_SkyDomeShader = 0;
	}

	//Release the sky dome object.
	if (m_SkyDome)
	{
		m_SkyDome->Shutdown();
		delete m_SkyDome;
		m_SkyDome = 0;
	}

	//Release the water shader object.
	if (m_WaterShader)
	{
		m_WaterShader->Shutdown();
		delete m_WaterShader;
		m_WaterShader = 0;
	}

	//Release the water object.
	if (m_Water)
	{
		m_Water->Shutdown();
		delete m_Water;
		m_Water = 0;
	}

	//Release the reflection shader object.
	if (m_ReflectionShader)
	{
		m_ReflectionShader->Shutdown();
		delete m_ReflectionShader;
		m_ReflectionShader = 0;
	}

	//Release the reflection render to texture object.
	if (m_ReflectionTexture)
	{
		m_ReflectionTexture->Shutdown();
		delete m_ReflectionTexture;
		m_ReflectionTexture = 0;
	}

	//Release the refraction render to texture object.
	if (m_RefractionTexture)
	{
		m_RefractionTexture->Shutdown();
		delete m_RefractionTexture;
		m_RefractionTexture = 0;
	}

	//Release the cpu object.
	if (m_Cpu)
	{
		m_Cpu->Shutdown();
		delete m_Cpu;
		m_Cpu = 0;
	}

	//Release the fps object.
	if (m_Fps)
	{
		delete m_Fps;
		m_Fps = 0;
	}

	//Release the terrain shader object.
	if (m_TerrainShader)
	{
		m_TerrainShader->Shutdown();
		delete m_TerrainShader;
		m_TerrainShader = 0;
	}

	//Release the terrain object.
	if (m_Terrain)
	{
		m_Terrain->Shutdown();
		delete m_Terrain;
		m_Terrain = 0;
	}

	//Release the light object.
	if (m_DirectionalLight)
	{
		delete m_DirectionalLight;
		m_DirectionalLight = 0;
	}

	//Release the camera object.
	if (m_Camera)
	{
		delete m_Camera;
		m_Camera = 0;
	}

	//Release the position object.
	if (m_Position)
	{
		delete m_Position;
		m_Position = 0;
	}

	//Release the timer object.
	if (m_Timer)
	{
		delete m_Timer;
		m_Timer = 0;
	}

	//Release the Direct3D object.
	if (m_Direct3D)
	{
		m_Direct3D->Shutdown();
		delete m_Direct3D;
		m_Direct3D = 0;
	}

	//Release the input object.
	if (m_Input)
	{
		m_Input->Shutdown();
		delete m_Input;
		m_Input = 0;
	}

	return;
}


bool GraphicsClass::Frame()
{
	bool result;

	//Update the system stats
	m_Timer->Frame();
	m_Fps->Frame();
	m_Cpu->Frame();

	//Read the user input
	result = m_Input->Frame();
	if (!result)
	{
		return false;
	}

	//Do the water frame processing
	m_Water->Frame();

	//Do the sky plane frame processing
	m_SkyPlane->Frame();

	//Do the particle system frame processing.
	m_ParticleSystem->Frame(m_Timer->GetTime(), m_Direct3D->GetDeviceContext());

	//Render the refraction of the scene to a texture
	RenderRefractionToTexture();

	//Render the reflection of the scene to a texture
	RenderReflectionToTexture();

	//Render the glass refraction of the scene to a texture
	RenderGlassRefractionToTexture();

	//Render the shadows of the scene to a texture
	result = RenderShadowToTexture();
	if (!result)
	{
		return false;
	}

	//Check if the user pressed escape and wants to exit the application
	if (m_Input->IsEscapePressed() == true)
	{
		return false;
	}

	//Do the frame input processing
	result = HandleMovementInput(m_Timer->GetTime());
	if (!result)
	{
		return false;
	}

	//Update the FPS value in the text object
	result = m_Text->SetFps(m_Fps->GetFps(), m_Direct3D->GetDeviceContext());
	if (!result)
	{
		return false;
	}

	//Update the CPU usage value in the text object
	result = m_Text->SetCpu(m_Cpu->GetCpuPercentage(), m_Direct3D->GetDeviceContext());
	if (!result)
	{
		return false;
	}



	m_DirectionalLight->Frame();
	//Generate the light view matrix based on the light's position
	m_DirectionalLight->GenerateViewMatrix();
	if (!ToggleTime)
	{
		m_DirectionalLight->SetAmbientColor(0.15f, 0.15f, 0.15f, 1.0f);
		m_DirectionalLight->SetDiffuseColor(0.15f, 0.15f, 0.15f, 1.0f);
		m_DirectionalLight->SetSpecularColor(1.0f, 1.0f, 1.0f, 1.0f);
		m_DirectionalLight->SetSpecularPower(64.0f);
		m_DirectionalLight->SetPosition(0, 0, 0);
		m_DirectionalLight->SetLookAt(0.5f, -0.75f, 0.25f);
		m_DirectionalLight->GenerateProjectionMatrix(SCREEN_DEPTH, SCREEN_NEAR);
	}
	else
	{
		m_DirectionalLight->SetAmbientColor(0.15f, 0.15f, 0.15f, 1.0f);
		m_DirectionalLight->SetDiffuseColor(1.0f, 1.0f, 1.0f, 1.0f);
		m_DirectionalLight->SetSpecularColor(1.0f, 1.0f, 1.0f, 1.0f);
		m_DirectionalLight->SetSpecularPower(64.0f);
		m_DirectionalLight->SetPosition(0, 0, 0);
		m_DirectionalLight->SetLookAt(0.5f, -0.75f, 0.25f);
		m_DirectionalLight->GenerateProjectionMatrix(SCREEN_DEPTH, SCREEN_NEAR);
	}

	// Turn on wire frame
	if (m_wireFrame)
	{
		m_Direct3D->EnableWireframe();
	}
	else
	{
		m_Direct3D->DisableWireframe();
	}



	//Render the graphics
	result = Render();
	if (!result)
	{
		return false;
	}

	return result;
}


bool GraphicsClass::HandleMovementInput(float frameTime)
{
	bool keyDown, result;
	float posX, posY, posZ, rotX, rotY, rotZ;

	// Set the frame time for calculating the updated position.
	m_Position->SetFrameTime(frameTime);

	// Handle the input.
	keyDown = m_Input->IsLeftPressed();
	m_Position->TurnLeft(keyDown);

	keyDown = m_Input->IsRightPressed();
	m_Position->TurnRight(keyDown);

	keyDown = m_Input->IsWPressed();
	m_Position->MoveForward(keyDown);

	keyDown = m_Input->IsSPressed();
	m_Position->MoveBackward(keyDown);

	keyDown = m_Input->IsAPressed();
	m_Position->MoveLeft(keyDown);

	keyDown = m_Input->IsDPressed();
	m_Position->MoveRight(keyDown);

	keyDown = m_Input->IsPgUpPressed();
	m_Position->MoveUpward(keyDown);

	keyDown = m_Input->IsPgDownPressed();
	m_Position->MoveDownward(keyDown);

	keyDown = m_Input->IsEPressed();
	m_Position->MoveUpward(keyDown);

	keyDown = m_Input->IsQPressed();
	m_Position->MoveDownward(keyDown);

	keyDown = m_Input->IsUpPressed();
	m_Position->LookUpward(keyDown);

	keyDown = m_Input->IsDownPressed();
	m_Position->LookDownward(keyDown);



	if (m_Input->IsNPressed())
	{
		if (!ToggleTime)
		{
			m_DirectionalLight->SetAmbientColor(0.15f, 0.15f, 0.15f, 1.0f);
			m_DirectionalLight->SetDiffuseColor(0.15f, 0.15f, 0.15f, 1.0f);
			m_DirectionalLight->SetSpecularColor(1.0f, 1.0f, 1.0f, 1.0f);
			m_DirectionalLight->SetSpecularPower(64.0f);
			m_DirectionalLight->SetPosition(0, 0, 0);
			m_DirectionalLight->SetLookAt(0.5f, -0.75f, 0.25f);
			m_DirectionalLight->GenerateProjectionMatrix(SCREEN_DEPTH, SCREEN_NEAR);
			ToggleTime;
		}
		else
		{
			m_DirectionalLight->SetAmbientColor(0.15f, 0.15f, 0.15f, 1.0f);
			m_DirectionalLight->SetDiffuseColor(1.0f, 1.0f, 1.0f, 1.0f);
			m_DirectionalLight->SetSpecularColor(1.0f, 1.0f, 1.0f, 1.0f);
			m_DirectionalLight->SetSpecularPower(64.0f);
			m_DirectionalLight->SetPosition(0, 0, 0);
			m_DirectionalLight->SetLookAt(0.5f, -0.75f, 0.25f);
			m_DirectionalLight->GenerateProjectionMatrix(SCREEN_DEPTH, SCREEN_NEAR);
			!ToggleTime;
		}
	}

	// Determine if the terrain should be rendered in wireframe or not.
	if (m_Input->IsF1Toggled())
	{
		m_wireFrame = !m_wireFrame;
		// Turn on wire frame
		if (m_wireFrame)
		{
			m_Direct3D->EnableWireframe();
		}
		else
		{
			m_Direct3D->DisableWireframe();
		}
	}



	// HandleMouse Rotations
	m_Position->MouseRotate(m_Input->GetMouseXDelta(), m_Input->GetMouseYDelta());

	// Get the view point position/rotation.
	m_Position->GetPosition(posX, posY, posZ);
	m_Position->GetRotation(rotX, rotY, rotZ);
	m_Input->ResetCursorPos();

	// Set the position of the camera.
	m_Camera->SetPosition(posX, posY, posZ);
	m_Camera->SetRotation(rotX, rotY, rotZ);

	//Update the position values in the text object
	result = m_Text->SetCameraPosition(posX, posY, posZ, m_Direct3D->GetDeviceContext());
	if (!result)
	{
		return false;
	}

	//Update the rotation values in the text object
	result = m_Text->SetCameraRotation(rotX, rotY, rotZ, m_Direct3D->GetDeviceContext());
	if (!result)
	{
		return false;
	}

	return true;
}


bool GraphicsClass::RenderShadowToTexture()
{
	XMMATRIX worldMatrix, lightViewMatrix, lightProjectionMatrix, translateMatrix;
	float posX, posY, posZ;
	bool result;


	//Set the render target to be the render to texture
	m_ShadowTexture->SetRenderTarget(m_Direct3D->GetDeviceContext());

	//Clear the render to texture
	m_ShadowTexture->ClearRenderTarget(m_Direct3D->GetDeviceContext(), 0.0f, 0.0f, 0.0f, 1.0f);

	//Generate the light view matrix based on the light's position
	m_DirectionalLight->GenerateViewMatrix();

	//Get the world matrix from the d3d object
	m_Direct3D->GetWorldMatrix(worldMatrix);

	//Get the view and orthographic matrices from the light object
	m_DirectionalLight->GetViewMatrix(lightViewMatrix);
	m_DirectionalLight->GetProjectionMatrix(lightProjectionMatrix);

	// Setup the rotation and translation of the 1st model.
	worldMatrix = XMMatrixIdentity();
	worldMatrix = XMMatrixScaling(5.0, 7.5, 5.0);
	translateMatrix = XMMatrixTranslation(-2550.0f, 0.0f, -2550.0f);
	worldMatrix = XMMatrixMultiply(worldMatrix, translateMatrix);

	//Render the terrain model with the depth shader
	m_Terrain->Render(m_Direct3D->GetDeviceContext());
	result = m_ShaderManager->RenderDepthShader(m_Direct3D->GetDeviceContext(), m_Terrain->GetIndexCount(), worldMatrix, lightViewMatrix, lightProjectionMatrix);
	if (!result)
	{
		return false;
	}

	//Reset the render target back to the original back buffer and not the render to texture anymore
	m_Direct3D->SetBackBufferRenderTarget();

	//Reset the viewport back to the original
	m_Direct3D->ResetViewport();

	return true;
}


bool GraphicsClass::Render()
{
	XMMATRIX worldMatrix, viewMatrix, projectionMatrix, orthoMatrix, baseViewMatrix, reflectionViewMatrix, translateMatrix, lightViewMatrix, lightProjectionMatrix;
	XMFLOAT4 diffuseColor[4];
	XMFLOAT4 lightPosition[4];
	bool result;
	XMFLOAT3 cameraPosition;
	//Variables for the fire 
	XMFLOAT3 scrollSpeeds, scales;
	XMFLOAT2 distortion1, distortion2, distortion3;
	float distortionScale, distortionBias;
	static float frameTime = 0.0f;
	//Glass variables
	float glassRefractionScale;
	float iceRefractionScale;
	float posX, posY, posZ;

	//Set the refraction scale for the glass and ice shader
	glassRefractionScale = 0.01f;
	iceRefractionScale = 0.1f;

	//Increment the frame time counter
	frameTime += 0.01f;
	if (frameTime > 1000.0f)
	{
		frameTime = 0.0f;
	}

	//Set the three scrolling speeds for the three different noise textures
	scrollSpeeds = XMFLOAT3(1.3f, 2.1f, 2.3f);

	//Set the three scales which will be used to create the three different noise octave textures
	scales = XMFLOAT3(1.0f, 2.0f, 3.0f);

	//Set the three different x and y distortion factors for the three different noise textures
	distortion1 = XMFLOAT2(0.1f, 0.2f);
	distortion2 = XMFLOAT2(0.1f, 0.3f);
	distortion3 = XMFLOAT2(0.1f, 0.1f);

	//The the scale and bias of the texture coordinate sampling perturbation
	distortionScale = 0.8f;
	distortionBias = 0.5f;

	//Update the rotation variable each frame
	static float rotation;
	rotation += (float)XM_PI * 0.0005f * m_Timer->GetTime();

	//Create the diffuse color array from the four light colors
	diffuseColor[0] = m_PointLight1->GetDiffuseColor();
	diffuseColor[1] = m_PointLight2->GetDiffuseColor();
	diffuseColor[2] = m_PointLight3->GetDiffuseColor();
	diffuseColor[3] = m_PointLight4->GetDiffuseColor();

	//Create the light position array from the four light positions
	lightPosition[0] = m_PointLight1->GetPosition();
	lightPosition[1] = m_PointLight2->GetPosition();
	lightPosition[2] = m_PointLight3->GetPosition();
	lightPosition[3] = m_PointLight4->GetPosition();

	//Clear the scene.
	m_Direct3D->BeginScene(0.0f, 0.0f, 0.0f, 1.0f);

	//Generate the view matrix based on the camera's position
	m_Camera->Render();

	//Generate the reflection matrix based on the camera's position and the height of the water
	m_Camera->RenderReflection(m_Water->GetWaterHeight());

	//Get the world, view, projection, ortho, and base view matrices from the camera and Direct3D objects
	m_Direct3D->GetWorldMatrix(worldMatrix);
	m_Camera->GetViewMatrix(viewMatrix);
	m_Direct3D->GetProjectionMatrix(projectionMatrix);
	m_Direct3D->GetOrthoMatrix(orthoMatrix);
	m_Camera->GetReflectionViewMatrix(reflectionViewMatrix);



	// Turn on wire frame
	if (m_wireFrame)
	{
		m_Direct3D->EnableWireframe();
	}
	else
	{
		m_Direct3D->DisableWireframe();
	}



	//Get the position of the camera
	cameraPosition = m_Camera->GetPosition();

	//Translate the sky dome to be centered around the camera position
	worldMatrix = XMMatrixTranslation(cameraPosition.x, cameraPosition.y, cameraPosition.z);

	//Turn off back face culling and the Z buffer
	m_Direct3D->TurnOffCulling();
	m_Direct3D->TurnZBufferOff();

	//Setup the scaling of the sky dome
	worldMatrix = XMMatrixScaling(500.0, 750.0, 500.0);

	//Render the sky dome using the sky dome shader
	m_SkyDome->Render(m_Direct3D->GetDeviceContext());
	m_SkyDomeShader->Render(m_Direct3D->GetDeviceContext(), m_SkyDome->GetIndexCount(), worldMatrix, viewMatrix, projectionMatrix,
		m_SkyDome->GetApexColor(), m_SkyDome->GetCenterColor());

	//Turn back face culling back on
	m_Direct3D->TurnOnCulling();

	//Enable additive blending so the clouds blend with the sky dome color
	m_Direct3D->EnableSecondBlendState();

	//Render the sky plane using the sky plane shader
	m_SkyPlane->Render(m_Direct3D->GetDeviceContext());
	m_SkyPlaneShader->Render(m_Direct3D->GetDeviceContext(), m_SkyPlane->GetIndexCount(), worldMatrix, viewMatrix, projectionMatrix,
		m_SkyPlane->GetCloudTexture(), m_SkyPlane->GetPerturbTexture(), m_SkyPlane->GetTranslation(), m_SkyPlane->GetScale(),
		m_SkyPlane->GetBrightness());

	//Turn off blending
	m_Direct3D->TurnOffAlphaBlending();

	//Turn the Z buffer back on
	m_Direct3D->TurnZBufferOn();

	//Translate to the location of the water and render it
	worldMatrix = XMMatrixTranslation(0.0f, m_Water->GetWaterHeight(), 0.0f);

	m_Water->Render(m_Direct3D->GetDeviceContext());
	m_WaterShader->Render(m_Direct3D->GetDeviceContext(), m_Water->GetIndexCount(), worldMatrix, viewMatrix, projectionMatrix, reflectionViewMatrix,
		m_RefractionTexture->GetShaderResourceView(), m_ReflectionTexture->GetShaderResourceView(), m_Water->GetTexture(),
		m_Camera->GetPosition(), m_Water->GetNormalMapTiling(), m_Water->GetWaterTranslation(), m_Water->GetReflectRefractScale(),
		m_Water->GetRefractionTint(), m_DirectionalLight->GetLookAt(), m_Water->GetSpecularShininess());

	//Generate the light view matrix based on the light's position
	m_DirectionalLight->GenerateViewMatrix();

	//Get the world, view, and projection matrices from the camera and d3d objects
	m_Camera->GetViewMatrix(viewMatrix);
	m_Direct3D->GetWorldMatrix(worldMatrix);
	m_Direct3D->GetProjectionMatrix(projectionMatrix);

	//Get the light's view and projection matrices from the light object
	m_DirectionalLight->GetViewMatrix(lightViewMatrix);
	m_DirectionalLight->GetProjectionMatrix(lightProjectionMatrix);

	// Setup the rotation and translation of the 1st model.
	worldMatrix = XMMatrixIdentity();
	worldMatrix = XMMatrixScaling(5.0, 7.5, 5.0);
	translateMatrix = XMMatrixTranslation(-2550, 0, -2550);
	worldMatrix = XMMatrixMultiply(worldMatrix, translateMatrix);

	//Render the terrain using the terrain shader
	m_Terrain->Render(m_Direct3D->GetDeviceContext());
	result = m_TerrainShader->Render(m_Direct3D->GetDeviceContext(), m_Terrain->GetIndexCount(), worldMatrix, viewMatrix, projectionMatrix, m_Terrain->GetColorTexture(),
		m_Terrain->GetNormalTexture(), m_DirectionalLight->GetDiffuseColor(), m_DirectionalLight->GetLookAt(), 2.0f);
	if (!result)
	{
		return false;
	}

	
	// Setup the rotation and translation of the 1st model.
	worldMatrix = XMMatrixIdentity();
	worldMatrix = XMMatrixScaling(0.5, 0.5, 0.5);
	translateMatrix = XMMatrixTranslation(150, 8, 150);
	worldMatrix = XMMatrixMultiply(worldMatrix, translateMatrix);

	// Render the first model using the texture shader.
	m_Model1->Render(m_Direct3D->GetDeviceContext());
	result = m_ShaderManager->RenderLightShader(m_Direct3D->GetDeviceContext(), m_Model1->GetIndexCount(), worldMatrix, viewMatrix, projectionMatrix,
		m_Model1->GetTexture(), m_DirectionalLight->GetLookAt(), m_DirectionalLight->GetAmbientColor(), m_DirectionalLight->GetDiffuseColor(),
		m_Camera->GetPosition(), m_DirectionalLight->GetSpecularColor(), m_DirectionalLight->GetSpecularPower());
	if (!result)
	{
		return false;
	}

	//PointLight Tester \/
	
	// Setup the rotation and translation of the 1st model.
	worldMatrix = XMMatrixIdentity();
	worldMatrix = XMMatrixScaling(0.5, 0.5, 0.5);
	translateMatrix = XMMatrixTranslation(225, 8, 225);
	worldMatrix = XMMatrixMultiply(worldMatrix, translateMatrix);

	// Render the first model using the texture shader.
	m_Model1->Render(m_Direct3D->GetDeviceContext());
	result = m_ShaderManager->RenderPointLightShader(m_Direct3D->GetDeviceContext(), m_Model1->GetIndexCount(), worldMatrix, viewMatrix, projectionMatrix,
		m_Model1->GetTexture(), diffuseColor, lightPosition);
	if (!result)
	{
		return false;
	}



	//Setup the rotation and translation of the bridge model
	worldMatrix = XMMatrixIdentity();
	worldMatrix = XMMatrixMultiply(worldMatrix, XMMatrixScaling(10, 10, 10));
	worldMatrix = XMMatrixMultiply(worldMatrix, XMMatrixRotationY(90));
	worldMatrix = XMMatrixMultiply(worldMatrix, XMMatrixTranslation(75, 5, 100));

	//Render the model using the bridge map shader
	m_Bridge->Render(m_Direct3D->GetDeviceContext());
	result = m_ShaderManager->RenderBumpMapShader(m_Direct3D->GetDeviceContext(), m_Bridge->GetIndexCount(), worldMatrix, viewMatrix, projectionMatrix,
		m_Bridge->GetColorTexture(), m_Bridge->GetNormalMapTexture(), m_DirectionalLight->GetLookAt(),
		m_DirectionalLight->GetDiffuseColor());
	if (!result)
	{
		return false;
	}

	//Setup the rotation and translation of the model
	worldMatrix = XMMatrixIdentity();
	worldMatrix = XMMatrixMultiply(worldMatrix, XMMatrixScaling(8, 8, 8));
	worldMatrix = XMMatrixMultiply(worldMatrix, XMMatrixTranslation(200, 8, 200));

	//Render the model using the relavent shader
	m_Campfire->Render(m_Direct3D->GetDeviceContext());
	result = m_ShaderManager->RenderBumpMapShader(m_Direct3D->GetDeviceContext(), m_Campfire->GetIndexCount(), worldMatrix, viewMatrix, projectionMatrix,
		m_Campfire->GetColorTexture(), m_Campfire->GetNormalMapTexture(), m_DirectionalLight->GetLookAt(),
		m_DirectionalLight->GetDiffuseColor());
	if (!result)
	{
		return false;
	}

	//Turn on alpha blending for the fire transparency
	m_Direct3D->TurnOnAlphaBlending();

	//Turn back face culling back on
	m_Direct3D->TurnOffCulling();

	//Get the world, view, and projection matrices from the camera and d3d objects
	m_Camera->GetViewMatrix(viewMatrix);
	m_Direct3D->GetProjectionMatrix(projectionMatrix);

	//Setup the rotation and translation of the model
	worldMatrix = XMMatrixIdentity();
	worldMatrix = XMMatrixMultiply(worldMatrix, XMMatrixScaling(0.12, 0.12, 0.12));
	worldMatrix = XMMatrixMultiply(worldMatrix, XMMatrixTranslation(200, 8, 200));

	//Render the square model using the fire shader
	m_FireModel->Render(m_Direct3D->GetDeviceContext());
	result = m_ShaderManager->RenderFireShader(m_Direct3D->GetDeviceContext(), m_FireModel->GetIndexCount(), worldMatrix, viewMatrix, projectionMatrix,
		m_FireModel->GetTexture1(), m_FireModel->GetTexture2(), m_FireModel->GetTexture3(), frameTime, scrollSpeeds,
		scales, distortion1, distortion2, distortion3, distortionScale, distortionBias);
	if (!result)
	{
		return false;
	}

	//Setup the rotation and translation of the model
	worldMatrix = XMMatrixIdentity();
	worldMatrix = XMMatrixMultiply(worldMatrix, XMMatrixScaling(8, 10, 4));
	worldMatrix = XMMatrixMultiply(worldMatrix, XMMatrixRotationZ(210));
	worldMatrix = XMMatrixMultiply(worldMatrix, XMMatrixTranslation(200, 30, 200));

	//Put the particle system vertex and index buffers on the graphics pipeline to prepare them for drawing
	m_ParticleSystem->Render(m_Direct3D->GetDeviceContext());
	result = m_ShaderManager->RenderParticleShader(m_Direct3D->GetDeviceContext(), m_ParticleSystem->GetIndexCount(), worldMatrix, viewMatrix, projectionMatrix,
		m_ParticleSystem->GetTexture());
	if (!result)
	{
		return false;
	}

	//Turn off alpha blending
	m_Direct3D->TurnOffAlphaBlending();

	//Turn back face culling back on
	m_Direct3D->TurnOnCulling();





	//Turn back face culling back on
	m_Direct3D->TurnOnCulling();

	//Turn off the Z buffer to begin all 2D rendering
	m_Direct3D->TurnZBufferOff();

	//Turn on the alpha blending before rendering the text
	m_Direct3D->TurnOnAlphaBlending();

	m_Direct3D->GetWorldMatrix(worldMatrix);

	//Render the text user interface elements
	result = m_Text->Render(m_Direct3D->GetDeviceContext(), m_FontShader, worldMatrix, orthoMatrix);
	if (!result)
	{
		return false;
	}

	//Turn off alpha blending after rendering the text
	m_Direct3D->TurnOffAlphaBlending();

	//Turn the Z buffer back on now that all 2D rendering has completed
	m_Direct3D->TurnZBufferOn();

	//Present the rendered scene to the screen
	m_Direct3D->EndScene();

	return true;
}


void GraphicsClass::RenderRefractionToTexture()
{
	XMFLOAT4 clipPlane;
	XMMATRIX worldMatrix, viewMatrix, projectionMatrix, translateMatrix;


	//Setup a clipping plane based on the height of the water to clip everything above it to create a refraction
	clipPlane = XMFLOAT4(0.0f, -1.0f, 0.0f, m_Water->GetWaterHeight() + 0.1f);

	//Set the render target to be the refraction render to texture
	m_RefractionTexture->SetRenderTarget(m_Direct3D->GetDeviceContext());

	//Clear the refraction render to texture
	m_RefractionTexture->ClearRenderTarget(m_Direct3D->GetDeviceContext(), 0.0f, 0.0f, 0.0f, 1.0f);

	//Generate the view matrix based on the camera's position
	m_Camera->Render();

	//Get the matrices from the camera and d3d objects
	m_Direct3D->GetWorldMatrix(worldMatrix);
	m_Camera->GetViewMatrix(viewMatrix);
	m_Direct3D->GetProjectionMatrix(projectionMatrix);

	// Setup the rotation and translation of the 1st model.
	worldMatrix = XMMatrixIdentity();
	worldMatrix = XMMatrixScaling(5.0, 7.5, 5.0);
	translateMatrix = XMMatrixTranslation(-2550.0f, 0.0f, -2550.0f);
	worldMatrix = XMMatrixMultiply(worldMatrix, translateMatrix);

	//Render the terrain using the reflection shader and the refraction clip plane to produce the refraction effect
	m_Terrain->Render(m_Direct3D->GetDeviceContext());
	m_ReflectionShader->Render(m_Direct3D->GetDeviceContext(), m_Terrain->GetIndexCount(), worldMatrix, viewMatrix, projectionMatrix,
		m_Terrain->GetColorTexture(), m_Terrain->GetNormalTexture(), m_DirectionalLight->GetDiffuseColor(), m_DirectionalLight->GetLookAt(), 2.0f,
		clipPlane);

	//Reset the render target back to the original back buffer and not the render to texture anymore
	m_Direct3D->SetBackBufferRenderTarget();

	//Reset the viewport back to the original
	m_Direct3D->ResetViewport();

	return;
}


void GraphicsClass::RenderReflectionToTexture()
{
	XMFLOAT4 clipPlane;
	XMMATRIX reflectionViewMatrix, worldMatrix, projectionMatrix, translateMatrix;
	XMFLOAT3 cameraPosition;

	//Update the rotation variable each frame
	static float rotation;
	rotation += (float)XM_PI * 0.0005f * m_Timer->GetTime();


	//Setup a clipping plane based on the height of the water to clip everything below it
	clipPlane = XMFLOAT4(0.0f, 1.0f, 0.0f, -m_Water->GetWaterHeight());

	//Set the render target to be the reflection render to texture
	m_ReflectionTexture->SetRenderTarget(m_Direct3D->GetDeviceContext());

	//Clear the reflection render to texture
	m_ReflectionTexture->ClearRenderTarget(m_Direct3D->GetDeviceContext(), 0.0f, 0.0f, 0.0f, 1.0f);

	//Use the camera to render the reflection and create a reflection view matrix
	m_Camera->RenderReflection(m_Water->GetWaterHeight());

	//Get the camera reflection view matrix instead of the normal view matrix
	m_Camera->GetReflectionViewMatrix(reflectionViewMatrix);

	//Get the world and projection matrices from the d3d object
	m_Direct3D->GetWorldMatrix(worldMatrix);
	m_Direct3D->GetProjectionMatrix(projectionMatrix);

	//Get the position of the camera
	cameraPosition = m_Camera->GetPosition();

	//Invert the Y coordinate of the camera around the water plane height for the reflected camera position
	cameraPosition.y = -cameraPosition.y + (m_Water->GetWaterHeight() * 2.0f);

	//Translate the sky dome and sky plane to be centered around the reflected camera position
	worldMatrix = XMMatrixTranslation(cameraPosition.x, cameraPosition.y, cameraPosition.z);

	//Turn off back face culling and the Z buffer
	m_Direct3D->TurnOffCulling();
	m_Direct3D->TurnZBufferOff();

	//Render the sky dome using the reflection view matrix
	m_SkyDome->Render(m_Direct3D->GetDeviceContext());
	m_SkyDomeShader->Render(m_Direct3D->GetDeviceContext(), m_SkyDome->GetIndexCount(), worldMatrix, reflectionViewMatrix, projectionMatrix,
		m_SkyDome->GetApexColor(), m_SkyDome->GetCenterColor());

	//Enable back face culling
	m_Direct3D->TurnOnCulling();

	//Enable additive blending so the clouds blend with the sky dome color
	m_Direct3D->EnableSecondBlendState();

	//Render the sky plane using the sky plane shader
	m_SkyPlane->Render(m_Direct3D->GetDeviceContext());
	m_SkyPlaneShader->Render(m_Direct3D->GetDeviceContext(), m_SkyPlane->GetIndexCount(), worldMatrix, reflectionViewMatrix, projectionMatrix,
		m_SkyPlane->GetCloudTexture(), m_SkyPlane->GetPerturbTexture(), m_SkyPlane->GetTranslation(), m_SkyPlane->GetScale(),
		m_SkyPlane->GetBrightness());

	//Turn off blending and enable the Z buffer again
	m_Direct3D->TurnOffAlphaBlending();
	m_Direct3D->TurnZBufferOn();

	// Setup the rotation and translation of the 1st model.
	worldMatrix = XMMatrixIdentity();
	worldMatrix = XMMatrixScaling(5.0, 7.5, 5.0);
	translateMatrix = XMMatrixTranslation(-2550, 0, -2550);
	worldMatrix = XMMatrixMultiply(worldMatrix, translateMatrix);

	//Render the terrain using the reflection view matrix and reflection clip plane
	m_Terrain->Render(m_Direct3D->GetDeviceContext());
	m_ReflectionShader->Render(m_Direct3D->GetDeviceContext(), m_Terrain->GetIndexCount(), worldMatrix, reflectionViewMatrix, projectionMatrix,
		m_Terrain->GetColorTexture(), m_Terrain->GetNormalTexture(), m_DirectionalLight->GetDiffuseColor(), m_DirectionalLight->GetLookAt(), 2.0f,
		clipPlane);

	//set up positioning factors
	m_Direct3D->GetWorldMatrix(worldMatrix);
	worldMatrix = XMMatrixMultiply(worldMatrix, XMMatrixScaling(10, 10, 10));
	worldMatrix = XMMatrixMultiply(worldMatrix, XMMatrixRotationY(90));
	worldMatrix = XMMatrixMultiply(worldMatrix, XMMatrixTranslation(75, 5, 100));

	//Render the model using the reflection view matrix and reflection clip plane
	m_Bridge->Render(m_Direct3D->GetDeviceContext());
	m_ShaderManager->RenderLightShader(m_Direct3D->GetDeviceContext(), m_Bridge->GetIndexCount(), worldMatrix, reflectionViewMatrix,
		projectionMatrix, m_Bridge->GetColorTexture(), m_DirectionalLight->GetLookAt(), m_DirectionalLight->GetAmbientColor(), m_DirectionalLight->GetDiffuseColor(),
		cameraPosition, m_DirectionalLight->GetSpecularColor(), m_DirectionalLight->GetSpecularPower());




	//Reset the render target back to the original back buffer and not the render to texture anymore
	m_Direct3D->SetBackBufferRenderTarget();

	//Reset the viewport back to the original
	m_Direct3D->ResetViewport();

	return;
}


bool GraphicsClass::RenderGlassRefractionToTexture()
{
	XMMATRIX worldMatrix, viewMatrix, projectionMatrix;
	bool result;



	//Reset the render target back to the original back buffer and not the render to texture anymore
	m_Direct3D->SetBackBufferRenderTarget();

	return true;
}