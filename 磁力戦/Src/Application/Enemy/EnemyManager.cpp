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

	for (int i = 0;i < ENEMY4_MAX;i++)
	{
		if (enemy4[i] != nullptr)
		{
			enemy4[i]->Draw();
		}
	}

	for (int i = 0;i < GENERATOR_MAX;i++)
	{
		if (generator[i] != nullptr)
		{
			generator[i]->Draw();
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

	for (int i = 0;i < ENEMY4_MAX;i++)
	{
		if (enemy4[i] != nullptr)
		{
			delete enemy4[i];
			enemy4[i] = nullptr;
		}
	}

	for (int i = 0;i < GENERATOR_MAX;i++)
	{
		if (generator[i] != nullptr)
		{
			delete generator[i];
			generator[i] = nullptr;
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
	if (GetAsyncKeyState(VK_F1) & 0x8000)
	{
		for (int i = 0;i < ENEMY4_MAX;i++)
		{
			if (enemy4[i] != nullptr)
			{
				delete enemy4[i];
				enemy4[i] = nullptr;
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

		SCENE_MGR.SetNowWave(Boss);

		if (boss == nullptr)
		{
			boss = new C_Boss(&bossTex, &bossShieldTex, &bossBreakTex);
		}
		for (int i = 0;i < GENERATOR_MAX;i++)
		{
			if (generator[i] == nullptr)
			{
				generator[i] = new C_Generator(&generatorTex, i);
			}
		}
	}

	WaveInterval();

	switch (SCENE_MGR.GetNowWave())
	{
	case Wave1:

		if (enemyKillCnt < 10)
		{
			//敵1の生成
			for (int i = 0;i < ENEMY1_MAX;i++)
			{
				if (enemy1[i] == nullptr)
				{
					enemy1[i] = new C_Enemy1(&enemy1Tex, &enemy1BreakTex, i);
					break;
				}
			}
		}
		else
		{
			//敵1が全滅したら次のウェーブへ
			for (int i = 0;i < ENEMY1_MAX;i++)
			{
				if (enemy1[i] != nullptr)break;

				if (i == ENEMY1_MAX - 1)
				{
					isInterval = true;
				}
			}
		}

		for (int i = 0;i < ENEMY1_MAX;i++)
		{
			//敵1の更新
			if (enemy1[i] != nullptr)
			{
				enemy1[i]->Update(SCENE.GetPlayer()->GetPlayerPos());
				if (enemy1[i]->GetFinishAnim())
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
				for (int i = 0, j = 0;i < LOCKON_ENEMY_MAX;i++)
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
			//敵2の生成
			for (int i = 0;i < ENEMY2_MAX;i++)
			{
				if (enemy2[i] == nullptr)
				{
					enemy2[i] = new C_Enemy2(&enemy2Tex, &enemy2BreakTex, i);
					break;
				}
			}
		}
		else
		{
			//敵2が全滅したら次のウェーブへ
			for (int i = 0;i < ENEMY2_MAX;i++)
			{
				if (enemy2[i] != nullptr)break;

				if (i == ENEMY2_MAX - 1)
				{
					isInterval = true;
				}
			}
		}

		for (int i = 0;i < ENEMY2_MAX;i++)
		{
			if (enemy2[i] != nullptr)
			{
				enemy2[i]->Update(SCENE.GetPlayer()->GetPlayerPos());
				if (enemy2[i]->GetFinishAnim())
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
				for (int i = 0, j = 0;i < LOCKON_ENEMY_MAX;i++)
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
		if (enemyKillCnt < 10)
		{
			for (int i = 0;i < ENEMY3_MAX;i++)
			{
				//敵3の生成
				if (enemy3[i] == nullptr)
				{
					enemy3[i] = new C_Enemy3(&enemy3Tex, &enemy3BreakTex, i);
					break;
				}
			}

			for (int i = 0;i < ENEMY1_MAX;i++)
			{
				//敵1の生成
				if (enemy1[i] == nullptr)
				{
					enemy1[i] = new C_Enemy1(&enemy1Tex, &enemy1BreakTex, i);
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

					for (int j = 0;j < ENEMY1_MAX;j++)
					{
						if (enemy1[j] != nullptr)break;
						if (j == ENEMY1_MAX - 1)
						{
							isInterval = true;
						}
					
					}
					
				}
			}
		}

		for (int i = 0;i < ENEMY1_MAX;i++)
		{
			if (enemy1[i] != nullptr)
			{
				enemy1[i]->Update(SCENE.GetPlayer()->GetPlayerPos());
				if (enemy1[i]->GetFinishAnim())
				{
					delete enemy1[i];
					enemy1[i] = nullptr;
					enemyKillCnt++;
				}
			}
		}

		for (int i = 0;i < ENEMY3_MAX;i++)
		{
			if (enemy3[i] != nullptr)
			{
				enemy3[i]->Update(SCENE.GetPlayer()->GetPlayerPos());
				if (enemy3[i]->GetFinishAnim())
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
				for (int i = 0, j = 0;i < LOCKON_ENEMY_MAX;i++)
				{
					LockOnEnemyPos[i] = { 0,-500 };
					if (enemy3[i] != nullptr)
					{
						if (enemy3[i]->GetIsLockOn())
						{
							LockOnEnemyPos[j] = enemy3[i]->GetPos();
							j++;
						}
					}
					if(enemy1[i] != nullptr)
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
	case Wave4:
		if (enemyKillCnt < 10)
		{
			for (int i = 0;i < ENEMY4_MAX;i++)
			{
				//敵4の生成
				if (enemy4[i] == nullptr)
				{
					enemy4[i] = new C_Enemy4(&enemy4Tex, &enemy4BreakTex);
					break;
				}
			}

			for (int i = 0;i < ENEMY2_MAX;i++)
			{
				//敵2の生成
				if (enemy2[i] == nullptr)
				{
					enemy2[i] = new C_Enemy2(&enemy2Tex,&enemy2BreakTex, i);
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
					for (int j = 0;j < ENEMY4_MAX;j++)
					{
						if (enemy4[j] != nullptr)break;
						if (j == ENEMY4_MAX - 1)
						{
							isInterval = true;
						}
					}
				}
			}
		}

		for (int i = 0;i < ENEMY2_MAX;i++)
		{
			if (enemy2[i] != nullptr)
			{
				enemy2[i]->Update(SCENE.GetPlayer()->GetPlayerPos());
				if (enemy2[i]->GetFinishAnim())
				{
					delete enemy2[i];
					enemy2[i] = nullptr;
					enemyKillCnt++;
				}
			}
		}

		for (int i = 0;i < ENEMY4_MAX;i++)
		{
			if (enemy4[i] != nullptr)
			{
				enemy4[i]->Update(SCENE.GetPlayer()->GetPlayerPos());
				if (enemy4[i]->GetFinishAnim())
				{
					delete enemy4[i];
					enemy4[i] = nullptr;
					enemyKillCnt++;
				}
			}
		}
		if (GetAsyncKeyState(VK_LBUTTON) & 0x8000)
		{
			if (!isClick)
			{
				isClick = true;
				int j = 0;
				for (int i = 0;i < LOCKON_ENEMY_MAX;i++)
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
					if (enemy4[i] != nullptr)
					{
						if (enemy4[i]->GetIsLockOn())
						{
							LockOnEnemyPos[j] = enemy4[i]->GetPos();
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
	case Boss:
		for (int i = 0;i < GENERATOR_MAX;i++)
		{
			if (generator[i] != nullptr)
			{
				generator[i]->Update();
				if (generator[i]->GetHp() <= 0)
				{
					delete generator[i];
					generator[i] = nullptr;
				}
			}
		}

		if (boss != nullptr)
		{
			boss->Update(GetGeneratorHp());
			if (boss->GetIsFinishAnim()==true)
			{
				delete boss;
				boss = nullptr;
				isInterval = true;
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

	for (int i = 0;i < ENEMY4_MAX;i++)
	{
		if (enemy4[i] != nullptr)
		{
			delete enemy4[i];
			enemy4[i] = nullptr;
		}
	}

	for (int i = 0;i < GENERATOR_MAX;i++)
	{
		if (generator[i] != nullptr)
		{
			delete generator[i];
			generator[i] = nullptr;
		}
	}

	if (boss != nullptr)
	{
		delete boss;
		boss = nullptr;
	}

	enemy1Tex.Release();
	enemy1BreakTex.Release();
	enemy2Tex.Release();
	enemy2BreakTex.Release();
	enemy3Tex.Release();
	enemy3BreakTex.Release();
	enemy4Tex.Release();
	enemy4BreakTex.Release();
	generatorTex.Release();
	bossTex.Release();
	bossBreakTex.Release();
	bossShieldTex.Release();
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
				SCENE_MGR.SetNowWave(Boss);

				if (boss == nullptr)
				{
					boss = new C_Boss(&bossTex, &bossShieldTex, &bossBreakTex);
				}
				for (int i = 0;i < GENERATOR_MAX;i++)
				{
					if (generator[i] == nullptr)
					{
						generator[i] = new C_Generator(&generatorTex,i);
					}
				}
				break;
			case Boss:
				SCENE_MGR.SetNowScene(SceneList::Result);
				break;
			}
			
		}
	}
}

Math::Vector2 C_EnemyManager::GetEnemyWavePos()
{
	int cycleCnt = 0;
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
			returnPosCnt ++;
			return LockOnEnemyPos[2];
		}
		else if (!(LockOnEnemyPos[3].x == 0 && LockOnEnemyPos[3].y == -500) && returnPosCnt == 3)
		{
			returnPosCnt++;
			return LockOnEnemyPos[3];
		}
		else if (!(LockOnEnemyPos[4].x == 0 && LockOnEnemyPos[4].y == -500) && returnPosCnt == 4)
		{
			returnPosCnt = 0;
			return LockOnEnemyPos[4];
		}
		else
		{
			returnPosCnt = 0;
			cycleCnt++;
			if (cycleCnt >= 2)
			{
				return { 0,-500 };
			}
		}
	}
}

Math::Vector2 C_EnemyManager::GetEnemy4Pos(int num)
{
	return enemy4[num]->GetPos();
}

Math::Vector2 C_EnemyManager::GetGeneratorPos(int num)
{
	return generator[num]->GetPos();
}

Math::Vector2 C_EnemyManager::GetBossPos()
{
	if (boss != nullptr)
	{
		if (boss->GetIsLockOn())
		{
			return boss->GetBossPos();
		}
	}
	return {0,0};
}

bool C_EnemyManager::GetIsEnemy4Alive(int num)
{
	if (enemy4[num] != nullptr)
	{
		return true;
	}
	else
	{
		return false;
	}
}

bool C_EnemyManager::GetIsGeneratorAlive(int num)
{
	if (generator[num] != nullptr)
	{
		return true;
	}
	else
	{
		return false;
	}
}

bool C_EnemyManager::GetIsEnemyAlive(int type, int num)
{
	
	switch (type)
	{
	case 0:
		if (enemy1[num] != nullptr)
		{
			if (enemy1[num]->GetIsLockOn())
			{
				return true;
			}
		}
		break;
	case 1:
		if (enemy2[num] != nullptr)
		{
			if (enemy2[num]->GetIsLockOn())
			{
				return true;
			}
			return true;
		}
		break;
	case 2:
		if (enemy3[num] != nullptr)
		{
			if(enemy3[num]->GetIsLockOn())
			{
				return true;
			}
		}
		break;
	case 3:
		if (enemy4[num] != nullptr)
		{
			if (enemy4[num]->GetIsLockOn())
			{
				return true;
			}
		}
		break;
	}

	return false;
}

void C_EnemyManager::RegisterLockonEnemyNum()
{
	lockonCnt = 0;
	switch (SCENE_MGR.GetNowWave())
	{
	case WaveList::Wave1:
		for (int i = 0, j = 0;i < 5;i++)
		{
			lockonEnemyNumType[i][0] = -1;
			lockonEnemyNumType[i][1] = 6;
			if (enemy1[i] != nullptr)
			{
				if (enemy1[i]->GetIsLockOn())
				{
					lockonEnemyNumType[j][0] = i;
					lockonEnemyNumType[j][1] = 0;
					j++;
					lockonCnt++;
				}

			}

			if (lockonCnt >= 5)
			{
				break;
			}

		}
		break;
	case WaveList::Wave2:
		for (int i = 0, j = 0;i < 5;i++)
		{
			lockonEnemyNumType[i][0] = -1;
			lockonEnemyNumType[i][1] = 6;
			
			if (enemy2[i] != nullptr)
			{
				if (enemy2[i]->GetIsLockOn())
				{
					lockonEnemyNumType[j][0] = i;
					lockonEnemyNumType[j][1] = 1;
					j++;
					lockonCnt++;
				}
			}

			if (lockonCnt >= 5)
			{
				break;
			}

		}
		break;
	case WaveList::Wave3:
		for (int i = 0, j = 0;i < 5;i++)
		{
			lockonEnemyNumType[i][0] = -1;
			lockonEnemyNumType[i][1] = 6;
			if (enemy3[i] != nullptr)
			{
				if (enemy3[i]->GetIsLockOn())
				{
					lockonEnemyNumType[j][0] = i;
					lockonEnemyNumType[j][1] = 2;
					j++;
					lockonCnt++;
				}

			}

			if (enemy1[i] != nullptr)
			{
				if (enemy1[i]->GetIsLockOn())
				{
					lockonEnemyNumType[j][0] = i;
					lockonEnemyNumType[j][1] = 0;
					j++;
					lockonCnt++;
				}
			}

			if (lockonCnt >= 5)
			{
				break;
			}

		}
		break;
	case WaveList::Wave4:
		
		for (int i = 0, j = 0;i < 5;i++)
		{
			lockonEnemyNumType[i][0] = -1;
			lockonEnemyNumType[i][1] = 6;

			if (enemy2[i] != nullptr)
			{
				if (enemy2[i]->GetIsLockOn())
				{
					lockonEnemyNumType[j][0] = i;
					lockonEnemyNumType[j][1] = 1;
					j++;
					lockonCnt++;
				}
			}

			if (enemy4[i] != nullptr)
			{
				if (enemy4[i]->GetIsLockOn())
				{
					lockonEnemyNumType[j][0] = i;
					lockonEnemyNumType[j][1] = 3;
					j++;
					lockonCnt++;
				}

			}
		
			

			if (lockonCnt >= 5)
			{
				break;
			}

		}
		

		break;
	case Boss:
		break;
	default:
		break;
	}

}

bool C_EnemyManager::GetEnemy3Annihilation()
{
	//敵3が全滅しているかどうかを返す
	//全滅している場合はtrue,していなければ（存在していなければ）falseを返す
	for(int i=0;i<ENEMY3_MAX;i++)
	{
		if (enemy3[i] != nullptr)
		{
			return false;
		}
	}
	return true;
}

int C_EnemyManager::GetLockonEnemyNum(int num)
{
	return lockonEnemyNumType[num][0];
}

int C_EnemyManager::GetLockonEnemyType(int num)
{
	return lockonEnemyNumType[num][1];
}

int C_EnemyManager::GetGeneratorHp()
{
	int sum = 0;

	for (int i = 0;i < GENERATOR_MAX;i++)
	{
		if (generator[i] != nullptr)
		{
			sum += generator[i]->GetHp();
		}
	}
	return sum;
}

int C_EnemyManager::GetBossHp()
{
	if (boss != nullptr)
	{
		return boss->GetBossHp();
	}

	return 0;
}

bool C_EnemyManager::GetBossFinisher()
{
	if (boss != nullptr)
	{
		return boss->GetFinisher();
	}
	return false;
}

bool C_EnemyManager::GetCanShotMagBullet()
{
	if (SCENE_MGR.GetNowWave() == Boss)return true;

	for (int k = 0;k < 5;k++)
	{
		if (lockonEnemyNumType[k][0] != -1 && lockonEnemyNumType[k][1] != 6)
		{
			return true;
		}
	}
	return false;

}

Math::Vector2 C_EnemyManager::GetLockOnEnemyPos(int type, int number)
{
	if (number == 0 || number == 1 || number == 2 || number == 3 || number == 4)
	{
		//return { 500,-500 };
		switch (type)
		{
		case 0:
			if (enemy1[number] != nullptr)
			{
				if (enemy1[number]->GetIsLockOn())
				{
					return enemy1[number]->GetPos();
				}
			}
			break;
		case 1:
			if (enemy2[number] != nullptr)
			{
				if (enemy2[number]->GetIsLockOn())
				{
					return enemy2[number]->GetPos();
				}
			}
			break;
		case 2:
			if (enemy3[number] != nullptr)
			{
				if (enemy3[number]->GetIsLockOn())
				{
					return enemy3[number]->GetPos();
				}
			}
			break;
		case 3:
			if (enemy4[number] != nullptr)
			{
				if (enemy4[number]->GetIsLockOn())
				{
					return enemy4[number]->GetPos();
				}
			}
			break;

		default:
			return { -500,-500 };
			break;
		}

		return { -500,-500 };
	}
	return { -500,-500 };
}
