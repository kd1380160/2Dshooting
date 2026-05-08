#include "EnemyDebri.h"

C_EnemyDebri::C_EnemyDebri(KdTexture* debritex, Math::Vector2 pos,Math::Color color)
{
	tex = debritex;
	debriPos = pos;
	debriMove = { (float)(rand() % 9 - 4),(float)(rand() % 11 - 4) };
	alpha = 0.9f;
	debriColor = color;
}

void C_EnemyDebri::Update()
{
	alpha -= 0.02f;
	if (alpha <= 0.0f)alpha = 0.0f;

	//debriMove.y -= 0.1f;
	debriPos += debriMove;

	Math::Matrix trans, scale,rotate;

	rotate = Math::Matrix::CreateRotationZ(DirectX::XMConvertToRadians(rand() % 361 - 1));
	trans = Math::Matrix::CreateTranslation(debriPos.x, debriPos.y, 0);
	scale = Math::Matrix::CreateScale(0.4f, 0.4f, 1);
	mat = scale *rotate* trans;
}

void C_EnemyDebri::Draw()
{
	D3D.SetBlendState(BlendMode::Add);

	Math::Color color = { debriColor.R(),debriColor.G(),debriColor.B(),alpha};
	SHADER.m_spriteShader.SetMatrix(mat);
	SHADER.m_spriteShader.DrawTex(tex, Math::Rectangle{ 0,0,64,64 },&color);

	D3D.SetBlendState(BlendMode::Alpha);
}

bool C_EnemyDebri::GetIsFinish()
{
	if (alpha == 0.0f)
	{
		return true;
	}
	else
	{
		return false;
	}
}
