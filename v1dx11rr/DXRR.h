#ifndef _dxrr
#define _dxrr
#include <d3d11.h>
#include <d3dx11.h>
#include <d3dx10.h>
#include <d3dx10math.h>
#include "TerrenoRR.h"
#include "Camara.h"
#include "SkyDome.h"
#include "Billboard.h"
#include "ModeloRR.h"
#include "XACT3Util.h"
#include "GUI.h"
#include "Text.h"
#include <stdio.h>
#include <stdlib.h>
#include <sstream>

class DXRR{	

private:
	int ancho;
	int alto;
public:	
	HINSTANCE hInstance;
	HWND hWnd;

	D3D_DRIVER_TYPE driverType;
	D3D_FEATURE_LEVEL featureLevel;

	ID3D11Device* d3dDevice;
	ID3D11DeviceContext* d3dContext;
	IDXGISwapChain* swapChain;
	ID3D11RenderTargetView* backBufferTarget;

	ID3D11Texture2D* depthTexture;
	ID3D11DepthStencilView* depthStencilView;

	ID3D11DepthStencilState* depthStencilState;
	ID3D11DepthStencilState* depthStencilDisabledState;

	ID3D11BlendState *alphaBlendState, *commonBlendState;

	int frameBillboard;
	bool colisionorilla = true;
	float rotCam;

	TerrenoRR *terreno;
	SkyDome *skydome;
	BillboardRR *billboard;
	BillboardRR* arbol;
	Camara *camara;
	ModeloRR* colisionterreno;
	ModeloRR* model;
	ModeloRR* gema1;
	ModeloRR* gema2;
	ModeloRR* gema3;
	ModeloRR* gema4;
	ModeloRR* gema5;

	BillboardRR* vaca;
	BillboardRR* cerdo;
	BillboardRR* roca1;
	BillboardRR* roca2;
	BillboardRR* roca3;
	BillboardRR* arbol1;
	BillboardRR* arbol2;
	BillboardRR* arbol3;
	BillboardRR* arbol4;
	BillboardRR* arbol5;
	BillboardRR* arbol6;
	BillboardRR* arbol7;
	BillboardRR* arbol8;
	BillboardRR* arbol9;
	BillboardRR* arbol10;
	BillboardRR* otroaarbol;
	BillboardRR* otroaarbol2;
	BillboardRR* otroaarbol3;
	BillboardRR* otroaarbol4;
	BillboardRR* otroaarbol5;
	BillboardRR* montaña1;
	BillboardRR* montaña2;
	BillboardRR* montaña3;
	BillboardRR* montaña4;
	BillboardRR* pino1;
	BillboardRR* pino2;
	BillboardRR* pino3;
	BillboardRR* pino4;
	///resto de modelos/////
	ModeloRR* silo;
	ModeloRR* madera;
	ModeloRR* molino;
	ModeloRR* casa;
	ModeloRR* casa2;
	ModeloRR* granero;
	ModeloRR* torremadera;
	ModeloRR* zanahoria1;
	ModeloRR* zanahoria2;
	ModeloRR* zanahoria3;
	ModeloRR* zanahoria4;
	ModeloRR* zanahoria5;
	ModeloRR* zanahoria6;
	ModeloRR* zanahoria7;
	ModeloRR* caballo;



	//GUI
	GUI* vida;

	//Texto
	Text* tiempo;
	Text* zanahoriasText;
	Text* victoriaText;
	Text* derrotaText;

	//Globales
	float segundos;
	float rotGem;
	float floatGem;
	bool subir;
	
	float izqder;
	float arriaba;
	float vel;
	float velRightLeft;
	bool breakpoint;
	vector2 uv1[32];
	vector2 uv2[32];
	vector2 uv3[32];
	vector2 uv4[32];

	XACTINDEX cueIndex;
	CXACT3Util m_XACT3;

	bool effectDone;
	int zanahorias;

	//COLISIONES
	bool Csilobool = true;
	bool Cmaderabool = true;
	bool Cmolinobool = true;
	bool Ccasabool = true;
	bool Ccasa2bool = true;
	bool Cgranerobool = true;
	bool Ctorremaderabool = true;

	bool zanahoria1bool = true;
	bool zanahoria2bool = true;
	bool zanahoria3bool = true;
	bool zanahoria4bool = true;
	bool zanahoria5bool = true;
	bool zanahoria6bool = true;
	bool zanahoria7bool = true;
	
