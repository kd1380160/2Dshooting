#include "Player.h"
#include"../Bullet/BulletManager.h"
#include "../Scene.h"
#include "../Transition/Transition.h"


C_Player::C_Player()
{
	player.Pos = { 0,-500 };
	player.Move = { 0,2.5 };
	shotCnt = 0;
	animCnt = 0;
	player.Hp = PLAYER_MAX_HP;
	isInvincible = false;
	canStartGame = false;
	isDead = false;
	isFinishExpAnim = false;
	isLight = false;
	isRecoil = false;
	isShotMagBullet = false;
	cantShot_Debug = false;
	playerAlpha = 1.0f;
	lightAlpha = 0.0f;
	lightAlphaAdd = 0.1f;
	recoil = -5.0f;
	invincibleCnt = 0;
	expAnimXCnt = 0;
	expAnimYCnt = 0;
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
	//player.Hp = 1;

	isShake = false;
	isInvincible = false;
	canStartGame = false;
	isDead = false;
	isLight = false;
	isFinishExpAnim = false;
	isRecoil = false;
	isShotMagBullet = false;
	isFinish = false;
	cantShot_Debug = false;
	playerAlpha = 1.0f;
	lightAlpha = 0.0f;
	lightAlphaAdd = 0.1f;
	recoil = -5.0f;
	invincibleCnt = 0;
	expAnimXCnt = 0;
	expAnimYCnt = 0;
	expBeforeCnt = 0;
	shakeAmount = 0;
	shakeCnt = 0;
	player.Color = { 1,1,1,1 };
}

