
/* -------------------------------------------------------- +
 |                                                          |6
 |                        CharaBase.h                       |
 |                                                          |
 + -------------------------------------------------------- */
enum CharaMode {
	eCharaStop ,		// 停止中
	eCharaMove ,		// 移動	
	eCharaAttack,		// 攻撃
	eCharaJump,			// ジャンプ
	eCharaFall,			// 落下
	eCharaDamage,		// ダメージ
	eCharaDown			// ダウン
} ;

enum Direction {
	DOWN ,		// 下向き
	LEFT ,		// 左向き
	UP ,		// 上向き
	RIGHT ,		// 右向き
} ;



class CharaBase {
	protected :
		VECTOR posi ;			// 位置情報
		VECTOR spd ;			// スピード
		int use_flg ;			// 使用フラグ
		int act_mode ;			// アクションモード
		float direction ;		// 方向
		int motion ;			// 現在のアニメモーション
		int anim_attach ;		// 現在のアニメーションを格納
		float anim_time ;		// アニメーションの総時間を格納
		float play_time ;		// アニメーションの再生時間
		int rootflm ;			// アニメーション+移動可能にする
		float Width ;			// プレイヤーサイズ幅(ヒットチェック用)
		float Height ;			// プレイヤーサイズ高さ(ヒットチェック用)
		int hp ;
		int number;				// プレイヤー番号

	public :
		CharaBase( ) ;			// コンストラクタ
		~CharaBase( ) ;			// デストラクタ
		int init( ) ;			// 初期セット
		int MoveSet( ) ;		// 移動量をセット
		AnimationDate anim ;	// アニメーションデータ

		// --- インライン関数 ---
		// 使用フラグ取得セット
		int GetUse_Flg( ) {
			return use_flg ;
		} ;

		void SetUse_Flg( int set_flg ) {
			use_flg = set_flg ;
		} ;

		// 位置情報
		VECTOR GetPosition( ) {
			return posi ;
		}

		void SetPosition( VECTOR set_posi ) {
			posi = set_posi ;
		}

		void SetY_Posi( float set_posi ) {
			posi.y = set_posi ;
		}

		void SetX_Posi(float set_posi) {
			posi.x = set_posi;
		}

		// スピード
		VECTOR GetSpeed( ) {
			return spd ;
		}

		void SetSpeed( VECTOR set_spd )	{
			spd = set_spd ;
		}

		void SetY_Spd( float set_spd ) {
			spd.y = set_spd ;
		}

		void SetX_Spd(float set_spd) {
			spd.x = set_spd;
		}

		// アクションモード
		int GetAct_Mode( ) {
			return act_mode ;
		}

		void SetAct_Mode( int set_mode ) {
			act_mode = set_mode ;
		}

		// 方向
		float GetDirection( ) {
			return direction ;
		}

		void SetDiection( float set_direction ) {
			direction = set_direction ;
		}

		// アタッチアニメーション
		int GetAnim_Attach( ) {
			return anim_attach ;
		}

		void SetAnim_Attach( int set_anim ) {
			anim_attach = set_anim ;
		}		

		// アニメーション総時間
		float GetAnim_Time( ) {
			return anim_time ;
		}

		void SetAnim_Time( float set_time ) {
			anim_time = set_time ;
		}

		// アニメーション再生時間
		float GetPlay_Time( ) {
			return play_time ;
		}

		void SetPlay_Time( float set_time ) {
			play_time = set_time ;
		}

		void AddPlay_Time( float add_time ) {
			play_time += add_time ;
		}

		// プレイヤーサイズ幅
		float GetWidth() {
			return Width;
		}

		// プレイヤーサイズ幅
		void SetWidth( float width ) {
			Width = width;
		}

		// プレイヤーサイズ高さ
		float GetHeight() {
			return Height;
		}

		// プレイヤーサイズ高さ
		void SetHeight( float height ) {
			Height = height;
		}

		// アニメーション再生時間
		int GetRootFlm( ) {
			return rootflm ;
		}

		void SetRootFlm( int set_flm ) {
			rootflm = set_flm ;
		}

		// アニメーション再生時間
		AnimationDate GetAnimation_Data( ) {
			return anim ;
		}

		// アニメーション再生時間
		void SetAnimation_Data( AnimationDate set_anim ) {
			anim = set_anim ;
		}

		// アニメーション再生時間
		int GetMotion( ) {
			return motion ;
		}

		void SetMotion( int set_motion ) {
			motion = set_motion ;
		}

		int GetNumber() {
			return number;
		}

		void SetNumber(int set_number) {
			number = set_number;
		}
} ;

