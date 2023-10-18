#include "Common.h"

void MobInit() {
	mob[0].use_flg = TRUE;													// 使用フラグセット
	mob[0].pos = VGet(800.0f, 100.0f, 1000.0f);								// 位置初期セット
	mob[0].direction = 0;
	mob[0].type = SPEEDMODE;
	mob[0].anim.model = MV1DuplicateModel(Original[0].type[SPEEDMODE]);
	mob[0].anim.stop = MV1DuplicateModel(Original[0].typestop[SPEEDMODE]);	// 立ちアニメ

	mob[1].use_flg = TRUE;													// 使用フラグセット
	mob[1].pos = VGet(1600.0f, 100.0f, 1000.0f);								// 位置初期セット
	mob[1].direction = 0;
	mob[1].type = SPEEDMODE;
	mob[1].anim.model = MV1DuplicateModel(Original[1].type[SPEEDMODE]);
	mob[1].anim.stop = MV1DuplicateModel(Original[1].typestop[SPEEDMODE]);	// 立ちアニメ

	mob[2].use_flg = FALSE;													// 使用フラグセット
	mob[2].pos = VGet(800.0f, 100.0f, 1000.0f);								// 位置初期セット
	mob[2].direction = 0;
	mob[2].type = BALANCEMODE;
	mob[2].anim.model = MV1DuplicateModel(Original[0].type[BALANCEMODE]);
	mob[2].anim.stop = MV1DuplicateModel(Original[0].typestop[BALANCEMODE]);	// 立ちアニメ

	mob[3].use_flg = FALSE;													// 使用フラグセット
	mob[3].pos = VGet(1600.0f, 100.0f, 1000.0f);								// 位置初期セット
	mob[3].direction = 0;
	mob[3].type = BALANCEMODE;
	mob[3].anim.model = MV1DuplicateModel(Original[1].type[BALANCEMODE]);
	mob[3].anim.stop = MV1DuplicateModel(Original[1].typestop[BALANCEMODE]);	// 立ちアニメ

	mob[4].use_flg = FALSE;													// 使用フラグセット
	mob[4].pos = VGet(800.0f, 100.0f, 1000.0f);								// 位置初期セット
	mob[4].direction = 0;
	mob[4].type = POWERMODE;
	mob[4].anim.model = MV1DuplicateModel(Original[0].type[POWERMODE]);
	mob[4].anim.stop = MV1DuplicateModel(Original[0].typestop[POWERMODE]);	// 立ちアニメ


	// モデルの回転
	MV1SetRotationXYZ(mob[0].anim.model, VGet(0.0f, 1.57f * mob[0].direction, 0.0f));
	MV1SetRotationXYZ(mob[1].anim.model, VGet(0.0f, 1.57f * mob[1].direction, 0.0f));
	// モデルの移動(配置)
	MV1SetPosition(mob[0].anim.model, mob[0].pos);
	MV1SetPosition(mob[1].anim.model, mob[1].pos);

}

void MobDraw() {

	MV1SetRotationXYZ(mob[0].anim.model, VGet(0.0f, 1.57f * mob[0].direction, 0.0f));
	// モデルの移動(配置)
	MV1SetPosition(mob[0].anim.model, mob[0].pos);

	MV1DrawModel(mob[0].anim.model);
	for (int i = 1; i < MAX_MOB; i++) {
		if (mob[i].use_flg == TRUE) {
			// モデルの回転
			MV1SetRotationXYZ(mob[i].anim.model, VGet(0.0f, 1.57f * mob[i].direction, 0.0f));
			// モデルの移動(配置)
			MV1SetPosition(mob[i].anim.model, mob[i].pos);

			MV1DrawModel(mob[i].anim.model);
		}
	}
}



