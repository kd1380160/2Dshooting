#include "EnemyManager.h"
#include"../Scene.h"

void C_EnemyManager::Draw()
{
	for (int i = 0;i < ENEMY1_MAX;i++)
	{
		if (enemy1[i] != nullptr)
		{
			enemy1[i]->Draw();
		}
	}

	if (boss!=nullptr)
	{
		boss->Draw();
	}
}

void C_EnemyManager::Init()
{
	isBoss = false;
	isCallBoss = false;
	enemyKillCnt = 0;
	returnPosCnt = 0;
	enemy1Tex.Load("Assets/Image/Enemy/enemy.png");
	bossTex.Load("Assets/Image/Enemy/Boss.png");
}

void C_EnemyManager::Update()
{
	if (enemyKillCnt < 10)
	{
		for (int i = 0;i < ENEMY1_MAX;i++)
		{
			if (enemy1[i] == nullptr)
			{
				enemy1[i] = new C_Enemy1(&enemy1Tex, i);
				break;
			}
		}
	}
	else
	{
		if (!isCallBoss)
		{
			for (int i = 0;i < ENEMY1_MAX;i++)
			{
				if (enemy1[i] != nullptr)
				{
					break;
				}

				if (i == ENEMY1_MAX - 1)
				{
					isBoss = true;	
					boss = new C_Boss(&bossTex);
					isCallBoss = true;
				}
			}
		}
	}

	for (int i = 0;i < ENEMY1_MAX;i++)
	{
		if (enemy1[i] != nullptr)
		{
			enemy1[i]->Update(SCENE.GetPlayer()->GetPlayerPos());
			if (enemy1[i]->GetBulletHitCheck())
			{
				delete enemy1[i];
				enemy1[i] = nullptr;
				enemyKillCnt++;
			}
		}
	}

	

	if (boss != nullptr)
	{
		boss->Update();
		

		if (boss->GetBossHp() <= 0)
		{
			delete boss;
			boss = nullptr;
		}
	}

	if (GetAsyncKeyState(VK_LBUTTON) & 0x8000)
	{
		if (!isClick)
		{
			isClick = true;
			for (int i = 0, j = 0;i < ENEMY1_MAX;i++)
			{
				LockOnEnemyPos[i] = { 0,-500 };
				if (enemy1[i] != nullptr)
				{
					if (enemy1[i]->GetIsLockOn())
					{
						LockOnEnemyPos[j] = enemy1[i]->GetPos();
						j++;
					}
				}
			}
		}
	}
	else
	{
		isClick = false;
	}


}

void C_EnemyManager::Release()
{
	enemy1Tex.Release();
	bossTex.Release();
}

Math::Vector2 C_EnemyManager::GetEnemy1Pos()
{
	

	while (1)
	{
		if (!(LockOnEnemyPos[0].x == 0 && LockOnEnemyPos[0].y == -500)&&returnPosCnt==0)
		{
			returnPosCnt++;
			return LockOnEnemyPos[0];
		}
		else if (!(LockOnEnemyPos[1].x == 0 && LockOnEnemyPos[1].y == -500) && returnPosCnt == 1 )
		{
			returnPosCnt++;
			return LockOnEnemyPos[1];
		}
		else if (!(LockOnEnemyPos[2].x == 0 && LockOnEnemyPos[2].y == -500) && returnPosCnt == 2)
		{
			returnPosCnt = 0;
			return LockOnEnemyPos[2];
		}
		else
		{
			returnPosCnt = 0;
		}
	}


	/*if (enemy1[0] != nullptr&&enemy1[0]->GetIsLockOn())
	{

		return enemy1[0]->GetPos();
	}
	else if (enemy1[1] != nullptr && enemy1[1]->GetIsLockOn())
	{
		return enemy1[1]->GetPos();
	}
	else if (enemy1[2] != nullptr && enemy1[2]->GetIsLockOn())
	{
		return enemy1[2]->GetPos();
	}
	else
	{
		return { 0,0 };
	}*/

}
