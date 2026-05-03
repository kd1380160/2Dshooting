#pragma once

class C_Cursor
{
public:

	C_Cursor();
	~C_Cursor();

	void Init();
	void Update();
	void Draw();


private:

	KdTexture	 cursorTex;
	Math::Matrix cursorMat;
	float		 cursorSize;
	bool		 isLclick;
	int          cursorCnt;
};