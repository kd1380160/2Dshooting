#pragma once

class C_Result
{
public:

	C_Result();
	~C_Result();

	enum Score {
		S,
		A,
		B
	};

	void Init();
	void Update();
	void Draw();
	void ScoreCheck();

	float GetShakeAmount() { return shakeAmount; }
	KdTexture* GetNumberTex() { return &numberTex; }
private:

	Score rank;

	const float NUMBER_SIZE = 8.0f;
	const float CLEARTIME_TEXT_SIZE = 2.0f;
	float clearSize;
	float LclickSize;
	float RclickSize;
	float scoreSize;

	bool isLClick;
	bool isRClick;
	bool isBlight;
	bool isFinishCounting;
	bool isShow;
	bool isShowScore;
	bool isShake;
	bool isBigScore;
	bool isSmallScore;
	KdTexture numberTex;
	KdTexture clearTex;
	KdTexture clearTimeTex;
	KdTexture lightTex;
	KdTexture LclickTex;
	KdTexture RclickTex;
	KdTexture SscoreTex;
	KdTexture AscoreTex;
	KdTexture BscoreTex;

	Math::Matrix clearTimeMat[5];
	Math::Matrix clearTimeTextMat;
	Math::Matrix clearMat;
	Math::Matrix lightMat;
	Math::Matrix scoreLightMat;
	Math::Matrix choiceLightMat[2];
	Math::Matrix scoreMat;
	Math::Matrix LclickMat;
	Math::Matrix RclickMat;
	Math::Vector2 RclickPos;
	Math::Vector2 LclickPos;
	Math::Vector2 scoreLightPos;
	

	Math::Color timeColor;

	float clearAlpha;
	float lightAlpha;
	float lightAlphaAdd;
	float choiceLightAlpha;
	float choiceLightAlphaAdd;
	float textAlpha;
	float textAlphaAdd;
	float scoreLightAlpha;
	int time;
	int timeCnt;
	int minute;
	int second;
	int shakeCnt;
	float shakeAmount;
};