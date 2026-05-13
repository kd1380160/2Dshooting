#pragma once

enum SEtype {
	
	SEnum
};

class C_SoundEffect	//シングルトン
{
public:

	void SetSound(SEtype se);	//鳴らす効果音をセットする
	void PlaySE();				//効果音を再生する

	void SetVolume(float vol);

	float* GetVolume() { return &SEvol; }
	float Getvolume() { return SEvol; }

	static C_SoundEffect& GetInstance()
	{
		static C_SoundEffect instance;
		return instance;
	}
private:

	C_SoundEffect();

	//SE用
	//vector<std::shared_ptr<KdSoundEffect>>* se=NULL;
	std::vector<std::shared_ptr<KdSoundInstance>>  seInstVec;

	std::shared_ptr<KdSoundEffect> se;
	std::shared_ptr<KdSoundInstance> seInst;
	float  SEvol;	//音量調節用(効果音)

};

#define SE C_SoundEffect::GetInstance()
