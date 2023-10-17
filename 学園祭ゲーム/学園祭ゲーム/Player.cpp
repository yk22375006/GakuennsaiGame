
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
	RevivalTime = 0;						// �����ɂ����鎞��
	selectflg = FALSE;						// �L�����I��
	blowdirection = NONBLOW;				// ������ԕ���
	damageflg = FALSE;						// �U�����ꂽ
	falldamageflg = FALSE;					// �������Ƀ_���[�W�𕉂���
	type = SPEEDMODE;
	score = 0;
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
				(key1 & PAD_INPUT_LEFT) || (key1 & PAD_INPUT_RIGHT) ||
					key1 & PAD_INPUT_C)
	{
		return( true ) ;
	}

	return( false ) ;
}
/* ======================================================== +
 |                      LoadAnimation( )                    |
 |                   �A�j���[�V�����ǂݍ���               |
 |                                                          |
 + ======================================================== */
int Player::LoadAnimation(CharaBase* pp1) {

	if (pp1 == &player[0]) {
		switch (pp1->GetType())
		{
			case SPEEDMODE:
			case POWERMODE:
				pp1->anim.model		= MV1DuplicateModel(Original[0].type[SPEEDMODE]);
				pp1->anim.stop		= MV1DuplicateModel(Original[0].typestop[SPEEDMODE]);		// �����A�j��
				pp1->anim.run		= MV1DuplicateModel(Original[0].run);		// ����A�j��
				pp1->anim.jump_in	= MV1DuplicateModel(Original[0].jump_in);	// �W�����v����n�߃A�j��
				pp1->anim.jump		= MV1DuplicateModel(Original[0].jump);		// �W�����v���[�v�A�j��
				pp1->anim.fall		= MV1DuplicateModel(Original[0].fall);		// �W�����v���[�v�A�j��
				pp1->anim.attack	= MV1DuplicateModel(Original[0].attack);	// �U���A�j��
				pp1->anim.damage	= MV1DuplicateModel(Original[0].damage);	// ��_���[�W�A�j��
				break;

			case BALANCEMODE:
				pp1->anim.model		= MV1DuplicateModel(Original[0].type[BALANCEMODE]);
				pp1->anim.stop		= MV1DuplicateModel(Original[0].typestop[BALANCEMODE]);		// �����A�j��
				pp1->anim.run		= MV1DuplicateModel(Original[1].run);		// ����A�j��
				pp1->anim.jump_in	= MV1DuplicateModel(Original[1].jump_in);	// �W�����v����n�߃A�j��
				pp1->anim.jump		= MV1DuplicateModel(Original[1].jump);		// �W�����v���[�v�A�j��
				pp1->anim.fall		= MV1DuplicateModel(Original[1].fall);		// �W�����v���[�v�A�j��
				pp1->anim.attack	= MV1DuplicateModel(Original[1].attack);	// �U���A�j��
				pp1->anim.damage	= MV1DuplicateModel(Original[1].damage);	// ��_���[�W�A�j��
				break;
		}
	}
	if (pp1 == &player[1]) {
		switch (pp1->GetType()) {
			case SPEEDMODE:
			case POWERMODE:
				pp1->anim.model		= MV1DuplicateModel(Original[1].type[SPEEDMODE]);
				pp1->anim.stop		= MV1DuplicateModel(Original[1].typestop[SPEEDMODE]);		// �����A�j�� 
				pp1->anim.run		= MV1DuplicateModel(Original[0].run);		// ����A�j��
				pp1->anim.jump_in	= MV1DuplicateModel(Original[0].jump_in);	// �W�����v����n�߃A�j��
				pp1->anim.jump		= MV1DuplicateModel(Original[0].jump);		// �W�����v���[�v�A�j��
				pp1->anim.fall		= MV1DuplicateModel(Original[0].fall);		// �W�����v���[�v�A�j��
				pp1->anim.attack	= MV1DuplicateModel(Original[0].attack);	// �U���A�j��
				pp1->anim.damage	= MV1DuplicateModel(Original[0].damage);	// ��_���[�W�A�j��
				break;

			case BALANCEMODE:
				pp1->anim.model		= MV1DuplicateModel(Original[1].type[BALANCEMODE]);
				pp1->anim.stop		= MV1DuplicateModel(Original[1].typestop[BALANCEMODE]);		// �����A�j��
				pp1->anim.run		= MV1DuplicateModel(Original[1].run);		// ����A�j��
				pp1->anim.jump_in	= MV1DuplicateModel(Original[1].jump_in);	// �W�����v����n�߃A�j��
				pp1->anim.jump		= MV1DuplicateModel(Original[1].jump);		// �W�����v���[�v�A�j��
				pp1->anim.fall		= MV1DuplicateModel(Original[1].fall);		// �W�����v���[�v�A�j��
				pp1->anim.attack	= MV1DuplicateModel(Original[1].attack);	// �U���A�j��
				pp1->anim.damage	= MV1DuplicateModel(Original[1].damage);	// ��_���[�W�A�j��
				break;
		}
	}
	return (false);
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
	MV1SetAttachAnimTime(pp1->GetAnimation_Data().type[pp1->GetType()], pp1->GetAnim_Attach(), pp1->GetPlay_Time());

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
	MV1DetachAnim(pp1->GetAnimation_Data().type[pp1->GetType()], pp1->GetAnim_Attach());

	// �A�j���[�V�����Z�b�g(�؂�ւ�)
	pp1->SetAnim_Attach(MV1AttachAnim(pp1->GetAnimation_Data().type[pp1->GetType()], 0, set_anim));
	pp1->SetAnim_Time(MV1GetAttachAnimTotalTime(pp1->GetAnimation_Data().type[pp1->GetType()], pp1->GetAnim_Attach()));

	// �A�j���[�V�������ē����Ă����̏�œ����Ă�悤�ȏ�Ԃɂ���
	pp1->SetRootFlm(MV1SearchFrame(pp1->GetAnimation_Data().type[pp1->GetType()], "root"));
	MV1SetFrameUserLocalMatrix(pp1->GetAnimation_Data().type[pp1->GetType()], pp1->GetRootFlm(), MGetIdent());
	pp1->SetPlay_Time(0.0f);

	return(false);
}
/* ############################################################################################### */
/* ======================================================== +
 |						CharaChoice( )						|
 |						�L�����I��							|
 |                                                          |
 + ======================================================== */
