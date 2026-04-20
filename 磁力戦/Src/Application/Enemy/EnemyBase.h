#pragma once
#include "EnemyInfo.h"

class C_EnemyBase
{
public:

	C_EnemyBase(){}
	~C_EnemyBase(){}

	Math::Vector2 GetPos() const { return enemy.Pos; }
	bool GetIsLockOn() { return isLockOn; }
protected:

	S_Enemy enemy;

	bool isLockOn = false;	//ロックオンされたかどうか
};