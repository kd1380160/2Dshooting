#pragma once
#include "Player/Player.h"
#include"BackGround/BackGround.h"
#include"Bullet/BulletManager.h"
#include"Enemy/EnemyManager.h"
#include"Scene/SceneManager.h"

class Scene
{
private:

	//画面サイズの宣言
	static const int ScrWidth = 1280;
	static const int ScrHeight = 720;

	//マウス座標(メンバにxとyを持つ型)
	POINT mouse;		// 毎フレームのマウス座標
	POINT clickPos;		//クリックした瞬間のマウス座標
	POINT releasePos;	//クリックを離した瞬間のマウス座標
	bool clickFlg;		//クリック入力用フラグ

	//プレイヤー
	C_Player player;
	KdTexture playerTex;

	
	

public:

	// 初期設定
	void Init();

	// 解放
	void Release();

	// 更新処理
	void Update();

	// 描画処理
	void Draw2D();

	//画像のロードとセット
	void LoadTexture();

	// GUI処理
	void ImGuiUpdate();

	//マウス座標取得
	POINT GetMousePos();

	C_Player* GetPlayer() { return &player; }
	
private:

	Scene() {}

public:
	static Scene& GetInstance()
	{
		static Scene instance;
		return instance;
	}
};

#define SCENE Scene::GetInstance()
