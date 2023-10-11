
#include "Common.h"		// --- 全ファイルでの共通ヘッダー

int WINAPI WinMain(HINSTANCE hI,HINSTANCE hP,LPSTR lpC,int nC){
	
	int ScreenHandle;
	int Gauss = 0;			//ガウスフィルタ大きさ

	int BmpDate[6];

	float camera_direction = 0.0f;
	
	// 全体的なゲームの管理
	int gamemode = eSceneBlank ;

	//ステージのポジション
	VECTOR stagepos = VGet(0.0f,0.0f,0.0f) ;
	VECTOR skypos = VGet(0.0f, 0.0f, 0.0f);
		
	ChangeWindowMode(FALSE);
	SetGraphMode(1920, 1080, 32);

	// DXライブラリの初期化				DXライブラリースタート
	if(DxLib_Init() == -1) return -1 ;

	ScreenHandle = MakeScreen(1920, 1080, FALSE);

	// ステージ情報の読み込み
	skydate = MV1LoadModel("..\\Data\\Stage\\スカイドーム.mv1");

	MV1SetUseZBuffer(skydate, false);
	// 背景読み込み
	bgdate[BACKGROUNDTATAMI] = MV1LoadModel("..\\Data\\Stage\\背景_畳sub.mv1");
	stagedate = MV1LoadModel("..\\Data\\Stage\\石畳.mv1");
	MV1SetPosition(stagedate, VGet(1500.0f, 100.0f, -100.0f));
	MV1SetUseZBuffer(skydate, false);

	// ブロックモデルの読み込み
	blockdate[TATAMI_BLOCK]		= MV1LoadModel("..\\Data\\Stage\\畳.mv1");
	blockdate[BREAK_BLOCK]		= MV1LoadModel("..\\Data\\Stage\\木材.mv1");
	blockdate[FALL_BLOCK]		= MV1LoadModel("..\\Data\\Stage\\落下ブロック.mv1");
	blockdate[INVINCIBLE_BLOCK]	= MV1LoadModel("..\\Data\\Stage\\無敵畳.mv1");
	blockdate[MOVE_BLOCK]		= MV1LoadModel("..\\Data\\Stage\\移動床.mv1");
	blockdate[NEEDLE_BLOCK]		= MV1LoadModel("..\\Data\\Stage\\棘.mv1");
	blockdate[WOOD_BLOCK]		= MV1LoadModel("..\\Data\\Stage\\柱.mv1");

	//月モデルの読み込み
	moon = MV1LoadModel("..\\Data\\Stage\\moon.mv1");
	//城モデルの読み込み
	castle = MV1LoadModel("..\\Data\\japanese-castle\\source\\japanese castle 2.mv1");

	// プレイヤーの作成
	player[0].anim.model = MV1LoadModel("..\\Data\\Ninja\\白忍者.mv1");
	player[1].anim.model = MV1LoadModel("..\\Data\\Ninja\\忍者.mv1");
	player[0].SetPosition(VGet(3000.0f, 200.0f, 500.0f));

	//	Atten0 = 0.3f;
	//	Atten1 = 0.0f;
	//	Atten2 = 0.0f;
	//	C_DirectionX = 0.0f * (DX_PI_F / 180.0f);
	//	C_DirectionY = 270.0f * (DX_PI_F / 180.0f);
	//	C_DirectionZ = 0.0f;

	// スポットライト
	LHandle_p1 = CreateSpotLightHandle(
		VGet(player[0].GetPosition().x - 0.0f, player[0].GetPosition().y - 0.0f, player[0].GetPosition().z - 500.0f),
		VGet(0.0f, 45.0f * (DX_PI_F / 180.0f), 90.0f * (DX_PI_F / 180.0f)),
		0.7f, 0.4f,
		2000.0f,
		0.391586f, 0.001662f, 0.0f);

	LHandle_p2 = CreateSpotLightHandle(
		VGet(player[1].GetPosition().x, player[1].GetPosition().y + 0.0f, player[1].GetPosition().z - 100.0f),
		VGet(0.0f, 0.78f, 1.57f),
		0.24582103f, 6.28318548f,
		2000.0f,
		0.3f, 0.0f, 0.0f);

	// ライトの方向を設定
	SetLightDirection( VGet( 0.0f, -0.5f, 0.5f ) );
	ShadowMapHandle = MakeShadowMap( 1024, 1024 ) ;

	// ライトの色　黒
	SetLightDifColor(GetColorF(0.5f, 0.5f, 0.5f, 0.0f));

	// シャドウマップが想定するライトの方向もセット
	SetShadowMapLightDirection( ShadowMapHandle, VGet( 0.0f, -0.5f, 0.5f ) ) ;

	// シャドウマップに描画する範囲を設定
	SetShadowMapDrawArea( ShadowMapHandle, VGet( -5000.0f, -10.0f, -5000.0f ), VGet( 5000.0f, 1000.0f, 5000.0f ) ) ;

	SetDrawScreen(DX_SCREEN_BACK);

	for (int i = 0; i < BACKGROUNDFLOOR; i++) {
		bg_tatami[i] = MV1DuplicateModel(bgdate[BACKGROUNDTATAMI]);
		MV1SetPosition(bg_tatami[i], VGet(1500.0f, 100.0f + (i * 800.0f), 100.0f));
	}

	blockcnt = 0;
	// マップデータに反映
	for (int y = MAP_Y - 1; y >= 0; y--) {
		for (int x = 0; x < MAP_X; x++) {
			if (StageMap[y][x] != 0) {
				switch (StageMap[y][x]) {
				case TATAMI_BLOCK:
					m_block[blockcnt].b_model = MV1DuplicateModel(blockdate[TATAMI_BLOCK]);
					m_block[blockcnt].SetBlockType(TATAMI_BLOCK);
					break;

				case BREAK_BLOCK:
					m_block[blockcnt].b_model = MV1DuplicateModel(blockdate[BREAK_BLOCK]);
					m_block[blockcnt].SetBlockType(BREAK_BLOCK);
					break;

				case FALL_BLOCK:
					m_block[blockcnt].b_model = MV1DuplicateModel(blockdate[FALL_BLOCK]);
					m_block[blockcnt].SetBlockType(FALL_BLOCK);
					break;

				case INVINCIBLE_BLOCK:
					m_block[blockcnt].b_model = MV1DuplicateModel(blockdate[INVINCIBLE_BLOCK]);
					m_block[blockcnt].SetBlockType(INVINCIBLE_BLOCK);
					break;

				case MOVE_BLOCK:
					m_block[blockcnt].b_model = MV1DuplicateModel(blockdate[MOVE_BLOCK]);
					m_block[blockcnt].SetBlockType(MOVE_BLOCK);
					m_block[blockcnt].SetMapPositionX(x);
					break;

				case NEEDLE_BLOCK:
					m_block[blockcnt].b_model = MV1DuplicateModel(blockdate[NEEDLE_BLOCK]);
					m_block[blockcnt].SetBlockType(NEEDLE_BLOCK);
					break;

				case WOOD_BLOCK:
					m_block[blockcnt].b_model = MV1DuplicateModel(blockdate[WOOD_BLOCK]);
					m_block[blockcnt].SetBlockType(WOOD_BLOCK);
					break;
				}
				m_block[blockcnt].SetMapPositionY(y);
				m_block[blockcnt].SetMapPositionX(x);
				m_block[blockcnt].SetBlockFlag(TRUE);
				blockcnt++;
			}
		}
	}

	blockcnt = 0;

	for (int y = (MAP_Y - 1); y >= 0; y--) {
		for (int x = 0; x < MAP_X; x++) {
			if (StageMap[y][x] != 0) {
				if (StageMap[y][x] != NEEDLE_BLOCK) {
					MV1SetPosition(m_block[blockcnt].b_model, VGet((x * 200.0f), ((MAP_Y - y) * 100.0f), 0.0f));
					m_block[blockcnt].SetBlockPosition(VGet((x * 200.0f), ((MAP_Y - y) * 100.0f), 0.0f));
				}
				else {
					MV1SetPosition(m_block[blockcnt].b_model, VGet((x * 200.0f), ((MAP_Y - y) * 100.0f) + 50.0f, 0.0f));
					m_block[blockcnt].SetBlockPosition(VGet((x * 200.0f), ((MAP_Y - y) * 100.0f) + 50.0f, 0.0f));
				}
				blockcnt++;
			}
		}
	}

	//月 初期セット
	MV1SetPosition(moon, VGet(600.0f, 1000.0f, 1000.0f));
	//城 初期セット
	MV1SetPosition(castle, VGet(3000.0f, 170.0f, 3000.0f));
	MV1SetRotationXYZ(castle, VGet(0.0f, 1.57f * 1.3f, 0.0f));

	//画像の読み込み
	BmpDate[0] = LoadGraph("..\\Data\\Stage\\金箔雲エフェクト1.png");
	BmpDate[1] = LoadGraph("..\\Data\\Stage\\金箔雲エフェクト2.png");
	BmpDate[2] = LoadGraph("..\\Data\\Stage\\金箔雲エフェクト3.png");
	BmpDate[3] = LoadGraph("..\\Data\\Stage\\金箔雲エフェクト4.png");
	BmpDate[4] = LoadGraph("..\\Data\\Stage\\金箔雲エフェクト5.png");
	BmpDate[5] = LoadGraph("..\\Data\\Stage\\金箔雲エフェクト6.png");


	/* ------------------------------------------------------------------------------------------------
												ゲームループ										
	 ----------------------------------------------------------------------------------------------- */
	while(ProcessMessage() == 0 && CheckHitKey(KEY_INPUT_ESCAPE) == 0){
		static int x = 0;
		static int x1 = 0;
		static BOOL GamemodeChenge_flg = 0;

		MV1SetUseZBuffer(skydate, false);

		switch(gamemode){
			case eSceneBlank :
				cpos = VGet(1600.0f, 170.0f, -100.0f);
				ctgt = VGet(1600.0f, 200.0f,    0.0f);

				//カメラ情報の反映
				SetCameraPositionAndTargetAndUpVec(cpos, ctgt, VGet(0.0f, 1.0f, 0.0f));

				g_Chara[0] = &player[0];
				g_Chara[1] = &player[1];

				gamemode = eSceneTitle;
				break;

			case eSceneTitle:

				ClearDrawScreen();

				// 地面(配置)＆描画
				MV1DrawModel(skydate);
				MV1DrawModel(stagedate);
				MV1DrawModel(moon);
				MV1DrawModel(castle);


				ScreenFlip();  
				if (CheckHitKey(KEY_INPUT_SPACE) == 1) {
					gamemode = eSceneChoice;
				}

				break;

			case eSceneChoice:
				if (player[0].GetPosition().x >= 1930) {
					player[0].SetPosition(VGet(2400.0f - x, 150.0f, 500.0f));
					player[1].SetPosition(VGet( 800.0f + x, 150.0f, 500.0f));
					x += 20;
					Gauss += 20;
				}
				SetDrawScreen(ScreenHandle);

				// 画面をクリア
				ClearDrawScreen();

				//カメラ情報の反映
				SetCameraPositionAndTargetAndUpVec(cpos, ctgt, VGet(0.0f, 1.0f, 0.0f));

				// モデルの移動(配置)
				MV1SetPosition(player[0].anim.model, player[0].GetPosition());
				MV1SetPosition(player[1].anim.model, player[1].GetPosition());

				// 地面(配置)＆描画
				MV1DrawModel(skydate);
				MV1DrawModel(stagedate);
				MV1DrawModel(moon);
				MV1DrawModel(castle);

				SetLightAngleHandle(LHandle_p1, 0.24582103f, 6.28318548f);
				SetLightPositionHandle(LHandle_p1, VGet(player[0].GetPosition().x, player[0].GetPosition().y + 100.0f, player[0].GetPosition().z - 500.0f)); // ライトの位置
				SetLightPositionHandle(LHandle_p2, VGet(player[1].GetPosition().x, player[1].GetPosition().y + 100.0f, player[1].GetPosition().z - 500.0f)); // ライトの位置

				// ８分の１に縮小した画像をガウスフィルタでぼかす
				GraphFilter(ScreenHandle, DX_GRAPH_FILTER_GAUSS, 32, Gauss);

				// モデルの描画
				MV1DrawModel(player[0].anim.model);
				MV1DrawModel(player[1].anim.model);

				if (player[0].GetPosition().x <= 1930) {
					SetFontSize(128);
					ChangeFont("HGS行書体");
					DrawString(130, 70, "プレイヤー１", GetColor(252, 252, 252));
					DrawString(1030, 70, "プレイヤー２", GetColor(252, 252, 252));

					DrawString(100, 380, "<", GetColor(252, 0, 0));
					DrawString(830, 380, ">", GetColor(252, 0, 0));

					DrawString(1000, 380, "<", GetColor(252, 0, 0));
					DrawString(1730, 380, ">", GetColor(252, 0, 0));
				}

				// 描画対象を裏画面にする
				SetDrawScreen(DX_SCREEN_BACK);

				// 通常の描画結果を描画する
				DrawGraph(0, 0, ScreenHandle, FALSE);

				if (GamemodeChenge_flg == 1) {

					if (x >= 2000) {
					}

					if (x <= 3000) {
						x += 30;
						x1 += 20;
					}
					if (x >= 6000) {
						player[0].SetPosition(VGet(200.0f, 1800.0f, 0.0f));
						player[1].SetPosition(VGet(2800.0f, 1800.0f, 0.0f));
						cpos = VGet(1484.0f, 2360.0f, -1860.0f);
						ctgt = VGet(0.0f, 1000.0f, 0.0f);
						gamemode = eScenePlay;
					}

					// BMP画像の表示
					//左から第一陣
					DrawGraph(-1000 +  x,   0, BmpDate[0], TRUE);
					DrawGraph(-1000 +  x, 360, BmpDate[1], TRUE);
					DrawGraph(-1000 +  x, 690, BmpDate[2], TRUE);
					DrawGraph(-1000 + x1, 180, BmpDate[3], TRUE);
					DrawGraph(-1000 + x1, 540, BmpDate[4], TRUE);
					DrawGraph(-1000 + x1, 900, BmpDate[5], TRUE);
					//左から第二陣
					DrawGraph(-1500 +  x,   0, BmpDate[0], TRUE);
					DrawGraph(-1500 +  x, 360, BmpDate[1], TRUE);
					DrawGraph(-1500 +  x, 690, BmpDate[2], TRUE);
					DrawGraph(-1500 + x1, 180, BmpDate[3], TRUE);
					DrawGraph(-1500 + x1, 540, BmpDate[4], TRUE);
					DrawGraph(-1500 + x1, 900, BmpDate[5], TRUE);
					//右から第一陣
					DrawGraph(2000 -  x,   0, BmpDate[0], TRUE);
					DrawGraph(2000 -  x, 360, BmpDate[1], TRUE);
					DrawGraph(2000 -  x, 690, BmpDate[2], TRUE);
					DrawGraph(2000 - x1, 180, BmpDate[3], TRUE);
					DrawGraph(2000 - x1, 540, BmpDate[4], TRUE);
					DrawGraph(2000 - x1, 900, BmpDate[5], TRUE);
					//右から第二陣
					DrawGraph(2500 -  x,   0, BmpDate[0], TRUE);
					DrawGraph(2500 -  x, 360, BmpDate[1], TRUE);
					DrawGraph(2500 -  x, 690, BmpDate[2], TRUE);
					DrawGraph(2500 - x1, 180, BmpDate[3], TRUE);
					DrawGraph(2500 - x1, 540, BmpDate[4], TRUE);
					DrawGraph(2500 - x1, 900, BmpDate[5], TRUE);

				}


				ScreenFlip();

				if (CheckHitKey(KEY_INPUT_RETURN) == 1 && GamemodeChenge_flg == 0) {
					GamemodeChenge_flg = 1;
					x = 0;
					x1 = 0;
				}

				break;

			case eScenePlay :
				g_Chara[0]->ActionLoop(g_Chara[0], g_Chara[1]);
				g_Chara[1]->ActionLoop(g_Chara[1], g_Chara[0]);

				ClearDrawScreen() ;
				// カメラの視点操作
				CameraMove();

				// 背景(空)の操作
				skypos.x = cpos.x;
				skypos.y = cpos.y - 3000.0f;
				skypos.z = cpos.z;

				SetCameraPositionAndTargetAndUpVec(cpos,ctgt,VGet(0.0f,1.0f,0.0f)) ;

				// モデルの回転
				MV1SetRotationXYZ(player[0].anim.model,VGet(0.0f,1.57f * player[0].GetDirection(),0.0f)) ;
				// モデルの移動(配置)
				MV1SetPosition(player[0].anim.model,player[0].GetPosition());

				// モデルの回転
				MV1SetRotationXYZ(player[1].anim.model, VGet(0.0f, 1.57f * player[1].GetDirection(), 0.0f));
				// モデルの移動(配置)
				MV1SetPosition(player[1].anim.model ,player[1].GetPosition());

				MV1SetPosition(skydate, skypos);

				// 描画
				Draw();

				ScreenFlip() ;
				break ;

			case eSceneClear :
				break ;
		}
	}

	//画像ハンドルの削除
	DeleteGraph(BmpDate[0]);
	DeleteGraph(BmpDate[1]);
	DeleteGraph(BmpDate[2]);
	DeleteGraph(BmpDate[3]);
	DeleteGraph(BmpDate[4]); 
	DeleteGraph(BmpDate[5]);

	// ライトハンドルの削除
	DeleteLightHandle(LHandle_p1);
	DeleteLightHandle(LHandle_p2);
	// シャドウマップの削除
	DeleteShadowMap(ShadowMapHandle);
	// キャラクターモデルの削除
	MV1DeleteModel(player[0].anim.model);
	MV1DeleteModel(player[1].anim.model);
	// ブロックモデルの削除
	MV1DeleteModel(blockdate[TATAMI_BLOCK]);
	MV1DeleteModel(blockdate[FALL_BLOCK]);
	MV1DeleteModel(blockdate[NEEDLE_BLOCK]);
	MV1DeleteModel(blockdate[WOOD_BLOCK]);
	// 背景の削除
	MV1DeleteModel(bgdate[BACKGROUNDTATAMI]);
	DxLib_End();
	return 0 ;
}

