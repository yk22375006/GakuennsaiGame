
#include "Common.h"

/* -------------------------------------------------------- +
 |                                                          |
 |                        CharaBase.cpp                     |
 |                                                          |
 + -------------------------------------------------------- */
/* ======================================================== +
 |                                                          |
 |                     �@�R���X�g���N�^                     |
 |                                                          |
 + ======================================================== */
CharaBase::CharaBase( ) 
{
	init( ) ;
}

/* ======================================================== +
 |                                                          |
 |                     �@�f�X�g���N�^                       |
 |                                                          |
 + ======================================================== */
CharaBase::~CharaBase( ) 
{
}

/* ======================================================== +
 |                         init( )                          |
 |                     �@�����Z�b�g�@                       |
 |                                                          |
 + ======================================================== */
int CharaBase::init( )
{
	use_flg = TRUE ;						// �g�p�t���O�Z�b�g
	act_mode = 0 ;							// �A�N�V�������[�h�Z�b�g
	direction = DOWN ;						// ������
	spd = VGet( 0.0f , 0.0f , 0.0f ) ;		// �X�s�[�h�N���A
	posi = VGet( 0.0f , 0.0f , 0.0f ) ;		// �ʒu�����Z�b�g

	return( false ) ;
}

/* ======================================================== +
 |                         MoveSet( )                       |
 |                     �@  �@�`��@�@                       |
 |                                                          |
 + ======================================================== */
int CharaBase::MoveSet(CharaBase* pp1)
{
	switch ( key1 & (PAD_INPUT_LEFT + PAD_INPUT_RIGHT + PAD_INPUT_DOWN + PAD_INPUT_UP + PAD_INPUT_C) )
	{
		case PAD_INPUT_UP:
		case PAD_INPUT_C :
			if (act_mode != eCharaFall) {
				act_mode = eCharaJump;
			}
			break ;

		case PAD_INPUT_DOWN:
//			direction = DOWN;
			break;

		case PAD_INPUT_LEFT:
			spd.x = -pp1->GetMoveSpeed(); // �������� ���Ɉړ�
			spd.z = 0.0f ;
			direction = LEFT ;
			break ;

		case PAD_INPUT_RIGHT:
			spd.x = pp1->GetMoveSpeed(); // �E������ �E�Ɉړ�
			spd.z = 0.0f ;
			direction = RIGHT ;
			break ;

		case (PAD_INPUT_LEFT + PAD_INPUT_UP) :
		case (PAD_INPUT_LEFT + PAD_INPUT_C):
			spd.x = -pp1->GetMoveSpeed(); // �E������ �E�Ɉړ�
			if (act_mode != eCharaFall) {
				posi.y = posi.y + 11.0f;
				spd.y = PLAYER_JUMP_SPEED;
				act_mode = eCharaJump;
			}
			break ;

		case (PAD_INPUT_RIGHT + PAD_INPUT_UP) :
		case (PAD_INPUT_RIGHT + PAD_INPUT_C):
			spd.x = pp1->GetMoveSpeed(); // �E������ �E�Ɉړ�
			if (act_mode != eCharaFall) {
				posi.y = posi.y + 11.0f;
				spd.y = PLAYER_JUMP_SPEED;
				act_mode = eCharaJump;
			}
			break ;
	}
	if (posi.x < (MIN_X + PLAYER_SIZE_W)&& spd.x < 0 )
		spd.x = 0.0f;
	if (posi.x > (MAX_X - PLAYER_SIZE_W) && spd.x > 0)
		spd.x = 0.0f;

	return( false ) ;
}

