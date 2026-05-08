#include "EffectManager.h"

void C_EffectManager::Init()
{
	bulletEx.clear();
	enemyDebri.clear();
	emitHeat.clear();
}

void C_EffectManager::Update()
{
	for (auto& d : bulletEx)
	{
		d.Update();

	}

	for (auto itr = bulletEx.begin(); itr != bulletEx.end(); ) // ここで itr++ しない
	{
		if (itr->GetIsAnimFin())
		{
			// eraseの戻り値でイテレータを更新
			itr = bulletEx.erase(itr);
		}
		else
		{
			// 削除しなかった場合のみ、次へ進める
			itr++;
		}
	}


	for (auto& d : enemyDebri)
	{
		d.Update();
	}

	for (auto itr = enemyDebri.begin(); itr !=enemyDebri.end(); ) // ここで itr++ しない
	{
		if (itr->GetIsFinish())
		{
			// eraseの戻り値でイテレータを更新
			itr = enemyDebri.erase(itr);
		}
		else
		{
			// 削除しなかった場合のみ、次へ進める
			itr++;
		}
	}

	for (auto& d : emitHeat)
	{
		d.Update();
	}

	for (auto itr = emitHeat.begin(); itr != emitHeat.end(); ) // ここで itr++ しない
	{
		if (itr->GetIsFinish())
		{
			// eraseの戻り値でイテレータを更新
			itr = emitHeat.erase(itr);
		}
		else
		{
			// 削除しなかった場合のみ、次へ進める
			itr++;
		}
	}

	
}

void C_EffectManager::Draw()
{
	for (auto& d : bulletEx)
	{
		d.Draw();
	}

	for (auto& d : enemyDebri)
	{
		d.Draw();
	}

	for (auto& d : emitHeat)
	{
		d.Draw();
	}
}

void C_EffectManager::SpawnBulletExplosion(Math::Vector2 pos)
{
	bulletEx.push_back(C_BulletExplosion(&bulletExplosionTex,{pos.x+(rand()%81-40),pos.y + (rand() % 81 - 40) }));
}

void C_EffectManager::SpawnEmitHeat(Math::Vector2 pos,Math::Color color)
{
	emitHeat.push_back(C_EmitHeat(&smokeTex, pos,color));
}

void C_EffectManager::SpawnEnemyDebri(Math::Vector2 pos, Math::Color color)
{
	enemyDebri.push_back(C_EnemyDebri(&enemyDebriTex, pos,color));
}

void C_EffectManager::Release()
{
	bulletEx.clear();
	enemyDebri.clear();

	bulletExplosionTex.Release();
	enemyDebriTex.Release();
}
