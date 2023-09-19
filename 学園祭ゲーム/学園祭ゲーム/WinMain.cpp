
#include "Common.h"		// --- �S�t�@�C���ł̋��ʃw�b�_�[

int WINAPI WinMain(HINSTANCE hI,HINSTANCE hP,LPSTR lpC,int nC){
	
	int stagedata_c ;
	float camera_direction = 0.0f;

	char str[100];
	// �S�̓I�ȃQ�[���̊Ǘ�
	int gamemode = eSceneBlank ;

	//�X�e�[�W�̃|�W�V����
	VECTOR stagepos = VGet(0.0f,0.0f,0.0f) ;
	VECTOR skypos = VGet(0.0f, 0.0f, 0.0f);
		
		
	// �J�����|�W�V���� cpos:�J�����ʒu�@ctgt:�J���������_
	cpos = VGet(500.0f,1000.0f,-2000.0f) ;
	ctgt = VGet(0.0f,500.0f,-400.0f) ;
	cadd = VGet(0.0f, 0.0f, 0.0f);

	VECTOR Position ;


	ChangeWindowMode(TRUE) ;

	SetGraphMode(900,600,32) ;

	// DX���C�u�����̏�����				DX���C�u�����[�X�^�[�g
	if(DxLib_Init() == -1) return -1 ;

	AnimationInit();
	PlayerInit();
	WeaponInit();
	EnemyInit();

	// �R�~�b�g�p�R�����g
	// �X�e�[�W���̓ǂݍ���
	stagedata = MV1LoadModel("..\\Data\\Stage\\Stage00.mv1") ;
	skydata = MV1LoadModel("..\\Data\\Stage\\Stage00_sky.mv1");
	MV1SetUseZBuffer(skydata, false);
	// �u���b�N���f���̓ǂݍ���
	blockdate[TATAMI_BLOCK] = MV1LoadModel("..\\Data\\Stage\\������.mv1");
	blockdate[FALL_BLOCK] = MV1LoadModel("..\\Data\\Stage\\�����u���b�N.mv1");
	blockdate[NEEDLE_BLOCK] = MV1LoadModel("..\\Data\\Stage\\��.mv1");
	blockcnt = 0;
	// �}�b�v�f�[�^�ɔ��f
	for (int y = MAP_Y - 1; y >= 0; y--) {
		for (int x = 0; x < MAP_X; x++) {
			switch (StageMap[y][x]) {
				case TATAMI_BLOCK :
					m_block[blockcnt].b_model = MV1DuplicateModel(blockdate[TATAMI_BLOCK]);
					m_block[blockcnt].SetMapPositionY( y );
					m_block[blockcnt].SetMapPositionX( x );
					m_block[blockcnt].SetBlockFlag( TRUE );
					break;

				case FALL_BLOCK :
					m_block[blockcnt].b_model = MV1DuplicateModel(blockdate[FALL_BLOCK]);
					m_block[blockcnt].SetMapPositionY(y);
					m_block[blockcnt].SetMapPositionX(x);
					m_block[blockcnt].SetBlockFlag(TRUE);
					break;

				case NEEDLE_BLOCK :
					m_block[blockcnt].b_model = MV1DuplicateModel(blockdate[NEEDLE_BLOCK]);
					m_block[blockcnt].SetMapPositionY(y);
					m_block[blockcnt].SetMapPositionX(x);
					m_block[blockcnt].SetBlockFlag(TRUE);
					break;
			}
			if (m_block[blockcnt].GetBlockFlag() == TRUE)
				blockcnt++;
		}
	}

	blockcnt = 0;

	for (int y = (MAP_Y - 1); y >= 0; y--) {
		for (int x = 0; x < MAP_X; x++) {
			if (StageMap[y][x] != 0) {
				MV1SetPosition(m_block[blockcnt].b_model, VGet((x * 200.0f), ((MAP_Y - y) * 200.0f), 0.0f));
				m_block[blockcnt].SetBlockPosition(VGet((x * 200.0f), ((MAP_Y - y) * 200.0f), 0.0f));
				m_block[blockcnt].SetBlockTopPosition(m_block[blockcnt].GetBlockPosition());
				m_block[blockcnt].SetBlockTopPositionY(m_block[blockcnt].GetBlockPosition().y + 120.0f);
				blockcnt++;
			}
		}
	}
	// �V���h�E�}�b�v�n���h���̍쐬


	// ���C�g�̕�����ݒ�
	SetLightDirection( VGet( 0.5f, -0.5f, 0.5f ) );
	ShadowMapHandle = MakeShadowMap( 1024, 1024 ) ;

	// �V���h�E�}�b�v���z�肷�郉�C�g�̕������Z�b�g
	SetShadowMapLightDirection( ShadowMapHandle, VGet( 0.5f, -0.5f, 0.5f ) ) ;

	// �V���h�E�}�b�v�ɕ`�悷��͈͂�ݒ�
	SetShadowMapDrawArea( ShadowMapHandle, VGet( -5000.0f, -10.0f, -5000.0f ), VGet( 5000.0f, 1000.0f, 5000.0f ) ) ;

	stagedata_c = MV1LoadModel("..\\Data\\Stage\\Stage00_c.mv1") ;
	if(stagedata == -1) return -1 ;
	// ���f���S�̂̃R���W�������̃Z�b�g�A�b�v
	MV1SetupCollInfo( stagedata, -1 ) ;

	SetDrawScreen(DX_SCREEN_BACK) ;

	int MeshNum ;

	// ���f���Ɋ܂܂�郁�b�V���̐����擾����
    MeshNum = MV1GetMeshNum( stagedata ) ;

    // ���b�V���̐��������[�v
    for(int i = 0 ; i < MeshNum ; i ++ ){
	// ���b�V���Ɋ܂܂�钸�_�̃��[�J�����W�̍ő���W�l��`��
		Position = MV1GetMeshMaxPosition( stagedata, i ) ;
//		DrawFormatString( 0, 112, GetColor( 255,255,255 ), "Max Position          x %f  y %f  z %f", Position.x, Position.y, Position.z ) ;

		// ���b�V���Ɋ܂܂�钸�_�̃��[�J�����W�̍ŏ����W�l��`��
		Position = MV1GetMeshMinPosition( stagedata, i ) ;
//		DrawFormatString( 0, 128, GetColor( 255,255,255 ), "Min Position          x %f  y %f  z %f", Position.x, Position.y, Position.z ) ;

	}
	/* ------------------------------------------------------------------------------------------------
												�Q�[�����[�v										
	 ----------------------------------------------------------------------------------------------- */
	while(ProcessMessage() == 0 && CheckHitKey(KEY_INPUT_ESCAPE) == 0){
		PolyCharaHitField[0] = VGet(0.0f,0.0f,0.0f) ;
		PolyCharaHitField[1] = VGet(0.0f,0.0f,0.0f) ;
		PolyCharaHitField[2] = VGet(0.0f,0.0f,0.0f) ;
		MV1SetUseZBuffer(skydata, false);

						
		switch(gamemode){
			case eSceneBlank :
				gamemode = eSceneTitle;
				break;

			case eSceneTitle:
				if (CheckHitKey(KEY_INPUT_SPACE) == 1) {
					gamemode = eSceneChoice;
				}
				break;

			case eSceneChoice:
				cpos = VGet(0.0f, 1000.0f, -1500.0f);
				ctgt = VGet(0.0f, 500.0f, 0.0f);
				cadd = VGet(0.0f, 0.0f, 0.0f);

				Player[0].pos = VGet(200.0f, 200.0f, 0.0f);
				Player[1].pos = VGet(600.0f, 300.0f, 200.0f);

				// ���f���̈ړ�(�z�u)
				MV1SetRotationXYZ(Player[0].model, VGet(0.0f, 1.57f * Player[0].direction, 0.0f));
				MV1SetPosition(Player[0].model, Player[0].pos);
				MV1SetRotationXYZ(Player[1].model, VGet(0.0f, 1.57f * Player[1].direction, 0.0f));
				MV1SetPosition(Player[1].model, Player[1].pos);

				Draw();
				ScreenFlip();

				if (CheckHitKey(KEY_INPUT_RETURN) == 1) {
					Player[0].pos = VGet(200.0f, 200.0f, -1000.0f);
					gamemode = eScenePlay;
				}
				break;

			case eScenePlay :
				// �A�j���[�V�����i�s
				if(Player[0].mode != JUMPOUT){
					Player[0].playtime += 0.5f ;
				}
				else{
					Player[0].playtime += 1.0f ;		
				}

				Player[1].playtime += 0.5f;
				if (Player[1].mode == E_BLOWIN) {
					Player[1].playtime += 2.0f;
				}

				//�@�G�l�~�[�̃��[�V�����I�����̏���
				if (Player[1].playtime > Player[1].anim_totaltime) {
					switch (Player[1].mode) {
						case E_STAND :
							Player[1].playtime = 0.0f;
							break;

						case E_BLOWIN :
							AnimationEnemy(E_BLOWLOOP);
							Player[1].playtime = 0.0f;
							Player[1].move.x = 0.0f;
							Player[1].move.y = 0.0f;
							Player[1].move.z = 0.0f;
							break;

						case E_BLOWLOOP :
							AnimationEnemy(E_BLOWOUT);
							Player[1].playtime = 0.0f;
							Player[1].anim_totaltime = MV1GetAnimTotalTime(Player[1].model, Player[1].attachidx);
							MV1SetAttachAnimTime(Player[1].model, Player[1].attachidx, Player[1].playtime);
							break;

						case E_BLOWOUT :
							AnimationEnemy(E_STAND);
							Player[1].playtime = 0.0f;
							break;
					}
				}

				//�@�v���C���[�̃��[�V�����I�����̏���
				if (Player[0].mode != FALL){
					if (Player[0].playtime > Player[0].anim_totaltime){
						if (Player[0].mode == JUMPIN) {
							AnimationPlayer(JUMPLOOP);
							Player[0].move.y = 40.0f;
							Player[0].pos.y += (Player[0].move.y * 4);	// �W�����v����̒n�ʂ߂荞�݂�����邽��
						}

						if (Player[0].mode == JUMPOUT)
							AnimationPlayer(STAND);

						if (Player[0].mode == ATTACK)
							AnimationPlayer(STAND);

						Player[0].playtime = 0.0f ;
					}
				}

				// �v���C���[�̍U�����[�V�������̈ړ��ʕω��̏���
				if (Player[0].mode == ATTACK) {
					if (Player[0].playtime > 8.0f) {
						Player[0].move.x = 0;
						Player[0].move.y = 0;
						Player[0].move.z = 0;
					}
				}

				// �A�j���[�V�����̔��f
				MV1SetAttachAnimTime(Player[0].model, Player[0].attachidx, Player[0].playtime);
				MV1SetAttachAnimTime(Player[1].model, Player[1].attachidx, Player[1].playtime);
				PlayerMove();
				// �L�[����
				if(Player[0].mode == STAND || Player[0].mode == RUN){

					// �A�j���̃��[�v�Ǘ�(�W�����v���[�v�Ɨ�������̂̓��[�v���Ȃ�)
					if ( Player[0].mode != JUMPLOOP && Player[0].mode != FALL ) {
						if (Player[0].playtime > Player[0].anim_totaltime) {
							if ( Player[0].mode == JUMPIN ) {
								AnimationPlayer(JUMPLOOP);
								Player[0].move.y = 15.0f;
								Player[0].pos.y += (Player[0].move.y * 4);	// �W�����v����̒n�ʂ߂荞�݂�����邽��
							}
						}
					}
				}

				// �����Ă��邩�����Ă��邩�̋��
				if(key == 0){
					if(Player[0].mode == RUN) {
						AnimationPlayer(STAND);
						Player[0].move.x = 0.0f;
						Player[0].move.y = 0.0f;
						Player[0].move.z = 0.0f;
					}
				}
				else{
					if(Player[0].mode == STAND){
						AnimationPlayer(RUN);
					}
				}
				ClearDrawScreen() ;
				// �����ɐF�X������ǉ�����
//				DrawBox(0,0,900,600,GetColor(255,255,255),true) ; //�Ō�̈�����false�ɂ���Ɠh��Ԃ�����

				// �L�����ƃq�b�g�`�F�b�N
				if(HitCheck_Capsule_Capsule(VAdd(Player[0].pos,Player[0].move),VAdd(Player[0].pos,Player[0].move),Player[0].charahitinfo.Width / 2,
											VAdd(Player[1].pos,Player[1].move),VAdd(Player[1].pos,Player[1].move),Player[1].charahitinfo.Width / 2) == TRUE){
					// �ړ��ʂ𖳂���
					Player[0].move.x = 0.0f ;
					Player[0].move.y = 0.0f ;
					Player[0].move.z = 0.0f ;
				}

				// �U�����̃G�l�~�[�̃q�b�g�`�F�b�N
				if (Player[0].mode == ATTACK) {
					if (Player[1].mode == E_STAND) {
						if (HitCheck_Capsule_Capsule(VAdd(VGet(Player[0].pos.x - 80.0f, Player[0].pos.y, Player[0].pos.z - 80.0f), Player[0].move),
														VAdd(VGet(Player[0].pos.x + 80.0f, Player[0].pos.y, Player[0].pos.z + 80.0f), Player[0].move), Player[0].charahitinfo.Width / 2,
															VAdd(Player[1].pos, Player[1].move), VAdd(Player[1].pos, Player[1].move), Player[1].charahitinfo.Width / 2) == TRUE) {
							AnimationEnemy(E_BLOWIN);
							Player[1].playtime = 0.0f;
							// �G�l�~�[�̃m�b�N�o�b�N
							if (Player[0].direction == DOWN) {
								Player[1].move.z -= ENEMY_KNOCKBACK;
								Player[1].direction = UP;
							}
							if (Player[0].direction == 0.5f) {
								Player[1].move.x -= ENEMY_KNOCKBACK / 2;
								Player[1].move.z -= ENEMY_KNOCKBACK / 2;
								Player[1].direction = 2.5f;
							}
							if (Player[0].direction == LEFT) {
								Player[1].move.x -= ENEMY_KNOCKBACK;
								Player[1].direction = RIGHT;
							}
							if (Player[0].direction == 1.5f) {
								Player[1].move.x -= ENEMY_KNOCKBACK / 2;
								Player[1].move.z += ENEMY_KNOCKBACK / 2;
								Player[1].direction = 3.5f;
							}
							if (Player[0].direction == UP) {
								Player[1].move.z += ENEMY_KNOCKBACK;
								Player[1].direction = DOWN;
							}
							if (Player[0].direction == 2.5f) {
								Player[1].move.x += ENEMY_KNOCKBACK / 2;
								Player[1].move.z += ENEMY_KNOCKBACK / 2;
								Player[1].direction = 0.5f;
							}
							if (Player[0].direction == RIGHT) {
								Player[1].move.x += ENEMY_KNOCKBACK;
								Player[1].direction = LEFT;
							}
							if (Player[0].direction == 3.5f) {
								Player[1].move.x += ENEMY_KNOCKBACK / 2;
								Player[1].move.z += ENEMY_KNOCKBACK / 2;
								Player[1].direction = 1.5f;
							}
						}
					}
				}

				HitFlag = CollisionBlock();
				// ���|���S���ɓ����������ǂ����ŏ����𕪊�
				if( HitFlag == 1 ){
					// �ڐG�����|���S���ň�ԍ����x���W���L�����N�^�[�̂x���W�ɂ���
					Player[0].pos.y = MaxY ;
					Player[0].move.y = 0.0f ;

					if(Player[0].mode == FALL){
						AnimationPlayer(JUMPOUT);
						Player[0].playtime = 0.0f ;
						Player[0].move.x = 0.0f ;
						Player[0].move.y = 0.0f ;
						Player[0].move.z = 0.0f ;
					}
				}
				else{
					// ���ɕ��������
					if(Player[0].mode != FALL){ // �W�����v��Ԃ���Ȃ�
						MV1DetachAnim(Player[0].model,Player[0].attachidx) ;
						Player[0].mode = FALL ;
						Player[0].attachidx = MV1AttachAnim(Player[0].model,0, plyanim_jumploop) ;
						Player[0].anim_totaltime = MV1GetAttachAnimTotalTime(Player[0].model,Player[0].attachidx) ;
						Player[0].playtime = 7.0f ;
						MV1SetAttachAnimTime(Player[0].model,Player[0].attachidx,Player[0].playtime) ;
					}
				}
				// �W�����v����������d�͒ǉ�������
				if (Player[0].mode == FALL) {
					Player[0].move.y -= 0.5f;
				}

				E1_FloorSearch();
				// ���|���S���ɓ����������ǂ����ŏ����𕪊�
				if (E1_HitFlag == 1) {
					// �ڐG�����|���S���ň�ԍ����x���W���L�����N�^�[�̂x���W�ɂ���
					Player[1].pos.y = E1_MaxY;
					Player[1].move.y = 0.0f;
				}

				// ���o�����L�����N�^�[�̎��͂̃|���S�������J������
				MV1CollResultPolyDimTerminate( HitDim ) ;

				if (CheckHitKey(KEY_INPUT_C) == 1) {
					printf("%d|", Player[0].mode);
					Player[0].pos.y = 1000.0f;
					Player[0].move.y = 0.0f;
				}

				// �ړ�����
				Player[0].pos.x += Player[0].move.x ;
				Player[0].pos.y += Player[0].move.y ;
				Player[0].pos.z += Player[0].move.z ;

				Player[1].pos.x += Player[1].move.x;
				Player[1].pos.y += Player[1].move.y;
				Player[1].pos.z += Player[1].move.z;

				// �J�����̎��_����
				CameraMove();

				// �w�i(��)�̑���
				skypos.x = cpos.x;
				skypos.y = cpos.y - 5000.0f;
				skypos.z = cpos.z;

				// �G�l�~�[�̌����̌���
				if (Player[1].direction < 0.0f) Player[1].direction += 4.0f;
				if (Player[1].direction > 4.0f) Player[1].direction -= 4.0f;

				SetCameraPositionAndTargetAndUpVec(cpos,ctgt,VGet(0.0f,1.0f,0.0f)) ;

				// ���f���̉�]
				MV1SetRotationXYZ(Player[0].model,VGet(0.0f,1.57f * Player[0].direction,0.0f)) ;
				// ���f���̈ړ�(�z�u)
				MV1SetPosition(Player[0].model,Player[0].pos);

				// ���f���̉�]
				MV1SetRotationXYZ(Player[1].model, VGet(0.0f, 1.57f * Player[1].direction, 0.0f));
				// ���f���̈ړ�(�z�u)
				MV1SetPosition(Player[1].model,Player[1].pos);

				// ������g�����f���ɃA�^�b�`����(�A�^�b�`�����郂�f���̉�]��ړ��̌�ɍs��)
				WeaponMatrix = MV1GetFrameLocalWorldMatrix(Player[0].model, WeponAttachFrameNum);	// �A�^�b�`�����郂�f���Ƃ��̃t���[����Ⴂ���̃��[�J�����W�����[���h���W�ɕϊ�����}�g���b�N�X��Ԃ��֐�
				MV1SetMatrix(PlayerSabel.model, WeaponMatrix);									// �A�^�b�`���郂�f���ƃ}�g���b�N�X��Ⴂ���W�ɒ����֐�

				// �n��(�z�u)
				MV1SetPosition(stagedata, stagepos);
				MV1SetPosition(skydata, skypos);

				// �`��
				Draw();

				ScreenFlip() ;
				break ;

			case eSceneClear :
				break ;
		}

	}


	// �V���h�E�}�b�v�̍폜
	DeleteShadowMap(ShadowMapHandle);
	// �X�e�[�W���f���̍폜
	MV1DeleteModel(stagedata);
	// �L�����N�^�[���f���̍폜
	MV1DeleteModel(Player[0].model);
	MV1DeleteModel(Player[1].model);

	DxLib_End();
	return 0 ;
}