void C_Player::Update()
{


	animCnt++;
	if (animCnt >= 12)
	{
		animCnt = 0;
	}

	if (!TRANSITION.GetIsTransition())
	{
		if (canStartGame)
		{


			if (!ENEMY_MGR.GetIsBossDead())
			{
				//WASD移動の処理	
				KeyProcess();
			}

			Recoil();

			if (BULLET_MGR.PlayerHitCHeck(player.Pos, PLAYER_RADIUS))
			{
				if (!isInvincible)
				{
					player.Hp -= 1;
					if (player.Hp <= 0)
					{
						player.Hp = 0;
					}
					else
					{
						isInvincible = true;
						isShake = true;
					}
				}
			}

			if (ENEMY_MGR.PlayerEnemyHitCheck(player.Pos, PLAYER_RADIUS))
			{
				if (!isInvincible)
				{
					player.Hp -= 1;
					if (player.Hp <= 0)player.Hp = 0;
					isInvincible = true;
					isShake = true;
				}
			}

			if (isShake)
			{
				if (isShotMagBullet)
				{
					if (shakeCnt == 0)shakeAmount = 10;
				}
				else
				{
					if (shakeCnt == 0)shakeAmount = 8;
				}

				shakeCnt++;
				if (shakeCnt % 3 == 0)
				{
					shakeAmount *= -0.8;
					if (shakeCnt == 21)
					{
						shakeAmount = 0;
						shakeCnt = 0;
						isShake = false;
						isShotMagBullet = false;
					}
				}
			}




			if (player.Hp <= 0)
			{
				isDead = true;

			}

			if (isDead)
			{
				expBeforeCnt++;

				if (!isInvincible && expBeforeCnt > 40)
				{
					isInvincible = true;
				}

				if (expBeforeCnt > 120)
				{
					isShake = true;
					expAnimXCnt++;

					if (expAnimXCnt >= 20)
					{
						expAnimXCnt = 0;
						expAnimYCnt++;

						if (expAnimYCnt >= 4)
						{
							expAnimYCnt = 0;
							isFinishExpAnim = true;
						}
					}
				}
			}

			if (isFinishExpAnim)
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


			if (!cantShot_Debug)
			{
				if (SCENE_MGR.GetIsWave1TextFin())
				{
					if (player.Hp > 0)
					{
						if (SCENE_MGR.GetNowWave() == Boss)
						{
							if (ENEMY_MGR.GetBossHp() > 0)
							{
								//通常弾発射
								ShotNormalBullet();
							}
						}
						else if (SCENE_MGR.GetNowScene() == Tutorial) {}
						else
						{
							ShotNormalBullet();
						}
					}
				}
			}

			if (!isLight)
			{
				if (BULLET_MGR.GetIsMagBulletMax())
				{
					isLight = true;
				}
			}
			else
			{
				lightAlpha += lightAlphaAdd;
				if (lightAlpha >= 1.0f)
				{
					lightAlphaAdd *= -1;
				}
				if (lightAlpha < 0.0f)
				{
					isLight = false;
					lightAlpha = 0.0f;
					lightAlphaAdd *= -1;
				}
			}
		}
		else
		{
			if (player.Pos.y >= -200)
			{
				player.Pos.y = -200;
				canStartGame = true;
				SCENE_MGR.StartTimeCnt();
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

			if (!isFinish)
			{
				if (player.Pos.y >= 500.0f)
				{
					TRANSITION.Start(Result);
					isFinish = true;
				}
			}
		}
		else
		{
			player.Pos += player.Move * player.Speed;
		
			if (player.Pos.y >= 360 - PLAYER_RADIUS)
			{
				player.Pos.y = 360 - PLAYER_RADIUS;
			}
		}


	}
	//=============発表会用================

	//体力ＭＡＸ
	if (GetAsyncKeyState('Z') & 0x8000)
	{
		player.Hp = PLAYER_MAX_HP;
	}

	//通常弾を撃たないように(トグルスイッチ)
	if (GetAsyncKeyState('X') & 0x8000)
	{
		if (!isX_Debug)
		{
			isX_Debug = true;
			if (!cantShot_Debug)
			{
				cantShot_Debug = true;
			}
			else
			{
				cantShot_Debug = false;
			}
		}
	}
	else
	{
		isX_Debug = false;
	}

	//体力を０に
	if (GetAsyncKeyState('C') & 0x8000)
	{
		if (!isC_Debug)
		{
			isC_Debug = true;
			player.Hp = 0;
		}
	}
	else
	{
		isC_Debug = false;
	}

	if (player.Pos.x <= -640 + PLAYER_RADIUS)
	{
		player.Pos.x = -640 + PLAYER_RADIUS;
	}
	else if (player.Pos.x >= 640 - PLAYER_RADIUS)
	{
		player.Pos.x = 640 - PLAYER_RADIUS;
	}

	if (player.Pos.y <= -360 + PLAYER_RADIUS+20)
	{
		player.Pos.y = -360 + PLAYER_RADIUS+20;
	}
	
	//====================================
	
	//行列作成
	player.Scale = Math::Matrix::CreateScale(2, 2, 1);
	player.Trans = Math::Matrix::CreateTranslation(player.Pos.x+shakeAmount, player.Pos.y + shakeAmount, 0);
	player.Mat = player.Scale * player.Trans;

	Math::Matrix trans, scale;

	trans = Math::Matrix::CreateTranslation(player.Pos.x , player.Pos.y + 5 , 0);
	scale = Math::Matrix::CreateScale(0.5f, 0.5f, 1);
	lightMat = scale * trans;

	trans = Math::Matrix::CreateTranslation(player.Pos.x + shakeAmount, player.Pos.y - 11 + shakeAmount, 0);
	scale = Math::Matrix::CreateScale(2, 2, 1);
	engineBaseMat = scale * trans;

	engineMat = scale * trans;

	trans = Math::Matrix::CreateTranslation(player.Pos.x + shakeAmount, player.Pos.y + shakeAmount, 0);
	scale = Math::Matrix::CreateScale(8, 8, 1);
	expMat = scale * trans;


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
		switch (player.Hp)
		{
		case 1:
			SHADER.m_spriteShader.DrawTex(player.HP1Tex, Math::Rectangle{ 0,0,48,48 }, &player.Color);
			break;
		case 2:
			SHADER.m_spriteShader.DrawTex(player.HP2Tex, Math::Rectangle{ 0,0,48,48 }, &player.Color);
			break;
		case 3:
			SHADER.m_spriteShader.DrawTex(player.HP3Tex, Math::Rectangle{ 0,0,48,48 }, &player.Color);
			break;
		case 4:
			SHADER.m_spriteShader.DrawTex(player.HP4Tex, Math::Rectangle{ 0,0,48,48 }, &player.Color);
			break;
		}

		SHADER.m_spriteShader.SetMatrix(engineBaseMat);
		SHADER.m_spriteShader.DrawTex(player.EngineTex, Math::Rectangle{ 48 * (animCnt / 4),0,48,48 }, &player.Color);

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
	else
	{
		if (expBeforeCnt <= 120)
		{
			SHADER.m_spriteShader.SetMatrix(engineBaseMat);
			SHADER.m_spriteShader.DrawTex(player.EngineBaseTex, Math::Rectangle{ 0,0,48,48 }, &color);

			SHADER.m_spriteShader.SetMatrix(player.Mat);
			SHADER.m_spriteShader.DrawTex(player.HP1Tex, Math::Rectangle{ 0,0,48,48 }, &player.Color);

			SHADER.m_spriteShader.SetMatrix(engineBaseMat);
			SHADER.m_spriteShader.DrawTex(player.EngineTex, Math::Rectangle{ 48 * 4,0,48,48 }, &player.Color);
		}
		else
		{
			SHADER.m_spriteShader.SetMatrix(expMat);
			SHADER.m_spriteShader.DrawTex(player.ExplosionTex, Math::Rectangle{ 64 * (expAnimXCnt / 5),65 * expAnimYCnt,64,64 });
		}
	}


	if (isLight)
	{
		//色のブレンド方法の設定（加算合成）
		D3D.SetBlendState(BlendMode::Add);

		color = { 4,4,4,lightAlpha };
		SHADER.m_spriteShader.SetMatrix(lightMat);
		SHADER.m_spriteShader.DrawTex(SCENE_MGR.GetGameOver()->GetSunTex(), Math::Rectangle(0, 0, 128, 128),&color);

		//色のブレンド方法の設定（合成なし）
		D3D.SetBlendState(BlendMode::Alpha);
	}
}

void C_Player::ShotNormalBullet()
{
	shotCnt++;
	if (shotCnt >= 30)
	{
		BULLET_MGR.ShotNormalBullet(player.Pos);
		shotCnt = 0;
	}
}

void C_Player::KeyProcess()
{
	player.Move = { 0,0 };
	if (!isDead)
	{
		

		//WASDで上下左右移動
		if (GetAsyncKeyState('W') & 0x8000)	player.Move.y += 1;
		if (GetAsyncKeyState('S') & 0x8000)	player.Move.y += -1;
		if (GetAsyncKeyState('D') & 0x8000)	player.Move.x += 1;
		if (GetAsyncKeyState('A') & 0x8000)	player.Move.x += -1;

		player.Move.Normalize();//正規化
	}
}

void C_Player::Recoil()
{
	if (!isRecoil)return;

	Math::Color heatColor[2] = { {0.8f,0.8f,1.0f,1},{0.8f,0.4f,0.0f,1.0f} };
	Math::Vector2 pos = {0,0};
	pos = player.Pos - pos;


	player.Pos.y += recoil;
	if (recoil < 0)
	{
		recoil += 0.3f;
	}
	else
	{
		recoil += 0.1f;
	}

	if (recoil >0.0f)
	{
		for (int i = 0;i < 50;++i)
		{
			if (i < 40)
			{
				EFFECT_MGR.SpawnEmitHeat(pos, heatColor[0]);
			}
			else
			{
				EFFECT_MGR.SpawnEmitHeat(pos, heatColor[1]);
			}
		}

		recoil = -5.0f;
		isRecoil = false;
	}
		
}

void C_Player::SetPlayerTex(KdTexture* tex, KdTexture* hp2, KdTexture* hp3, KdTexture* hp4)
{
	player.HP1Tex = tex;
	player.HP2Tex = hp2;
	player.HP3Tex = hp3;
	player.HP4Tex = hp4;
}
