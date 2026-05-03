#pragma once

class C_Tutorial
{
public:

	enum WindowPage
	{
		page1,
		page2
	};

	C_Tutorial();
	~C_Tutorial() { Release(); }

	void Init();
	void Update();
	void Draw();
	void Release();

	bool GetIsShowWindow()  const	{ return isWindow; }		//ウィンドウ表示中かどうか
	bool GetIsFinishPage2() const   { return isFinishPage2; }	//２ページ目の表示が終わったかどうか

private:

	WindowPage page;

	bool isLClick;
	bool isWindow;
	bool isFinishWindow;
	bool isPage1;
	bool isFinishPage1;
	bool isPage2;
	bool isFinishPage2;
	bool canStartSceneChange;

	KdTexture explainBackTex;
	KdTexture tutorialTex;
	KdTexture canInhaleTex;
	KdTexture cantInhaleTex;
	KdTexture goNextPageTex;
	KdTexture downArrowTex;
	KdTexture lockOnTex;
	KdTexture shotTex;
	

	Math::Matrix explainBackMat;
	Math::Matrix tutorialMat;
	Math::Matrix canInhaleMat;
	Math::Matrix cantInhaleMat;
	Math::Matrix canInhaleBulletMat;
	Math::Matrix cantInhaleBulletMat;
	Math::Matrix goNextPageMat;
	Math::Matrix enemy1Mat[2];
	Math::Matrix lockonMat;
	Math::Matrix downArrowMat;
	Math::Matrix lockonTextMat;
	Math::Matrix shotMat;

	float windowSize;
	int lockOnBlinkingCnt = 0;
	int purgeCnt;
	int sceneChangeCnt;
};