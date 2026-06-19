#pragma once
#include "Engine/GameObject.h"
class Bullet :
    public GameObject
{
public:
	//コンストラクタ
	//引数：parent  親オブジェクト（SceneManager）
	Bullet(GameObject* parent);
	~Bullet(){}//インライン定義
	//初期化
	void Initialize() override;
	//更新
	void Update() override;
	//描画
	void Draw() override;
	//開放
	void Release() override;
	void SetMoveVector(XMFLOAT3 move) { move_ = move; }
private:
	int hModel_;
	XMFLOAT3 move_;
	float gravity_;
};

