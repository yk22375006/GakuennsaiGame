/* -----------------------------------------------------------------------------------------
|																						   |
|										Block.h											   |
|																						   |
+ --------------------------------------------------------------------------------------- */


class Block {
	private:
		VECTOR b_posi;
		POINT b_Map;
		int b_type;
		bool b_use_flg;
		 
	public:
		int b_model;

		void init();

		// �ʒu���
		VECTOR GetBlockPosition() {
			return b_posi;
		}
		void SetBlockPosition(VECTOR set_top_posi) {
			b_posi = set_top_posi;
		}

		// �}�b�v���W
		POINT GetMapPosition() {
			return b_Map;
		}
		int GetMapPositionX() {
			return b_Map.x;
		}
		int GetMapPositionY() {
			return b_Map.y;
		}
		void SetMapPosition(POINT set_b_map) {
			b_Map = set_b_map;
		}
		void SetMapPositionY(int set_b_map_x) {
			b_Map.x = set_b_map_x;
		}
		void SetMapPositionX(int set_b_map_x) {
			b_Map.y = set_b_map_x;
		}

		// �u���b�N�̎��
		int GetBlockType() {
			return b_type;
		}
		void SetBlockType(int set_b_type) {
			b_type = set_b_type;
		}

		// �g�p�t���O
		bool GetBlockFlag() {
			return b_use_flg;
		}
		void SetBlockFlag(bool set_b_use_flg) {
			b_use_flg = set_b_use_flg;
		}
};