    DXRR(HWND hWnd, int Ancho, int Alto)
	{
		zanahorias = 7;
		segundos = 121;
		rotGem = 0.0f;
		floatGem = 0.0f;
		subir = true;
		effectDone = false;
		breakpoint = false;
		frameBillboard = 0;
		ancho = Ancho;
		alto = Alto;
		driverType = D3D_DRIVER_TYPE_NULL;
		featureLevel = D3D_FEATURE_LEVEL_11_0;
		d3dDevice = 0;
		d3dContext = 0;
		swapChain = 0;
		backBufferTarget = 0;
		IniciaD3D(hWnd);
		izqder = 0;
		arriaba = 0;
		billCargaFuego();
		rotCam = 0.0;
		camara = new Camara(D3DXVECTOR3(0,80,6), D3DXVECTOR3(0,80,0), D3DXVECTOR3(0,1,0), Ancho, Alto);
		terreno = new TerrenoRR(300, 300, d3dDevice, d3dContext);
		skydome = new SkyDome(32, 32, 100.0f, &d3dDevice, &d3dContext, L"SkyDome.png");

		billboard = new BillboardRR(L"Assets/Billboards/fuego-anim.png",L"Assets/Billboards/fuego-anim-normal.png", d3dDevice, d3dContext, 5);
		arbol = new BillboardRR(L"Assets/Billboards/tree.png", L"Assets/Billboards/tree_normal.png", d3dDevice, d3dContext, 1);

		vaca = new BillboardRR(L"Assets/vaca.png", L"Assets/vaca.png", d3dDevice, d3dContext, 5);
		cerdo = new BillboardRR(L"Assets/cerdo.png", L"Assets/cerdo.png", d3dDevice, d3dContext, 3);
		roca1 = new BillboardRR(L"Assets/roca.png", L"Assets/roca.png", d3dDevice, d3dContext, 10);
		roca2 = new BillboardRR(L"Assets/roca2.png", L"Assets/roca2.png", d3dDevice, d3dContext, 15);
		roca3 = new BillboardRR(L"Assets/roca3.png", L"Assets/roca3.png", d3dDevice, d3dContext, 15);
		arbol1 = new BillboardRR(L"Assets/arbol.png", L"Assets/arbol.png", d3dDevice, d3dContext, 50);
		arbol2 = new BillboardRR(L"Assets/arbol.png", L"Assets/arbol.png", d3dDevice, d3dContext, 52);
		arbol3 = new BillboardRR(L"Assets/arbol.png", L"Assets/arbol.png", d3dDevice, d3dContext, 20);
		arbol4 = new BillboardRR(L"Assets/arbol.png", L"Assets/arbol.png", d3dDevice, d3dContext, 19);
		arbol5 = new BillboardRR(L"Assets/arbol.png", L"Assets/arbol.png", d3dDevice, d3dContext, 17);
		arbol6 = new BillboardRR(L"Assets/arbol.png", L"Assets/arbol.png", d3dDevice, d3dContext, 20);
		arbol7 = new BillboardRR(L"Assets/arbol.png", L"Assets/arbol.png", d3dDevice, d3dContext, 21);
		arbol8 = new BillboardRR(L"Assets/arbol.png", L"Assets/arbol.png", d3dDevice, d3dContext, 22);
		arbol9 = new BillboardRR(L"Assets/arbol.png", L"Assets/arbol.png", d3dDevice, d3dContext, 20);
		arbol10 = new BillboardRR(L"Assets/arbol.png", L"Assets/arbol.png", d3dDevice, d3dContext, 24);
		otroaarbol = new BillboardRR(L"Assets/arbol2.png", L"Assets/arbol2.png", d3dDevice, d3dContext, 50);
		otroaarbol2 = new BillboardRR(L"Assets/arbol2.png", L"Assets/arbol2.png", d3dDevice, d3dContext, 52);
		otroaarbol3 = new BillboardRR(L"Assets/arbol2.png", L"Assets/arbol2.png", d3dDevice, d3dContext, 20);
		otroaarbol4 = new BillboardRR(L"Assets/arbol2.png", L"Assets/arbol2.png", d3dDevice, d3dContext, 19);
		otroaarbol5 = new BillboardRR(L"Assets/arbol2.png", L"Assets/arbol2.png", d3dDevice, d3dContext, 17);
		montaña1 = new BillboardRR(L"Assets/mountain7.png", L"Assets/mountain7.png", d3dDevice, d3dContext, 17);
		montaña2 = new BillboardRR(L"Assets/mountain7.png", L"Assets/mountain7.png", d3dDevice, d3dContext, 17);
		montaña3 = new BillboardRR(L"Assets/mountain7.png", L"Assets/mountain7.png", d3dDevice, d3dContext, 17);
		montaña4 = new BillboardRR(L"Assets/mountain7.png", L"Assets/mountain7.png", d3dDevice, d3dContext, 17);
		pino1 = new BillboardRR(L"Assets/pino.png", L"Assets/pino.png", d3dDevice, d3dContext, 17);
		pino2 = new BillboardRR(L"Assets/pino.png", L"Assets/pino.png", d3dDevice, d3dContext, 17);
		pino3 = new BillboardRR(L"Assets/pino.png", L"Assets/pino.png", d3dDevice, d3dContext, 17);
		pino4 = new BillboardRR(L"Assets/pino.png", L"Assets/pino.png", d3dDevice, d3dContext, 17);
		

		//MODELOS
		model = new ModeloRR(d3dDevice, d3dContext, "Assets/Cofre/cofre.obj", L"Assets/Cofre/Cofre-color.png", L"Assets/Cofre/Cofre-spec.png", L"Assets/Gema/emerald.jpg", 0, 0);
		gema1 = new ModeloRR(d3dDevice, d3dContext, "Assets/Gema/emerald.obj", L"Assets/Gema/emerald.jpg", L"Assets/Gema/emerald.jpg", L"Assets/Gema/emerald.jpg", 0, 0);
		gema2 = new ModeloRR(d3dDevice, d3dContext, "Assets/Gema/emerald.obj", L"Assets/Gema/emerald.jpg", L"Assets/Gema/emerald.jpg", L"Assets/Gema/emerald.jpg", 0, 0);
		gema3 = new ModeloRR(d3dDevice, d3dContext, "Assets/Gema/emerald.obj", L"Assets/Gema/emerald.jpg", L"Assets/Gema/emerald.jpg", L"Assets/Gema/emerald.jpg", 0, 0);
		gema4 = new ModeloRR(d3dDevice, d3dContext, "Assets/Gema/emerald.obj", L"Assets/Gema/emerald.jpg", L"Assets/Gema/emerald.jpg", L"Assets/Gema/emerald.jpg", 0, 0);
		gema5 = new ModeloRR(d3dDevice, d3dContext, "Assets/Gema/emerald.obj", L"Assets/Gema/emerald.jpg", L"Assets/Gema/emerald.jpg", L"Assets/Gema/emerald.jpg", 0, 0);
		
		//OTROS MODELOS
		silo = new ModeloRR(d3dDevice, d3dContext, "Assets/Silo.obj", L"Assets/Silo_color.jpg", L"Assets/Silo_specular.png", L"Assets/Silo_normal.png", -100, 20);
		madera = new ModeloRR(d3dDevice, d3dContext, "Assets/madera.obj", L"Assets/wood_color.png", L"Assets/wood_specular.png", L"Assets/wood_normal.png", 80, -35);
		molino = new ModeloRR(d3dDevice, d3dContext, "Assets/molino.obj", L"Assets/Windmill_color.jpg", L"Assets/Windmill_specular.jpg", L"Assets/Windmill_normal.jpg", 90, 25);
		casa = new ModeloRR(d3dDevice, d3dContext, "Assets/cottage.obj", L"Assets/cottage_diffuse.png", L"Assets/cottage_specular3.png", L"Assets/cottage_normal.png", 90, -20);
		casa2 = new ModeloRR(d3dDevice, d3dContext, "Assets/cottage.obj", L"Assets/cottage_diffuse.png", L"Assets/cottage_specular3.png", L"Assets/cottage_normal.png", -100, 50);
		granero = new ModeloRR(d3dDevice, d3dContext, "Assets/barn.obj", L"Assets/barn_color.jpg", L"Assets/barn_specular6.png", L"Assets/barn_normal2.png", 90, 50);
		colisionterreno = new ModeloRR(d3dDevice, d3dContext, "Assets/caja.obj", L"Assets/caja.jpg", L"Assets/CajaS.png", L"Assets/CajaN.png", 0, 0);
		torremadera = new ModeloRR(d3dDevice, d3dContext, "Assets/torreMadera.obj", L"Assets/Wood_Tower_color.jpg", L"Assets/Wood_Tower_specular.png", L"Assets/Wood_Tower_normal.jpg", -50, -125);
		zanahoria1 = new ModeloRR(d3dDevice, d3dContext, "Assets/Carrot1.obj", L"Assets/carrot_albedo2.jpg", L"Assets/carrot_opacity.jpg", L"Assets/carrot_normal.jpg", 8, 80);
		zanahoria2 = new ModeloRR(d3dDevice, d3dContext, "Assets/Carrot1.obj", L"Assets/carrot_albedo2.jpg", L"Assets/carrot_opacity.jpg", L"Assets/carrot_normal.jpg", 2, 20);
		zanahoria3 = new ModeloRR(d3dDevice, d3dContext, "Assets/Carrot1.obj", L"Assets/carrot_albedo2.jpg", L"Assets/carrot_opacity.jpg", L"Assets/carrot_normal.jpg", 3, 30);
		zanahoria4 = new ModeloRR(d3dDevice, d3dContext, "Assets/Carrot1.obj", L"Assets/carrot_albedo2.jpg", L"Assets/carrot_opacity.jpg", L"Assets/carrot_normal.jpg", 4, 40);
		zanahoria5 = new ModeloRR(d3dDevice, d3dContext, "Assets/Carrot1.obj", L"Assets/carrot_albedo2.jpg", L"Assets/carrot_opacity.jpg", L"Assets/carrot_normal.jpg", 5, 50);
		zanahoria6 = new ModeloRR(d3dDevice, d3dContext, "Assets/Carrot1.obj", L"Assets/carrot_albedo2.jpg", L"Assets/carrot_opacity.jpg", L"Assets/carrot_normal.jpg", 6, 60);
		zanahoria7 = new ModeloRR(d3dDevice, d3dContext, "Assets/Carrot1.obj", L"Assets/carrot_albedo2.jpg", L"Assets/carrot_opacity.jpg", L"Assets/carrot_normal.jpg", 7, 70);
		caballo = new ModeloRR(d3dDevice, d3dContext, "Assets/caballo3.obj", L"Assets/caballo_textura3.jpg", L"Assets/caballo_specular.jpg", L"Assets/caballo_normal.jpg", 55, -15);


		//GUI
		//vida = new GUI(d3dDevice, d3dContext, 0.15, 0.26, L"Assets/GUI/health_full.png");

		//Texto
		tiempo = new Text(d3dDevice, d3dContext, 3.6, 1.2, L"Assets/GUI/font.jpg", XMFLOAT4(1.0f, 1.0f, 1.0f, 1.0f));
		zanahoriasText = new Text(d3dDevice, d3dContext, 3.6, 1.2, L"Assets/GUI/font.jpg", XMFLOAT4(1.0f, 1.0f, 1.0f, 1.0f));
		victoriaText = new Text(d3dDevice, d3dContext, 8.0, 2.67, L"Assets/GUI/font.jpg", XMFLOAT4(1.0f, 1.0f, 1.0f, 1.0f));
		derrotaText = new Text(d3dDevice, d3dContext, 8.0, 2.67, L"Assets/GUI/font.jpg", XMFLOAT4(1.0f, 1.0f, 1.0f, 1.0f));
	}

