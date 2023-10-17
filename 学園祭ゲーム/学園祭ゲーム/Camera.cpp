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

	// Xキー
	if (CheckHitKey(KEY_INPUT_X) == 1) {
		cpos.y += 48.0f;
	}

	// Zキー
	if (CheckHitKey(KEY_INPUT_Z) == 1) {
		cpos.y -= 48.0f;
	}
}


