#include <DxLib.h>
#include "Common.h"

// ------------------------------------------------------------------------ //
//							�v���C���[�̏����Z�b�g							//
// ------------------------------------------------------------------------ //
void PlayerInit() {
	// ---------------------------- // 
	//		�L�������Z�b�g		//
	// ---------------------------- //
	if (CHOICESTAGE == 1) {
		Player[0].pos = VGet(200.0f, 700.0f, 0.0f);		 // ����
	}
	else {
		Player[0].pos = VGet(500.0f, 800.0f, 2800.0f); // ���A
	}
	Player[0].mode = STAND;
	Player[0].direction = DOWN;
	Player[0].charahitinfo.Height = PC_HEIGHT;
	Player[0].charahitinfo.Width = PC_WIDTH;
	Player[0].charahitinfo.CenterPosition = Player[0].pos;
	Player[0].move = VGet(0.0f, 0.0f, 0.0f);

	// ---------------------------- // 
	//		�L�������f���Z�b�g		//
	// ---------------------------^ // 
	Player[0].model = MV1LoadModel("..\\Data\\Ninja\\�E��_sub.mv1");
	Player[0].attachidx = MV1AttachAnim(Player[0].model, 0, plyanim_nutral);
	Player[0].anim_totaltime = MV1GetAttachAnimTotalTime(Player[0].model, Player[0].attachidx);
	// �A�j���[�V�������ē����Ă����̏�œ����Ă�悤�ȏ��
	Player[0].rootflm = MV1SearchFrame(Player[0].model, "root");
	MV1SetFrameUserLocalMatrix(Player[0].model, Player[0].rootflm, MGetIdent());
	Player[0].playtime = 0.0f;
}

// ------------------------------------------------------------------------ //
//							�v���C���[�̈ړ��֐�							//
// ------------------------------------------------------------------------ //
void PlayerMove() {
	key = GetJoypadInputState(DX_INPUT_KEY_PAD1);
	// �������� ��O�Ɉړ�
	if (key & PAD_INPUT_DOWN) {
		Player[0].move.x = 0.0f;
		Player[0].move.z = -12.0f;
		Player[0].direction = DOWN;
	}

	// ������� ���Ɉړ�
	if (key & PAD_INPUT_UP) {
		Player[0].move.x = 0.0f;
		Player[0].move.z = +12.0f;
		Player[0].direction = UP;
	}

	// �������� ���Ɉړ�
	if (key & PAD_INPUT_LEFT) {
		Player[0].move.x = -12.0f;
		Player[0].move.z = 0.0f;
		Player[0].direction = LEFT;
		// �������� ��O�Ɉړ�
		if (key & PAD_INPUT_DOWN) {
			Player[0].move.z = -12.0f;
			Player[0].direction = 0.5f;
		}
		// ������� ���Ɉړ�
		if (key & PAD_INPUT_UP) {
			Player[0].move.z = +12.0f;
			Player[0].direction = 1.5f;
		}
	}

	// �E�����ւ̈ړ�����
	if (key & PAD_INPUT_RIGHT) {
		Player[0].move.x = +12.0f;
		Player[0].move.z = 0.0f;
		Player[0].direction = RIGHT;
		// �������� ��O�Ɉړ�
		if (key & PAD_INPUT_DOWN) {
			Player[0].move.z = -12.0f;
			Player[0].direction = 3.5f;
		}
		// ������� ���Ɉړ�
		if (key & PAD_INPUT_UP) {
			Player[0].move.z = +12.0f;
			Player[0].direction = 2.5f;
		}
	}

	// �U���{�^�� D�L�[
/*	if (key & PAD_INPUT_6) {
		if (Player[0].mode == RUN) {
			if ((Player[0].direction >= 0) & (Player[0].direction < 1)) {
				Player[0].move.z += (Player[0].direction - 1) * Player[0]_ATTACK_SPEED;
				Player[0].move.x += (-Player[0].direction) * Player[0]_ATTACK_SPEED;
			}
			else if ((Player[0].direction >= 1) & (Player[0].direction < 2)) {
				Player[0].move.z += (Player[0].direction - 1) * Player[0]_ATTACK_SPEED;
				Player[0].move.x += (Player[0].direction - 2) * Player[0]_ATTACK_SPEED;
			}
			else if ((Player[0].direction >= 2) & (Player[0].direction < 3)) {
				Player[0].move.z += (3 - Player[0].direction) * Player[0]_ATTACK_SPEED;
				Player[0].move.x += (Player[0].direction - 2) * Player[0]_ATTACK_SPEED;
			}
			else if ((Player[0].direction >= 3) & (Player[0].direction < 4)) {
				Player[0].move.z += (3 - Player[0].direction) * Player[0]_ATTACK_SPEED;
				Player[0].move.x += (4 - Player[0].direction) * Player[0]_ATTACK_SPEED;
			}
		}
		AnimationPlayer[0](ATTACK);
		Player[0].playtime = 0.0f;
		MV1SetAttachAnimTime(Player[0].model, Player[0].attachidx, Player[0].playtime);
	}
*/
	if (CheckHitKey(KEY_INPUT_SPACE) == 1) {
		Player[0].pos.y += 30.0f;
		Player[0].move.y = 40.0f;
	}
	if (CheckHitKey(KEY_INPUT_LSHIFT) == 1) {
		Player[0].move.x *= 2.0f;
		Player[0].move.z *= 2.0f;
	}

	if (Player[0].pos.x < -5300.0f) {
		if (Player[0].move.x < 0.0)
			Player[0].move.x = 0.0f;
	}
	if (Player[0].pos.x > 6150.0f) {
		if (Player[0].move.x > 0.0)
			Player[0].move.x = 0.0f;
	}
	if (Player[0].pos.z > 4000.0f) {
		if (Player[0].move.z > 0)
			Player[0].move.z = 0.0f;
	}
	if (Player[0].pos.z < -6640.0f) {
		if (Player[0].move.z < 0)
			Player[0].move.z = 0.0f;
	}
}