	~DXRR()
	{
		LiberaD3D();
		m_XACT3.Terminate();
	}
	
	bool IniciaD3D(HWND hWnd)
	{
		this->hInstance = hInstance;
		this->hWnd = hWnd;

		//obtiene el ancho y alto de la ventana donde se dibuja
		RECT dimensions;
		GetClientRect(hWnd, &dimensions);
		unsigned int width = dimensions.right - dimensions.left;
		unsigned int heigth = dimensions.bottom - dimensions.top;

		//Las formas en como la pc puede ejecutar el DX11, la mas rapida es D3D_DRIVER_TYPE_HARDWARE pero solo se puede usar cuando lo soporte el hardware
		//otra opcion es D3D_DRIVER_TYPE_WARP que emula el DX11 en los equipos que no lo soportan
		//la opcion menos recomendada es D3D_DRIVER_TYPE_SOFTWARE, es la mas lenta y solo es util cuando se libera una version de DX que no sea soportada por hardware
		D3D_DRIVER_TYPE driverTypes[]=
		{
			D3D_DRIVER_TYPE_HARDWARE, D3D_DRIVER_TYPE_WARP, D3D_DRIVER_TYPE_SOFTWARE
		};
		unsigned int totalDriverTypes = ARRAYSIZE(driverTypes);

		//La version de DX que utilizara, en este caso el DX11
		D3D_FEATURE_LEVEL featureLevels[]=
		{
			D3D_FEATURE_LEVEL_11_0, D3D_FEATURE_LEVEL_10_1, D3D_FEATURE_LEVEL_10_0
		};
		unsigned int totalFeaturesLevels = ARRAYSIZE(featureLevels);

		DXGI_SWAP_CHAIN_DESC swapChainDesc;
		ZeroMemory(&swapChainDesc, sizeof(swapChainDesc));
		swapChainDesc.BufferCount = 1;
		swapChainDesc.BufferDesc.Width = width;
		swapChainDesc.BufferDesc.Height = heigth;
		swapChainDesc.BufferDesc.Format = DXGI_FORMAT_R8G8B8A8_UNORM;
		swapChainDesc.BufferDesc.RefreshRate.Numerator = 60;
		swapChainDesc.BufferDesc.RefreshRate.Denominator = 1;
		swapChainDesc.BufferUsage = DXGI_USAGE_RENDER_TARGET_OUTPUT;
		swapChainDesc.OutputWindow = hWnd;
		swapChainDesc.Windowed = true;
		swapChainDesc.SampleDesc.Count = 1;
		swapChainDesc.SampleDesc.Quality = 0;

		HRESULT result;
		unsigned int driver = 0, creationFlags = 0;
		for(driver = 0; driver<totalDriverTypes; driver++)
		{
			result = D3D11CreateDeviceAndSwapChain(0, driverTypes[driver], 0,
				creationFlags, featureLevels, totalFeaturesLevels, 
				D3D11_SDK_VERSION, &swapChainDesc, &swapChain,
				&d3dDevice, &featureLevel, &d3dContext);

			if(SUCCEEDED(result))
			{
				driverType = driverTypes[driver];
				break;
			}
		}

		if(FAILED(result))
		{

			//Error al crear el Direct3D device
			return false;
		}
		
		ID3D11Texture2D* backBufferTexture;
		result = swapChain->GetBuffer(0, __uuidof(ID3D11Texture2D), (LPVOID*)&backBufferTexture);
		if(FAILED(result))
		{
			//"Error al crear el swapChainBuffer
			return false;
		}

		result = d3dDevice->CreateRenderTargetView(backBufferTexture, 0, &backBufferTarget);
		if(backBufferTexture)
			backBufferTexture->Release();

		if(FAILED(result))
		{
			//Error al crear el renderTargetView
			return false;
		}


		D3D11_VIEWPORT viewport;
		viewport.Width = (FLOAT)width;
		viewport.Height = (FLOAT)heigth;
		viewport.MinDepth = 0.0f;
		viewport.MaxDepth = 1.0f;
		viewport.TopLeftX = 0.0f;
		viewport.TopLeftY = 0.0f;

		d3dContext->RSSetViewports(1, &viewport);

		D3D11_TEXTURE2D_DESC depthTexDesc;
		ZeroMemory(&depthTexDesc, sizeof(depthTexDesc));
		depthTexDesc.Width = width;
		depthTexDesc.Height = heigth;
		depthTexDesc.MipLevels = 1;
		depthTexDesc.ArraySize = 1;
		depthTexDesc.Format = DXGI_FORMAT_D24_UNORM_S8_UINT;
		depthTexDesc.SampleDesc.Count = 1;
		depthTexDesc.SampleDesc.Quality = 0;
		depthTexDesc.Usage = D3D11_USAGE_DEFAULT;
		depthTexDesc.BindFlags = D3D11_BIND_DEPTH_STENCIL;
		depthTexDesc.CPUAccessFlags = 0;
		depthTexDesc.MiscFlags = 0;
		
		result = d3dDevice->CreateTexture2D(&depthTexDesc, NULL, &depthTexture);
		if(FAILED(result))
		{
			MessageBox(0, L"Error", L"Error al crear la DepthTexture", MB_OK);
			return false;
		}

		D3D11_DEPTH_STENCIL_VIEW_DESC descDSV;
		ZeroMemory(&descDSV, sizeof(descDSV));
		descDSV.Format = depthTexDesc.Format;
		descDSV.ViewDimension = D3D11_DSV_DIMENSION_TEXTURE2D;
		descDSV.Texture2D.MipSlice = 0;

		result = d3dDevice->CreateDepthStencilView(depthTexture, &descDSV, &depthStencilView);
		if(FAILED(result))
		{
			MessageBox(0, L"Error", L"Error al crear el depth stencil target view", MB_OK);
			return false;
		}

		d3dContext->OMSetRenderTargets(1, &backBufferTarget, depthStencilView);

		//Inicializar XACT
		bool res = m_XACT3.Initialize();
		if (!res) return false;
		res = m_XACT3.LoadWaveBank(L"Win\\WaveBank.xwb");
		if (!res) return false;
		res = m_XACT3.LoadSoundBank(L"Win\\SoundBank.xsb");
		if (!res) return false;

		// Reproducir
		cueIndex = m_XACT3.m_pSoundBank->GetCueIndex("Fondo");
		//m_XACT3.m_pSoundBank->Play(cueIndex, 0, 0, 0);
		cueIndex = m_XACT3.m_pSoundBank->GetCueIndex("Item");

		return true;			
		
	}

