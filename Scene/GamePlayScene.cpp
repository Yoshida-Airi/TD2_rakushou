#include "GamePlayScene.h"

void GamePlayScene::Initialize()
{
	texture = TextureManager::GetInstance();
	input = Input::GetInstance();

	spriteData = new SpriteData;
	sprite = new Sprite;
	model_ = new Model;

	player_ = new Player;

	// ビュープロジェクションの初期化
	viewProjection_.Initialize();

	spriteData->vertex[0] = { 0.0f,360.0f,0.0f,1.0f };
	spriteData->vertex[1] = { 0.0f,0.0f,0.0f,1.0f };
	spriteData->vertex[2] = { 640.0f,360.0f,0.0f,1.0f };
	spriteData->vertex[3] = { 0.0f,0.0f,0.0f,1.0f };
	spriteData->vertex[4] = { 640.0f,0.0f,0.0f,1.0f };
	spriteData->vertex[5] = { 640.0f,360.0f,0.0f,1.0f };

	spriteData->transform =
	{
		{1.0f,1.0f,1.0f},
		{0.0f,0.0f,0.0f},
		{0.0f,0.0f,0.0f}
	};

	spriteTransform_.Initialize();

	uvTexture = texture->LoadTexture("Resources/uvChecker.png");
	monsterTexture = texture->LoadTexture("Resources/monsterBall.png");



	sprite->Initialize(spriteData, uvTexture);

	Vector3 playerPos = { -38, 22, 0 };
	player_->Initialize(model_, playerPos);

}

void GamePlayScene::Update()
{
	input->Update();


	player_->Update();

	sprite->Update();



}

void GamePlayScene::Draw()
{

	player_->Draw(viewProjection_);
	sprite->Draw(spriteTransform_);

	
}

void GamePlayScene::Finalize()
{
	delete player_;
	delete model_;
	delete sprite;
	delete spriteData;
	
}
