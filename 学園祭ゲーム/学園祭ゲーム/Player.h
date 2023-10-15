
/* -------------------------------------------------------- +
 |                                                          |
 |                         Player.h                         |
 |                                                          |
 + -------------------------------------------------------- */
class Player : public CharaBase {
	public :
		Player( ) ;					// �R���X�g���N�^
		~Player( ) ;				// �f�X�g���N�^
		int init( ) ;				// �����Z�b�g
		int Draw( CharaBase *pp1 ) ;	// �`��
		int AllowKey( ) ;			// ���L�[��������Ă邩

		// �A�j���[�V�����֐�
		int LoadAnimation( CharaBase* pp1 ) ;				// �A�j���[�V�����ǂݍ���
		int AnimationInit( ) ;				// �A�j���[�V���������Z�b�g
		int Animation( CharaBase *pp1 ) ;	// �A�j���[�V�����Đ�
		int ChangeAnimation( CharaBase *pp1 , int set_anim ) ;	// �A�j���[�V�����؂�ւ�
		int AnimationType(CharaBase* pp1);						// �^�C�v�ʃA�j���[�V�����Đ�
		int ChangeAnimationType(CharaBase* pp1, int set_anim);	// �^�C�v�ʃA�j���[�V�����؂�ւ�

		// �L�����`���C�X
		void CharaChoice(CharaBase* pp1) ;						// �L�����I��

		// �A�N�V�������[�h�֐�
		int ActionLoop( CharaBase *pp1 , CharaBase *pp2 ) ;		// �A�N�V�������[�v
		void CharaStop( CharaBase *pp1 , CharaBase* pp2 ) ;		// ��~��
		void CharaMove( CharaBase *pp1 , CharaBase* pp2 ) ;		// �ړ�
		void CharaAttack( CharaBase *pp1 , CharaBase* pp2 ) ;	// �U��
		void CharaDamage( CharaBase *pp1 , CharaBase* pp2 ) ;	// �_���[�W
		void CharaDown( CharaBase* pp1, CharaBase* pp2);		// �_�E��
		void CharaJump( CharaBase* pp1, CharaBase* pp2);		// �W�����v�����ݒ�
		void CharaFall(CharaBase* pp1, CharaBase* pp2);			// ����
		void CharaRevival(CharaBase* pp1, CharaBase* pp2);		// ����

		// �q�b�g�`�F�b�N
		void Move_HitCheck(CharaBase* pp1, CharaBase* pp2);
		void Block_HitCheck(CharaBase* pp1);
		void Revival_HitCheck(CharaBase* pp1);

} ;