	void LiberaD3D(void)
	{
		if(depthTexture)
			depthTexture->Release();
		if(depthStencilView)
			depthStencilView->Release();
		if(backBufferTarget)
			backBufferTarget->Release();
		if(swapChain)
			swapChain->Release();
		if(d3dContext)
			d3dContext->Release();
		if(d3dDevice)
			d3dDevice->Release();

		depthTexture = 0;
		depthStencilView = 0;
		d3dDevice = 0;
		d3dContext = 0;
		swapChain = 0;
		backBufferTarget = 0;
	}
	
	void Render(void)
	{
		rotCam += izqder;
		// Trabaja XACT
		m_XACT3.DoWork();
		stringstream ss;

		float sphere[3] = { 0,0,0 };
		float prevPos[3] = { camara->posCam.x, camara->posCam.z, camara->posCam.z };
		static float angle = 0.0f;
		angle += 0.005;
		if (angle >= 360) angle = 0.0f;
		bool collide = false;
		if( d3dContext == 0 )
			return;

		float clearColor[4] = { 0, 0, 0, 1.0f };
		d3dContext->ClearRenderTargetView( backBufferTarget, clearColor );
		d3dContext->ClearDepthStencilView( depthStencilView, D3D11_CLEAR_DEPTH, 1.0f, 0 );

		camara->posCam.y = terreno->Superficie(camara->posCam.x, camara->posCam.z) + 10;
		//camara->posCam3P.y = terreno->Superficie(camara->posCam.x, camara->posCam.z) + 4;

		camara->UpdateCam(vel, velRightLeft, arriaba, izqder);

		//MENSAJE DE VICTORIA Y DERROTA
		if (zanahorias ==0 )
		{
			victoriaText->DrawTextW(-0.30, 0.0, "(: Ganaste! :) ", 0.015);

		}

		if (segundos <= 0.0)
		{
			segundos = 0;
			derrotaText->DrawTextW(-0.30, 0.0, "): Perdiste :( ", 0.015);
			zanahoria1bool = false;
			zanahoria2bool = false;
			zanahoria3bool = false;
			zanahoria4bool = false;
			zanahoria5bool = false;
			zanahoria6bool = false;
			zanahoria7bool = false;

		}

		//Colisiones

		if (isPointInsideSphere(camara->getPos(), silo->getSphere(25))) {

			Csilobool = false;

		}
		else Csilobool = true;

		if (isPointInsideSphere(camara->getPos(), madera->getSphere(5))) {

			Cmaderabool = false;

		}
		else Cmaderabool = true;

		if (isPointInsideSphere(camara->getPos(), molino->getSphere(2))) {

			Cmolinobool = false;

		}
		else Cmolinobool = true;

		if (isPointInsideSphere(camara->getPos(), casa->getSphere(20))) {

			Ccasabool = false;

		}
		else Ccasabool = true;

		if (isPointInsideSphere(camara->getPos(), casa2->getSphere(25))) {

			Ccasa2bool = false;

		}
		else Ccasa2bool = true;

		if (isPointInsideSphere(camara->getPos(), granero->getSphere(25))) {

			Cgranerobool = false;

		}
		else Cgranerobool = true;

		if (isPointInsideSphere(camara->getPos(), torremadera->getSphere(23))) {

			Ctorremaderabool = false;

		}
		else Ctorremaderabool = true;


		if (isPointInsideSphere(camara->getPos(), zanahoria1->getSphere(5))) {
			//camara->posCam = camara->posCamPast;
			if (!effectDone && zanahoria1bool) {
				m_XACT3.m_pSoundBank->Play(cueIndex, 0, 0, 0);
				effectDone = true;
				zanahorias --;
				zanahoria1bool = false;
			}
		}
		else if (isPointInsideSphere(camara->getPos(), zanahoria2->getSphere(5))) {
			//camara->posCam = camara->posCamPast;
			if (!effectDone && zanahoria2bool) {
				m_XACT3.m_pSoundBank->Play(cueIndex, 0, 0, 0);
				effectDone = true;
				zanahorias--;
				zanahoria2bool = false;
			}
		}
		else if (isPointInsideSphere(camara->getPos(), zanahoria3->getSphere(5))) {
			//camara->posCam = camara->posCamPast;
			if (!effectDone && zanahoria3bool) {
				m_XACT3.m_pSoundBank->Play(cueIndex, 0, 0, 0);
				effectDone = true;
				zanahorias--;
				zanahoria3bool = false;
			}
		}
		else if (isPointInsideSphere(camara->getPos(), zanahoria4->getSphere(5))) {
			//camara->posCam = camara->posCamPast;
			if (!effectDone && zanahoria4bool) {
				m_XACT3.m_pSoundBank->Play(cueIndex, 0, 0, 0);
				effectDone = true;
				zanahorias--;
				zanahoria4bool = false;
			}
		}
		else if (isPointInsideSphere(camara->getPos(), zanahoria5->getSphere(5))) {
			//camara->posCam = camara->posCamPast;
			if (!effectDone && zanahoria5bool) {
				m_XACT3.m_pSoundBank->Play(cueIndex, 0, 0, 0);
				effectDone = true;
				zanahorias--;
				zanahoria5bool = false;
			}
		}
		else if (isPointInsideSphere(camara->getPos(), zanahoria6->getSphere(5))) {
			//camara->posCam = camara->posCamPast;
			if (!effectDone && zanahoria6bool) {
				m_XACT3.m_pSoundBank->Play(cueIndex, 0, 0, 0);
				effectDone = true;
				zanahorias--;
				zanahoria6bool = false;
			}
		}
		else if (isPointInsideSphere(camara->getPos(), zanahoria7->getSphere(5))) {
			//camara->posCam = camara->posCamPast;
			if (!effectDone && zanahoria7bool) {
				m_XACT3.m_pSoundBank->Play(cueIndex, 0, 0, 0);
				effectDone = true;
				zanahorias--;
				zanahoria7bool = false;
			}
		}

		//Colision con orillas
		if (!(isPointInsideSphere(camara->getPos(), colisionterreno->getSphere(148)))) {

			colisionorilla = false;

		}
		else colisionorilla = true;

		skydome->Update(camara->vista, camara->proyeccion);

		float camPosXZ[2] = { camara->posCam.x, camara->posCam.z };

		TurnOffDepth();
		skydome->Render(camara->posCam);
		TurnOnDepth();

		terreno->Draw(camara->vista, camara->proyeccion);
		
		billboard->Draw(camara->vista, camara->proyeccion, camara->posCam,
			-11, -78, 4, 5, uv1, uv2, uv3, uv4, frameBillboard, true);

		arbol->Draw(camara->vista, camara->proyeccion, camara->posCam,
			-11, 78, terreno->Superficie(-11, 78), 5, uv1, uv2, uv3, uv4, frameBillboard, false);

		//OTROS BILLBOARDS

		vaca->Draw(camara->vista, camara->proyeccion, camara->posCam,
			65, 68, 10, 5, uv1, uv2, uv3, uv4, frameBillboard, false);
		cerdo->Draw(camara->vista, camara->proyeccion, camara->posCam,
			65, 35, 10, 3, uv1, uv2, uv3, uv4, frameBillboard, false);
		roca1->Draw(camara->vista, camara->proyeccion, camara->posCam,
			-25, 130, 9, 5, uv1, uv2, uv3, uv4, frameBillboard, false);
		roca2->Draw(camara->vista, camara->proyeccion, camara->posCam,
			45, -140, 10, 5, uv1, uv2, uv3, uv4, frameBillboard, false);
		roca3->Draw(camara->vista, camara->proyeccion, camara->posCam,
			0, -120, 10, 7, uv1, uv2, uv3, uv4, frameBillboard, false);
		arbol1->Draw(camara->vista, camara->proyeccion, camara->posCam,
			-95, -120, 8, 10, uv1, uv2, uv3, uv4, frameBillboard, false);
		arbol2->Draw(camara->vista, camara->proyeccion, camara->posCam,
			-100, -75, 8, 9, uv1, uv2, uv3, uv4, frameBillboard, false);
		arbol3->Draw(camara->vista, camara->proyeccion, camara->posCam,
			-120, -50, 8, 9, uv1, uv2, uv3, uv4, frameBillboard, false);
		arbol4->Draw(camara->vista, camara->proyeccion, camara->posCam,
			115, -5, 8, 10, uv1, uv2, uv3, uv4, frameBillboard, false);
		arbol5->Draw(camara->vista, camara->proyeccion, camara->posCam,
			120, -80, 8, 10, uv1, uv2, uv3, uv4, frameBillboard, false);
		arbol6->Draw(camara->vista, camara->proyeccion, camara->posCam,
			20, 120, 8, 12, uv1, uv2, uv3, uv4, frameBillboard, false);
		arbol7->Draw(camara->vista, camara->proyeccion, camara->posCam,
			100, 80, 13, 9, uv1, uv2, uv3, uv4, frameBillboard, false);
		arbol8->Draw(camara->vista, camara->proyeccion, camara->posCam,
			-25, -110, 10, 8, uv1, uv2, uv3, uv4, frameBillboard, false);
		arbol9->Draw(camara->vista, camara->proyeccion, camara->posCam,
			35, 130, 10, 9, uv1, uv2, uv3, uv4, frameBillboard, false);
		arbol10->Draw(camara->vista, camara->proyeccion, camara->posCam,
			20, -100, 10, 9, uv1, uv2, uv3, uv4, frameBillboard, false);
		otroaarbol->Draw(camara->vista, camara->proyeccion, camara->posCam,
			-45, 110, 10, 10, uv1, uv2, uv3, uv4, frameBillboard, false);
		otroaarbol2->Draw(camara->vista, camara->proyeccion, camara->posCam,
			35, 115, 10, 9, uv1, uv2, uv3, uv4, frameBillboard, false);
		otroaarbol3->Draw(camara->vista, camara->proyeccion, camara->posCam,
			-45, 130, 10, 11, uv1, uv2, uv3, uv4, frameBillboard, false);
		otroaarbol4->Draw(camara->vista, camara->proyeccion, camara->posCam,
			115, -5, 8, 10, uv1, uv2, uv3, uv4, frameBillboard, false);
		otroaarbol5->Draw(camara->vista, camara->proyeccion, camara->posCam,
			35, 120, 8, 10, uv1, uv2, uv3, uv4, frameBillboard, false);
		montaña1->Draw(camara->vista, camara->proyeccion, camara->posCam,
			145, -145, 8, 70, uv1, uv2, uv3, uv4, frameBillboard, false);
		montaña2->Draw(camara->vista, camara->proyeccion, camara->posCam,
			145, 145, 8, 70, uv1, uv2, uv3, uv4, frameBillboard, false);
		montaña3->Draw(camara->vista, camara->proyeccion, camara->posCam,
			-145, 145, 8, 70, uv1, uv2, uv3, uv4, frameBillboard, false);
		montaña4->Draw(camara->vista, camara->proyeccion, camara->posCam,
			-145, -145, 8, 70, uv1, uv2, uv3, uv4, frameBillboard, false);
		pino1->Draw(camara->vista, camara->proyeccion, camara->posCam,
			-75, -130, 8, 15, uv1, uv2, uv3, uv4, frameBillboard, false);
		pino2->Draw(camara->vista, camara->proyeccion, camara->posCam,
			50, -130, 8, 15, uv1, uv2, uv3, uv4, frameBillboard, false);


		model->Draw(camara->vista, camara->proyeccion, terreno->Superficie(10, 20), camara->posCam, 10.0f, 0, 'A', 1);
		//Gemas
		gema1->setPos(10, 10);
		gema1->Draw(camara->vista, camara->proyeccion, terreno->Superficie(0, 0) + 2.5 + floatGem, camara->posCam, 10.0f, D3DX_PI / 2 + rotGem, 'Y', 1);

		gema2->setPos(20, 10);
		gema2->Draw(camara->vista, camara->proyeccion, terreno->Superficie(0, 0) + 2.5 - floatGem, camara->posCam, 10.0f, D3DX_PI / 2 + -rotGem, 'Y', 1);

		gema3->setPos(30, 10);
		gema3->Draw(camara->vista, camara->proyeccion, terreno->Superficie(0, 0) + 2.5 - floatGem, camara->posCam, 10.0f, D3DX_PI / 2 + rotGem, 'Y', 1);

		gema4->setPos(40, 10);
		gema4->Draw(camara->vista, camara->proyeccion, terreno->Superficie(0, 0) + 2.5 + floatGem, camara->posCam, 10.0f, D3DX_PI / 2 + -rotGem, 'Y', 1);

		gema5->setPos(50, 10);
		gema5->Draw(camara->vista, camara->proyeccion, terreno->Superficie(0, 0) + 2.5 - floatGem, camara->posCam, 10.0f, D3DX_PI / 2 + -rotGem, 'Y', 1);

		//OTROS MODELOS 
		silo->Draw(camara->vista, camara->proyeccion, terreno->Superficie(0, 0), camara->posCam, 10.0f, 0, 'A', 5.5);
		madera->Draw(camara->vista, camara->proyeccion, terreno->Superficie(0, 0), camara->posCam, 10.0f, 0, 'A', 3);
		molino->Draw(camara->vista, camara->proyeccion, terreno->Superficie(0, 0), camara->posCam, 10.0f, 0, 'A', 5);
		casa->Draw(camara->vista, camara->proyeccion, terreno->Superficie(0, 0), camara->posCam, 10.0f, 0, 'A', 4);
		casa2->Draw(camara->vista, camara->proyeccion, terreno->Superficie(0, 0), camara->posCam, 10.0f, 0, 'A', 4);
		granero->Draw(camara->vista, camara->proyeccion, terreno->Superficie(0, 0), camara->posCam, 10.0f, 0, 'A', 4);
		torremadera->Draw(camara->vista, camara->proyeccion, terreno->Superficie(0, 0), camara->posCam, 10.0f, 0, 'A', 3);
		zanahoria1->Draw(camara->vista, camara->proyeccion, terreno->Superficie(100, 20) + 3.5 + floatGem, camara->posCam, 10.0f, 0, 'A', 1.5);
		zanahoria2->Draw(camara->vista, camara->proyeccion, terreno->Superficie(100, 20) + 3.5 - floatGem, camara->posCam, 10.0f, 0, 'A', 1.5);
		zanahoria3->Draw(camara->vista, camara->proyeccion, terreno->Superficie(100, 20) + 3.5 + floatGem, camara->posCam, 10.0f, 0, 'A', 1.5);
		zanahoria4->Draw(camara->vista, camara->proyeccion, terreno->Superficie(100, 20) + 3.5 + floatGem, camara->posCam, 10.0f, 0, 'A', 1.5);
		zanahoria5->Draw(camara->vista, camara->proyeccion, terreno->Superficie(100, 20) + 3.5 - floatGem, camara->posCam, 10.0f, 0, 'A', 1.5);
		zanahoria6->Draw(camara->vista, camara->proyeccion, terreno->Superficie(100, 20) + 3.5 - floatGem, camara->posCam, 10.0f, 0, 'A', 1.5);
		zanahoria7->Draw(camara->vista, camara->proyeccion, terreno->Superficie(100, 20) + 3.5 + floatGem, camara->posCam, 10.0f, 0, 'A', 1.5);
		
		caballo->setPosX(camara->hdveo.x);
		caballo->setPosZ(camara->hdveo.z);
		caballo->Draw(camara->vista, camara->proyeccion, terreno->Superficie(caballo->getPosX(), caballo->getPosZ()) , camara->posCam, 10.0f, rotCam + 80, 'Y', 1.5);

		//GUI
		//vida->Draw(-0.8, -0.8);

		//Texto

		ss << zanahorias;
		tiempo->DrawTextW(-0.85, 0.85, "Tiempo Restante: " + tiempo->Time(segundos), 0.015);
		zanahoriasText->DrawTextW(-0.85, 0.78, "Zanahorias: " + ss.str(), 0.015);


		//Globales
		segundos -= 0.02;
		rotGem += 0.01;
		if (subir) {
			floatGem += 0.01;
		}
		else {
			floatGem -= 0.01;
		}

		if (floatGem > 1.5) {
			floatGem = 1.5;
			subir = false;
		}
		else if (floatGem < -1.5) {
			floatGem = -1.5;
			subir = true;
		}
		

		swapChain->Present( 1, 0 );
	}

