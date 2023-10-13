
// ------------------------------------------------------------------------ //
//							�v���C���[�̏����Z�b�g							//
// ------------------------------------------------------------------------ //
#include "Common.h"
#include<math.h>

/* -------------------------------------------------------- +
 |                                                          |
 |                        Player.cpp1                        |
 |                                                          |
 + -------------------------------------------------------- */
/* ======================================================== +
 |                                                          |
 |                     �@�R���X�g���N�^                     |
 |                                                          |
 + ======================================================== */
Player::Player( ) 
{
	init( ) ;
}

/* ======================================================== +
 |                                                          |
 |                     �@�f�X�g���N�^                       |
 |                                                          |
 + ======================================================== */
Player::~Player( ) 
{
}

/* ======================================================== +
 |                         init( )                          |
 |                     �@�����Z�b�g�@                       |
 |                                                          |
 + ======================================================== */
int Player::init( )
{
	use_flg = TRUE ;						// �g�p�t���O�Z�b�g
	act_mode = eCharaStop ;					// �������[�h
	spd = VGet( 0.0f , 0.0f , 0.0f ) ;		// �X�s�[�h�N���A
	posi = VGet( 0.0f , 0.0f , 0.0f ) ;		// �ʒu�����Z�b�g
	Width = PLAYER_SIZE_W;					// �v���C���[�T�C�Y��
	Height = PLAYER_SIZE_H ;				// �v���C���[�T�C�Y����
	RevivalTime = 0;

	return( false ) ;
}

/* ======================================================== +
 |                          Draw( )                         |
 |                     �@  �@�`��@�@                       |
 |                                                          |
 + ======================================================== */
int Player::Draw( CharaBase *pp1 )
{
	// ���f���̉�]
	MV1SetRotationXYZ( pp1->anim.model, VGet( 0.0f, 1.57f * pp1->GetDirection( ) , 0.0f ) ) ;

	// ���f���̈ړ�(�z�u)
	MV1SetPosition(pp1->anim.model, pp1->GetPosition());

	// ���f���̕`��
	MV1DrawModel( pp1->anim.model ) ;

	return( false ) ;
}

/* ======================================================== +
 |                        AllowKey( )                       |
 |                     �@  �L�[����                         |
 |                                                          |
 + ======================================================== */
int Player::AllowKey( )
{
	// �ړ��L�[�������ꂽ��
	if ( (key1 & PAD_INPUT_DOWN) || (key1 & PAD_INPUT_UP) ||
				(key1 & PAD_INPUT_LEFT) || (key1 & PAD_INPUT_RIGHT) )
	{
		return( true ) ;
	}

	return( false ) ;
}

/* ======================================================== +
 |                      AnimationInit( )                    |
 |                   �A�j���[�V���������Z�b�g               |
 |                                                          |
 + ======================================================== */
int Player::AnimationInit()
{
	g_Chara[0]->SetMotion(anim.stop);
	g_Chara[1]->SetMotion(anim.stop);

	// �A�j���[�V�����Z�b�g
	anim_attach = MV1AttachAnim(anim.model, 0, anim.stop);
	anim_time = MV1GetAttachAnimTotalTime(anim.model, anim_attach);

	// �A�j���[�V�������ē����Ă����̏�œ����Ă�悤�ȏ�Ԃɂ���
	rootflm = MV1SearchFrame(anim.model, "root");
	MV1SetFrameUserLocalMatrix(anim.model, rootflm, MGetIdent());
	play_time = 0.0f;

	return(false);
}

/* ======================================================== +
 |                        Animation( )                      |
 |                     �@�A�j���[�V�����@�@                 |
 |                                                          |
 + ======================================================== */
int Player::Animation(CharaBase* pp1)
{
	if (pp1->GetPlay_Time() > pp1->GetAnim_Time()) {
		pp1->SetPlay_Time(0.0f);
	}
	// �A�j���[�V�����Đ����ԂƓ���������
	MV1SetAttachAnimTime(pp1->GetAnimation_Data().model, pp1->GetAnim_Attach(), pp1->GetPlay_Time());

	return(false);
}

/* ======================================================== +
 |                     ChangeAnimation( )                   |
 |                    �A�j���[�V�����؂�ւ�                |
 |                                                          |
 + ======================================================== */
