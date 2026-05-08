#pragma once
#include "../Scene/SceneManager.h"

class C_Transition
{
public:

	void Init();
	void Draw();
	void Update();

	void Start(SceneList next);

	bool GetIsTransition() const { return isTransition; }
private:

	bool isTransition=false;
	bool isWhiteOut=false;
	float alpha=0.0f;
	SceneList nextScene;
	int cnt=0;
	
private:

	C_Transition() {}

public:
	static C_Transition& GetInstance()
	{
		static C_Transition instance;
		return instance;
	}
};

#define TRANSITION C_Transition::GetInstance()