	bool isPointInsideSphere(float* point, float* sphere) {
		bool collition = false;

		float distance = sqrt((point[0] - sphere[0]) * (point[0] - sphere[0]) +
			(point[1] - sphere[1]) * (point[1] - sphere[1]));

		if (distance < sphere[2]) {
			collition = true;
		}
		else if (distance > 5) {
			effectDone = false;
		}
		

		return collition;
	}

	//Activa el alpha blend para dibujar con transparencias
	void TurnOnAlphaBlending()
	{
		float blendFactor[4];
		blendFactor[0] = 0.0f;
		blendFactor[1] = 0.0f;
		blendFactor[2] = 0.0f;
		blendFactor[3] = 0.0f;
		HRESULT result;

		D3D11_BLEND_DESC descABSD;
		ZeroMemory(&descABSD, sizeof(D3D11_BLEND_DESC));
		descABSD.RenderTarget[0].BlendEnable = TRUE;
		descABSD.RenderTarget[0].SrcBlend = D3D11_BLEND_ONE;
		descABSD.RenderTarget[0].DestBlend = D3D11_BLEND_INV_SRC_ALPHA;
		descABSD.RenderTarget[0].BlendOp = D3D11_BLEND_OP_ADD;
		descABSD.RenderTarget[0].SrcBlendAlpha = D3D11_BLEND_ONE;
		descABSD.RenderTarget[0].DestBlendAlpha = D3D11_BLEND_ZERO;
		descABSD.RenderTarget[0].BlendOpAlpha = D3D11_BLEND_OP_ADD;
		descABSD.RenderTarget[0].RenderTargetWriteMask = 0x0f;

		result = d3dDevice->CreateBlendState(&descABSD, &alphaBlendState);
		if(FAILED(result))
		{
			MessageBox(0, L"Error", L"Error al crear el blend state", MB_OK);
			return;
		}

		d3dContext->OMSetBlendState(alphaBlendState, blendFactor, 0xffffffff);
	}

