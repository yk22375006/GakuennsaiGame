#include <DxLib.h>
#include "Common.h"


int CollisionBlock() {
	HitFlag = 0;
	VECTOR cal_pos1 = VAdd(player[0].GetPosition(), VGet(0.0f, PLAYER_SIZE_H, 0.0f));
	VECTOR cal_pos2 = VAdd(player[0].GetPosition(), VGet(0.0f, -10.0f, 0.0f));

	for (int i = 0; i < MAX_BLOCK; i++) {
		if (m_block[i].GetBlockFlag() == TRUE) {
			switch (m_block[i].GetBlockType()) {
				case TATAMI_BLOCK :
				case BREAK_BLOCK :
				case FALL_BLOCK :
				case MOVE_BLOCK :
				case WOOD_BLOCK :
				case NEEDLE_BLOCK:
					LineBlock = HitCheck_Line_Cube(cal_pos1, cal_pos2,
						VGet(m_block[i].GetBlockPosition().x - 100.0f, m_block[i].GetBlockPosition().y, m_block[i].GetBlockPosition().z - 100.0f),
						VGet(m_block[i].GetBlockPosition().x + 100.0f, m_block[i].GetBlockPosition().y + BLOCK_TOP, m_block[i].GetBlockPosition().z + 100.0f));
					break;

				case INVINCIBLE_BLOCK :
					LineBlock = HitCheck_Line_Cube(cal_pos1, cal_pos2,
						VGet(m_block[i].GetBlockPosition().x - 100.0f, m_block[i].GetBlockPosition().y, m_block[i].GetBlockPosition().z - 100.0f),
						VGet(m_block[i].GetBlockPosition().x + 100.0f, m_block[i].GetBlockPosition().y + BLOCK_TOP * 2, m_block[i].GetBlockPosition().z + 100.0f));
					break;
			}

			// ìñÇΩÇ¡ÇΩèÍçáÇÃèàóù
			if (LineBlock.HitFlag == TRUE) {
				// É|ÉäÉSÉìÇ…ìñÇΩÇ¡ÇΩÉtÉâÉOÇóßÇƒÇÈ
				if (player->GetSpeed().y> 0) {
					switch (m_block[i].GetBlockType()) {
						case TATAMI_BLOCK :
						case BREAK_BLOCK :
						case FALL_BLOCK :
							player->SetY_Spd(player->GetSpeed().y * -1);
							MaxY = player->GetSpeed().y - 100.0f;
							m_block[i].SetBlockFlag(FALSE);
							break;
							
						case INVINCIBLE_BLOCK :
						case MOVE_BLOCK :
						case NEEDLE_BLOCK :
						case WOOD_BLOCK :
							player->SetY_Spd(player->GetSpeed().y * -1);
							MaxY = player->GetSpeed().y - 100.0f;
							break;
					}
				}
				else {
					HitFlag = 1;
					if (m_block[i].GetBlockType() != INVINCIBLE_BLOCK) {
						// ê⁄êGÇµÇΩÇxç¿ïWÇï€ë∂Ç∑ÇÈ
						MaxY = m_block[i].GetBlockPosition().y + BLOCK_TOP;
					}
					else {
						// ê⁄êGÇµÇΩÇxç¿ïWÇï€ë∂Ç∑ÇÈ
						MaxY = m_block[i].GetBlockPosition().y + BLOCK_TOP * 2;
					}
				}
			}
		}
	}
	return HitFlag;
}


