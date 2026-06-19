#include "Enemy.h"
#include "Engine/Model.h"
#include "Engine/Input.h"
#include "Engine/Debug.h"
#include "Ground.h"

Enemy::Enemy(GameObject* parent)
	:GameObject(parent, "Enemy"), hModel_(-1)
{
}

void Enemy::Initialize()
{
	hModel_ = Model::Load("Enemy.fbx");
	assert(hModel_);

	float x = (rand() % 600 - 300) / 10.0f; // -30.0～30.0
	float z = (rand() % 600 - 300) / 10.0f; // -30.0～30.0
	transform_.position_ = XMFLOAT3(x, 0.0f, z);

	BoxCollider* collider = new BoxCollider(XMFLOAT3(0.0f, 0.0f, 0.0f), 1.0f);
	AddCollider(collider);

}

void Enemy::Update()
{
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
		transform_.position_.y = -data.dist;
	}
}

void Enemy::Draw()
{
	Model::SetTransform(hModel_, transform_);
	Model::Draw(hModel_);
}

void Enemy::Release()
{
}