	//Regresa al blend normal(solido)
	void TurnOffAlphaBlending()
	{
		D3D11_BLEND_DESC descCBSD;
		ZeroMemory(&descCBSD, sizeof(D3D11_BLEND_DESC));
		descCBSD.RenderTarget[0].BlendEnable = FALSE;
		descCBSD.RenderTarget[0].SrcBlend = D3D11_BLEND_ONE;
		descCBSD.RenderTarget[0].DestBlend = D3D11_BLEND_INV_SRC_ALPHA;
		descCBSD.RenderTarget[0].BlendOp = D3D11_BLEND_OP_ADD;
		descCBSD.RenderTarget[0].SrcBlendAlpha = D3D11_BLEND_ONE;
		descCBSD.RenderTarget[0].DestBlendAlpha = D3D11_BLEND_ZERO;
		descCBSD.RenderTarget[0].BlendOpAlpha = D3D11_BLEND_OP_ADD;
		descCBSD.RenderTarget[0].RenderTargetWriteMask = 0x0f;
		HRESULT result;

		result = d3dDevice->CreateBlendState(&descCBSD, &commonBlendState);
		if(FAILED(result))
		{
			MessageBox(0, L"Error", L"Error al crear el blend state", MB_OK);
			return;
		}

		d3dContext->OMSetBlendState(commonBlendState, NULL, 0xffffffff);
	}