int Player::ChangeAnimation(CharaBase* pp1, int set_anim)
{
	// �A�j���[�V�������f�^�b�`����
	MV1DetachAnim(pp1->GetAnimation_Data().model, pp1->GetAnim_Attach());

	// �A�j���[�V�����Z�b�g(�؂�ւ�)
	pp1->SetAnim_Attach(MV1AttachAnim(pp1->GetAnimation_Data().model, 0, set_anim));
	pp1->SetAnim_Time(MV1GetAttachAnimTotalTime(pp1->GetAnimation_Data().model, pp1->GetAnim_Attach()));

	// �A�j���[�V�������ē����Ă����̏�œ����Ă�悤�ȏ�Ԃɂ���
	pp1->SetRootFlm(MV1SearchFrame(pp1->GetAnimation_Data().model, "root"));
	MV1SetFrameUserLocalMatrix(pp1->GetAnimation_Data().model, pp1->GetRootFlm(), MGetIdent());
	pp1->SetPlay_Time(0.0f);

	return(false);
}

/* ======================================================== +
 |                        AnimationType( )                  |
 |                     �@�A�j���[�V�����@�@                 |
 |                                                          |
 + ======================================================== */
int Player::AnimationType(CharaBase* pp1)
{
	if (pp1->GetPlay_Time() > pp1->GetAnim_Time()) {
		pp1->SetPlay_Time(0.0f);
	}
	// �A�j���[�V�����Đ����ԂƓ���������
	MV1SetAttachAnimTime(pp1->GetAnimation_Data().type[chara_type], pp1->GetAnim_Attach(), pp1->GetPlay_Time());

	return(false);
}

/* ======================================================== +
 |                     ChangeAnimationType( )               |
 |                    �A�j���[�V�����؂�ւ�                |
 |                                                          |
 + ======================================================== */
int Player::ChangeAnimationType(CharaBase* pp1, int set_anim)
{
	// �A�j���[�V�������f�^�b�`����
	MV1DetachAnim(pp1->GetAnimation_Data().type[chara_type], pp1->GetAnim_Attach());

	// �A�j���[�V�����Z�b�g(�؂�ւ�)
	pp1->SetAnim_Attach(MV1AttachAnim(pp1->GetAnimation_Data().type[chara_type], 0, set_anim));
	pp1->SetAnim_Time(MV1GetAttachAnimTotalTime(pp1->GetAnimation_Data().type[chara_type], pp1->GetAnim_Attach()));

	// �A�j���[�V�������ē����Ă����̏�œ����Ă�悤�ȏ�Ԃɂ���
	pp1->SetRootFlm(MV1SearchFrame(pp1->GetAnimation_Data().type[chara_type], "root"));
	MV1SetFrameUserLocalMatrix(pp1->GetAnimation_Data().type[chara_type], pp1->GetRootFlm(), MGetIdent());
	pp1->SetPlay_Time(0.0f);

	return(false);
}

/* ############################################################################################### */
/* ======================================================== +
 |                       CharaStop( )                       |
 |                       �@��~���@                         |
 |                                                          |
 + ======================================================== */
