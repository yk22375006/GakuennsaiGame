#include <DxLib.h>
#include "Common.h"

// ------------------------------------------------------------------------ //
//						�v���C���[�̏��ւ̃q�b�g�`�F�b�N					//
// ------------------------------------------------------------------------ //
int FloorSearch() {
	float MaxY_poly;
	// ���|���S���ɓ����������ǂ����̃t���O��|���Ă���
	HitFlag = 0;
	// ��ԍ������|���S���ɂԂ���ׂ̔���p�ϐ���������
	MaxY = 0.0f;
	MaxY_poly = 0.0f;

	// ���|���S���̐������J��Ԃ�
	for (int i = 0; i < FloorNum; i++) {
		// i�Ԗڂ̏��|���S���̃A�h���X�����|���S���|�C���^�z�񂩂�擾
		Poly = Floor[i];

		VECTOR cal_pos1 = VAdd(Player[0].pos, VGet(0.0f, PC_HEIGHT, 0.0f));
		VECTOR cal_pos2 = VAdd(Player[0].pos, VGet(0.0f, -25.0f, 0.0f));
		if (Player[0].mode == JUMPIN || Player[0].mode == JUMPLOOP) {
			cal_pos2 = VAdd(Player[0].pos, VGet(0.0f, 5.0f, 0.0f));
		}
		// �����Ă���ꍇ�͓��̐悩�炻�������Ⴂ�ʒu�̊Ԃœ������Ă��邩�𔻒�( �X�΂ŗ�����ԂɈڍs���Ă��܂�Ȃ��� )
		LineRes = HitCheck_Line_Triangle(cal_pos1, cal_pos2, Poly->Position[0], Poly->Position[1], Poly->Position[2]);

		// �������Ă��Ȃ������牽�����Ȃ�
		if (LineRes.HitFlag == TRUE) {
			PolyCharaHitField[0] = Poly->Position[0];
			PolyCharaHitField[1] = Poly->Position[1];
			PolyCharaHitField[2] = Poly->Position[2];
		}
		else {
			continue;
		}

		// ���ɓ��������|���S��������A�����܂Ō��o�������|���S�����Ⴂ�ꍇ�͉������Ȃ�
		if (HitFlag == 1 && MaxY > LineRes.Position.y) {
			continue;
		}

		// �|���S���ɓ��������t���O�𗧂Ă�
		HitFlag = 1;

		// �ڐG�����x���W��ۑ�����
		MaxY = LineRes.Position.y;
		MaxY_poly = Poly->Position[1].y;
	}


	return HitFlag;
}

// ------------------------------------------------------------------------ //
//						�G�l�~�[�̏��ւ̃q�b�g�`�F�b�N						//
// ------------------------------------------------------------------------ //
void E1_FloorSearch() {
	float E1_MaxY_poly;
	// ���|���S���ɓ����������ǂ����̃t���O��|���Ă���
	E1_HitFlag = 0;
	// ��ԍ������|���S���ɂԂ���ׂ̔���p�ϐ���������
	E1_MaxY = 0.0f;
	E1_MaxY_poly = 0.0f;

	// ���|���S���̐������J��Ԃ�
	for (int i = 0; i < FloorNum; i++) {
		// i�Ԗڂ̏��|���S���̃A�h���X�����|���S���|�C���^�z�񂩂�擾
		Poly = Floor[i];

		VECTOR cal_pos1 = VAdd(Player[1].pos, VGet(0.0f, PC_HEIGHT, 0.0f));
		VECTOR cal_pos2 = VAdd(Player[1].pos, VGet(0.0f, -25.0f, 0.0f));
		if (Player[1].mode == JUMPIN || Player[1].mode == JUMPLOOP) {
			cal_pos2 = VAdd(Player[1].pos, VGet(0.0f, 5.0f, 0.0f));
		}
		// �����Ă���ꍇ�͓��̐悩�炻�������Ⴂ�ʒu�̊Ԃœ������Ă��邩�𔻒�( �X�΂ŗ�����ԂɈڍs���Ă��܂�Ȃ��� )
		E1_LineRes = HitCheck_Line_Triangle(cal_pos1, cal_pos2, Poly->Position[0], Poly->Position[1], Poly->Position[2]);

		// �������Ă��Ȃ������牽�����Ȃ�
		if (E1_LineRes.HitFlag == TRUE) {
			PolyCharaHitField[0] = Poly->Position[0];
			PolyCharaHitField[1] = Poly->Position[1];
			PolyCharaHitField[2] = Poly->Position[2];
		}
		else {
			continue;
		}

		// ���ɓ��������|���S��������A�����܂Ō��o�������|���S�����Ⴂ�ꍇ�͉������Ȃ�
		if (E1_HitFlag == 1 && E1_MaxY > E1_LineRes.Position.y) {
			continue;
		}

		// �|���S���ɓ��������t���O�𗧂Ă�
		E1_HitFlag = 1;

		// �ڐG�����x���W��ۑ�����
		E1_MaxY = E1_LineRes.Position.y;
		E1_MaxY_poly = Poly->Position[1].y;
	}
}

int CollisionBlock() {
	VECTOR cal_pos1 = VAdd(Player[0].pos, VGet(0.0f, PC_HEIGHT, 0.0f));
	VECTOR cal_pos2 = VAdd(Player[0].pos, VGet(0.0f, -25.0f, 0.0f));

//	for (int i = 0; i < 100; i++) {
		LineBlock = HitCheck_Line_Cube(cal_pos1, cal_pos2,
			VGet(m_block[10].GetBlockPosition().x - 100.0f, m_block[10].GetBlockPosition().y, m_block[10].GetBlockPosition().z - 100.0f),
			VGet(m_block[10].GetBlockTopPosition().x + 100.0f, m_block[10].GetBlockTopPosition().y, m_block[10].GetBlockTopPosition().z + 100.0f));

		// �������Ă��Ȃ������牽�����Ȃ�
		if (LineBlock.HitFlag == TRUE) {
			// �|���S���ɓ��������t���O�𗧂Ă�
			HitFlag = 1;
			printf("�u���b�N�ɓ�������");

			// �ڐG�����x���W��ۑ�����
			MaxY = m_block[10].GetBlockTopPosition().y;
		}
//		if (m_block[i].GetBlockFlag() == FALSE) {
//			break;
//		}
//	}

	return HitFlag;
}


