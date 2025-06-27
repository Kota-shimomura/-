#ifdef WINDOWS_PC
#include    "C:/project/libs/systemOZ_v4/soz.h"
#else
#include    "D:/project/guardians_2dx/proj.win32/src/systemOZ/soz.h"
#endif

#include    "C:/project/bace/src/game/game_include.h"

SINT32 seq_data[] =
{
	NEXT_STAGE,
#if 0
//#ifdef DEBUG	// ����e�X�g�p
	NEXT_WAVE,
	SEQ_WARNING,
	WAIT_TIME( 30 * 10 ),
	SUMMON_BOSS,	// �{�X�̏o��
	NEXT_WAVE,
#else
	NEXT_WAVE,
/// STAGE 01	/ ���i���Ă���G�̂�
	ENE_MOVE( 1 ),			// �o������G�̓���
	FORMATION( XR_Y ),		// �G�̏o���z�u
	ENE_GEN( 40, 5, 0 ),	// �G�̏o��
	FORMATION( X_Y ),		// �G�̏o���z�u
	ENE_GEN( 40, 5, 0 ),	// �G�̏o��
	FORMATION( XL_Y ),		// �G�̏o���z�u
	ENE_GEN( 40, 5, 0 ),	// �G�̏o��
	FORMATION( X2_YD ),		// �G�̏o���z�u
	ENE_GEN( 40, 5, 2 ),	// �G�̏o��


	FORMATION( X_Y2 ),			// �G�̏o���z�u
	ENE_GEN( 40, 5, 1 ),	// �G�̏o��
	FORMATION( X3_Y ),			// �G�̏o���z�u
	ENE_GEN( 40, 5, 2 ),	// �G�̏o��

	NEXT_WAVE,
	NEXT_STAGE,


/// STAGE 02	/ �~�T�C���������Ă���
	ENE_MOVE( 6 ),			// �o������G�̓���
	FORMATION( X2_Y ),			// �G�̏o���z�u
	ENE_GEN( 90, 3, 3 ),	// �G�̏o��

	FORMATION( X2_YU ),			// �G�̏o���z�u
	ENE_GEN( 90, 3, 4 ),	// �G�̏o��

	FORMATION( X2_YD ),			// �G�̏o���z�u
	ENE_GEN( 90, 3, 1 ),	// �G�̏o��

	FORMATION( XL_Y3 ),			// �G�̏o���z�u
	ENE_GEN( 90, 3, 4 ),	// �G�̏o��

	FORMATION( XR_Y3 ),			// �G�̏o���z�u
	ENE_GEN( 90, 3, 4 ),	// �G�̏o��

	NEXT_WAVE,
	NEXT_STAGE,

/// STAGE 03	/ �����������G
	ENE_MOVE( 4 ),			// �o������G�̓���
	FORMATION( XL_B ),			// �G�̏o���z�u
	ENE_GEN( 40, 8, 4 ),	// �G�̏o��

	ENE_MOVE( 5 ),			// �o������G�̓���
	FORMATION( XR_B ),			// �G�̏o���z�u
	ENE_GEN( 40, 8, 4 ),	// �G�̏o��

	ENE_MOVE( 2 ),			// �o������G�̓���
	FORMATION( X2_YU ),			// �G�̏o���z�u
	ENE_GEN( 40, 4, 2 ),	// �G�̏o��

	ENE_MOVE( 3 ),			// �o������G�̓���
	FORMATION( X2_YD ),			// �G�̏o���z�u
	ENE_GEN( 40, 4, 2 ),	// �G�̏o��

	ENE_MOVE( 4 ),			// �o������G�̓���
	FORMATION( XL_B ),			// �G�̏o���z�u
	ENE_GEN( 40, 4, 4 ),	// �G�̏o��

	ENE_MOVE( 2 ),			// �o������G�̓���
	FORMATION( X2_YU ),			// �G�̏o���z�u
	ENE_GEN( 40, 4, 2 ),	// �G�̏o��

	NEXT_WAVE,
	NEXT_STAGE,

/// STAGE 04	/ ��ʂ̓G
	ENE_MOVE( 1 ),			// �o������G�̓���
	FORMATION( XR_YU ),			// �G�̏o���z�u
	ENE_GEN( 10, 1, 0 ),	// �G�̏o��
	FORMATION( XR_Y ),			// �G�̏o���z�u
	ENE_GEN( 10, 1, 0 ),	// �G�̏o��
	FORMATION( XR_YD ),			// �G�̏o���z�u
	ENE_GEN( 10, 1, 0 ),	// �G�̏o��
	FORMATION( X_YD ),			// �G�̏o���z�u
	ENE_GEN( 10, 1, 0 ),	// �G�̏o��
	FORMATION( XL_YD ),			// �G�̏o���z�u
	ENE_GEN( 10, 1, 0 ),	// �G�̏o��
	FORMATION( XL_Y ),			// �G�̏o���z�u
	ENE_GEN( 10, 1, 0 ),	// �G�̏o��
	FORMATION( XL_YU ),			// �G�̏o���z�u
	ENE_GEN( 10, 1, 0 ),	// �G�̏o��
	FORMATION( X_YU ),			// �G�̏o���z�u
	ENE_GEN( 10, 1, 0 ),	// �G�̏o��

	WAIT_TIME( 20 ),
	ENE_MOVE( 4 ),			// �o������G�̓���
	FORMATION( XL_B ),			// �G�̏o���z�u
	ENE_GEN( 40, 4, 4 ),	// �G�̏o��
	ENE_MOVE( 5 ),			// �o������G�̓���
	FORMATION( XR_B ),			// �G�̏o���z�u
	ENE_GEN( 40, 4, 4 ),	// �G�̏o��

	ENE_MOVE( 6 ),			// �o������G�̓���
	FORMATION( XL2_YU ),			// �G�̏o���z�u
	ENE_GEN( 40, 4, 3 ),	// �G�̏o��
	FORMATION( XR2_YD ),			// �G�̏o���z�u
	ENE_GEN( 40, 4, 3 ),	// �G�̏o��


	ENE_MOVE( 6 ),			// �o������G�̓���
	FORMATION( XR_YU ),			// �G�̏o���z�u
	ENE_GEN( 10, 1, 0 ),	// �G�̏o��
	FORMATION( XR_Y ),			// �G�̏o���z�u
	ENE_GEN( 10, 1, 0 ),	// �G�̏o��
	FORMATION( XR_YD ),			// �G�̏o���z�u
	ENE_GEN( 10, 1, 0 ),	// �G�̏o��
	FORMATION( X_YD ),			// �G�̏o���z�u
	ENE_GEN( 10, 1, 0 ),	// �G�̏o��
	FORMATION( XL_YD ),			// �G�̏o���z�u
	ENE_GEN( 10, 1, 0 ),	// �G�̏o��
	FORMATION( XL_Y ),			// �G�̏o���z�u
	ENE_GEN( 10, 1, 0 ),	// �G�̏o��
	FORMATION( XL_YU ),			// �G�̏o���z�u
	ENE_GEN( 10, 1, 0 ),	// �G�̏o��
	FORMATION( X_YU ),			// �G�̏o���z�u
	ENE_GEN( 10, 1, 0 ),	// �G�̏o��

	NEXT_WAVE,
	NEXT_STAGE,

// STAGE 05 BOSS
	SEQ_WARNING,
	WAIT_TIME( 60 * 5 ),
	SUMMON_BOSS,	// �{�X�̏o��
#endif
	WAIT_TIME( 60 * 60 * 60 ),
	WAIT_TIME( 60 * 60 * 60 ),
	WAIT_TIME( 60 * 60 * 60 ),
	WAIT_TIME( 60 * 60 * 60 ),
	SEQ_TOP,
};


