#include "BulletManager.h"
#include"../Scene.h"
void C_BulletManager::Draw()
{
	//通常弾（プレイヤー発射）
	for (int i = 0;i < NORMAL_BULLET_MAX;i++)
	{
		if (normalBullets[i] != nullptr)
		{
			normalBullets[i]->Draw();
		}
	}


	//敵1弾
	for (int i = 0;i < ENEMY1_BULLET_MAX;i++)
	{
		if (enemy1Bullets[i] != nullptr)
		{
			enemy1Bullets[i]->Draw();
		}
	}

	//敵2弾
	for (int i = 0;i < ENEMY2_BULLET_MAX;i++)
	{
		if (enemy2Bullets[i] != nullptr)
		{
			enemy2Bullets[i]->Draw();
		}
	}

	//磁力弾（プレイヤー発射）
	for (int i = 0;i < MAGNETIC_BULLET_MAX;i++)
	{
		if (magneticBullets[i] != nullptr)
		{
			magneticBullets[i]->Draw();
		}
	}

}

void C_BulletManager::Update()
{
	Math::Vector2 playerpos = SCENE.GetPlayer()->GetPlayerPos();

	for (int i = 0;i < NORMAL_BULLET_MAX;i++)
	{
		//弾が存在する場合のみ更新
		if (normalBullets[i] != nullptr)
		{
			normalBullets[i]->Update();

			if (normalBullets[i]->GetPos().y >= 400)
			{
				delete normalBullets[i];
				normalBullets[i] = nullptr;
			}
		}
	}

	for (int i = 0;i < ENEMY1_BULLET_MAX;i++)
	{
		//弾が存在する場合のみ更新
		if (enemy1Bullets[i] != nullptr)
		{
			enemy1Bullets[i]->Update(playerpos);

			if (enemy1Bullets[i]->GetIsAbsorption())
			{
				delete  enemy1Bullets[i];
				enemy1Bullets[i] = nullptr;
			
				SpawnMagBullet(playerpos);
				continue;
			}

			//画面外に出た弾は消去
			if (enemy1Bullets[i]->GetPos().y <= -400)
			{
				delete enemy1Bullets[i];
				enemy1Bullets[i] = nullptr;
			}
		}
	}

	for (int i = 0;i < ENEMY2_BULLET_MAX;i++)
	{
		//弾が存在する場合のみ更新
		if (enemy2Bullets[i] != nullptr)
		{
			enemy2Bullets[i]->Update(playerpos);

			if (enemy2Bullets[i]->GetIsAbsorption())
			{
				delete  enemy2Bullets[i];
				enemy2Bullets[i] = nullptr;

				SpawnMagBullet(playerpos);
				continue;
			}

			//画面外に出た弾は消去
			if (enemy2Bullets[i]->GetPos().y <= -400)
			{
				delete enemy2Bullets[i];
				enemy2Bullets[i] = nullptr;
			}
		}
	}

	if (GetAsyncKeyState(VK_LBUTTON) & 0x8000)
	{
		if (!isLClick)
		{
			isLClick = true;
			ShotMagBullet();
		}
	}
	else
	{
		isLClick = false;
	}

	for (int i = 0;i < MAGNETIC_BULLET_MAX;i++)
	{
		//弾が存在する場合のみ更新
		if (magneticBullets[i] != nullptr)
		{
			

			if (isLClick)
			{
				magneticBullets[i]->SetIsShotFlg(true);
				magneticBullets[i]->SetIsHomingTrue();
				//magneticBullets[i]->Update(SCENE.GetPlayer()->GetPlayerPos(), ENEMY_MGR.GetEnemy1Pos());
				//break;
			}
			magneticBullets[i]->Update(SCENE.GetPlayer()->GetPlayerPos(), {100,100});

			//画面外に出た弾は消去
			if (magneticBullets[i]->GetPos().y >= 376||magneticBullets[i]->GetPos().y<=-376
				||magneticBullets[i]->GetPos().x>=676 || magneticBullets[i]->GetPos().x <= -676)
			{
				delete magneticBullets[i];
				magneticBullets[i] = nullptr;
			}
		}
	}
}

void C_BulletManager::Init()
{
	isLClick = false;

	for (int i = 0;i < NORMAL_BULLET_MAX;i++)
	{
		if (normalBullets[i] != nullptr)
		{
			delete normalBullets[i];
			normalBullets[i] = nullptr;
		}
	}

	for (int i = 0;i < MAGNETIC_BULLET_MAX;i++)
	{
		if (magneticBullets[i] != nullptr)
		{
			delete magneticBullets[i];
			magneticBullets[i] = nullptr;
		}
	}

	for (int i = 0;i < ENEMY1_BULLET_MAX;i++)
	{
		if (enemy1Bullets[i] != nullptr)
		{
			delete enemy1Bullets[i];
			enemy1Bullets[i] = nullptr;
		}
	}

	for (int i = 0;i < ENEMY2_BULLET_MAX;i++)
	{
		if (enemy2Bullets[i] != nullptr)
		{
			delete enemy2Bullets[i];
			enemy2Bullets[i] = nullptr;
		}
	}
}

