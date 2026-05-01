#pragma once

class C_GameOver
{
public:
	C_GameOver();
	~C_GameOver();

	void Init();
	void Update();
	void Draw();

	void Release();
private:

	KdTexture tex;
	KdTexture blackBackTex;
	KdTexture retryTex;
	KdTexture LclickTex;
	KdTexture RclickTex;
	KdTexture SunTex;

	Math::Matrix mat;
	Math::Vector2 pos;

	Math::Matrix retryMat;
	Math::Vector2 retryPos;

	Math::Matrix LclickMat;
	Math::Vector2 LclickPos;

	Math::Matrix RclickMat;
	Math::Vector2 RclickPos;

	Math::Matrix SunMat[4];
	Math::Vector2 SunPos[4] = { {640,360},{-640,360},{640,-360},{-640,-360} };

	float size;
	float retrySize;
	float LclickSize;
	float RclickSize;
	float SunSize;
	float sizeAdd;
	float posAdd;
	float angle;
	float sunAlpha;
	float sunAlphaAdd;
};