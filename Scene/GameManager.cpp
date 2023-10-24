#include "GameManager.h"

void GameManager::Initialize()
{
	winApp = WindowAPI::GetInstance();
	winApp->StartApp(kWindowTitle, kWindowWidth, kWindowHeight);
	dxCommon = DirectXCommon::GetInstance();
	dxCommon->Initialize();
	engine = MyEngine::GetInstance();
	engine->Initialize();

#ifdef _DEBUG
	imGuiManager = ImGuiManager::GetInstance();
	imGuiManager->Initialize();
#endif // _DEBUG


	texture = TextureManager::GetInstance();
	texture->Initialize(kWindowWidth, kWindowHeight);
	input = Input::GetInstance();
	input->Initialize();


	CoInitializeEx(0, COINIT_MULTITHREADED);


	title = new GameTitleScene;
	title->Initialize();
	gameScene = new GamePlayScene;
	gameScene->Initialize();

	scene = TITLE;

}

void GameManager::Update()
{
	dxCommon->PreDraw();
	engine->PreDraw();

#ifdef _DEBUG
	imGuiManager->Begin();
#endif // _DEBUG

	switch (scene)
	{
	case TITLE:
		title->Update();
		title->Draw();

		if (input->TriggerKey(DIK_RETURN))
		{
			scene = PLAY;
		}

		break;

	case PLAY:
		gameScene->Update();
		gameScene->Draw();

		if (input->TriggerKey(DIK_RETURN))
		{
			scene = OVER;

		}

		break;

	case OVER:

		scene = TITLE;


		break;
	}


#ifdef _DEBUG	//現在のシーン番号
	ImGui::Begin("Scene");
	ImGui::Text("%d", scene);
	ImGui::End();
#endif // _DEBUG




#ifdef _DEBUG
	imGuiManager->End();
#endif // _DEBUG

}

void GameManager::Draw()
{


#ifdef _DEBUG
	imGuiManager->Draw();
#endif // _DEBUG


	engine->PostDraw();
	dxCommon->PostDraw();
}

void GameManager::Finalize()
{
#ifdef _DEBUG
	D3DResourceLeakChecker leakCheak;
#endif // _DEBUG


	CoUninitialize();


	gameScene->Finalize();
	title->Finalize();

	delete engine;
	delete texture;
	delete dxCommon;
	delete winApp;
	delete input;
	delete imGuiManager;

}