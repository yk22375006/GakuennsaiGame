
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
int CharaBase::MoveSet( )
{
	switch ( key1 & (PAD_INPUT_LEFT + PAD_INPUT_RIGHT + PAD_INPUT_DOWN + PAD_INPUT_UP) )
	{
		case PAD_INPUT_DOWN:
//			spd.x = 0.0f ;
//			spd.z = -12.0f ; // �������� ��O�Ɉړ�
//			direction = DOWN ;
			break ;

		case PAD_INPUT_UP:
//			spd.x = 0.0f ;
//			spd.z = 12.0f ; // �������� ��O�Ɉړ�
//			direction = UP ;
			spd.y = 40.0f;
			act_mode = eCharaJump;
			break ;

		case PAD_INPUT_LEFT:
			spd.x = -12.0f ; // �������� ���Ɉړ�
			spd.z = 0.0f ;
			direction = LEFT ;
			break ;

		case PAD_INPUT_RIGHT:
			spd.x = 12.0f ; // �E������ �E�Ɉړ�
			spd.z = 0.0f ;
			direction = RIGHT ;
			break ;

/*		case (PAD_INPUT_LEFT + PAD_INPUT_DOWN):
			spd.x = -8.0f ; // �E������ �E�Ɉړ�
			spd.z = -8.0f ;
			direction = DOWN + 0.5f ;
			break ;

		case (PAD_INPUT_LEFT + PAD_INPUT_UP) :
			spd.x = -8.0f ; // �E������ �E�Ɉړ�
			spd.z = 8.0f ;
			direction = LEFT + 0.5f ;
			break ;

		case (PAD_INPUT_RIGHT + PAD_INPUT_DOWN) :
			spd.x = 8.0f ; // �E������ �E�Ɉړ�
			spd.z = -8.0f ;
			direction = RIGHT + 0.5f ;
			break ;

		case (PAD_INPUT_RIGHT + PAD_INPUT_UP) :
			spd.x = 8.0f ; // �E������ �E�Ɉړ�
			spd.z = 8.0f ;
			direction = UP + 0.5f ;
			break ;
*/	}


	return( false ) ;
}

