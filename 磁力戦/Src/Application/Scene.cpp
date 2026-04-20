#include "main.h"
#include "Scene.h"

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
	sprintf_s(str, sizeof(str),"敵を倒した数: %d", ENEMY_MGR.GetEnemyKillCnt());
	SHADER.m_spriteShader.DrawString(-600, 300, str, Math::Vector4{ 1,1,1,1 });

	sprintf_s(str, sizeof(str), "今のWave: %d", SCENE_MGR.GetNowWave()+1);
	SHADER.m_spriteShader.DrawString(-600, 250, str, Math::Vector4{1,1,1,1});
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
	}
	else if (GetAsyncKeyState('3') & 0x8000)
	{
		SCENE_MGR.SetNowScene(Result);
	}
}

void Scene::Init()
{
	srand(timeGetTime());
	mouse = { 0,0 };
	clickPos = { 0,0 };
	releasePos = { 0,0 };
	clickFlg = false;
	
	SCENE_MGR.SetNowScene(Game);
	player.Init();
	LoadTexture();

	ENEMY_MGR.Init();
	BULLET_MGR.Init();
	BACKGRND.Init();
}

void Scene::LoadTexture()
{
	//画像読み込み
	playerTex.Load("Assets/Image/Player/player.png");
	



	//画像セット
	player.SetPlayerTex(&playerTex);
}

void Scene::Release()
{
	playerTex.Release();
	ENEMY_MGR.Release();
	BULLET_MGR.Release();
	BACKGRND.Release();
}

void Scene::ImGuiUpdate()
{
	return;

	ImGui::SetNextWindowPos(ImVec2(20, 20), ImGuiSetCond_Once);
	ImGui::SetNextWindowSize(ImVec2(200, 100), ImGuiSetCond_Once);

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
