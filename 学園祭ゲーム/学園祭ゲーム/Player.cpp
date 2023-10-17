
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
	RevivalTime = 0;						// 復活にかかる時間
	selectflg = FALSE;						// キャラ選択
	blowdirection = NONBLOW;				// 吹っ飛ぶ方向
	damageflg = FALSE;						// 攻撃された
	falldamageflg = FALSE;					// 落下中にダメージを負った
	type = SPEEDMODE;
	score = 0;
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
				(key1 & PAD_INPUT_LEFT) || (key1 & PAD_INPUT_RIGHT) ||
					key1 & PAD_INPUT_C)
	{
		return( true ) ;
	}

	return( false ) ;
}
/* ======================================================== +
 |                      LoadAnimation( )                    |
 |                   アニメーション読み込み               |
 |                                                          |
 + ======================================================== */
int Player::LoadAnimation(CharaBase* pp1) {

	if (pp1 == &player[0]) {
		switch (pp1->GetType())
		{
			case SPEEDMODE:
			case POWERMODE:
				pp1->anim.model		= MV1DuplicateModel(Original[0].type[SPEEDMODE]);
				pp1->anim.stop		= MV1DuplicateModel(Original[0].typestop[SPEEDMODE]);		// 立ちアニメ
				pp1->anim.run		= MV1DuplicateModel(Original[0].run);		// 走りアニメ
				pp1->anim.jump_in	= MV1DuplicateModel(Original[0].jump_in);	// ジャンプ入り始めアニメ
				pp1->anim.jump		= MV1DuplicateModel(Original[0].jump);		// ジャンプループアニメ
				pp1->anim.fall		= MV1DuplicateModel(Original[0].fall);		// ジャンプループアニメ
				pp1->anim.attack	= MV1DuplicateModel(Original[0].attack);	// 攻撃アニメ
				pp1->anim.damage	= MV1DuplicateModel(Original[0].damage);	// 被ダメージアニメ
				break;

			case BALANCEMODE:
				pp1->anim.model		= MV1DuplicateModel(Original[0].type[BALANCEMODE]);
				pp1->anim.stop		= MV1DuplicateModel(Original[0].typestop[BALANCEMODE]);		// 立ちアニメ
				pp1->anim.run		= MV1DuplicateModel(Original[1].run);		// 走りアニメ
				pp1->anim.jump_in	= MV1DuplicateModel(Original[1].jump_in);	// ジャンプ入り始めアニメ
				pp1->anim.jump		= MV1DuplicateModel(Original[1].jump);		// ジャンプループアニメ
				pp1->anim.fall		= MV1DuplicateModel(Original[1].fall);		// ジャンプループアニメ
				pp1->anim.attack	= MV1DuplicateModel(Original[1].attack);	// 攻撃アニメ
				pp1->anim.damage	= MV1DuplicateModel(Original[1].damage);	// 被ダメージアニメ
				break;
		}
	}
	if (pp1 == &player[1]) {
		switch (pp1->GetType()) {
			case SPEEDMODE:
			case POWERMODE:
				pp1->anim.model		= MV1DuplicateModel(Original[1].type[SPEEDMODE]);
				pp1->anim.stop		= MV1DuplicateModel(Original[1].typestop[SPEEDMODE]);		// 立ちアニメ 
				pp1->anim.run		= MV1DuplicateModel(Original[0].run);		// 走りアニメ
				pp1->anim.jump_in	= MV1DuplicateModel(Original[0].jump_in);	// ジャンプ入り始めアニメ
				pp1->anim.jump		= MV1DuplicateModel(Original[0].jump);		// ジャンプループアニメ
				pp1->anim.fall		= MV1DuplicateModel(Original[0].fall);		// ジャンプループアニメ
				pp1->anim.attack	= MV1DuplicateModel(Original[0].attack);	// 攻撃アニメ
				pp1->anim.damage	= MV1DuplicateModel(Original[0].damage);	// 被ダメージアニメ
				break;

			case BALANCEMODE:
				pp1->anim.model		= MV1DuplicateModel(Original[1].type[BALANCEMODE]);
				pp1->anim.stop		= MV1DuplicateModel(Original[1].typestop[BALANCEMODE]);		// 立ちアニメ
				pp1->anim.run		= MV1DuplicateModel(Original[1].run);		// 走りアニメ
				pp1->anim.jump_in	= MV1DuplicateModel(Original[1].jump_in);	// ジャンプ入り始めアニメ
				pp1->anim.jump		= MV1DuplicateModel(Original[1].jump);		// ジャンプループアニメ
				pp1->anim.fall		= MV1DuplicateModel(Original[1].fall);		// ジャンプループアニメ
				pp1->anim.attack	= MV1DuplicateModel(Original[1].attack);	// 攻撃アニメ
				pp1->anim.damage	= MV1DuplicateModel(Original[1].damage);	// 被ダメージアニメ
				break;
		}
	}
	return (false);
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
	MV1SetAttachAnimTime(pp1->GetAnimation_Data().type[pp1->GetType()], pp1->GetAnim_Attach(), pp1->GetPlay_Time());

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
	MV1DetachAnim(pp1->GetAnimation_Data().type[pp1->GetType()], pp1->GetAnim_Attach());

	// アニメーションセット(切り替え)
	pp1->SetAnim_Attach(MV1AttachAnim(pp1->GetAnimation_Data().type[pp1->GetType()], 0, set_anim));
	pp1->SetAnim_Time(MV1GetAttachAnimTotalTime(pp1->GetAnimation_Data().type[pp1->GetType()], pp1->GetAnim_Attach()));

	// アニメーションして動いてもその場で動いてるような状態にする
	pp1->SetRootFlm(MV1SearchFrame(pp1->GetAnimation_Data().type[pp1->GetType()], "root"));
	MV1SetFrameUserLocalMatrix(pp1->GetAnimation_Data().type[pp1->GetType()], pp1->GetRootFlm(), MGetIdent());
	pp1->SetPlay_Time(0.0f);

	return(false);
}
/* ############################################################################################### */
/* ======================================================== +
 |						CharaChoice( )						|
 |						キャラ選択							|
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
		if (key1 & PAD_INPUT_UP || key1 & PAD_INPUT_C){
			pp1->MoveSet( pp1 );
		}
		else {
			pp1->SetAct_Mode(eCharaMove);
			pp1->SetMotion(pp1->GetAnimation_Data().run);
			ChangeAnimation(pp1, pp1->GetAnimation_Data().run);	// アニメーション切り替え
		}
	}

	if (gamemode == eScenePlay1)
		Block_HitCheck(pp1);
	if( gamemode == eScenePlay2 )
		Block_HitCheck2(pp1);

	// 移動量を加える
	pp1->SetPosition(VAdd(pp1->GetPosition(), pp1->GetSpeed()));

	// Aが△
	// Bが○
	// Cが×
	// Xが□
	// ○が押されたら
	if (key1 & PAD_INPUT_B) {
		pp1->SetAct_Mode(eCharaAttack);
		pp1->SetMotion(pp1->GetAnimation_Data().attack);
		ChangeAnimation(pp1, pp1->GetAnimation_Data().attack);	// アニメーション切り替え
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
	pp1->MoveSet( pp1 ) ;

	// ヒットチェック
	Move_HitCheck( pp1 , pp2) ;

	if (gamemode == eScenePlay1)
		Block_HitCheck(pp1);

	if (gamemode == eScenePlay2)
		Block_HitCheck2(pp1);

	// 移動量を加える
	pp1->SetPosition( VAdd( pp1->GetPosition( ) , pp1->GetSpeed( ) ) ) ;

	// ○が押されたら
	if (key1 & PAD_INPUT_B) {
		pp1->SetSpeed(VGet(0.0f, 0.0f, 0.0f));
		pp1->SetAct_Mode(eCharaAttack);
		ChangeAnimation(pp1, pp1->GetAnimation_Data().attack);	// アニメーション切り替え
	}

	// 何も押されていなければ
	if (key1 == 0) {
		pp1->SetSpeed(VGet(0.0f, 0.0f, 0.0f));
		pp1->SetAct_Mode(eCharaStop);
		pp1->SetMotion(pp1->GetAnimation_Data().stop);
		ChangeAnimation(pp1, pp1->GetAnimation_Data().stop);				// アニメーション切り替え
	}

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
	pp1->MoveSet(pp1);
	if (pp1->GetPlay_Time() > pp1->GetAnim_Time()) {
		pp1->SetSpeed(VGet(0.0f, 0.0f, 0.0f));
		pp1->SetAct_Mode(eCharaStop);
		pp1->SetMotion(pp1->GetAnimation_Data().stop);
		ChangeAnimation(pp1, pp1->GetAnimation_Data().stop);				// アニメーション切り替え
	}

	// 攻撃時の当たり判定をモデルの前方に配置
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
		ChangeAnimation(pp2, pp2->GetAnimation_Data().damage);	// アニメーション切り替え
	}
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

	// 上昇中のアニメーション
	if (pp1->GetAnim_Attach() == pp1->GetAnimation_Data().jump)
		pp1->SetMotion(pp1->GetAnimation_Data().jump);

	// y軸の速度が0を下回った時の処理
	if (pp1->GetAnim_Attach() != pp1->GetAnimation_Data().fall &&
		pp1->GetSpeed().y < 0 ) {
		ChangeAnimation(pp1, pp1->GetAnimation_Data().fall);	// アニメーション切り替え
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
 |                     　ダメージ　                         |
 |                                                          |
 + ======================================================== */
