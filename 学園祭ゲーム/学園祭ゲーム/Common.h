
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
#define PLAYER_SIZE_H	425.0f
#define PLAYER_SIZE_W	200.0f
#define SPEED_ATTACK_RANGE			100.0f	// �X�s�[�h�^�C�v�̍U���͈�
#define SPEED_ATTACK_MIDDLE_RANGE	130.0f	// �X�s�[�h�^�C�v�̍U���͈͂̒���
#define BLANCE_ATTACK_RANGE			170.0f	// �o�����X�^�C�v�̍U���͈�
#define BLANCE_ATTACK_MIDDLE_RANGE	200.0f	// �o�����X�^�C�v�̍U���͈͂̒���
#define POWER_ATTACK_RANGE			200.0f	// �p���[�^�C�v�̍U���͈�
#define POWER_ATTACK_MIDDLE_RANGE	250.0f	// �p���[�^�C�v�̍U���͈͂̒���

//	�v���C���[�̃^�C�v
#define SPEEDMODE	0	// �X�s�[�h�^�C�v
#define BALANCEMODE	1	// �o�����X�^�C�v
#define POWERMODE	2	// �p���[�^�C�v

// �v���C���[�̈ړ����x
#define PLAYER_SPEED		12.0f	// �����̈ړ��X�s�[�h
#define PLAYER_JUMP_SPEED	63.0f	// �W�����v�̏���
#define PLAYER_FALL_SPEED	1.5f	// �������x
#define SPEEDPLAYER_SPEED	24.0f	// �X�s�[�h�L�����̈ړ����x
#define BALANCEPLAYER_SPEED	18.0f	// �o�����X�L�����̈ړ����x
#define POWERPLAYER_SPEED	12.0f	// �p���[�L�����̈ړ����x
#define SPEEDBLOWDISTANCE	50.0f	// �X�s�[�h�L�����̐�����ы���
#define BALANCEBLOWDISTANCE	75.0f	// �o�����X�L�����̐�����ы���
#define POWERBLOWDISTANCE	100.0f	// �p���[�L�����̐�����ы���

// �v���C���[�̍U������
#define SPEED_ATTACK_START		5.5f	// �X�s�[�h�L�����̍U���J�n����
#define SPEED_ATTACK_END		8.0f	// �X�s�[�h�L�����̍U���I������
#define BALANCE_ATTACK_START	18.5	// �X�s�[�h�L�����̍U���J�n����
#define BALANCE_ATTACK_END		21.5f	// �X�s�[�h�L�����̍U���I������
#define POWER_ATTACK_START		12.5f	// �X�s�[�h�L�����̍U���J�n����
#define POWER_ATTACK_END		21.0f	// �X�s�[�h�L�����̍U���I������

// �u���b�N
#define MAX_BLOCK			640		// �u���b�N�̍ő吔
#define BLOCK_TYPE			10		// �u���b�N�̎��
#define BLOCK_TOP			100.0f	// �u���b�N�̍���
#define BLOCK_X_SIZE		125.0f	// �u���b�N�̉����񕪂̈�
#define TATAMI_BLOCK		1		// ��u���b�N
#define BREAK_BLOCK			2		// �󂹂�u���b�N
#define FALL_BLOCK			3		// �����u���b�N
#define INVINCIBLE_BLOCK	4		// ���Ȃ��u���b�N
#define NEEDLE_BLOCK		5		// �j�u���b�N
#define WOOD_BLOCK			6		// �ǃu���b�N
#define MOVE_BLOCK_X		7		// 
#define MOVE_BLOCK_Y		8		//  
#define MOVE_BLOCK_Z		9		// 
#define BLOCK_MOVE_SPD		2.5f	// 

#define WEAPON_HEIGHT 110.0f
#define WEAPON_WIDTH 6.0f

// �w�i
#define BACKGROUNDTYPE		5	// 
#define BACKGROUNDTATAMI	0	// 
#define BACKGROUNDFLOOR		18	// �w�i�̃u���b�N�̎�ފK�w��

// �v���C���[�̈ړ��U�����̉���
#define Player_ATTACK_SPEED 16.0f

// �G�l�~�[�̋��݈ړ�
#define ENEMY_KNOCKBACK 15.0f

// �J�����̉�]��
#define CAMERA_ROTATE 200.0f

// ������ѕ����̎w��
#define NONBLOW		0	// ������΂Ȃ�
#define BLOWRIGHT	1	// �E�ɐ������
#define BLOWLEFT	2	// ���ɐ������

// �}�b�v
#define MAP_Y 181		// �u���b�N�̏c�̐�
#define MAP_X 16		// �u���b�N�̉��̐�
#define MIN_X 70.0f		// �}�b�v��ōł����̍��W
#define MAX_X 2930.0f	// �}�b�v��ōł��E�̍��W
#define MAP_Y 181
#define MAP_X 16

#define MAP_Y2 13

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
	int jump_in;	// �W�����v����
	int jump_out;	// �W�����v�I���
	int fall;		// ����
	int type[3];	// �L�����^�C�v��
	int typestop[3];// �L�����ʑҋ@���[�V����
} AnimationDate;

/* -----------------------------------------------------------------------------------------
|
|       ���ʃw�b�_�[
|
+ --------------------------------------------------------------------------------------- */
#include <DxLib.h>
#include "CharaBase.h"
#include "StageDate.h"
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

// --- �v���C���[

// --- �J�����̈ړ�
void CameraMove();

// --- �`��
extern void Draw();

/* -----------------------------------------------------------------------------------------
|
|       �O���Q�Ɛ錾
|
+ --------------------------------------------------------------------------------------- */
extern int gamemode;

// --- �R���\�[���E�B���h�E
extern ConsoleWindow g_cWin ;	

// --- �v���C���[
extern Player player[12];
extern Player* g_Chara[12];
extern AnimationDate Original[3];
extern int chara_type1;
extern int chara_type2;

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

// ���f��
extern int StageMap[MAP_Y][MAP_X];
extern int StageMap2[MAP_Y2][MAP_X];

extern Block m_block[MAX_BLOCK];
extern Block m_block2[MAX_BLOCK];
 
extern int blockcnt;
extern int moon;
extern int castle;

// �w�i
extern int bgdate[BACKGROUNDTYPE];
extern int bg_tatami[BACKGROUNDFLOOR];

// �}�g���b�N�X
extern MATRIX WeaponMatrix;

// �A�Ő���
extern int continuous_limit;
extern int DrawLimit;

// --- ������
extern char DrawScore1[10];
extern char DrawScore2[10];

// --- �������ԗp
extern int timediff;
extern LONGLONG timelimit;
extern char drawtime[10];

// ���C�g
extern int LHandle_p1;
extern int LHandle_p2;
extern float Range;
extern float OutAngle;
extern float InAngle;
extern float C_DirectionX;
extern float C_DirectionY;
extern float C_DirectionZ;





