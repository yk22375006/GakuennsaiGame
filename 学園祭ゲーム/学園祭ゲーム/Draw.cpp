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
		if (cpos.y - MV1GetPosition(bg_tatami[i]).y > -1500.0f)
			MV1DrawModel(bg_tatami[i]);
	}
//	if (cpos.y - MV1GetPosition(bg_roof).y > -1500.0f)
		MV1DrawModel(bg_roof);

	blockcnt = 0;
	for (blockcnt = 0; blockcnt < MAX_BLOCK; blockcnt++) {
		if (cpos.y - m_block[blockcnt].GetBlockPosition().y > -1400.0f) {
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
		if (cpos.y - m_block[blockcnt].GetBlockPosition().y > 2450.0f)
			m_block[blockcnt].SetBlockFlag(FALSE);
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

	// 描画に使用するシャドウマップの設定を解除
	SetUseShadowMap(0, -1);
}



