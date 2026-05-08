#include "EmitHeat.h"

C_EmitHeat::C_EmitHeat(KdTexture* heattex, Math::Vector2 pos,Math::Color color)
{
	tex = heattex;
	heatPos = pos;
	//heatPos.x += (rand() % 30 - 15) / 10.0f;
	heatMove = {(float)((rand()%51-25)/10.0f),(float)((rand()%21-50)/10.f)};
	//heatMove.y = {-10};
	alpha = 0.9f;

	size = 0.5f;
	degree = rand() % 361 - 1;
	heatColor = { 1,1,1 };
	lifeTime = 60;
}

void C_EmitHeat::Update()
{
	float g=1.0f, b = 1.0f;

	lifeTime--;
	if (lifeTime <= 0)lifeTime = 0;

	if(lifeTime<30)
	{ 
		g = lifeTime * 0.03;
	}

	if (lifeTime < 50)
	{
		b = 0.0f;
	}
	else
	{
		b = 0.1f * (60 - lifeTime);
	}
	heatColor = { 1.0f,g,b };


	heatMove.y *= 0.99f;
	heatPos += heatMove;
	alpha -= 0.01;
	if (alpha <= 0.0f)alpha = 0.0f;

	size += 0.01f;
	if (size <= 0.0f)size = 0.0f;

	Math::Matrix trans, scale, rotate;

	rotate = Math::Matrix::CreateRotationZ(DirectX::XMConvertToRadians(degree));
	trans = Math::Matrix::CreateTranslation(heatPos.x,heatPos.y, 0);
	scale = Math::Matrix::CreateScale(size, size, 1);
	mat = scale * rotate * trans;
	//mat = scale * trans;
}

void C_EmitHeat::Draw()
{
	D3D.GetInstance().SetBlendState(BlendMode::Add);
	Math::Color color = { heatColor.R(),heatColor.G(),heatColor.B(),alpha };
	SHADER.m_spriteShader.SetMatrix(mat);
	SHADER.m_spriteShader.DrawTex(tex, Math::Rectangle{ 0,0,64,64 }, &color);
	D3D.GetInstance().SetBlendState(BlendMode::Alpha);
}

bool C_EmitHeat::GetIsFinish()
{
	return false;
}
