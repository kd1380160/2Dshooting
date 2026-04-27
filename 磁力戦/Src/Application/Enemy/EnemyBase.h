#pragma once
#include "EnemyInfo.h"

class C_EnemyBase
{
public:

	C_EnemyBase(){}
	~C_EnemyBase(){}

	Math::Vector2 GetPos() const { return enemy.Pos; }
	bool GetIsLockOn() { return isLockOn; }
	bool GetFinishAnim() const { return enemy.isFinishAnim; }
protected:

	S_Enemy enemy;

	bool isLockOn = false;	//ロックオンされたかどうか
};