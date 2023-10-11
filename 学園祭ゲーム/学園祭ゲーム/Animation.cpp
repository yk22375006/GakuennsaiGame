#include <DxLib.h>
#include "Common.h"

// ------------------------------------------------------------------------ //
//						アニメーションの初期セット							//
// ------------------------------------------------------------------------ //
void AnimationInit() {
	// -------------------------------- // 
	//		アニメーションの読み込み	//
	// -------------------------------- //
	player[0].anim.stop = MV1LoadModel("..\\Data\\Ninja\\忍者_苦無_待機.mv1");		// 立ちアニメ
	player[0].anim.run = MV1LoadModel("..\\Data\\Ninja\\忍者_苦無_移動.mv1");		// 走りアニメ	
	player[0].anim.jimp_in = MV1LoadModel("..\\Data\\Player\\Anim_Jump_In.mv1");	// ジャンプ入り始めアニメ
	player[0].anim.jump = MV1LoadModel("..\\Data\\Player\\Anim_Jump_Loop.mv1");		// ジャンプループアニメ
	player[0].anim.jump_out = MV1LoadModel("..\\Data\\Player\\Anim_Jump_Out.mv1");	// ジャンプ着地アニメ
	player[0].anim.attack = MV1LoadModel("..\\Data\\Player\\Anim_Attack1.mv1");		// 攻撃アニメ
}

// ------------------------------------------------------------------------ //
//						プレイヤーのアニメーション							//
// ------------------------------------------------------------------------ //
void AnimationPlayer( int Animation ) {
	MV1DetachAnim(player[0].anim.model, player[0].GetAnim_Attach());
	switch (Animation) {
		// 立ち状態の処理
		case STAND:
			player[0].SetAnim_Attach(MV1AttachAnim(player[0].anim.model, 0, player[0].anim.stop));
			player[0].SetAct_Mode(STAND) ;
			break;

		//走り状態の処理
		case RUN:
			player[0].SetAnim_Attach( MV1AttachAnim(player[0].anim.model, 0, player[0].anim.run));
			player[0].SetAct_Mode(RUN) ;
			break;

		// ジャンプ開始時の処理
		case JUMPIN :
			player[0].SetAnim_Attach( MV1AttachAnim(player[0].anim.model ,0, player[0].anim.jimp_in));
			player[0].SetAct_Mode(JUMPIN) ;
			break;

		// ジャンプ中の処理
		case JUMPLOOP :
			player[0].SetAnim_Attach( MV1AttachAnim(player[0].anim.model, 0, player[0].anim.jump));
			player[0].SetAct_Mode(JUMPLOOP) ;
			break;

		// ジャンプ終了時の処理
		case JUMPOUT :
			player[0].SetAnim_Attach( MV1AttachAnim(player[0].anim.model, 0, player[0].anim.jump_out));
			player[0].SetAct_Mode(JUMPOUT) ;
			break;

		// 攻撃時の処理
		case ATTACK :
			player[0].SetAnim_Attach( MV1AttachAnim(player[0].anim.model, 0, player[0].anim.attack));
			player[0].SetAct_Mode(ATTACK);
			break;
	}
	player[0].SetAnim_Time( MV1GetAttachAnimTotalTime(player[0].anim.model, player[0].GetAnim_Attach()));
}

// ------------------------------------------------------------------------ //
//						エネミーのアニメーション							//
// ------------------------------------------------------------------------ //
void AnimationEnemy(int Animation) {
/*
	MV1DetachAnim(player[1].model, player[1].attachidx);
	switch (Animation) {
		// 立ち状態の処理
		case E_STAND:
			player[1].attachidx = MV1AttachAnim(player[1].model, 0, gobanim_ntural);
			player[1].mode = E_STAND;
			break;

		// ダメージを負う開始時の処理
		case E_BLOWIN :
			player[1].attachidx = MV1AttachAnim(player[1].model, 0, gobanim_blowin);
			player[1].mode = E_BLOWIN;
			break;


		// ダメージ中の処理
		case E_BLOWLOOP :
			player[1].attachidx = MV1AttachAnim(player[1].model, 0, gobanim_blowloop);
			player[1].mode = E_BLOWLOOP;
			break;

		// ダメージ終了時の処理
		case E_BLOWOUT :
			player[1].attachidx = MV1AttachAnim(player[1].model, 0, gobanim_blowout);
			player[1].mode = E_BLOWOUT;
			break;
	}
	player[1].anim_totaltime = MV1GetAttachAnimTotalTime(player[0].model, player[0].attachidx);
*/
}



