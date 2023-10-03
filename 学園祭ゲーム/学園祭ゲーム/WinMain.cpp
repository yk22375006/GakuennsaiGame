
#include "Common.h"		// --- ‘Sƒtƒ@ƒCƒ‹‚Å‚Ì‹¤’Êƒwƒbƒ_[

int WINAPI WinMain(HINSTANCE hI,HINSTANCE hP,LPSTR lpC,int nC){
	
	int ScreenHandle;

	float camera_direction = 0.0f;
	
	// ‘S‘Ì“I‚ÈƒQ[ƒ€‚ÌŠÇ—
	int gamemode = eSceneBlank ;

	//ƒXƒe[ƒW‚Ìƒ|ƒWƒVƒ‡ƒ“
	VECTOR stagepos = VGet(0.0f,0.0f,0.0f) ;
	VECTOR skypos = VGet(0.0f, 0.0f, 0.0f);
		
		
	// ƒJƒƒ‰ƒ|ƒWƒVƒ‡ƒ“ cpos:ƒJƒƒ‰ˆÊ’u@ctgt:ƒJƒƒ‰’‹“_
	cpos = VGet(3500.0f, 2300.0f, -3500.0f);

//	cpos = VGet(500.0f,1000.0f,-2000.0f) ;
	ctgt = VGet(0.0f,500.0f,-400.0f) ;
	cadd = VGet(0.0f, 0.0f, 0.0f);

<<<<<<< HEAD
	ChangeWindowMode(TRUE);
	SetGraphMode(1440, 810, 32);
=======
	ChangeWindowMode(FALSE);
	SetGraphMode(1920, 1080, 32);
>>>>>>> origin/ã•ã™ã‚‰ã„ã®åç„¡ã—ã®ãƒ–ãƒ©ãƒ³ãƒã ãŠ

	// DXƒ‰ƒCƒuƒ‰ƒŠ‚Ì‰Šú‰»				DXƒ‰ƒCƒuƒ‰ƒŠ[ƒXƒ^[ƒg
	if(DxLib_Init() == -1) return -1 ;

	ScreenHandle = MakeScreen(1920, 1080, FALSE);


	// ƒXƒe[ƒWî•ñ‚Ì“Ç‚İ‚İ
	// ƒRƒ~ƒbƒg—pƒRƒƒ“ƒg
	// ƒXƒe[ƒWî•ñ‚Ì“Ç‚İ‚İ
	skydate = MV1LoadModel("..\\Data\\Stage\\ƒXƒJƒCƒh[ƒ€.mv1");
	if (skydate == -1) return -1;

	MV1SetUseZBuffer(skydate, false);
	// ”wŒi“Ç‚İ‚İ
	bgdate[BACKGROUNDTATAMI] = MV1LoadModel("..\\Data\\Stage\\”wŒi_ôsub.mv1");
	stagedate = MV1LoadModel("..\\Data\\Stage\\Îô.mv1");
	MV1SetPosition(stagedate, VGet(1500.0f, 100.0f, -100.0f));
	MV1SetUseZBuffer(skydate, false);

	// ƒuƒƒbƒNƒ‚ƒfƒ‹‚Ì“Ç‚İ‚İ

	blockdate[TATAMI_BLOCK]		= MV1LoadModel("..\\Data\\Stage\\ô.mv1");
	blockdate[BREAK_BLOCK]		= MV1LoadModel("..\\Data\\Stage\\–ØŞ.mv1");
	blockdate[FALL_BLOCK]		= MV1LoadModel("..\\Data\\Stage\\—‰ºƒuƒƒbƒN.mv1");
	blockdate[INVINCIBLE_BLOCK]	= MV1LoadModel("..\\Data\\Stage\\–³“Gô.mv1");
	blockdate[MOVE_BLOCK]		= MV1LoadModel("..\\Data\\Stage\\ˆÚ“®°.mv1");
	blockdate[NEEDLE_BLOCK]		= MV1LoadModel("..\\Data\\Stage\\™.mv1");
	blockdate[WOOD_BLOCK]		= MV1LoadModel("..\\Data\\Stage\\’Œ.mv1");
	// ƒvƒŒƒCƒ„[‚Ìì¬
	player[0].anim.model = MV1LoadModel("..\\Data\\Ninja\\”’”EÒ.mv1");
	player[1].anim.model = MV1LoadModel("..\\Data\\Ninja\\”EÒ.mv1");

	//	Atten0 = 0.3f;
	//	Atten1 = 0.0f;
	//	Atten2 = 0.0f;
	//	C_DirectionX = 0.0f * (DX_PI_F / 180.0f);
	//	C_DirectionY = 270.0f * (DX_PI_F / 180.0f);
	//	C_DirectionZ = 0.0f;
	// ƒXƒ|ƒbƒgƒ‰ƒCƒg
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

	// ƒ‰ƒCƒg‚Ì•ûŒü‚ğİ’è
	SetLightDirection( VGet( 0.0f, -0.5f, 0.5f ) );
	ShadowMapHandle = MakeShadowMap( 1024, 1024 ) ;

	// ƒ‰ƒCƒg‚ÌF@•
	SetLightDifColor(GetColorF(0.5f, 0.5f, 0.5f, 0.0f));

	// ƒVƒƒƒhƒEƒ}ƒbƒv‚ª‘z’è‚·‚éƒ‰ƒCƒg‚Ì•ûŒü‚àƒZƒbƒg
	SetShadowMapLightDirection( ShadowMapHandle, VGet( 0.0f, -0.5f, 0.5f ) ) ;

	// ƒVƒƒƒhƒEƒ}ƒbƒv‚É•`‰æ‚·‚é”ÍˆÍ‚ğİ’è
	SetShadowMapDrawArea( ShadowMapHandle, VGet( -5000.0f, -10.0f, -5000.0f ), VGet( 5000.0f, 1000.0f, 5000.0f ) ) ;

	SetDrawScreen(DX_SCREEN_BACK);

	for (int i = 0; i < BACKGROUNDFLOOR; i++) {
		bg_tatami[i] = MV1DuplicateModel(bgdate[BACKGROUNDTATAMI]);
		MV1SetPosition(bg_tatami[i], VGet(1500.0f, 100.0f + (i * 800.0f), 100.0f));
	}

	blockcnt = 0;
	// ƒ}ƒbƒvƒf[ƒ^‚É”½‰f
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

	/* ------------------------------------------------------------------------------------------------
												ƒQ[ƒ€ƒ‹[ƒv										
	 ----------------------------------------------------------------------------------------------- */
	while(ProcessMessage() == 0 && CheckHitKey(KEY_INPUT_ESCAPE) == 0){
		MV1SetUseZBuffer(skydate, false);

						
		switch(gamemode){
			case eSceneBlank :
				gamemode = eSceneChoice;
				g_Chara[0] = &player[0];
				g_Chara[1] = &player[1];
				break;

			case eSceneTitle:
				if (CheckHitKey(KEY_INPUT_SPACE) == 1) {
					gamemode = eSceneChoice;
				}
				break;

			case eSceneChoice:
				SetDrawScreen(ScreenHandle);

				// ‰æ–Ê‚ğƒNƒŠƒA
				ClearDrawScreen();

				cpos = VGet(0.0f, 1000.0f, -1500.0f);
				ctgt = VGet(0.0f, 2000.0f, 0.0f);
				cadd = VGet(0.0f, 0.0f, 0.0f);

				player[0].SetPosition(VGet(200.0f, 200.0f, 0.0f));
//				player[1].pos = VGet(600.0f, 300.0f, 200.0f);
				player[1].SetPosition(VGet(0.0f, 2000.0f, 0.0f));

				//ƒJƒƒ‰î•ñ‚Ì”½‰f
				SetCameraPositionAndTargetAndUpVec(cpos, ctgt, VGet(0.0f, 1.0f, 0.0f));

				// ƒ‚ƒfƒ‹‚ÌˆÚ“®(”z’u)
				MV1SetRotationXYZ(player[0].anim.model, VGet(0.0f, 1.57f * player[0].GetDirection(), 0.0f));
				MV1SetPosition(player[0].anim.model, player[0].GetPosition());
				MV1SetRotationXYZ(player[1].anim.model, VGet(0.0f, 1.57f * player[1].GetDirection(), 0.0f));
				MV1SetPosition(player[1].anim.model, player[1].GetPosition());

				// ƒVƒƒƒhƒEƒ}ƒbƒv‚Ö‚Ì•`‰æ‚Ì€”õ
				ShadowMap_DrawSetup(ShadowMapHandle);

				// ƒ‚ƒfƒ‹‚Ì•`‰æ - ‰e‚Ì•`‰æ
				MV1DrawModel(player[0].anim.model);
				MV1DrawModel(player[1].anim.model);

				// ƒVƒƒƒhƒEƒ}ƒbƒv‚Ö‚Ì•`‰æ‚ğI—¹
				ShadowMap_DrawEnd();

				// •`‰æ‚Ég—p‚·‚éƒVƒƒƒhƒEƒ}ƒbƒv‚ğİ’è
				SetUseShadowMap(0, ShadowMapHandle);

				// ’n–Ê(”z’u)••`‰æ
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

				SetLightRangeAttenHandle(LHandle_p1, Range, Atten0, Atten1, Atten2);
				SetLightAngleHandle(LHandle_p1, 0.24582103f, 6.28318548f);
				SetLightPositionHandle(LHandle_p1, VGet(player[0].GetPosition().x, player[0].GetPosition().y + 100.0f, player[0].GetPosition().z - 500.0f)); // ƒ‰ƒCƒg‚ÌˆÊ’u
				SetLightPositionHandle(LHandle_p2, VGet(player[1].GetPosition().x, player[1].GetPosition().y + 100.0f, player[1].GetPosition().z - 500.0f)); // ƒ‰ƒCƒg‚ÌˆÊ’u
			//	SetLightDirectionHandle(LHandle_p1, VGet(ctgt.x = cpos.x , ctgt.y = cpos.y - 400   , ctgt.z = cpos.z ));  // ƒ‰ƒCƒg‚Ì•ûŒü
			//	SetLightAngleHandle(LHandle_p1, 0.78f, 0.5f);

				// •`‰æ‚Ég—p‚·‚éƒVƒƒƒhƒEƒ}ƒbƒv‚Ìİ’è‚ğ‰ğœ
				SetUseShadowMap(0, -1);

				// ‚W•ª‚Ì‚P‚Ék¬‚µ‚½‰æ‘œ‚ğƒKƒEƒXƒtƒBƒ‹ƒ^‚Å‚Ú‚©‚·
				GraphFilter(ScreenHandle, DX_GRAPH_FILTER_GAUSS, 16, 1400);

				// ƒ‚ƒfƒ‹‚Ì•`‰æ
				MV1DrawModel(player[0].anim.model);
				MV1DrawModel(player[1].anim.model);

				// •`‰æ‘ÎÛ‚ğ— ‰æ–Ê‚É‚·‚é
				SetDrawScreen(DX_SCREEN_BACK);

				// ’Êí‚Ì•`‰æŒ‹‰Ê‚ğ•`‰æ‚·‚é
				DrawGraph(0, 0, ScreenHandle, FALSE);

				ScreenFlip();

				if (CheckHitKey(KEY_INPUT_RETURN) == 1) {
					player[0].SetPosition(VGet(200.0f, 1800.0f, 0.0f));
					player[1].SetPosition(VGet(2800.0f, 1800.0f, 0.0f));
					cpos = VGet(1484.0f, 2360.0f, -1860.0f);

					gamemode = eScenePlay;
				}
				break;

			case eScenePlay :
				g_Chara[0]->ActionLoop(g_Chara[0], g_Chara[1]);
				g_Chara[1]->ActionLoop(g_Chara[1], g_Chara[0]);

				// ƒAƒjƒ[ƒVƒ‡ƒ“‚Ì”½‰f
//				MV1SetAttachAnimTime(player[0].anim.model, player[0].GetAnim_Attach(), player[0].GetAnim_Time());
//				MV1SetAttachAnimTime(player[1].anim.model, player[1].GetAnim_Attach(), player[1].GetAnim_Time());
//				PlayerMove();
				ClearDrawScreen() ;
				// ƒJƒƒ‰‚Ì‹“_‘€ì
				CameraMove();

				// ”wŒi(‹ó)‚Ì‘€ì
				skypos.x = cpos.x;
				skypos.y = cpos.y - 3000.0f;
				skypos.z = cpos.z;

				SetCameraPositionAndTargetAndUpVec(cpos,ctgt,VGet(0.0f,1.0f,0.0f)) ;

				// ƒ‚ƒfƒ‹‚Ì‰ñ“]
				MV1SetRotationXYZ(player[0].anim.model,VGet(0.0f,1.57f * player[0].GetDirection(),0.0f)) ;
				// ƒ‚ƒfƒ‹‚ÌˆÚ“®(”z’u)
				MV1SetPosition(player[0].anim.model,player[0].GetPosition());

				// ƒ‚ƒfƒ‹‚Ì‰ñ“]
				MV1SetRotationXYZ(player[1].anim.model, VGet(0.0f, 1.57f * player[1].GetDirection(), 0.0f));
				// ƒ‚ƒfƒ‹‚ÌˆÚ“®(”z’u)
				MV1SetPosition(player[1].anim.model ,player[1].GetPosition());

				MV1SetPosition(skydate, skypos);

				// •`‰æ
				Draw();

				ScreenFlip() ;
				break ;

			case eSceneClear :
				break ;
		}
	}

	// ƒ‰ƒCƒgƒnƒ“ƒhƒ‹‚Ìíœ
	DeleteLightHandle(LHandle_p1);
	DeleteLightHandle(LHandle_p2);
	// ƒVƒƒƒhƒEƒ}ƒbƒv‚Ìíœ
	DeleteShadowMap(ShadowMapHandle);
	// ƒLƒƒƒ‰ƒNƒ^[ƒ‚ƒfƒ‹‚Ìíœ
	MV1DeleteModel(player[0].anim.model);
	MV1DeleteModel(player[1].anim.model);
	// ƒuƒƒbƒNƒ‚ƒfƒ‹‚Ìíœ
	MV1DeleteModel(blockdate[TATAMI_BLOCK]);
	MV1DeleteModel(blockdate[FALL_BLOCK]);
	MV1DeleteModel(blockdate[NEEDLE_BLOCK]);
	MV1DeleteModel(blockdate[WOOD_BLOCK]);
	// ”wŒi‚Ìíœ
	MV1DeleteModel(bgdate[BACKGROUNDTATAMI]);
	DxLib_End();
	return 0 ;
}

