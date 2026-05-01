#include "EnemyBase.h"

void C_EnemyBase::LockOnAnimUpdate()
{
	if (isFinishLockOnAnim)return;

	float rad;	//ラジアン
	float deg;	//ディグリー
	float a;	//底辺
	float b;	//高さ
	float distance;

	for (int i = 0;i < LOCKON_DIVISION_NUM;++i)
	{
		distance = sqrt((enemy.Pos.x-lockOnPos[i].x) * (enemy.Pos.x - lockOnPos[i].x) + (enemy.Pos.y - lockOnPos[i].y) * (enemy.Pos.y - lockOnPos[i].y));

		//目的地から元の位置を引く！
		a = enemy.Pos.x - lockOnPos[i].x;
		b = enemy.Pos.y - lockOnPos[i].y;

		//角度を求める
		rad = atan2(b, a);

		//ディグリーに直す
		deg = DirectX::XMConvertToDegrees(rad);

		//負の値を正の値に直す
		if (deg < 0)
		{
			deg += 360;
		}

		lockOnMoveAmount.x = cos(DirectX::XMConvertToRadians(deg)) * (distance/10);
		lockOnMoveAmount.y = sin(DirectX::XMConvertToRadians(deg)) * (distance/10);
	
		lockOnPos[i] += lockOnMoveAmount;

		if (distance<=20)
		{
			isFinishLockOnAnim = true;
		}
	}
	

	Math::Matrix trans, scale;
	scale = Math::Matrix::CreateScale(7, 7, 1);

	for(int i=0;i<LOCKON_DIVISION_NUM;++i)
	{ 
		trans = Math::Matrix::CreateTranslation(lockOnPos[i].x, lockOnPos[i].y, 0);	
		lockOnMat[i] = scale * trans;
	}
}

void C_EnemyBase::LockOnAnimDraw()
{
	if (isFinishLockOnAnim)return;

	Math::Color col = { 20,0,0,1 };

	for (int i = 0;i < LOCKON_DIVISION_NUM;i++)
	{
		SHADER.m_spriteShader.SetMatrix(lockOnMat[i]);
		switch (i)
		{
		case 0:
			SHADER.m_spriteShader.DrawTex(enemy.LockOnTex, Math::Rectangle{ 0,0,9,8 },&col);
			break;
		case 1:
			SHADER.m_spriteShader.DrawTex(enemy.LockOnTex, Math::Rectangle{ 8 ,0,9,8 }, &col);
			break;
		case 2:
			SHADER.m_spriteShader.DrawTex(enemy.LockOnTex, Math::Rectangle{ 0,8,9,8 }, &col);
			break;
		case 3:
			SHADER.m_spriteShader.DrawTex(enemy.LockOnTex, Math::Rectangle{ 8 ,8,9,8 }, &col);
			break;

		}
	}
}
