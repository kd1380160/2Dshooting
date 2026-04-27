#pragma once

class C_Text
{
public:

	C_Text();
	~C_Text();

	void Init();
	void Update();
	void Draw();

private:

	KdTexture shotTex;	
	Math::Matrix shotMat;
	float shotAlpha;
	float shotAlphaAdd;
};