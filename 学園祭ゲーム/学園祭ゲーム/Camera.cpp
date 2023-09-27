#include <DxLib.h>

#include "Common.h"

// ------------------------------------------------------------------------ //
//								カメラの移動関数							//
// ------------------------------------------------------------------------ //
void CameraMove() {
	if (key & PAD_INPUT_5) {
		cpos.z -= 48.0f;
	}

	// 上を押下 奥に移動
	if (key & PAD_INPUT_8) {
		cpos.z += 48.0f;
	}

	// 左を押下 左に移動
	if (key & PAD_INPUT_4) {
		cpos.x -= 48.0f;
	}

	// 右方向への移動処理
	if (key & PAD_INPUT_6) {
		cpos.x += 48.0f;
	}
	// Xキー
	if (key & PAD_INPUT_2) {
		cpos.y += 48.0f;
	}

	// Zキー
	if (key & PAD_INPUT_1) {
		cpos.y -= 48.0f;
	}

	if (CheckHitKey(KEY_INPUT_C)) {
		Player[0].pos.y = 1800.0f;
	}

	// カメラのスクロール
	cpos.y += 3.5f;

	// カメラの注視点操作
	ctgt.x = cpos.x;
	ctgt.y = cpos.y - 400.0f ;
	ctgt.z = cpos.z + 1000.0f;
}


