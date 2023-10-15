
/* -------------------------------------------------------- +
 |                                                          |
 |                         Player.h                         |
 |                                                          |
 + -------------------------------------------------------- */
class Player : public CharaBase {
	public :
		Player( ) ;					// コンストラクタ
		~Player( ) ;				// デストラクタ
		int init( ) ;				// 初期セット
		int Draw( CharaBase *pp1 ) ;	// 描画
		int AllowKey( ) ;			// 矢印キーが押されてるか

		// アニメーション関数
		int LoadAnimation( CharaBase* pp1 ) ;				// アニメーション読み込み
		int AnimationInit( ) ;				// アニメーション初期セット
		int Animation( CharaBase *pp1 ) ;	// アニメーション再生
		int ChangeAnimation( CharaBase *pp1 , int set_anim ) ;	// アニメーション切り替え
		int AnimationType(CharaBase* pp1);						// タイプ別アニメーション再生
		int ChangeAnimationType(CharaBase* pp1, int set_anim);	// タイプ別アニメーション切り替え

		// キャラチョイス
		void CharaChoice(CharaBase* pp1) ;						// キャラ選択

		// アクションモード関数
		int ActionLoop( CharaBase *pp1 , CharaBase *pp2 ) ;		// アクションループ
		void CharaStop( CharaBase *pp1 , CharaBase* pp2 ) ;		// 停止中
		void CharaMove( CharaBase *pp1 , CharaBase* pp2 ) ;		// 移動
		void CharaAttack( CharaBase *pp1 , CharaBase* pp2 ) ;	// 攻撃
		void CharaDamage( CharaBase *pp1 , CharaBase* pp2 ) ;	// ダメージ
		void CharaDown( CharaBase* pp1, CharaBase* pp2);		// ダウン
		void CharaJump( CharaBase* pp1, CharaBase* pp2);		// ジャンプ初期設定
		void CharaFall(CharaBase* pp1, CharaBase* pp2);			// 落下
		void CharaRevival(CharaBase* pp1, CharaBase* pp2);		// 復活

		// ヒットチェック
		void Move_HitCheck(CharaBase* pp1, CharaBase* pp2);
		void Block_HitCheck(CharaBase* pp1);
		void Revival_HitCheck(CharaBase* pp1);

} ;