void summon_formation( SINT32 formation_id, SINT32 move_id, SINT32 skin_id )
{
	switch( formation_id )
	{
		case XR_YD:			//�@X�E		Y��
		enemy_disp( move_id, skin_id, 700, -500, 30000, 250, 500 );
			break;

		case X_YD:			//�@X���S	Y��
		enemy_disp( move_id, skin_id, 0, -500, 30000, 250, 500 );
			break;

		case XL_YD:			//�@X��		Y��
		enemy_disp( move_id, skin_id, -700, -500, 30000, 250, 500 );
			break;

		case XR_Y:			//�@X�E		Y���S
		enemy_disp( move_id, skin_id, 700, 0, 30000, 250, 500 );
			break;

		case X_Y:			//�@X���S	Y���S
		enemy_disp( move_id, skin_id, 0, 0, 30000, 250, 500 );
			break;

		case XL_Y:			//�@X��		Y���S
		enemy_disp( move_id, skin_id, -700, 0, 30000, 250, 500 );
			break;

		case XR_YU:			//�@X�E		Y��
		enemy_disp( move_id, skin_id, 700, 500, 30000, 250, 500 );
			break;

		case X_YU:			//�@X���S	Y��
		enemy_disp( move_id, skin_id, 0, 500, 30000, 250, 500 );
			break;

		case XL_YU:			//�@X��		Y��
		enemy_disp( move_id, skin_id, -700, 500, 30000, 250, 500 );
			break;


		case XR2_YD:			//	X�E�Q	Y��
		enemy_disp( move_id, skin_id, 700, -500, 30000, 250, 500 );
		enemy_disp( move_id, skin_id, 0, -500, 30000, 250, 500 );
			break;

		case X2_YD:		//	X�T�C�h	Y��
		enemy_disp( move_id, skin_id, 700, -500, 30000, 250, 500 );
		enemy_disp( move_id, skin_id, -700, -500, 30000, 250, 500 );
			break;

		case XL2_YD:		//	X���Q	Y��
		enemy_disp( move_id, skin_id, 0, -500, 30000, 250, 500 );
		enemy_disp( move_id, skin_id, -700, -500, 30000, 250, 500 );
			break;

		case XR2_Y:		//	X�E�Q	Y���S
		enemy_disp( move_id, skin_id, 700, 0, 30000, 250, 500 );
		enemy_disp( move_id, skin_id, 0, 0, 30000, 250, 500 );
			break;

		case X2_Y:		//	X�T�C�h	Y���S
		enemy_disp( move_id, skin_id, 700, 0, 30000, 250, 500 );
		enemy_disp( move_id, skin_id, -700, 0, 30000, 250, 500 );
			break;

		case XL2_Y:		//	X���Q	Y���S
		enemy_disp( move_id, skin_id, 0, 0, 30000, 250, 500 );
		enemy_disp( move_id, skin_id, -700, 0, 30000, 250, 500 );
			break;

		case XR2_YU:		//	X�E�Q	Y��
		enemy_disp( move_id, skin_id, 700, 500, 30000, 250, 500 );
		enemy_disp( move_id, skin_id, 0, 500, 30000, 250, 500 );
			break;

		case X2_YU:			//	X�T�C�h	Y��
		enemy_disp( move_id, skin_id, 700, 500, 30000, 250, 500 );
		enemy_disp( move_id, skin_id, -700, 500, 30000, 250, 500 );
			break;

		case XL2_YU:		//	X���Q	Y��
		enemy_disp( move_id, skin_id, 0, 500, 30000, 250, 500 );
		enemy_disp( move_id, skin_id, -700, 500, 30000, 250, 500 );
			break;

		case XR_YD2:		//	X�E	Y��2
		enemy_disp( move_id, skin_id, 700, -500, 30000, 250, 500 );
		enemy_disp( move_id, skin_id, 700, 0, 30000, 250, 500 );
			break;

		case X_YD2:			//	X���S	Y��2
		enemy_disp( move_id, skin_id, 0, -500, 30000, 250, 500 );
		enemy_disp( move_id, skin_id, 0, 0, 30000, 250, 500 );
			break;

		case XL_YD2:		//	X��	Y��2
		enemy_disp( move_id, skin_id, -700, -500, 30000, 250, 500 );
		enemy_disp( move_id, skin_id, -700, 0, 30000, 250, 500 );
			break;

		case XR_Y2:			//	X�E	Y�T���h
		enemy_disp( move_id, skin_id, 700, -500, 30000, 250, 500 );
		enemy_disp( move_id, skin_id, 700, 500, 30000, 250, 500 );
			break;

		case X_Y2:			//	X���S	Y�T���h
		enemy_disp( move_id, skin_id, 0, -500, 30000, 250, 500 );
		enemy_disp( move_id, skin_id, 0, 500, 30000, 250, 500 );
			break;

		case XL_Y2:			//	X��	Y�T���h
		enemy_disp( move_id, skin_id, -700, -500, 30000, 250, 500 );
		enemy_disp( move_id, skin_id, -700, 500, 30000, 250, 500 );
			break;

		case XR_YU2:		//	X�E	Y��2
		enemy_disp( move_id, skin_id, 700, 0, 30000, 250, 500 );
		enemy_disp( move_id, skin_id, 700, 500, 30000, 250, 500 );
			break;

		case X_YU2:			//	X���S	Y��2
		enemy_disp( move_id, skin_id, 0, 0, 30000, 250, 500 );
		enemy_disp( move_id, skin_id, 0, 500, 30000, 250, 500 );
			break;

		case XL_YU2:		//	X��	Y��2
		enemy_disp( move_id, skin_id, -700, 0, 30000, 250, 500 );
		enemy_disp( move_id, skin_id, -700, 500, 30000, 250, 500 );
			break;

		case X3_Y:	// Y���W�̐^�񒆂ɉ����ɂR�̓G������
		enemy_disp( move_id, skin_id, 700, 0, 30000, 250, 500 );
		enemy_disp( move_id, skin_id, 0, 0, 30000, 250, 500 );
		enemy_disp( move_id, skin_id, -700, 0, 30000, 250, 500 );
			break;

		case X3_YU:	// ��������ɉ����ɂR�̓G������
			enemy_disp( move_id, skin_id, 700, -500, 30000, 250, 500 );
			enemy_disp( move_id, skin_id, 0, -500, 30000, 250, 500 );
			enemy_disp( move_id, skin_id, -700, -500, 30000, 250, 500 );
			break;

		case X3_YD:	// ������艺�ɉ����ɂR�̓G������
			enemy_disp( move_id, skin_id, 700, 500, 30000, 250, 500 );
			enemy_disp( move_id, skin_id, 0, 500, 30000, 250, 500 );
			enemy_disp( move_id, skin_id, -700, 500, 30000, 250, 500 );
			break;

		case X_Y3: // �^�񒆂ɏc���ɂR�̓G������
			enemy_disp( move_id, skin_id, 0, 0, 30000, 250, 500 );
			enemy_disp( move_id, skin_id, 0, -500, 30000, 250, 500 );
			enemy_disp( move_id, skin_id, 0, 500, 30000, 250, 500 );
			break;

		case XR_Y3: // �E���ɏc���ɂR�̓G������
			enemy_disp( move_id, skin_id, 700, 0, 30000, 250, 500 );
			enemy_disp( move_id, skin_id, 700, -500, 30000, 250, 500 );
			enemy_disp( move_id, skin_id, 700, 500, 30000, 250, 500 );
			break;

		case XL_Y3: // �����ɏc���ɂR�̓G������
			enemy_disp( move_id, skin_id, -700, 0, 30000, 250, 500 );
			enemy_disp( move_id, skin_id, -700, -500, 30000, 250, 500 );
			enemy_disp( move_id, skin_id, -700, 500, 30000, 250, 500 );
			break;

		case 33:	// ���@�̍����ɓG����̏���
			enemy_disp( move_id, skin_id, -1600, 0, -5000, 100, 400 );
			break;

		case 34:	// ���@�̉E���ɓG����̏���
			enemy_disp( move_id, skin_id, 1600, 0, -5000, 100, 400 );
			break;

/*
	case 8:	// �G���T�̏���
		enemy_disp( move_id, skin_id, -700, -500, 30000, 250, 500 );
		enemy_disp( move_id, skin_id, -700, 500, 30000, 250, 500 );
		enemy_disp( move_id, skin_id, 0, 0, 30000, 250, 500 );
		enemy_disp( move_id, skin_id, 700, -500, 30000, 250, 500 );
		enemy_disp( move_id, skin_id, 700, 500, 30000, 250, 500 );
		break;
*/
	case 999:	// �e�X�g�p
		enemy_disp( move_id, skin_id, 0, 0, 30000, 250, 1 );
		break;
	}
}

