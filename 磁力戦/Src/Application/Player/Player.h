#pragma once
#include "PlayerInfo.h"
#include "../Bullet/NormalBullet.h"

class C_Player
{
public:

	C_Player();

	void Init();
	void Update();
	void Draw();

	void ShotNormalBullet();//通常弾発射
	void KeyProcess();//キー操作処理

	//セッター
	void SetPlayerTex(KdTexture* tex) { player.Tex = tex; }
	void SetPlayerEngineTex(KdTexture* tex) { player.EngineTex = tex; }
	void SetPlayerEngineBaseTex(KdTexture* tex) { player.EngineBaseTex = tex; }

	//ゲッター
	Math::Vector2 GetPlayerPos() { return player.Pos; }
	bool GetCanStartGame() const { return canStartGame; }
	int GetPlayerRadius()const { return PLAYER_RADIUS; }
	bool GetisInvincible()const { return isInvincible; }
	int GetPlayerHp() const { return player.Hp; }
private:

	//プレイヤー構造体
	S_player player;
	
	Math::Matrix engineBaseMat;
	Math::Matrix engineMat;

	int shotCnt;
	int animCnt;
	int finishAnimCnt;

	const int PLAYER_MAX_HP = 4;
	const int PLAYER_RADIUS = 24;
	float playerAlpha;
	bool isInvincible;
	bool canStartGame;
	int invincibleCnt;
};