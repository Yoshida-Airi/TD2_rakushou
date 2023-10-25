#include "GameTitleScene.h"


GameTitleScene::~GameTitleScene()
{
	delete model;
}

void GameTitleScene::Initialize()
{
	texture = TextureManager::GetInstance();
	input = Input::GetInstance();

	model = new Model;
	model->Initialize("Resources", "gamename.obj");

	Vector3 position = { 0,10,0 };

	worldTransform_.Initialize();
	worldTransform_.translation_ = position;
	worldTransform_.scale_ = { 10,10,0 };
	worldTransform_.UpdateMatrix();

	viewProjection_.Initialize();




}

void GameTitleScene::Update()
{
	input->Update();
	
	worldTransform_.UpdateMatrix();
}

void GameTitleScene::Draw()
{
	model->Draw(viewProjection_, worldTransform_);
}

