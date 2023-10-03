#include <DxLib.h>
#include "Common.h"

// ------------------------------------------------------------------------ //
//								描画関数									//
// ------------------------------------------------------------------------ //
void Draw() {
	// シャドウマップへの描画の準備
	ShadowMap_DrawSetup(ShadowMapHandle);

	// モデルの描画 - 影の描画
	MV1DrawModel(player[0].anim.model);
	MV1DrawModel(player[1].anim.model);

	// シャドウマップへの描画を終了
	ShadowMap_DrawEnd();

	// 描画に使用するシャドウマップを設定
	SetUseShadowMap(0, ShadowMapHandle);
	// 地面(配置)＆描画
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
//	C_DirectionX += 1.0f* (DX_PI_F / 180.0f);
//	SetLightDirectionHandle(LHandle_p1, VGet(C_DirectionX, C_DirectionY, C_DirectionZ));
	SetLightPositionHandle(LHandle_p1, VGet(player[0].GetPosition().x, player[0].GetPosition().y + 100.0f, player[0].GetPosition().z - 500.0f)); // ライトの位置
	SetLightPositionHandle(LHandle_p2, VGet(player[1].GetPosition().x, player[1].GetPosition().y + 100.0f, player[1].GetPosition().z - 500.0f)); // ライトの位置
//	SetLightDirectionHandle(LHandle_p1, VGet(ctgt.x = cpos.x , ctgt.y = cpos.y - 400   , ctgt.z = cpos.z ));  // ライトの方向
//	SetLightAngleHandle(LHandle_p1, 0.78f, 0.5f);


	// モデルの描画
	MV1DrawModel(player[0].anim.model);
	MV1DrawModel(player[1].anim.model);

	// 描画に使用するシャドウマップの設定を解除
	SetUseShadowMap(0, -1);

}



