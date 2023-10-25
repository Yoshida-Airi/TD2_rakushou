#include "GameManager.h"

GameManager::~GameManager()
{

#ifdef _DEBUG
	D3DResourceLeakChecker leakCheak;
#endif // _DEBUG


	CoUninitialize();

	delete title;
	delete gameScene;
	delete over;
	delete clear;

	delete engine;
	delete texture;
	delete dxCommon;
	delete winApp;
	delete input;
	delete imGuiManager;

}

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
	audio = Audio::GetInstance();
	audio->Initialize();


	CoInitializeEx(0, COINIT_MULTITHREADED);


	title = new GameTitleScene;
	title->Initialize();
	gameScene = new GamePlayScene;
	gameScene->Initialize();
	over = new GameOverScene;
	over->Initialize();
	clear = new GameClearScene;;
	clear->Initialize();

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

		//ゲームパットの状態を得る変数(XINPUT)
		XINPUT_STATE joyState;

		if (!Input::GetInstance()->GetJoystickState(0, joyState))
		{
			if (input->TriggerKey(DIK_RETURN))
			{
				scene = PLAY;
			}
		}
		

		if (Input::GetInstance()->GetJoystickState(0, joyState))
		{
			if (joyState.Gamepad.wButtons & XINPUT_GAMEPAD_X)
			{
				scene = PLAY;
			}
		}

		break;

	case PLAY:
		gameScene->Update();
		gameScene->Draw();

		if (input->TriggerKey(DIK_RETURN))
		{
			scene = OVER;

		}
		if (input->TriggerKey(DIK_X))
		{
			scene = CLEAR;

		}

		break;

	case OVER:

		over->Update();
		over->Draw();

		if (input->TriggerKey(DIK_RETURN))
		{
			scene = TITLE;
		}

		break;

	case CLEAR:

		clear->Update();
		clear->Draw();

		if (input->TriggerKey(DIK_RETURN))
		{
			scene = TITLE;
		}

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

