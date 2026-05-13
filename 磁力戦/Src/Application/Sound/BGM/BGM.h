#pragma once

enum BGMtype {
	
	BGMnum
};

class C_BGM
{
public:

	void Update();

	void SetBGM(BGMtype bgm);
	void PlayBGM();
	void StopBGM();

	void FadeOut();
	void FadeOn();

	void SetVolume(float vol);
	void SetMemorize(float memorize);

	float* GetVolume() { return &BGMvol; }
	float  Getvolume() { return BGMvol; }

	static C_BGM& GetInstance()
	{
		static C_BGM instance;
		return instance;
	}
private:

	//BGM用
	std::shared_ptr<KdSoundEffect>		  bgm;
	std::shared_ptr<KdSoundInstance>  bgmInst;

	float BGMvol;		 //音量調節用(BGM)
	float memorizeBGMvol;//音量を記憶させておく変数
	bool  isFadeOut;	 //フェードアウト用

	C_BGM();
};

#define BGM C_BGM::GetInstance()
