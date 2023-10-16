
#include "Common.h"		// --- �S�t�@�C���ł̋��ʃw�b�_�[

int WINAPI WinMain(HINSTANCE hI,HINSTANCE hP,LPSTR lpC,int nC){
	
	int ScreenHandle;
	int Gauss = 0;			//�K�E�X�t�B���^�傫��
	int BmpDate[7];			// �a�l�o�摜�̃������ւ̓ǂ݂���

	float camera_direction = 0.0f;
	
	//�X�e�[�W�̃|�W�V����
	VECTOR stagepos = VGet(0.0f,0.0f,0.0f) ;
	VECTOR skypos = VGet(0.0f, 0.0f, 0.0f);
		
//	SetGraphMode(1280, 720, 32);
	ChangeWindowMode(FALSE);
	SetGraphMode(1920, 1080, 32);

	// DX���C�u�����̏�����				DX���C�u�����[�X�^�[�g
	if(DxLib_Init() == -1) return -1 ;

	ScreenHandle = MakeScreen(1920, 1080, FALSE);

	// �X�e�[�W���̓ǂݍ���
	skydate = MV1LoadModel("..\\Data\\Stage\\�X�J�C�h�[��.mv1");

	MV1SetUseZBuffer(skydate, false);
	// �w�i�ǂݍ���
	bgdate[BACKGROUNDTATAMI] = MV1LoadModel("..\\Data\\Stage\\�w�i_��.mv1");
	stagedate = MV1LoadModel("..\\Data\\Stage\\�Ώ�.mv1");
	MV1SetPosition(stagedate, VGet(1500.0f, 100.0f, -100.0f));
	MV1SetUseZBuffer(skydate, false);

	// �u���b�N���f���̓ǂݍ���
	blockdate[TATAMI_BLOCK]		= MV1LoadModel("..\\Data\\Stage\\��.mv1");
	blockdate[BREAK_BLOCK]		= MV1LoadModel("..\\Data\\Stage\\�؍�.mv1");
	blockdate[FALL_BLOCK]		= MV1LoadModel("..\\Data\\Stage\\�����u���b�N.mv1");
	blockdate[INVINCIBLE_BLOCK]	= MV1LoadModel("..\\Data\\Stage\\���G��.mv1");
	blockdate[NEEDLE_BLOCK]		= MV1LoadModel("..\\Data\\Stage\\��.mv1");
	blockdate[WOOD_BLOCK]		= MV1LoadModel("..\\Data\\Stage\\��.mv1");
	blockdate[MOVE_BLOCK_X]		= MV1LoadModel("..\\Data\\Stage\\�ړ���.mv1");

	//�����f���̓ǂݍ���
	moon = MV1LoadModel("..\\Data\\Stage\\moon.mv1");
	//�郂�f���̓ǂݍ���
	castle = MV1LoadModel("..\\Data\\japanese-castle\\source\\japanese castle 2.mv1");
	//�郂�f���̓ǂݍ���
	roof = MV1LoadModel("..\\Data\\Stage\\��.mv1");

	Original[0].type[SPEEDMODE]			= MV1LoadModel("..\\Data\\Ninja\\�E��_�ꖳ.mv1");
	Original[0].typestop[SPEEDMODE]		= MV1LoadModel("..\\Data\\Ninja\\�E��_�ꖳ_�ҋ@.mv1");

	Original[0].type[BALANCEMODE]		= MV1LoadModel("..\\Data\\Ninja\\�E��_�o�����X.mv1");
	Original[0].typestop[BALANCEMODE]	= MV1LoadModel("..\\Data\\Ninja\\�E�ґҋ@_�o�����X.mv1");

	Original[0].type[POWERMODE]			= MV1LoadModel("..\\Data\\Ninja\\�E�҃p���[.mv1");
	Original[0].typestop[POWERMODE]		= MV1LoadModel("..\\Data\\Ninja\\�E�ґҋ@_�p���[.mv1");

	Original[1].type[SPEEDMODE]			= MV1LoadModel("..\\Data\\Ninja\\���E��_�ꖳ.mv1");
	Original[1].typestop[SPEEDMODE]		= MV1LoadModel("..\\Data\\Ninja\\���E��_�ꖳ_�ҋ@.mv1");
	
	Original[1].type[BALANCEMODE]		= MV1LoadModel("..\\Data\\Ninja\\�E��_�o�����X.mv1");
	Original[1].typestop[BALANCEMODE]	= MV1LoadModel("..\\Data\\Ninja\\�E�ґҋ@_�o�����X.mv1");
	
	Original[1].type[POWERMODE]			= MV1LoadModel("..\\Data\\Ninja\\���E�҃p���[.mv1");
	Original[1].typestop[POWERMODE]		= MV1LoadModel("..\\Data\\Ninja\\�E�ґҋ@_�p���[.mv1");

	// �v���C���[�̍쐬
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

	Original[0].run = MV1LoadModel("..\\Data\\Ninja\\�E��_�ꖳ_�ړ�.mv1");			// ����A�j��
	Original[0].jump_in = MV1LoadModel("..\\Data\\Ninja\\�E��_�ꖳ_�W�����v�J�n.mv1");	// �W�����v����n�߃A�j��
	Original[0].jump = MV1LoadModel("..\\Data\\Ninja\\�E��_�ꖳ_�W�����v��.mv1");	// �W�����v���[�v�A�j��
	Original[0].fall = MV1LoadModel("..\\Data\\Ninja\\�E��_�ꖳ_����.mv1");			// �W�����v���[�v�A�j��
	Original[0].attack = MV1LoadModel("..\\Data\\Ninja\\�E��_�ꖳ_�U��.mv1");			// �U���A�j��
	Original[0].damage = MV1LoadModel("..\\Data\\Ninja\\�E��_�ꖳ_�_���[�W.mv1");		// ��_���[�W�A�j��

	Original[1].run = MV1LoadModel("..\\Data\\Ninja\\�E�ґ���_�o�����X.mv1");		// ����A�j��
	Original[1].jump_in = MV1LoadModel("..\\Data\\Ninja\\�E��_�ꖳ_�W�����v�J�n.mv1");	// �W�����v����n�߃A�j��
	Original[1].jump = MV1LoadModel("..\\Data\\Ninja\\�E�҃W�����v_�o�����X.mv1");	// �W�����v���[�v�A�j��
	Original[1].fall = MV1LoadModel("..\\Data\\Ninja\\�E�җ���_�o�����X.mv1");		// �W�����v���[�v�A�j��
	Original[1].attack = MV1LoadModel("..\\Data\\Ninja\\�E�ҍU��_�o�����X.mv1");		// �U���A�j��
	Original[1].damage = MV1LoadModel("..\\Data\\Ninja\\�E�҃_���[�W_�o�����X.mv1");	// ��_���[�W�A�j��

	// �X�|�b�g���C�g
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

	// ���C�g�̕�����ݒ�
	SetLightDirection( VGet( 0.0f, -0.5f, 0.5f ) );
	ShadowMapHandle = MakeShadowMap( 1024, 1024 ) ;

	// ���C�g�̐F�@��
	SetLightDifColor(GetColorF(0.5f, 0.5f, 0.5f, 0.0f));

	// �V���h�E�}�b�v���z�肷�郉�C�g�̕������Z�b�g
	SetShadowMapLightDirection( ShadowMapHandle, VGet( 0.0f, -0.5f, 0.5f ) ) ;

	// �V���h�E�}�b�v�ɕ`�悷��͈͂�ݒ�
	SetShadowMapDrawArea( ShadowMapHandle, VGet( -5000.0f, -10.0f, -5000.0f ), VGet( 5000.0f, 1000.0f, 5000.0f ) ) ;

	SetDrawScreen(DX_SCREEN_BACK);

	// �u���b�N�̏����Z�b�g
	m_block->init();

	//�� �����Z�b�g
	MV1SetPosition(moon, VGet(600.0f, 1000.0f, 1000.0f));
	//�� �����Z�b�g
	MV1SetPosition(castle, VGet(3000.0f, 170.0f, 3000.0f));
	MV1SetRotationXYZ(castle, VGet(0.0f, 1.57f * 1.3f, 0.0f));
	//���� �����Z�b�g
	MV1SetPosition(roof, VGet(1550.0f, -1000.0f, 700.0f));

	//�摜�̓ǂݍ���
	BmpDate[0] = LoadGraph("..\\Data\\Stage\\�����_�G�t�F�N�g1.png");
	BmpDate[1] = LoadGraph("..\\Data\\Stage\\�����_�G�t�F�N�g2.png");
	BmpDate[2] = LoadGraph("..\\Data\\Stage\\�����_�G�t�F�N�g3.png");
	BmpDate[3] = LoadGraph("..\\Data\\Stage\\�����_�G�t�F�N�g4.png");
	BmpDate[4] = LoadGraph("..\\Data\\Stage\\�����_�G�t�F�N�g5.png");
	BmpDate[5] = LoadGraph("..\\Data\\Stage\\�����_�G�t�F�N�g6.png");
	BmpDate[6] = LoadGraph("..\\Data\\Stage\\milky2.jpg");


	/* ------------------------------------------------------------------------------------------------
												�Q�[�����[�v										
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

				//�J�������̔��f
				SetCameraPositionAndTargetAndUpVec(cpos, ctgt, VGet(0.0f, 1.0f, 0.0f));

				g_Chara[0] = &player[0];
				g_Chara[1] = &player[1];

				gamemode = eSceneTitle;
				DrawLimit = 0;
				continuous_limit = 0;
				break;

			case eSceneTitle:

				ClearDrawScreen();

				// �n��(�z�u)���`��
				MV1DrawModel(skydate);
				MV1DrawModel(stagedate);
				MV1DrawModel(moon);
				MV1DrawModel(castle);

				ScreenFlip();
				key1 = GetJoypadInputState(DX_INPUT_KEY_PAD1);
//				if (key1 & PAD_INPUT_A) {
				if (CheckHitKey(KEY_INPUT_RETURN) == 1) {
						gamemode = eSceneChoice;
					chara_type1 = SPEEDMODE;
					chara_type2 = SPEEDMODE;
					player[1].SetPosition(VGet(3000.0f, 200.0f, 500.0f));
					player[0].ChangeAnimationType(g_Chara[0], player[0].anim.typestop[chara_type1]);
					player[1].ChangeAnimationType(g_Chara[1], player[1].anim.typestop[chara_type2]);

				}
/*				if (CheckHitKey(KEY_INPUT_RETURN) == 1) {
					player[0].SetPosition(VGet(200.0f, 2200.0f, 0.0f));
					player[1].SetPosition(VGet(2800.0f, 2200.0f, 0.0f));
					cpos = VGet(1484.0f, 2360.0f, -1860.0f);
					ctgt = VGet(0.0f, 1000.0f, 0.0f);
					gamemode = eScenePlay1;
				}
*/				break;

			case eSceneChoice:
				if (player[1].GetPosition().x >= 1930) {
					player[0].SetPosition(VGet(800.0f + x, 150.0f, 500.0f));
					player[1].SetPosition(VGet(2400.0f - x, 150.0f, 500.0f));
					Gauss += 20;
					if (GamemodeChenge_flg != 1)
						x += 20;
				}
				key1 = GetJoypadInputState(DX_INPUT_KEY_PAD1);
//				if (key1 & PAD_INPUT_B && GamemodeChenge_flg != 1) {
				if (CheckHitKey(KEY_INPUT_RETURN) == 1 && GamemodeChenge_flg != 1) {
						GamemodeChenge_flg = 1;
					x = 0;
					x1 = 0;
					player[0].LoadAnimation(g_Chara[0]);
					player[1].LoadAnimation(g_Chara[1]);
					player[0].ChangeAnimation(g_Chara[0], player[0].anim.stop);
					player[1].ChangeAnimation(g_Chara[1], player[1].anim.stop);
				}
				g_Chara[0]->CharaChoice(g_Chara[0]);
				g_Chara[1]->CharaChoice(g_Chara[1]);

				if (continuous_limit > 0) {
					continuous_limit--;
				}
				if (continuous_limit < 0) {
					continuous_limit = 0;
				}

				SetDrawScreen(ScreenHandle);

				// ��ʂ��N���A
				ClearDrawScreen();

				//�J�������̔��f
				SetCameraPositionAndTargetAndUpVec(cpos, ctgt, VGet(0.0f, 1.0f, 0.0f));

				// �A�j���[�V����
				g_Chara[0]->AddPlay_Time(0.5f);
				g_Chara[1]->AddPlay_Time(0.5f);
				g_Chara[0]->AnimationType(g_Chara[0]);
				g_Chara[1]->AnimationType(g_Chara[1]);


				// ���f���̈ړ�(�z�u)
				MV1SetPosition(player[0].anim.type[chara_type1], player[0].GetPosition());
				MV1SetPosition(player[1].anim.type[chara_type2], player[1].GetPosition());

				// �n��(�z�u)���`��
				MV1DrawModel(skydate);
				MV1DrawModel(stagedate);
				MV1DrawModel(moon);
				MV1DrawModel(castle);

				SetLightAngleHandle(LHandle_p1, 0.24582103f, 6.28318548f);
				SetLightPositionHandle(LHandle_p1, VGet(player[0].GetPosition().x, player[0].GetPosition().y + 100.0f, player[0].GetPosition().z - 500.0f)); // ���C�g�̈ʒu
				SetLightPositionHandle(LHandle_p2, VGet(player[1].GetPosition().x, player[1].GetPosition().y + 100.0f, player[1].GetPosition().z - 500.0f)); // ���C�g�̈ʒu

				// �W���̂P�ɏk�������摜���K�E�X�t�B���^�łڂ���
				GraphFilter(ScreenHandle, DX_GRAPH_FILTER_GAUSS, 32, Gauss);

				// ���f���̕`��
				MV1DrawModel(player[0].anim.type[chara_type1]); 
				MV1DrawModel(player[1].anim.type[chara_type2]);

				if (player[0].GetPosition().x <= 1930) {
					SetFontSize(128);
					ChangeFont("HGS�s����");
					DrawString(130, 70, "�v���C���[�P", GetColor(252, 252, 252));
					DrawString(1030, 70, "�v���C���[�Q", GetColor(252, 252, 252));

					DrawString(100, 380, "<", GetColor(252, 0, 0));
					DrawString(830, 380, ">", GetColor(252, 0, 0));

					DrawString(1000, 380, "<", GetColor(252, 0, 0));
					DrawString(1730, 380, ">", GetColor(252, 0, 0));
				}

				// �`��Ώۂ𗠉�ʂɂ���
				SetDrawScreen(DX_SCREEN_BACK);

				// �ʏ�̕`�挋�ʂ�`�悷��
				DrawGraph(0, 0, ScreenHandle, FALSE);
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
						// �w�i(��)�̑���
						skypos.x = cpos.x;
						skypos.y = cpos.y - 3000.0f;
						skypos.z = cpos.z;

						SetCameraPositionAndTargetAndUpVec(cpos, ctgt, VGet(0.0f, 1.0f, 0.0f));

						// ���f���̉�]
						MV1SetRotationXYZ(player[0].anim.model, VGet(0.0f, 1.57f * player[0].GetDirection(), 0.0f));
						MV1SetRotationXYZ(player[1].anim.model, VGet(0.0f, 1.57f * player[1].GetDirection(), 0.0f));
						// ���f���̈ړ�(�z�u)
						MV1SetPosition(player[0].anim.model, player[0].GetPosition());
						MV1SetPosition(player[1].anim.model, player[1].GetPosition());

						MV1SetPosition(skydate, skypos);

						// ��ʂ��N���A
						ClearDrawScreen();
						// �`��
						Draw();
					}
					if (x >= 4500) {
						gamemode = eScenePlay1;
					}
					// BMP�摜�̕\��
					//��������w
					DrawGraph(-1000 + x, 0, BmpDate[0], TRUE);
					DrawGraph(-1000 + x, 360, BmpDate[1], TRUE);
					DrawGraph(-1000 + x, 690, BmpDate[2], TRUE);
					DrawGraph(-1000 + x1, 180, BmpDate[3], TRUE);
					DrawGraph(-1000 + x1, 540, BmpDate[4], TRUE);
					DrawGraph(-1000 + x1, 900, BmpDate[5], TRUE);
					//��������w
					DrawGraph(-1500 + x, 0, BmpDate[0], TRUE);
					DrawGraph(-1500 + x, 360, BmpDate[1], TRUE);
					DrawGraph(-1500 + x, 690, BmpDate[2], TRUE);
					DrawGraph(-1500 + x, 180, BmpDate[3], TRUE);
					DrawGraph(-1500 + x, 540, BmpDate[4], TRUE);
					DrawGraph(-1500 + x, 900, BmpDate[5], TRUE);
					//�E������w
					DrawGraph(2000 - x, 0, BmpDate[0], TRUE);
					DrawGraph(2000 - x, 360, BmpDate[1], TRUE);
					DrawGraph(2000 - x, 690, BmpDate[2], TRUE);
					DrawGraph(2000 - x1, 180, BmpDate[3], TRUE);
					DrawGraph(2000 - x1, 540, BmpDate[4], TRUE);
					DrawGraph(2000 - x1, 900, BmpDate[5], TRUE);
					//�E������w
					DrawGraph(2500 - x, 0, BmpDate[0], TRUE);
					DrawGraph(2500 - x, 360, BmpDate[1], TRUE);
					DrawGraph(2500 - x, 690, BmpDate[2], TRUE);
					DrawGraph(2500 - x, 180, BmpDate[3], TRUE);
					DrawGraph(2500 - x, 540, BmpDate[4], TRUE);
					DrawGraph(2500 - x, 900, BmpDate[5], TRUE);
				}

				ScreenFlip();
				break;

			case eScenePlay1 :
				g_Chara[0]->ActionLoop(g_Chara[0], g_Chara[1]);
				g_Chara[1]->ActionLoop(g_Chara[1], g_Chara[0]);
				g_Chara[0]->Animation(g_Chara[0]);
				g_Chara[1]->Animation(g_Chara[1]);

				// �X�N���[���N���A�[
				ClearDrawScreen() ;
				// �J�����̎��_����
				CameraMove();

				// �w�i(��)�̑���
				skypos.x = cpos.x;
				skypos.y = cpos.y - 3000.0f;
				skypos.z = cpos.z;

				SetCameraPositionAndTargetAndUpVec(cpos,ctgt,VGet(0.0f,1.0f,0.0f)) ;

				// ���f���̉�]
				MV1SetRotationXYZ(player[0].anim.model, VGet(0.0f, 1.57f * player[0].GetDirection(), 0.0f));
				MV1SetRotationXYZ(player[1].anim.model, VGet(0.0f, 1.57f * player[1].GetDirection(), 0.0f));
				// ���f���̈ړ�(�z�u)
				MV1SetPosition(player[0].anim.model, player[0].GetPosition());
				MV1SetPosition(player[1].anim.model, player[1].GetPosition());

				MV1SetPosition(skydate, skypos);

				// �`��
				Draw();

				if (DrawLimit > 0)
					DrawLimit--;

				if (DrawLimit < 0)
					DrawLimit = 0;

				ScreenFlip() ;

				if (cpos.y >= 18500 || CheckHitKey(KEY_INPUT_RETURN) == 1) {
					cpos = VGet(1484.0f, 2100.0f, -1700.0f);
					ctgt = VGet(1484.0f, 2100.0f, -1500.0f);
					MV1SetPosition(moon, VGet(300.0f, 2700.0f, 0.0f));
					for (int i = 0; i <= MAX_BLOCK - 1;i++) {
						m_block[i].SetBlockFlag(FALSE);
						m_block2[i].SetBlockFlag(TRUE);
					}

					// ���C�g�̐F�@��
					SetLightDifColor(GetColorF(1.0f, 1.0f, 1.0f, 0.0f));

					gamemode = eScenePlay2;
				}
				break ;

			case eScenePlay2:		
				g_Chara[0]->ActionLoop(g_Chara[0], g_Chara[1]);
				g_Chara[1]->ActionLoop(g_Chara[1], g_Chara[0]);
				g_Chara[0]->Animation(g_Chara[0]);
				g_Chara[1]->Animation(g_Chara[1]);

				// �X�N���[���N���A
				ClearDrawScreen();

				//�J�������̔��f
				SetCameraPositionAndTargetAndUpVec(cpos, ctgt, VGet(0.0f, 1.0f, 0.0f));

				// �w�i(��)�̑���
				skypos.x = cpos.x;
				skypos.y = cpos.y - 3000.0f;
				skypos.z = cpos.z;
				MV1SetPosition(skydate, skypos);
				
				// ���f���̉�]
				MV1SetRotationXYZ(player[0].anim.model, VGet(0.0f, 1.57f * player[0].GetDirection(), 0.0f));
				MV1SetRotationXYZ(player[1].anim.model, VGet(0.0f, 1.57f * player[1].GetDirection(), 0.0f));
				// ���f���̈ړ�(�z�u)
				MV1SetPosition(player[0].anim.model, player[0].GetPosition());
				MV1SetPosition(player[1].anim.model, player[1].GetPosition());

				DrawGraph(0, 0, BmpDate[6], TRUE);

				// �`��
				MV1DrawModel(moon);
				MV1DrawModel(roof);
				for (blockcnt = 0; blockcnt < 30; blockcnt++) {
					if (m_block2[blockcnt].GetBlockFlag() == TRUE) {
						MV1DrawModel(m_block2[blockcnt].b_model);
					}
				}

				// ���f���̕`��
				if (player[0].GetUse_Flg() == TRUE)
					MV1DrawModel(player[0].anim.model);
				if (player[1].GetUse_Flg() == TRUE)
					MV1DrawModel(player[1].anim.model);

				ScreenFlip();
				break;

			case eSceneClear :
				break ;
		}
	}

	// ���C�g�n���h���̍폜
	DeleteLightHandle(LHandle_p1);
	DeleteLightHandle(LHandle_p2);
	// �V���h�E�}�b�v�̍폜
	DeleteShadowMap(ShadowMapHandle);
	// �L�����N�^�[���f���̍폜
	MV1DeleteModel(player[0].anim.model);
	MV1DeleteModel(player[1].anim.model);
	// �u���b�N���f���̍폜
	MV1DeleteModel(blockdate[TATAMI_BLOCK]);
	MV1DeleteModel(blockdate[FALL_BLOCK]);
	MV1DeleteModel(blockdate[NEEDLE_BLOCK]);
	MV1DeleteModel(blockdate[WOOD_BLOCK]);
	// �w�i�̍폜
	MV1DeleteModel(bgdate[BACKGROUNDTATAMI]);
	DxLib_End();
	return 0 ;
}

