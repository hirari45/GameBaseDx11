#include "Tank.h"
#include "Engine/Model.h"
#include "Engine/Input.h"
#include "Engine/Debug.h"
#include "Ground.h"

namespace
{
	XMVECTOR vFront = { 0, 0, 1, 0 };//タンクの前方向ベクトル
	const float moveSpeed = 0.1f;
	enum
}

//タンクのボディを表すクラス
Tank::Tank(GameObject* parent)
	:GameObject(parent, "Tank"), hModel_(-1)
{
}

void Tank::Initialize()
{
	hModel_ = Model::Load("Tankbody.fbx");
	assert(hModel_);
}

void Tank::Update()
{
	/////////////
	switch (camType_)
	{
	case FIXED_CAM:
		Camera::SetTarget(XMFLOAT3(0, 0, 0));
		Camera::SetPosition(XMFLOAT3(0, 20, -30));
		break;
	case TPS_CAM:

		break;
	case TPS_CAMROT:

		break;
	case FPS_CAM:

		break;
	}
	//Aで左、Dで右
	if (Input::IsKey(DIK_A))
	{
		transform_.rotate_.y -= 1.0f;
	}
	if (Input::IsKey(DIK_D))
	{
		transform_.rotate_.y += 1.0f;
	}
	Debug::Log("Yangle=");
	Debug::Log(transform_.rotate_.y, true);
	//wキーを押している間、前に進む
	if (Input::IsKey(DIK_W))
	{
		XMVECTOR vPos = XMLoadFloat3(&transform_.position_);
		XMMATRIX matRot = XMMatrixRotationY(XMConvertToRadians(transform_.rotate_.y));//Y軸回転行列を作る
		//XMVector3TransformCoordは、ベクトル行列を変換する関数、
		XMVECTOR vMove = XMVector3TransformCoord(vFront, matRot);
		vPos = vPos + moveSpeed * vMove;
		XMStoreFloat3(&transform_.position_, vPos);
	}

	//レイキャストして、浮いてたら、地面まで落とす
	RayCastData data;
	data.start = transform_.position_;
	data.start.y = 0.0f;//地面は0より下に掘られて作られている。そうじゃないときはもっと上から！
	data.dir = { 0, -1, 0 };//真下に例を飛ばす
	Ground* pGround = (Ground*)FindObject("Ground");//ground
	int hGroundModel = pGround->GetModelHandele();//ground
	Model::RayCast(hGroundModel, &data);//

	if (data.hit == true)
	{
		transform_.position_.y = - data.dist;
	}


	
}

void Tank::Draw()
{
	Model::SetTransform(hModel_, transform_);
	Model::Draw(hModel_);
}

void Tank::Release()
{
}
