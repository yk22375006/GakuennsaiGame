#include <DxLib.h>

#include "Common.h"

// ------------------------------------------------------------------------ //
//								�J�����̈ړ��֐�							//
// ------------------------------------------------------------------------ //
void CameraMove() {
	if (key & PAD_INPUT_5) {
		cpos.z -= 12.0f;
	}

	// ������� ���Ɉړ�
	if (key & PAD_INPUT_8) {
		cpos.z += 12.0f;
	}

	// �������� ���Ɉړ�
	if (key & PAD_INPUT_4) {
		cpos.x -= 12.0f;
	}

	// �E�����ւ̈ړ�����
	if (key & PAD_INPUT_6) {
		cpos.x += 12.0f;
	}
	// X�L�[
	if (key & PAD_INPUT_2) {
		cpos.y += 48.0f;
	}

	// Z�L�[
	if (key & PAD_INPUT_1) {
		cpos.y -= 48.0f;
	}

	if (CheckHitKey(KEY_INPUT_C)) {
		Player[0].pos.y = 1000.0f;
	}

	// �J�����̎��_����
	cpos.x;
	cpos.y;
	cpos.z;

	// �J�����̒����_����
	ctgt.x = cpos.x;
	ctgt.y = cpos.y;
	ctgt.z = cpos.z + 1000.0f;
}


