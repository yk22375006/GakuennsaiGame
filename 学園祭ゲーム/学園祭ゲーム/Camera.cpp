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
<<<<<<< HEAD
=======

	// カメラのスクロール
	cpos.y += 3.5f;

	// カメラの注視点操作
	ctgt.x = cpos.x;
	ctgt.y = cpos.y - 400.0f ;
	ctgt.z = cpos.z + 1000.0f;
>>>>>>> 蟄ｦ蝨堤･ｭ/G_seika
}


