
#include "Common.h"		// --- �S�t�@�C���ł̋��ʃw�b�_�[

int WINAPI WinMain(HINSTANCE hI,HINSTANCE hP,LPSTR lpC,int nC){
	
	int ScreenHandle;
	int Gauss = 0;			//�K�E�X�t�B���^�傫��

	float camera_direction = 0.0f;
	
	// �S�̓I�ȃQ�[���̊Ǘ�
	int gamemode = eSceneBlank ;

	//�X�e�[�W�̃|�W�V����
	VECTOR stagepos = VGet(0.0f,0.0f,0.0f) ;
	VECTOR skypos = VGet(0.0f, 0.0f, 0.0f);
		
	ChangeWindowMode(FALSE);
	SetGraphMode(1920, 1080, 32);

	// DX���C�u�����̏�����				DX���C�u�����[�X�^�[�g
	if(DxLib_Init() == -1) return -1 ;

	ScreenHandle = MakeScreen(1920, 1080, FALSE);

	// �X�e�[�W���̓ǂݍ���
	skydate = MV1LoadModel("..\\Data\\Stage\\�X�J�C�h�[��.mv1");

	MV1SetUseZBuffer(skydate, false);
	// �w�i�ǂݍ���
	bgdate[BACKGROUNDTATAMI] = MV1LoadModel("..\\Data\\Stage\\�w�i_��sub.mv1");
	stagedate = MV1LoadModel("..\\Data\\Stage\\�Ώ�.mv1");
	MV1SetPosition(stagedate, VGet(1500.0f, 100.0f, -100.0f));
	MV1SetUseZBuffer(skydate, false);

	// �u���b�N���f���̓ǂݍ���
	blockdate[TATAMI_BLOCK]		= MV1LoadModel("..\\Data\\Stage\\��.mv1");
	blockdate[BREAK_BLOCK]		= MV1LoadModel("..\\Data\\Stage\\�؍�.mv1");
	blockdate[FALL_BLOCK]		= MV1LoadModel("..\\Data\\Stage\\�����u���b�N.mv1");
	blockdate[INVINCIBLE_BLOCK]	= MV1LoadModel("..\\Data\\Stage\\���G��.mv1");
	blockdate[MOVE_BLOCK]		= MV1LoadModel("..\\Data\\Stage\\�ړ���.mv1");
	blockdate[NEEDLE_BLOCK]		= MV1LoadModel("..\\Data\\Stage\\��.mv1");
	blockdate[WOOD_BLOCK]		= MV1LoadModel("..\\Data\\Stage\\��.mv1");

	//�����f���̓ǂݍ���
	moon = MV1LoadModel("..\\Data\\Stage\\moon.mv1");
	//�郂�f���̓ǂݍ���
	castle = MV1LoadModel("..\\Data\\japanese-castle\\source\\japanese castle 2.mv1");

	// �v���C���[�̍쐬
	player[0].anim.model = MV1LoadModel("..\\Data\\Ninja\\���E��.mv1");
	player[1].anim.model = MV1LoadModel("..\\Data\\Ninja\\�E��.mv1");
	player[0].SetPosition(VGet(3000.0f, 200.0f, 500.0f));

	//	Atten0 = 0.3f;
	//	Atten1 = 0.0f;
	//	Atten2 = 0.0f;
	//	C_DirectionX = 0.0f * (DX_PI_F / 180.0f);
	//	C_DirectionY = 270.0f * (DX_PI_F / 180.0f);
	//	C_DirectionZ = 0.0f;

	// �X�|�b�g���C�g
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

	for (int i = 0; i < BACKGROUNDFLOOR; i++) {
		bg_tatami[i] = MV1DuplicateModel(bgdate[BACKGROUNDTATAMI]);
		MV1SetPosition(bg_tatami[i], VGet(1500.0f, 100.0f + (i * 800.0f), 100.0f));
	}

	blockcnt = 0;
	// �}�b�v�f�[�^�ɔ��f
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

	//�� �����Z�b�g
	MV1SetPosition(moon, VGet(600.0f, 1000.0f, 1000.0f));
	//�� �����Z�b�g
	MV1SetPosition(castle, VGet(3000.0f, 170.0f, 3000.0f));
	MV1SetRotationXYZ(castle, VGet(0.0f, 1.57f * 1.3f, 0.0f));

	// �a�l�o�摜�̃������ւ̓ǂ݂���
	static int GHandle[6];
	GHandle[0] = LoadGraph("..\\Data\\Stage\\�����_�G�t�F�N�g1.png");
	GHandle[1] = LoadGraph("..\\Data\\Stage\\�����_�G�t�F�N�g2.png");
	GHandle[2] = LoadGraph("..\\Data\\Stage\\�����_�G�t�F�N�g3.png");
	GHandle[3] = LoadGraph("..\\Data\\Stage\\�����_�G�t�F�N�g4.png");
	GHandle[4] = LoadGraph("..\\Data\\Stage\\�����_�G�t�F�N�g5.png");
	GHandle[5] = LoadGraph("..\\Data\\Stage\\�����_�G�t�F�N�g6.png");


	/* ------------------------------------------------------------------------------------------------
												�Q�[�����[�v										
	 ----------------------------------------------------------------------------------------------- */
	while(ProcessMessage() == 0 && CheckHitKey(KEY_INPUT_ESCAPE) == 0){
		static int x = 0;

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
				break;

			case eSceneTitle:

				ClearDrawScreen();

				// �n��(�z�u)���`��
				MV1DrawModel(skydate);
				MV1DrawModel(stagedate);
				MV1DrawModel(moon);
				MV1DrawModel(castle);

				// BMP�摜�̕\��
				LoadGraphScreen(0, 0, "..\\Data\\Stage\\�����_�G�t�F�N�g1.png", TRUE);
				LoadGraphScreen(0, 360, "..\\Data\\Stage\\�����_�G�t�F�N�g2.png", TRUE);
				LoadGraphScreen(0, 690, "..\\Data\\Stage\\�����_�G�t�F�N�g3.png", TRUE);
				LoadGraphScreen(1000, 0, "..\\Data\\Stage\\�����_�G�t�F�N�g4.png", TRUE);
				LoadGraphScreen(1000, 360, "..\\Data\\Stage\\�����_�G�t�F�N�g5.png", TRUE);
				LoadGraphScreen(1000, 690, "..\\Data\\Stage\\�����_�G�t�F�N�g6.png", TRUE);

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

				// ��ʂ��N���A
				ClearDrawScreen();

				//�J�������̔��f
				SetCameraPositionAndTargetAndUpVec(cpos, ctgt, VGet(0.0f, 1.0f, 0.0f));

				// ���f���̈ړ�(�z�u)
				MV1SetPosition(player[0].anim.model, player[0].GetPosition());
				MV1SetPosition(player[1].anim.model, player[1].GetPosition());

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
				MV1DrawModel(player[0].anim.model);
				MV1DrawModel(player[1].anim.model);

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

				ScreenFlip();

				if (CheckHitKey(KEY_INPUT_RETURN) == 1) {
					player[0].SetPosition(VGet(200.0f, 1800.0f, 0.0f));
					player[1].SetPosition(VGet(2800.0f, 1800.0f, 0.0f));
					cpos = VGet(1484.0f, 2360.0f, -1860.0f);
					ctgt = VGet(0.0f, 1000.0f, 0.0f);
					gamemode = eScenePlay;
				}
				break;

			case eScenePlay :
				g_Chara[0]->ActionLoop(g_Chara[0], g_Chara[1]);
				g_Chara[1]->ActionLoop(g_Chara[1], g_Chara[0]);

				ClearDrawScreen() ;
				// �J�����̎��_����
				CameraMove();

				// �w�i(��)�̑���
				skypos.x = cpos.x;
				skypos.y = cpos.y - 3000.0f;
				skypos.z = cpos.z;

				SetCameraPositionAndTargetAndUpVec(cpos,ctgt,VGet(0.0f,1.0f,0.0f)) ;

				// ���f���̉�]
				MV1SetRotationXYZ(player[0].anim.model,VGet(0.0f,1.57f * player[0].GetDirection(),0.0f)) ;
				// ���f���̈ړ�(�z�u)
				MV1SetPosition(player[0].anim.model,player[0].GetPosition());

				// ���f���̉�]
				MV1SetRotationXYZ(player[1].anim.model, VGet(0.0f, 1.57f * player[1].GetDirection(), 0.0f));
				// ���f���̈ړ�(�z�u)
				MV1SetPosition(player[1].anim.model ,player[1].GetPosition());

				MV1SetPosition(skydate, skypos);

				// �`��
				Draw();

				ScreenFlip() ;
				break ;

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

