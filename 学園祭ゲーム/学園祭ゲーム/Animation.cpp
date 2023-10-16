#include <DxLib.h>
#include "Common.h"

// ------------------------------------------------------------------------ //
//						アニメーションの初期セット							//
// ------------------------------------------------------------------------ //
void AnimationInit() {
	// -------------------------------- // 
	//		アニメーションの読み込み	//
	// -------------------------------- //
/*	if (chara_type1 == SPEEDMODE) {
		player[0].anim.stop = MV1LoadModel("..\\Data\\Ninja\\忍者_苦無_待機.mv1");			// 立ちアニメ
		player[0].anim.run = MV1LoadModel("..\\Data\\Ninja\\忍者_苦無_移動.mv1");			// 走りアニメ
		player[0].anim.jump_in = MV1LoadModel("..\\Data\\Ninja\\忍者_苦無_ジャンプ開始.mv1");	// ジャンプ入り始めアニメ
		player[0].anim.jump = MV1LoadModel("..\\Data\\Ninja\\忍者_苦無_ジャンプ中.mv1");	// ジャンプループアニメ
		player[0].anim.fall = MV1LoadModel("..\\Data\\Ninja\\忍者_苦無_落下.mv1");			// ジャンプループアニメ
		player[0].anim.attack = MV1LoadModel("..\\Data\\Ninja\\忍者_苦無_攻撃.mv1");			// 攻撃アニメ
		player[0].anim.damage = MV1LoadModel("..\\Data\\Ninja\\忍者_苦無_ダメージ.mv1");		// 被ダメージアニメ
	}*/
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
			player[0].SetAnim_Attach( MV1AttachAnim(player[0].anim.model ,0, player[0].anim.jump_in));
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



