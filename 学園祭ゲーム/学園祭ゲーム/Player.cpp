
// ------------------------------------------------------------------------ //
//							プレイヤーの初期セット							//
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
 |                     　コンストラクタ                     |
 |                                                          |
 + ======================================================== */
Player::Player( ) 
{
	init( ) ;
}

/* ======================================================== +
 |                                                          |
 |                     　デストラクタ                       |
 |                                                          |
 + ======================================================== */
Player::~Player( ) 
{
}

/* ======================================================== +
 |                         init( )                          |
 |                     　初期セット　                       |
 |                                                          |
 + ======================================================== */
int Player::init( )
{
	use_flg = TRUE ;						// 使用フラグセット
	act_mode = eCharaStop ;					// 初期モード
	spd = VGet( 0.0f , 0.0f , 0.0f ) ;		// スピードクリア
	posi = VGet( 0.0f , 0.0f , 0.0f ) ;		// 位置初期セット
	Width = PLAYER_SIZE_W;					// プレイヤーサイズ幅
	Height = PLAYER_SIZE_H ;				// プレイヤーサイズ高さ
	RevivalTime = 0;

	return( false ) ;
}

/* ======================================================== +
 |                          Draw( )                         |
 |                     　  　描画　　                       |
 |                                                          |
 + ======================================================== */
int Player::Draw( CharaBase *pp1 )
{
	// モデルの回転
	MV1SetRotationXYZ( pp1->anim.model, VGet( 0.0f, 1.57f * pp1->GetDirection( ) , 0.0f ) ) ;

	// モデルの移動(配置)
	MV1SetPosition(pp1->anim.model, pp1->GetPosition());

	// モデルの描画
	MV1DrawModel( pp1->anim.model ) ;

	return( false ) ;
}

/* ======================================================== +
 |                        AllowKey( )                       |
 |                     　  キー入力                         |
 |                                                          |
 + ======================================================== */
int Player::AllowKey( )
{
	// 移動キーが押されたら
	if ( (key1 & PAD_INPUT_DOWN) || (key1 & PAD_INPUT_UP) ||
				(key1 & PAD_INPUT_LEFT) || (key1 & PAD_INPUT_RIGHT) )
	{
		return( true ) ;
	}

	return( false ) ;
}

/* ======================================================== +
 |                      AnimationInit( )                    |
 |                   アニメーション初期セット               |
 |                                                          |
 + ======================================================== */
int Player::AnimationInit()
{
	g_Chara[0]->SetMotion(anim.stop);
	g_Chara[1]->SetMotion(anim.stop);

	// アニメーションセット
	anim_attach = MV1AttachAnim(anim.model, 0, anim.stop);
	anim_time = MV1GetAttachAnimTotalTime(anim.model, anim_attach);

	// アニメーションして動いてもその場で動いてるような状態にする
	rootflm = MV1SearchFrame(anim.model, "root");
	MV1SetFrameUserLocalMatrix(anim.model, rootflm, MGetIdent());
	play_time = 0.0f;

	return(false);
}

/* ======================================================== +
 |                        Animation( )                      |
 |                     　アニメーション　　                 |
 |                                                          |
 + ======================================================== */
int Player::Animation(CharaBase* pp1)
{
	if (pp1->GetPlay_Time() > pp1->GetAnim_Time()) {
		pp1->SetPlay_Time(0.0f);
	}
	// アニメーション再生時間と同期させる
	MV1SetAttachAnimTime(pp1->GetAnimation_Data().model, pp1->GetAnim_Attach(), pp1->GetPlay_Time());

	return(false);
}

/* ======================================================== +
 |                     ChangeAnimation( )                   |
 |                    アニメーション切り替え                |
 |                                                          |
 + ======================================================== */
int Player::ChangeAnimation(CharaBase* pp1, int set_anim)
{
	// アニメーションをデタッチする
	MV1DetachAnim(pp1->GetAnimation_Data().model, pp1->GetAnim_Attach());

	// アニメーションセット(切り替え)
	pp1->SetAnim_Attach(MV1AttachAnim(pp1->GetAnimation_Data().model, 0, set_anim));
	pp1->SetAnim_Time(MV1GetAttachAnimTotalTime(pp1->GetAnimation_Data().model, pp1->GetAnim_Attach()));

	// アニメーションして動いてもその場で動いてるような状態にする
	pp1->SetRootFlm(MV1SearchFrame(pp1->GetAnimation_Data().model, "root"));
	MV1SetFrameUserLocalMatrix(pp1->GetAnimation_Data().model, pp1->GetRootFlm(), MGetIdent());
	pp1->SetPlay_Time(0.0f);

	return(false);
}