void Player::CharaStop( CharaBase *pp1 , CharaBase* pp2)
{
	pp1->SetX_Spd(0.0f);

	// �A�j���[�V����
	pp1->AddPlay_Time( 0.5f ) ;
	pp1->SetMotion( pp1->GetAnimation_Data( ).stop ) ;

	if ( AllowKey( ) == (int)true ){
		if (key1 & PAD_INPUT_UP){
			pp1->MoveSet( );
		}
		else {
			pp1->SetAct_Mode(eCharaMove);
			pp1->SetMotion(pp1->GetAnimation_Data().run);
			ChangeAnimation(pp1, pp1->GetAnimation_Data().run);	// �A�j���[�V�����؂�ւ�
		}
	}
	Block_HitCheck(pp1);

	// �ړ��ʂ�������
	pp1->SetPosition(VAdd(pp1->GetPosition(), pp1->GetSpeed()));

	// �ړ��ʃZ�b�g
//	pp1->MoveSet( ) ;

	// A����
	// B����
	// C���~
	// X����
	// ���������ꂽ��
	if (key1 & PAD_INPUT_C) {
		pp1->SetAct_Mode(eCharaAttack);
		pp1->SetMotion(pp1->GetAnimation_Data().attack);
		ChangeAnimation(pp1, pp1->GetAnimation_Data().attack);	// �A�j���[�V�����؂�ւ�
	}

	// x�������ꂽ��
	if (key1 & PAD_INPUT_2) {
//		pp1->SetAct_Mode(eCharaDown);
//		pp1->SetMotion(pp1->GetAnimation_Data().down);
//		ChangeAnimation(pp1, pp1->GetAnimation_Data().down);	// �A�j���[�V�����؂�ւ�
	}

	if (key1 & PAD_INPUT_3) {
		pp1->SetAct_Mode(eCharaDamage);
//		pp1->SetMotion(pp1->GetAnimation_Data().damage);
//		ChangeAnimation(pp1, pp1->GetAnimation_Data().damage);	// �A�j���[�V�����؂�ւ�
	}

	if (key1 & PAD_INPUT_10) {
//		pp1->SetSpeed(VGet(0.0f, 0.0f, 0.0f));
//		pp1->SetAct_Mode(eCharaJump);
//		pp1->SetMotion(pp1->GetAnimation_Data().jump);
//		ChangeAnimation(pp1, pp1->GetAnimation_Data().jump);	// �A�j���[�V�����؂�ւ�
	}
}

/* ======================================================== +
 |                       CharaMove( )                       |
 |                     �@    �ړ��@                         |
 |                                                          |
 + ======================================================== */
void Player::CharaMove( CharaBase *pp1 , CharaBase* pp2)
{
	pp1->SetX_Spd(0.0f);
	// �A�j���[�V����
	pp1->AddPlay_Time( 1.0f ) ;
	pp1->SetMotion( pp1->GetAnimation_Data( ).run ) ;

	// �ړ��ʃZ�b�g(�����]��)
	pp1->MoveSet( ) ;

	// �q�b�g�`�F�b�N
	Move_HitCheck( pp1 , pp2) ;

	Block_HitCheck(pp1);

	// �ړ��ʂ�������
	pp1->SetPosition( VAdd( pp1->GetPosition( ) , pp1->GetSpeed( ) ) ) ;

	// ���������ꂽ��
	if (key1 & PAD_INPUT_C) {
		pp1->SetSpeed(VGet(0.0f, 0.0f, 0.0f));
		pp1->SetAct_Mode(eCharaAttack);
		ChangeAnimation(pp1, pp1->GetAnimation_Data().attack);	// �A�j���[�V�����؂�ւ�
	}

	// x�������ꂽ��
	if (key1 & PAD_INPUT_2) {
//		pp1->SetAct_Mode(eCharaDown);
//		pp1->SetMotion(pp1->GetAnimation_Data().down);
//		ChangeAnimation(pp1, pp1->GetAnimation_Data().down);	// �A�j���[�V�����؂�ւ�
	}

	if (key1 & PAD_INPUT_10) {
		pp1->SetSpeed(VGet(0.0f, 0.0f, 0.0f));
///		pp1->SetAct_Mode(eCharaJumpInit);
//		pp1->SetMotion(pp1->GetAnimation_Data().jump);
//		ChangeAnimation(pp1, pp1->GetAnimation_Data().jump);	// �A�j���[�V�����؂�ւ�
	}

	// ����������Ă��Ȃ����
	if (key1 == 0) {
		pp1->SetSpeed(VGet(0.0f, 0.0f, 0.0f));
		pp1->SetAct_Mode(eCharaStop);
		pp1->SetMotion(pp1->GetAnimation_Data().stop);
		ChangeAnimation(pp1, pp1->GetAnimation_Data().stop);				// �A�j���[�V�����؂�ւ�
	}

//	if (key1 & PAD_INPUT_3) {
//		pp1->SetAct_Mode(eCharaDamage);
//		pp1->SetMotion(pp1->GetAnimation_Data().damage);
//		ChangeAnimation(pp1, pp1->GetAnimation_Data().damage);	// �A�j���[�V�����؂�ւ�
//	}

}
/* ======================================================== +
 |                       CharaAttack( )                     |
 |                     �@    �U���@                         |
 |                                                          |
 + ======================================================== */
