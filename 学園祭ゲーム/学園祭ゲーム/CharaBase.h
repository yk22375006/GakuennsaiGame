
/* -------------------------------------------------------- +
 |                                                          |6
 |                        CharaBase.h                       |
 |                                                          |
 + -------------------------------------------------------- */
enum CharaMode {
	eCharaStop ,		// ��~��
	eCharaMove ,		// �ړ�	
	eCharaAttack,		// �U��
	eCharaJump,			// �W�����v
	eCharaFall,			// ����
	eCharaDamage,		// �_���[�W
	eCharaDown			// �_�E��
} ;

enum Direction {
	DOWN ,		// ������
	LEFT ,		// ������
	UP ,		// �����
	RIGHT ,		// �E����
} ;



class CharaBase {
	protected :
		VECTOR posi ;			// �ʒu���
		VECTOR spd ;			// �X�s�[�h
		int use_flg ;			// �g�p�t���O
		int act_mode ;			// �A�N�V�������[�h
		float direction ;		// ����
		int motion ;			// ���݂̃A�j�����[�V����
		int anim_attach ;		// ���݂̃A�j���[�V�������i�[
		float anim_time ;		// �A�j���[�V�����̑����Ԃ��i�[
		float play_time ;		// �A�j���[�V�����̍Đ�����
		int rootflm ;			// �A�j���[�V����+�ړ��\�ɂ���
		float Width ;			// �v���C���[�T�C�Y��(�q�b�g�`�F�b�N�p)
		float Height ;			// �v���C���[�T�C�Y����(�q�b�g�`�F�b�N�p)
		int hp ;
		int number;				// �v���C���[�ԍ�

	public :
		CharaBase( ) ;			// �R���X�g���N�^
		~CharaBase( ) ;			// �f�X�g���N�^
		int init( ) ;			// �����Z�b�g
		int MoveSet( ) ;		// �ړ��ʂ��Z�b�g
		AnimationDate anim ;	// �A�j���[�V�����f�[�^

		// --- �C�����C���֐� ---
		// �g�p�t���O�擾�Z�b�g
		int GetUse_Flg( ) {
			return use_flg ;
		} ;

		void SetUse_Flg( int set_flg ) {
			use_flg = set_flg ;
		} ;

		// �ʒu���
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

		// �X�s�[�h
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

		// �A�N�V�������[�h
		int GetAct_Mode( ) {
			return act_mode ;
		}

		void SetAct_Mode( int set_mode ) {
			act_mode = set_mode ;
		}

		// ����
		float GetDirection( ) {
			return direction ;
		}

		void SetDiection( float set_direction ) {
			direction = set_direction ;
		}

		// �A�^�b�`�A�j���[�V����
		int GetAnim_Attach( ) {
			return anim_attach ;
		}

		void SetAnim_Attach( int set_anim ) {
			anim_attach = set_anim ;
		}		

		// �A�j���[�V����������
		float GetAnim_Time( ) {
			return anim_time ;
		}

		void SetAnim_Time( float set_time ) {
			anim_time = set_time ;
		}

		// �A�j���[�V�����Đ�����
		float GetPlay_Time( ) {
			return play_time ;
		}

		void SetPlay_Time( float set_time ) {
			play_time = set_time ;
		}

		void AddPlay_Time( float add_time ) {
			play_time += add_time ;
		}

		// �v���C���[�T�C�Y��
		float GetWidth() {
			return Width;
		}

		// �v���C���[�T�C�Y��
		void SetWidth( float width ) {
			Width = width;
		}

		// �v���C���[�T�C�Y����
		float GetHeight() {
			return Height;
		}

		// �v���C���[�T�C�Y����
		void SetHeight( float height ) {
			Height = height;
		}

		// �A�j���[�V�����Đ�����
		int GetRootFlm( ) {
			return rootflm ;
		}

		void SetRootFlm( int set_flm ) {
			rootflm = set_flm ;
		}

		// �A�j���[�V�����Đ�����
		AnimationDate GetAnimation_Data( ) {
			return anim ;
		}

		// �A�j���[�V�����Đ�����
		void SetAnimation_Data( AnimationDate set_anim ) {
			anim = set_anim ;
		}

		// �A�j���[�V�����Đ�����
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