void enemy_gen_exec( TASK *ap )
{
	ap->work2[ X ]--;
	if( ap->work3[ X ] <= 0 )	// �w�萔�G�𔭐���������^�X�N�G���h����B
	{
		TASK_end( ap );
		return;
	}
	else if( ap->work2[ X ] <= 0 )	// ����̎��Ԍo�߂�����
	{
		if( ap->work3[ X ] > 0 )	// �w�萔�G�𔭐������Ă��Ȃ��ꍇ
		{
			summon_formation( ap->work1[ X ], ap->work1[ Y ], ap->work1[ Z ] );
			ap->work3[ X ]--;					// �G�𔭐���������J�E���g�_�E������ 
			ap->work2[ X ] = ap->work2[ Y ];					// �G�𔭐������Ă�l������������
		}
	}
	if( life == 0 )		// ���@�̎c��Ȃ��Ȃ�����^�X�N������
	{
		TASK_end( ap );
		return;
	}
}

void enemy_gen( SINT32 ct, SINT32 summon_num, SINT32 formation_id, SINT32 move_id, SINT32 skin_id )
{
	TASK *ap;
	ap = TASK_start( enemy_gen_exec, GROUP_UI, "�G�̃W�F�l���[�^�[" );
	ap->work1[ X ] = formation_id;
	ap->work1[ Y ] = move_id;
	ap->work1[ Z ] = skin_id;
// �G�̔����̃N�[���^�C��
	ap->work2[ X ] = 0;
	ap->work2[ Y ] = ct;
// �G�̘A��������
	ap->work3[ X ] = summon_num;
}



