#pragma once
#include"GamePlayScene.h"
#include"GameTitleScene.h"
#include"LeakCheck.h"

enum Scene
{
	TITLE,
	PLAY,
	OVER,
};

class GameManager
{
public:

	void Initialize();
	void Update();
	void Draw();
	void Finalize();



private:
	GamePlayScene* gameScene = nullptr;
	GameTitleScene* title = nullptr;

	const wchar_t* kWindowTitle = L"CG2";

	//アプリケーションの開始
	const uint32_t kWindowWidth = 1280;
	const uint32_t kWindowHeight = 720;


	WindowAPI* winApp = nullptr;
	DirectXCommon* dxCommon = nullptr;
	MyEngine* engine = nullptr;
	ImGuiManager* imGuiManager = nullptr;
	TextureManager* texture = nullptr;
	Input* input = nullptr;
	Scene scene;

};

