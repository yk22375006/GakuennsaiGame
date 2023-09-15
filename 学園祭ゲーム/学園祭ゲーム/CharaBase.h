/* -----------------------------------------------------------------------------------------
|																						   |
|								�L�����N�^�[��DEFINE�錾								   |
|																						   |
+ --------------------------------------------------------------------------------------- */
// �L�����T�C�Y
#define PC_WIDTH 80.0f
#define PC_HEIGHT 180.0f


#define EFFECT_SLASH_WIDTH_MAX 15
#define EFFECT_SLASH_WIDTH_MIN 1
#define EFFECT_SLASH_WIDTH_FRAME 3
#define EFFECT_SLASH_WIDTH_SIZE 200
#define EFFECT_SLASH_HEIGHT_SIZE 200

#define EFFECT_SLASH_RADIAN 315

#define CHARA_ENUM_DEFAULT_SIZE		500.0f		// ���͂̃|���S�����o�Ɏg�p���鋅�̏����T�C�Y
#define CHARA_MAX_HITCOLL			2048		// ��������R���W�����|���S���̍ő吔

#define CHARA_HIT_HEIGHT			700.0f		// �����蔻��J�v�Z���̍���

// �L�����N�^�[�̃f�[�^�t�@�C�����i�[����Ă���t�H���_
#define CHARADATA_DIR					"..\\Data\\Data\\Character\\"
/* -----------------------------------------------------------------------------------------
|																						   |
|								     CHARA�̍\���̐錾									   |
|																						   |
+ --------------------------------------------------------------------------------------- */
// �L�����N�^�[�̓����蔻��̏��
typedef struct _SCharaHitInfo
{
	// �����蔻��̕�
	float                 Width;

	// �����蔻��̍���
	float                 Height;

	// �����蔻��̒��S���W
	VECTOR                CenterPosition;
} SCharaHitInfo;

// �L�������\����
typedef struct _CharaInfo{
	int				model ;				// �L�����̃��f�����i�[
	int				mode ;				// �L�����̏��
	int				attachidx ;			// �L�����̌��݂̃A�j���[�V�������i�[�i�A�^�b�`�j
	float			anim_totaltime ;	// �A�j���̃g�[�^���A�j��
	float			playtime ;			// �A�j���Đ�����
	int				rootflm ;			// �A�j���̃��[�g
	VECTOR			pos ;				// �L�����̍��W x,y,z
	VECTOR			move ;				// �L�����̈ړ��� x,y,z
	float			direction ;			// �L�����̌���
	SCharaHitInfo	charahitinfo ;		// �L�����q�b�g�`�F�b�N�p���

} SCharaInfo ;

typedef struct _WeaponInfo {
	int				model;
	VECTOR			pos;
	SCharaHitInfo	weaponhitinfo;
} SWeaponInfo ;


