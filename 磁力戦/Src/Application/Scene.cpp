#include "main.h"
#include "Scene.h"
#include "UI/UI.h"

void Scene::Draw2D()
{
	SCENE_MGR.Draw();
	
	/*for (int i = 0;i < ENEMY1_MAX;i++)
	{
		if (enemy1[i] != nullptr)
		{
			if (enemy1[i]->GetIsLockOn())
			{
				SHADER.m_spriteShader.DrawLine(enemy1[i]->GetPos().x, enemy1[i]->GetPos().x, player.GetPlayerPos().x, player.GetPlayerPos().y);
			}
		}
	}*/

	char str[80];
	sprintf_s(str, sizeof(str),"敵を倒した数: %f", GetPlayer()->GetPlayerPos().y);
	//SHADER.m_spriteShader.DrawString(-600, 300, str, Math::Vector4{ 1,1,1,1 });

	sprintf_s(str, sizeof(str), "クリアタイム: %d", SCENE_MGR.GePlayTime());
	//SHADER.m_spriteShader.DrawString(-600, 300, str, Math::Vector4{ 1,1,1,1 });

	sprintf_s(str, sizeof(str), "今のWave: %d", SCENE_MGR.GetNowWave()+1);
	//SHADER.m_spriteShader.DrawString(-600, 250, str, Math::Vector4{1,1,1,1});

	sprintf_s(str, sizeof(str), "敵番号: %d,%d,%d,%d,%d", ENEMY_MGR.GetLockonEnemyNum(0), ENEMY_MGR.GetLockonEnemyNum(1), ENEMY_MGR.GetLockonEnemyNum(2), ENEMY_MGR.GetLockonEnemyNum(3), ENEMY_MGR.GetLockonEnemyNum(4));
	//SHADER.m_spriteShader.DrawString(-600, 200, str, Math::Vector4{ 1,1,1,1 });

	sprintf_s(str, sizeof(str), "敵の種類: %d,%d,%d,%d,%d", ENEMY_MGR.GetLockonEnemyType(0), ENEMY_MGR.GetLockonEnemyType(1), ENEMY_MGR.GetLockonEnemyType(2), ENEMY_MGR.GetLockonEnemyType(3), ENEMY_MGR.GetLockonEnemyType(4));
	//SHADER.m_spriteShader.DrawString(-600, 150, str, Math::Vector4{ 1,1,1,1 });
}

void Scene::Update()
{
	SCENE_MGR.Update();

	if (GetAsyncKeyState('1') & 0x8000)
	{
		SCENE_MGR.SetNowScene(Title);
	}
	else if (GetAsyncKeyState('2') & 0x8000)
	{
		SCENE_MGR.SetNowScene(Game);
		UI.ShowLeftEnemy();
	}
	else if (GetAsyncKeyState('3') & 0x8000)
	{
		SCENE_MGR.SetNowScene(Result);
	}
	else if (GetAsyncKeyState('4') & 0x8000)
	{
		SCENE_MGR.SetNowScene(GameOver);
	}
	else if (GetAsyncKeyState('5') & 0x8000)
	{
		SCENE_MGR.SetNowScene(Game);
		SCENE_MGR.SetNowWave(Wave1);
		UI.ShowLeftEnemy();
		UI.SetNextWave(1);
	}
	else if (GetAsyncKeyState('6') & 0x8000)
	{
		SCENE_MGR.SetNowScene(Game);
		SCENE_MGR.SetNowWave(Wave2);
		UI.ShowLeftEnemy();
		UI.SetNextWave(2);
	}
	else if (GetAsyncKeyState('7') & 0x8000)
	{
		SCENE_MGR.SetNowScene(Game);
		SCENE_MGR.SetNowWave(Wave3);
		UI.ShowLeftEnemy();
		UI.SetNextWave(3);
	}
	else if (GetAsyncKeyState('8') & 0x8000)
	{
		SCENE_MGR.SetNowScene(Game);
		SCENE_MGR.SetNowWave(Wave4);
		UI.ShowLeftEnemy();
		UI.SetNextWave(4);
	}
	else if (GetAsyncKeyState('9') & 0x8000)
	{
		SCENE_MGR.SetNowScene(Game);
		SCENE_MGR.SetNowWave(Boss);
		UI.ShowLeftEnemy();
	}
	
	if (GetAsyncKeyState('J') & 0x8000)
	{
		SCENE_MGR.SetTimeCnt(60 * 180);
		//timeCnt = 60 * 180;
		SCENE_MGR.SetNowScene(Result);
	}
	if (GetAsyncKeyState('K') & 0x8000)
	{
		SCENE_MGR.SetTimeCnt(60 * 240);
		//timeCnt = 60 * 240;
		SCENE_MGR.SetNowScene(Result);
	}
	if (GetAsyncKeyState('L') & 0x8000)
	{
		SCENE_MGR.SetTimeCnt(60 * 241);
		//timeCnt = 60 * 241;
		SCENE_MGR.SetNowScene(Result);
	}

	if (GetAsyncKeyState(VK_SPACE) & 0x8000)
	{
		if (!isSpace_Debug)
		{
			isSpace_Debug = true;
			
			if (isDebugWindow)
			{
				isDebugWindow = false;
			}
			else
			{
				isDebugWindow = true;
			}
		}
	}
	else
	{
		isSpace_Debug = false;
	}
}

