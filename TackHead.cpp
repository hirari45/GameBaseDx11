#include "TackHead.h"
#include "Engine/Model.h"
#include "Engine/Input.h"
#include "Engine/Debug.h"


TackHead::TackHead(GameObject* parent)
	:GameObject(parent, "TackHead"), hModel_(-1)
{
}

void TackHead::Initialize()

{
	hModel_ = Model::Load("TankHead.fbx");
	assert(hModel_);
}

void TackHead::Update()
{
	XMVECTOR vPos = XMLoadFloat3(&transform_.position_);
	XMMATRIX matRot = XMMatrixRotationY(XMConvertToRadians(transform_.rotate_.y));//Y軸回転行列を作る
	//XMVector3TransformCoordは、ベクトル行列を変換する関数、
	XMVECTOR vMove = XMVector3TransformCoord(vFront, matRot);

}

void TackHead::Draw()
{
	Model::SetTransform(hModel_, transform_);
	Model::Draw(hModel_);
}

void TackHead::Release()
{
}
