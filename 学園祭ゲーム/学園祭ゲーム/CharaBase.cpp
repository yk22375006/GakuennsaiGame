
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
int CharaBase::MoveSet( )
{
	switch ( key1 & (PAD_INPUT_LEFT + PAD_INPUT_RIGHT + PAD_INPUT_DOWN + PAD_INPUT_UP) )
	{
		case PAD_INPUT_DOWN:
//			spd.x = 0.0f ;
//			spd.z = -12.0f ; // 下を押下 手前に移動
//			direction = DOWN ;
			break ;

		case PAD_INPUT_UP:
//			spd.x = 0.0f ;
//			spd.z = 12.0f ; // 下を押下 手前に移動
//			direction = UP ;
			spd.y = 40.0f;
			act_mode = eCharaJump;
			break ;

		case PAD_INPUT_LEFT:
			spd.x = -12.0f ; // 左を押下 左に移動
			spd.z = 0.0f ;
			direction = LEFT ;
			break ;

		case PAD_INPUT_RIGHT:
			spd.x = 12.0f ; // 右を押下 右に移動
			spd.z = 0.0f ;
			direction = RIGHT ;
			break ;

/*		case (PAD_INPUT_LEFT + PAD_INPUT_DOWN):
			spd.x = -8.0f ; // 右を押下 右に移動
			spd.z = -8.0f ;
			direction = DOWN + 0.5f ;
			break ;

		case (PAD_INPUT_LEFT + PAD_INPUT_UP) :
			spd.x = -8.0f ; // 右を押下 右に移動
			spd.z = 8.0f ;
			direction = LEFT + 0.5f ;
			break ;

		case (PAD_INPUT_RIGHT + PAD_INPUT_DOWN) :
			spd.x = 8.0f ; // 右を押下 右に移動
			spd.z = -8.0f ;
			direction = RIGHT + 0.5f ;
			break ;

		case (PAD_INPUT_RIGHT + PAD_INPUT_UP) :
			spd.x = 8.0f ; // 右を押下 右に移動
			spd.z = 8.0f ;
			direction = UP + 0.5f ;
			break ;
*/	}


	return( false ) ;
}

