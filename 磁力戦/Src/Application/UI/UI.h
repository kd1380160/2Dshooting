#pragma once

class C_UI
{
public:

	C_UI();
	~C_UI();

	void Init();
	void Update();
	void Draw();

private:

	static const int LIFE_MAX = 3;

	bool isInvincible;

	const float HEART_SIZE = 3.0f;
	KdTexture heartTex;
	Math::Matrix heartMat[LIFE_MAX];
	Math::Vector2 heartPos[LIFE_MAX] = { {-50,-300},{0,-300},{50,-300} };
	int life;
	int heartAnimCnt[LIFE_MAX];
	bool isDecreaseHeart[LIFE_MAX];
	bool isFinishHeartAnim[LIFE_MAX];

	KdTexture heartBackTex;
	Math::Matrix heartBackMat[LIFE_MAX];
	
public:
	static C_UI& GetInstance()
	{
		static C_UI instance;
		return instance;
	}
};
#define UI C_UI::GetInstance()