void Player::CharaAttack(CharaBase* pp1, CharaBase* pp2)
{
	// �A�j���[�V����
	pp1->AddPlay_Time(0.5f);
	pp1->SetMotion(pp1->GetAnimation_Data().attack);

	// �ړ��ʃZ�b�g
	pp1->MoveSet();
	if (pp1->GetPlay_Time() > pp1->GetAnim_Time()) {
		pp1->SetSpeed(VGet(0.0f, 0.0f, 0.0f));
		pp1->SetAct_Mode(eCharaStop);
		pp1->SetMotion(pp1->GetAnimation_Data().stop);
		ChangeAnimation(pp1, pp1->GetAnimation_Data().stop);				// �A�j���[�V�����؂�ւ�
	}


/*	if (HitCheck_Capsule_Capsule(VAdd(pp1->GetPosition(), pp1->GetSpeed()), VAdd(pp1->GetPosition(), pp1->GetSpeed()), pp1->GetWidth() / 2,
		VAdd(pp2->GetPosition(), pp2->GetSpeed()), VAdd(pp2->GetPosition(), pp2->GetSpeed()), pp2->GetWidth() / 2) == TRUE) {
		pp1->SetSpeed(VGet(0, 0, 0));
		pp2->SetAct_Mode(eCharaDamage);
		pp2->SetMotion(pp2->GetAnimation_Data().damage);
		ChangeAnimation(pp2, pp2->GetAnimation_Data().damage);
		CharaDamage(pp2, pp1);
	}

	// �v���C���[�P
	if (pp1->GetAnim_Time() < pp1->GetPlay_Time()) {
		if (direction == DOWN) {
			pp1->SetPosition(VGet(pp1->GetPosition().x, pp1->GetPosition().y, pp1->GetPosition().z - 300));
		}
		if (HitCheck_Capsule_Capsule(VAdd(pp1->GetPosition(), pp1->GetSpeed()), VAdd(pp1->GetPosition(), pp1->GetSpeed()), pp1->GetWidth() / 2,
			VAdd(pp2->GetPosition(), pp2->GetSpeed()), VAdd(pp2->GetPosition(), pp2->GetSpeed()), pp2->GetWidth() / 2) == TRUE) {
			pp1->SetSpeed(VGet(0, 0, 0));
			pp2->AddPlay_Time(0.5f);
//			pp2->SetMotion(pp2->GetAnimation_Data().damage);
		}
	}

	if (direction == UP) {
		pp1->SetPosition(VGet(pp1->GetPosition().x, pp1->GetPosition().y, pp1->GetPosition().z + 300));
		if (HitCheck_Capsule_Capsule(VAdd(pp1->GetPosition(), pp1->GetSpeed()), VAdd(pp1->GetPosition(), pp1->GetSpeed()), pp1->GetWidth() / 2,
			VAdd(pp2->GetPosition(), pp2->GetSpeed()), VAdd(pp2->GetPosition(), pp2->GetSpeed()), pp2->GetWidth() / 2) == TRUE) {
			pp1->SetSpeed(VGet(0, 0, 0));
			pp2->AddPlay_Time(0.5f);
//			pp2->SetMotion(pp2->GetAnimation_Data().damage);
		}

		// �J�����Ɉړ��ʂ�������
		cpos.z += 300;
		ctgt.z += 300;
	}

	if (direction == LEFT) {
		pp1->SetPosition(VGet(pp1->GetPosition().x - 300, pp1->GetPosition().y, pp1->GetPosition().z));
		if (HitCheck_Capsule_Capsule(VAdd(pp1->GetPosition(), pp1->GetSpeed()), VAdd(pp1->GetPosition(), pp1->GetSpeed()), pp1->GetWidth() / 2,
			VAdd(pp2->GetPosition(), pp2->GetSpeed()), VAdd(pp2->GetPosition(), pp2->GetSpeed()), pp2->GetWidth() / 2) == TRUE) {
			pp1->SetSpeed(VGet(0, 0, 0));
			pp2->AddPlay_Time(0.5f);
//			pp2->SetMotion(pp2->GetAnimation_Data().damage);
		}
	}

	if (direction == RIGHT) {
		pp1->SetPosition(VGet(pp1->GetPosition().x + 300, pp1->GetPosition().y, pp1->GetPosition().z));
		if (HitCheck_Capsule_Capsule(VAdd(pp1->GetPosition(), pp1->GetSpeed()), VAdd(pp1->GetPosition(), pp1->GetSpeed()), pp1->GetWidth() / 2,
			VAdd(pp2->GetPosition(), pp2->GetSpeed()), VAdd(pp2->GetPosition(), pp2->GetSpeed()), pp2->GetWidth() / 2) == TRUE) {
			pp1->SetSpeed(VGet(0, 0, 0));
			pp2->AddPlay_Time(0.5f);
//			pp2->SetMotion(pp2->GetAnimation_Data().damage);
		}

	}
*/
}

