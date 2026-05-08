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
	bool GetIsLockOnAnim() { return isFinishLockOnAnim; }
	bool GetFinishAnim() const { return enemy.isFinishAnim; }
	int GetRadius()const { return enemy.Radius; }
protected:

	S_Enemy enemy;
	static const int LOCKON_DIVISION_NUM = 4;
	Math::Matrix lockOnMat[LOCKON_DIVISION_NUM];
	Math::Vector2 lockOnPos[LOCKON_DIVISION_NUM] = { {-650,370},{650,370},{-650,-370},{650,-370} };
	Math::Vector2 lockOnMoveAmount = {};
	
	int lockOnReductionCnt = 0;
	int lockOnBlinkingCnt=0;
	float lockOnSize = 7.0f;
	bool isFinishLockOnAnim=false;
	bool isLockOn = false;	//ロックオンされたかどうか
	bool isReduction = false;
	bool isFinishReduction = false;
};