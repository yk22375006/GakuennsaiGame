#include <DxLib.h>
#include "Common.h"

// ------------------------------------------------------------------------ //
//								�`��֐�									//
// ------------------------------------------------------------------------ //
void Draw() {
	// �V���h�E�}�b�v�ւ̕`��̏���
	ShadowMap_DrawSetup(ShadowMapHandle);

	// ���f���̕`�� - �e�̕`��
	MV1DrawModel(player[0].anim.model);
	MV1DrawModel(player[1].anim.model);

	// �V���h�E�}�b�v�ւ̕`����I��
	ShadowMap_DrawEnd();

	// �`��Ɏg�p����V���h�E�}�b�v��ݒ�
	SetUseShadowMap(0, ShadowMapHandle);

	// �n��(�z�u)���`��
	MV1DrawModel(skydate);
	MV1DrawModel(stagedate);
	for (int i = 0; i < BACKGROUNDFLOOR; i++) {
		MV1DrawModel(bg_tatami[i]);
	}

	blockcnt = 0;
	for (blockcnt = 0; blockcnt < MAX_BLOCK; blockcnt++) {
		if (m_block[blockcnt].GetBlockFlag() == TRUE) {
			MV1DrawModel(m_block[blockcnt].b_model);
		}
	}

	SetLightRangeAttenHandle(LHandle_p1, Range, Atten0, Atten1, Atten2);
	SetLightAngleHandle(LHandle_p1, 0.24582103f, 6.28318548f);
	SetLightPositionHandle(LHandle_p1, VGet(player[0].GetPosition().x, player[0].GetPosition().y + 100.0f, player[0].GetPosition().z - 500.0f)); // ���C�g�̈ʒu
	SetLightPositionHandle(LHandle_p2, VGet(player[1].GetPosition().x, player[1].GetPosition().y + 100.0f, player[1].GetPosition().z - 500.0f)); // ���C�g�̈ʒu
//	SetLightDirectionHandle(LHandle_p1, VGet(ctgt.x = cpos.x , ctgt.y = cpos.y - 400   , ctgt.z = cpos.z ));  // ���C�g�̕���
//	SetLightAngleHandle(LHandle_p1, 0.78f, 0.5f);


	// ���f���̕`��
	MV1DrawModel(player[0].anim.model);
	MV1DrawModel(player[1].anim.model);

	// �`��Ɏg�p����V���h�E�}�b�v�̐ݒ������
	SetUseShadowMap(0, -1);

}



