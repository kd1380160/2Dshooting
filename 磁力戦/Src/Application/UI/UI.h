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
	void ShowLeftEnemy() { canShowLeftEnemy = true; }
	void StartCntUp() { canCntUp = true; }
	void SetNextWave(int next) { nextWave = next; }
private:

	static const int LIFE_MAX = 4;

	bool isInvincible;
	bool canShowLeftEnemy;
	bool canCntUp;

	const float ENERGY_SIZE_X = 4.0f;
	const float ENERGY_SIZE_Y = 7.0f;
	KdTexture energyTex;
	KdTexture redEnergyTex;
	KdTexture redEnergyBlockTex;
	KdTexture leftEnemyTex;
	KdTexture slashTex;
	KdTexture hpTex;
	Math::Matrix energyMat;
	Math::Matrix redEnergyBlockMat;
	Math::Matrix leftEnemyMat;
	Math::Matrix numberMat[5];
	Math::Matrix hpMat;
	Math::Vector2 energyPos = {0,-320};
	Math::Vector2 redEnergyBlockPos = {94,-320};
	Math::Vector2 leftEnemyPos = { -63,-280 };
	
	Math::Color energyColor;
	int life;
	int leftEnemyNum;
	int maxEnemyNum;
	int enemyUpCnt;
	int enemyMaxUpCnt;
	int nextWave;
	float energyAlpha;
	float leftEnemyAlpha;
	float redEnergyBlockAlpha;
	bool isRedBlockDisappear;
	bool isFirstAppear=false;

	//ライト関連
	KdTexture SunTex;
	Math::Matrix SunMat;
	Math::Vector2 SunPos = { -95,-320 };
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