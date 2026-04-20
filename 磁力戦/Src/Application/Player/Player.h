#pragma once
#include "PlayerInfo.h"
#include "../Bullet/NormalBullet.h"

class C_Player
{
public:

	void Init();
	void Update();
	void Draw();

	void ShotNormalBullet();//通常弾発射
	void KeyProcess();//キー操作処理

	//セッター
	void SetPlayerTex(KdTexture* tex) { player.Tex = tex; }

	//ゲッター
	Math::Vector2 GetPlayerPos() { return player.Pos; }

private:

	//プレイヤー構造体
	S_player player;
	
	int shotCnt;

	
};