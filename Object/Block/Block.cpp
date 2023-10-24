#include "Block.h"
#include "TextureManager.h"
#include "Player.h"
#include "ImGuiManager.h"

void Block::Initialize(Model* model, Vector3 translation, const std::string& filename) {
	// NULLポインタチェック
	assert(model);
	model_ = model;
	model_->Initialize("Resources", filename);


	worldTransform_.Initialize();

	worldTransform_.translation_ = translation;
}

Block::~Block() {}

void Block::Move() {
	worldTransform_.translation_.x -= velocity_.x;
	worldTransform_.translation_.y -= velocity_.y;
	worldTransform_.translation_.z -= velocity_.z;
}

void Block::Update() {
	// ワールドトランスフォームの更新
	worldTransform_.UpdateMatrix();
}

void Block::Draw(const ViewProjection& viewProjection) {
	// モデル描画
	model_->Draw(viewProjection,worldTransform_);
}

void Block::OnCollision() {}

Vector3 Block::GetWorldPosition() {
	// ワールド座標を入れる変数
	Vector3 worldPos;
	// ワールド行列の平行移動成分を取得
	worldPos.x = worldTransform_.matWorld_.m[3][0];
	worldPos.y = worldTransform_.matWorld_.m[3][1];
	worldPos.z = worldTransform_.matWorld_.m[3][2];

	return worldPos;
}
