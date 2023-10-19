#include "Common.h"

void MobInit() {
	mob[0].use_flg = TRUE;													// 使用フラグセット
	mob[0].pos = VGet(1200.0f, 100.0f, 600.0f);								// 位置初期セット
	mob[0].direction = 3;
	mob[0].type = SPEEDMODE;
	mob[0].anim.model = MV1DuplicateModel(Original[0].type[SPEEDMODE]);
	mob[0].anim.stop = MV1DuplicateModel(Original[0].typestop[SPEEDMODE]);	// 立ちアニメ

	mob[1].use_flg = TRUE;													// 使用フラグセット
	mob[1].pos = VGet(2000.0f, 100.0f, 600.0f);							// 位置初期セット
	mob[1].direction = 1;
	mob[1].type = SPEEDMODE;
	mob[1].anim.model = MV1DuplicateModel(Original[1].type[SPEEDMODE]);
	mob[1].anim.stop = MV1DuplicateModel(Original[1].typestop[SPEEDMODE]);	// 立ちアニメ

	mob[2].use_flg = FALSE;													// 使用フラグセット
	mob[2].pos = VGet(0.0f, 0.0f, 0.0f);									// 位置初期セット
	mob[2].direction = 0;
	mob[2].type = BALANCEMODE;
	mob[2].anim.model = MV1DuplicateModel(Original[0].type[BALANCEMODE]);
	mob[2].anim.stop = MV1DuplicateModel(Original[0].typestop[BALANCEMODE]);	// 立ちアニメ

	mob[3].use_flg = FALSE;														// 使用フラグセット
	mob[3].pos = VGet(1600.0f, 100.0f, 1000.0f);								// 位置初期セット
	mob[3].direction = 0;
	mob[3].type = BALANCEMODE;
	mob[3].anim.model = MV1DuplicateModel(Original[1].type[BALANCEMODE]);
	mob[3].anim.stop = MV1DuplicateModel(Original[1].typestop[BALANCEMODE]);	// 立ちアニメ

	mob[4].use_flg = FALSE;														// 使用フラグセット
	mob[4].pos = VGet(800.0f, 100.0f, 1000.0f);									// 位置初期セット
	mob[4].direction = 0;
	mob[4].type = POWERMODE;
	mob[4].anim.model = MV1DuplicateModel(Original[0].type[POWERMODE]);
	mob[4].anim.stop = MV1DuplicateModel(Original[0].typestop[POWERMODE]);		// 立ちアニメ


	// モデルの回転
	MV1SetRotationXYZ(mob[0].anim.model, VGet(0.0f, 1.57f * mob[0].direction, 0.0f));
	MV1SetRotationXYZ(mob[1].anim.model, VGet(0.0f, 1.57f * mob[1].direction, 0.0f));
	// モデルの移動(配置)
	MV1SetPosition(mob[0].anim.model, mob[0].pos);
	MV1SetPosition(mob[1].anim.model, mob[1].pos);

	for (int i = 0; i < MAX_MOB; i++) {
		mob[i].motion = mob[i].anim.stop;
		// アニメーションセット
		mob[i].anim_attach = MV1AttachAnim(mob[i].anim.model, 0, mob[i].anim.stop);
		mob[i].anim_time = MV1GetAttachAnimTotalTime(mob[i].anim.model, mob[i].anim_attach);
		// アニメーションして動いてもその場で動いてるような状態にする
		mob[i].rootflm = MV1SearchFrame(mob[i].anim.model, "root");
		MV1SetFrameUserLocalMatrix(mob[i].anim.model, mob[i].rootflm, MGetIdent());
		mob[i].play_time = 0.0f;
	}
}

void MobDraw() {
	for (int i = 0; i < MAX_MOB; i++) {
		if (mob[i].use_flg == TRUE) {
			// モデルの回転
			MV1SetRotationXYZ(mob[i].anim.model, VGet(0.0f, 1.57f * mob[i].direction, 0.0f));
			// モデルの移動(配置)
			MV1SetPosition(mob[i].anim.model, mob[i].pos);

			MV1DrawModel(mob[i].anim.model);

			if (mob[i].play_time > mob[i].anim_time) {
				mob[i].play_time = 0.0f;
			}
			// アニメーション再生時間と同期させる
			MV1SetAttachAnimTime(mob[i].anim.model, mob[i].anim_attach, mob[i].play_time );
		}
	}
}