void annihilation_check( TASK *ap )		// �G���c���Ă��邩���m�F
{

}

void enemy_seq_exec( TASK *ap )
{
	TASK *actp;
	SINT32 time;
	SINT32 ct, summon_num, formation_id, move_id, skin_id;
	ap->work1[Y]--;
	if( ap->work1[ Y ] > 0 )	// WAIT TIME �v�Z
		return;

	if( life <= 0 )				// GAME OVER �ɂȂ�����^�X�N�G���h������
	{
		TASK_end( ap );
		return;
	}

	if( game_type == TYPE_CLEAR || game_type == TYPE_OVER )		// ���U���g��ʂɔ�񂾂炱�̃^�X�N������
	{
		TASK_end( ap );
		return;
	}


	switch ( *ap->work_p[X]++ )
	{
		case SEQ_WAIT:	// wait time�̐ݒ�
			time = *ap->work_p[ X ]++;
			ap->work1[ Y ] = time;
			break;

		case SEQ_TOP:	// �V�[�P���X���ŏ��ɖ߂�
			ap->work_p[ X ] = ap->work_p[ Y ];
			break;

		case SEQ_FORMATION:	// �G�̔z�u�ԍ��̎w��
			ap->workF[ P ] = *ap->work_p[ X ]++;
			break;

		case SEQ_ENE_MOVE:	// �G�̓����̐ݒ�
			ap->workF[ D ] = *ap->work_p[ X ]++;
			break;

		case SEQ_ANNIHILATION: // �G�̑S�Ŋm�F
			for( actp = ap_start; actp != NULL; actp = actp->next )
				if( actp->task_group == GROUP_ENEMY )
				{
					ap->work_p[ X ]--;
					return;
				}
			break;

		case SEQ_ENE_GEN:	// �G�̏o��
			ct = *ap->work_p[ X ]++;
			summon_num = *ap->work_p[ X ]++;
			formation_id = ap->workF[ P ];
			move_id = ap->workF[ D ];
			skin_id = *ap->work_p[ X ]++;
			ap->work1[ Y ] = ct * summon_num + 60;
			enemy_gen( ct, summon_num, formation_id, move_id, skin_id );	// �G�̑��񏢊�
			break;

		case SEQ_WARNING:
			warning();
			break;

		case SEQ_BOSS:	// �{�X�������������ƁA�V�[�P���X���^�X�N�G���h������
			boss_logo();
//			boss_start();		// �{�X�̏���
			TASK_end( ap );
			return;
			break;

		case SEQ_NEXT_STAGE:
			switch( Rand2( 0, 4 ) )
			{
			case 0:
				planet_start(  -5700,  -5780, 32000,   5, Rand2( 0, 3 ), 1.0f );
				break;
			case 1:
				planet_start( -10000,   9000, 34000,   4, Rand2( 0, 3 ), 1.0f );
				break;
			case 2:
				planet_start(   9000,  -9470, 36000,   4, Rand2( 0, 3 ), 1.0f );
				break;
			case 3:
				planet_start(  -5700,   6980, 38000,   5, Rand2( 0, 3 ),  1.0f );
				break;
			}

			stage++;
			break;
	}
}
void enemy_seq( void )
{
	TASK *ap;
	ap = TASK_start( enemy_seq_exec, GROUP_UI, "�V�[�P���X" );
	ap->work_p[ X ] = seq_data;
	ap->work_p[ Y ] = ap->work_p[ X ];
	ap->work1[ Y ] = 0;

// �t�H�[���[�V�����i���o�[�ۑ���
	ap->workF[ P ] = 0;
// �G�̓����̔ԍ��ۑ���
	ap->workF[ D ] = 0;

// �w�i�̗���鑬�x��������
	bg_speed = 1;
}