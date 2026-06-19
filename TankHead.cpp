#include "TankHead.h"
#include "Engine/Model.h"
#include "Engine/Input.h"
#include "Engine/Debug.h"
#include "Bullet.h"


TankHead::TankHead(GameObject* parent)
	:GameObject(parent, "TankHead"), hModel_(-1)
{
}

void TankHead::Initialize()
{
	hModel_ = Model::Load("TankHead.fbx");
	assert(hModel_);
}

void TankHead::Update()
{
	//XMVECTOR vPos = XMLoadFloat3(&transform_.position_);
	//XMMATRIX matRot = XMMatrixRotationY(XMConvertToRadians(transform_.rotate_.y));//Y軸回転行列を作る
	//XMVector3TransformCoordは、ベクトル行列を変換する関数、
	//XMVECTOR vMove = XMVector3TransformCoord(vFront, matRot);
	if (Input::IsKey(DIK_LEFT))
	{
		transform_.rotate_.y -= 2.0f;
	}
	if (Input::IsKey(DIK_RIGHT))
	{
		transform_.rotate_.y += 2.0f;
	}

	if (Input::IsKeyDown(DIK_SPACE))
	{
		XMFLOAT3 cannonTop = Model::GetBonePosition(hModel_, "Top");
		XMFLOAT3 cannonRoot = Model::GetBonePosition(hModel_, "Root");
		XMVECTOR vTop = XMLoadFloat3(&cannonTop);
		XMVECTOR vRoot = XMLoadFloat3(&cannonRoot);
		XMVECTOR vMove = vTop - vRoot;
		vMove = 0.2f * vMove;
		XMFLOAT3 move;
		XMStoreFloat3(&move, vMove);

		//弾を生成する
		Bullet* pBullet = Instantiate<Bullet>(GetParent()->GetParent());
		pBullet->SetMoveVector(move);
		pBullet->SetPosition(cannonTop);
	}
}

void TankHead::Draw()
{
	Model::SetTransform(hModel_, transform_);
	Model::Draw(hModel_);
}

void TankHead::Release()
{
}
