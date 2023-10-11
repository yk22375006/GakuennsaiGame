#include "Common.h"


/* -------------------------------------------------------- +
 |                                                          |
 |                        Block.cpp							|
 |                                                          |
 + -------------------------------------------------------- */
 /* ======================================================== +
  |                                                          |
  |                     　コンストラクタ                     |
  |                                                          |
  + ======================================================== */
Block::Block() {

}

/* ======================================================== +
 |                                                          |
 |                     　デストラクタ                       |
 |                                                          |
 + ======================================================== */
Block::~Block() {

}

/* ======================================================== +
 |                         init( )                          |
 |                     　初期セット　                       |
 |                                                          |
 + ======================================================== */
void Block::init() {
	for (int i = 0; i < BACKGROUNDFLOOR; i++) {
		bg_tatami[i] = MV1DuplicateModel(bgdate[BACKGROUNDTATAMI]);
		MV1SetPosition(bg_tatami[i], VGet(1500.0f, 100.0f + (i * 1000.0f), 100.0f));
	}
	blockcnt = 0;
	// マップデータを反映
	for (int y = MAP_Y - 1; y >= 0; y--) {
		for (int x = 0; x < MAP_X; x++) {
			if (StageMap[y][x] != 0) {
				switch (StageMap[y][x]) {
					case TATAMI_BLOCK:
						m_block[blockcnt].b_model = MV1DuplicateModel(blockdate[TATAMI_BLOCK]);
						m_block[blockcnt].b_type = TATAMI_BLOCK;
						break;

					case BREAK_BLOCK:
						m_block[blockcnt].b_model = MV1DuplicateModel(blockdate[BREAK_BLOCK]);
						m_block[blockcnt].b_type = BREAK_BLOCK;
						break;

					case FALL_BLOCK:
						m_block[blockcnt].b_model = MV1DuplicateModel(blockdate[FALL_BLOCK]);
						m_block[blockcnt].b_type = FALL_BLOCK;
						break;

					case INVINCIBLE_BLOCK:
						m_block[blockcnt].b_model = MV1DuplicateModel(blockdate[INVINCIBLE_BLOCK]);
						m_block[blockcnt].b_type = INVINCIBLE_BLOCK;
						break;

					case MOVE_BLOCK_X:
						m_block[blockcnt].b_model = MV1DuplicateModel(blockdate[MOVE_BLOCK_X]);
						m_block[blockcnt].b_type = MOVE_BLOCK_X;
						break;

					case MOVE_BLOCK_Y:
						m_block[blockcnt].b_model = MV1DuplicateModel(blockdate[MOVE_BLOCK_X]);
						m_block[blockcnt].b_type = MOVE_BLOCK_Y;
						break;

					case MOVE_BLOCK_Z:
						m_block[blockcnt].b_model = MV1DuplicateModel(blockdate[MOVE_BLOCK_X]);
						m_block[blockcnt].b_type = MOVE_BLOCK_Z;
						break;

					case NEEDLE_BLOCK:
						m_block[blockcnt].b_model = MV1DuplicateModel(blockdate[NEEDLE_BLOCK]);
						m_block[blockcnt].b_type = NEEDLE_BLOCK;
						break;

					case WOOD_BLOCK:
						m_block[blockcnt].b_model = MV1DuplicateModel(blockdate[WOOD_BLOCK]);
						m_block[blockcnt].b_type = WOOD_BLOCK;
						break;
				}
				m_block[blockcnt].b_Map.y = y;
				m_block[blockcnt].b_Map.x = x;
				m_block[blockcnt].b_use_flg =TRUE;
				m_block[blockcnt].b_move_flg = FALSE;
				m_block[blockcnt].b_number =blockcnt;
				m_block[blockcnt].b_spd = VGet(0.0f, 0.0f, 0.0f);
				blockcnt++;
			}
		}
	}

	blockcnt = 0;

	// 座標の配置
	for (int y = (MAP_Y - 1); y >= 0; y--) {
		for (int x = 0; x < MAP_X; x++) {
			if (StageMap[y][x] != 0) {
				if (StageMap[y][x] != NEEDLE_BLOCK) {
					MV1SetPosition(m_block[blockcnt].b_model, VGet((x * 200.0f), ((MAP_Y - y) * 100.0f), 0.0f));
					m_block[blockcnt].SetBlockPosition(VGet((x * 200.0f), ((MAP_Y - y) * 100.0f), 0.0f));
					m_block[blockcnt].SetBlockFirstPosition(VGet((x * 200.0f), ((MAP_Y - y) * 100.0f), 0.0f));

				}
				else {
					MV1SetPosition(m_block[blockcnt].b_model, VGet((x * 200.0f), ((MAP_Y - y) * 100.0f) - 50.0f, 0.0f));
					m_block[blockcnt].b_posi = VGet((x * 200.0f), ((MAP_Y - y) * 100.0f) - 50.0f, 0.0f);
					m_block[blockcnt].b_first_posi = VGet((x * 200.0f), ((MAP_Y - y) * 100.0f) - 50.0f, 0.0f);
				}
				blockcnt++;
			}
		}
	}
	m_block[27].b_posi = VGet(1500.0f, 100.0f + (6 * 1000.0f), 300.0f);
	m_block[27].b_first_posi = VGet(1500.0f, 100.0f + (6 * 1000.0f), 300.0f);
}

