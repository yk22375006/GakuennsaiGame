#include <DxLib.h>
#include "Common.h"

// ------------------------------------------------------------------------ //
//						�A�j���[�V�����̏����Z�b�g							//
// ------------------------------------------------------------------------ //
void AnimationInit() {
	// -------------------------------- // 
	//		�A�j���[�V�����̓ǂݍ���	//
	// -------------------------------- //
	plyanim_nutral = MV1LoadModel("..\\Data\\Player\\Anim_Neutral.mv1");		// �����A�j��
	plyanim_run = MV1LoadModel("..\\Data\\Player\\Anim_Run.mv1");				// ����A�j��	
	plyanim_jumpin = MV1LoadModel("..\\Data\\Player\\Anim_Jump_In.mv1");		// �W�����v����n�߃A�j��
	plyanim_jumploop = MV1LoadModel("..\\Data\\Player\\Anim_Jump_Loop.mv1");	// �W�����v���[�v�A�j��
	plyanim_jumpout = MV1LoadModel("..\\Data\\Player\\Anim_Jump_Out.mv1");		// �W�����v���n�A�j��
	plyanim_attack = MV1LoadModel("..\\Data\\Player\\Anim_Attack1.mv1");		// �U���A�j��

	gobanim_ntural = MV1LoadModel("..\\Data\\Goblin\\Anim_Neutral.mv1");		// �S�u�����̗����A�j���[�V����
	gobanim_blowin = MV1LoadModel("..\\Data\\Goblin\\Anim_Blow_In.mv1");		// �S�u�����̃_���[�W�J�n�A�j��
	gobanim_blowloop = MV1LoadModel("..\\Data\\Goblin\\Anim_Blow_Loop.mv1");	// �S�u�����̃_���[�W���A�j��
	gobanim_blowloop = MV1LoadModel("..\\Data\\Goblin\\Anim_Blow_Out.mv1");		// �S�u�����̃_���[�W�I����A�j��

}

// ------------------------------------------------------------------------ //
//						�v���C���[�̃A�j���[�V����							//
// ------------------------------------------------------------------------ //
void AnimationPlayer( int Animation ) {
	MV1DetachAnim(Player[0].model, Player[0].attachidx);
	switch (Animation) {
		// ������Ԃ̏���
		case STAND:
			Player[0].attachidx = MV1AttachAnim(Player[0].model, 0, plyanim_nutral);
			Player[0].mode = STAND;
			break;

		//�����Ԃ̏���
		case RUN:
			Player[0].attachidx = MV1AttachAnim(Player[0].model, 0, plyanim_run);
			Player[0].mode = RUN;
			break;

		// �W�����v�J�n���̏���
		case JUMPIN :
			Player[0].attachidx = MV1AttachAnim(Player[0].model, 0, plyanim_jumpin);
			Player[0].mode = JUMPIN;
			break;

		// �W�����v���̏���
		case JUMPLOOP :
			Player[0].attachidx = MV1AttachAnim(Player[0].model, 0, plyanim_jumploop);
			Player[0].mode = JUMPLOOP;
			break;

		// �W�����v�I�����̏���
		case JUMPOUT :
			Player[0].attachidx = MV1AttachAnim(Player[0].model, 0, plyanim_jumpout);
			Player[0].mode = JUMPOUT;
			break;

		// �U�����̏���
		case ATTACK :
			Player[0].attachidx = MV1AttachAnim(Player[0].model, 0, plyanim_attack);
			Player[0].mode = ATTACK;
			break;
	}
	Player[0].anim_totaltime = MV1GetAttachAnimTotalTime(Player[0].model, Player[0].attachidx);
}

// ------------------------------------------------------------------------ //
//						�G�l�~�[�̃A�j���[�V����							//
// ------------------------------------------------------------------------ //
void AnimationEnemy(int Animation) {
	MV1DetachAnim(Player[1].model, Player[1].attachidx);
	switch (Animation) {
		// ������Ԃ̏���
		case E_STAND:
			Player[1].attachidx = MV1AttachAnim(Player[1].model, 0, gobanim_ntural);
			Player[1].mode = E_STAND;
			break;

		// �_���[�W�𕉂��J�n���̏���
		case E_BLOWIN :
			Player[1].attachidx = MV1AttachAnim(Player[1].model, 0, gobanim_blowin);
			Player[1].mode = E_BLOWIN;
			break;


		// �_���[�W���̏���
		case E_BLOWLOOP :
			Player[1].attachidx = MV1AttachAnim(Player[1].model, 0, gobanim_blowloop);
			Player[1].mode = E_BLOWLOOP;
			break;

		// �_���[�W�I�����̏���
		case E_BLOWOUT :
			Player[1].attachidx = MV1AttachAnim(Player[1].model, 0, gobanim_blowout);
			Player[1].mode = E_BLOWOUT;
			break;
	}
	Player[1].anim_totaltime = MV1GetAttachAnimTotalTime(Player[0].model, Player[0].attachidx);

}