	void TurnOnDepth()
	{
		D3D11_DEPTH_STENCIL_DESC descDSD;
		ZeroMemory(&descDSD, sizeof(descDSD));
		descDSD.DepthEnable = true;
		descDSD.DepthWriteMask = D3D11_DEPTH_WRITE_MASK_ALL;
		descDSD.DepthFunc = D3D11_COMPARISON_LESS;
		descDSD.StencilEnable=true;
		descDSD.StencilReadMask = 0xFF;
		descDSD.StencilWriteMask = 0xFF;
		descDSD.FrontFace.StencilFailOp = D3D11_STENCIL_OP_KEEP;
		descDSD.FrontFace.StencilDepthFailOp = D3D11_STENCIL_OP_INCR;
		descDSD.FrontFace.StencilPassOp = D3D11_STENCIL_OP_KEEP;
		descDSD.FrontFace.StencilFunc = D3D11_COMPARISON_ALWAYS;
		descDSD.BackFace.StencilFailOp = D3D11_STENCIL_OP_KEEP;
		descDSD.BackFace.StencilDepthFailOp = D3D11_STENCIL_OP_DECR;
		descDSD.BackFace.StencilPassOp = D3D11_STENCIL_OP_KEEP;
		descDSD.BackFace.StencilFunc = D3D11_COMPARISON_ALWAYS;

		d3dDevice->CreateDepthStencilState(&descDSD, &depthStencilState);
		
		d3dContext->OMSetDepthStencilState(depthStencilState, 1);
	}