/* ======================================================== +
 |                        AnimationType( )                  |
 |                     　アニメーション　　                 |
 |                                                          |
 + ======================================================== */
int Player::AnimationType(CharaBase* pp1)
{
	if (pp1->GetPlay_Time() > pp1->GetAnim_Time()) {
		pp1->SetPlay_Time(0.0f);
	}
	// アニメーション再生時間と同期させる
	MV1SetAttachAnimTime(pp1->GetAnimation_Data().type[chara_type], pp1->GetAnim_Attach(), pp1->GetPlay_Time());

	return(false);
}

/* ======================================================== +
 |                     ChangeAnimationType( )               |
 |                    アニメーション切り替え                |
 |                                                          |
 + ======================================================== */
int Player::ChangeAnimationType(CharaBase* pp1, int set_anim)
{
	// アニメーションをデタッチする
	MV1DetachAnim(pp1->GetAnimation_Data().type[chara_type], pp1->GetAnim_Attach());

	// アニメーションセット(切り替え)
	pp1->SetAnim_Attach(MV1AttachAnim(pp1->GetAnimation_Data().type[chara_type], 0, set_anim));
	pp1->SetAnim_Time(MV1GetAttachAnimTotalTime(pp1->GetAnimation_Data().type[chara_type], pp1->GetAnim_Attach()));

	// アニメーションして動いてもその場で動いてるような状態にする
	pp1->SetRootFlm(MV1SearchFrame(pp1->GetAnimation_Data().type[chara_type], "root"));
	MV1SetFrameUserLocalMatrix(pp1->GetAnimation_Data().type[chara_type], pp1->GetRootFlm(), MGetIdent());
	pp1->SetPlay_Time(0.0f);

	return(false);
}

/* ############################################################################################### */
/* ======================================================== +
 |                       CharaStop( )                       |
 |                       　停止中　                         |
 |                                                          |
 + ======================================================== */
void Player::CharaStop( CharaBase *pp1 , CharaBase* pp2)
{
	pp1->SetX_Spd(0.0f);

	// アニメーション
	pp1->AddPlay_Time( 0.5f ) ;
	pp1->SetMotion( pp1->GetAnimation_Data( ).stop ) ;

	if ( AllowKey( ) == (int)true ){
		if (key1 & PAD_INPUT_UP){
			pp1->MoveSet( );
		}
		else {
			pp1->SetAct_Mode(eCharaMove);
			pp1->SetMotion(pp1->GetAnimation_Data().run);
			ChangeAnimation(pp1, pp1->GetAnimation_Data().run);	// アニメーション切り替え
		}
	}
	Block_HitCheck(pp1);

	// 移動量を加える
	pp1->SetPosition(VAdd(pp1->GetPosition(), pp1->GetSpeed()));

	// 移動量セット
//	pp1->MoveSet( ) ;

	// Aが△
	// Bが○
	// Cが×
	// Xが□
	// ○が押されたら
	if (key1 & PAD_INPUT_C) {
		pp1->SetAct_Mode(eCharaAttack);
		pp1->SetMotion(pp1->GetAnimation_Data().attack);
		ChangeAnimation(pp1, pp1->GetAnimation_Data().attack);	// アニメーション切り替え
	}

	// xが押されたら
	if (key1 & PAD_INPUT_2) {
//		pp1->SetAct_Mode(eCharaDown);
//		pp1->SetMotion(pp1->GetAnimation_Data().down);
//		ChangeAnimation(pp1, pp1->GetAnimation_Data().down);	// アニメーション切り替え
	}

	if (key1 & PAD_INPUT_3) {
		pp1->SetAct_Mode(eCharaDamage);
//		pp1->SetMotion(pp1->GetAnimation_Data().damage);
//		ChangeAnimation(pp1, pp1->GetAnimation_Data().damage);	// アニメーション切り替え
	}

	if (key1 & PAD_INPUT_10) {
//		pp1->SetSpeed(VGet(0.0f, 0.0f, 0.0f));
//		pp1->SetAct_Mode(eCharaJump);
//		pp1->SetMotion(pp1->GetAnimation_Data().jump);
//		ChangeAnimation(pp1, pp1->GetAnimation_Data().jump);	// アニメーション切り替え
	}
}

/* ======================================================== +
 |                       CharaMove( )                       |
 |                     　    移動　                         |
 |                                                          |
 + ======================================================== */
