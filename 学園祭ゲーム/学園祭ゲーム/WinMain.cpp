
#include "Common.h"		// --- 全ファイルでの共通ヘッダー

int WINAPI WinMain(HINSTANCE hI, HINSTANCE hP, LPSTR lpC, int nC) {

	int ScreenHandle;
	int Gauss = 0;			//ガウスフィルタ大きさ
	int BmpDate[7];			// ＢＭＰ画像のメモリへの読みこみ

	float camera_direction = 0.0f;

	//ステージのポジション
	VECTOR stagepos = VGet(0.0f, 0.0f, 0.0f);
	VECTOR skypos = VGet(0.0f, 0.0f, 0.0f);

	ChangeWindowMode(FALSE);
	SetGraphMode(1920, 1080, 32);
	//フォントタイプ
	ChangeFontType(DX_FONTTYPE_EDGE);

	// DXライブラリの初期化				DXライブラリースタート
	if (DxLib_Init() == -1) return -1;

	ScreenHandle = MakeScreen(1920, 1080, FALSE);

	// ステージ情報の読み込み
	skydate = MV1LoadModel("..\\Data\\Stage\\スカイドーム.mv1");

	MV1SetUseZBuffer(skydate, false);
	// 背景読み込み
	bgdate[BACKGROUNDTATAMI] = MV1LoadModel("..\\Data\\Stage\\背景_畳.mv1");
	stagedate = MV1LoadModel("..\\Data\\Stage\\石畳.mv1");
	MV1SetPosition(stagedate, VGet(1500.0f, 100.0f, -100.0f));
	MV1SetUseZBuffer(skydate, false);

	// ブロックモデルの読み込み
	blockdate[TATAMI_BLOCK] = MV1LoadModel("..\\Data\\Stage\\畳.mv1");
	blockdate[BREAK_BLOCK] = MV1LoadModel("..\\Data\\Stage\\木材.mv1");
	blockdate[FALL_BLOCK] = MV1LoadModel("..\\Data\\Stage\\落下ブロック.mv1");
	blockdate[INVINCIBLE_BLOCK] = MV1LoadModel("..\\Data\\Stage\\無敵畳.mv1");
	blockdate[NEEDLE_BLOCK] = MV1LoadModel("..\\Data\\Stage\\棘.mv1");
	blockdate[WOOD_BLOCK] = MV1LoadModel("..\\Data\\Stage\\柱.mv1");
	blockdate[MOVE_BLOCK_X] = MV1LoadModel("..\\Data\\Stage\\移動床.mv1");

	//月モデルの読み込み
	moon = MV1LoadModel("..\\Data\\Stage\\moon.mv1");
	//城モデルの読み込み
	castle = MV1LoadModel("..\\Data\\japanese-castle\\source\\japanese castle 2.mv1");
	//城モデルの読み込み
	roof = MV1LoadModel("..\\Data\\Stage\\瓦.mv1");

	// 
	Original[0].type[SPEEDMODE] = MV1LoadModel("..\\Data\\Ninja\\忍者_苦無.mv1");
	Original[0].typestop[SPEEDMODE] = MV1LoadModel("..\\Data\\Ninja\\忍者_苦無_待機.mv1");

	Original[0].type[BALANCEMODE] = MV1LoadModel("..\\Data\\Ninja\\忍者_バランス.mv1");
	Original[0].typestop[BALANCEMODE] = MV1LoadModel("..\\Data\\Ninja\\忍者待機_バランス.mv1");
	
	Original[0].type[POWERMODE] = MV1LoadModel("..\\Data\\Ninja\\忍者パワー.mv1");
	Original[0].typestop[POWERMODE] = MV1LoadModel("..\\Data\\Ninja\\忍者待機_パワー.mv1");

	Original[1].type[SPEEDMODE] = MV1LoadModel("..\\Data\\Ninja\\白忍者_苦無.mv1");
	Original[1].typestop[SPEEDMODE] = MV1LoadModel("..\\Data\\Ninja\\白忍者_苦無_待機.mv1");

	Original[1].type[BALANCEMODE] = MV1LoadModel("..\\Data\\Ninja\\忍者_バランス.mv1");
	Original[1].typestop[BALANCEMODE] = MV1LoadModel("..\\Data\\Ninja\\忍者待機_バランス.mv1");

	Original[1].type[POWERMODE] = MV1LoadModel("..\\Data\\Ninja\\白忍者パワー.mv1");
	Original[1].typestop[POWERMODE] = MV1LoadModel("..\\Data\\Ninja\\忍者待機_パワー.mv1");

	// プレイヤーの作成
	player[0].anim.type[SPEEDMODE] = MV1DuplicateModel(Original[0].type[SPEEDMODE]);
	player[0].anim.typestop[SPEEDMODE] = MV1DuplicateModel(Original[0].typestop[SPEEDMODE]);
	player[0].anim.type[BALANCEMODE] = MV1DuplicateModel(Original[0].type[BALANCEMODE]);
	player[0].anim.typestop[BALANCEMODE] = MV1DuplicateModel(Original[0].typestop[BALANCEMODE]);
	player[0].anim.type[POWERMODE] = MV1DuplicateModel(Original[0].type[POWERMODE]);
	player[0].anim.typestop[POWERMODE] = MV1DuplicateModel(Original[0].typestop[POWERMODE]);

	player[1].anim.type[SPEEDMODE] = MV1DuplicateModel(Original[1].type[SPEEDMODE]);
	player[1].anim.typestop[SPEEDMODE] = MV1DuplicateModel(Original[1].typestop[SPEEDMODE]);;
	player[1].anim.type[BALANCEMODE] = MV1DuplicateModel(Original[1].type[BALANCEMODE]);
	player[1].anim.typestop[BALANCEMODE] = MV1DuplicateModel(Original[1].typestop[BALANCEMODE]);
	player[1].anim.type[POWERMODE] = MV1DuplicateModel(Original[1].type[POWERMODE]);
	player[1].anim.typestop[POWERMODE] = MV1DuplicateModel(Original[1].typestop[POWERMODE]);

	Original[0].run = MV1LoadModel("..\\Data\\Ninja\\忍者_苦無_移動.mv1");
	Original[0].jump_in = MV1LoadModel("..\\Data\\Ninja\\忍者_苦無_ジャンプ開始.mv1.mv1");
	Original[0].jump = MV1LoadModel("..\\Data\\Ninja\\忍者_苦無_ジャンプ中");
	Original[0].fall = MV1LoadModel("..\\Data\\Ninja\\忍者_苦無_落下.mv1");
	Original[0].attack = MV1LoadModel("..\\Data\\Ninja\\忍者_苦無_攻撃.mv1");
	Original[0].damage = MV1LoadModel("..\\Data\\Ninja\\忍者_苦無_ダメージ.mv1");

	Original[1].run = MV1LoadModel("..\\Data\\Ninja\\忍者走り_バランス.mv1");
	Original[1].jump_in = MV1LoadModel("..\\Data\\Ninja\\忍者_苦無_ジャンプ開始.mv1.mv1");
	Original[1].jump = MV1LoadModel("..\\Data\\Ninja\\忍者ジャンプ_バランス");
	Original[1].fall = MV1LoadModel("..\\Data\\Ninja\\忍者落下_バランス.mv1");
	Original[1].attack = MV1LoadModel("..\\Data\\Ninja\\忍者攻撃_バランス.mv1");
	Original[1].damage = MV1LoadModel("..\\Data\\Ninja\\忍者ダメージ_バランス.mv1");

	// スポットライト
	LHandle_p1 = CreateSpotLightHandle(
		VGet(player[1].GetPosition().x, player[1].GetPosition().y + 0.0f, player[1].GetPosition().z - 100.0f),
		VGet(0.0f, 0.78f, 1.57f),
		0.24582103f, 6.28318548f,
		2000.0f,
		0.3f, 0.0f, 0.0f);

	LHandle_p2 = CreateSpotLightHandle(
		VGet(player[1].GetPosition().x, player[1].GetPosition().y + 0.0f, player[1].GetPosition().z - 100.0f),
		VGet(0.0f, 0.78f, 1.57f),
		0.24582103f, 6.28318548f,
		2000.0f,
		0.3f, 0.0f, 0.0f);

	// ライトの方向を設定
	SetLightDirection(VGet(0.0f, -0.5f, 0.5f));
	ShadowMapHandle = MakeShadowMap(1024, 2048);

	// ライトの色　黒
	SetLightDifColor(GetColorF(0.5f, 0.5f, 0.5f, 0.0f));

	// シャドウマップが想定するライトの方向もセット
	SetShadowMapLightDirection(ShadowMapHandle, VGet(0.0f, 0.0f, 0.5f));

	// シャドウマップに描画する範囲を設定
	SetShadowMapDrawArea(ShadowMapHandle, VGet(-100.0f, -10.0f, -100.0f), VGet(3000.0f, 20000.0f, 1000.0f));

	SetDrawScreen(DX_SCREEN_BACK);

	// ブロックの初期セット
	m_block->init();

	//月 初期セット
	MV1SetPosition(moon, VGet(600.0f, 1000.0f, 1000.0f));
	//城 初期セット
	MV1SetPosition(castle, VGet(3000.0f, 170.0f, 3000.0f));
	MV1SetRotationXYZ(castle, VGet(0.0f, 1.57f * 1.3f, 0.0f));
	//屋根 初期セット
	MV1SetPosition(roof, VGet(1550.0f, -1000.0f, 700.0f));

	//画像の読み込み
	BmpDate[0] = LoadGraph("..\\Data\\Stage\\金箔雲エフェクト1.png");
	BmpDate[1] = LoadGraph("..\\Data\\Stage\\金箔雲エフェクト2.png");
	BmpDate[2] = LoadGraph("..\\Data\\Stage\\金箔雲エフェクト3.png");
	BmpDate[3] = LoadGraph("..\\Data\\Stage\\金箔雲エフェクト4.png");
	BmpDate[4] = LoadGraph("..\\Data\\Stage\\金箔雲エフェクト5.png");
	BmpDate[5] = LoadGraph("..\\Data\\Stage\\金箔雲エフェクト6.png");
	BmpDate[6] = LoadGraph("..\\Data\\Stage\\milky2.jpg");

	/* ------------------------------------------------------------------------------------------------
												ゲームループ
	 ----------------------------------------------------------------------------------------------- */
	while (ProcessMessage() == 0 && CheckHitKey(KEY_INPUT_ESCAPE) == 0) {
		static int x = 0;
		static int x1 = 0;
		static BOOL GamemodeChenge_flg = 0;
		static int FontSize = 0;

		MV1SetUseZBuffer(skydate, false);

		switch (gamemode) {
		case eSceneBlank:
			cpos = VGet(1600.0f, 170.0f, -100.0f);
			ctgt = VGet(1600.0f, 200.0f, 0.0f);

			//カメラ情報の反映
			SetCameraPositionAndTargetAndUpVec(cpos, ctgt, VGet(0.0f, 1.0f, 0.0f));

			g_Chara[0] = &player[0];
			g_Chara[1] = &player[1];

			gamemode = eSceneTitle;
			DrawLimit = 0;
			continuous_limit = 0;
			break;
			// ------------------------------------------------------------------------ //
			//																			//
			//								タイトル画面	　							//
			//																			//
			// ------------------------------------------------------------------------ //
		case eSceneTitle:
			ClearDrawScreen();

			// 地面(配置)＆描画
			MV1DrawModel(skydate);
			MV1DrawModel(stagedate);
			MV1DrawModel(moon);
			MV1DrawModel(castle);

			ScreenFlip();
			key1 = GetJoypadInputState(DX_INPUT_KEY_PAD1);
			if (key1 & PAD_INPUT_A) {
				gamemode = eSceneChoice;
				player[0].SetType(SPEEDMODE);
				player[1].SetType(SPEEDMODE);
				player[1].SetPosition(VGet(3000.0f, 200.0f, 500.0f));
				player[0].ChangeAnimationType(g_Chara[0], player[0].anim.typestop[player[0].GetType()]);
				player[1].ChangeAnimationType(g_Chara[1], player[1].anim.typestop[player[1].GetType()]);
			}
			if (CheckHitKey(KEY_INPUT_SPACE) == 1) {
				gamemode = eSceneChoice;
				player[0].SetType(SPEEDMODE);
				player[1].SetType(SPEEDMODE);
				player[1].SetPosition(VGet(3000.0f, 200.0f, 500.0f));
				player[0].ChangeAnimationType(g_Chara[0], player[0].anim.typestop[player[0].GetType()]);
				player[1].ChangeAnimationType(g_Chara[1], player[1].anim.typestop[player[1].GetType()]);
			}
			break;
			// ------------------------------------------------------------------------ //
			//																			//
			//								キャラ選択画面　							//
			//																			//
			// ------------------------------------------------------------------------ //
		case eSceneChoice:
			if (player[1].GetPosition().x >= 1930) {
				player[0].SetPosition(VGet(800.0f + x, 150.0f, 500.0f));
				player[1].SetPosition(VGet(2400.0f - x, 150.0f, 500.0f));
				Gauss += 20;
				if (GamemodeChenge_flg != 1)
					x += 20;
			}
			key1 = GetJoypadInputState(DX_INPUT_KEY_PAD1);
			key2 = GetJoypadInputState(DX_INPUT_PAD2);
			if (((key1 & PAD_INPUT_B) || (CheckHitKey(KEY_INPUT_RETURN) == 1)) && GamemodeChenge_flg != 1 &&
				player[0].GetSelectFlg() == TRUE && player[1].GetSelectFlg() == TRUE) {
				GamemodeChenge_flg = 1;
				x = 0;
				x1 = 0;
				player[0].LoadAnimation(g_Chara[0]);
				player[1].LoadAnimation(g_Chara[1]);
				player[0].ChangeAnimation(g_Chara[0], player[0].anim.stop);
				player[1].ChangeAnimation(g_Chara[1], player[1].anim.stop);
				switch (player[0].GetType()) {
				case SPEEDMODE:
					player[0].SetAttackMiddleRange(SPEED_ATTACK_MIDDLE_RANGE);
					player[0].SetAttackRange(SPEED_ATTACK_RANGE);
					player[0].SetMoveSpeed(SPEEDPLAYER_SPEED);
					CharaIcon[0] = LoadGraph("..\\Data\\Icon\\スピードやられ.png");
					break;

				case BALANCEMODE:
					player[0].SetAttackMiddleRange(BLANCE_ATTACK_MIDDLE_RANGE);
					player[0].SetAttackRange(BLANCE_ATTACK_RANGE);
					player[0].SetMoveSpeed(BALANCEPLAYER_SPEED);
					CharaIcon[0] = LoadGraph("..\\Data\\Icon\\バランスやられ.png");
					break;

				case POWERMODE:
					player[0].SetAttackMiddleRange(POWER_ATTACK_MIDDLE_RANGE);
					player[0].SetAttackRange(POWER_ATTACK_RANGE);
					player[0].SetMoveSpeed(POWERPLAYER_SPEED);
					CharaIcon[0] = LoadGraph("..\\Data\\Icon\\パワーやられ.png");
					break;
				}
				switch (player[1].GetType()) {
				case SPEEDMODE:
					player[1].SetAttackMiddleRange(SPEED_ATTACK_MIDDLE_RANGE);
					player[1].SetAttackRange(SPEED_ATTACK_RANGE);
					player[1].SetMoveSpeed(SPEEDPLAYER_SPEED);
					CharaIcon[1] = LoadGraph("..\\Data\\Icon\\白スピードやられ.png");
					break;

				case BALANCEMODE:
					player[1].SetAttackMiddleRange(BLANCE_ATTACK_MIDDLE_RANGE);
					player[1].SetAttackRange(BLANCE_ATTACK_RANGE);
					player[1].SetMoveSpeed(BALANCEPLAYER_SPEED);
					CharaIcon[1] = LoadGraph("..\\Data\\Icon\\白バランスやられ.png");
					break;

				case POWERMODE:
					player[1].SetAttackMiddleRange(POWER_ATTACK_MIDDLE_RANGE);
					player[1].SetAttackRange(POWER_ATTACK_RANGE);
					player[1].SetMoveSpeed(POWERPLAYER_SPEED);
					CharaIcon[1] = LoadGraph("..\\Data\\Icon\\白パワーやられ.png");
					break;
				}
			}
			if (CheckHitKey(KEY_INPUT_I) == 1 || key1 & PAD_INPUT_B)
				player[0].SetSelectFlg(TRUE);

			if (CheckHitKey(KEY_INPUT_O) == 1 || key2 & PAD_INPUT_B)
				player[1].SetSelectFlg(TRUE);

			if ((CheckHitKey(KEY_INPUT_K) == 1 || key1 & PAD_INPUT_C) && player[0].GetSelectFlg() == TRUE)
				player[0].SetSelectFlg(FALSE);

			if ((CheckHitKey(KEY_INPUT_L) == 1 || key2 & PAD_INPUT_C) && player[1].GetSelectFlg() == TRUE)
				player[1].SetSelectFlg(FALSE);

			g_Chara[0]->CharaChoice(g_Chara[0]);
			g_Chara[1]->CharaChoice(g_Chara[1]);

			if (continuous_limit > 0) {
				continuous_limit--;
			}
			if (continuous_limit < 0) {
				continuous_limit = 0;
			}

			SetDrawScreen(ScreenHandle);

			// 画面をクリア
			ClearDrawScreen();

			//カメラ情報の反映
			SetCameraPositionAndTargetAndUpVec(cpos, ctgt, VGet(0.0f, 1.0f, 0.0f));

			// アニメーション
			g_Chara[0]->AddPlay_Time(0.5f);
			g_Chara[1]->AddPlay_Time(0.5f);
			g_Chara[0]->AnimationType(g_Chara[0]);
			g_Chara[1]->AnimationType(g_Chara[1]);


			// モデルの移動(配置)
			MV1SetPosition(player[0].anim.type[player[0].GetType()], player[0].GetPosition());
			MV1SetPosition(player[1].anim.type[player[0].GetType()], player[1].GetPosition());

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
			MV1DrawModel(player[0].anim.type[player[0].GetType()]);
			MV1DrawModel(player[1].anim.type[player[1].GetType()]);

			if (player[0].GetPosition().x <= 1930) {
				SetFontSize(128);
				ChangeFont("HGS行書体");
				if (player[0].GetSelectFlg() == FALSE) {
					DrawString(130, 70, "プレイヤー１", GetColor(252, 0, 0));
					DrawString(100, 380, "<", GetColor(252, 0, 0));
					DrawString(830, 380, ">", GetColor(252, 0, 0));
				}
				else {
					DrawString(130, 70, "プレイヤー１", GetColor(255, 255, 0));
				}
				if (player[1].GetSelectFlg() == FALSE) {
					DrawString(1030, 70, "プレイヤー２", GetColor(0, 0, 252));
					DrawString(1000, 380, "<", GetColor(252, 0, 0));
					DrawString(1730, 380, ">", GetColor(252, 0, 0));
				}
				else {
					DrawString(1030, 70, "プレイヤー２", GetColor(255, 255, 0));
				}
			}

			// 描画対象を裏画面にする
			SetDrawScreen(DX_SCREEN_BACK);

			// 通常の描画結果を描画する
			DrawGraph(0, 0, ScreenHandle, FALSE);

			// --- 画面切り替え処理
			if (GamemodeChenge_flg == 1) {

				x += 30;
				x1 += 20;
				if (x >= 1500 && x <= 3000) {
					DrawBox(0, 0, 1920, 1080, GetColor(0, 0, 0), TRUE);
				}
				if (x >= 2000) {
					player[0].SetPosition(VGet(800.0f, 2200.0f, 0.0f));
					player[1].SetPosition(VGet(2200.0f, 2200.0f, 0.0f));
					cpos = VGet(1484.0f, 2360.0f, -1860.0f);
					ctgt = VGet(1484.0f, 2160.0f, -860.0f);
					// 背景(空)の操作
					skypos.x = cpos.x;
					skypos.y = cpos.y - 3000.0f;
					skypos.z = cpos.z;

					SetCameraPositionAndTargetAndUpVec(cpos, ctgt, VGet(0.0f, 1.0f, 0.0f));

					// モデルの回転
					MV1SetRotationXYZ(player[0].anim.model, VGet(0.0f, 1.57f * player[0].GetDirection(), 0.0f));
					MV1SetRotationXYZ(player[1].anim.model, VGet(0.0f, 1.57f * player[1].GetDirection(), 0.0f));
					// モデルの移動(配置)
					MV1SetPosition(player[0].anim.model, player[0].GetPosition());
					MV1SetPosition(player[1].anim.model, player[1].GetPosition());

					MV1SetPosition(skydate, skypos);

					// 画面をクリア
					ClearDrawScreen();
					// 描画
					Draw();
				}
				if (x >= 4500) {
					timelimit = GetNowHiPerformanceCount() + 96000000;
					GamemodeChenge_flg = 0;
					gamemode = eScenePlay1;
				}
				// BMP画像の表示
				//左から第一陣
				DrawGraph(-1000 + x, 0, BmpDate[0], TRUE);
				DrawGraph(-1000 + x, 360, BmpDate[1], TRUE);
				DrawGraph(-1000 + x, 690, BmpDate[2], TRUE);
				DrawGraph(-1000 + x1, 180, BmpDate[3], TRUE);
				DrawGraph(-1000 + x1, 540, BmpDate[4], TRUE);
				DrawGraph(-1000 + x1, 900, BmpDate[5], TRUE);
				//左から第二陣
				DrawGraph(-1500 + x, 0, BmpDate[0], TRUE);
				DrawGraph(-1500 + x, 360, BmpDate[1], TRUE);
				DrawGraph(-1500 + x, 690, BmpDate[2], TRUE);
				DrawGraph(-1500 + x, 180, BmpDate[3], TRUE);
				DrawGraph(-1500 + x, 540, BmpDate[4], TRUE);
				DrawGraph(-1500 + x, 900, BmpDate[5], TRUE);
				//右から第一陣
				DrawGraph(2000 - x, 0, BmpDate[0], TRUE);
				DrawGraph(2000 - x, 360, BmpDate[1], TRUE);
				DrawGraph(2000 - x, 690, BmpDate[2], TRUE);
				DrawGraph(2000 - x1, 180, BmpDate[3], TRUE);
				DrawGraph(2000 - x1, 540, BmpDate[4], TRUE);
				DrawGraph(2000 - x1, 900, BmpDate[5], TRUE);
				//右から第二陣
				DrawGraph(2500 - x, 0, BmpDate[0], TRUE);
				DrawGraph(2500 - x, 360, BmpDate[1], TRUE);
				DrawGraph(2500 - x, 690, BmpDate[2], TRUE);
				DrawGraph(2500 - x, 180, BmpDate[3], TRUE);
				DrawGraph(2500 - x, 540, BmpDate[4], TRUE);
				DrawGraph(2500 - x, 900, BmpDate[5], TRUE);
			}

			ScreenFlip();
			break;

			// ------------------------------------------------------------------------ //
			//																			//
			//								第1ステージ									//
			//																			//
			// ------------------------------------------------------------------------ //
		case eScenePlay1:
			if (timediff / 1000000 <= 90) {
				if (GamemodeChenge_flg == 0) {
					g_Chara[0]->ActionLoop(g_Chara[0], g_Chara[1]);
					g_Chara[1]->ActionLoop(g_Chara[1], g_Chara[0]);
					g_Chara[0]->Animation(g_Chara[0]);
					g_Chara[1]->Animation(g_Chara[1]);
					// カメラのスクロール
					cpos.y += 4.25f;
					// カメラの注視点操作
					ctgt.x = cpos.x;
					ctgt.y = cpos.y - 200.0f;
					ctgt.z = cpos.z + 1000.0f;			
				}
			}

			// スクリーンクリアー
			ClearDrawScreen();

			// 背景(空)の操作
			skypos.x = cpos.x;
			skypos.y = cpos.y - 3000.0f;
			skypos.z = cpos.z;

			SetCameraPositionAndTargetAndUpVec(cpos, ctgt, VGet(0.0f, 1.0f, 0.0f));

			// モデルの回転
			MV1SetRotationXYZ(player[0].anim.model, VGet(0.0f, 1.57f * player[0].GetDirection(), 0.0f));
			MV1SetRotationXYZ(player[1].anim.model, VGet(0.0f, 1.57f * player[1].GetDirection(), 0.0f));
			// モデルの移動(配置)
			MV1SetPosition(player[0].anim.model, player[0].GetPosition());
			MV1SetPosition(player[1].anim.model, player[1].GetPosition());

			MV1SetPosition(skydate, skypos);

			// 描画
			Draw();

			// 時間
			timediff = int(timelimit - GetNowHiPerformanceCount());
			if ( timediff / 1000000 <= 90 ) {
				wsprintf(drawtime, "%02d", timediff / 1000000);
				DrawString(900, 50, drawtime, GetColor(0, 0, 0));
				SetFontSize(120);
				DrawString(900, 50, drawtime, GetColor(255, 255, 0));
			}
			else {
				//制限時間を開始まで90秒で固定
				DrawString(900, 50, "90", GetColor(0, 0, 0));
				SetFontSize(120);
				DrawString(900, 50, "90", GetColor(255, 255, 0));

				//試合開始カウントダウン
				SetFontSize(210);
				if (timediff / 1000000 <= 94 && timediff / 1000000 > 93) {
					DrawString(920, 400, "3", GetColor(255, 0, 0), GetColor(0, 0, 0));
				}
				if (timediff / 1000000 <= 93 && timediff / 1000000 > 92) {
					DrawString(920, 400, "2", GetColor(255, 0, 0), GetColor(0, 0, 0));
				}
				if (timediff / 1000000 <= 92 && timediff / 1000000 > 91) {
					DrawString(920, 400, "1", GetColor(255, 0, 0), GetColor(0, 0, 0));
				}
				if (timediff / 1000000 <= 91) {
					DrawString(600, 350, "はじめ!!", GetColor(255, 0, 0), GetColor(0, 0, 0));
				}
			}

			if (DrawLimit > 0)
				DrawLimit--;

			if (DrawLimit < 0)
				DrawLimit = 0;

			// --- 画面切り替え処理
			if (GamemodeChenge_flg == 1) {
				x += 30;
				x1 += 20;

				if (x >= 1500 && x <= 3000) {
					DrawBox(0, 0, 1920, 1080, GetColor(0, 0, 0), TRUE);

					player[0].SetPosition(VGet( 600.0f,2100.0f, 0.0f));
					player[0].SetAct_Mode(eCharaFall);
					player[1].SetPosition(VGet(2400.0f,2100.0f, 0.0f));
					player[1].SetAct_Mode(eCharaFall);
					cpos = VGet(1484.0f, 2100.0f, -1700.0f);
					ctgt = VGet(1484.0f, 2100.0f, -1500.0f);
					MV1SetPosition(moon, VGet(0.0f, 3000.0f, 1000.0f));

					for (int i = 0; i <= MAX_BLOCK - 1; i++) {
						m_block[i].SetBlockFlag(FALSE);
						m_block2[i].SetBlockFlag(TRUE);
					}
				}
				if (x >= 2000) {
					//カメラ情報の反映
					SetCameraPositionAndTargetAndUpVec(cpos, ctgt, VGet(0.0f, 1.0f, 0.0f));

					// 背景(空)の操作
					skypos.x = cpos.x;
					skypos.y = cpos.y - 3000.0f;
					skypos.z = cpos.z;
					MV1SetPosition(skydate, skypos);

					// モデルの回転
					MV1SetRotationXYZ(player[0].anim.model, VGet(0.0f, 1.57f * player[0].GetDirection(), 0.0f));
					MV1SetRotationXYZ(player[1].anim.model, VGet(0.0f, 1.57f * player[1].GetDirection(), 0.0f));
					// モデルの移動(配置)
					MV1SetPosition(player[0].anim.model, player[0].GetPosition());
					MV1SetPosition(player[1].anim.model, player[1].GetPosition());

					// 画面をクリア
					ClearDrawScreen();

					//夜空描画
					DrawGraph(0, 0, BmpDate[6], TRUE);

					// 描画
					MV1DrawModel(moon);
					MV1DrawModel(roof);

					for (blockcnt = 0; blockcnt < 10; blockcnt++) {
						if (m_block2[blockcnt].GetBlockFlag() == TRUE) {
							MV1DrawModel(m_block2[blockcnt].b_model);
						}
					}

					// モデルの描画
					if (player[0].GetUse_Flg() == TRUE)
						MV1DrawModel(player[0].anim.model);
					if (player[1].GetUse_Flg() == TRUE)
						MV1DrawModel(player[1].anim.model);

					// スコア
					DrawGraph(0, 0, CharaIcon[0], TRUE);
					DrawGraph(1650, 0, CharaIcon[1], TRUE);

					SetFontSize(128);

					DrawString(20, 150, "???", GetColor(255, 255, 0));
					DrawString(1670, 150, "???", GetColor(255, 255, 0));
				}
				if (x >= 4500) {
					// ライトの色　黒
					SetLightDifColor(GetColorF(1.0f, 1.0f, 1.0f, 0.0f));
					timelimit = GetNowHiPerformanceCount() + 20000000;
					gamemode = eScenePlay2;
				}

				// BMP画像の表示
				//左から第一陣
				DrawGraph(-1000 + x, 0, BmpDate[0], TRUE);
				DrawGraph(-1000 + x, 360, BmpDate[1], TRUE);
				DrawGraph(-1000 + x, 690, BmpDate[2], TRUE);
				DrawGraph(-1000 + x1, 180, BmpDate[3], TRUE);
				DrawGraph(-1000 + x1, 540, BmpDate[4], TRUE);
				DrawGraph(-1000 + x1, 900, BmpDate[5], TRUE);
				//左から第二陣
				DrawGraph(-1500 + x, 0, BmpDate[0], TRUE);
				DrawGraph(-1500 + x, 360, BmpDate[1], TRUE);
				DrawGraph(-1500 + x, 690, BmpDate[2], TRUE);
				DrawGraph(-1500 + x, 180, BmpDate[3], TRUE);
				DrawGraph(-1500 + x, 540, BmpDate[4], TRUE);
				DrawGraph(-1500 + x, 900, BmpDate[5], TRUE);
				//右から第一陣
				DrawGraph(2000 - x, 0, BmpDate[0], TRUE);
				DrawGraph(2000 - x, 360, BmpDate[1], TRUE);
				DrawGraph(2000 - x, 690, BmpDate[2], TRUE);
				DrawGraph(2000 - x1, 180, BmpDate[3], TRUE);
				DrawGraph(2000 - x1, 540, BmpDate[4], TRUE);
				DrawGraph(2000 - x1, 900, BmpDate[5], TRUE);
				//右から第二陣
				DrawGraph(2500 - x, 0, BmpDate[0], TRUE);
				DrawGraph(2500 - x, 360, BmpDate[1], TRUE);
				DrawGraph(2500 - x, 690, BmpDate[2], TRUE);
				DrawGraph(2500 - x, 180, BmpDate[3], TRUE);
				DrawGraph(2500 - x, 540, BmpDate[4], TRUE);
				DrawGraph(2500 - x, 900, BmpDate[5], TRUE);
			}

			if ((timediff / 1000000 <= 20 && GamemodeChenge_flg != 1 )
				|| (CheckHitKey(KEY_INPUT_RETURN) == 1 && GamemodeChenge_flg != 1)) {
				GamemodeChenge_flg = 1;
				x  = 0;
				x1 = 0;
			}

			ScreenFlip();
			break;

// ------------------------------------------------------------------------ //
//																			//
//								第2ステージ									//
//																			//
// ------------------------------------------------------------------------ //
		case eScenePlay2:
			g_Chara[0]->ActionLoop(g_Chara[0], g_Chara[1]);
			g_Chara[1]->ActionLoop(g_Chara[1], g_Chara[0]);
			g_Chara[0]->Animation(g_Chara[0]);
			g_Chara[1]->Animation(g_Chara[1]);

			// スクリーンクリア
			ClearDrawScreen();

			//カメラ情報の反映
			SetCameraPositionAndTargetAndUpVec(cpos, ctgt, VGet(0.0f, 1.0f, 0.0f));

			// 背景(空)の操作
			skypos.x = cpos.x;
			skypos.y = cpos.y - 3000.0f;
			skypos.z = cpos.z;
			MV1SetPosition(skydate, skypos);

			// モデルの回転
			MV1SetRotationXYZ(player[0].anim.model, VGet(0.0f, 1.57f * player[0].GetDirection(), 0.0f));
			MV1SetRotationXYZ(player[1].anim.model, VGet(0.0f, 1.57f * player[1].GetDirection(), 0.0f));
			// モデルの移動(配置)
			MV1SetPosition(player[0].anim.model, player[0].GetPosition());
			MV1SetPosition(player[1].anim.model, player[1].GetPosition());

			DrawGraph(0, 0, BmpDate[6], TRUE);

			// 描画
			MV1DrawModel(moon);
			MV1DrawModel(roof);
			for (blockcnt = 0; blockcnt < 10; blockcnt++) {
				if (m_block2[blockcnt].GetBlockFlag() == TRUE) {
					MV1DrawModel(m_block2[blockcnt].b_model);
				}
			}

			// モデルの描画
			if (player[0].GetUse_Flg() == TRUE)
				MV1DrawModel(player[0].anim.model);
			if (player[1].GetUse_Flg() == TRUE)
				MV1DrawModel(player[1].anim.model);

			// スコア
			DrawGraph(0, 0, CharaIcon[0], TRUE);
			DrawGraph(1650, 0, CharaIcon[1], TRUE);

			SetFontSize(128);

			DrawString(  20, 150, "???", GetColor(255, 255, 0));
			DrawString(1670, 150, "???", GetColor(255, 255, 0));


			// 時間
			timediff = int(timelimit - GetNowHiPerformanceCount());
			wsprintf(drawtime, "%02d", timediff / 1000000);
			if (timediff / 1000000 <= 0) {
				DrawString(900, 50, "00", GetColor(0, 0, 0));
				SetFontSize(120);
				DrawString(900, 50, "00", GetColor(255, 0, 0));

				SetFontSize(FontSize);
				DrawString(850 - (FontSize * 2), 400, "そこまで!!", GetColor(255, 0, 0), GetColor(0, 0, 0));
				if (FontSize <= 200)
					FontSize += 10;
			}
			else if (timediff / 1000000 <= 3 ) {
				DrawString(900, 50, drawtime, GetColor(0, 0, 0));
				SetFontSize(120);
				DrawString(900, 50, drawtime, GetColor(255, 0, 0));
			}
			else {
				DrawString(900, 50, drawtime, GetColor(0, 0, 0));
				SetFontSize(120);
				DrawString(900, 50, drawtime, GetColor(255, 255, 0));
			}

			if (timediff / 1000000 <= -3) {
				gamemode = eSceneClear;
			}

			ScreenFlip();
			break;

		case eSceneClear:
			// スクリーンクリア
			ClearDrawScreen();

			DrawGraph(0, 0, BmpDate[6], TRUE);

			ScreenFlip();
			break;
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
	return 0;
}

