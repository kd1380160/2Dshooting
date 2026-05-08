#pragma once
#include <list>
#include "BulletExplosion.h"
#include "EnemyDebri/EnemyDebri.h"
#include "EmitHeat/EmitHeat.h"

using namespace std;

class C_EffectManager
{
public:

	void Init();
	void Update();
	void Draw();

	void SpawnBulletExplosion(Math::Vector2 pos);
	void SpawnEmitHeat(Math::Vector2 pos,Math::Color color);
	void SpawnEnemyDebri(Math::Vector2 pos, Math::Color color);
	void Release();

private:

	KdTexture bulletExplosionTex;
	std::list<C_BulletExplosion> bulletEx;

	KdTexture enemyDebriTex;
	std::list<C_EnemyDebri> enemyDebri;

	KdTexture smokeTex;
	std::list<C_EmitHeat> emitHeat;
private:

	C_EffectManager() {
		smokeTex.Load("Assets/Image/Effect/smoke.png");
		bulletExplosionTex.Load("Assets/Image/Effect/BulletExplosion.png");
		enemyDebriTex.Load("Assets/Image/Effect/debri.png");
	}

public:
	static C_EffectManager& GetInstance()
	{
		static C_EffectManager instance;
		return instance;
	}
};

#define EFFECT_MGR C_EffectManager::GetInstance()


