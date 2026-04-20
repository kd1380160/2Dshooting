#pragma once
#include"EnemyBase.h"

class C_Boss :public C_EnemyBase
{
public:
	C_Boss(KdTexture* tex);
	~C_Boss();


	void Init();
	void Update();
	void Draw();
	void Release();

	int GetBossHp() { return boss.HP; }
	void DecleaseBossHp() { boss.HP -= 1; }
private:
	S_Enemy boss;
};