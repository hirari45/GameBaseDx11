#include "Ground.h"
#include "Engine/Model.h"

Ground::Ground(GameObject* parent)
	:GameObject(parent, "Ground"), hModel_(-1)
{
}

/// <summary>
/// なんもしない
/// </summary>
Ground::~Ground()
{
}//デストラクタ（オブジェクトが削除され鵜r時に呼ばれる関数）

void Ground::Initialize()
{
	//モデルの読み込み
	hModel_ = Model::Load("Ground.fbx");
}

void Ground::Update()
{
}

void Ground::Draw()
{
	Model::SetTransform(hModel_, transform_);
	Model::Draw(hModel_);
}

void Ground::Release()
{
}
