#include "GamePlayScene.h"

void GamePlayScene::Initialize()
{
	texture = TextureManager::GetInstance();
	input = Input::GetInstance();
	audio = Audio::GetInstance();

	spriteData = new SpriteData;
	sprite = new Sprite;
	model_ = new Model;

	soundData1 = audio->SoundLoadWave("Resources/Sound/distress.wav");
	audio->SoundPlayWave(soundData1, true);

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

	LoadBlockPopData();

}

void GamePlayScene::Update()
{
	input->Update();
	
	

	UpdateBlockPopCommands();
	for (Block* block : blocks_) {
		block->Update();
	}
	player_->Update();

	sprite->Update();

	

}

void GamePlayScene::Draw()
{

	for (Block* block : blocks_) {
		block->Draw(viewProjection_);
	}



	player_->Draw(viewProjection_);
	sprite->Draw(spriteTransform_);
	
}

void GamePlayScene::Finalize()
{
	delete player_;
	delete model_;
	delete sprite;
	delete spriteData;
	
	for (Block* block : blocks_) {
		delete block;
	}

	
}

void GamePlayScene::LoadBlockPopData() {
	// ファイルを開く
	std::ifstream file;
	file.open("csv/blockPop.csv");
	assert(file.is_open());

	// ファイルも内容を文字列ストリームにコピー
	blockPopCommands << file.rdbuf();

	// ファイルを閉じる
	file.close();
}

void GamePlayScene::UpdateBlockPopCommands() {

	// 1行分の文字列を入れる変数
	std::string line;

	// コマンド実行ループ
	while (getline(blockPopCommands, line)) {
		// 1行分の文字列をストリームに変換して解析しやすくなる
		std::istringstream line_stream(line);

		std::string word;
		// ,区切りで行の先頭文字列を取得
		getline(line_stream, word, ',');

		// "//"から始まる行はコメント
		if (word.find("//") == 0) {
			// コメント行を飛ばす
			continue;
		}

		// POPコマンド
		if (word.find("POP") == 0) {
			// X座標
			getline(line_stream, word, ',');
			blockPos.x = (float)std::atof(word.c_str());

			// Y座標
			getline(line_stream, word, ',');
			blockPos.y = (float)std::atof(word.c_str());

			// Z座標
			getline(line_stream, word, ',');
			blockPos.z = (float)std::atof(word.c_str());
		}

		// TYPEコマンド
		if (word.find("TYPE") == 0) {
			// type
			getline(line_stream, word, ',');
			float type = (float)std::atof(word.c_str());

			// ブロックを発生させる
			BlockSpown(Vector3(blockPos.x, blockPos.y, blockPos.z), type);

			break;
		}
	}
}

void GamePlayScene::BlockSpown(Vector3 translation, float type) {
	// ブロックの生成
	Block* block_ = new Block();
	// ブロックの初期化
	if (type < 3) {
		block_->Initialize(model_,  translation);
	}
	// ブロックのタイプ設定
	block_->SetType(type);
	AddBlock(block_);
}

void GamePlayScene::AddBlock(Block* block) {
	// リストに登録する
	blocks_.push_back(block);
}