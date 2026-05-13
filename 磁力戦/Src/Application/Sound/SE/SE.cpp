#include "SE.h"

C_SoundEffect::C_SoundEffect()
{
	////インスタンス生成時になんでもいいから音を読み込む(音量変更時のエラーを防ぐため)
	//se = std::make_shared<KdSoundEffect>();
	//se->Load("Assets/Sound/SoundEffects/Player/se_bubble_pop02.wav");
	//seInst = se->CreateInstance(false);
	//seInst->SetVolume(SEvol);

}


void C_SoundEffect::SetSound(SEtype soundE)
{
	std::shared_ptr<KdSoundEffect> se_;
	se_ = std::make_shared<KdSoundEffect>();

	switch (soundE)	//引数（ヘッダーのenum）で鳴らす効果音を変更
	{
	
		break;
	}

	std::shared_ptr<KdSoundInstance> sei;
	sei = se_->CreateInstance(false);
	seInstVec.push_back(sei);

	if (seInst->IsPlay() == false)
	{
		seInst = se->CreateInstance(false);
		seInst->SetVolume(SEvol);
	}
}

void C_SoundEffect::PlaySE()
{
	for (auto v = seInstVec.begin();v != seInstVec.end();)
	{
		(*v)->SetVolume(SEvol);
		if ((*v)->IsPlay() == false)
		{
			(*v)->Play();
			v = seInstVec.erase(v);
			if (seInstVec.size() == 0)break;
		}
		else
		{
			v++;
		}
	}

}

void C_SoundEffect::SetVolume(float vol)
{
	SEvol = vol;
	seInst->SetVolume(SEvol);
}
