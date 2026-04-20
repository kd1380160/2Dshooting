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

	for (int i = 0;i < ENEMY2_MAX;i++)
	{
		if (enemy2[i] != nullptr)
		{
			enemy2[i]->Draw();
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
	isInterval = false;
	enemyKillCnt = 0;
	returnPosCnt = 0;

	for (int i = 0;i < ENEMY1_MAX;i++)
	{
		if (enemy1[i] != nullptr)
		{
			delete enemy1[i];
			enemy1[i] = nullptr;
		}
	}

	for (int i = 0;i < ENEMY2_MAX;i++)
	{
		if (enemy2[i] != nullptr)
		{
			delete enemy2[i];
			enemy2[i] = nullptr;
		}
	}

	if (boss != nullptr)
	{
		delete boss;
		boss = nullptr;
	}
}

void C_EnemyManager::Update()
{
	WaveInterval();

	switch (SCENE_MGR.GetNowWave())
	{
	case Wave1:

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

			for (int i = 0;i < ENEMY1_MAX;i++)
			{
				if (enemy1[i] != nullptr)
				{
					break;
				}

				if (i == ENEMY1_MAX - 1)
				{

					isInterval = true;
					//SCENE_MGR.SetNowWave(Wave2);
					//isBoss = true;	
					//boss = new C_Boss(&bossTex);
					//isCallBoss = true;
					//enemyKillCnt = 0;
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
		break;
	case Wave2:

		if (enemyKillCnt < 10)
		{
			for (int i = 0;i < ENEMY2_MAX;i++)
			{
				if (enemy2[i] == nullptr)
				{
					enemy2[i] = new C_Enemy2(&enemy2Tex, i);
					break;
				}
			}
		}
		else
		{

			for (int i = 0;i < ENEMY2_MAX;i++)
			{
				if (enemy2[i] != nullptr)
				{
					break;
				}

				if (i == ENEMY2_MAX - 1)
				{

					isInterval = true;
					//SCENE_MGR.SetNowWave(Wave2);
					//isBoss = true;	
					//boss = new C_Boss(&bossTex);
					//isCallBoss = true;
					//enemyKillCnt = 0;
				}
			}

		}

		for (int i = 0;i < ENEMY2_MAX;i++)
		{
			if (enemy2[i] != nullptr)
			{
				enemy2[i]->Update(SCENE.GetPlayer()->GetPlayerPos());
				if (enemy2[i]->GetBulletHitCheck())
				{
					delete enemy2[i];
					enemy2[i] = nullptr;
					enemyKillCnt++;
				}
			}
		}





		if (GetAsyncKeyState(VK_LBUTTON) & 0x8000)
		{
			if (!isClick)
			{
				isClick = true;
				for (int i = 0, j = 0;i < ENEMY2_MAX;i++)
				{
					LockOnEnemyPos[i] = { 0,-500 };
					if (enemy2[i] != nullptr)
					{
						if (enemy2[i]->GetIsLockOn())
						{
							LockOnEnemyPos[j] = enemy2[i]->GetPos();
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

		break;
	case Wave3:
		break;
	case Wave4:
		break;
	case Wave5:
		break;
	case Boss:

		if (boss != nullptr)
		{
			boss->Update();


			if (boss->GetBossHp() <= 0)
			{
				delete boss;
				boss = nullptr;
			}
		}
		break;
	}
	


}

void C_EnemyManager::Release()
{
	for (int i = 0;i < ENEMY1_MAX;i++)
	{
		if (enemy1[i] != nullptr)
		{
			delete enemy1[i];
			enemy1[i] = nullptr;
		}
	}

	for (int i = 0;i < ENEMY2_MAX;i++)
	{
		if (enemy2[i] != nullptr)
		{
			delete enemy2[i];
			enemy2[i] = nullptr;
		}
	}

	if (boss != nullptr)
	{
		delete boss;
		boss = nullptr;
	}

	enemy1Tex.Release();
	enemy2Tex.Release();
	bossTex.Release();
}

void C_EnemyManager::WaveInterval()
{
	if (isInterval)
	{
		intervalCnt++;
		if (intervalCnt >= INTERVAL)
		{
			intervalCnt = 0;
			isInterval = false;
			enemyKillCnt = 0;
			switch (SCENE_MGR.GetNowWave())
			{
			case Wave1:
				SCENE_MGR.SetNowWave(Wave2);
				break;
			case Wave2:
				SCENE_MGR.SetNowWave(Wave3);
				break;
			case Wave3:
				SCENE_MGR.SetNowWave(Wave4);
				break;
			case Wave4:
				SCENE_MGR.SetNowWave(Wave5);
				break;
			case Wave5:
				SCENE_MGR.SetNowWave(Boss);
				break;
			}
			
		}
	}
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