void Scene::Init()
{
	ShowCursor(false);
	srand(timeGetTime());
	mouse = { 0,0 };
	clickPos = { 0,0 };
	releasePos = { 0,0 };
	clickFlg = false;
	
	SCENE_MGR.SetNowScene(Title);
	player.Init();
	LoadTexture();

	ENEMY_MGR.Init();
	BULLET_MGR.Init();
	BACKGRND.Init();

	//BGM.StopBGM();
	//BGM.SetBGM(Title);
	//BGM.PlayBGM();
}

void Scene::LoadTexture()
{
	//画像読み込み
	playerhp4Tex.Load("Assets/Image/Player/playerlife4.png");
	playerhp3Tex.Load("Assets/Image/Player/playerlife3.png");
	playerhp2Tex.Load("Assets/Image/Player/playerlife2.png");
	playerhp1Tex.Load("Assets/Image/Player/playerlife1.png");
	playerEngineTex.Load("Assets/Image/Player/playerEngine.png");
	playerEngineBaseTex.Load("Assets/Image/Player/playerEngineBase.png");
	playerExplosionTex.Load("Assets/Image/Effect/PlayerExplosion.png");



	//画像セット
	player.SetPlayerTex(&playerhp1Tex,&playerhp2Tex, &playerhp3Tex, &playerhp4Tex);
	player.SetPlayerEngineTex(&playerEngineTex);
	player.SetPlayerEngineBaseTex(&playerEngineBaseTex);
	player.SetPlayerExplosionTex(&playerExplosionTex);
}

void Scene::Release()
{
	playerhp1Tex.Release();
	playerhp2Tex.Release();
	playerhp3Tex.Release();
	playerhp4Tex.Release();
	playerEngineTex.Release();
	playerEngineBaseTex.Release();
	playerExplosionTex.Release();
	ENEMY_MGR.Release();
	BULLET_MGR.Release();
	BACKGRND.Release();
	EFFECT_MGR.Release();
	SCENE_MGR.Release();
}

void Scene::ImGuiUpdate()
{
	if(!isDebugWindow)return;

	ImGui::SetNextWindowPos(ImVec2(20, 20), ImGuiSetCond_Once);
	ImGui::SetNextWindowSize(ImVec2(100, 50), ImGuiSetCond_Once);

	// デバッグウィンドウ
	if (ImGui::Begin("Debug Window"))
	{
		ImGui::Text("FPS : %d", APP.m_fps);
	}
	ImGui::End();
}

POINT Scene::GetMousePos()
{
	POINT mousePos;	//戻り値用

	//ディスプレイ上のマウス座標を取得(PC画面の左上が(0,0))
	GetCursorPos(&mousePos);

	//指定のウィンドウ基準のマウス座標に変換(実行画面の左上が(0,0))
	//							  ↓実行ウィンドウを識別するための番号
	ScreenToClient(APP.m_window.GetWndHandle(), &mousePos);

	//マウスの座標系を実行画面の座標系(中心が0,0)に補正
	mousePos.x -= ScrWidth / 2;
	mousePos.y -= ScrHeight / 2;
	mousePos.y *= -1;


	return mousePos;
}
