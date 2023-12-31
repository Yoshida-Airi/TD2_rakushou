#include "Sphere.h"

Sphere::~Sphere()
{
	
}

void Sphere::Initialize(uint32_t textureHandle)
{
	winApp_ = WindowAPI::GetInstance();
	dxCommon_ = DirectXCommon::GetInstance();
	engine_ = MyEngine::GetInstance();
	texture_ = TextureManager::GetInstance();
	textureHandle_ = textureHandle;
	

	kClientHeight_ = winApp_->GetHeight();
	kClientWidth_ = winApp_->GetWidth();

	

	VertexBuffer();
	MaterialBuffer();
	WvpBuffer();
	LightBuffer();


	//緯度の方向に分割
	for (uint32_t latIndex = 0; latIndex < kSubdivision; ++latIndex)
	{
		float lat = static_cast<float>(-std::numbers::pi) / 2.0f + kLatEvery * latIndex;

		//経度の方向に分割しながら線を書く
		for (uint32_t lonIndex = 0; lonIndex < kSubdivision; ++lonIndex)
		{
			
			//最初の頂点位置
			uint32_t start = (latIndex * kSubdivision + lonIndex) * 6;

			float lon = lonIndex * kLonEvery;

		
			
			//頂点にデータを入力する	頂点a
			vertexData_[start].position.x = std::cos(lat) * std::cos(lon);
			vertexData_[start].position.y = std::sin(lat);
			vertexData_[start].position.z = std::cos(lat) * std::sin(lon);
			vertexData_[start].position.w = 1.0f;

			vertexData_[start].texcoord.x = float(lonIndex) / float(kSubdivision);
			vertexData_[start].texcoord.y = 1.0f - float(latIndex) / float(kSubdivision);

			vertexData_[start].normal.x = vertexData_[start].position.x;
			vertexData_[start].normal.y = vertexData_[start].position.y;
			vertexData_[start].normal.z = vertexData_[start].position.z;


			//頂点b
			vertexData_[start + 1].position.x = std::cos(lat + kLatEvery) * std::cos(lon);
			vertexData_[start + 1].position.y = std::sin(lat + kLatEvery);
			vertexData_[start + 1].position.z = std::cos(lat + kLatEvery) * std::sin(lon);
			vertexData_[start + 1].position.w = 1.0f;
			
			vertexData_[start + 1].texcoord.x = float(lonIndex) / float(kSubdivision);
			vertexData_[start + 1].texcoord.y = 1.0f - float(latIndex + 1) / float(kSubdivision);
			
			vertexData_[start + 1].normal.x = vertexData_[start + 1].position.x;
			vertexData_[start + 1].normal.y = vertexData_[start + 1].position.y;
			vertexData_[start + 1].normal.z = vertexData_[start + 1].position.z;

			//頂点c
			vertexData_[start + 2].position.x = std::cos(lat) * std::cos(lon + kLonEvery);
			vertexData_[start + 2].position.y = std::sin(lat);
			vertexData_[start + 2].position.z = std::cos(lat) * std::sin(lon + kLonEvery);
			vertexData_[start + 2].position.w = 1.0f;
			
			vertexData_[start + 2].texcoord.x = float(lonIndex + 1) / float(kSubdivision);
			vertexData_[start + 2].texcoord.y = 1.0f - float(latIndex) / float(kSubdivision);
			
			vertexData_[start + 2].normal.x = vertexData_[start + 2].position.x;
			vertexData_[start + 2].normal.y = vertexData_[start + 2].position.y;
			vertexData_[start + 2].normal.z = vertexData_[start + 2].position.z;

			//頂点d
			vertexData_[start + 3].position.x = std::cos(lat) * std::cos(lon + kLonEvery);
			vertexData_[start + 3].position.y = std::sin(lat);
			vertexData_[start + 3].position.z = std::cos(lat) * std::sin(lon + kLonEvery);
			vertexData_[start + 3].position.w = 1.0f;
			
			vertexData_[start + 3].texcoord.x = float(lonIndex + 1) / float(kSubdivision);
			vertexData_[start + 3].texcoord.y = 1.0f - float(latIndex) / float(kSubdivision);
			
			vertexData_[start + 3].normal.x = vertexData_[start + 3].position.x;
			vertexData_[start + 3].normal.y = vertexData_[start + 3].position.y;
			vertexData_[start + 3].normal.z = vertexData_[start + 3].position.z;
			
			//頂点e
			vertexData_[start + 4].position.x = std::cos(lat + kLatEvery) * std::cos(lon);
			vertexData_[start + 4].position.y = std::sin(lat + kLatEvery);
			vertexData_[start + 4].position.z = std::cos(lat + kLatEvery) * std::sin(lon);
			vertexData_[start + 4].position.w = 1.0f;
			
			vertexData_[start + 4].texcoord.x = float(lonIndex) / float(kSubdivision);
			vertexData_[start + 4].texcoord.y = 1.0f - float(latIndex + 1) / float(kSubdivision);
			
			vertexData_[start + 4].normal.x = vertexData_[start + 4].position.x;
			vertexData_[start + 4].normal.y = vertexData_[start + 4].position.y;
			vertexData_[start + 4].normal.z = vertexData_[start + 4].position.z;
			
			//頂点f
			vertexData_[start + 5].position.x = std::cos(lat + kLatEvery) * std::cos(lon + kLonEvery);
			vertexData_[start + 5].position.y = std::sin(lat + kLatEvery);
			vertexData_[start + 5].position.z = std::cos(lat + kLatEvery) * std::sin(lon + kLonEvery);
			vertexData_[start + 5].position.w = 1.0f;
			
			vertexData_[start + 5].texcoord.x = float(lonIndex + 1) / float(kSubdivision);
			vertexData_[start + 5].texcoord.y = 1.0f - float(latIndex + 1) / float(kSubdivision);
			
			vertexData_[start + 5].normal.x = vertexData_[start + 5].position.x;
			vertexData_[start + 5].normal.y = vertexData_[start + 5].position.y;
			vertexData_[start + 5].normal.z = vertexData_[start + 5].position.z;

		}
	}

	materialData_->color = { 1.0f,1.0f,1.0f,1.0f };

	//Lightingを有効にする
	materialData_->enableLighting = true;
	
	materialData_->uvTransform = MakeIdentity4x4();

	transform_ =
	{
		{1.0f,1.0f,1.0f},
		{0.0f,0.0f,0.0f},
		{0.0f,0.0f,0.0f}
	};

	cameraTransform_ =
	{
		{1.0f, 1.0f, 1.0f },
		{0.0f, 0.0f, 0.0f },
		{0.0f, 0.0f, -10.0f}
	};

	//ライトのデフォルト値

	lightData_->color = { 1.0f,1.0f,1.0f,1.0f };
	lightData_->direction = { -1.0f,-1.0f,1.0f };
	lightData_->intensity = 1.0f;

}

