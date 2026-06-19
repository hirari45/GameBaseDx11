#pragma once
#include "Engine/GameObject.h"
class TankHead :
    public GameObject
{
public:
	//コンストラクタ
	TankHead(GameObject* parent);
	~TankHead(){}//インライン定義
	//初期化
	void Initialize() override;
	//更新
	void Update() override;
	//描画
	void Draw() override;
	//開放
	void Release() override;

private:
	int hModel_;//タンクヘッドモデルのハンドル
};