void C_BulletManager::SpawnMagBullet(Math::Vector2 enemyPos)
{
	//弾が無ければ生成
	for (int i = 0;i < MAGNETIC_BULLET_MAX;i++)
	{
		if (magneticBullets[i] == nullptr)
		{
			magneticBullets[i] = new C_MagneticBullet(&magneticBulletTex, enemyPos);
			break;
		}
	}
}

void C_BulletManager::ShotNormalBullet(Math::Vector2 playerPos)
{
	//弾が無ければ生成
	for (int i = 0;i < NORMAL_BULLET_MAX;i++)
	{
		if (normalBullets[i] == nullptr)
		{
			normalBullets[i] = new C_NormalBullet(playerPos, &normalBulletTex);
			break;
		}
	}
}

void C_BulletManager::ShotEnemy1Bullet(Math::Vector2 enemyPos)
{
	//弾が無ければ生成
	for (int i = 0;i < ENEMY1_BULLET_MAX;i++)
	{
		if (enemy1Bullets[i] == nullptr)
		{
			enemy1Bullets[i] = new C_Enemy1Bullet(&enemy1BulletTex, enemyPos);
			break;
		}
	}
}

void C_BulletManager::ShotEnemy2Bullet(Math::Vector2 enemyPos,int num)
{
	//弾が無ければ生成
	for (int i = 0;i < ENEMY2_BULLET_MAX;i++)
	{
		if (enemy2Bullets[i] == nullptr)
		{
			enemy2Bullets[i] = new C_Enemy2Bullet(&enemy2BulletTex, enemyPos,num);
			break;
		}
	}
}

void C_BulletManager::ShotMagBullet()
{
	for (int i = 0;i < MAGNETIC_BULLET_MAX;i++)
	{
		if (magneticBullets[i] != nullptr)
		{
			magneticBullets[i]->SetDestinationPos(ENEMY_MGR.GetEnemy1Pos());
			
		}
	}
}

bool  C_BulletManager::EnemyHitCheck(Math::Vector2 pos, int radius)
{
	//通常弾との当たり判定
	for (int i = 0;i < NORMAL_BULLET_MAX;i++)
	{
		//弾が存在する場合のみ更新
		if (normalBullets[i] != nullptr)
		{
			const float a = normalBullets[i]->GetPos().x - pos.x;
			const float b = normalBullets[i]->GetPos().y - pos.y;
			const float c = sqrt(a * a + b * b);
			const float sumRadius = normalBullets[i]->GetRadius() + radius;

			//当たってたらtrue
			if (c < sumRadius)
			{
				delete normalBullets[i];
				normalBullets[i] = nullptr;

				return true;
			}
		}

	}

	//磁力弾との当たり判定
	for (int i = 0;i < MAGNETIC_BULLET_MAX;i++)
	{
		//弾が存在する場合のみ更新
		if (magneticBullets[i] != nullptr)
		{
			const float a = magneticBullets[i]->GetPos().x - pos.x;
			const float b = magneticBullets[i]->GetPos().y - pos.y;
			const float c = sqrt(a * a + b * b);
			const float sumRadius = magneticBullets[i]->GetRadius() + radius;

			//当たってたらtrue
			if (c < sumRadius)
			{
				delete magneticBullets[i];
				magneticBullets[i] = nullptr;

				return true;
			}
		}

	}

	//当たってなければfalse
	return false;
}

void C_BulletManager::Release()
{
	for (int i = 0;i < NORMAL_BULLET_MAX;i++)
	{
		if (normalBullets[i] != nullptr)
		{
			delete normalBullets[i];
			normalBullets[i] = nullptr;
		}
	}

	for (int i = 0;i < MAGNETIC_BULLET_MAX;i++)
	{
		if (magneticBullets[i] != nullptr)
		{
			delete magneticBullets[i];
			magneticBullets[i] = nullptr;
		}
	}

	for (int i = 0;i < ENEMY1_BULLET_MAX;i++)
	{
		if (enemy1Bullets[i] != nullptr)
		{
			delete enemy1Bullets[i];
			enemy1Bullets[i] = nullptr;
		}
	}

	for (int i = 0;i < ENEMY2_BULLET_MAX;i++)
	{
		if (enemy2Bullets[i] != nullptr)
		{
			delete enemy2Bullets[i];
			enemy2Bullets[i] = nullptr;
		}
	}

	normalBulletTex.Release();
	magneticBulletTex.Release();
	enemy1BulletTex.Release();
	enemy2BulletTex.Release();
}
