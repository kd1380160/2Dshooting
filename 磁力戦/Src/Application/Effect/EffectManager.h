#pragma once
#include <list>
#include "BulletExplosion.h"
using namespace std;

class C_EffectManager
{
public:

	void Init();
	void Update();
	void Draw();

	void SpawnBulletExplosion(Math::Vector2 pos);
	void Release();

private:

	KdTexture bulletExplosionTex;
	std::list<C_BulletExplosion> bulletEx;


private:

	C_EffectManager() {
		bulletExplosionTex.Load("Assets/Image/Effect/BulletExplosion.png");
	}

public:
	static C_EffectManager& GetInstance()
	{
		static C_EffectManager instance;
		return instance;
	}
};

#define EFFECT_MGR C_EffectManager::GetInstance()


