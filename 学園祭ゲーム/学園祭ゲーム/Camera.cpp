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

	// �������� ���Ɉړ�
	if (CheckHitKey(KEY_INPUT_A) == 1) {
		cpos.x -= 48.0f;
	}

	// �E�����ւ̈ړ�����
	if (CheckHitKey(KEY_INPUT_D) == 1) {
		cpos.x += 48.0f;
	}
	// X�L�[
	if (CheckHitKey(KEY_INPUT_X) == 1) {
		cpos.y += 48.0f;
	}

	// Z�L�[
	if (CheckHitKey(KEY_INPUT_Z) == 1) {
		cpos.y -= 48.0f;
	}
<<<<<<< HEAD
=======

	// �J�����̃X�N���[��
	cpos.y += 3.5f;

	// �J�����̒����_����
	ctgt.x = cpos.x;
	ctgt.y = cpos.y - 400.0f ;
	ctgt.z = cpos.z + 1000.0f;
>>>>>>> 学園祭/G_seika
}


