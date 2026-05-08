#pragma once

class C_Title
{
public:
	C_Title();
	~C_Title() { Release(); }

	void Init();
	void Update();
	void Draw();
	void Release();
private:

	static const int BULLET_MAX = 15;

	bool isClick;
	bool isChangeScene;
	bool isFinishTransition;
	bool isWpress;
	bool isApress;
	bool isSpress;
	bool isDpress;
	bool isW;
	bool isA;
	bool isS;
	bool isD;


	KdTexture MAGTex;
	KdTexture LOCKONTex;
	KdTexture startTex;
	KdTexture wTex;
	KdTexture aTex;
	KdTexture sTex;
	KdTexture dTex;

	KdTexture wPressTex;
	KdTexture aPressTex;
	KdTexture sPressTex;
	KdTexture dPressTex;

	Math::Matrix MAGMat;
	Math::Matrix LOCKONMat;
	Math::Matrix startMat;
	Math::Matrix bulletMat[BULLET_MAX];
	Math::Matrix wMat;
	Math::Matrix aMat;
	Math::Matrix sMat;
	Math::Matrix dMat;

	Math::Vector2 bulletPos[BULLET_MAX];
	Math::Vector2 bulletMove[BULLET_MAX];
	
	int titleCnt;
	int boostCnt[BULLET_MAX];
	int transitionCnt;

	float bulletSize[BULLET_MAX];
	float startTexAlpha;
	float alphaAdd;
	float bulletAlpha;
};