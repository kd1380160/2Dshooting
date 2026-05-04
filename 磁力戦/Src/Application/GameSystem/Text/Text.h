#pragma once

class C_Text
{
public:

	C_Text();
	~C_Text();

	void Init();
	void Update();
	void Draw();

	void ChangeWave(int nextwave);
	bool GetIsFinishDirection() { return isFinishDirection; }
private:

	bool isChangingWave;
	bool isUp;
	bool isFinishDirection;

	KdTexture shotTex;	
	KdTexture waveTex;
	KdTexture finalTex;
	Math::Matrix shotMat;
	Math::Matrix waveMat;
	Math::Matrix numberMat;

	Math::Vector2 wavePos;
	float shotAlpha;
	float shotAlphaAdd;
	float waveAlpha;
	float waveAlphaAdd;
	int waveCnt;
	int nextWave;
};