void Sphere::Update()
{
	transform_.rotate.y += 0.01f;

	Matrix4x4 worldMatrix = MakeAffinMatrix(transform_.scale, transform_.rotate, transform_.translate);

	Matrix4x4 cameraMatrix = MakeAffinMatrix(cameraTransform_.scale, cameraTransform_.rotate, cameraTransform_.translate);
	Matrix4x4 viewMatrix = Inverse(cameraMatrix);
	Matrix4x4 projectionMatrix = MakePerspectiveFovMatrix(0.45f, float(kClientWidth_) / float(kClientHeight_), 0.1f, 100.0f);
	//WVPMatrixを作る
	Matrix4x4 worldViewProjectionMatrix = Multiply(worldMatrix, Multiply(viewMatrix, projectionMatrix));
	wvpData_->WVP = worldViewProjectionMatrix;
	wvpData_->World = worldMatrix;

#ifdef _DEBUG
	ImGui::Begin("texture");
	ImGui::Checkbox("useMonsterBall", &useMonsterBall);

	float direction[] = { lightData_->direction.x,lightData_->direction.y,lightData_->direction.z };
	ImGui::SliderFloat3("lightDirection", direction, -1.0f, 1.0f);

	lightData_->direction.x = direction[0];
	lightData_->direction.y = direction[1];
	lightData_->direction.z = direction[2];
	ImGui::End();
#endif // _DEBUG


	
}

void Sphere::Draw()
{
	//VBVを設定
	dxCommon_->GetCommandList()->IASetVertexBuffers(0, 1, &vertexBufferView_);
	//形状を設定。PS0にせっていしているものとはまた別。同じものを設定する
	dxCommon_->GetCommandList()->IASetPrimitiveTopology(D3D_PRIMITIVE_TOPOLOGY_TRIANGLELIST);
	//マテリアルCBufferの場所を設定
	dxCommon_->GetCommandList()->SetGraphicsRootConstantBufferView(0, materialResource_->GetGPUVirtualAddress());
	dxCommon_->GetCommandList()->SetGraphicsRootConstantBufferView(3, lightResource_->GetGPUVirtualAddress());
	dxCommon_->GetCommandList()->SetGraphicsRootConstantBufferView(1, wvpResource_->GetGPUVirtualAddress());
	
	// SRVのDescriptorTableの先頭を設定。
	dxCommon_->GetCommandList()->SetGraphicsRootDescriptorTable(2, texture_->GetGPUHandle(textureHandle_));
	//描画
	dxCommon_->GetCommandList()->DrawInstanced(totalVertex, 1, 0, 0);

}


/*=====================================*/
/* 　　　　   プライベートメソッド　　　    */
/*=====================================*/

/// <summary>
/// 頂点のバッファの取得
/// </summary>
void Sphere::VertexBuffer()
{
	vertexResource_ = engine_->CreateBufferResource(sizeof(VertexData) * totalVertex);	//頂点用のデータ
	//リソースの先頭のアドレスから使う
	vertexBufferView_.BufferLocation = vertexResource_->GetGPUVirtualAddress();
	//使用するリソースのサイズは頂点3つ分のサイズ
	vertexBufferView_.SizeInBytes = sizeof(VertexData) * totalVertex;
	//1頂点当たりのサイズ
	vertexBufferView_.StrideInBytes = sizeof(VertexData);
	//書き込むためのアドレスを取得
	vertexResource_->Map(0, nullptr, reinterpret_cast<void**>(&vertexData_));

}

/// <summary>
/// マテリアルのバッファの取得
/// </summary>
void Sphere::MaterialBuffer()
{

	materialResource_ = engine_->CreateBufferResource(sizeof(Material));	//マテリアル用のデータ
	//書き込むためのアドレスを取得
	materialResource_->Map(0, nullptr, reinterpret_cast<void**>(&materialData_));

}

/// <summary>
/// wvpのバッファの取得
/// </summary>
void Sphere::WvpBuffer()
{
	//トランスフォーメーションマトリックス用のリソースを作る
	wvpResource_ = engine_->CreateBufferResource(sizeof(TransformationMatrix));
	//書き込むためのアドレスを取得
	wvpResource_->Map(0, nullptr, reinterpret_cast<void**>(&wvpData_));
	//単位行列を書き込んでおく
	wvpData_->WVP = MakeIdentity4x4();

}


void Sphere::LightBuffer()
{
	lightResource_ = engine_->CreateBufferResource(sizeof(DirectionalLight));
	lightResource_->Map(0, nullptr, reinterpret_cast<void**>(&lightData_));
}