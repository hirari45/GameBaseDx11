#include "Bullet.h"
#include "Engine/Model.h"
#include "Engine/Input.h"
#include "Engine/Debug.h"

namespace
{
	const float GRAVITY = 0.005f;
}

Bullet::Bullet(GameObject* parent)
	:GameObject(parent, "Bullet"), hModel_(-1), move_(XMFLOAT3(0, 0, 0))
{
}

void Bullet::Initialize()
{
	hModel_ = Model::Load("Bullet.fbx");
	assert(hModel_);
	gravity_ = GRAVITY;

	SphereCollider* collider = new SphereCollider(XMFLOAT3(0.0f, 0.0f, 0.0f), 1.0f);
	AddCollider(collider);
}

void Bullet::Update()
{
	//transform_.position_ = transform_.position_ + move_;
	XMVECTOR vPos = XMLoadFloat3(&transform_.position_);
	move_.y -= gravity_;
	XMVECTOR vMove = XMLoadFloat3(&move_);
	vPos = vPos + vMove;
	XMStoreFloat3(&transform_.position_, vPos);
	//transform_.position_.x += move_.x;
	//transform_.position_.y += move_.y;
	//transform_.position_.z += move_.z;
	if (transform_.position_.z > 50.0f || transform_.position_.z < -50.0f
		|| transform_.position_.x>50.0f || transform_.position_.x < -50.0f)
	{
		KillMe();
	}

}

void Bullet::Draw()
{
	Model::SetTransform(hModel_, transform_);
	Model::Draw(hModel_);
}

void Bullet::Release()
{
}
