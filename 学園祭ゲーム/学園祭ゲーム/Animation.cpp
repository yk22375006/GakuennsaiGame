#include <DxLib.h>
#include "Common.h"

// ------------------------------------------------------------------------ //
//						�A�j���[�V�����̏����Z�b�g							//
// ------------------------------------------------------------------------ //
void AnimationInit() {
	// -------------------------------- // 
	//		�A�j���[�V�����̓ǂݍ���	//
	// -------------------------------- //
	player[0].anim.stop = MV1LoadModel("..\\Data\\Ninja\\�E��_�ꖳ_�ҋ@.mv1");		// �����A�j��
	player[0].anim.run = MV1LoadModel("..\\Data\\Ninja\\�E��_�ꖳ_�ړ�.mv1");		// ����A�j��	
	player[0].anim.jimp_in = MV1LoadModel("..\\Data\\Player\\Anim_Jump_In.mv1");	// �W�����v����n�߃A�j��
	player[0].anim.jump = MV1LoadModel("..\\Data\\Player\\Anim_Jump_Loop.mv1");		// �W�����v���[�v�A�j��
	player[0].anim.jump_out = MV1LoadModel("..\\Data\\Player\\Anim_Jump_Out.mv1");	// �W�����v���n�A�j��
	player[0].anim.attack = MV1LoadModel("..\\Data\\Player\\Anim_Attack1.mv1");		// �U���A�j��
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
			player[0].SetAnim_Attach( MV1AttachAnim(player[0].anim.model ,0, player[0].anim.jimp_in));
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

// ------------------------------------------------------------------------ //
//						�G�l�~�[�̃A�j���[�V����							//
// ------------------------------------------------------------------------ //
void AnimationEnemy(int Animation) {
/*
	MV1DetachAnim(player[1].model, player[1].attachidx);
	switch (Animation) {
		// ������Ԃ̏���
		case E_STAND:
			player[1].attachidx = MV1AttachAnim(player[1].model, 0, gobanim_ntural);
			player[1].mode = E_STAND;
			break;

		// �_���[�W�𕉂��J�n���̏���
		case E_BLOWIN :
			player[1].attachidx = MV1AttachAnim(player[1].model, 0, gobanim_blowin);
			player[1].mode = E_BLOWIN;
			break;


		// �_���[�W���̏���
		case E_BLOWLOOP :
			player[1].attachidx = MV1AttachAnim(player[1].model, 0, gobanim_blowloop);
			player[1].mode = E_BLOWLOOP;
			break;

		// �_���[�W�I�����̏���
		case E_BLOWOUT :
			player[1].attachidx = MV1AttachAnim(player[1].model, 0, gobanim_blowout);
			player[1].mode = E_BLOWOUT;
			break;
	}
	player[1].anim_totaltime = MV1GetAttachAnimTotalTime(player[0].model, player[0].attachidx);
*/
}



