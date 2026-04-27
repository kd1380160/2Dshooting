#pragma once

class C_Title
{
public:
	C_Title();
	~C_Title() { Release(); }

	void Init();
	void Update();
	void Draw();

private:

	void Release();

	bool isClick;

	KdTexture titleTex;
	KdTexture startTex;

	Math::Matrix titleMat;
	Math::Matrix startMat;
	
	float startTexAlpha;
	float alphaAdd;
};