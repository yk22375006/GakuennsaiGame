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

	DrawTriangle3D(PolyCharaHitField[0], PolyCharaHitField[1], PolyCharaHitField[2],
		GetColor(255, 0, 0), TRUE);

	// ���f���̕`��
	MV1DrawModel(player[0].anim.model);
	MV1DrawModel(player[1].anim.model);

	// �`��Ɏg�p����V���h�E�}�b�v�̐ݒ������
	SetUseShadowMap(0, -1);

}



