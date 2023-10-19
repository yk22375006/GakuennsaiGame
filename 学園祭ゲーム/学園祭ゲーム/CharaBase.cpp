
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
	switch ( key[0] & (PAD_INPUT_LEFT + PAD_INPUT_RIGHT + PAD_INPUT_C) )
	{
		case PAD_INPUT_C :
			if (act_mode != eCharaFall) {
				posi.y = posi.y + 11.0f;
				act_mode = eCharaJump;
			}
			break ;

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

		case (PAD_INPUT_LEFT + PAD_INPUT_C):
			spd.x = -PLAYER_SPEED; // 右を押下 右に移動
			if (act_mode != eCharaFall) {
				posi.y = posi.y + 11.0f;
				switch (type) {
					case SPEEDMODE :
						spd.y = SPEED_JUMP_SPEED;
						break;

					case BALANCEMODE:
						spd.y = BALANCE_JUMP_SPEED;
						break;

					case POWERMODE:
						spd.y = POWER_JUMP_SPEED;
						break;
				}
				act_mode = eCharaJump;
			}
			break ;

		case (PAD_INPUT_RIGHT + PAD_INPUT_C):
			spd.x = PLAYER_SPEED; // 右を押下 右に移動
			if (act_mode != eCharaFall) {
				posi.y = posi.y + 11.0f;
				switch (type) {
					case SPEEDMODE:
						spd.y = SPEED_JUMP_SPEED;
						break;

					case BALANCEMODE:
						spd.y = BALANCE_JUMP_SPEED;
						break;

					case POWERMODE:
						spd.y = POWER_JUMP_SPEED;
						break;
				}
				act_mode = eCharaJump;
			}
			break ;
	}
	if (posi.x < (100.0f + PLAYER_SIZE_W)&& spd.x < 0 )
		spd.x = 0.0f;
	if (posi.x > (2900.0f - PLAYER_SIZE_W) && spd.x > 0)
		spd.x = 0.0f;

	return( false ) ;
}



