#include <DxLib.h>

#include "Common.h"

// ------------------------------------------------------------------------ //
//								�J�����̈ړ��֐�							//
// ------------------------------------------------------------------------ //
void CameraMove() {
	if (CheckHitKey(KEY_INPUT_S) == 1) {
		cpos.z -= 48.0f;
	}

	// ������� ���Ɉړ�
	if (CheckHitKey(KEY_INPUT_W) == 1) {
		cpos.z += 48.0f;
	}

	// X�L�[
	if (CheckHitKey(KEY_INPUT_X) == 1) {
		cpos.y += 48.0f;
	}

	// Z�L�[
	if (CheckHitKey(KEY_INPUT_Z) == 1) {
		cpos.y -= 48.0f;
	}

	// �J�����̃X�N���[��
	cpos.y += 3.5f;

	// �J�����̒����_����
	ctgt.x = cpos.x;
	ctgt.y = cpos.y - 200.0f;
	ctgt.z = cpos.z + 1000.0f;
//	ctgt.y = cpos.y - 200.0f ;
//	ctgt.z = cpos.z + 600.0f;
}


