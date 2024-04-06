////////////////////////////////////////////////////////////////////////////////
// Filename: graphicsclass.cpp
////////////////////////////////////////////////////////////////////////////////
#include "graphicsclass.h"


GraphicsClass::GraphicsClass()
{
	m_Input = 0;
	m_D3D = 0;
	m_Timer = 0;
	m_Position = 0;
	m_Camera = 0;
	m_Light = 0;
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

	m_ParticleSystem = 0;

	m_Model1 = 0;
	m_Model2 = 0;
	m_Model3 = 0;
	m_Model4 = 0;
}


GraphicsClass::GraphicsClass(const GraphicsClass& other)
{
}


GraphicsClass::~GraphicsClass()
{
}


bool GraphicsClass::Initialize(HINSTANCE hinstance, HWND hwnd, int screenWidth, int screenHeight)
{
	// Used for debugging
	bool result;

	XMMATRIX baseViewMatrix;
	char videoCard[128];
	int videoMemory;

	//Retrieve the video card information.
	//m_D3D->GetVideoCardInfo(videoCard, videoMemory);

	// Create the input object.  The input object will be used to handle reading the keyboard and mouse input from the user.
	m_Input = new InputClass;
	if (!m_Input)
	{
		return false;
	}

	// Initialize the input object.
	result = m_Input->Initialize(hinstance, hwnd, screenWidth, screenHeight);
	if (!result)
	{
		MessageBox(hwnd, L"Could not initialize the input object.", L"Error", MB_OK);
		return false;
	}

	// Create the Direct3D object.
	m_D3D = new D3DClass;
	if(!m_D3D)
	{
		return false;
	}

	// Initialize the Direct3D object.
	result = m_D3D->Initialize(screenWidth, screenHeight, VSYNC_ENABLED, hwnd, FULL_SCREEN, SCREEN_DEPTH, SCREEN_NEAR);
	if(!result)
	{
		MessageBox(hwnd, L"Could not initialize Direct3D.", L"Error", MB_OK);
		return false;
	}

	// Create the shader manager object.
	m_ShaderManager = new ShaderManagerClass;
	if(!m_ShaderManager)
	{
		return false;
	}

	// Initialize the shader manager object.
	result = m_ShaderManager->Initialize(m_D3D->GetDevice(), hwnd);
	if(!result)
	{
		MessageBox(hwnd, L"Could not initialize the shader manager object.", L"Error", MB_OK);
		return false;
	}

	//Create the terrain shader object.
	m_TerrainShader = new TerrainShaderClass;
	if (!m_TerrainShader)
	{
		return false;
	}

	//Initialize the terrain shader object.
	result = m_TerrainShader->Initialize(m_D3D->GetDevice(), hwnd);
	if (!result)
	{
		MessageBox(hwnd, L"Could not initialize the terrain shader object.", L"Error", MB_OK);
		return false;
	}

	// Create the timer object.
	m_Timer = new TimerClass;
	if (!m_Timer)
	{
		return false;
	}

	// Initialize the timer object.
	result = m_Timer->Initialize();
	if (!result)
	{
		MessageBox(hwnd, L"Could not initialize the timer object.", L"Error", MB_OK);
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

	/*

	//Create the font shader object.
	m_FontShader = new FontShaderClass;
	if (!m_FontShader)
	{
		return false;
	}

	//Initialize the font shader object.
	result = m_FontShader->Initialize(m_D3D->GetDevice(), hwnd);
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
	result = m_Text->Initialize(m_D3D->GetDevice(), m_D3D->GetDeviceContext(), hwnd, screenWidth, screenHeight, baseViewMatrix);
	if (!result)
	{
		MessageBox(hwnd, L"Could not initialize the text object.", L"Error", MB_OK);
		return false;
	}

	//Set the video card information in the text object.
	result = m_Text->SetVideoCardInfo(videoCard, videoMemory, m_D3D->GetDeviceContext());
	if (!result)
	{
		MessageBox(hwnd, L"Could not set video card info in the text object.", L"Error", MB_OK);
		return false;
	}

	*/

	//Create the render to texture object for water refraction.
	m_RefractionTexture = new RenderTextureClass;
	if (!m_RefractionTexture)
	{
		return false;
	}

	//Initialize the refraction render to texture object.
	result = m_RefractionTexture->Initialize(m_D3D->GetDevice(), screenWidth, screenHeight, SCREEN_DEPTH, SCREEN_NEAR);
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
	result = m_ReflectionTexture->Initialize(m_D3D->GetDevice(), screenWidth, screenHeight, SCREEN_DEPTH, SCREEN_NEAR);
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
	result = m_ShadowTexture->Initialize(m_D3D->GetDevice(), SHADOWMAP_WIDTH, SHADOWMAP_HEIGHT, SCREEN_DEPTH, SCREEN_NEAR);
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
	result = m_ReflectionShader->Initialize(m_D3D->GetDevice(), hwnd);
	if (!result)
	{
		MessageBox(hwnd, L"Could not initialize the reflection shader object.", L"Error", MB_OK);
		return false;
	}

	// Create the position object.
	m_Position = new PositionClass;
	if (!m_Position)
	{
		return false;
	}

	// Set the initial position and rotation of the viewer.
	m_Position->SetPosition(0.0f, 20.0f, -40.0f);
	m_Position->SetRotation(0.0f, 0.0f, 0.0f);

	// Create the camera object.
	m_Camera = new CameraClass;
	if (!m_Camera)
	{
		return false;
	}
	
	// Create the light object.
	m_Light = new LightClass;
	if(!m_Light)
	{
		return false;
	}

	// Initialize the light object.
	m_Light->SetAmbientColor(0.15f, 0.15f, 0.15f, 1.0f);
	m_Light->SetDiffuseColor(1.0f, 1.0f, 1.0f, 1.0f);
	m_Light->SetLookAt(0.0f, 0.0f, 1.0f);
	m_Light->SetSpecularColor(1.0f, 1.0f, 1.0f, 1.0f);
	m_Light->SetSpecularPower(64.0f);

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

	//Create the terrain object.
	m_Terrain = new TerrainClass;
	if (!m_Terrain)
	{
		return false;
	}

	//Initialize the terrain object.
	result = m_Terrain->Initialize(m_D3D->GetDevice(), "../Engine/data/HM3.bmp", "../Engine/data/HMC.bmp",
		12.5f, L"../Engine/data/grass.dds", L"../Engine/data/grass_n.dds");
	if (!result)
	{
		MessageBox(hwnd, L"Could not initialize the terrain object.", L"Error", MB_OK);
		return false;
	}

	//Create the water object.
	m_Water = new WaterClass;
	if (!m_Water)
	{
		return false;
	}

	//Initialize the water object.
	result = m_Water->Initialize(m_D3D->GetDevice(), L"../Engine/data/waternormal.dds", 6.0f, 10000.0f);
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
	result = m_WaterShader->Initialize(m_D3D->GetDevice(), hwnd);
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
	result = m_SkyDome->Initialize(m_D3D->GetDevice());
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
	result = m_SkyDomeShader->Initialize(m_D3D->GetDevice(), hwnd);
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
	result = m_SkyPlane->Initialize(m_D3D->GetDevice(), L"../Engine/data/clouds1.dds", L"../Engine/data/perturb001.dds");
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
	result = m_SkyPlaneShader->Initialize(m_D3D->GetDevice(), hwnd);
	if (!result)
	{
		MessageBox(hwnd, L"Could not initialize the sky plane shader object.", L"Error", MB_OK);
		return false;
	}

	// Create the model object.
	m_Model1 = new ModelClass;
	if(!m_Model1)
	{
		return false;
	}

	// Initialize the model object.
	result = m_Model1->Initialize(m_D3D->GetDevice(), "../Engine/data/House.txt", L"../Engine/data/House-Textured.dds");
	if(!result)
	{
		MessageBox(hwnd, L"Could not initialize the first model object.", L"Error", MB_OK);
		return false;
	}

	// Create the second model object.
	m_Model2 = new ModelClass;
	if(!m_Model2)
	{
		return false;
	}

	// Initialize the second model object.
	result = m_Model2->Initialize(m_D3D->GetDevice(), "../Engine/data/Zombie.txt", L"../Engine/data/Zombie-Textured.dds");
	if(!result)
	{
		MessageBox(hwnd, L"Could not initialize the second model object.", L"Error", MB_OK);
		return false;
	}

	// Create the third bump model object for models with normal maps and related vectors.
	m_Model3 = new BumpModelClass;
	if(!m_Model3)
	{
		return false;
	}

	// Initialize the bump model object.
	result = m_Model3->Initialize(m_D3D->GetDevice(), "../Engine/data/Lamp.txt", L"../Engine/data/Lamp-Textured.dds", 
								  L"../Engine/data/normal.dds");
	if(!result)
	{
		MessageBox(hwnd, L"Could not initialize the third model object.", L"Error", MB_OK);
		return false;
	}

	// Create the 4th model object.
	m_Model4 = new ModelClass;
	if (!m_Model4)
	{
		return false;
	}

	// Initialize the 4th model object.
	result = m_Model4->Initialize(m_D3D->GetDevice(), "../Engine/data/terrain.txt", L"../Engine/data/Terrain-Textured2.dds");
	if (!result)
	{
		MessageBox(hwnd, L"Could not initialize the 4th model object.", L"Error", MB_OK);
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

	if (m_Model2)
	{
		m_Model2->Shutdown();
		delete m_Model2;
		m_Model2 = 0;
	}

	if (m_Model3)
	{
		m_Model3->Shutdown();
		delete m_Model3;
		m_Model3 = 0;
	}

	if (m_Model4)
	{
		m_Model4->Shutdown();
		delete m_Model4;
		m_Model4 = 0;
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

	//Release the render to texture object.
	if (m_ShadowTexture)
	{
		m_ShadowTexture->Shutdown();
		delete m_ShadowTexture;
		m_ShadowTexture = 0;
	}

	//Release the light object.
	if (m_DirectionalLight)
	{
		delete m_DirectionalLight;
		m_DirectionalLight = 0;
	}

	// Release the light object.
	if (m_Light)
	{
		delete m_Light;
		m_Light = 0;
	}

	// Release the camera object.
	if (m_Camera)
	{
		delete m_Camera;
		m_Camera = 0;
	}

	// Release the position object.
	if (m_Position)
	{
		delete m_Position;
		m_Position = 0;
	}

	// Release the shader manager object.
	if (m_ShaderManager)
	{
		m_ShaderManager->Shutdown();
		delete m_ShaderManager;
		m_ShaderManager = 0;
	}

	// Release the timer object.
	if (m_Timer)
	{
		delete m_Timer;
		m_Timer = 0;
	}

	// Release the D3D object.
	if (m_D3D)
	{
		m_D3D->Shutdown();
		delete m_D3D;
		m_D3D = 0;
	}

	// Release the input object.
	if (m_Input)
	{
		m_Input->Shutdown();
		delete m_Input;
		m_Input = 0;
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

	//Release the particle system object.
	if (m_ParticleSystem)
	{
		m_ParticleSystem->Shutdown();
		delete m_ParticleSystem;
		m_ParticleSystem = 0;
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

	// Read the user input.
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
	//m_ParticleSystem->Frame(m_Timer->GetTime(), m_D3D->GetDeviceContext());

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

	/*

	//Update the FPS value in the text object
	result = m_Text->SetFps(m_Fps->GetFps(), m_D3D->GetDeviceContext());
	if (!result)
	{
		return false;
	}

	//Update the CPU usage value in the text object
	result = m_Text->SetCpu(m_Cpu->GetCpuPercentage(), m_D3D->GetDeviceContext());
	if (!result)
	{
		return false;
	}

	*/

	// Check if the user pressed escape and wants to exit the application.
	if (m_Input->IsEscapePressed() == true)
	{
		return false;
	}

	// Do the frame input processing.
	result = HandleMovementInput(m_Timer->GetTime());
	if (!result)
	{
		return false;
	}

	// Render the graphics.
	result = Render();
	if (!result)
	{
		return false;
	}

	return true;
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

	// HandleMouse Rotations
	m_Position->MouseRotate(m_Input->GetMouseXDelta(), m_Input->GetMouseYDelta());

	// Get the view point position/rotation.
	m_Position->GetPosition(posX, posY, posZ);
	m_Position->GetRotation(rotX, rotY, rotZ);
	m_Input->ResetCursorPos();

	// Set the position of the camera.
	m_Camera->SetPosition(posX, posY, posZ);
	m_Camera->SetRotation(rotX, rotY, rotZ);

	/*
	
	//Update the position values in the text object
	result = m_Text->SetCameraPosition(posX, posY, posZ, m_D3D->GetDeviceContext());
	if (!result)
	{
		return false;
	}

	//Update the rotation values in the text object
	result = m_Text->SetCameraRotation(rotX, rotY, rotZ, m_D3D->GetDeviceContext());
	if (!result)
	{
		return false;
	}

	*/

	return true;
}


bool GraphicsClass::RenderShadowToTexture()
{
	XMMATRIX worldMatrix, lightViewMatrix, lightProjectionMatrix, translateMatrix;
	float posX, posY, posZ;
	bool result;


	//Set the render target to be the render to texture
	//m_ShadowTexture->SetRenderTarget(m_D3D->GetDeviceContext());

	//Clear the render to texture
	//m_ShadowTexture->ClearRenderTarget(m_D3D->GetDeviceContext(), 0.0f, 0.0f, 0.0f, 1.0f);

	//Generate the light view matrix based on the light's position
	m_DirectionalLight->GenerateViewMatrix();

	//Get the world matrix from the d3d object
	m_D3D->GetWorldMatrix(worldMatrix);

	//Get the view and orthographic matrices from the light object
	m_DirectionalLight->GetViewMatrix(lightViewMatrix);
	m_DirectionalLight->GetProjectionMatrix(lightProjectionMatrix);

	//Setup the rotation and translation of the terrain
	worldMatrix = XMMatrixIdentity();
	worldMatrix = XMMatrixScaling(5.0, 7.5, 5.0);
	translateMatrix = XMMatrixTranslation(-2550.0f, 0.0f, -2550.0f);
	worldMatrix = XMMatrixMultiply(worldMatrix, translateMatrix);

	//Render the terrain model with the depth shader
	m_Terrain->Render(m_D3D->GetDeviceContext());
	result = m_ShaderManager->RenderDepthShader(m_D3D->GetDeviceContext(), m_Terrain->GetIndexCount(), worldMatrix, lightViewMatrix, lightProjectionMatrix);
	if (!result)
	{
		return false;
	}

	/*

	//Setup the translation matrix for the cube model
	m_ShadowShowcaseCubeModel->GetPosition(posX, posY, posZ);
	worldMatrix = XMMatrixScaling(10.0f, 10.0f, 10.0f);
	worldMatrix = XMMatrixMultiply(worldMatrix, XMMatrixTranslation(posX, posY, posZ));

	//Render the cube model with the depth shader
	m_ShadowShowcaseCubeModel->Render(m_Direct3D->GetDeviceContext());
	result = m_ShaderManager->RenderDepthShader(m_Direct3D->GetDeviceContext(), m_ShadowShowcaseCubeModel->GetIndexCount(), worldMatrix, lightViewMatrix, lightProjectionMatrix);
	if (!result)
	{
		return false;
	}

	m_Direct3D->GetWorldMatrix(worldMatrix);
	worldMatrix = XMMatrixMultiply(worldMatrix, XMMatrixScaling(1, 1, 1));
	worldMatrix = XMMatrixMultiply(worldMatrix, XMMatrixRotationY(0));
	worldMatrix = XMMatrixMultiply(worldMatrix, XMMatrixTranslation(15, -15, 15));
	m_Dungeon->Render(m_Direct3D->GetDeviceContext());

	result = m_ShaderManager->RenderDepthShader(m_Direct3D->GetDeviceContext(), m_Dungeon->GetIndexCount(), worldMatrix, lightViewMatrix, lightProjectionMatrix);
	if (!result)
	{
		return false;
	}

	//Reset the world matrix
	m_Direct3D->GetWorldMatrix(worldMatrix);

	//Setup the translation matrix for the sphere model
	m_ShadowShowcaseSphereModel->GetPosition(posX, posY, posZ);
	worldMatrix = XMMatrixTranslation(posX, posY, posZ);

	//Render the sphere model with the depth shader
	m_ShadowShowcaseSphereModel->Render(m_Direct3D->GetDeviceContext());
	result = m_ShaderManager->RenderDepthShader(m_Direct3D->GetDeviceContext(), m_ShadowShowcaseSphereModel->GetIndexCount(), worldMatrix, lightViewMatrix, lightProjectionMatrix);
	if (!result)
	{
		return false;
	}

	//Reset the world matrix
	m_Direct3D->GetWorldMatrix(worldMatrix);

	//Setup the translation matrix for the ground model
	m_ShadowShowcaseGroundModel->GetPosition(posX, posY, posZ);
	worldMatrix = XMMatrixScaling(7.0f, 1.0f, 1.0f);
	worldMatrix = XMMatrixMultiply(worldMatrix, XMMatrixTranslation(posX, posY, posZ));

	//Render the ground model with the depth shader
	m_ShadowShowcaseGroundModel->Render(m_Direct3D->GetDeviceContext());
	result = m_ShaderManager->RenderDepthShader(m_Direct3D->GetDeviceContext(), m_ShadowShowcaseGroundModel->GetIndexCount(), worldMatrix, lightViewMatrix, lightProjectionMatrix);
	if (!result)
	{
		return false;
	}

	*/

	//Reset the render target back to the original back buffer and not the render to texture anymore
	//m_D3D->SetBackBufferRenderTarget();

	//Reset the viewport back to the original
	m_D3D->ResetViewport();

	return true;
}


bool GraphicsClass::Render()
{
	XMMATRIX worldMatrix, viewMatrix, projectionMatrix, orthoMatrix, baseViewMatrix, reflectionViewMatrix, translateMatrix, lightViewMatrix, lightProjectionMatrix;
	XMFLOAT4 diffuseColor[4];
	XMFLOAT4 lightPosition[4];
	bool result;
	XMFLOAT3 cameraPosition;

	// Variables for the fire 
	XMFLOAT3 scrollSpeeds, scales;
	XMFLOAT2 distortion1, distortion2, distortion3;
	float distortionScale, distortionBias;
	static float frameTime = 0.0f;

	// Glass variables
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

	/*

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

	*/

	// Clear the buffers to begin the scene.
	m_D3D->BeginScene(0.0f, 0.0f, 0.0f, 1.0f);

	//Generate the view matrix based on the camera's position
	m_Camera->Render();

	//Generate the reflection matrix based on the camera's position and the height of the water
	m_Camera->RenderReflection(m_Water->GetWaterHeight());

	//Get the world, view, projection, ortho, and base view matrices from the camera and Direct3D objects
	m_D3D->GetWorldMatrix(worldMatrix);
	m_Camera->GetViewMatrix(viewMatrix);
	m_D3D->GetProjectionMatrix(projectionMatrix);
	m_D3D->GetOrthoMatrix(orthoMatrix);
	m_Camera->GetReflectionViewMatrix(reflectionViewMatrix);

	//Get the position of the camera
	cameraPosition = m_Camera->GetPosition();

	//Translate the sky dome to be centered around the camera position
	worldMatrix = XMMatrixTranslation(cameraPosition.x, cameraPosition.y, cameraPosition.z);

	//Turn off back face culling and the Z buffer
	m_D3D->TurnOffCulling();
	m_D3D->TurnZBufferOff();

	//Setup the scaling of the sky dome
	worldMatrix = XMMatrixScaling(500.0, 750.0, 500.0);

	//Render the sky dome using the sky dome shader
	m_SkyDome->Render(m_D3D->GetDeviceContext());
	m_SkyDomeShader->Render(m_D3D->GetDeviceContext(), m_SkyDome->GetIndexCount(), worldMatrix, viewMatrix, projectionMatrix,
		m_SkyDome->GetApexColor(), m_SkyDome->GetCenterColor());

	//Turn back face culling back on
	m_D3D->TurnOnCulling();

	//Enable additive blending so the clouds blend with the sky dome color
	m_D3D->EnableSecondBlendState();

	//Render the sky plane using the sky plane shader
	m_SkyPlane->Render(m_D3D->GetDeviceContext());
	m_SkyPlaneShader->Render(m_D3D->GetDeviceContext(), m_SkyPlane->GetIndexCount(), worldMatrix, viewMatrix, projectionMatrix,
		m_SkyPlane->GetCloudTexture(), m_SkyPlane->GetPerturbTexture(), m_SkyPlane->GetTranslation(), m_SkyPlane->GetScale(),
		m_SkyPlane->GetBrightness());

	//Turn off blending
	m_D3D->TurnOffAlphaBlending();

	//Turn the Z buffer back on
	m_D3D->TurnZBufferOn();

	//Translate to the location of the water and render it
	worldMatrix = XMMatrixTranslation(0.0f, m_Water->GetWaterHeight(), 0.0f);

	m_Water->Render(m_D3D->GetDeviceContext());
	m_WaterShader->Render(m_D3D->GetDeviceContext(), m_Water->GetIndexCount(), worldMatrix, viewMatrix, projectionMatrix, reflectionViewMatrix,
		m_RefractionTexture->GetShaderResourceView(), m_ReflectionTexture->GetShaderResourceView(), m_Water->GetTexture(),
		m_Camera->GetPosition(), m_Water->GetNormalMapTiling(), m_Water->GetWaterTranslation(), m_Water->GetReflectRefractScale(),
		m_Water->GetRefractionTint(), m_DirectionalLight->GetLookAt(), m_Water->GetSpecularShininess());


	//Generate the light view matrix based on the light's position
	m_DirectionalLight->GenerateViewMatrix();

	//Get the world, view, and projection matrices from the camera and d3d objects
	m_Camera->GetViewMatrix(viewMatrix);
	m_D3D->GetWorldMatrix(worldMatrix);
	m_D3D->GetProjectionMatrix(projectionMatrix);

	//Get the light's view and projection matrices from the light object
	m_DirectionalLight->GetViewMatrix(lightViewMatrix);
	m_DirectionalLight->GetProjectionMatrix(lightProjectionMatrix);


	// Setup the rotation and translation of the 1st model.
	worldMatrix = XMMatrixIdentity();
	worldMatrix = XMMatrixScaling(5.0, 7.5, 5.0);
	translateMatrix = XMMatrixTranslation(-2550.0f, 0.0f, -2550.0f);
	worldMatrix = XMMatrixMultiply(worldMatrix, translateMatrix);

	//Render the terrain using the terrain shader
	m_Terrain->Render(m_D3D->GetDeviceContext());
	result = m_TerrainShader->Render(m_D3D->GetDeviceContext(), m_Terrain->GetIndexCount(), worldMatrix, viewMatrix,
		projectionMatrix, m_Terrain->GetColorTexture(), m_Terrain->GetNormalTexture(), m_DirectionalLight->GetDiffuseColor(),
		m_DirectionalLight->GetLookAt(), 2.5f);
	if (!result)
	{
		return false;
	}


	// Setup the rotation and translation of the 1st model.
	worldMatrix = XMMatrixIdentity();
	worldMatrix = XMMatrixScaling(2.5f, 2.5f, 2.5f);
	translateMatrix = XMMatrixTranslation(-100.0f, 7.5f, 100.0f);
	worldMatrix = XMMatrixMultiply(worldMatrix, translateMatrix);

	// Render the first model using the texture shader.
	m_Model1->Render(m_D3D->GetDeviceContext());
	result = m_ShaderManager->RenderLightShader(m_D3D->GetDeviceContext(), m_Model2->GetIndexCount(), worldMatrix, viewMatrix, projectionMatrix,
		m_Model1->GetTexture(), m_DirectionalLight->GetLookAt(), m_DirectionalLight->GetAmbientColor(), m_DirectionalLight->GetDiffuseColor(),
		m_Camera->GetPosition(), m_DirectionalLight->GetSpecularColor(), m_DirectionalLight->GetSpecularPower());
	if(!result)
	{
		return false;
	}


	// Setup the rotation and translation of the 2nd model.
	worldMatrix = XMMatrixIdentity();
	worldMatrix = XMMatrixScaling(0.25f, 0.25f, 0.25f);
	translateMatrix = XMMatrixTranslation(-100.0f, 7.5f, 0.0f);
	worldMatrix = XMMatrixMultiply(worldMatrix, translateMatrix);

	// Render the second model using the light shader.
	m_Model2->Render(m_D3D->GetDeviceContext());
	result = m_ShaderManager->RenderLightShader(m_D3D->GetDeviceContext(), m_Model2->GetIndexCount(), worldMatrix, viewMatrix, projectionMatrix,
		m_Model2->GetTexture(), m_DirectionalLight->GetLookAt(), m_DirectionalLight->GetAmbientColor(), m_DirectionalLight->GetDiffuseColor(),
		m_Camera->GetPosition(), m_DirectionalLight->GetSpecularColor(), m_DirectionalLight->GetSpecularPower());
	if(!result)
	{
		return false;
	}

	// Setup the rotation and translation of the 3rd model.
	worldMatrix = XMMatrixIdentity();
	worldMatrix = XMMatrixScaling(0.25f, 0.25f, 0.25f);
	translateMatrix = XMMatrixTranslation(-10.0f, 7.5f, 0.0f);
	worldMatrix = XMMatrixMultiply(worldMatrix, translateMatrix);

	// Render the third model using the bump map shader.
	m_Model3->Render(m_D3D->GetDeviceContext());
	result = m_ShaderManager->RenderBumpMapShader(m_D3D->GetDeviceContext(), m_Model3->GetIndexCount(), worldMatrix, viewMatrix, projectionMatrix,
		m_Model3->GetColorTexture(), m_Model3->GetNormalMapTexture(), m_DirectionalLight->GetLookAt(),
		m_DirectionalLight->GetDiffuseColor());
	if(!result)
	{
		return false;
	}

	// Setup the rotation and translation of the 4th model.
	worldMatrix = XMMatrixIdentity();
	worldMatrix = XMMatrixScaling(1.0f, 1.0f, 1.0f); //(20.0f, 20.0f, 20.0f);
	translateMatrix = XMMatrixTranslation(0.0f, 0.0f, 0.0f);
	worldMatrix = XMMatrixMultiply(worldMatrix, translateMatrix);

	// Render the first model using the texture shader.
	m_Model4->Render(m_D3D->GetDeviceContext());
	result = m_ShaderManager->RenderTextureShader(m_D3D->GetDeviceContext(), m_Model4->GetIndexCount(), worldMatrix, viewMatrix, projectionMatrix,
		m_Model4->GetTexture());
	if (!result)
	{
		return false;
	}
	

	// Present the rendered scene to the screen.
	m_D3D->EndScene();

	return true;
}


void GraphicsClass::RenderRefractionToTexture()
{
	XMFLOAT4 clipPlane;
	XMMATRIX worldMatrix, viewMatrix, projectionMatrix, translateMatrix;


	//Setup a clipping plane based on the height of the water to clip everything above it to create a refraction
	clipPlane = XMFLOAT4(0.0f, -1.0f, 0.0f, m_Water->GetWaterHeight() + 0.1f);

	//Set the render target to be the refraction render to texture
	m_RefractionTexture->SetRenderTarget(m_D3D->GetDeviceContext());

	//Clear the refraction render to m_D3D
	m_RefractionTexture->ClearRenderTarget(m_D3D->GetDeviceContext(), 0.0f, 0.0f, 0.0f, 1.0f);

	//Generate the view matrix based on the camera's position
	m_Camera->Render();

	//Get the matrices from the camera and d3d objects
	m_D3D->GetWorldMatrix(worldMatrix);
	m_Camera->GetViewMatrix(viewMatrix);
	m_D3D->GetProjectionMatrix(projectionMatrix);

	// Setup the rotation and translation of the 1st model.
	worldMatrix = XMMatrixIdentity();
	worldMatrix = XMMatrixScaling(5.0, 7.5, 5.0);
	translateMatrix = XMMatrixTranslation(-2550.0f, 0.0f, -2550.0f);
	worldMatrix = XMMatrixMultiply(worldMatrix, translateMatrix);

	//Render the terrain using the reflection shader and the refraction clip plane to produce the refraction effect
	m_Terrain->Render(m_D3D->GetDeviceContext());
	m_ReflectionShader->Render(m_D3D->GetDeviceContext(), m_Terrain->GetIndexCount(), worldMatrix, viewMatrix, projectionMatrix,
		m_Terrain->GetColorTexture(), m_Terrain->GetNormalTexture(), m_DirectionalLight->GetDiffuseColor(), m_DirectionalLight->GetLookAt(), 2.0f,
		clipPlane);

	//Reset the render target back to the original back buffer and not the render to texture anymore
	m_D3D->SetBackBufferRenderTarget();

	//Reset the viewport back to the original
	m_D3D->ResetViewport();

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
	m_ReflectionTexture->SetRenderTarget(m_D3D->GetDeviceContext());

	//Clear the reflection render to texture
	m_ReflectionTexture->ClearRenderTarget(m_D3D->GetDeviceContext(), 0.0f, 0.0f, 0.0f, 1.0f);

	//Use the camera to render the reflection and create a reflection view matrix
	m_Camera->RenderReflection(m_Water->GetWaterHeight());

	//Get the camera reflection view matrix instead of the normal view matrix
	m_Camera->GetReflectionViewMatrix(reflectionViewMatrix);

	//Get the world and projection matrices from the d3d object
	m_D3D->GetWorldMatrix(worldMatrix);
	m_D3D->GetProjectionMatrix(projectionMatrix);

	//Get the position of the camera
	cameraPosition = m_Camera->GetPosition();

	//Invert the Y coordinate of the camera around the water plane height for the reflected camera position
	cameraPosition.y = -cameraPosition.y + (m_Water->GetWaterHeight() * 2.0f);

	//Translate the sky dome and sky plane to be centered around the reflected camera position
	worldMatrix = XMMatrixTranslation(cameraPosition.x, cameraPosition.y, cameraPosition.z);

	//Turn off back face culling and the Z buffer
	m_D3D->TurnOffCulling();
	m_D3D->TurnZBufferOff();

	//Setup the scaling of the sky dome
	worldMatrix = XMMatrixScaling(500.0, 750.0, 500.0);

	//Render the sky dome using the reflection view matrix
	m_SkyDome->Render(m_D3D->GetDeviceContext());
	m_SkyDomeShader->Render(m_D3D->GetDeviceContext(), m_SkyDome->GetIndexCount(), worldMatrix, reflectionViewMatrix, projectionMatrix,
		m_SkyDome->GetApexColor(), m_SkyDome->GetCenterColor());

	//Enable back face culling
	m_D3D->TurnOnCulling();

	//Enable additive blending so the clouds blend with the sky dome color
	m_D3D->EnableSecondBlendState();

	//Render the sky plane using the sky plane shader
	m_SkyPlane->Render(m_D3D->GetDeviceContext());
	m_SkyPlaneShader->Render(m_D3D->GetDeviceContext(), m_SkyPlane->GetIndexCount(), worldMatrix, reflectionViewMatrix, projectionMatrix,
		m_SkyPlane->GetCloudTexture(), m_SkyPlane->GetPerturbTexture(), m_SkyPlane->GetTranslation(), m_SkyPlane->GetScale(),
		m_SkyPlane->GetBrightness());

	//Turn off blending and enable the Z buffer again
	m_D3D->TurnOffAlphaBlending();
	m_D3D->TurnZBufferOn();

	//Reset the world matrix
	m_D3D->GetWorldMatrix(worldMatrix);

	//Render the terrain using the reflection view matrix and reflection clip plane
	m_Terrain->Render(m_D3D->GetDeviceContext());
	m_ReflectionShader->Render(m_D3D->GetDeviceContext(), m_Terrain->GetIndexCount(), worldMatrix, reflectionViewMatrix, projectionMatrix,
		m_Terrain->GetColorTexture(), m_Terrain->GetNormalTexture(), m_DirectionalLight->GetDiffuseColor(), m_DirectionalLight->GetLookAt(), 2.0f,
		clipPlane);

	// Setup the rotation and translation of the 1st model.
	worldMatrix = XMMatrixIdentity();
	worldMatrix = XMMatrixScaling(2.5f, 2.5f, 2.5f);
	translateMatrix = XMMatrixTranslation(0.0f, 0.0f, 100.0f);
	worldMatrix = XMMatrixMultiply(worldMatrix, translateMatrix);

	// Render the first model using the texture shader.
	m_Model1->Render(m_D3D->GetDeviceContext());
	m_ShaderManager->RenderLightShader(m_D3D->GetDeviceContext(), m_Model2->GetIndexCount(), worldMatrix, reflectionViewMatrix, projectionMatrix,
		m_Model1->GetTexture(), m_DirectionalLight->GetLookAt(), m_DirectionalLight->GetAmbientColor(), m_DirectionalLight->GetDiffuseColor(),
		m_Camera->GetPosition(), m_DirectionalLight->GetSpecularColor(), m_DirectionalLight->GetSpecularPower());


	/*

	//set up positioning factors
	m_D3D->GetWorldMatrix(worldMatrix);
	worldMatrix = XMMatrixMultiply(worldMatrix, XMMatrixScaling(0.3f, 0.5f, 0.3f));
	worldMatrix = XMMatrixMultiply(worldMatrix, XMMatrixRotationY(0.0f));
	worldMatrix = XMMatrixMultiply(worldMatrix, XMMatrixTranslation(255, 19.25, 235));

	//Render the model using the reflection view matrix and reflection clip plane
	m_Castle->Render(m_Direct3D->GetDeviceContext());
	m_ShaderManager->RenderLightShader(m_Direct3D->GetDeviceContext(), m_Castle->GetIndexCount(), worldMatrix, reflectionViewMatrix,
		projectionMatrix, m_Castle->GetTexture(), m_DirectionalLight->GetLookAt(), m_DirectionalLight->GetAmbientColor(), m_DirectionalLight->GetDiffuseColor(),
		cameraPosition, m_DirectionalLight->GetSpecularColor(), m_DirectionalLight->GetSpecularPower());

	//set up positioning factors
	m_D3D->GetWorldMatrix(worldMatrix);
	worldMatrix = XMMatrixMultiply(worldMatrix, XMMatrixScaling(4.0f, 4.0f, 4.0f));
	worldMatrix = XMMatrixMultiply(worldMatrix, XMMatrixRotationY(XM_PIDIV2));
	translateMatrix = XMMatrixTranslation(65.0f, 0.0f, 0.0f);
	worldMatrix = XMMatrixMultiply(worldMatrix, translateMatrix);

	//set up rotation factors
	XMVECTOR MyAxis;
	MyAxis = XMVectorSet(0.0f, 1.0f, 0.0f, 0.0f);
	worldMatrix = XMMatrixMultiply(worldMatrix, XMMatrixRotationAxis(MyAxis, rotation * 0.1f));
	translateMatrix = XMMatrixTranslation(255.0f, 3.6f, 255.0f);
	worldMatrix = XMMatrixMultiply(worldMatrix, translateMatrix);

	//Render the model using the reflection view matrix and reflection clip plane
	m_Boat->Render(m_Direct3D->GetDeviceContext());
	m_ReflectionShader->Render(m_Direct3D->GetDeviceContext(), m_Boat->GetIndexCount(), worldMatrix, reflectionViewMatrix, projectionMatrix,
		m_Boat->GetColorTexture(), m_Boat->GetNormalMapTexture(), m_DirectionalLight->GetDiffuseColor(), m_DirectionalLight->GetLookAt(), 2.0f,
		clipPlane);

	//set up positioning factors
	m_Direct3D->GetWorldMatrix(worldMatrix);
	worldMatrix = XMMatrixMultiply(worldMatrix, XMMatrixScaling(0.03f, 0.03f, 0.03f));
	worldMatrix = XMMatrixMultiply(worldMatrix, XMMatrixTranslation(320.0f, 15.0f, 300.0f));

	//Render the model using the reflection view matrix and reflection clip plane
	m_MultiTextureModel->Render(m_Direct3D->GetDeviceContext());
	m_ShaderManager->RenderLightShader(m_Direct3D->GetDeviceContext(), m_MultiTextureModel->GetIndexCount(), worldMatrix, reflectionViewMatrix,
		projectionMatrix, m_MultiTextureModel->GetTextureArray()[0], m_DirectionalLight->GetLookAt(), m_DirectionalLight->GetAmbientColor(), m_DirectionalLight->GetDiffuseColor(),
		cameraPosition, m_DirectionalLight->GetSpecularColor(), m_DirectionalLight->GetSpecularPower());

	//set up positioning factors
	m_Direct3D->GetWorldMatrix(worldMatrix);
	worldMatrix = XMMatrixMultiply(worldMatrix, XMMatrixScaling(37.0f, 34.0f, 37.0f));
	worldMatrix = XMMatrixMultiply(worldMatrix, XMMatrixTranslation(256.0f, -21.0f, 256.0f));

	//Render the model using the reflection view matrix and reflection clip plane
	m_BumpModel->Render(m_Direct3D->GetDeviceContext());
	m_ShaderManager->RenderLightShader(m_Direct3D->GetDeviceContext(), m_BumpModel->GetIndexCount(), worldMatrix, reflectionViewMatrix,
		projectionMatrix, m_BumpModel->GetColorTexture(), m_DirectionalLight->GetLookAt(), m_DirectionalLight->GetAmbientColor(), m_DirectionalLight->GetDiffuseColor(),
		cameraPosition, m_DirectionalLight->GetSpecularColor(), m_DirectionalLight->GetSpecularPower());

	//set up positioning factors
	worldMatrix = XMMatrixTranslation(340, 15, 300);

	//Render the model using the reflection view matrix and reflection clip plane
	m_LightMapModel->Render(m_Direct3D->GetDeviceContext());
	m_ShaderManager->RenderLightShader(m_Direct3D->GetDeviceContext(), m_LightMapModel->GetIndexCount(), worldMatrix, reflectionViewMatrix,
		projectionMatrix, m_LightMapModel->GetTextureArray()[1], m_DirectionalLight->GetLookAt(), m_DirectionalLight->GetAmbientColor(), m_DirectionalLight->GetDiffuseColor(),
		cameraPosition, m_DirectionalLight->GetSpecularColor(), m_DirectionalLight->GetSpecularPower());

	m_D3D->TurnOffCulling();

	//set up positioning factors
	m_Direct3D->GetWorldMatrix(worldMatrix);
	worldMatrix = XMMatrixMultiply(worldMatrix, XMMatrixScaling(0.27f, 0.27f, 0.27f));
	worldMatrix = XMMatrixMultiply(worldMatrix, XMMatrixRotationX(-0.15f));
	worldMatrix = XMMatrixMultiply(worldMatrix, XMMatrixTranslation(260, 5, 167));


	//Render the model using the reflection view matrix and reflection clip plane
	m_Bridge->Render(m_Direct3D->GetDeviceContext());
	m_ShaderManager->RenderLightShader(m_Direct3D->GetDeviceContext(), m_Bridge->GetIndexCount(), worldMatrix, reflectionViewMatrix,
		projectionMatrix, m_Bridge->GetTextureArray()[1], m_DirectionalLight->GetLookAt(), m_DirectionalLight->GetAmbientColor(), m_DirectionalLight->GetDiffuseColor(),
		cameraPosition, m_DirectionalLight->GetSpecularColor(), m_DirectionalLight->GetSpecularPower());

	//set up positioning factors
	m_Direct3D->GetWorldMatrix(worldMatrix);
	worldMatrix = XMMatrixMultiply(worldMatrix, XMMatrixScaling(0.27f, 0.27f, 0.27f));
	worldMatrix = XMMatrixMultiply(worldMatrix, XMMatrixRotationX(-0.15f));
	worldMatrix = XMMatrixMultiply(worldMatrix, XMMatrixTranslation(260.0f, 9.5f, 199.0f));

	//Render the bridge model
	m_ShaderManager->RenderLightShader(m_Direct3D->GetDeviceContext(), m_Bridge->GetIndexCount(), worldMatrix, reflectionViewMatrix,
		projectionMatrix, m_Bridge->GetTextureArray()[1], m_DirectionalLight->GetLookAt(), m_DirectionalLight->GetAmbientColor(), m_DirectionalLight->GetDiffuseColor(),
		cameraPosition, m_DirectionalLight->GetSpecularColor(), m_DirectionalLight->GetSpecularPower());

	m_D3D->TurnOnCulling();

	*/

	//Reset the render target back to the original back buffer and not the render to texture anymore
	m_D3D->SetBackBufferRenderTarget();

	//Reset the viewport back to the original
	m_D3D->ResetViewport();

	return;
}


bool GraphicsClass::RenderGlassRefractionToTexture()
{
	XMMATRIX worldMatrix, viewMatrix, projectionMatrix;
	bool result;

	/*

	//Set the render target to be the render to texture
	m_GlassRenderTexture->SetRenderTarget(m_D3D->GetDeviceContext());

	//Clear the render to texture
	m_GlassRenderTexture->ClearRenderTarget(m_D3D->GetDeviceContext(), 0.0f, 0.0f, 0.0f, 1.0f);

	//Generate the view matrix based on the camera's position
	m_Camera->Render();

	//Get the world, view, and projection matrices from the camera and d3d objects
	m_D3D->GetWorldMatrix(worldMatrix);
	m_Camera->GetViewMatrix(viewMatrix);
	m_D3D->GetProjectionMatrix(projectionMatrix);

	worldMatrix = XMMatrixTranslation(0, -30, 0);

	//Put the cube model vertex and index buffers on the graphics pipeline to prepare them for drawing
	m_GlassIceShowcaseModel->Render(m_D3D->GetDeviceContext());

	//Render the cube model using the texture shader
	result = m_ShaderManager->RenderTextureShader(m_D3D->GetDeviceContext(), m_GlassIceShowcaseModel->GetIndexCount(), worldMatrix, viewMatrix, projectionMatrix, m_GlassIceShowcaseModel->GetColorTexture());
	if (!result)
	{
		return false;
	}

	*/

	//Reset the render target back to the original back buffer and not the render to texture anymore
	m_D3D->SetBackBufferRenderTarget();

	return true;
}