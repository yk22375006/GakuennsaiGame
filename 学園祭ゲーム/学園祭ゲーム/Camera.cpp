#include <DxLib.h>

#include "Common.h"

// ------------------------------------------------------------------------ //
//								カメラの移動関数							//
// ------------------------------------------------------------------------ //
void CameraMove() {
	if (CheckHitKey(KEY_INPUT_S) == 1) {
		cpos.z -= 48.0f;
	}

	// 上を押下 奥に移動
	if (CheckHitKey(KEY_INPUT_W) == 1) {
		cpos.z += 48.0f;
	}

	// 左を押下 左に移動
	if (CheckHitKey(KEY_INPUT_A) == 1) {
		cpos.x -= 48.0f;
	}

	// 右方向への移動処理
	if (CheckHitKey(KEY_INPUT_D) == 1) {
		cpos.x += 48.0f;
	}
	// Xキー
	if (CheckHitKey(KEY_INPUT_X) == 1) {
		cpos.y += 48.0f;
	}

	// Zキー
	if (CheckHitKey(KEY_INPUT_Z) == 1) {
		cpos.y -= 48.0f;
	}

	if (CheckHitKey(KEY_INPUT_T) == 1 && Lightlimit == 0) {
		Atten0 += 0.01f;
		Lightlimit = 50;
	}

	if (CheckHitKey(KEY_INPUT_G) == 1 && Lightlimit == 0) {
		Atten0 -= 0.01f;
		Lightlimit = 50;
	}

	if (CheckHitKey(KEY_INPUT_Y) == 1 && Lightlimit == 0) {
		Atten1 += 0.0001f;
		Lightlimit = 50;
	}

	if (CheckHitKey(KEY_INPUT_H) == 1 && Lightlimit == 0) {
		Atten1 -= 0.0001f;
		Lightlimit = 50;
	}

	if (CheckHitKey(KEY_INPUT_U) == 1 && Lightlimit == 0) {
		Atten2 += 0.000001f;
		Lightlimit = 50;
	}

	if (CheckHitKey(KEY_INPUT_J) == 1 && Lightlimit == 0) {
		Atten2 -= 0.000001f;
		Lightlimit = 50;
	}

	if (CheckHitKey(KEY_INPUT_I) == 1 && Lightlimit == 0) {
		OutAngle += 1.0f;
		Lightlimit = 50;
	}

	if (CheckHitKey(KEY_INPUT_K) == 1 && Lightlimit == 0) {
		OutAngle -= 1.0f;
		Lightlimit = 50;
	}

	if (CheckHitKey(KEY_INPUT_O) == 1 && Lightlimit == 0) {
		InAngle += 1.0f;
		Lightlimit = 50;
	}

	if (CheckHitKey(KEY_INPUT_L) == 1 && Lightlimit == 0) {
		InAngle -= 1.0f;
		Lightlimit = 50;
	}

	if (Lightlimit > 0) {
		Lightlimit--;
	}
	if (Lightlimit < 0) {
		Lightlimit = 0;
	}
	if (CheckHitKey(KEY_INPUT_SPACE) == 1 && Lightlimit == 0) {
		printf("Atten0   : %10.8f\n", Atten0);
		printf("Atten1   : %10.8f\n", Atten1);
		printf("Atten2   : %10.8f\n", Atten2);
		printf("OutAngle : %10.8f\n", OutAngle);
		printf("InAngle  : %10.8f\n", InAngle);
		printf("DX_PI_F / OutAngle : %10.8f\n", DX_PI_F / OutAngle);
		printf("DX_PI_F / InAngle  : %10.8f\n", DX_PI_F / InAngle);
		printf("-------------------------------------------------------------------\n");
		Lightlimit = 50;
		// OutAngle : 0.54352820
		// InAngle: 0.57119870
	}
	// カメラのスクロール
//	cpos.y += 3.5f;

	// カメラの注視点操作
	ctgt.x = cpos.x;
	ctgt.y = cpos.y - 400.0f ;
	ctgt.z = cpos.z + 1000.0f;
}


