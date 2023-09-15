
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

// �u���b�N
#define BLOCK_TYPE			10
#define TATAMI_BLOCK		1
#define BREAK_BLOCK			2
#define FALL_BLOCK			3
#define INVINCIBLE_BLOCK	4
#define MOVE_BLOCK			5
#define NEEDLE_BLOCK		6

#define WEAPON_HEIGHT 110.0f
#define WEAPON_WIDTH 6.0f

// �v���C���[�̈ړ��U�����̉���
#define Player_ATTACK_SPEED 16.0f

// �G�l�~�[�̋��݈ړ�
#define ENEMY_KNOCKBACK 15.0f

// �J�����̉�]��
#define CAMERA_ROTATE 200.0f

// �}�b�v
#define MAP_Y 13
#define MAP_X 10
/* -----------------------------------------------------------------------------------------
|
|       ���ʃw�b�_�[
|
+ --------------------------------------------------------------------------------------- */
#include <DxLib.h>
#include "CharaBase.h"
#include "StageData.h"
#include "Animation.h"
#include "Block.h"

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

// --- �L�����̕���
enum Direction
{
	DOWN,
	LEFT,
	UP,
	RIGHT,
} ;

// --- �L�����̏��
enum CharaMode
{
	STAND,		// �����ҋ@
	RUN,		// ������
	JUMPIN,		// �W�����v�J�n
	JUMPLOOP,	// �㏸��
	JUMPOUT,	// ���n
	FALL,		// ������
	ATTACK,		// �U��
} ;

enum EnemyMode 
{
	E_STAND,		// �����ҋ@
	E_BLOWIN,		// �_���[�W�J�n
	E_BLOWLOOP,	// �_���[�W��
	E_BLOWOUT,	// �_���[�W�I��
};

/* -----------------------------------------------------------------------------------------
|
|       �\���̐錾
|
+ --------------------------------------------------------------------------------------- */

/* -----------------------------------------------------------------------------------------
|
|       �v���g�^�C�v�錾
|
+ --------------------------------------------------------------------------------------- */
// --- �A�j���[�V����
extern void AnimationInit();
extern void AnimationPlayer(int);
extern void AnimationEnemy(int);

// --- �v���C���[
extern void PlayerInit();
extern void PlayerMove();

// --- ����
extern void WeaponInit();

// --- �G�l�~�[
extern void EnemyInit();

// --- ���̓����蔻��
extern int FloorSearch();
extern void E1_FloorSearch();
extern int CollisionBlock();

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

// --- �A�j���[�V����
extern int plyanim_nutral, plyanim_run, plyanim_jumpin, plyanim_jumploop, plyanim_jumpout;
extern int plyanim_attack;

extern int gobanim_ntural, gobanim_blowin, gobanim_blowloop, gobanim_blowout;

// --- �v���C���[
extern SCharaInfo Player[2];

// --- ����
extern SWeaponInfo PlayerSabel;
extern int WeponAttachFrameNum;

// --- �J����
extern VECTOR cpos;
extern VECTOR ctgt;
extern VECTOR cadd;

// --- �L�[����
extern int key;

// �V���h�E�}�b�v�n���h��
extern int ShadowMapHandle;

// �X�e�[�W�n���h��
extern int stagedata;
extern int skydata;
extern int blockdate[BLOCK_TYPE];


// �X�e�[�W�R���W�������
extern MV1_COLL_RESULT_POLY_DIM HitDim;					// �L�����N�^�[�̎��͂ɂ���|���S�������o�������ʂ��������铖���蔻�茋�ʍ\����
extern int WallNum;										// �ǃ|���S���Ɣ��f���ꂽ�|���S���̐�
extern int FloorNum;										// ���|���S���Ɣ��f���ꂽ�|���S���̐�
extern MV1_COLL_RESULT_POLY* Wall[CHARA_MAX_HITCOLL];		// �ǃ|���S���Ɣ��f���ꂽ�|���S���̍\���̂̃A�h���X��ۑ����Ă������߂̃|�C���^�z��
extern MV1_COLL_RESULT_POLY* Floor[CHARA_MAX_HITCOLL];	// ���|���S���Ɣ��f���ꂽ�|���S���̍\���̂̃A�h���X��ۑ����Ă������߂̃|�C���^�z��


extern int HitFlag;						// �|���S���ɓ����������ǂ������L�����Ă����̂Ɏg���ϐ�( �O:�������Ă��Ȃ�  �P:�������� )
extern int E1_HitFlag;					// �G�l�~�[�p�q�b�g�t���O
extern MV1_COLL_RESULT_POLY* Poly;		// �|���S���̍\���̂ɃA�N�Z�X���邽�߂Ɏg�p����|�C���^( �g��Ȃ��Ă��ς܂����܂����v���O�����������Ȃ�̂ŁE�E�E )
extern HITRESULT_LINE LineRes;			// �����ƃ|���S���Ƃ̓����蔻��̌��ʂ�������\����
extern HITRESULT_LINE E1_LineRes;
extern HITRESULT_LINE LineBlock;

// �L�������q�b�g�������̃|���S���\���̍��W
extern VECTOR PolyCharaHitField[3];
extern float MaxY;
extern float E1_MaxY;

extern int StageMap[MAP_Y][MAP_X];
extern Block m_block[100];
extern int blockcnt;

// �}�g���b�N�X
extern MATRIX WeaponMatrix;

