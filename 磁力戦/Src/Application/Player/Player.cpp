#include "Player.h"
#include"../Bullet/BulletManager.h"

void C_Player::Init()
{
	player.Pos = { 0,-200 };
	player.Move = { 0,0 };
	shotCnt = 0;
}

void C_Player::Update()
{
	player.Move = { 0,0 };

	KeyProcess();

	//座標確定
	player.Pos += player.Move;

	
	//通常弾発射
	ShotNormalBullet();
	
	

	//行列作成
	player.Scale = Math::Matrix::CreateScale(1, 1, 1);
	player.Trans = Math::Matrix::CreateTranslation(player.Pos.x, player.Pos.y, 0);
	player.Mat = player.Scale * player.Trans;
}

void C_Player::Draw()
{
	//プレイヤー
	SHADER.m_spriteShader.SetMatrix(player.Mat);
	SHADER.m_spriteShader.DrawTex(player.Tex, Math::Rectangle{ 0,0,64,64 });
}

void C_Player::ShotNormalBullet()
{
	shotCnt++;
	if (shotCnt >= 15)
	{
		BULLET_MGR.ShotNormalBullet(player.Pos);
		shotCnt = 0;
	}


	


}

void C_Player::KeyProcess()
{
	//WASDで上下左右移動
	if (GetAsyncKeyState('W') & 0x8000)	player.Move.y += 4;
	if (GetAsyncKeyState('S') & 0x8000)	player.Move.y += -4;
	if (GetAsyncKeyState('D') & 0x8000)	player.Move.x += 5;
	if (GetAsyncKeyState('A') & 0x8000)	player.Move.x += -5;
}