/* ======================================================== +
 |							CharaJump( )					|
 |						�W�����v�����ݒ�					|
 |															|
 + ======================================================== */
void Player::CharaJump(CharaBase* pp1, CharaBase* pp2)
{
	pp1->AddPlay_Time(0.5f);
	pp1->SetX_Spd(0.0f);
	pp1->SetY_Posi(posi.y + 11.0f);
	pp1->SetY_Spd(PLAYER_JUMP_SPEED);
	pp1->SetAct_Mode(eCharaFall);
	ChangeAnimation(pp1, pp1->GetAnimation_Data().jump);	// �A�j���[�V�����؂�ւ�
}

/* ======================================================== +
 |                       CharaFall( )                 �@	|
 |							����							|
 |                                                          |
 + ======================================================== */
void Player::CharaFall(CharaBase* pp1, CharaBase* pp2) {
	// �A�j���[�V����
	pp1->AddPlay_Time(0.5f);

	if (pp1->GetAnimation_Data().model == pp1->anim.jump_in)
		ChangeAnimation(pp1, pp1->GetAnimation_Data().jump);	// �A�j���[�V�����؂�ւ�

	if (pp1->GetAnim_Attach() == pp1->GetAnimation_Data().jump)
		pp1->SetMotion(pp1->GetAnimation_Data().jump);

	if (pp1->GetAnim_Attach() != pp1->GetAnimation_Data().fall &&
		pp1->GetSpeed().y < 0 ) {
		ChangeAnimation(pp1, pp1->GetAnimation_Data().fall);	// �A�j���[�V�����؂�ւ�
	}

	pp1->MoveSet();
	
	if (pp1->GetSpeed().y > -50.0f) {
		pp1->SetY_Spd(pp1->GetSpeed().y - PLAYER_FALL_SPEED);
		if (pp1->GetSpeed().y < -2.0f && pp1->GetSpeed().y > -40.0f) {
			pp1->SetY_Spd(pp1->GetSpeed().y - PLAYER_FALL_SPEED);
		}
	}
	Block_HitCheck(pp1);

	pp1->SetPosition(VAdd(pp1->GetPosition(), pp1->GetSpeed()));
}


/* ======================================================== +
 |                       CharaDamage( )                     |
 |                     �@�_���[�W�@                         |
 |                                                          |
 + ======================================================== */
void Player::CharaDamage(CharaBase* pp1, CharaBase* pp2)
{
	pp1->AddPlay_Time(0.5f);
	pp1->SetMotion(pp1->GetAnimation_Data().damage);

	if (pp1->GetAnim_Time() < pp1->GetPlay_Time()) {
		pp1->SetSpeed(VGet(0.0f, 0.0f, 0.0f));
		pp1->SetAct_Mode(eCharaStop);
		pp1->SetMotion(pp1->GetAnimation_Data().stop);
		ChangeAnimation(pp1, pp1->GetAnimation_Data().stop);				// �A�j���[�V�����؂�ւ�
	}
	printf("%d\n", HitFlag);
}

/* ======================================================== +
 |                       CharaDown( )                     �@|
 |                     �@ �_�E���@                          |
 |                                                          |
 + ======================================================== */
void Player::CharaDown(CharaBase* pp1, CharaBase* pp2)
{
}
/* ======================================================== +
 |                    CharaRevival( )                       |
 |             �@     �q�b�g�`�F�b�N�@                      |
 |                                                          |
 + ======================================================== */
