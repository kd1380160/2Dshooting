#include "Player.h"
#include"../Bullet/BulletManager.h"
#include "../Scene.h"


C_Player::C_Player()
{
	player.Pos = { 0,-200 };
	player.Move = { 0,0 };
	shotCnt = 0;
	player.Hp = PLAYER_MAX_HP;
	isInvincible = false;
	playerAlpha = 1.0f;
	invincibleCnt = 0;
	player.Color = { 1,1,1,1 };
}

void C_Player::Init()
{
	player.Pos = { 0,-200 };
	player.Move = { 0,0 };
	shotCnt = 0;
	animCnt = 0;
	player.Hp = PLAYER_MAX_HP;
	isInvincible = false;
	playerAlpha = 1.0f;
}

void C_Player::Update()
{
	animCnt++;
	if (animCnt >= 12)
	{
		animCnt = 0;
	}
	
	player.Move = { 0,0 };

	KeyProcess();

	//座標確定
	player.Pos += player.Move;

	if (BULLET_MGR.PlayerHitCHeck(player.Pos, PLAYER_RADIUS))
	{
		if (!isInvincible)
		{
			player.Hp -= 1;
			if (player.Hp <= 0)player.Hp = 0;
			isInvincible = true;
		}
	}

	

	//無敵時間の点滅
	if (isInvincible)
	{
		invincibleCnt++;

		if (invincibleCnt % 7 == 0)
		{
			if (playerAlpha == 1.0f)
			{
				playerAlpha = 0.2f;
				player.Color = { 0.8,0.8,0.8,playerAlpha };
			}
			else if (playerAlpha == 0.2f)
			{
				playerAlpha = 1.0f;
				player.Color = { 6,6,6,playerAlpha };
			}
		}

		//120fで無敵解除
		if (invincibleCnt >= 120)
		{
			isInvincible = false;
			playerAlpha = 1.0f;
			invincibleCnt = 0;
			player.Color = { 1,1,1,playerAlpha };
		}
	}

	if (SCENE_MGR.GetNowWave() == Boss)
	{
		if (ENEMY_MGR.GetBossHp() > 0)
		{
			//通常弾発射
			ShotNormalBullet();
		}
	}
	else
	{
		ShotNormalBullet();
	}
	

	//行列作成
	player.Scale = Math::Matrix::CreateScale(2, 2, 1);
	player.Trans = Math::Matrix::CreateTranslation(player.Pos.x, player.Pos.y, 0);
	player.Mat = player.Scale * player.Trans;

	Math::Matrix trans,scale;
	trans= Math::Matrix::CreateTranslation(player.Pos.x, player.Pos.y - 11, 0);
	scale = Math::Matrix::CreateScale(2, 2, 1);
	engineBaseMat = scale * trans;

	engineMat = scale * trans;
}

void C_Player::Draw()
{
	//player.Color = { 1,1,1,playerAlpha };
	Math::Color color = { 2,2,2,playerAlpha };
	//プレイヤー
	if (player.Hp > 0)
	{
		SHADER.m_spriteShader.SetMatrix(engineBaseMat);
		SHADER.m_spriteShader.DrawTex(player.EngineBaseTex, Math::Rectangle{ 0,0,48,48 }, &color);

		SHADER.m_spriteShader.SetMatrix(player.Mat);
		SHADER.m_spriteShader.DrawTex(player.Tex, Math::Rectangle{ 0,0,48,48 },&player.Color);

		SHADER.m_spriteShader.SetMatrix(engineBaseMat);
		SHADER.m_spriteShader.DrawTex(player.EngineTex, Math::Rectangle{ 48*(animCnt/4),0,48,48}, &player.Color);

		
	}
}

void C_Player::ShotNormalBullet()
{
	shotCnt++;
	if (shotCnt >= 15)
	{
		BULLET_MGR.ShotNormalBullet(player.Pos);
		shotCnt = 0;
	}


	


}

void C_Player::KeyProcess()
{
	//WASDで上下左右移動
	if (GetAsyncKeyState('W') & 0x8000)	player.Move.y += 4;
	if (GetAsyncKeyState('S') & 0x8000)	player.Move.y += -4;
	if (GetAsyncKeyState('D') & 0x8000)	player.Move.x += 5;
	if (GetAsyncKeyState('A') & 0x8000)	player.Move.x += -5;
}
