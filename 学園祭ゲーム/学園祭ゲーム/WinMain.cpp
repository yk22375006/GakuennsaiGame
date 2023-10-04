
#include "Common.h"		// --- 全ファイルでの共通ヘッダー

int WINAPI WinMain(HINSTANCE hI,HINSTANCE hP,LPSTR lpC,int nC){
	
	int ScreenHandle;

	float camera_direction = 0.0f;
	
	// 全体的なゲームの管理
	int gamemode = eSceneBlank ;

	//ステージのポジション
	VECTOR stagepos = VGet(0.0f,0.0f,0.0f) ;
	VECTOR skypos = VGet(0.0f, 0.0f, 0.0f);
		
		
	// カメラポジション cpos:カメラ位置　ctgt:カメラ注視点
	cpos = VGet(3500.0f, 2300.0f, -3500.0f);

//	cpos = VGet(500.0f,1000.0f,-2000.0f) ;
	ctgt = VGet(0.0f,500.0f,-400.0f) ;
	cadd = VGet(0.0f, 0.0f, 0.0f);

	ChangeWindowMode(TRUE);
	SetGraphMode(1440, 810, 32);

	// DXライブラリの初期化				DXライブラリースタート
	if(DxLib_Init() == -1) return -1 ;

	ScreenHandle = MakeScreen(1920, 1080, FALSE);


	// ステージ情報の読み込み
	// コミット用コメント
	// ステージ情報の読み込み
	skydate = MV1LoadModel("..\\Data\\Stage\\スカイドーム.mv1");
	if (skydate == -1) return -1;

	MV1SetUseZBuffer(skydate, false);
	// 背景読み込み
	bgdate[BACKGROUNDTATAMI] = MV1LoadModel("..\\Data\\Stage\\背景_畳.mv1");
	stagedate = MV1LoadModel("..\\Data\\Stage\\石畳.mv1");
	MV1SetPosition(stagedate, VGet(1500.0f, 100.0f, -100.0f));
	MV1SetUseZBuffer(skydate, false);

	// ブロックモデルの読み込み
	blockdate[TATAMI_BLOCK]		= MV1LoadModel("..\\Data\\Stage\\畳.mv1");
	blockdate[BREAK_BLOCK]		= MV1LoadModel("..\\Data\\Stage\\木材.mv1");
	blockdate[FALL_BLOCK]		= MV1LoadModel("..\\Data\\Stage\\落下ブロック.mv1");
	blockdate[INVINCIBLE_BLOCK]	= MV1LoadModel("..\\Data\\Stage\\無敵畳.mv1");
	blockdate[NEEDLE_BLOCK]		= MV1LoadModel("..\\Data\\Stage\\棘.mv1");
	blockdate[WOOD_BLOCK]		= MV1LoadModel("..\\Data\\Stage\\柱.mv1");
	blockdate[MOVE_BLOCK_X] = MV1LoadModel("..\\Data\\Stage\\移動床.mv1");
	// プレイヤーの作成
	player[0].anim.model = MV1LoadModel("..\\Data\\Ninja\\白忍者.mv1");
	player[1].anim.model = MV1LoadModel("..\\Data\\Ninja\\忍者.mv1");

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

	m_block->init();

	/* ------------------------------------------------------------------------------------------------
												ゲームループ										
	 ----------------------------------------------------------------------------------------------- */
	while(ProcessMessage() == 0 && CheckHitKey(KEY_INPUT_ESCAPE) == 0){
		MV1SetUseZBuffer(skydate, false);

						
		switch(gamemode){
			case eSceneBlank :
				gamemode = eSceneChoice;
				g_Chara[0] = &player[0];
				g_Chara[1] = &player[1];
				DrawLimit = 0;
				break;

			case eSceneTitle:
				if (CheckHitKey(KEY_INPUT_SPACE) == 1) {
					gamemode = eSceneChoice;
				}
				break;

			case eSceneChoice:
				SetDrawScreen(ScreenHandle);

				// 画面をクリア
				ClearDrawScreen();

				cpos = VGet(0.0f, 1000.0f, -1500.0f);
				ctgt = VGet(0.0f, 2000.0f, 0.0f);
				cadd = VGet(0.0f, 0.0f, 0.0f);

				player[0].SetPosition(VGet(200.0f, 200.0f, 0.0f));
				player[1].SetPosition(VGet(0.0f, 2000.0f, 0.0f));

				//カメラ情報の反映
				SetCameraPositionAndTargetAndUpVec(cpos, ctgt, VGet(0.0f, 1.0f, 0.0f));

				// モデルの移動(配置)
				MV1SetRotationXYZ(player[0].anim.model, VGet(0.0f, 1.57f * player[0].GetDirection(), 0.0f));
				MV1SetPosition(player[0].anim.model, player[0].GetPosition());
				MV1SetRotationXYZ(player[1].anim.model, VGet(0.0f, 1.57f * player[1].GetDirection(), 0.0f));
				MV1SetPosition(player[1].anim.model, player[1].GetPosition());

				// シャドウマップへの描画の準備
				ShadowMap_DrawSetup(ShadowMapHandle);

				// モデルの描画 - 影の描画
				MV1DrawModel(player[0].anim.model);
				MV1DrawModel(player[1].anim.model);

				// シャドウマップへの描画を終了
				ShadowMap_DrawEnd();

				// 描画に使用するシャドウマップを設定
				SetUseShadowMap(0, ShadowMapHandle);

				// 地面(配置)＆描画
				MV1DrawModel(skydate);
				MV1DrawModel(stagedate);
				for (int i = 0; i < BACKGROUNDFLOOR; i++) {
					MV1DrawModel(bg_tatami[i]);
				}

				blockcnt = 0;
				for (blockcnt = 0; blockcnt < MAX_BLOCK; blockcnt++) {
					if (m_block[blockcnt].GetBlockFlag() == TRUE) {
						MV1DrawModel(m_block[blockcnt].b_model);
					}
				}

//				SetLightRangeAttenHandle(LHandle_p1, Range, Atten0, Atten1, Atten2);
				SetLightAngleHandle(LHandle_p1, 0.24582103f, 6.28318548f);
				SetLightPositionHandle(LHandle_p1, VGet(player[0].GetPosition().x, player[0].GetPosition().y + 100.0f, player[0].GetPosition().z - 500.0f)); // ライトの位置
				SetLightPositionHandle(LHandle_p2, VGet(player[1].GetPosition().x, player[1].GetPosition().y + 100.0f, player[1].GetPosition().z - 500.0f)); // ライトの位置
			//	SetLightDirectionHandle(LHandle_p1, VGet(ctgt.x = cpos.x , ctgt.y = cpos.y - 400   , ctgt.z = cpos.z ));  // ライトの方向
			//	SetLightAngleHandle(LHandle_p1, 0.78f, 0.5f);

				// 描画に使用するシャドウマップの設定を解除
				SetUseShadowMap(0, -1);

				// ８分の１に縮小した画像をガウスフィルタでぼかす
				GraphFilter(ScreenHandle, DX_GRAPH_FILTER_GAUSS, 16, 1400);

				// モデルの描画
				MV1DrawModel(player[0].anim.model);
				MV1DrawModel(player[1].anim.model);

				// 描画対象を裏画面にする
				SetDrawScreen(DX_SCREEN_BACK);

				// 通常の描画結果を描画する
				DrawGraph(0, 0, ScreenHandle, FALSE);

				ScreenFlip();

				if (CheckHitKey(KEY_INPUT_RETURN) == 1) {
					player[0].SetPosition(VGet(200.0f, 2000.0f, 0.0f));
					player[1].SetPosition(VGet(2800.0f, 2000.0f, 0.0f));
					cpos = VGet(1484.0f, 2360.0f, -1860.0f);

					gamemode = eScenePlay;
				}
				break;

			case eScenePlay :
				g_Chara[0]->ActionLoop(g_Chara[0], g_Chara[1]);
				g_Chara[1]->ActionLoop(g_Chara[1], g_Chara[0]);

				// スクリーンクリアー
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

				if (DrawLimit > 0)
					DrawLimit--;

				if (DrawLimit < 0)
					DrawLimit = 0;

				ScreenFlip() ;
				break ;

			case eSceneClear :
				break ;
		}
	}

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