	void TurnOffDepth()
	{
		D3D11_DEPTH_STENCIL_DESC descDDSD;
		ZeroMemory(&descDDSD, sizeof(descDDSD));
		descDDSD.DepthEnable = false;
		descDDSD.DepthWriteMask = D3D11_DEPTH_WRITE_MASK_ALL;
		descDDSD.DepthFunc = D3D11_COMPARISON_LESS;
		descDDSD.StencilEnable=true;
		descDDSD.StencilReadMask = 0xFF;
		descDDSD.StencilWriteMask = 0xFF;
		descDDSD.FrontFace.StencilFailOp = D3D11_STENCIL_OP_KEEP;
		descDDSD.FrontFace.StencilDepthFailOp = D3D11_STENCIL_OP_INCR;
		descDDSD.FrontFace.StencilPassOp = D3D11_STENCIL_OP_KEEP;
		descDDSD.FrontFace.StencilFunc = D3D11_COMPARISON_ALWAYS;
		descDDSD.BackFace.StencilFailOp = D3D11_STENCIL_OP_KEEP;
		descDDSD.BackFace.StencilDepthFailOp = D3D11_STENCIL_OP_DECR;
		descDDSD.BackFace.StencilPassOp = D3D11_STENCIL_OP_KEEP;
		descDDSD.BackFace.StencilFunc = D3D11_COMPARISON_ALWAYS;

		d3dDevice->CreateDepthStencilState(&descDDSD, &depthStencilDisabledState);
		d3dContext->OMSetDepthStencilState(depthStencilDisabledState, 1);
	}

	void billCargaFuego()
	{
		uv1[0].u = .125;
		uv2[0].u = .125;
		uv3[0].u = 0;
		uv4[0].u = 0;

		uv1[0].v = .25;
		uv2[0].v = 0;
		uv3[0].v = 0;
		uv4[0].v = .25;


		for (int j = 0; j < 8; j++) {
			uv1[j].u = uv1[0].u + (j * .125);
			uv2[j].u = uv2[0].u + (j * .125);
			uv3[j].u = uv3[0].u + (j * .125);
			uv4[j].u = uv4[0].u + (j * .125);

			uv1[j].v = .25;
			uv2[j].v = 0;
			uv3[j].v = 0;
			uv4[j].v = .25;
		}
		for (int j = 0; j < 8; j++) {
			uv1[j + 8].u = uv1[0].u + (j * .125);
			uv2[j + 8].u = uv2[0].u + (j * .125);
			uv3[j + 8].u = uv3[0].u + (j * .125);
			uv4[j + 8].u = uv4[0].u + (j * .125);

			uv1[j + 8].v = .5;
			uv2[j + 8].v = .25;
			uv3[j + 8].v = .25;
			uv4[j + 8].v = .5;
		}

		for (int j = 0; j < 8; j++) {
			uv1[j + 16].u = uv1[0].u + (j * .125);
			uv2[j + 16].u = uv2[0].u + (j * .125);
			uv3[j + 16].u = uv3[0].u + (j * .125);
			uv4[j + 16].u = uv4[0].u + (j * .125);

			uv1[j + 16].v = .75;
			uv2[j + 16].v = .5;
			uv3[j + 16].v = .5;
			uv4[j + 16].v = .75;
		}

		for (int j = 0; j < 8; j++) {
			uv1[j + 24].u = uv1[0].u + (j * .125);
			uv2[j + 24].u = uv2[0].u + (j * .125);
			uv3[j + 24].u = uv3[0].u + (j * .125);
			uv4[j + 24].u = uv4[0].u + (j * .125);

			uv1[j + 24].v = 1;
			uv2[j + 24].v = .75;
			uv3[j + 24].v = .75;
			uv4[j + 24].v = 1;
		}
	}

};
#endif