void Player::CharaChoice(CharaBase* pp1) {
	if (pp1 == &player[0])
		key1 = GetJoypadInputState(DX_INPUT_KEY_PAD1);
	if (pp1 == &player[1])
		key1 = GetJoypadInputState(DX_INPUT_PAD2);

	if (continuous_limit == 0 && pp1->GetSelectFlg() == FALSE) {
		if (key1 & PAD_INPUT_RIGHT) {
			pp1->SetType(pp1->GetType() - 1);
			continuous_limit = 15;
			if (pp1->GetType() < SPEEDMODE)
				pp1->SetType(POWERMODE);
		}
		if (key1 & PAD_INPUT_LEFT) {
			pp1->SetType(pp1->GetType() - 1);
			continuous_limit = 15;
			if (pp1->GetType() < SPEEDMODE)
				pp1->SetType(POWERMODE) ;

		}
		if ((key1 & PAD_INPUT_LEFT) || (key1 & PAD_INPUT_RIGHT)) {
				ChangeAnimationType(pp1, pp1->anim.typestop[pp1->GetType()]);
		}
	}
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
		if (key1 & PAD_INPUT_UP || key1 & PAD_INPUT_C){
			pp1->MoveSet( pp1 );
		}
		else {
			pp1->SetAct_Mode(eCharaMove);
			pp1->SetMotion(pp1->GetAnimation_Data().run);
			ChangeAnimation(pp1, pp1->GetAnimation_Data().run);	// �A�j���[�V�����؂�ւ�
		}
	}

	if (gamemode == eScenePlay1)
		Block_HitCheck(pp1);
	if( gamemode == eScenePlay2 )
		Block_HitCheck2(pp1);

	// �ړ��ʂ�������
	pp1->SetPosition(VAdd(pp1->GetPosition(), pp1->GetSpeed()));

	// A����
	// B����
	// C���~
	// X����
	// ���������ꂽ��
	if (key1 & PAD_INPUT_B) {
		pp1->SetAct_Mode(eCharaAttack);
		pp1->SetMotion(pp1->GetAnimation_Data().attack);
		ChangeAnimation(pp1, pp1->GetAnimation_Data().attack);	// �A�j���[�V�����؂�ւ�
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
	pp1->MoveSet( pp1 ) ;

	// �q�b�g�`�F�b�N
	Move_HitCheck( pp1 , pp2) ;

	if (gamemode == eScenePlay1)
		Block_HitCheck(pp1);

	if (gamemode == eScenePlay2)
		Block_HitCheck2(pp1);

	// �ړ��ʂ�������
	pp1->SetPosition( VAdd( pp1->GetPosition( ) , pp1->GetSpeed( ) ) ) ;

	// ���������ꂽ��
	if (key1 & PAD_INPUT_B) {
		pp1->SetSpeed(VGet(0.0f, 0.0f, 0.0f));
		pp1->SetAct_Mode(eCharaAttack);
		ChangeAnimation(pp1, pp1->GetAnimation_Data().attack);	// �A�j���[�V�����؂�ւ�
	}

	// ����������Ă��Ȃ����
	if (key1 == 0) {
		pp1->SetSpeed(VGet(0.0f, 0.0f, 0.0f));
		pp1->SetAct_Mode(eCharaStop);
		pp1->SetMotion(pp1->GetAnimation_Data().stop);
		ChangeAnimation(pp1, pp1->GetAnimation_Data().stop);				// �A�j���[�V�����؂�ւ�
	}

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
	pp1->MoveSet(pp1);
	if (pp1->GetPlay_Time() > pp1->GetAnim_Time()) {
		pp1->SetSpeed(VGet(0.0f, 0.0f, 0.0f));
		pp1->SetAct_Mode(eCharaStop);
		pp1->SetMotion(pp1->GetAnimation_Data().stop);
		ChangeAnimation(pp1, pp1->GetAnimation_Data().stop);				// �A�j���[�V�����؂�ւ�
	}

	// �U�����̓����蔻������f���̑O���ɔz�u
	VECTOR AttackPosTop;
	AttackPosTop = player[0].GetPosition();
	AttackPosTop.x = player[0].GetPosition().x - cosf((player[0].GetDirection() - 1.001f) * 1.57f) * pp1->GetAttackMiddleRange();
	AttackPosTop.y = player[0].GetPosition().y + (PLAYER_SIZE_H - 100.0f);

	VECTOR AttackPosBottom;
	AttackPosBottom = player[0].GetPosition();
	AttackPosBottom.x = player[0].GetPosition().x - cosf((player[0].GetDirection() - 1.001f) * 1.57f) * pp1->GetAttackMiddleRange();
	AttackPosBottom.y = player[0].GetPosition().y + 100.0f;

	VECTOR pp2_MAX_Y_Pos;
	pp2_MAX_Y_Pos = pp2->GetPosition();
	pp2_MAX_Y_Pos.y = pp2->GetPosition().y + PLAYER_SIZE_H;

	if (HitCheck_Capsule_Capsule(VAdd(AttackPosTop, pp1->GetSpeed()), VAdd(AttackPosBottom, pp1->GetSpeed()),pp1->GetAttackRange(),
		VAdd(pp2_MAX_Y_Pos, pp2->GetSpeed()), VAdd(pp2->GetPosition(), pp2->GetSpeed()), pp2->GetWidth() / 2) == TRUE) {
		if (pp2->GetPosition().x >= pp1->GetPosition().x)
			pp2->SetBlowDirection(BLOWRIGHT);
		if (pp2->GetPosition().x < pp1->GetPosition().x)
			pp2->SetBlowDirection(BLOWLEFT);
		pp2->SetDamageFlg(TRUE);
		pp1->SetSpeed(VGet(0, 0, 0));
		pp2->SetAct_Mode(eCharaDamage);
		ChangeAnimation(pp2, pp2->GetAnimation_Data().damage);	// �A�j���[�V�����؂�ւ�
	}
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

	// �㏸���̃A�j���[�V����
	if (pp1->GetAnim_Attach() == pp1->GetAnimation_Data().jump)
		pp1->SetMotion(pp1->GetAnimation_Data().jump);

	// y���̑��x��0������������̏���
	if (pp1->GetAnim_Attach() != pp1->GetAnimation_Data().fall &&
		pp1->GetSpeed().y < 0 ) {
		ChangeAnimation(pp1, pp1->GetAnimation_Data().fall);	// �A�j���[�V�����؂�ւ�
	}

	pp1->MoveSet(pp1);
	
	if (pp1->GetSpeed().y > -50.0f) {
		pp1->SetY_Spd(pp1->GetSpeed().y - PLAYER_FALL_SPEED);
		if (pp1->GetSpeed().y < -2.0f && pp1->GetSpeed().y > -40.0f) {
			pp1->SetY_Spd(pp1->GetSpeed().y - PLAYER_FALL_SPEED);
		}
	}

	if (gamemode == eScenePlay1)
		Block_HitCheck(pp1);
	if (gamemode == eScenePlay2)
		Block_HitCheck2(pp1);

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

	// ������т̏���
	if (pp1->GetBlowDirection() == BLOWLEFT && pp1->GetDamageFlg() == TRUE) {
		pp1->SetX_Spd(-50.0f);
		pp1->SetDamageFlg(FALSE);
		pp1->SetDirection(RIGHT);
		if (pp1->GetSpeed().y <= 0)
			pp1->SetY_Spd(20.0f);
	}
	if (pp1->GetBlowDirection() == BLOWRIGHT && pp1->GetDamageFlg() == TRUE) {
		pp1->SetX_Spd(50.0f);
		pp1->SetDamageFlg(FALSE);
		pp1->SetDirection(LEFT);
		if (pp1->GetSpeed().y <= 0)
			pp1->SetY_Spd(20.0f);
	}

	// ����
	if (pp1->GetBlowDirection() == BLOWLEFT) {
		if (pp1->GetSpeed().x < 0)
			pp1->SetX_Spd(pp1->GetSpeed().x + 5.0f);
		if (pp1->GetSpeed().x > 0)
			pp1->SetX_Spd(0.0f);
	}
	if (pp1->GetBlowDirection() == BLOWRIGHT) {
		if (pp1->GetSpeed().x > 0)
			pp1->SetX_Spd(pp1->GetSpeed().x - 5.0f);
		if (pp1->GetSpeed().x < 0)
			pp1->SetX_Spd(0.0f);
	}

	if ( gamemode != eScenePlay2) {
		// �ړ�����
		if (pp1->GetPosition().x < (MIN_X + PLAYER_SIZE_W) && pp1->GetSpeed().x < 0) {
			pp1->SetX_Spd(0.0f);
			pp1->SetAct_Mode(eCharaFall);
			ChangeAnimation(pp1, pp1->GetAnimation_Data().jump);
		}
		if (pp1->GetPosition().x > (MAX_X - PLAYER_SIZE_W) && pp1->GetSpeed().x > 0) {
			pp1->SetX_Spd(0.0f);
			pp1->SetAct_Mode(eCharaFall);
			ChangeAnimation(pp1, pp1->GetAnimation_Data().jump);

		}
	}
	if (pp1->GetSpeed().y > -50.0f) {
		pp1->SetY_Spd(pp1->GetSpeed().y - PLAYER_FALL_SPEED);
		if (pp1->GetSpeed().y < -2.0f && pp1->GetSpeed().y > -40.0f) {
			pp1->SetY_Spd(pp1->GetSpeed().y - PLAYER_FALL_SPEED);
		}
	}

	if (gamemode == eScenePlay1)
		Block_HitCheck(pp1);

	if (gamemode == eScenePlay2)
		Block_HitCheck2(pp1);

	// �ړ��ʂ�������
	pp1->SetPosition(VAdd(pp1->GetPosition(), pp1->GetSpeed()));

	if (pp1->GetAnim_Time() < pp1->GetPlay_Time()) {
		pp1->SetFallDamageFlg(FALSE);
		pp1->SetBlowDirection(NONBLOW);
		pp1->SetSpeed(VGet(0.0f, 0.0f, 0.0f));
		pp1->SetAct_Mode(eCharaStop);
		pp1->SetMotion(pp1->GetAnimation_Data().stop);
		ChangeAnimation(pp1, pp1->GetAnimation_Data().stop);				// �A�j���[�V�����؂�ւ�
	}
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
 |						�������							|
 |                                                          |
 + ======================================================== */
void Player::CharaRevival(CharaBase* pp1, CharaBase* pp2) {
	pp1->SetRevivalTime(pp1->GetRevivalTime() - 1);

	if (gamemode == eScenePlay1) {
		if (pp1 == &player[0])
			pp1->SetPosition(VGet(300.0f, cpos.y - 500.0f, 0.0f));

		if (pp1 == &player[1])
			pp1->SetPosition(VGet(2700.0f, cpos.y - 500.0f, 0.0f));
	}

	if (gamemode == eScenePlay2) {
		if (pp1 == &player[0])
			pp1->SetPosition(VGet( 600.0f, cpos.y + 200.0f, 0.0f));

		if (pp1 == &player[1])
			pp1->SetPosition(VGet(2400.0f, cpos.y + 200.0f, 0.0f));
	}

	if (pp1->GetRevivalTime() % 3 == 0) {
		pp1->SetUse_Flg(FALSE);
	}
	else
	{
		pp1->SetUse_Flg(TRUE);
	}


	if (pp1->GetRevivalTime() == 0) {
		pp1->AddScore();
		if (gamemode == eScenePlay1)
			Revival_HitCheck(pp1);

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
//		pp1->SetSpeed(VGet(0, 0, 0));
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
							if (m_block[i].GetBlockPosition().x >= pp1->GetPosition().x) {
								pp1->SetBlowDirection(BLOWLEFT);
							}
							else
							{
								pp1->SetBlowDirection(BLOWRIGHT);
							}
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
							if (m_block[i].GetBlockPosition().x >= pp1->GetPosition().x) {
								pp1->SetBlowDirection(BLOWLEFT);
							}
							else
							{
								pp1->SetBlowDirection(BLOWRIGHT);
							}
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

			if (pp1->GetAct_Mode() == eCharaFall || pp1->GetAct_Mode() == eCharaDamage) {
				pp1->SetAct_Mode(eCharaStop);
				ChangeAnimation(pp1, pp1->GetAnimation_Data().stop);	// �A�j���[�V�����؂�ւ�
				pp1->SetAnim_Time(0.0f);
				pp1->SetSpeed(VGet(0.0f, 0.0f, 0.0f));
			}
		}
		else {
			pp1->SetDamageFlg(TRUE);
			pp1->SetAct_Mode(eCharaDamage);
			ChangeAnimation(pp1, pp1->GetAnimation_Data().damage);	// �A�j���[�V�����؂�ւ�
		}
	}
	else {
		if (b_damegeflg == FALSE) {
			// ���ɕ��������
			if (pp1->GetAct_Mode() != eCharaFall && pp1->GetAct_Mode() != eCharaDamage) { // �W�����v��Ԃ���Ȃ�
				pp1->SetAct_Mode(eCharaFall);
				ChangeAnimation(pp1, pp1->GetAnimation_Data().jump);
			}
		}
		else {
			pp1->SetFallDamageFlg(TRUE);
			pp1->SetDamageFlg(TRUE);
			pp1->SetAct_Mode(eCharaDamage);
			ChangeAnimation(pp1, pp1->GetAnimation_Data().damage);	// �A�j���[�V�����؂�ւ�
		}
	}
}
/* ======================================================== +
 |                    Block_HitCheck2( )                    |
 |             �@     �q�b�g�`�F�b�N2                       |
 |                                                          |
 + ======================================================== */
