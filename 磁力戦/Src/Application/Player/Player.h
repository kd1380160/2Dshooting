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
	void Recoil();
	void Shake() { isShake = true;isShotMagBullet = true; }

	//セッター
	void SetPlayerTex(KdTexture* tex, KdTexture* hp2, KdTexture* hp3, KdTexture* hp4);
	void SetPlayerEngineTex(KdTexture* tex) { player.EngineTex = tex; }
	void SetPlayerEngineBaseTex(KdTexture* tex) { player.EngineBaseTex = tex; }
	void SetPlayerExplosionTex(KdTexture* tex) { player.ExplosionTex = tex; }
	void SetIsRecoil(bool flg) { isRecoil = flg; }

	//ゲッター
	Math::Vector2 GetPlayerPos() { return player.Pos; }
	bool GetCanStartGame() const { return canStartGame; }
	int GetPlayerRadius()const { return PLAYER_RADIUS; }
	bool GetisInvincible()const { return isInvincible; }
	int GetPlayerHp() const { return player.Hp; }
	int GetShakeAmount()const  { return shakeAmount; }
	bool GetIsShotMagBullet() const { return isShotMagBullet; }

private:

	//プレイヤー構造体
	S_player player;
	
	Math::Matrix engineBaseMat;
	Math::Matrix engineMat;
	Math::Matrix expMat;
	Math::Matrix lightMat;

	int shotCnt;
	int animCnt;
	int finishAnimCnt;

	const int PLAYER_MAX_HP = 4;
	const int PLAYER_RADIUS = 24;
	float playerAlpha;
	float lightAlpha;
	float lightAlphaAdd;
	float recoil;
	bool isInvincible;
	bool canStartGame;
	bool isFinishExpAnim;
	bool isDead;
	bool isShake;
	bool isLight;
	bool isRecoil;
	bool isShotMagBullet;
	bool isFinish=false;
	bool cantShot_Debug;
	bool isX_Debug;
	bool isC_Debug;
	int invincibleCnt;
	int expAnimXCnt;
	int expAnimYCnt;
	int expBeforeCnt;
	int shakeCnt;
	int shakeAmount;
};