void Player::CharaDamage(CharaBase* pp1, CharaBase* pp2)
{
	pp1->AddPlay_Time(0.5f);
	pp1->SetMotion(pp1->GetAnimation_Data().damage);

	// 吹っ飛びの初速
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

	// 減速
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
		// 移動制限
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

	// 移動量を加える
	pp1->SetPosition(VAdd(pp1->GetPosition(), pp1->GetSpeed()));

	if (pp1->GetAnim_Time() < pp1->GetPlay_Time()) {
		pp1->SetFallDamageFlg(FALSE);
		pp1->SetBlowDirection(NONBLOW);
		pp1->SetSpeed(VGet(0.0f, 0.0f, 0.0f));
		pp1->SetAct_Mode(eCharaStop);
		pp1->SetMotion(pp1->GetAnimation_Data().stop);
		ChangeAnimation(pp1, pp1->GetAnimation_Data().stop);				// アニメーション切り替え
	}
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
 |						復活状態							|
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
//		pp1->SetSpeed(VGet(0, 0, 0));
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

			if (pp1->GetAct_Mode() == eCharaFall || pp1->GetAct_Mode() == eCharaDamage) {
				pp1->SetAct_Mode(eCharaStop);
				ChangeAnimation(pp1, pp1->GetAnimation_Data().stop);	// アニメーション切り替え
				pp1->SetAnim_Time(0.0f);
				pp1->SetSpeed(VGet(0.0f, 0.0f, 0.0f));
			}
		}
		else {
			pp1->SetDamageFlg(TRUE);
			pp1->SetAct_Mode(eCharaDamage);
			ChangeAnimation(pp1, pp1->GetAnimation_Data().damage);	// アニメーション切り替え
		}
	}
	else {
		if (b_damegeflg == FALSE) {
			// 宙に浮いた状態
			if (pp1->GetAct_Mode() != eCharaFall && pp1->GetAct_Mode() != eCharaDamage) { // ジャンプ状態じゃない
				pp1->SetAct_Mode(eCharaFall);
				ChangeAnimation(pp1, pp1->GetAnimation_Data().jump);
			}
		}
		else {
			pp1->SetFallDamageFlg(TRUE);
			pp1->SetDamageFlg(TRUE);
			pp1->SetAct_Mode(eCharaDamage);
			ChangeAnimation(pp1, pp1->GetAnimation_Data().damage);	// アニメーション切り替え
		}
	}
}
/* ======================================================== +
 |                    Block_HitCheck2( )                    |
 |             　     ヒットチェック2                       |
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

			// 当たった場合の処理
			if (LineBlock.HitFlag == TRUE) {
				// ポリゴンに当たったフラグを立てる
				if (pp1->GetSpeed().y > 0) {
					switch (m_block2[i].GetBlockType()) {
					case TATAMI_BLOCK:
					case BREAK_BLOCK:
					case FALL_BLOCK:
						// ブロックの底面よりプレイヤーの頭が小さい時の処理
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
							// 接触したＹ座標を保存する
							MaxY = m_block2[i].GetBlockPosition().y + BLOCK_TOP;
							if (m_block2[i].GetBlockType() == MOVE_BLOCK_X) {
								pp1->SetX_Spd(pp1->GetSpeed().x + m_block2[i].GetBlockSpeed().x);
							}
						}
						else {
							MaxY = pp1->GetPosition().y;
							if (pp1->GetSpeed().y < 0)
								HitFlag = 0;

							// 横の床への移動の制限
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
							// 接触したＹ座標を保存する
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
 |                    Revival_HitCheck( )					|
 |             　     復活時ヒットチェック					|
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

	if ((cpos.y - pp1->GetPosition().y > 2050.0f)) {
		pp1->SetAct_Mode(eCharaRevival);
		pp1->SetDirection(DOWN);
		pp1->SetRevivalTime(100);
	}

	// アクションループ
	( this->*PlayerModeTbl[act_mode] )( pp1 , pp2 ) ;

	return( false ) ;
}



