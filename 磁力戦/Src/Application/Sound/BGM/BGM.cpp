#include "BGM.h"

C_BGM::C_BGM() :BGMvol(0.5f), memorizeBGMvol(BGMvol)
{
	//インスタンス生成時になんでもいいから音を読み込む(音量変更時のエラーを防ぐため)
	/*bgm = std::make_shared<KdSoundEffect>();
	bgm->Load("Assets/Sound/BGM/Game/snowwhite/Boss.wav");
	bgmInst = bgm->CreateInstance(false);
	bgmInst->SetVolume(BGMvol);
	isFadeOut = false;*/
}

void C_BGM::Update()
{
	FadeOut();
}

void C_BGM::SetBGM(BGMtype bgmE)
{
	StopBGM();

	bgm = std::make_shared<KdSoundEffect>();

	switch (bgmE)
	{
	
		break;
	}

	BGMvol = memorizeBGMvol;
	bgmInst = bgm->CreateInstance(false);
	bgmInst->SetVolume(BGMvol);

	PlayBGM();
}

void C_BGM::PlayBGM()
{
	if (bgmInst->IsPlay() == false)
	{
		bgmInst->Play(true);
	}
}

void C_BGM::StopBGM()
{
	if (bgmInst->IsPlay() == true)
	{
		bgmInst->Stop();
	}
}

void C_BGM::FadeOut()
{
	if (!isFadeOut)return;

	BGMvol -= 0.02f;
	if (BGMvol < 0.0f)
	{
		BGMvol = 0.0f;
		isFadeOut = false;
	}
	//音量変更後は必ずSetVolume
	bgmInst->SetVolume(BGMvol);
}

void C_BGM::FadeOn()
{
	isFadeOut = true;
	memorizeBGMvol = BGMvol;
}

void C_BGM::SetVolume(float vol)
{
	BGMvol = vol;
	memorizeBGMvol = vol;
	bgmInst->SetVolume(BGMvol);
}

void C_BGM::SetMemorize(float memorize)
{
	memorizeBGMvol = memorize;
}
