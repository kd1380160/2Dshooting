#pragma once

class C_UI
{
public:

	C_UI();
	~C_UI();

	void Init();
	void Update();
	void Draw();

	void ShakeEnergy();
private:

	static const int LIFE_MAX = 4;

	bool isInvincible;

	const float ENERGY_SIZE_X = 4.0f;
	const float ENERGY_SIZE_Y = 7.0f;
	KdTexture energyTex;
	KdTexture redEnergyTex;
	KdTexture redEnergyBlockTex;
	Math::Matrix energyMat;
	Math::Matrix redEnergyBlockMat;
	Math::Vector2 energyPos = {0,-300};
	Math::Vector2 redEnergyBlockPos = {94,-300};
	Math::Color energyColor;
	int life;
	float energyAlpha;
	float redEnergyBlockAlpha;
	bool isRedBlockDisappear;

	KdTexture SunTex;
	Math::Matrix SunMat;
	Math::Vector2 SunPos = { -95,-300 };
	float sunAlpha;
	float sunCnt;
	
	//揺らす用
	int shakeLock;
	bool isShake;
	int shakeCnt;


public:
	static C_UI& GetInstance()
	{
		static C_UI instance;
		return instance;
	}
};
#define UI C_UI::GetInstance()