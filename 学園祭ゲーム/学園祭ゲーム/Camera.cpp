#include <DxLib.h>

#include "Common.h"

// ------------------------------------------------------------------------ //
//								�J�����̈ړ��֐�							//
// ------------------------------------------------------------------------ //
void CameraMove() {
	if (key & PAD_INPUT_5) {
		cpos.z -= 48.0f;
	}

	// ������� ���Ɉړ�
	if (key & PAD_INPUT_8) {
		cpos.z += 48.0f;
	}

	// �������� ���Ɉړ�
	if (key & PAD_INPUT_4) {
		cpos.x -= 48.0f;
	}

	// �E�����ւ̈ړ�����
	if (key & PAD_INPUT_6) {
		cpos.x += 48.0f;
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
		Player[0].pos.y = 1800.0f;
	}

	// �J�����̃X�N���[��
	cpos.y += 3.5f;

	// �J�����̒����_����
	ctgt.x = cpos.x;
	ctgt.y = cpos.y - 400.0f ;
	ctgt.z = cpos.z + 1000.0f;
}


