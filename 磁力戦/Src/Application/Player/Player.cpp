#include "Player.h"
#include"../Bullet/BulletManager.h"
#include "../Scene.h"


C_Player::C_Player()
{
	player.Pos = { 0,-500 };
	player.Move = { 0,2.5 };
	shotCnt = 0;
	animCnt = 0;
	player.Hp = PLAYER_MAX_HP;
	isInvincible = false;
	canStartGame = true;
	playerAlpha = 1.0f;
	invincibleCnt = 0;
	
	player.Speed = 4;
	player.Color = { 1,1,1,1 };
}

void C_Player::Init()
{
	player.Pos = { 0,-500 };
	player.Move = { 0,2.5 };
	shotCnt = 0;
	animCnt = 0;
	finishAnimCnt = 0;
	player.Hp = PLAYER_MAX_HP;
	isInvincible = false;
	canStartGame = false;
	playerAlpha = 1.0f;
	invincibleCnt = 0;
}

void C_Player::Update()
{
	animCnt++;
	if (animCnt >= 12)
	{
		animCnt = 0;
	}


	if (canStartGame)
	{
		if (!ENEMY_MGR.GetIsBossDead())
		{
			//WASD移動の処理	
			KeyProcess();
		}

		if (BULLET_MGR.PlayerHitCHeck(player.Pos, PLAYER_RADIUS))
		{
			if (!isInvincible)
			{
				player.Hp -= 1;
				if (player.Hp <= 0)player.Hp = 0;
				isInvincible = true;
			}
		}

		if (ENEMY_MGR.PlayerEnemyHitCheck(player.Pos, PLAYER_RADIUS))
		{
			if (!isInvincible)
			{
				player.Hp -= 1;
				if (player.Hp <= 0)player.Hp = 0;
				isInvincible = true;
			}
		}

		if (player.Hp <= 0)
		{
			SCENE_MGR.SetNowScene(GameOver);
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
	}
	else
	{
		if (player.Pos.y >= -200)
		{
			player.Pos.y = -200;

			canStartGame = true;
		}
	}

	if (ENEMY_MGR.GetIsBossDead())
	{
		if (finishAnimCnt == 0)
		{
			player.Move = {};
		}

		finishAnimCnt++;


		if (finishAnimCnt >= 150)
		{
			player.Move.y += 0.05;
		}

		player.Pos += player.Move;

		if (player.Pos.y >= 900)
		{
			SCENE_MGR.SetNowScene(Result);
		}
	}
	else
	{
		player.Pos += player.Move * player.Speed;
	}


	
	//行列作成
	player.Scale = Math::Matrix::CreateScale(2, 2, 1);
	player.Trans = Math::Matrix::CreateTranslation(player.Pos.x, player.Pos.y, 0);
	player.Mat = player.Scale * player.Trans;

	Math::Matrix trans, scale;
	trans = Math::Matrix::CreateTranslation(player.Pos.x, player.Pos.y - 11, 0);
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

		//弾を引き寄せる範囲を円で表示
		if (!BULLET_MGR.GetIsJamming())
		{
			if (!ENEMY_MGR.GetIsBossDead())
			{
				//非ジャミング
				SHADER.m_spriteShader.SetMatrix(Math::Matrix::CreateTranslation(0, 0, 0));
				SHADER.m_spriteShader.DrawCircle(player.Pos.x, player.Pos.y, 100, &Math::Color(0, 0, 10, 0.7), false); // 半透明の青い線
			}
		}
		else
		{
			//ジャミング中
			SHADER.m_spriteShader.SetMatrix(Math::Matrix::CreateTranslation(0, 0, 0));
			SHADER.m_spriteShader.DrawCircle(player.Pos.x, player.Pos.y, 100, &Math::Color(10, 0, 0, 0.7), false); // 半透明の赤い線
		}

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
	player.Move = { 0,0 };

	//WASDで上下左右移動
	if (GetAsyncKeyState('W') & 0x8000)	player.Move.y = 1;
	if (GetAsyncKeyState('S') & 0x8000)	player.Move.y = -1;
	if (GetAsyncKeyState('D') & 0x8000)	player.Move.x = 1;
	if (GetAsyncKeyState('A') & 0x8000)	player.Move.x = -1;
	
	player.Move.Normalize();//正規化
}
