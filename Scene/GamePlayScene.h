#pragma once
#include<Windows.h>
#include"Triangle.h"
#include"ImGuiManager.h"
#include"Sprite.h"
#include"Sphere.h"
#include"Model.h"
#include"Input.h"
#include"Audio.h"

#include"Player.h"
#include"Object/Block/Block.h"
#include"CSVReader.h"


class GamePlayScene
{
public:

	void Initialize();
	void Update();
	void Draw();
	void Finalize();


	/// <summary>
	/// ブロックデータの読み込み
	/// </summary>
	void LoadBlockPopData();

	/// <summary>
	/// ブロック発生コマンドの更新
	/// </summary>
	void UpdateBlockPopCommands();

	void BlockSpown(Vector3, float);

	/// <summary>
	///	敵:敵弾を追加する
	/// </summary>
	void AddBlock(Block* block);

private:

	TextureManager* texture = nullptr;
	Input* input = nullptr;
	Audio* audio = nullptr;

	SoundData soundData1;

	SpriteData* spriteData = nullptr;
	Sprite* sprite;
	Model* model_ = nullptr;

	uint32_t uvTexture;
	uint32_t monsterTexture;

	ViewProjection viewProjection_;
	WorldTransform spriteTransform_;

	Player* player_ = nullptr;


	Vector3 blockPos;


	// ブロック発生コマンド
	std::stringstream blockPopCommands;
	// ブロック
	std::list<Block*> blocks_;
};

