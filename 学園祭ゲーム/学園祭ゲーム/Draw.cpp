#include "Common.h"

// ------------------------------------------------------------------------ //
//								描画関数									//
// ------------------------------------------------------------------------ //
void Draw() {

	// シャドウマップへの描画の準備
	ShadowMap_DrawSetup(ShadowMapHandle);
	// 描画に使用するシャドウマップを設定
	SetUseShadowMap(0, ShadowMapHandle);

	// モデルの描画 - 影の描画
	MV1DrawModel(player[0].anim.model);
	MV1DrawModel(player[1].anim.model);

	// シャドウマップへの描画を終了
	ShadowMap_DrawEnd();

	// 地面(配置)＆描画
	MV1DrawModel(skydate);
	MV1DrawModel(stagedate);
	
	for (int i = 0; i < BACKGROUNDFLOOR; i++) {
		MV1DrawModel(bg_tatami[i]);
	}

	blockcnt = 0;
	for (blockcnt = 0; blockcnt < MAX_BLOCK; blockcnt++) {
		if (m_block[blockcnt].GetBlockFlag() == TRUE) {
			switch (m_block[blockcnt].GetBlockType()) {
			case MOVE_BLOCK_X:
			case MOVE_BLOCK_Y:
			case MOVE_BLOCK_Z:
				m_block[blockcnt].BlockMove(&m_block[blockcnt]);
				break;
			}
			MV1DrawModel(m_block[blockcnt].b_model);
		}
	}

	SetLightPositionHandle(LHandle_p1, VGet(player[0].GetPosition().x, player[0].GetPosition().y + 100.0f, player[0].GetPosition().z - 500.0f)); // ライトの位置
	SetLightPositionHandle(LHandle_p2, VGet(player[1].GetPosition().x, player[1].GetPosition().y + 100.0f, player[1].GetPosition().z - 500.0f)); // ライトの位置


	// モデルの描画
	if (player[0].GetUse_Flg() == TRUE)
		MV1DrawModel(player[0].anim.model);
	if (player[1].GetUse_Flg() == TRUE)
		MV1DrawModel(player[1].anim.model);


	DrawGraph(0, 0, CharaIcon[0], TRUE);
	DrawGraph(1650, 0, CharaIcon[1], TRUE);

	wsprintf(DrawScore1, "%d", player[0].GetScore());
	wsprintf(DrawScore2, "%d", player[1].GetScore());

	SetFontSize(128);
	ChangeFont("HGS行書体");

	if (player[0].GetScore() < 10) {
		DrawString(100, 150, DrawScore1, GetColor(255, 255, 0));
	}
	else {
		DrawString(50, 150, DrawScore1, GetColor(255, 255, 0));
	}
	if (player[1].GetScore() < 10) {
		DrawString(1750, 150, DrawScore2, GetColor(255, 255, 0));
	}
	else {
		DrawString(1700, 150, DrawScore2, GetColor(255, 255, 0));
	}


/*	VECTOR AttackPosTop;
	AttackPosTop = player[0].GetPosition();
	AttackPosTop.x = player[0].GetPosition().x - cosf((player[0].GetDirection() - 1.001f) * 1.57f) * player[0].GetAttackMiddleRange();
	AttackPosTop.y = player[0].GetPosition().y + (PLAYER_SIZE_H - 100.0f);

	VECTOR AttackPosBottom;
	AttackPosBottom = player[0].GetPosition();
	AttackPosBottom.x = player[0].GetPosition().x - cosf((player[0].GetDirection() - 1.001f) * 1.57f) * player[0].GetAttackMiddleRange();
	AttackPosBottom.y = player[0].GetPosition().y +100.0f;

	VECTOR pp2_MAX_Y_Pos;
	pp2_MAX_Y_Pos = player[1].GetPosition();
	pp2_MAX_Y_Pos.y = player[1].GetPosition().y + PLAYER_SIZE_H;

	DrawCapsule3D(VAdd(AttackPosTop, player[0].GetSpeed()), VAdd(AttackPosBottom, player[0].GetSpeed()),
		player[0].GetAttackRange(),
		8, GetColor(255, 255, 0), GetColor(255, 255, 0), FALSE);

	DrawCapsule3D(VAdd(pp2_MAX_Y_Pos, player[1].GetSpeed()), VAdd(player[1].GetPosition(), player[1].GetSpeed()),
		player[1].GetWidth() / 2,
		8, GetColor(0, 0, 255), GetColor(0, 0, 255), FALSE);
*/
	// 描画に使用するシャドウマップの設定を解除
	SetUseShadowMap(0, -1);
}



