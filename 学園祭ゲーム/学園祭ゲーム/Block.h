/* -----------------------------------------------------------------------------------------
|																						   |
|										Block.h											   |
|																						   |
+ --------------------------------------------------------------------------------------- */


class Block {
	private:
		VECTOR b_posi;
		VECTOR b_first_posi;
		VECTOR b_spd;
		POINT b_Map;
		int b_type;
		int b_number;
		bool b_use_flg;
		bool b_move_flg;
		  
	public:
		int b_model;

		// ブロック
		Block();
		~Block();
		void init();
		void BlockMove(Block* bb);
		void BlockFall(Block* bb);


		// 位置情報
		VECTOR GetBlockPosition() {
			return b_posi;
		}
		void SetBlockPosition(VECTOR set_top_posi) {
			b_posi = set_top_posi;
		}

		// ブロックの初期位置
		VECTOR GetBlockFirstPosition() {
			return b_first_posi;
		}
		void SetBlockFirstPosition(VECTOR set_b_first_posi) {
			b_first_posi = set_b_first_posi;
		}

		// ブロックの移動速度
		VECTOR GetBlockSpeed() {
			return b_spd;
		}
		void SetBlockSpeed(VECTOR set_b_spd) {
			b_spd = set_b_spd;
		}
		void SetBlockSpeedX(float set_b_spd_x) {
			b_spd.x = set_b_spd_x;
		}
		void SetBlockSpeedY(float set_b_spd_y) {
			b_spd.y = set_b_spd_y;
		}
		void SetBlockSpeedZ(float set_b_spd_z) {
			b_spd.y = set_b_spd_z;
		}

		// マップ座標
		POINT GetMapPosition() {
			return b_Map;
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

		// ブロックの種類
		int GetBlockType() {
			return b_type;
		}
		void SetBlockType(int set_b_type) {
			b_type = set_b_type;
		}

		// ブロックの番号
		int GetBlockNumber() {
			return b_number;
		}
		void SetBlockNumber(int set_b_number) {
			b_number = set_b_number;
		}

		// 使用フラグ
		bool GetBlockFlag() {
			return b_use_flg;
		}
		void SetBlockFlag(bool set_b_use_flg) {
			b_use_flg = set_b_use_flg;
		}

		// ブロックの移動反転フラグ
		bool GetMoveBlockFlag() {
			return b_move_flg;
		}
		void SetMoveBlodkFlag(bool set_b_move_flg) {
			b_move_flg = set_b_move_flg;
		}
};

