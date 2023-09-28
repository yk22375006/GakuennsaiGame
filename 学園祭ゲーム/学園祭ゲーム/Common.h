
/* _/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/

	FILE	: Common.h
	NAME	: kz-matsu

+ ------ Explanation of file --------------------------------------------------------------------------
       
	�S�Ẵt�@�C���ŋ��ʂ̃w�b�_�[�t�@�C��

+ _/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/ */

/* -----------------------------------------------------------------------------------------
|
|       DEFINE�錾
|
+ --------------------------------------------------------------------------------------- */
// ��̃C�x���g�ӂ�Ɏw��ł���I�u�W�F�N�g�̍ő吔
#define STAGE_EVENT_OBJECT_MAX_NUM					(16)

// �R���W�������f���̍ő�}�e���A����
#define STAGE_COLLISION_MODEL_MATERIAL_MAX_NUM		(32)

// �L�����N�^�[�A�j���[�V������FPS
#define CHARA_ANIM_FPS					(30)

// �L�����N�^�[�ɕt������T�u�R�c���f���̍ő吔
#define CHARA_MAX_SUBMODEL				(4)

// �L�����N�^�[�̕�����f�[�^�Ŏg�p�ł���ő啶����
#define CHARA_MAX_STRINGLENGTH			(64)

// �L�����N�^�[�̂P�A�j���[�V�����ň�����U��������̐�
#define CHARA_ATTACK_MAX_NUM			(4)

// �L�����N�^�[�̍U������p�ʒu���̍ő吔
#define CHARA_ATTACK_POS_MAX_NUM		(4)

// �X�e�[�W�I��
#define CHOICESTAGE 1

// �v���C���[���f���̃T�C�Y
#define PLAYER_SIZE_H	340.0f
#define PLAYER_SIZE_W	80.0f

// �v���C���[�̈ړ����x
#define PLAYER_SPEED 12.0f
#define PLAYER_JUMP_SPEED 50.0f
#define PLAYER_FALL_SPEED 1.5f

// �u���b�N
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

// �w�i
#define BACKGROUNDTYPE		5
#define BACKGROUNDTATAMI	0
#define BACKGROUNDFLOOR		18

// �v���C���[�̈ړ��U�����̉���
#define Player_ATTACK_SPEED 16.0f

// �G�l�~�[�̋��݈ړ�
#define ENEMY_KNOCKBACK 15.0f

// �J�����̉�]��
#define CAMERA_ROTATE 200.0f

// �}�b�v
#define MAP_Y 145
#define MAP_X 16
/* -----------------------------------------------------------------------------------------
|
|       �\���̐錾
|
+ --------------------------------------------------------------------------------------- */
typedef struct
{
	int model;		// ���f��
	int run;		// ����
	int attack;		// �U��
	int stop;		// ��~��
	int damage;		// �_���[�W��
	int down;		// �_�E��
	int jump;		// �W�����v
	int jimp_in;	// �W�����v����
	int jump_out;	// �W�����v�I���
} AnimationDate;

/* -----------------------------------------------------------------------------------------
|
|       ���ʃw�b�_�[
|
+ --------------------------------------------------------------------------------------- */
#include <DxLib.h>
#include "CharaBase.h"
#include "stagedate.h"
#include "Animation.h"
#include "Block.h"
#include "Player.h"


#include "ConsoleWindow.h"	// --- �R���\�[���E�B���h�E


#include "math.h"
#include <ctime>        // time
#include <cstdlib>      // srand,rand
/* -----------------------------------------------------------------------------------------
|
|       �^�錾
|
+ --------------------------------------------------------------------------------------- */

// --- �V�[���̖��O
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
	E_STAND,		// �����ҋ@
	E_BLOWIN,		// �_���[�W�J�n
	E_BLOWLOOP,	// �_���[�W��
	E_BLOWOUT,	// �_���[�W�I��
};



/* -----------------------------------------------------------------------------------------
|
|       �v���g�^�C�v�錾
|
+ --------------------------------------------------------------------------------------- */
// --- �A�j���[�V����
extern void AnimationPlayer(int);
extern void AnimationEnemy(int);

// --- �v���C���[

// --- ����
extern void WeaponInit();

// --- �J�����̈ړ�
void CameraMove();

// --- �`��
extern void Draw();

/* -----------------------------------------------------------------------------------------
|
|       �O���Q�Ɛ錾
|
+ --------------------------------------------------------------------------------------- */
// --- �R���\�[���E�B���h�E
extern ConsoleWindow g_cWin ;	

// --- �v���C���[
extern Player player[2];
extern Player* g_Chara[2];

// --- ����



// --- �J����
extern VECTOR cpos;
extern VECTOR ctgt;
extern VECTOR cadd;

// --- �L�[����
extern int key1;
extern int key2;

// �V���h�E�}�b�v�n���h��
extern int ShadowMapHandle;

// �X�e�[�W�n���h��
extern int stagedate;
extern int skydate;
extern int blockdate[BLOCK_TYPE];


// �X�e�[�W�R���W�������
extern int HitFlag;						// �u���b�N�ɓ����������ǂ������L�����Ă����̂Ɏg���ϐ�( �O:�������Ă��Ȃ�  �P:�������� )
extern HITRESULT_LINE LineBlock;

// �L�������q�b�g�������̃|���S���\���̍��W
extern float MaxY;

// ����u���b�N
extern int StageMap[MAP_Y][MAP_X];
extern Block m_block[MAX_BLOCK];
extern int blockcnt;

// �w�i
extern int bgdate[BACKGROUNDTYPE];
extern int bg_tatami[BACKGROUNDFLOOR];

// �}�g���b�N�X
extern MATRIX WeaponMatrix;

// ���C�g
extern int LHandle;
