#pragma once

class C_BackGround
{
public:

	void Init();
	void Update();
	void Draw();
	void Release();

private:

	KdTexture backgroundTex;
	Math::Vector2 backgroundPos[2];
	Math::Matrix backgroundMat[2];

private:

	C_BackGround() {}

public:
	static C_BackGround& GetInstance()
	{
		static C_BackGround instance;
		return instance;
	}
};

#define BACKGRND C_BackGround::GetInstance()

