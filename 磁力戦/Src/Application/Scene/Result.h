#pragma once

class C_Result
{
public:

	C_Result();
	~C_Result();

	void Init();
	void Update();
	void Draw();

private:

	const float NUMBER_SIZE = 8.0f;
	const float CLEARTIME_TEXT_SIZE = 2.0f;
	float clearSize;
	float LclickSize;
	float RclickSize;

	bool isLClick;
	bool isRClick;
	bool isBlight;
	bool isFinishCounting;
	KdTexture numberTex;
	KdTexture clearTex;
	KdTexture clearTimeTex;
	KdTexture lightTex;
	KdTexture LclickTex;
	KdTexture RclickTex;

	Math::Matrix clearTimeMat[5];
	Math::Matrix clearTimeTextMat;
	Math::Matrix clearMat;
	Math::Matrix lightMat;
	Math::Matrix choiceLightMat[2];
	Math::Matrix LclickMat;
	Math::Matrix RclickMat;
	Math::Vector2 RclickPos;
	Math::Vector2 LclickPos;

	Math::Color timeColor;

	float clearAlpha;
	float lightAlpha;
	float lightAlphaAdd;
	float choiceLightAlpha;
	float choiceLightAlphaAdd;
	int time;
	int timeCnt;
	int minute;
	int second;
};