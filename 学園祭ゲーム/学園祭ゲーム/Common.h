
/* _/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/

	FILE	: Common.h
	NAME	: kz-matsu

+ ------ Explanation of file --------------------------------------------------------------------------
       
	全てのファイルで共通のヘッダーファイル

+ _/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/ */

/* -----------------------------------------------------------------------------------------
|
|       DEFINE宣言
|
+ --------------------------------------------------------------------------------------- */
// 一つのイベント辺りに指定できるオブジェクトの最大数
#define STAGE_EVENT_OBJECT_MAX_NUM					(16)

// コリジョンモデルの最大マテリアル数
#define STAGE_COLLISION_MODEL_MATERIAL_MAX_NUM		(32)

// キャラクターアニメーションのFPS
#define CHARA_ANIM_FPS					(30)

// キャラクターに付けられるサブ３Ｄモデルの最大数
#define CHARA_MAX_SUBMODEL				(4)

// キャラクターの文字列データで使用できる最大文字数
#define CHARA_MAX_STRINGLENGTH			(64)

// キャラクターの１アニメーションで扱える攻撃判定情報の数
#define CHARA_ATTACK_MAX_NUM			(4)

// キャラクターの攻撃判定用位置情報の最大数
#define CHARA_ATTACK_POS_MAX_NUM		(4)

// ステージ選択
#define CHOICESTAGE 1

// プレイヤーモデルのサイズ
#define PLAYER_SIZE_H	340.0f
#define PLAYER_SIZE_W	80.0f

// プレイヤーの移動速度
#define PLAYER_SPEED 12.0f
#define PLAYER_JUMP_SPEED 50.0f
#define PLAYER_FALL_SPEED 1.5f

// ブロック
#define MAX_BLOCK			600
#define BLOCK_TYPE			10
#define BLOCK_TOP			100.0f
#define BLOCK_X_SIZE		125.0f
#define TATAMI_BLOCK		1
#define BREAK_BLOCK			2
#define FALL_BLOCK			3
#define INVINCIBLE_BLOCK	4
#define MOVE_BLOCK			5
#define NEEDLE_BLOCK		6
#define WOOD_BLOCK			7

#define WEAPON_HEIGHT 110.0f
#define WEAPON_WIDTH 6.0f

// 背景
#define BACKGROUNDTYPE		5
#define BACKGROUNDTATAMI	0
#define BACKGROUNDFLOOR		18

// プレイヤーの移動攻撃時の加速
#define Player_ATTACK_SPEED 16.0f

// エネミーの怯み移動
#define ENEMY_KNOCKBACK 15.0f

// カメラの回転量
#define CAMERA_ROTATE 200.0f

// マップ
#define MAP_Y 145
#define MAP_X 16
/* -----------------------------------------------------------------------------------------
|
|       構造体宣言
|
+ --------------------------------------------------------------------------------------- */
typedef struct
{
	int model;		// モデル
	int run;		// 走り
	int attack;		// 攻撃
	int stop;		// 停止中
	int damage;		// ダメージ中
	int down;		// ダウン
	int jump;		// ジャンプ
	int jimp_in;	// ジャンプ入り
	int jump_out;	// ジャンプ終わり
} AnimationDate;

/* -----------------------------------------------------------------------------------------
|
|       共通ヘッダー
|
+ --------------------------------------------------------------------------------------- */
#include <DxLib.h>
#include "CharaBase.h"
#include "stagedate.h"
#include "Animation.h"
#include "Block.h"
#include "Player.h"


#include "ConsoleWindow.h"	// --- コンソールウィンドウ


#include "math.h"
#include <ctime>        // time
#include <cstdlib>      // srand,rand
/* -----------------------------------------------------------------------------------------
|
|       型宣言
|
+ --------------------------------------------------------------------------------------- */

// --- シーンの名前
enum SceneName
{
	eSceneBlank = -1 ,
	eSceneTitle ,
	eSceneChoice , 
	eScenePlay ,
	eSceneClear ,
	eSceneOver ,
} ;

enum CharaAnimationMode
{
	STAND,
	RUN,
	JUMPIN,
	JUMPLOOP,
	JUMPOUT,
	FALL,
	ATTACK,
	BLOW,
	BLOWLOOP,
	DOWNLOOP,

};

enum EnemyMode 
{
	E_STAND,		// 立ち待機
	E_BLOWIN,		// ダメージ開始
	E_BLOWLOOP,	// ダメージ中
	E_BLOWOUT,	// ダメージ終了
};



/* -----------------------------------------------------------------------------------------
|
|       プロトタイプ宣言
|
+ --------------------------------------------------------------------------------------- */
// --- アニメーション
extern void AnimationPlayer(int);
extern void AnimationEnemy(int);

// --- プレイヤー

// --- 武器
extern void WeaponInit();

// --- カメラの移動
void CameraMove();

// --- 描画
extern void Draw();

/* -----------------------------------------------------------------------------------------
|
|       外部参照宣言
|
+ --------------------------------------------------------------------------------------- */
// --- コンソールウィンドウ
extern ConsoleWindow g_cWin ;	

// --- プレイヤー
extern Player player[2];
extern Player* g_Chara[2];

// --- 武器



// --- カメラ
extern VECTOR cpos;
extern VECTOR ctgt;
extern VECTOR cadd;

// --- キー入力
extern int key1;
extern int key2;

// シャドウマップハンドル
extern int ShadowMapHandle;

// ステージハンドル
extern int stagedate;
extern int skydate;
extern int blockdate[BLOCK_TYPE];


// ステージコリジョン情報
extern int HitFlag;						// ブロックに当たったかどうかを記憶しておくのに使う変数( ０:当たっていない  １:当たった )
extern HITRESULT_LINE LineBlock;

// キャラがヒットした床のポリゴン表示の座標
extern float MaxY;

// 足場ブロック
extern int StageMap[MAP_Y][MAP_X];
extern Block m_block[MAX_BLOCK];
extern int blockcnt;

// 背景
extern int bgdate[BACKGROUNDTYPE];
extern int bg_tatami[BACKGROUNDFLOOR];

// マトリックス
extern MATRIX WeaponMatrix;

// ライト
extern int LHandle;
