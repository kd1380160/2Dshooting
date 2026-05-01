#include "BulletExplosion.h"

C_BulletExplosion::C_BulletExplosion(KdTexture* explosiontex, Math::Vector2 pos)
{
	tex = explosiontex;
	exPos = pos;
	animXCnt = 0;
	animYCnt = 0;
	isAnimFinish = false;
}

void C_BulletExplosion::Update()
{
	animXCnt++;

	if (animXCnt >= 6)
	{
		animXCnt = 0;
		animYCnt++;

		if (animYCnt >= 4)
		{
			animYCnt = 0;
			isAnimFinish = true;
		}
	}

	Math::Matrix trans, scale;
	trans = Math::Matrix::CreateTranslation(exPos.x, exPos.y, 0);
	scale = Math::Matrix::CreateScale(SIZE,SIZE,1);
	mat = scale * trans;
}

void C_BulletExplosion::Draw()
{
	SHADER.m_spriteShader.SetMatrix(mat);
	SHADER.m_spriteShader.DrawTex(tex, Math::Rectangle{ 32*(animXCnt/2),32*(animYCnt),32,32});
}
