#include "EffectManager.h"

void C_EffectManager::Init()
{
	bulletEx.clear();
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

	
}

void C_EffectManager::Draw()
{
	for (auto& d : bulletEx)
	{
		d.Draw();
	}
}

void C_EffectManager::SpawnBulletExplosion(Math::Vector2 pos)
{
	bulletEx.push_back(C_BulletExplosion(&bulletExplosionTex,{pos.x+(rand()%81-40),pos.y + (rand() % 81 - 40) }));
}

void C_EffectManager::Release()
{
	bulletEx.clear();

	bulletExplosionTex.Release();
}