void Player::Block_HitCheck2(CharaBase* pp1) {
	HitFlag = 0;
	MaxY = 0.0f;
	bool b_damegeflg = FALSE;
	VECTOR cal_pos1 = VAdd(pp1->GetPosition(), VGet(0.0f, PLAYER_SIZE_H, 0.0f));
	VECTOR cal_pos2 = VAdd(pp1->GetPosition(), VGet(0.0f, -10.0f, 0.0f));

	for (int i = 0; i < 10; i++) {
		if (m_block2[i].GetBlockFlag() == TRUE) {
			switch (m_block2[i].GetBlockType()) {
			case TATAMI_BLOCK:
			case BREAK_BLOCK:
			case FALL_BLOCK:
			case WOOD_BLOCK:
			case MOVE_BLOCK_X:
			case MOVE_BLOCK_Y:
			case MOVE_BLOCK_Z:
				LineBlock = HitCheck_Line_Cube(cal_pos1, cal_pos2,
					VGet(m_block2[i].GetBlockPosition().x - BLOCK_X_SIZE, m_block2[i].GetBlockPosition().y, m_block2[i].GetBlockPosition().z - 100.0f),
					VGet(m_block2[i].GetBlockPosition().x + BLOCK_X_SIZE, m_block2[i].GetBlockPosition().y + BLOCK_TOP, m_block2[i].GetBlockPosition().z + 100.0f));
				break;

			case INVINCIBLE_BLOCK:
			case NEEDLE_BLOCK:
				LineBlock = HitCheck_Line_Cube(cal_pos1, cal_pos2,
					VGet(m_block2[i].GetBlockPosition().x - BLOCK_X_SIZE, m_block2[i].GetBlockPosition().y, m_block2[i].GetBlockPosition().z - 100.0f),
					VGet(m_block2[i].GetBlockPosition().x + BLOCK_X_SIZE, m_block2[i].GetBlockPosition().y + BLOCK_TOP * 2, m_block2[i].GetBlockPosition().z + 100.0f));
				break;
			}

			// ���������ꍇ�̏���
			if (LineBlock.HitFlag == TRUE) {
				// �|���S���ɓ��������t���O�𗧂Ă�
				if (pp1->GetSpeed().y > 0) {
					switch (m_block2[i].GetBlockType()) {
					case TATAMI_BLOCK:
					case BREAK_BLOCK:
					case FALL_BLOCK:
						// �u���b�N�̒�ʂ��v���C���[�̓������������̏���
						if (m_block2[i].GetBlockPosition().y < pp1->GetPosition().y + PLAYER_SIZE_H) {
							if (m_block2[i].GetBlockPosition().y + BLOCK_TOP > pp1->GetPosition().y + PLAYER_SIZE_H) {
								pp1->SetY_Spd(pp1->GetSpeed().y * -1);
								MaxY = m_block2[i].GetBlockPosition().y - PLAYER_SIZE_H;
								m_block2[i].SetBlockFlag(FALSE);
							}
							else {
								if (m_block2[i].GetBlockPosition().x < pp1->GetPosition().x) {
									pp1->SetX_Posi(m_block2[i].GetBlockPosition().x + (BLOCK_X_SIZE + PLAYER_SPEED));
									if (pp1->GetSpeed().x > 0)
										pp1->SetX_Spd(0.0f);
								}
								if (m_block2[i].GetBlockPosition().x > pp1->GetPosition().x) {
									pp1->SetX_Posi(m_block2[i].GetBlockPosition().x - (BLOCK_X_SIZE + PLAYER_SPEED));
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
						if (m_block2[i].GetBlockPosition().y < pp1->GetPosition().y + PLAYER_SIZE_H) {
							if (m_block2[i].GetBlockPosition().y + BLOCK_TOP > pp1->GetPosition().y + PLAYER_SIZE_H) {
								pp1->SetY_Spd(pp1->GetSpeed().y * -1);
								MaxY = pp1->GetPosition().y - 250.0f;
							}
							else {
								if (m_block2[i].GetBlockPosition().x < pp1->GetPosition().x) {
									pp1->SetX_Posi(m_block2[i].GetBlockPosition().x + (BLOCK_X_SIZE + PLAYER_SPEED));
									if (pp1->GetSpeed().x > 0)
										pp1->SetX_Spd(0.0f);
								}
								if (m_block2[i].GetBlockPosition().x > pp1->GetPosition().x) {
									pp1->SetX_Posi(m_block2[i].GetBlockPosition().x - (BLOCK_X_SIZE + PLAYER_SPEED));
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
					if (m_block2[i].GetBlockType() != INVINCIBLE_BLOCK && m_block2[i].GetBlockType() != NEEDLE_BLOCK) {
						if (m_block2[i].GetBlockPosition().y + (BLOCK_TOP / 2) <= pp1->GetPosition().y) {
							// �ڐG�����x���W��ۑ�����
							MaxY = m_block2[i].GetBlockPosition().y + BLOCK_TOP;
							if (m_block2[i].GetBlockType() == MOVE_BLOCK_X) {
								pp1->SetX_Spd(pp1->GetSpeed().x + m_block2[i].GetBlockSpeed().x);
							}
						}
						else {
							MaxY = pp1->GetPosition().y;
							if (pp1->GetSpeed().y < 0)
								HitFlag = 0;

							// ���̏��ւ̈ړ��̐���
							if (m_block2[i].GetBlockPosition().x < pp1->GetPosition().x) {
								pp1->SetX_Posi(m_block2[i].GetBlockPosition().x + (BLOCK_X_SIZE + PLAYER_SPEED));
								if (pp1->GetSpeed().x > 0)
									pp1->SetX_Spd(0.0f);
							}
							if (m_block2[i].GetBlockPosition().x > pp1->GetPosition().x) {
								pp1->SetX_Posi(m_block2[i].GetBlockPosition().x - (BLOCK_X_SIZE + PLAYER_SPEED));
								if (pp1->GetSpeed().x < 0)
									pp1->SetX_Spd(0.0f);
							}
						}
					}
					else {
						if (m_block2[i].GetBlockType() == NEEDLE_BLOCK) {
							b_damegeflg = TRUE;
							if (pp1->GetSpeed().y < 0)
								HitFlag = 0;
						}
						if (m_block2[i].GetBlockPosition().y + BLOCK_TOP + (BLOCK_TOP / 2) <= pp1->GetPosition().y) {
							// �ڐG�����x���W��ۑ�����
							MaxY = m_block2[i].GetBlockPosition().y + BLOCK_TOP * 2;
						}
						else {
							MaxY = pp1->GetPosition().y;
							if (pp1->GetSpeed().y < 0)
								HitFlag = 0;
							if (m_block2[i].GetBlockPosition().x < pp1->GetPosition().x) {
								pp1->SetX_Posi(m_block2[i].GetBlockPosition().x + (BLOCK_X_SIZE + PLAYER_SPEED));
								if (pp1->GetSpeed().x > 0)
									pp1->SetX_Spd(0.0f);
							}
							if (m_block2[i].GetBlockPosition().x > pp1->GetPosition().x) {
								pp1->SetX_Posi(m_block2[i].GetBlockPosition().x - (BLOCK_X_SIZE + PLAYER_SPEED));
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
 |                    Revival_HitCheck( )					|
 |             �@     �������q�b�g�`�F�b�N					|
 |                                                          |
 + ======================================================== */
void Player::Revival_HitCheck(CharaBase* pp1) {
	for (int i = 0; i < BACKGROUNDFLOOR; i++) {
		if (pp1->GetPosition().y < 200.0f + (i * 1000.0f) && pp1->GetPosition().y > (i * 1000.0f) - 450.0f)
			pp1->SetPosition(VGet(pp1->GetPosition().x, 220.0f + (i * 1000.0f), pp1->GetPosition().z));
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

	if ((cpos.y - pp1->GetPosition().y > 2050.0f)) {
		pp1->SetAct_Mode(eCharaRevival);
		pp1->SetDirection(DOWN);
		pp1->SetRevivalTime(100);
	}

	// �A�N�V�������[�v
	( this->*PlayerModeTbl[act_mode] )( pp1 , pp2 ) ;

	return( false ) ;
}