void Player::CharaMove( CharaBase *pp1 , CharaBase* pp2)
{
	pp1->SetX_Spd(0.0f);
	// アニメーション
	pp1->AddPlay_Time( 1.0f ) ;
	pp1->SetMotion( pp1->GetAnimation_Data( ).run ) ;

	// 移動量セット(方向転換)
	pp1->MoveSet( ) ;

	// ヒットチェック
	Move_HitCheck( pp1 , pp2) ;

	Block_HitCheck(pp1);

	// 移動量を加える
	pp1->SetPosition( VAdd( pp1->GetPosition( ) , pp1->GetSpeed( ) ) ) ;

	// ○が押されたら
	if (key1 & PAD_INPUT_C) {
		pp1->SetSpeed(VGet(0.0f, 0.0f, 0.0f));
		pp1->SetAct_Mode(eCharaAttack);
		ChangeAnimation(pp1, pp1->GetAnimation_Data().attack);	// アニメーション切り替え
	}

	// xが押されたら
	if (key1 & PAD_INPUT_2) {
//		pp1->SetAct_Mode(eCharaDown);
//		pp1->SetMotion(pp1->GetAnimation_Data().down);
//		ChangeAnimation(pp1, pp1->GetAnimation_Data().down);	// アニメーション切り替え
	}

	if (key1 & PAD_INPUT_10) {
		pp1->SetSpeed(VGet(0.0f, 0.0f, 0.0f));
///		pp1->SetAct_Mode(eCharaJumpInit);
//		pp1->SetMotion(pp1->GetAnimation_Data().jump);
//		ChangeAnimation(pp1, pp1->GetAnimation_Data().jump);	// アニメーション切り替え
	}

	// 何も押されていなければ
	if (key1 == 0) {
		pp1->SetSpeed(VGet(0.0f, 0.0f, 0.0f));
		pp1->SetAct_Mode(eCharaStop);
		pp1->SetMotion(pp1->GetAnimation_Data().stop);
		ChangeAnimation(pp1, pp1->GetAnimation_Data().stop);				// アニメーション切り替え
	}

//	if (key1 & PAD_INPUT_3) {
//		pp1->SetAct_Mode(eCharaDamage);
//		pp1->SetMotion(pp1->GetAnimation_Data().damage);
//		ChangeAnimation(pp1, pp1->GetAnimation_Data().damage);	// アニメーション切り替え
//	}

}
/* ======================================================== +
 |                       CharaAttack( )                     |
 |                     　    攻撃　                         |
 |                                                          |
 + ======================================================== */