void Player::CharaRevival(CharaBase* pp1, CharaBase* pp2) {
	pp1->SetRevivalTime(pp1->GetRevivalTime() - 1);
	pp1->SetPosition(VGet(1500.0f, cpos.y - 1000.0f, 0.0f));

	if (pp1->GetRevivalTime() % 3 == 0) {
		pp1->SetUse_Flg(FALSE);
	}
	else
	{
		pp1->SetUse_Flg(TRUE);
	}


	if (pp1->GetRevivalTime() == 0) {
		Block_HitCheck(pp1);
		pp1->SetSpeed(VGet(0.0f, 0.0f, 0.0f));
		pp1->SetUse_Flg(TRUE);
		pp1->SetAct_Mode(eCharaStop);
		pp1->SetMotion(pp1->GetAnimation_Data().stop);
		ChangeAnimation(pp1, pp1->GetAnimation_Data().stop);				// �A�j���[�V�����؂�ւ�
	}
}

/* ======================================================== +
 |                    Move_HitCheck( )                      |
 |             �@     �q�b�g�`�F�b�N�@                      |
 |                                                          |
 + ======================================================== */
void Player::Move_HitCheck(CharaBase* pp1, CharaBase* pp2)
{
	if (HitCheck_Capsule_Capsule(VAdd(pp1->GetPosition(), pp1->GetSpeed()), VAdd(pp1->GetPosition(), pp1->GetSpeed()), pp1->GetWidth() / 2,
		VAdd(pp2->GetPosition(), pp2->GetSpeed()), VAdd(pp2->GetPosition(), pp2->GetSpeed()), pp2->GetWidth() / 2) == TRUE) {
		pp1->SetSpeed(VGet(0, 0, 0));
	}

}

/* ======================================================== +
 |                    Block_HitCheck( )                     |
 |             �@     �q�b�g�`�F�b�N�@                      |
 |                                                          |
 + ======================================================== */
