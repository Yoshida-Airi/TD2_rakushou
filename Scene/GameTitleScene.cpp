#include "GameTitleScene.h"


void GameTitleScene::Initialize()
{
	texture = TextureManager::GetInstance();
	input = Input::GetInstance();

}

void GameTitleScene::Update()
{
	input->Update();
}

void GameTitleScene::Draw()
{

}

void GameTitleScene::Finalize()
{

}
