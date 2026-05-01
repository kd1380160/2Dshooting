#pragma once
#include "EnemyInfo.h"

class C_EnemyBase
{
public:

	C_EnemyBase(){}
	virtual ~C_EnemyBase(){}

	void LockOnAnimUpdate();
	void LockOnAnimDraw();

	Math::Vector2 GetPos() const { return enemy.Pos; }
	bool GetIsLockOn() { return isLockOn; }
	bool GetFinishAnim() const { return enemy.isFinishAnim; }
	int GetRadius()const { return enemy.Radius; }
protected:

	S_Enemy enemy;
	static const int LOCKON_DIVISION_NUM = 4;
	Math::Matrix lockOnMat[LOCKON_DIVISION_NUM];
	Math::Vector2 lockOnPos[LOCKON_DIVISION_NUM] = { {-650,370},{650,370},{-650,-370},{650,-370} };
	Math::Vector2 lockOnMoveAmount = {};
	
	int lockOnBlinkingCnt=0;
	bool isFinishLockOnAnim=false;
	bool isLockOn = false;	//ロックオンされたかどうか
};