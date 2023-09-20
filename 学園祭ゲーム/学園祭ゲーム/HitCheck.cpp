#include <DxLib.h>
#include "Common.h"

// ------------------------------------------------------------------------ //
//						プレイヤーの床へのヒットチェック					//
// ------------------------------------------------------------------------ //
int FloorSearch() {
	float MaxY_poly;
	// 床ポリゴンに当たったかどうかのフラグを倒しておく
	HitFlag = 0;
	// 一番高い床ポリゴンにぶつける為の判定用変数を初期化
	MaxY = 0.0f;
	MaxY_poly = 0.0f;

	// 床ポリゴンの数だけ繰り返し
	for (int i = 0; i < FloorNum; i++) {
		// i番目の床ポリゴンのアドレスを床ポリゴンポインタ配列から取得
		Poly = Floor[i];

		VECTOR cal_pos1 = VAdd(Player[0].pos, VGet(0.0f, PC_HEIGHT, 0.0f));
		VECTOR cal_pos2 = VAdd(Player[0].pos, VGet(0.0f, -25.0f, 0.0f));
		if (Player[0].mode == JUMPIN || Player[0].mode == JUMPLOOP) {
			cal_pos2 = VAdd(Player[0].pos, VGet(0.0f, 5.0f, 0.0f));
		}
		// 走っている場合は頭の先からそこそこ低い位置の間で当たっているかを判定( 傾斜で落下状態に移行してしまわない為 )
		LineRes = HitCheck_Line_Triangle(cal_pos1, cal_pos2, Poly->Position[0], Poly->Position[1], Poly->Position[2]);

		// 当たっていなかったら何もしない
		if (LineRes.HitFlag == TRUE) {
			PolyCharaHitField[0] = Poly->Position[0];
			PolyCharaHitField[1] = Poly->Position[1];
			PolyCharaHitField[2] = Poly->Position[2];
		}
		else {
			continue;
		}

		// 既に当たったポリゴンがあり、且つ今まで検出した床ポリゴンより低い場合は何もしない
		if (HitFlag == 1 && MaxY > LineRes.Position.y) {
			continue;
		}

		// ポリゴンに当たったフラグを立てる
		HitFlag = 1;

		// 接触したＹ座標を保存する
		MaxY = LineRes.Position.y;
		MaxY_poly = Poly->Position[1].y;
	}


	return HitFlag;
}

// ------------------------------------------------------------------------ //
//						エネミーの床へのヒットチェック						//
// ------------------------------------------------------------------------ //
void E1_FloorSearch() {
	float E1_MaxY_poly;
	// 床ポリゴンに当たったかどうかのフラグを倒しておく
	E1_HitFlag = 0;
	// 一番高い床ポリゴンにぶつける為の判定用変数を初期化
	E1_MaxY = 0.0f;
	E1_MaxY_poly = 0.0f;

	// 床ポリゴンの数だけ繰り返し
	for (int i = 0; i < FloorNum; i++) {
		// i番目の床ポリゴンのアドレスを床ポリゴンポインタ配列から取得
		Poly = Floor[i];

		VECTOR cal_pos1 = VAdd(Player[1].pos, VGet(0.0f, PC_HEIGHT, 0.0f));
		VECTOR cal_pos2 = VAdd(Player[1].pos, VGet(0.0f, -25.0f, 0.0f));
		if (Player[1].mode == JUMPIN || Player[1].mode == JUMPLOOP) {
			cal_pos2 = VAdd(Player[1].pos, VGet(0.0f, 5.0f, 0.0f));
		}
		// 走っている場合は頭の先からそこそこ低い位置の間で当たっているかを判定( 傾斜で落下状態に移行してしまわない為 )
		E1_LineRes = HitCheck_Line_Triangle(cal_pos1, cal_pos2, Poly->Position[0], Poly->Position[1], Poly->Position[2]);

		// 当たっていなかったら何もしない
		if (E1_LineRes.HitFlag == TRUE) {
			PolyCharaHitField[0] = Poly->Position[0];
			PolyCharaHitField[1] = Poly->Position[1];
			PolyCharaHitField[2] = Poly->Position[2];
		}
		else {
			continue;
		}

		// 既に当たったポリゴンがあり、且つ今まで検出した床ポリゴンより低い場合は何もしない
		if (E1_HitFlag == 1 && E1_MaxY > E1_LineRes.Position.y) {
			continue;
		}

		// ポリゴンに当たったフラグを立てる
		E1_HitFlag = 1;

		// 接触したＹ座標を保存する
		E1_MaxY = E1_LineRes.Position.y;
		E1_MaxY_poly = Poly->Position[1].y;
	}
}

int CollisionBlock() {
	HitFlag = 0;
	VECTOR cal_pos1 = VAdd(Player[0].pos, VGet(0.0f, PC_HEIGHT, 0.0f));
	VECTOR cal_pos2 = VAdd(Player[0].pos, VGet(0.0f, -10.0f, 0.0f));

	for (int i = 0; i < MAX_BLOCK; i++) {
		if (m_block[i].GetBlockFlag() == TRUE) {
			LineBlock = HitCheck_Line_Cube(cal_pos1, cal_pos2,
				VGet(m_block[i].GetBlockPosition().x - 100.0f, m_block[i].GetBlockPosition().y, m_block[i].GetBlockPosition().z - 100.0f),
				VGet(m_block[i].GetBlockPosition().x + 100.0f, m_block[i].GetBlockPosition().y + BLOCK_TOP, m_block[i].GetBlockPosition().z + 100.0f));

			// 当たった場合の処理
			if (LineBlock.HitFlag == TRUE) {
				// ポリゴンに当たったフラグを立てる
				HitFlag = 1;
				if (Player->move.y > 0) {
					Player->move.y *= -1;
					MaxY = Player[0].pos.y - 100.0f;
					m_block[i].SetBlockFlag(FALSE);
				}
				else {
					// 接触したＹ座標を保存する
					MaxY = m_block[i].GetBlockPosition().y + BLOCK_TOP;
				}
			}
		}
	}

	return HitFlag;
}


