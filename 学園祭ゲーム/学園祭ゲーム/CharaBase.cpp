
#include "Common.h"

/* -------------------------------------------------------- +
 |                                                          |
 |                        CharaBase.cpp                     |
 |                                                          |
 + -------------------------------------------------------- */
/* ======================================================== +
 |                                                          |
 |                     　コンストラクタ                     |
 |                                                          |
 + ======================================================== */
CharaBase::CharaBase( ) 
{
	init( ) ;
}

/* ======================================================== +
 |                                                          |
 |                     　デストラクタ                       |
 |                                                          |
 + ======================================================== */
CharaBase::~CharaBase( ) 
{
}

/* ======================================================== +
 |                         init( )                          |
 |                     　初期セット　                       |
 |                                                          |
 + ======================================================== */
int CharaBase::init( )
{
	use_flg = TRUE ;						// 使用フラグセット
	act_mode = 0 ;							// アクションモードセット
	direction = DOWN ;						// 下向き
	spd = VGet( 0.0f , 0.0f , 0.0f ) ;		// スピードクリア
	posi = VGet( 0.0f , 0.0f , 0.0f ) ;		// 位置初期セット

	return( false ) ;
}

/* ======================================================== +
 |                         MoveSet( )                       |
 |                     　  　描画　　                       |
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
			spd.x = -pp1->GetMoveSpeed(); // 左を押下 左に移動
			spd.z = 0.0f ;
			direction = LEFT ;
			break ;

		case PAD_INPUT_RIGHT:
			spd.x = pp1->GetMoveSpeed(); // 右を押下 右に移動
			spd.z = 0.0f ;
			direction = RIGHT ;
			break ;

		case (PAD_INPUT_LEFT + PAD_INPUT_UP) :
		case (PAD_INPUT_LEFT + PAD_INPUT_C):
			spd.x = -pp1->GetMoveSpeed(); // 右を押下 右に移動
			if (act_mode != eCharaFall) {
				posi.y = posi.y + 11.0f;
				spd.y = PLAYER_JUMP_SPEED;
				act_mode = eCharaJump;
			}
			break ;

		case (PAD_INPUT_RIGHT + PAD_INPUT_UP) :
		case (PAD_INPUT_RIGHT + PAD_INPUT_C):
			spd.x = pp1->GetMoveSpeed(); // 右を押下 右に移動
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

