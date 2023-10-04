
#include "Common.h"		// --- �S�t�@�C���ł̋��ʃw�b�_�[

int WINAPI WinMain(HINSTANCE hI,HINSTANCE hP,LPSTR lpC,int nC){
	
	int ScreenHandle;

	float camera_direction = 0.0f;
	
	// �S�̓I�ȃQ�[���̊Ǘ�
	int gamemode = eSceneBlank ;

	//�X�e�[�W�̃|�W�V����
	VECTOR stagepos = VGet(0.0f,0.0f,0.0f) ;
	VECTOR skypos = VGet(0.0f, 0.0f, 0.0f);
		
		
	// �J�����|�W�V���� cpos:�J�����ʒu�@ctgt:�J���������_
	cpos = VGet(3500.0f, 2300.0f, -3500.0f);

//	cpos = VGet(500.0f,1000.0f,-2000.0f) ;
	ctgt = VGet(0.0f,500.0f,-400.0f) ;
	cadd = VGet(0.0f, 0.0f, 0.0f);

	ChangeWindowMode(TRUE);
	SetGraphMode(1440, 810, 32);

	// DX���C�u�����̏�����				DX���C�u�����[�X�^�[�g
	if(DxLib_Init() == -1) return -1 ;

	ScreenHandle = MakeScreen(1920, 1080, FALSE);


	// �X�e�[�W���̓ǂݍ���
	// �R�~�b�g�p�R�����g
	// �X�e�[�W���̓ǂݍ���
	skydate = MV1LoadModel("..\\Data\\Stage\\�X�J�C�h�[��.mv1");
	if (skydate == -1) return -1;

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
	blockdate[MOVE_BLOCK_X] = MV1LoadModel("..\\Data\\Stage\\�ړ���.mv1");
	// �v���C���[�̍쐬
	player[0].anim.model = MV1LoadModel("..\\Data\\Ninja\\���E��.mv1");
	player[1].anim.model = MV1LoadModel("..\\Data\\Ninja\\�E��.mv1");

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

	m_block->init();

	/* ------------------------------------------------------------------------------------------------
												�Q�[�����[�v										
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

				// ��ʂ��N���A
				ClearDrawScreen();

				cpos = VGet(0.0f, 1000.0f, -1500.0f);
				ctgt = VGet(0.0f, 2000.0f, 0.0f);
				cadd = VGet(0.0f, 0.0f, 0.0f);

				player[0].SetPosition(VGet(200.0f, 200.0f, 0.0f));
				player[1].SetPosition(VGet(0.0f, 2000.0f, 0.0f));

				//�J�������̔��f
				SetCameraPositionAndTargetAndUpVec(cpos, ctgt, VGet(0.0f, 1.0f, 0.0f));

				// ���f���̈ړ�(�z�u)
				MV1SetRotationXYZ(player[0].anim.model, VGet(0.0f, 1.57f * player[0].GetDirection(), 0.0f));
				MV1SetPosition(player[0].anim.model, player[0].GetPosition());
				MV1SetRotationXYZ(player[1].anim.model, VGet(0.0f, 1.57f * player[1].GetDirection(), 0.0f));
				MV1SetPosition(player[1].anim.model, player[1].GetPosition());

				// �V���h�E�}�b�v�ւ̕`��̏���
				ShadowMap_DrawSetup(ShadowMapHandle);

				// ���f���̕`�� - �e�̕`��
				MV1DrawModel(player[0].anim.model);
				MV1DrawModel(player[1].anim.model);

				// �V���h�E�}�b�v�ւ̕`����I��
				ShadowMap_DrawEnd();

				// �`��Ɏg�p����V���h�E�}�b�v��ݒ�
				SetUseShadowMap(0, ShadowMapHandle);

				// �n��(�z�u)���`��
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
				SetLightPositionHandle(LHandle_p1, VGet(player[0].GetPosition().x, player[0].GetPosition().y + 100.0f, player[0].GetPosition().z - 500.0f)); // ���C�g�̈ʒu
				SetLightPositionHandle(LHandle_p2, VGet(player[1].GetPosition().x, player[1].GetPosition().y + 100.0f, player[1].GetPosition().z - 500.0f)); // ���C�g�̈ʒu
			//	SetLightDirectionHandle(LHandle_p1, VGet(ctgt.x = cpos.x , ctgt.y = cpos.y - 400   , ctgt.z = cpos.z ));  // ���C�g�̕���
			//	SetLightAngleHandle(LHandle_p1, 0.78f, 0.5f);

				// �`��Ɏg�p����V���h�E�}�b�v�̐ݒ������
				SetUseShadowMap(0, -1);

				// �W���̂P�ɏk�������摜���K�E�X�t�B���^�łڂ���
				GraphFilter(ScreenHandle, DX_GRAPH_FILTER_GAUSS, 16, 1400);

				// ���f���̕`��
				MV1DrawModel(player[0].anim.model);
				MV1DrawModel(player[1].anim.model);

				// �`��Ώۂ𗠉�ʂɂ���
				SetDrawScreen(DX_SCREEN_BACK);

				// �ʏ�̕`�挋�ʂ�`�悷��
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