/* ======================================================== +
 |						BlockMove( )						|
 |						ブロックの移動						|
 |                                                          |
 + ======================================================== */
void Block::BlockMove(Block *bb) {

	switch (bb->b_type) {
		case MOVE_BLOCK_X :
			if (bb->b_move_flg == FALSE)
				bb->b_spd.x = +BLOCK_MOVE_SPD;
			if (bb->b_move_flg == TRUE)
				bb->b_spd.x = -BLOCK_MOVE_SPD;

			if (bb->b_posi.x - bb->b_first_posi.x > 500.0f)
				bb->b_move_flg = TRUE;

			if (bb->b_posi.x - bb->b_first_posi.x < -500.0f)
				bb->b_move_flg = FALSE;

			bb->b_posi.x += bb->b_spd.x;

			MV1SetPosition(bb->b_model, bb->b_posi);

			if ((m_block[bb->b_number - 1].b_type != WOOD_BLOCK &&
				m_block[bb->b_number - 1].b_type != MOVE_BLOCK_X &&
				m_block[bb->b_number - 1].b_type != MOVE_BLOCK_Y &&
				m_block[bb->b_number - 1].b_type != MOVE_BLOCK_Z)) {
				if (m_block[bb->b_number - 1].b_move_flg == FALSE)
					m_block[bb->b_number - 1].b_spd.x = +BLOCK_MOVE_SPD;
				if (m_block[bb->b_number - 1].b_move_flg == TRUE)
					m_block[bb->b_number - 1].b_spd.x = -BLOCK_MOVE_SPD;

				if (m_block[bb->b_number - 1].b_posi.x - m_block[bb->b_number - 1].b_first_posi.x > 500.0f)
					m_block[bb->b_number - 1].b_move_flg = TRUE;

				if (m_block[bb->b_number - 1].b_posi.x - m_block[bb->b_number - 1].b_first_posi.x < -500.0f)
					m_block[bb->b_number - 1].b_move_flg = FALSE;

				m_block[bb->b_number - 1].b_posi.x += m_block[bb->b_number - 1].b_spd.x;
				MV1SetPosition(m_block[bb->b_number - 1].b_model, m_block[bb->b_number - 1].b_posi);
			}
			if ((m_block[bb->b_number + 1].b_type != WOOD_BLOCK &&
				m_block[bb->b_number + 1].b_type != MOVE_BLOCK_X &&
				m_block[bb->b_number + 1].b_type != MOVE_BLOCK_Y &&
				m_block[bb->b_number + 1].b_type != MOVE_BLOCK_Z)) {
				if (m_block[bb->b_number + 1].b_move_flg == FALSE)
					m_block[bb->b_number + 1].b_spd.x = +BLOCK_MOVE_SPD;
				if (m_block[bb->b_number + 1].b_move_flg == TRUE)
					m_block[bb->b_number + 1].b_spd.x = -BLOCK_MOVE_SPD;

				if (m_block[bb->b_number + 1].b_posi.x - m_block[bb->b_number + 1].b_first_posi.x > 500.0f)
					m_block[bb->b_number + 1].b_move_flg = TRUE;

				if (m_block[bb->b_number + 1].b_posi.x - m_block[bb->b_number + 1].b_first_posi.x < -500.0f)
					m_block[bb->b_number + 1].b_move_flg = FALSE;

				m_block[bb->b_number + 1].b_posi.x += m_block[bb->b_number - 1].b_spd.x;
				MV1SetPosition(m_block[bb->b_number + 1].b_model, m_block[bb->b_number + 1].b_posi);
			}
			break;

		case MOVE_BLOCK_Y:
			if (bb->b_move_flg == FALSE)
				bb->b_spd.y = +BLOCK_MOVE_SPD;
			if (bb->b_move_flg == TRUE)
				bb->b_spd.y = -BLOCK_MOVE_SPD;

			if (bb->b_posi.y - bb->b_first_posi.y > 320.0f)
				bb->b_move_flg = TRUE;

			if (bb->b_posi.y - bb->b_first_posi.y < -320.0f)
				bb->b_move_flg = FALSE;

			bb->b_posi.y += bb->b_spd.y;
			MV1SetPosition(bb->b_model, bb->b_posi);
			break;

		case MOVE_BLOCK_Z:
			break;
	}
}




