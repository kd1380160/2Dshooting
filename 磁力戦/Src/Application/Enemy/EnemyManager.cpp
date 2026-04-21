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

	for (int i = 0;i < ENEMY3_MAX;i++)
	{
		if (enemy3[i] != nullptr)
		{
			enemy3[i]->Draw();
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

	for (int i = 0;i < ENEMY3_MAX;i++)
	{
		if (enemy3[i] != nullptr)
		{
			delete enemy3[i];
			enemy3[i] = nullptr;
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
				if (enemy1[i] != nullptr)break;

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
					LockOnEnemy1Pos[i] = { 0,-500 };
					if (enemy1[i] != nullptr)
					{
						if (enemy1[i]->GetIsLockOn())
						{
							LockOnEnemy1Pos[j] = enemy1[i]->GetPos();
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
				if (enemy2[i] != nullptr)break;

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
					LockOnEnemy2Pos[i] = { 0,-500 };
					if (enemy2[i] != nullptr)
					{
						if (enemy2[i]->GetIsLockOn())
						{
							LockOnEnemy2Pos[j] = enemy2[i]->GetPos();
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
		if (enemyKillCnt < 10)
		{
			for (int i = 0;i < ENEMY3_MAX;i++)
			{
				if (enemy3[i] == nullptr)
				{
					enemy3[i] = new C_Enemy3(&enemy3Tex, i);
					break;
				}
			}
		}
		else
		{
			for (int i = 0;i < ENEMY3_MAX;i++)
			{
				if (enemy3[i] != nullptr)break;

				if (i == ENEMY3_MAX - 1)
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

		for (int i = 0;i < ENEMY3_MAX;i++)
		{
			if (enemy3[i] != nullptr)
			{
				enemy3[i]->Update(SCENE.GetPlayer()->GetPlayerPos());
				if (enemy3[i]->GetBulletHitCheck())
				{
					delete enemy3[i];
					enemy3[i] = nullptr;
					enemyKillCnt++;
				}
			}
		}

		if (GetAsyncKeyState(VK_LBUTTON) & 0x8000)
		{
			if (!isClick)
			{
				isClick = true;
				for (int i = 0, j = 0;i < ENEMY3_MAX;i++)
				{
					LockOnEnemy3Pos[i] = { 0,-500 };
					if (enemy3[i] != nullptr)
					{
						if (enemy3[i]->GetIsLockOn())
						{
							LockOnEnemy3Pos[j] = enemy3[i]->GetPos();
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

	for (int i = 0;i < ENEMY3_MAX;i++)
	{
		if (enemy3[i] != nullptr)
		{
			delete enemy3[i];
			enemy3[i] = nullptr;
		}
	}

	if (boss != nullptr)
	{
		delete boss;
		boss = nullptr;
	}

	enemy1Tex.Release();
	enemy2Tex.Release();
	enemy3Tex.Release();
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
		if (!(LockOnEnemy1Pos[0].x == 0 && LockOnEnemy1Pos[0].y == -500)&&returnPosCnt==0)
		{
			returnPosCnt++;
			return LockOnEnemy1Pos[0];
		}
		else if (!(LockOnEnemy1Pos[1].x == 0 && LockOnEnemy1Pos[1].y == -500) && returnPosCnt == 1 )
		{
			returnPosCnt++;
			return LockOnEnemy1Pos[1];
		}
		else if (!(LockOnEnemy1Pos[2].x == 0 && LockOnEnemy1Pos[2].y == -500) && returnPosCnt == 2)
		{
			returnPosCnt = 0;
			return LockOnEnemy1Pos[2];
		}
		else
		{
			returnPosCnt = 0;
		}
	}
}

Math::Vector2 C_EnemyManager::GetEnemy2Pos()
{
	while (1)
	{
		if (!(LockOnEnemy2Pos[0].x == 0 && LockOnEnemy2Pos[0].y == -500) && returnPosCnt == 0)
		{
			returnPosCnt++;
			return LockOnEnemy2Pos[0];
		}
		else if (!(LockOnEnemy2Pos[1].x == 0 && LockOnEnemy2Pos[1].y == -500) && returnPosCnt == 1)
		{
			returnPosCnt++;
			return LockOnEnemy2Pos[1];
		}
		else if (!(LockOnEnemy2Pos[2].x == 0 && LockOnEnemy2Pos[2].y == -500) && returnPosCnt == 2)
		{
			returnPosCnt++;
			return LockOnEnemy2Pos[2];
		}
		else if (!(LockOnEnemy2Pos[3].x == 0 && LockOnEnemy2Pos[3].y == -500) && returnPosCnt == 3)
		{
			returnPosCnt++;
			return LockOnEnemy2Pos[3];
		}
		else if (!(LockOnEnemy2Pos[4].x == 0 && LockOnEnemy2Pos[4].y == -500) && returnPosCnt == 4)
		{
			returnPosCnt = 0;
			return LockOnEnemy2Pos[4];
		}
		else
		{
			returnPosCnt = 0;
		}
	}
}

Math::Vector2 C_EnemyManager::GetEnemy3Pos()
{
	while (1)
	{
		if (!(LockOnEnemy3Pos[0].x == 0 && LockOnEnemy3Pos[0].y == -500) && returnPosCnt == 0)
		{
			returnPosCnt++;
			return LockOnEnemy3Pos[0];
		}
		else if (!(LockOnEnemy2Pos[1].x == 0 && LockOnEnemy3Pos[1].y == -500) && returnPosCnt == 1)
		{
			returnPosCnt++;
			return LockOnEnemy3Pos[1];
		}
		else if (!(LockOnEnemy3Pos[2].x == 0 && LockOnEnemy3Pos[2].y == -500) && returnPosCnt == 2)
		{
			returnPosCnt++;
			return LockOnEnemy3Pos[2];
		}
		else if (!(LockOnEnemy3Pos[3].x == 0 && LockOnEnemy3Pos[3].y == -500) && returnPosCnt == 3)
		{
			returnPosCnt=0;
			return LockOnEnemy3Pos[3];
		}
		else
		{
			returnPosCnt = 0;
		}
	}
	
}

bool C_EnemyManager::GetEnemy3Annihilation()
{
	for(int i=0;i<ENEMY3_MAX;i++)
	{
		if (enemy3[i] != nullptr)
		{
			return false;
		}
	}

	return true;
}