void Player::Block_HitCheck(CharaBase* pp1) {
	HitFlag = 0;
	MaxY = 0.0f;
	bool b_damegeflg = FALSE;
	VECTOR cal_pos1 = VAdd(pp1->GetPosition(), VGet(0.0f, PLAYER_SIZE_H, 0.0f));
	VECTOR cal_pos2 = VAdd(pp1->GetPosition(), VGet(0.0f, -10.0f, 0.0f));

	for (int i = 0; i < MAX_BLOCK; i++) {
		if (m_block[i].GetBlockFlag() == TRUE) {
			switch (m_block[i].GetBlockType()) {
				case TATAMI_BLOCK:
				case BREAK_BLOCK:
				case FALL_BLOCK:
				case WOOD_BLOCK:
				case MOVE_BLOCK_X:
				case MOVE_BLOCK_Y:
				case MOVE_BLOCK_Z:
					LineBlock = HitCheck_Line_Cube(cal_pos1, cal_pos2,
						VGet(m_block[i].GetBlockPosition().x - BLOCK_X_SIZE, m_block[i].GetBlockPosition().y,				m_block[i].GetBlockPosition().z - 100.0f),
						VGet(m_block[i].GetBlockPosition().x + BLOCK_X_SIZE, m_block[i].GetBlockPosition().y + BLOCK_TOP, m_block[i].GetBlockPosition().z + 100.0f));
					break;

				case INVINCIBLE_BLOCK:
				case NEEDLE_BLOCK:
					LineBlock = HitCheck_Line_Cube(cal_pos1, cal_pos2,
						VGet(m_block[i].GetBlockPosition().x - BLOCK_X_SIZE, m_block[i].GetBlockPosition().y,					m_block[i].GetBlockPosition().z - 100.0f),
						VGet(m_block[i].GetBlockPosition().x + BLOCK_X_SIZE, m_block[i].GetBlockPosition().y + BLOCK_TOP * 2, m_block[i].GetBlockPosition().z + 100.0f));
					break;
			}

			// ���������ꍇ�̏���
			if (LineBlock.HitFlag == TRUE) {
				// �|���S���ɓ��������t���O�𗧂Ă�
				if (pp1->GetSpeed().y > 0) {
					switch (m_block[i].GetBlockType()) {
						case TATAMI_BLOCK:
						case BREAK_BLOCK:
						case FALL_BLOCK:
							// �u���b�N�̒�ʂ��v���C���[�̓������������̏���
							if (m_block[i].GetBlockPosition().y < pp1->GetPosition().y + PLAYER_SIZE_H ) {
								if (m_block[i].GetBlockPosition().y + BLOCK_TOP > pp1->GetPosition().y + PLAYER_SIZE_H) {
									pp1->SetY_Spd(pp1->GetSpeed().y * -1);
									MaxY = m_block[i].GetBlockPosition().y - PLAYER_SIZE_H;
									m_block[i].SetBlockFlag(FALSE);
								}
								else {
									if (m_block[i].GetBlockPosition().x < pp1->GetPosition().x) {
										pp1->SetX_Posi(m_block[i].GetBlockPosition().x + (BLOCK_X_SIZE + PLAYER_SPEED));
										if (pp1->GetSpeed().x > 0)
											pp1->SetX_Spd(0.0f);
									}
									if (m_block[i].GetBlockPosition().x > pp1->GetPosition().x) {
										pp1->SetX_Posi(m_block[i].GetBlockPosition().x - (BLOCK_X_SIZE + PLAYER_SPEED));
										if (pp1->GetSpeed().x < 0)
											pp1->SetX_Spd(0.0f);
									}
								}
							}
							break;

						case NEEDLE_BLOCK:
							b_damegeflg = TRUE;
						case INVINCIBLE_BLOCK:
						case MOVE_BLOCK_X:
						case MOVE_BLOCK_Y:
						case MOVE_BLOCK_Z:
						case WOOD_BLOCK:
							if (m_block[i].GetBlockPosition().y < pp1->GetPosition().y + PLAYER_SIZE_H) {
								if (m_block[i].GetBlockPosition().y + BLOCK_TOP > pp1->GetPosition().y + PLAYER_SIZE_H) {
									pp1->SetY_Spd(pp1->GetSpeed().y * -1);
									MaxY = pp1->GetPosition().y - 250.0f;
								}
								else {
									if (m_block[i].GetBlockPosition().x < pp1->GetPosition().x) {
										pp1->SetX_Posi(m_block[i].GetBlockPosition().x + (BLOCK_X_SIZE + PLAYER_SPEED));
										if (pp1->GetSpeed().x > 0)
											pp1->SetX_Spd(0.0f);
									}
									if (m_block[i].GetBlockPosition().x > pp1->GetPosition().x) {
										pp1->SetX_Posi(m_block[i].GetBlockPosition().x - (BLOCK_X_SIZE + PLAYER_SPEED));
										if (pp1->GetSpeed().x < 0)
											pp1->SetX_Spd(0.0f);
									}
								}
							}
							break;
					}
				}
				else {
					HitFlag = 1;
					if (m_block[i].GetBlockType() != INVINCIBLE_BLOCK && m_block[i].GetBlockType() != NEEDLE_BLOCK) {
						if (m_block[i].GetBlockPosition().y + (BLOCK_TOP / 2) <= pp1->GetPosition().y) {
							// �ڐG�����x���W��ۑ�����
							MaxY = m_block[i].GetBlockPosition().y + BLOCK_TOP;
							if (m_block[i].GetBlockType() == MOVE_BLOCK_X) {
								pp1->SetX_Spd(pp1->GetSpeed().x + m_block[i].GetBlockSpeed().x);
							}
						}
						else {
							MaxY = pp1->GetPosition().y;
							if (pp1->GetSpeed().y < 0)
								HitFlag = 0;

							// ���̏��ւ̈ړ��̐���
							if (m_block[i].GetBlockPosition().x < pp1->GetPosition().x) {
								pp1->SetX_Posi(m_block[i].GetBlockPosition().x + (BLOCK_X_SIZE + PLAYER_SPEED));
								if (pp1->GetSpeed().x > 0)
									pp1->SetX_Spd(0.0f);
							}
							if (m_block[i].GetBlockPosition().x > pp1->GetPosition().x) {
								pp1->SetX_Posi(m_block[i].GetBlockPosition().x - (BLOCK_X_SIZE + PLAYER_SPEED));
								if (pp1->GetSpeed().x < 0)
									pp1->SetX_Spd(0.0f);
							}
						}
					}
					else {
						if (m_block[i].GetBlockType() == NEEDLE_BLOCK) {
							b_damegeflg = TRUE;
							if (pp1->GetSpeed().y < 0)
								HitFlag = 0;
						}
						if (m_block[i].GetBlockPosition().y + BLOCK_TOP + (BLOCK_TOP / 2) <= pp1->GetPosition().y) {
							// �ڐG�����x���W��ۑ�����
							MaxY = m_block[i].GetBlockPosition().y + BLOCK_TOP * 2;
						}
						else {
							MaxY = pp1->GetPosition().y;
							if (pp1->GetSpeed().y < 0)
								HitFlag = 0;
							if (m_block[i].GetBlockPosition().x < pp1->GetPosition().x) {
								pp1->SetX_Posi(m_block[i].GetBlockPosition().x + (BLOCK_X_SIZE + PLAYER_SPEED));
								if (pp1->GetSpeed().x > 0)
									pp1->SetX_Spd(0.0f);
							}
							if (m_block[i].GetBlockPosition().x > pp1->GetPosition().x) {
								pp1->SetX_Posi(m_block[i].GetBlockPosition().x - (BLOCK_X_SIZE + PLAYER_SPEED));
								if (pp1->GetSpeed().x < 0)
									pp1->SetX_Spd(0.0f);
							}
						}
					}
				}
			}
		}
	}
	// ���|���S���ɓ����������ǂ����ŏ����𕪊�
	if (HitFlag == 1) {
		if (b_damegeflg == FALSE) {
			// �ڐG�����|���S���ň�ԍ����x���W���L�����N�^�[�̂x���W�ɂ���
			pp1->SetY_Posi(MaxY);
			pp1->SetY_Spd(0.0f);

			if (pp1->GetAct_Mode() == eCharaFall) {
				pp1->SetAct_Mode(eCharaStop);
				ChangeAnimation(pp1, pp1->GetAnimation_Data().stop);	// �A�j���[�V�����؂�ւ�
				pp1->SetAnim_Time(0.0f);
				pp1->SetSpeed(VGet(0.0f, 0.0f, 0.0f));
			}
		}
		else {
			pp1->SetAct_Mode(eCharaDamage);
			ChangeAnimation(pp1, pp1->GetAnimation_Data().damage);	// �A�j���[�V�����؂�ւ�
		}
	}
	else {
		if (b_damegeflg == FALSE) {
			// ���ɕ��������
			if (pp1->GetAct_Mode() != eCharaFall) { // �W�����v��Ԃ���Ȃ�
				pp1->SetAct_Mode(eCharaFall);
				ChangeAnimation(pp1, pp1->GetAnimation_Data().jump);
			}
		}
		else {
			pp1->SetAct_Mode(eCharaDamage);
			ChangeAnimation(pp1, pp1->GetAnimation_Data().damage);	// �A�j���[�V�����؂�ւ�
		}
	}
}

/* ======================================================== +
 |                       ActionLoop( )                      |
 |                     �@�A�N�V�����@                       |
 |                                                          |
 + ======================================================== */
void (Player::* PlayerModeTbl[])(CharaBase* pp1, CharaBase* pp2) = 
{
	& Player::CharaStop   ,
	& Player::CharaMove   ,
	& Player::CharaAttack ,
	& Player::CharaJump  ,
	& Player::CharaFall,
	& Player::CharaDamage,
	& Player::CharaDown,
	& Player::CharaRevival
};

int Player::ActionLoop( CharaBase *pp1 , CharaBase *pp2  )
{
	// �L�[����
	if (pp1 == &player[0])
		key1 = GetJoypadInputState(DX_INPUT_KEY_PAD1);
	if (pp1 == &player[1])
		key1 = GetJoypadInputState(DX_INPUT_PAD2);

	if ((cpos.y - pp1->GetPosition().y > 2750.0f) && (pp1 == &player[0])) {
		pp1->SetAct_Mode(eCharaRevival);
		pp1->SetRevivalTime(100);
	}

	// �A�N�V�������[�v
	( this->*PlayerModeTbl[act_mode] )( pp1 , pp2 ) ;

	return( false ) ;
}



