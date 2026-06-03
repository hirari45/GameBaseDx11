#include "Tank.h"
#include "Engine/Model.h"
#include "Engine/Input.h"

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
	//Aで左、Dで右
	if (Input::IsKey(DIK_A))
	{
		transform_.rotate_.y -= 1.0f;
	}
	if (Input::IsKey(DIK_D))
	{
		transform_.rotate_.y += 1.0f;
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
