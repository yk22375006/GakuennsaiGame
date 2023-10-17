
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
#define PLAYER_SIZE_H	425.0f
#define PLAYER_SIZE_W	200.0f
#define SPEED_ATTACK_RANGE			100.0f	// スピードタイプの攻撃範囲
#define SPEED_ATTACK_MIDDLE_RANGE	130.0f	// スピードタイプの攻撃範囲の中間
#define BLANCE_ATTACK_RANGE			170.0f	// バランスタイプの攻撃範囲
#define BLANCE_ATTACK_MIDDLE_RANGE	200.0f	// バランスタイプの攻撃範囲の中間
#define POWER_ATTACK_RANGE			200.0f	// パワータイプの攻撃範囲
#define POWER_ATTACK_MIDDLE_RANGE	250.0f	// パワータイプの攻撃範囲の中間

//	プレイヤーのタイプ
#define SPEEDMODE	0	// スピードタイプ
#define BALANCEMODE	1	// バランスタイプ
#define POWERMODE	2	// パワータイプ

// プレイヤーの移動速度
#define PLAYER_SPEED		12.0f	// 横軸の移動スピード
#define PLAYER_JUMP_SPEED	63.0f	// ジャンプの初速
#define PLAYER_FALL_SPEED	1.5f	// 落下速度
#define SPEEDPLAYER_SPEED	24.0f	// スピードキャラの移動速度
#define BALANCEPLAYER_SPEED	18.0f	// バランスキャラの移動速度
#define POWERPLAYER_SPEED	12.0f	// パワーキャラの移動速度
#define SPEEDBLOWDISTANCE	50.0f	// スピードキャラの吹っ飛び距離
#define BALANCEBLOWDISTANCE	75.0f	// バランスキャラの吹っ飛び距離
#define POWERBLOWDISTANCE	100.0f	// パワーキャラの吹っ飛び距離

// プレイヤーの攻撃時間
#define SPEED_ATTACK_START		5.5f	// スピードキャラの攻撃開始時間
#define SPEED_ATTACK_END		8.0f	// スピードキャラの攻撃終了時間
#define BALANCE_ATTACK_START	18.5	// スピードキャラの攻撃開始時間
#define BALANCE_ATTACK_END		21.5f	// スピードキャラの攻撃終了時間
#define POWER_ATTACK_START		12.5f	// スピードキャラの攻撃開始時間
#define POWER_ATTACK_END		21.0f	// スピードキャラの攻撃終了時間

// ブロック
#define MAX_BLOCK			640		// ブロックの最大数
#define BLOCK_TYPE			10		// ブロックの種類
#define BLOCK_TOP			100.0f	// ブロックの高さ
#define BLOCK_X_SIZE		125.0f	// ブロックの横幅二分の一
#define TATAMI_BLOCK		1		// 畳ブロック
#define BREAK_BLOCK			2		// 壊せるブロック
#define FALL_BLOCK			3		// 崩れるブロック
#define INVINCIBLE_BLOCK	4		// 壊れないブロック
#define NEEDLE_BLOCK		5		// 針ブロック
#define WOOD_BLOCK			6		// 壁ブロック
#define MOVE_BLOCK_X		7		// 
#define MOVE_BLOCK_Y		8		//  
#define MOVE_BLOCK_Z		9		// 
#define BLOCK_MOVE_SPD		2.5f	// 

#define WEAPON_HEIGHT 110.0f
#define WEAPON_WIDTH 6.0f

// 背景
#define BACKGROUNDTYPE		5	// 
#define BACKGROUNDTATAMI	0	// 
#define BACKGROUNDFLOOR		18	// 背景のブロックの種類階層数

// プレイヤーの移動攻撃時の加速
#define Player_ATTACK_SPEED 16.0f

// エネミーの怯み移動
#define ENEMY_KNOCKBACK 15.0f

// カメラの回転量
#define CAMERA_ROTATE 200.0f

// 吹っ飛び方向の指定
#define NONBLOW		0	// 吹っ飛ばない
#define BLOWRIGHT	1	// 右に吹っ飛ぶ
#define BLOWLEFT	2	// 左に吹っ飛ぶ

// マップ
#define MAP_Y 181		// ブロックの縦の数
#define MAP_X 16		// ブロックの横の数
#define MIN_X 70.0f		// マップ上で最も左の座標
#define MAX_X 2930.0f	// マップ上で最も右の座標
#define MAP_Y 181
#define MAP_X 16

#define MAP_Y2 13

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
	int jump_in;	// ジャンプ入り
	int jump_out;	// ジャンプ終わり
	int fall;		// 落下
	int type[3];	// キャラタイプ別
	int typestop[3];// キャラ別待機モーション
} AnimationDate;

/* -----------------------------------------------------------------------------------------
|
|       共通ヘッダー
|
+ --------------------------------------------------------------------------------------- */
#include <DxLib.h>
#include "CharaBase.h"
#include "StageDate.h"
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
	eScenePlay1 ,
	eScenePlay2 ,
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

// --- プレイヤー

// --- カメラの移動
void CameraMove();

// --- 描画
extern void Draw();

/* -----------------------------------------------------------------------------------------
|
|       外部参照宣言
|
+ --------------------------------------------------------------------------------------- */
extern int gamemode;

// --- コンソールウィンドウ
extern ConsoleWindow g_cWin ;	

// --- プレイヤー
extern Player player[12];
extern Player* g_Chara[12];
extern AnimationDate Original[3];
extern int chara_type1;
extern int chara_type2;

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

// モデル
extern int StageMap[MAP_Y][MAP_X];
extern int StageMap2[MAP_Y2][MAP_X];

extern Block m_block[MAX_BLOCK];
extern Block m_block2[MAX_BLOCK];
 
extern int blockcnt;
extern int moon;
extern int castle;

// 背景
extern int bgdate[BACKGROUNDTYPE];
extern int bg_tatami[BACKGROUNDFLOOR];

// マトリックス
extern MATRIX WeaponMatrix;

// 連打制限
extern int continuous_limit;
extern int DrawLimit;

// --- 死去数
extern char DrawScore1[10];
extern char DrawScore2[10];

// --- 制限時間用
extern int timediff;
extern LONGLONG timelimit;
extern char drawtime[10];

// ライト
extern int LHandle_p1;
extern int LHandle_p2;
extern float Range;
extern float OutAngle;
extern float InAngle;
extern float C_DirectionX;
extern float C_DirectionY;
extern float C_DirectionZ;