void Player::CharaAttack(CharaBase* pp1, CharaBase* pp2)
{
	// アニメーション
	pp1->AddPlay_Time(0.5f);
	pp1->SetMotion(pp1->GetAnimation_Data().attack);

	// 移動量セット
	pp1->MoveSet();
	if (pp1->GetPlay_Time() > pp1->GetAnim_Time()) {
		pp1->SetSpeed(VGet(0.0f, 0.0f, 0.0f));
		pp1->SetAct_Mode(eCharaStop);
		pp1->SetMotion(pp1->GetAnimation_Data().stop);
		ChangeAnimation(pp1, pp1->GetAnimation_Data().stop);				// アニメーション切り替え
	}


/*	if (HitCheck_Capsule_Capsule(VAdd(pp1->GetPosition(), pp1->GetSpeed()), VAdd(pp1->GetPosition(), pp1->GetSpeed()), pp1->GetWidth() / 2,
		VAdd(pp2->GetPosition(), pp2->GetSpeed()), VAdd(pp2->GetPosition(), pp2->GetSpeed()), pp2->GetWidth() / 2) == TRUE) {
		pp1->SetSpeed(VGet(0, 0, 0));
		pp2->SetAct_Mode(eCharaDamage);
		pp2->SetMotion(pp2->GetAnimation_Data().damage);
		ChangeAnimation(pp2, pp2->GetAnimation_Data().damage);
		CharaDamage(pp2, pp1);
	}

	// プレイヤー１
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

		// カメラに移動量を加える
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
 |						ジャンプ初期設定					|
 |															|
 + ======================================================== */
void Player::CharaJump(CharaBase* pp1, CharaBase* pp2)
{
	pp1->AddPlay_Time(0.5f);
	pp1->SetX_Spd(0.0f);
	pp1->SetY_Posi(posi.y + 11.0f);
	pp1->SetY_Spd(PLAYER_JUMP_SPEED);
	pp1->SetAct_Mode(eCharaFall);
	ChangeAnimation(pp1, pp1->GetAnimation_Data().jump);	// アニメーション切り替え
}

/* ======================================================== +
 |                       CharaFall( )                 　	|
 |							落下							|
 |                                                          |
 + ======================================================== */
void Player::CharaFall(CharaBase* pp1, CharaBase* pp2) {
	// アニメーション
	pp1->AddPlay_Time(0.5f);

	if (pp1->GetAnimation_Data().model == pp1->anim.jump_in)
		ChangeAnimation(pp1, pp1->GetAnimation_Data().jump);	// アニメーション切り替え

	if (pp1->GetAnim_Attach() == pp1->GetAnimation_Data().jump)
		pp1->SetMotion(pp1->GetAnimation_Data().jump);

	if (pp1->GetAnim_Attach() != pp1->GetAnimation_Data().fall &&
		pp1->GetSpeed().y < 0 ) {
		ChangeAnimation(pp1, pp1->GetAnimation_Data().fall);	// アニメーション切り替え
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
 |                     　ダメージ　                         |
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
		ChangeAnimation(pp1, pp1->GetAnimation_Data().stop);				// アニメーション切り替え
	}
	printf("%d\n", HitFlag);
}

/* ======================================================== +
 |                       CharaDown( )                     　|
 |                     　 ダウン　                          |
 |                                                          |
 + ======================================================== */
void Player::CharaDown(CharaBase* pp1, CharaBase* pp2)
{
}
/* ======================================================== +
 |                    CharaRevival( )                       |
 |             　     ヒットチェック　                      |
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
		ChangeAnimation(pp1, pp1->GetAnimation_Data().stop);				// アニメーション切り替え
	}
}

/* ======================================================== +
 |                    Move_HitCheck( )                      |
 |             　     ヒットチェック　                      |
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
 |             　     ヒットチェック　                      |
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

			// 当たった場合の処理
			if (LineBlock.HitFlag == TRUE) {
				// ポリゴンに当たったフラグを立てる
				if (pp1->GetSpeed().y > 0) {
					switch (m_block[i].GetBlockType()) {
						case TATAMI_BLOCK:
						case BREAK_BLOCK:
						case FALL_BLOCK:
							// ブロックの底面よりプレイヤーの頭が小さい時の処理
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
							// 接触したＹ座標を保存する
							MaxY = m_block[i].GetBlockPosition().y + BLOCK_TOP;
							if (m_block[i].GetBlockType() == MOVE_BLOCK_X) {
								pp1->SetX_Spd(pp1->GetSpeed().x + m_block[i].GetBlockSpeed().x);
							}
						}
						else {
							MaxY = pp1->GetPosition().y;
							if (pp1->GetSpeed().y < 0)
								HitFlag = 0;

							// 横の床への移動の制限
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
							// 接触したＹ座標を保存する
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
	// 床ポリゴンに当たったかどうかで処理を分岐
	if (HitFlag == 1) {
		if (b_damegeflg == FALSE) {
			// 接触したポリゴンで一番高いＹ座標をキャラクターのＹ座標にする
			pp1->SetY_Posi(MaxY);
			pp1->SetY_Spd(0.0f);

			if (pp1->GetAct_Mode() == eCharaFall) {
				pp1->SetAct_Mode(eCharaStop);
				ChangeAnimation(pp1, pp1->GetAnimation_Data().stop);	// アニメーション切り替え
				pp1->SetAnim_Time(0.0f);
				pp1->SetSpeed(VGet(0.0f, 0.0f, 0.0f));
			}
		}
		else {
			pp1->SetAct_Mode(eCharaDamage);
			ChangeAnimation(pp1, pp1->GetAnimation_Data().damage);	// アニメーション切り替え
		}
	}
	else {
		if (b_damegeflg == FALSE) {
			// 宙に浮いた状態
			if (pp1->GetAct_Mode() != eCharaFall) { // ジャンプ状態じゃない
				pp1->SetAct_Mode(eCharaFall);
				ChangeAnimation(pp1, pp1->GetAnimation_Data().jump);
			}
		}
		else {
			pp1->SetAct_Mode(eCharaDamage);
			ChangeAnimation(pp1, pp1->GetAnimation_Data().damage);	// アニメーション切り替え
		}
	}
}

/* ======================================================== +
 |                       ActionLoop( )                      |
 |                     　アクション　                       |
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
	// キー操作
	if (pp1 == &player[0])
		key1 = GetJoypadInputState(DX_INPUT_KEY_PAD1);
	if (pp1 == &player[1])
		key1 = GetJoypadInputState(DX_INPUT_PAD2);

	if ((cpos.y - pp1->GetPosition().y > 2750.0f) && (pp1 == &player[0])) {
		pp1->SetAct_Mode(eCharaRevival);
		pp1->SetRevivalTime(100);
	}

	// アクションループ
	( this->*PlayerModeTbl[act_mode] )( pp1 , pp2 ) ;

	return( false ) ;
}



