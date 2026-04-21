#include "Enemy3.h"
#include "../Scene.h"

C_Enemy3::C_Enemy3(KdTexture* tex, int num)
{
	enemy.Tex = tex;
	//enemy.Pos = { (float)( - 300 + 200 * num),400};
	enemy.Pos = { (float)(rand() % (1280 - ENEMY_RADIUS) - 640),400 };
	enemy.Move = { 0,-10 };
	shotCnt = 0;
	isLockOn = false;
	isHit = false;
}

void C_Enemy3::Init()
{
}

void C_Enemy3::Update(Math::Vector2 playerpos)
{
	enemy.Pos += enemy.Move;
	if (enemy.Pos.y <= 200)enemy.Pos.y = 200;

	LockOn();

	shotCnt++;
	if (shotCnt >= 45)
	{
			BULLET_MGR.ShotEnemy3Bullet(enemy.Pos);
		shotCnt = 0;
	}

	if (BULLET_MGR.EnemyHitCheck(enemy.Pos, ENEMY_RADIUS))
	{
		isHit = true;
	}
	else
	{
		isHit = false;
	}

	enemy.Scale = Math::Matrix::CreateScale(2, -2, 1);
	enemy.Trans = Math::Matrix::CreateTranslation(enemy.Pos.x, enemy.Pos.y, 0);
	enemy.Mat = enemy.Scale * enemy.Trans;
}

void C_Enemy3::Draw()
{
	Math::Color col = { 1,1,1,1 };
	if (isLockOn)col = { 10,10,10,1 };

	SHADER.m_spriteShader.SetMatrix(enemy.Mat);
	SHADER.m_spriteShader.DrawTex(enemy.Tex, Math::Rectangle(0, 0, 64, 64), &col);
}

void C_Enemy3::LockOn()
{
	const float x = enemy.Pos.x - SCENE.GetMousePos().x;
	const float y = enemy.Pos.y - SCENE.GetMousePos().y;
	const float z = sqrt(x * x + y * y);

	if (z < ENEMY_RADIUS)
	{
		isLockOn = true;
	}
}
