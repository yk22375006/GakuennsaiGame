
#include "Common.h"		// --- 全ファイルでの共通ヘッダー

int WINAPI WinMain(HINSTANCE hI, HINSTANCE hP, LPSTR lpC, int nC) {
	
	int ScreenHandle;
	int Gauss = 0;			//ガウスフィルタ大きさ
	int BmpDate[8];			// ＢＭＰ画像のメモリへの読みこみ
	int SE_flg[4] = { 0,0,0,0 };

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
	bgdate[BACKGROUNDTATAMI]	= MV1LoadModel("..\\Data\\Stage\\背景_畳.mv1");
	bg_roof						= MV1LoadModel("..\\Data\\Stage\\背景_瓦.mv1");
	stagedate					= MV1LoadModel("..\\Data\\Stage\\石畳.mv1");
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

	// 月モデルの読み込み
	moon	= MV1LoadModel("..\\Data\\Stage\\moon.mv1");
	// 城モデルの読み込み
	castle	= MV1LoadModel("..\\Data\\japanese-castle\\城.mv1");
	// 屋根モデルの読み込み
	roof	= MV1LoadModel("..\\Data\\Stage\\瓦.mv1");
	// 表彰台モデルの読み込み
	rizarut	= MV1LoadModel("..\\Data\\Stage\\表彰台.mv1");

	// 
	Original[0].type[SPEEDMODE]			= MV1LoadModel("..\\Data\\Ninja\\忍者_苦無.mv1");
	Original[0].typestop[SPEEDMODE]		= MV1LoadModel("..\\Data\\Ninja\\忍者_苦無_待機.mv1");

	Original[0].type[BALANCEMODE]		= MV1LoadModel("..\\Data\\Ninja\\忍者_バランス.mv1");
	Original[0].typestop[BALANCEMODE]	= MV1LoadModel("..\\Data\\Ninja\\忍者_バランス_待機.mv1");
	
	Original[0].type[POWERMODE]			= MV1LoadModel("..\\Data\\Ninja\\忍者_パワー.mv1");
	Original[0].typestop[POWERMODE]		= MV1LoadModel("..\\Data\\Ninja\\忍者_パワー_待機.mv1");

	Original[1].type[SPEEDMODE]			= MV1LoadModel("..\\Data\\Ninja\\白忍者_苦無.mv1");
	Original[1].typestop[SPEEDMODE]		= MV1DuplicateModel(Original[0].typestop[SPEEDMODE]);

	Original[1].type[BALANCEMODE]		= MV1LoadModel("..\\Data\\Ninja\\白忍者_バランス.mv1");
	Original[1].typestop[BALANCEMODE]	= MV1DuplicateModel(Original[0].typestop[BALANCEMODE]);

	Original[1].type[POWERMODE]			= MV1LoadModel("..\\Data\\Ninja\\白忍者_パワー.mv1");
	Original[1].typestop[POWERMODE]		= MV1DuplicateModel(Original[0].typestop[POWERMODE]);

	// プレイヤーの作成
	player[0].anim.type[SPEEDMODE]			= MV1DuplicateModel(Original[0].type[SPEEDMODE]);
	player[0].anim.typestop[SPEEDMODE]		= MV1DuplicateModel(Original[0].typestop[SPEEDMODE]);
	player[0].anim.type[BALANCEMODE]		= MV1DuplicateModel(Original[0].type[BALANCEMODE]);
	player[0].anim.typestop[BALANCEMODE]	= MV1DuplicateModel(Original[0].typestop[BALANCEMODE]);
	player[0].anim.type[POWERMODE]			= MV1DuplicateModel(Original[0].type[POWERMODE]);
	player[0].anim.typestop[POWERMODE]		= MV1DuplicateModel(Original[0].typestop[POWERMODE]);

	player[1].anim.type[SPEEDMODE]			= MV1DuplicateModel(Original[1].type[SPEEDMODE]);
	player[1].anim.typestop[SPEEDMODE]		= MV1DuplicateModel(Original[1].typestop[SPEEDMODE]);;
	player[1].anim.type[BALANCEMODE]		= MV1DuplicateModel(Original[1].type[BALANCEMODE]);
	player[1].anim.typestop[BALANCEMODE]	= MV1DuplicateModel(Original[1].typestop[BALANCEMODE]);
	player[1].anim.type[POWERMODE]			= MV1DuplicateModel(Original[1].type[POWERMODE]);
	player[1].anim.typestop[POWERMODE]		= MV1DuplicateModel(Original[1].typestop[POWERMODE]);

	Original[0].run		= MV1LoadModel("..\\Data\\Ninja\\忍者_苦無_移動.mv1");
	Original[0].jump_in	= MV1LoadModel("..\\Data\\Ninja\\忍者_苦無_ジャンプ開始.mv1");
	Original[0].jump	= MV1LoadModel("..\\Data\\Ninja\\忍者_苦無_ジャンプ中.mv1");
	Original[0].fall	= MV1LoadModel("..\\Data\\Ninja\\忍者_苦無_落下.mv1");
	Original[0].attack	= MV1LoadModel("..\\Data\\Ninja\\忍者_苦無_攻撃.mv1");
	Original[0].damage	= MV1LoadModel("..\\Data\\Ninja\\忍者_苦無_ダメージ.mv1");

	Original[1].run		= MV1LoadModel("..\\Data\\Ninja\\忍者_バランス_移動.mv1");
	Original[1].jump_in	= MV1LoadModel("..\\Data\\Ninja\\忍者_苦無_ジャンプ開始.mv1");
	Original[1].jump	= MV1LoadModel("..\\Data\\Ninja\\忍者_バランス_ジャンプ中.mv1");
	Original[1].fall	= MV1LoadModel("..\\Data\\Ninja\\忍者_バランス_落下.mv1");
	Original[1].attack	= MV1LoadModel("..\\Data\\Ninja\\忍者_バランス_攻撃.mv1");
	Original[1].damage	= MV1LoadModel("..\\Data\\Ninja\\忍者_バランス_ダメージ.mv1");

	Original[2].run		= MV1LoadModel("..\\Data\\Ninja\\忍者_パワー_移動.mv1");
	Original[2].jump_in	= MV1LoadModel("..\\Data\\Ninja\\忍者_苦無_ジャンプ開始.mv1");
	Original[2].jump	= MV1LoadModel("..\\Data\\Ninja\\忍者_パワー_ジャンプ.mv1");
	Original[2].fall	= MV1LoadModel("..\\Data\\Ninja\\忍者_パワー_落下.mv1");
	Original[2].attack	= MV1LoadModel("..\\Data\\Ninja\\忍者_パワー_攻撃.mv1");
	Original[2].damage	= MV1LoadModel("..\\Data\\Ninja\\忍者_パワー_ダメージ.mv1");

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

	// ライトの色 白
	SetLightDifColor(GetColorF(1.0f, 1.0f, 1.0f, 0.0f));

	// シャドウマップが想定するライトの方向もセット
	SetShadowMapLightDirection(ShadowMapHandle, VGet(0.0f, 0.0f, 0.5f));

	// シャドウマップに描画する範囲を設定
	SetShadowMapDrawArea(ShadowMapHandle, VGet(-100.0f, -10.0f, -100.0f), VGet(3000.0f, 20000.0f, 1000.0f));

	SetDrawScreen(DX_SCREEN_BACK);

	//月 初期セット
	MV1SetPosition(moon, VGet(600.0f, 1000.0f, 1000.0f));
	//城 初期セット
	MV1SetPosition(castle, VGet(3000.0f, 300.0f, 3000.0f));
	MV1SetRotationXYZ(castle, VGet(0.0f, 1.57f * 1.3f, 0.0f));
	//屋根 初期セット
	MV1SetPosition(roof, VGet(1550.0f, -1000.0f, 700.0f));
	//表彰台　初期セット
	MV1SetPosition(rizarut, VGet(1600.0f, 100.0f, 1000.0f));

	//画像の読み込み
	BmpDate[0] = LoadGraph("..\\Data\\Stage\\金箔雲エフェクト1.png");
	BmpDate[1] = LoadGraph("..\\Data\\Stage\\金箔雲エフェクト2.png");
	BmpDate[2] = LoadGraph("..\\Data\\Stage\\金箔雲エフェクト3.png");
	BmpDate[3] = LoadGraph("..\\Data\\Stage\\金箔雲エフェクト4.png");
	BmpDate[4] = LoadGraph("..\\Data\\Stage\\金箔雲エフェクト5.png");
	BmpDate[5] = LoadGraph("..\\Data\\Stage\\金箔雲エフェクト6.png");
	BmpDate[6] = LoadGraph("..\\Data\\Stage\\milky2.jpg");
	BmpDate[7] = LoadGraph("..\\Data\\Stage\\makimono.png");

	//音楽ファイル読み込み
	SHandle[TITLE_BGM] = LoadSoundMem("..\\Data\\Sound\\BGM\\TitleBGM.ogg");
	SHandle[GAME_BGM] = LoadSoundMem("..\\Data\\Sound\\BGM\\GameBGM.ogg");
	SHandle[GAME2_BGM] = LoadSoundMem("..\\Data\\Sound\\BGM\\GameBGM2.ogg");
	//	SHandle[RESULT_BGM] = LoadSoundMem("..\\Data\\Sound\\BGM\\GameBGM.mp3");
	SHandle[GAMESTARTBUTTON_SE] = LoadSoundMem("..\\Data\\Sound\\SE\\GameStartButton.mp3");
	SHandle[MAPCHENGE_SE] = LoadSoundMem("..\\Data\\Sound\\SE\\MapChange.mp3");
	SHandle[TAIKO1_SE] = LoadSoundMem("..\\Data\\Sound\\SE\\Taiko1.mp3");
	SHandle[TAIKO2_SE] = LoadSoundMem("..\\Data\\Sound\\SE\\Taiko2.mp3");
	SHandle[BLOCKBREAK_SE] = LoadSoundMem("..\\Data\\Sound\\SE\\BlockBreak.mp3");

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

				// ブロックの初期セット
				m_block->init();

				//カメラ情報の反映
				SetCameraPositionAndTargetAndUpVec(cpos, ctgt, VGet(0.0f, 1.0f, 0.0f));

				MobInit();

				g_Chara[0] = &player[0];
				g_Chara[1] = &player[1];

				player[0].LoadSE(g_Chara[0]);
				player[1].LoadSE(g_Chara[1]);

				gamemode = eSceneTitle;
				DrawLimit = 0;

				// BGMの再生
				PlaySoundMem(SHandle[TITLE_BGM], DX_PLAYTYPE_LOOP, TRUE);
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
				MobDraw();

				DrawGraph(300, 50, BmpDate[7], TRUE);
				SetFontSize(200);
				ChangeFont("HGS行書体");
				DrawString(450, 120, "攻城忍法帖", GetColor(252, 0, 0));

				ScreenFlip();
				key[0] = GetJoypadInputState(DX_INPUT_KEY_PAD1);
				key[1] = GetJoypadInputState(DX_INPUT_PAD2);
				if ((key[0] & PAD_INPUT_START) || (key[1] & PAD_INPUT_START)) {
					gamemode = eSceneChoice;
					player[0].SetType(SPEEDMODE);
					player[1].SetType(SPEEDMODE);
					player[1].SetPosition(VGet(3000.0f, 200.0f, 500.0f));
					player[0].ChangeAnimationType(g_Chara[0], player[0].anim.typestop[player[0].GetType()]);
					player[1].ChangeAnimationType(g_Chara[1], player[1].anim.typestop[player[1].GetType()]);
					// BGMの再生
					PlaySoundMem(SHandle[TAIKO1_SE], DX_PLAYTYPE_BACK, TRUE);
				}
				if (CheckHitKey(KEY_INPUT_SPACE) == 1) {
					gamemode = eSceneChoice;
					player[0].SetType(SPEEDMODE);
					player[1].SetType(SPEEDMODE);
					player[1].SetPosition(VGet(3000.0f, 200.0f, 500.0f));
					player[0].ChangeAnimationType(g_Chara[0], player[0].anim.typestop[player[0].GetType()]);
					player[1].ChangeAnimationType(g_Chara[1], player[1].anim.typestop[player[1].GetType()]);
					// BGMの再生
					PlaySoundMem(SHandle[TAIKO1_SE], DX_PLAYTYPE_BACK, TRUE);
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
				key[0] = GetJoypadInputState(DX_INPUT_KEY_PAD1);
				key[1] = GetJoypadInputState(DX_INPUT_PAD2);
				if (((key[0] & PAD_INPUT_B) || (CheckHitKey(KEY_INPUT_RETURN) == 1)) && GamemodeChenge_flg != 1 &&
					player[0].GetSelectFlg() == TRUE && player[1].GetSelectFlg() == TRUE) {
					// SEの再生
					PlaySoundMem(SHandle[GAMESTARTBUTTON_SE], DX_PLAYTYPE_BACK, TRUE);

					GamemodeChenge_flg = 1;
					x = 0;
					x1 = 0;
					for (int i = 0; i < 2; i++) {
						player[0].LoadAnimation(g_Chara[0]);
						player[1].LoadAnimation(g_Chara[1]);
						player[0].ChangeAnimation(g_Chara[0], player[0].anim.stop);
						player[1].ChangeAnimation(g_Chara[1], player[1].anim.stop);
						switch (player[0].GetType()) {
							case SPEEDMODE:
								player[i].SetAttackMiddleRange(SPEED_ATTACK_MIDDLE_RANGE);
								player[i].SetAttackRange(SPEED_ATTACK_RANGE);
								player[i].SetMoveSpeed(SPEEDPLAYER_SPEED);
								player[i].SetBlowDistance(SPEEDBLOWDISTANCE);
								player[i].SetAttackTimeStart(SPEED_ATTACK_START);
								player[i].SetAttackTimeEnd(SPEED_ATTACK_END);
								player[i].SetInitialVelocity(SPEED_JUMP_SPEED);
								player[i].SetGravity(SPEED_FALL_SPEED);
								if (i == 0)
									CharaIcon[i] = LoadGraph("..\\Data\\Icon\\スピードやられ.png");
								if (i == 1)
									CharaIcon[i] = LoadGraph("..\\Data\\Icon\\白スピードやられ.png");
								break;

							case BALANCEMODE:
								player[i].SetAttackMiddleRange(BLANCE_ATTACK_MIDDLE_RANGE);
								player[i].SetAttackRange(BLANCE_ATTACK_RANGE);
								player[i].SetMoveSpeed(BALANCEPLAYER_SPEED);
								player[i].SetBlowDistance(BALANCEBLOWDISTANCE);
								player[i].SetAttackTimeStart(BALANCE_ATTACK_START);
								player[i].SetAttackTimeEnd(BALANCE_ATTACK_END);
								player[i].SetInitialVelocity(BALANCE_JUMP_SPEED);
								player[i].SetGravity(BALANCE_FALL_SPEED);
								if (i == 0)
									CharaIcon[i] = LoadGraph("..\\Data\\Icon\\バランスやられ.png");
								if (i == 1)
									CharaIcon[i] = LoadGraph("..\\Data\\Icon\\白バランスやられ.png");
								break;

							case POWERMODE:
								player[i].SetAttackMiddleRange(POWER_ATTACK_MIDDLE_RANGE);
								player[i].SetAttackRange(POWER_ATTACK_RANGE);
								player[i].SetMoveSpeed(POWERPLAYER_SPEED);
								player[i].SetBlowDistance(POWERBLOWDISTANCE);
								player[i].SetAttackTimeStart(POWER_ATTACK_START);
								player[i].SetAttackTimeEnd(POWER_ATTACK_END);
								player[i].SetInitialVelocity(POWER_JUMP_SPEED);
								player[i].SetGravity(POWER_FALL_SPEED);
								if (i == 0)
									CharaIcon[i] = LoadGraph("..\\Data\\Icon\\パワーやられ.png");
								if (i == 1)
									CharaIcon[i] = LoadGraph("..\\Data\\Icon\\黒パワーやられ.png");
								break;
						}
					}
				}
				for (int i = 0; i < 2; i++) {
					if (key[i] & PAD_INPUT_B && player[i].GetRepeatedLimit() == 0) {
						player[i].SetSelectFlg(TRUE);
						player[i].SetRepeatedLimit(15);
					}
				}

				if (CheckHitKey(KEY_INPUT_I) == 1 || key[0] & PAD_INPUT_B) {
					player[0].SetSelectFlg(TRUE);
					// SEの再生
					PlaySoundMem(player[0].SoundHandle[CHARA_DECISION_SE], DX_PLAYTYPE_BACK, TRUE);
				}
				if (CheckHitKey(KEY_INPUT_O) == 1 || key[1] & PAD_INPUT_B) {
					player[1].SetSelectFlg(TRUE);
					// SEの再生
					PlaySoundMem(player[1].SoundHandle[CHARA_DECISION_SE], DX_PLAYTYPE_BACK, TRUE);
				}
				if ((CheckHitKey(KEY_INPUT_K) == 1 || key[0] & PAD_INPUT_C) && player[0].GetSelectFlg() == TRUE) {
					player[0].SetSelectFlg(FALSE);
					// SEの再生
					PlaySoundMem(player[0].SoundHandle[CANCEL_SE], DX_PLAYTYPE_BACK, TRUE);
				}
				if ((CheckHitKey(KEY_INPUT_L) == 1 || key[1] & PAD_INPUT_C) && player[1].GetSelectFlg() == TRUE) {
					player[1].SetSelectFlg(FALSE);
					// SEの再生
					PlaySoundMem(player[1].SoundHandle[CANCEL_SE], DX_PLAYTYPE_BACK, TRUE);
				}


				SetDrawScreen(ScreenHandle);

				// 画面をクリア
				ClearDrawScreen();

			//カメラ情報の反映
				SetCameraPositionAndTargetAndUpVec(cpos, ctgt, VGet(0.0f, 1.0f, 0.0f));

				for (int i = 0; i < 2; i++) {
					g_Chara[i]->CharaChoice(g_Chara[i]);
					g_Chara[i]->RepeatedProces(g_Chara[i]);
					// アニメーション
					g_Chara[i]->AddPlay_Time(0.5f);
					g_Chara[i]->AnimationType(g_Chara[i]);

				}

				// モデルの移動(配置)
				MV1SetPosition(player[0].anim.type[player[0].GetType()], player[0].GetPosition());
				MV1SetPosition(player[1].anim.type[player[1].GetType()], player[1].GetPosition());

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
						cpos = VGet(1484.0f, 2360.0f, -2460.0f);
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
					if (SE_flg[0] == 0) {
						PlaySoundMem(SHandle[MAPCHENGE_SE], DX_PLAYTYPE_BACK, TRUE);
						// BGMの停止
						StopSoundMem(SHandle[TITLE_BGM]);
						SE_flg[0] = 1;
					}
					if (x >= 4500) {
						timelimit = GetNowHiPerformanceCount() + 96000000;

						// ライトの色　黒
						SetLightDifColor(GetColorF(0.5f, 0.5f, 0.5f, 0.0f));

						StopSoundMem(SHandle[MAPCHENGE_SE]);

						SE_flg[0] = 0;
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
				// 時間
				timediff = int(timelimit - GetNowHiPerformanceCount());
				if (timediff / 1000000 <= 90) {
					if (GamemodeChenge_flg == 0) {
						g_Chara[0]->ActionLoop(g_Chara[0], g_Chara[1]);
						g_Chara[1]->ActionLoop(g_Chara[1], g_Chara[0]);
						g_Chara[0]->Animation(g_Chara[0]);
						g_Chara[1]->Animation(g_Chara[1]);
						g_Chara[0]->RepeatedProces(g_Chara[0]);
						g_Chara[1]->RepeatedProces(g_Chara[1]);
						// カメラのスクロール
						cpos.y += 4.25f;
						// カメラの注視点操作
						ctgt.x = cpos.x;
						ctgt.y = cpos.y - 200.0f;
						ctgt.z = cpos.z + 1600.0f;			
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

					if (SE_flg[0] == 0) {
						// BGMの再生
						PlaySoundMem(SHandle[GAME_BGM], DX_PLAYTYPE_LOOP, TRUE);
						SE_flg[0] = 1;
					}
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
						if (SE_flg[0] == 0) {
							// BGMの再生
							PlaySoundMem(SHandle[TAIKO1_SE], DX_PLAYTYPE_BACK, TRUE);
							SE_flg[0] = 1;
						}
					}
					if (timediff / 1000000 <= 93 && timediff / 1000000 > 92) {
						DrawString(920, 400, "2", GetColor(255, 0, 0), GetColor(0, 0, 0));
						// BGMの再生
						if (SE_flg[1] == 0) {
							// BGMの再生
							PlaySoundMem(SHandle[TAIKO1_SE], DX_PLAYTYPE_BACK, TRUE);
							SE_flg[1] = 1;
						}
					}
					if (timediff / 1000000 <= 92 && timediff / 1000000 > 91) {
						DrawString(920, 400, "1", GetColor(255, 0, 0), GetColor(0, 0, 0));
						// BGMの再生
						if (SE_flg[2] == 0) {
							// BGMの再生
							PlaySoundMem(SHandle[TAIKO1_SE], DX_PLAYTYPE_BACK, TRUE);
							SE_flg[2] = 1;
						}
					}
					if (timediff / 1000000 <= 91) {
						DrawString(600, 350, "はじめ!!", GetColor(255, 0, 0), GetColor(0, 0, 0));
						// BGMの再生
						if (SE_flg[3] == 0) {
							// BGMの再生
							PlaySoundMem(SHandle[TAIKO2_SE], DX_PLAYTYPE_BACK, TRUE);
							SE_flg[3] = 1;
							SE_flg[0] = 0;
						}
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

					SE_flg[0] = 0;

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

						for (blockcnt = 0; blockcnt < MAX_BLOCK2; blockcnt++) {
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
				if (SE_flg[0] == 0) {
					PlaySoundMem(SHandle[MAPCHENGE_SE], DX_PLAYTYPE_BACK, TRUE);
					SE_flg[0] = 1;
				}
				if (x >= 4500) {
					// ライトの色 白
					SetLightDifColor(GetColorF(1.0f, 1.0f, 1.0f, 0.0f));
					timelimit = GetNowHiPerformanceCount() + 20000000;

					// BGMの再生
					PlaySoundMem(SHandle[GAME2_BGM], DX_PLAYTYPE_LOOP, TRUE);
					// BGMの停止
					StopSoundMem(SHandle[GAME_BGM]);
					StopSoundMem(SHandle[MAPCHENGE_SE]);

					SE_flg[0] = 0;
					SE_flg[1] = 0;
					SE_flg[2] = 0;
					SE_flg[3] = 0;
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
				for (blockcnt = 0; blockcnt < MAX_BLOCK2; blockcnt++) {
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

				if (SE_flg[3] == 0 && FontSize >= 200) {
					// BGMの再生
					PlaySoundMem(SHandle[TAIKO2_SE], DX_PLAYTYPE_BACK, TRUE);
					SE_flg[3] = 1;
					SE_flg[0] = 0;
				}
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
				cpos = VGet(1600.0f, 170.0f, -100.0f);
				ctgt = VGet(1600.0f, 200.0f, 0.0f);

				ClearDrawScreen();
				SetLightDifColor(GetColorF(0.9f, 0.9f, 0.9f, 0.0f));
				player[0].ChangeAnimation(g_Chara[0], player[0].anim.stop);
				player[1].ChangeAnimation(g_Chara[1], player[1].anim.stop);

				player[0].SetPosition(VGet(1100.0f, 250.0f, 900.0f));
				player[1].SetPosition(VGet(2300.0f, 100.0f, 1000.0f));

				MV1SetPosition(player[0].anim.model, player[0].GetPosition());
				MV1SetPosition(player[1].anim.model, player[1].GetPosition());

				player[0].SetDirection(DOWN);
				player[1].SetDirection(DOWN);

				// 地面(配置)＆描画
				MV1DrawModel(skydate);
				MV1DrawModel(stagedate);
				MV1DrawModel(moon);
				MV1DrawModel(castle);
				MV1DrawModel(rizarut);
				// プレイヤー
				MV1DrawModel(player[0].anim.model);
				MV1DrawModel(player[1].anim.model);

				// 空
				skypos.x = cpos.x;
				skypos.y = cpos.y;
				skypos.z = cpos.z;

				MV1SetPosition(skydate, skypos);
				// プレイヤー		
			//	player[0].SetPosition(VGet(800.0f + x, 150.0f, 500.0f));		

				// モブ
				mob[0].use_flg = TRUE;
				mob[0].pos = VGet(700.0f, 300.0f, 1100.0f);

				mob[1].use_flg = TRUE;
				mob[1].pos = VGet(1100.0f, 300.0f, 1400.0f);

				mob[2].use_flg = TRUE;
				mob[2].pos = VGet(1600.0f, 300.0f, 1700.0f);

				mob[3].use_flg = TRUE;
				mob[3].pos = VGet(2000.0f, 300.0f, 1400.0f);

				mob[4].use_flg = TRUE;
				mob[4].pos = VGet(2500.0f, 300.0f, 1100.0f);

				MobDraw();

				// 城
				MV1SetPosition(castle, VGet(1600.0f, 170.0f, 3300.0f));
				MV1SetRotationXYZ(castle, VGet(0.0f, 1.57f, 0.0f));
				MV1SetPosition(moon, VGet(800.0f, 900.0f, 1000.0f));

				SetCameraPositionAndTargetAndUpVec(cpos, ctgt, VGet(0.0f, 1.0f, 0.0f));
				SetFontSize(180);
				DrawString(800, 100, "勝者", GetColor(252, 252, 0));

				// アイコン
				DrawGraph(0, 0, CharaIcon[0], TRUE);
				DrawGraph(1600, 0, CharaIcon[1], TRUE);
				SetFontSize(120);

				wsprintf(DrawScore1, "%d", player[0].GetScore());
				DrawString(50, 150, DrawScore1, GetColor(255, 2, 0));
				wsprintf(DrawScore2, "%d", player[1].GetScore());
				DrawString(1670, 150, DrawScore2, GetColor(255, 5, 0));

				//DrawGraph(0, 0, BmpDate[6], TRUE);
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

