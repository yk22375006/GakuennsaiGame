#include <DxLib.h>
#include "Common.h"

// ------------------------------------------------------------------------ //
//						�A�j���[�V�����̏����Z�b�g							//
// ------------------------------------------------------------------------ //
void AnimationInit() {
	// -------------------------------- // 
	//		�A�j���[�V�����̓ǂݍ���	//
	// -------------------------------- //
/*	if (chara_type1 == SPEEDMODE) {
		player[0].anim.stop = MV1LoadModel("..\\Data\\Ninja\\�E��_�ꖳ_�ҋ@.mv1");			// �����A�j��
		player[0].anim.run = MV1LoadModel("..\\Data\\Ninja\\�E��_�ꖳ_�ړ�.mv1");			// ����A�j��
		player[0].anim.jump_in = MV1LoadModel("..\\Data\\Ninja\\�E��_�ꖳ_�W�����v�J�n.mv1");	// �W�����v����n�߃A�j��
		player[0].anim.jump = MV1LoadModel("..\\Data\\Ninja\\�E��_�ꖳ_�W�����v��.mv1");	// �W�����v���[�v�A�j��
		player[0].anim.fall = MV1LoadModel("..\\Data\\Ninja\\�E��_�ꖳ_����.mv1");			// �W�����v���[�v�A�j��
		player[0].anim.attack = MV1LoadModel("..\\Data\\Ninja\\�E��_�ꖳ_�U��.mv1");			// �U���A�j��
		player[0].anim.damage = MV1LoadModel("..\\Data\\Ninja\\�E��_�ꖳ_�_���[�W.mv1");		// ��_���[�W�A�j��
	}*/
}

// ------------------------------------------------------------------------ //
//						�v���C���[�̃A�j���[�V����							//
// ------------------------------------------------------------------------ //
void AnimationPlayer( int Animation ) {
	MV1DetachAnim(player[0].anim.model, player[0].GetAnim_Attach());
	switch (Animation) {
		// ������Ԃ̏���
		case STAND:
			player[0].SetAnim_Attach(MV1AttachAnim(player[0].anim.model, 0, player[0].anim.stop));
			player[0].SetAct_Mode(STAND) ;
			break;

		//�����Ԃ̏���
		case RUN:
			player[0].SetAnim_Attach( MV1AttachAnim(player[0].anim.model, 0, player[0].anim.run));
			player[0].SetAct_Mode(RUN) ;
			break;

		// �W�����v�J�n���̏���
		case JUMPIN :
			player[0].SetAnim_Attach( MV1AttachAnim(player[0].anim.model ,0, player[0].anim.jump_in));
			player[0].SetAct_Mode(JUMPIN) ;
			break;

		// �W�����v���̏���
		case JUMPLOOP :
			player[0].SetAnim_Attach( MV1AttachAnim(player[0].anim.model, 0, player[0].anim.jump));
			player[0].SetAct_Mode(JUMPLOOP) ;
			break;

		// �W�����v�I�����̏���
		case JUMPOUT :
			player[0].SetAnim_Attach( MV1AttachAnim(player[0].anim.model, 0, player[0].anim.jump_out));
			player[0].SetAct_Mode(JUMPOUT) ;
			break;

		// �U�����̏���
		case ATTACK :
			player[0].SetAnim_Attach( MV1AttachAnim(player[0].anim.model, 0, player[0].anim.attack));
			player[0].SetAct_Mode(ATTACK);
			break;
	}
	player[0].SetAnim_Time( MV1GetAttachAnimTotalTime(player[0].anim.model, player[0].GetAnim_Attach()));
}



