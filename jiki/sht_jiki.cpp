#ifdef WINDOWS_PC
#include    "C:/project/libs/systemOZ_v4/soz.h"
#else
#include    "D:/project/guardians_2dx/proj.win32/src/systemOZ/soz.h"
#endif

#include    "C:/project/bace/src/game/game_include.h"
TASK *jiki;
SINT32 life = 3;
SINT32 rest_missile = 0;	// �~�T�C���̎c�e��
SINT32 j_state_mode = 0;	// �A�i���O�X�e�B�b�N���g�p���邩
SINT32 missile_ok = 0;		// ���b�N�I����Ԃ����m
SINT32 shot_break_count = 0;		// �V���b�g�Ŕj�󂵂��G�̐����J�E���g����

SINT32 sphire_hit_check( TASK *ap, TASK *actp )				// ���ǂ����̔���m�F
{
	FLOAT sa_x, sa_y, sa_z;
	FLOAT length;

	sa_x = ap->pos[ X ] - actp->pos[ X ];
	sa_y = ap->pos[ Y ] - actp->pos[ Y ];
	sa_z = ap->pos[ Z ] - actp->pos[ Z ];
	length = ( FLOAT )sqrt( ( sa_x * sa_x ) + ( sa_y * sa_y ) + ( sa_z * sa_z ) );

	if( length <= ( ap->sphire + actp->sphire ) )
		return 1;

	return 0;
}

void shot_hit_check( TASK *ap )								// ���@�̍U���������Ă���q�b�g�m�F
{
	TASK *actp;
	for( actp = ap_start; actp != NULL; actp = actp->next )
		switch( actp->task_group )
		{
			case  GROUP_ENEMY:
				if( sphire_hit_check( ap, actp ) != 0 )
				{
					actp->callback( ap, actp );
					ap->callback( ap, actp );
				}
				break;
		}
}

void myship_hit_check( TASK *ap )							// ���@�{�̂����q�b�g�m�F
{
	TASK *actp;
	for( actp = ap_start; actp != NULL; actp = actp->next )
		switch( actp->task_group )			// �G�̖{�̂������͍U���ɓ���������
		{
			case GROUP_BULLET:
			case  GROUP_ENEMY:
				if( sphire_hit_check( ap, actp ) != 0 )
				{
					bullet_myship_hit_effect();		// ��ʂ��Ԃ��Ȃ�G�t�F�N�g
					ap->callback( ap, actp );
					bonus = 0;					// SCORE�{�[�i�X������������
				}
				break;
		}
}

//------------------------------------------------------------------------------------------------------------------------------------------------------
// ���@�~�T�C���@
//------------------------------------------------------------------------------------------------------------------------------------------------------

// ��ԋ߂��G��_���v���O����( �ꉞ���삷�� )
void missile_lock_on ( TASK *ap )
{
	TASK *actp, *tp{};
	FLOAT sa = 0, sa_x = 0, sa_y = 0, sa_z = 0;
	for( actp = ap_start; actp != NULL; actp = actp->next )	// �^�X�N�̑S�{��
		if( actp->task_group == GROUP_ENEMY )	// �^�X�N�O���[�v��GOUP_ENEMY�̂��̂�T��
		{
			// �~�T�C���ƓG�̋������v�Z
			sa_x = ( ap->pos[ X ] - actp->pos[ X ] ) * ( ap->pos[ X ] - actp->pos[ X ] );
			sa_y = ( ap->pos[ Y ] - actp->pos[ Y ] ) * ( ap->pos[ Y ] - actp->pos[ Y ] );
			sa_z = ( ap->pos[ Z ] - actp->pos[ Z ] ) * ( ap->pos[ Z ] - actp->pos[ Z ] );
			ap->fwork1[ X ] = FLOAT( sqrtf( sa_x + sa_y + sa_z ) );
			if( sa < ap->fwork1[ X ] && actp->pos[ Z ] < 20000 )		// ��ԋ������߂��G��_��
			{
				if( ap != jiki )
					target_lock_vec( ap, actp );
				tp = actp;
				sa = ap->fwork1[ X ];
			}
		}
	if( tp != NULL )
	{
			ms_lockon_effect( tp->pos[ X ], tp->pos[ Y ], tp->pos[ Z ] );		// ���b�N�I���G�t�F�N�g�̕\��
			if( ap == jiki && tp->pos[ Z ] < 20000.0f && tp->pos[ Z ] > 500.0f )
			{
				missile_ok = 1;
				ms_lockon_font( tp->pos[ X ], tp->pos[ Y ], tp->pos[ Z ] );		// ���b�N�I���֘A�̃t�H���g�̕\��
			}
			else
				missile_ok = 0;
	}
}

// ���@�~�T�C���̎��s����
void jiki_missile_exec( TASK *ap )
{
	ap->work2[ X ] ++;
// ���W�ړ�
	ap->pos[ X ] += ap->vec[ X ];
	ap->pos[ Y ] += ap->vec[ Y ];
	ap->pos[ Z ] += ap->vec[ Z ];

// ���莞�Ԍo�߂�����
	if( ap->work2[ X ] >= 150 )
	{
		TASK_end( ap );
		return;
	}

	shot_hit_check( ap );		// �q�b�g�m�F

	if( ap->work2[ X ] % 2 == 0 )	// ����t���[�����ƂɃ~�T�C���̃G�t�F�N�g�𔭐�������
		missile_effect( ap->pos[ X ], ap->pos[ Y ], ap->pos[ Z ] );
}
void jiki_missile( void )
{
	TASK *ap;
	ap = TASK_start_MODEL( jiki_missile_exec, GROUP_SHOT, MODEL_MISSILE, TEXTURE_MISSILE, "���@�̃~�T�C��" );
	ap->grp_mode = WRITE_ZBUFFER | TEST_ZBUFFER | USE_LIGHTING;
	ap->pos[ X ] = jiki->pos[ X ];
	ap->pos[ Y ] = jiki->pos[ Y ];
	ap->pos[ Z ] = jiki->pos[ Z ];
	ap->fwork1[ X ] = 9999.0f;
	ap->work2[ X ] = 0;
	ap->work2[ D ] = 1000;
	ap->sphire = 180.0f;
	ap->sphire_shift[ X ] = 0;
	ap->sphire_shift[ Y ] = 0;
	ap->sphire_shift[ Z ] = 0;
	ap->callback = missile_callback;
	ap->vec[ X ] = 0;
	ap->vec[ Y ] = 0;
	ap->vec[ Z ] = 250;
	ap->ATK = jiki->ATK * 6;
	ap->BONUS = 50;
	missile_start_effect( ap->pos[ X ], ap->pos[ Y ], ap->pos[ Z ] );			// �~�T�C�����˂̃G�t�F�N�g
	SOZ_play_se( SE_MISSILE, 3.0f, 1, 0.0f );
	missile_lock_on( ap );			// ��ԋ߂��G�����b�N�I��
}

//------------------------------------------------------------------------------------------------------------------------------------------------------
// ���@�V���b�g
//------------------------------------------------------------------------------------------------------------------------------------------------------
void shot_exec( TASK *ap )
{
	ap->work1[ X ] ++;
	if( ap->pos[ Z ] < 12000 )
	{
		shot_hit_check( ap );								// �q�b�g�m�F
	}

	if( ap->work1[ X ] % 2 == 0 )
		illusion_start( ap, 75, BLEND_ADD );
// ���W�ړ�
	ap->pos[ X ] += ap->vec[ X ];
	ap->pos[ Y ] += ap->vec[ Y ];
	ap->pos[ Z ] += ap->vec[ Z ];
// �˒������܂ňړ�������^�X�N�G���h������B
	if( ap->pos[ Z ] > 300000 )
	{
		TASK_end( ap );
		return;
	}
}
void shot( FLOAT pos_x, FLOAT pos_y,FLOAT pos_z )
{
	TASK *ap;
	ap = TASK_start_MODEL( shot_exec, GROUP_SHOT, MODEL_SHOT, TEXTURE_SHOT, "���@�̍U��" );
	ap->grp_mode = TEST_ZBUFFER;
	ap->pos[ X ] = pos_x;
	ap->pos[ Y ] = pos_y;
	ap->pos[ Z ] = pos_z;
	ap->pri = PRI_SHOT;
	shot_vec_setting( ap, 400 * 1.5f );
	ap->ang[ Z ] = Rand2( 0x0000, 0xffff );
	ap->sphire = 240.0f;
	ap->sphire_shift[ X ] = 0;
	ap->sphire_shift[ Y ] = 0;
	ap->sphire_shift[ Z ] = 0;
	ap->base_color[ 0 ][ 0 ] = 0xaa;
	ap->blend_type = BLEND_ADD;
	ap->work1[ X ];
	ap->ATK = jiki->ATK;
	ap->BONUS = 25;
	ap->callback = shot_callback;
	shot_effect_start( ap->pos[ X ], ap->pos[ Y ], ap->pos[ Z ] );
//	SOZ_play_se( SE_SHOT, 2.0f, 1, 1 );
}

//------------------------------------------------------------------------------------------------------------------------------------------------------
// ���@
//------------------------------------------------------------------------------------------------------------------------------------------------------

// ���G���ԗp�e�N�X�`���\��	/�����������������P���Ďg������
void my_ship_tex_chenge( TASK *ap )
{
	//ap->workB[ D ] = 0;				// ���G����
	//ap->workB[ P ] = 0;				// �ԓ_��
	ap->workB[ D ]++;
	if( ap->workB[ D ] % 20 == 0 )
	{
		if( ap->base_color[ 0 ][ 0 ] == 0x88 )
			ap->base_color[ 0 ][ 0 ] = 0xff;
		else
			ap->base_color[ 0 ][ 0 ] = 0x88;
	}

	if( ap->workA[ Y ] <= 0 )	// ���Ԍo�߂Ŗ��G����
	{
		ap->base_color[ 0 ][ 0 ] = 0xff;
		ap->workB[ D ] = 0;
	}
}

// �A�i���O�X�e�B�b�N�̒l���擾���A�X�s�[�h�̒l�ɕϊ�����
void state_chenge_speed( TASK *ap )
{
	if( demo_mode == 0 )
	{
		ap->VEC_X = FLOAT( j_state->lX ) / 20.0f;
		ap->VEC_Y = FLOAT( -j_state->lY ) / 20;
	}
	else
	{
		ap->VEC_X = FLOAT( button_lr ) / 20.0f;
		ap->VEC_Y = -FLOAT( button_ud ) / 20;
	}
}

void my_ship_cont( TASK *ap )	// ���@���͓���
{
	if( demo_mode == 0 )
		button_data_get();				// �{�^���̓��͎擾
// �ŏ��Ɉړ��x�N�g���̏�����
	ap->vec[ X ] = 0;
	ap->vec[ Y ] = 0;

// �A�i���O�X�e�B�b�N�̒l���X�s�[�h�̒l�ɕϊ�
	if( ( stick_data & STICK_ANALOG ) != 0 )
		state_chenge_speed( ap );

	if( button_ud < 0 )						// �����:�㏸
	{
		if( ap->pos[ Y ] < POS_LIMIT2 )
			if( ap->ang[ X ] > 0 )
			{
				if( ( stick_data &  STICK_ANALOG ) == 0 )
					ap->vec[ Y ] = SPEED /2;
				else if( j_state->lY < -200 || button_ud < -200 )// �A�i���O�X�e�B�b�N�̒l��K��������
					ap->vec[ Y ] = ap->VEC_Y;
				ap->vec[ X ] = SOZ_get_sin( ap->ang[ Z ] ) *ap->vec[ X ];
				ap->vec[ Y ] = SOZ_get_cos( -ap->ang[ Z ] ) *ap->vec[ Y ];
			}

		if( ap->ang[ X ] < ANG_LIMIT2 )
		{
			ap->ang[ X ] += ANGLE_X;
		}
		else
			ap->ang[ X ] = ANG_LIMIT2;
	}
	else if( button_ud > 0 )				// ������:���~
	{
		if( ap->pos[ Y ] > -POS_LIMIT2 )
			if( ap->ang[ X ] < 0 )
			{
				if( ( stick_data &  STICK_ANALOG ) == 0 )
					ap->vec[ Y ] = -SPEED /2;
				else if( j_state->lY > 200 || button_ud > 200 )	// �A�i���O�X�e�B�b�N�̒l��K��������
					ap->vec[ Y ] = ap->VEC_Y;
				ap->vec[ X ] = SOZ_get_sin( -ap->ang[ Z ] ) *ap->vec[ X ];
				ap->vec[ Y ] = SOZ_get_cos( -ap->ang[ Z ] ) *ap->vec[ Y ];
			}

		if( ap->ang[ X ] > -ANG_LIMIT2 )
		{
			ap->ang[ X ] += -ANGLE_X;
		}
		else
			ap->ang[ X ] = -ANG_LIMIT2;
	}
	else
	{
		if( ap->ang[ X ] < ANGLE_X && ap->ang[ X ] > -ANGLE_X )
			ap->ang[ X ] = 0x0000;
		else if( ap->ang[ X ] >= ANGLE_X )
			ap->ang[ X ] += -ANGLE_X;
		else if( ap->ang[ X ] <= -ANGLE_X )
			ap->ang[ X ] += ANGLE_X;
	}


	if( button_lr < 0 )	//������E���ړ�
	{
		if( ap->pos[ X ] > -POS_LIMIT )
			if( ap->ang[ Z ] < 0 )
			{
				if( ( stick_data & STICK_ANALOG ) == 0 )
					ap->vec[ X ] = -SPEED /2;
				else if( j_state->lX < -200 || button_lr < -200 )	// �A�i���O�X�e�B�b�N�̒l��K��������
					ap->vec[ X ] = ap->VEC_X;
				ap->vec[ X ] += SOZ_get_sin( -ap->ang[ Z ] ) *ap->vec[ X ];
				ap->vec[ Y ] += SOZ_get_cos( -ap->ang[ Z ] ) *ap->vec[ Y ];
			}
		if( ap->ang[ Z ] > -ANG_LIMIT )
			ap->ang[ Z ] += -ANGLE_Z;
		else
			ap->ang[ Z ] = -ANG_LIMIT;
	}

	else if( button_lr > 0 )	//�E����E�E�ړ�
	{
		if( ap->pos[ X ] < POS_LIMIT )
			if( ap->ang[ Z ] > 0 )
			{
				if ( ( stick_data & STICK_ANALOG ) == 0 )
					ap->vec[ X ] = SPEED /2;
				else if( j_state->lX > 200 || button_lr > 200 )	// �A�i���O�X�e�B�b�N�̒l��K��������
					ap->vec[ X ] = ap->VEC_X;
				ap->vec[ X ] += SOZ_get_sin( ap->ang[ Z ] ) *ap->vec[ X ];
				ap->vec[ Y ] += SOZ_get_cos( -ap->ang[ Z ] ) *ap->vec[ Y ];
			}
		if( ap->ang[ Z ] < ANG_LIMIT )
			ap->ang[ Z ] += ANGLE_Z;
		else
			ap->ang[ Z ] = ANG_LIMIT;
	}

	else
	{
		if( ap->ang[ Z ] < ANGLE_Z && ap->ang[ Z ] > -ANGLE_Z )
		{
			ap->ang[ Z ] = 0x0000;
		}
		else if( ap->ang[ Z ] >= ANGLE_Z )
		{
			ap->ang[ Z ] += -ANGLE_Z;
		}
		else if( ap->ang[ Z ] <= -ANGLE_Z )
		{
			ap->ang[ Z ] += ANGLE_Z;
		}
	}

	ap->pos[ X ] += ap->vec[ X ];
	ap->pos[ Y ] += ap->vec[ Y ];
}
void shot_system( TASK *ap )	// �ˌ�����
{
// �e�̃Y�������
	SINT32 rand_pos_x, rand_pos_y;
	rand_pos_x = rand_pos_y = Rand2( 45, 90 );
	ANGLE rand_ang = Rand2( 0x0000, 0xffff );
	rand_pos_x = SINT32 ( SOZ_get_sin( rand_ang ) * rand_pos_x );
	rand_pos_y = SINT32 ( SOZ_get_cos( rand_ang ) * rand_pos_y );
// �ˌ�
	if( SOZ_Inkey_TRG( DIK_X ) || SOZ_Inpad_TRG( 0, PADDIK_SUB_MISSILE ) || ( ( attack_button & DEMO_MISSILE ) != 0 && demo_mode == 1 ) )			// �{�^���������ꂽ��~�T�C���𔭎�
	{
		if( missile_ok == 1 )
			if( rest_missile > 0 )			// �c�e������΃~�T�C���𔭎˂���1
			{
				jiki_missile();
				rest_missile --;			// �c�e�����炷
				clrFLG( attack_button, DEMO_MISSILE );	// �~�T�C���̃t���O��Q�����B
				ap->workC[ E ] = Rand2( 1, 30 );
			}
	}
	if( SOZ_Inkey_DAT( DIK_Z ) || SOZ_Inpad_DAT( 0, PADDIK_MAIN_ATTACK ) || ( attack_button & DEMO_SHOT ) != 0 )			// �{�^����������Ă���ԁA�o���J���𔭎�
	{

		ap->workB[ X ]++;
		if( ap->workB[ X ] % 2 == 0 )	// ��莞�Ԃ����ɒe�𔭎˂���
		{
			shot( ap->pos[ X ] + rand_pos_x, ap->pos[ Y ] + rand_pos_y, ap->pos[ Z ] + 900.0f );	// ���W�������o��������
			if( ap->workB[ X ] % 4 == 0 )
				SOZ_play_se( SE_SHOT, 1.0f, 1, 1 );
			else
				SOZ_play_se( SE_SHOT_2, 1.0f, 1, 1 );
		}
	}
}
void my_ship_break( TASK *ap )		// ���@���ĉ��o
{
	ap->workA[Z] ++;
	bg_speed /= 10;
	if( ap->workA[ Z ] == 5 )
		camera_vibration_medium();								// �J�����U���@��
	if( ap->workA[ Z ] % 10 == 0 && ap->workA[ Z ] < 30 )
	{
		SOZ_play_se( SE_BREAK, 2.0f, 1, 1.0f );	// ���ʉ���炷
		break_effect( ap->pos[ X ], ap->pos[ Y ], ap->pos[ Z ] );	// �����G�t�F�N�g
	}
	if( ap->workA[ Z ] == 30 )
	{
		SOZ_play_se( SE_BREAK_BOM, 2.0f, 1, 1.0f );	// ���ʉ���炷
		break_bom_effect( ap->pos[ X ], ap->pos[ Y ], ap->pos[ Z ] );	// �����G�t�F�N�g
		game_type = TYPE_OVER;
	}
	else if( ap->workA[ Z ] > 30 )
	{
		if( ap->workA[ Z ] % 30 == 0 )
		{
			break_effect( ap->pos[ X ] +F_Rand2( -600.0f, 600.0f ), ap->pos[ Y ] +F_Rand2( -100.0f, 100.0f ), ap->pos[ Z ] );	// �j��̃G�t�F�N�g��\��
			break_effect( ap->pos[ X ] +F_Rand2( -600.0f, 600.0f ), ap->pos[ Y ] +F_Rand2( -100.0f, 100.0f ), ap->pos[ Z ] );	// �j��̃G�t�F�N�g��\��
			break_effect( ap->pos[ X ] +F_Rand2( -600.0f, 600.0f ), ap->pos[ Y ] +F_Rand2( -100.0f, 100.0f ), ap->pos[ Z ] );	// �j��̃G�t�F�N�g��\��
			break_effect( ap->pos[ X ] +F_Rand2( -600.0f, 600.0f ), ap->pos[ Y ] +F_Rand2( -100.0f, 100.0f ), ap->pos[ Z ] );	// �j��̃G�t�F�N�g��\��
		}
		if( ap->workA[ Z ] % 40 == 0 || ap->workA[ Z ] % 35 == 0 )
		{
			break_effect_02( ap->pos[ X ] +F_Rand2( -600.0f, 600.0f ), ap->pos[ Y ] +F_Rand2( -100.0f, 100.0f ), ap->pos[ Z ] );
		}
		if( ap->workA[ Z ] > 300 )
		{
			break_effect_02( ap->pos[ X ] +F_Rand2( -600.0f, 600.0f ), ap->pos[ Y ] +F_Rand2( -100.0f, 100.0f ), ap->pos[ Z ] );
			break_effect_02( ap->pos[ X ] +F_Rand2( -600.0f, 600.0f ), ap->pos[ Y ] +F_Rand2( -100.0f, 100.0f ), ap->pos[ Z ] );
			break_effect_02( ap->pos[ X ] +F_Rand2( -600.0f, 600.0f ), ap->pos[ Y ] +F_Rand2( -100.0f, 100.0f ), ap->pos[ Z ] );
			break_effect_02( ap->pos[ X ] +F_Rand2( -600.0f, 600.0f ), ap->pos[ Y ] +F_Rand2( -100.0f, 100.0f ), ap->pos[ Z ] );
			break_effect_02( ap->pos[ X ] +F_Rand2( -600.0f, 600.0f ), ap->pos[ Y ] +F_Rand2( -100.0f, 100.0f ), ap->pos[ Z ] );
			TASK_end( ap );
			return;
		}
	}
}
void my_ship_game_clear( TASK *ap )
{
}
void my_ship_exec( TASK *ap )
{
	ap->workB[ Y ]++;
	switch ( ap->workA[ X ] )
	{
		case 0:	// �o��V�[��
			ap->pos[ Z ] += 50.0f;
			if( ap->pos[ Z ] >= 0 )
				ap->workA[ X ] = 1;
			break;

		case 1:	// �v���C���[���샂�[�h
			shot_system( ap );		// �V���b�g�ˌ�
			my_ship_cont( ap );		// �@�̂̑��c
//			myship_hit_check( ap);	// �G�Ǝ��@�̓����蔻��`�F�b�N
			camera_move( ap );
			SOZ_camera_move( 0 );
			missile_lock_on( ap );			// ��ԋ߂��G�����b�N�I��
			break;

		case 2:	// ���G���[�h
			missile_lock_on( ap );			// ��ԋ߂��G�����b�N�I��
			shot_system( ap );		// �V���b�g�ˌ�
			my_ship_cont( ap );		// �@�̂̑��c
			ap->workA[ Y ]--;
			if( ap->workA[ Y ] <= 0 )	// ���Ԍo�߂Ŗ��G����
			{
				ap->workA[ X ] = 1;
			}
			camera_move( ap );
			SOZ_camera_move( 0 );
			break;

		case 3:	// ���j���o/GAME OVER
			my_ship_break( ap );
			break;

		case 4:	// �N���A���o/GAME CLEAR
			my_ship_game_clear( ap );
			break;

		case 50:	// �{�X��Q�t�F�[�Y�ڍs�V�[��
			ap->pos[ Z ] += ap->workD[ X ];
			ap->workD[ X ] += 4;
			if( ap->pos[ Z ] > 30000 )
				ap->workA[ X ]++;
			break;

		case 51:
			ap->pos[ Z ] -= ap->workD[ X ];
			ap->workD[ X ] -= 2;
			if( ap->pos[ Z ] <= 10 )
				ap->workA[ X ] = 1;
			break;
	}

	// �A�t�^�[�o�[�i�[
	if( ap->workB[ Y ] % 2 == 0 )
	{
		jiki_burner_effect( ap, 50 );
		jiki_burner_effect( ap, -50 );
		if( life < 2 )
		{
			break_smoke( ap );
			if( ap->workB[ Y ] % 20 == 0 )
				spark_effect( ap, 10 );
		}
	}

//------------- ���@�̃f�o�b�O��� -------------------------------------------

	SOZ_locate_print( 2,  5, "[JIKI] pos X:	%f", ap->pos[ X ] );
	SOZ_locate_print( 2,  6, "[JIKI] pos X:	%f", ap->pos[ Y ] );
	SOZ_locate_print( 2,  7, "[JIKI] pos X:	%f", ap->pos[ Z ] );

	SOZ_locate_print( 2,  9, "[JIKI] vec X:	%f", ap->vec[ X ] );
	SOZ_locate_print( 2, 10, "[JIKI] vec X:	%f", ap->vec[ Y ] );
	SOZ_locate_print( 2, 11, "[JIKI] vec X:	%f", ap->vec[ Z ] );

	SOZ_locate_print( 2, 13, "[Lstic] LR : %05d", j_state->lX);		// ���X�e�B�b�N���E
	SOZ_locate_print( 2, 14, "[Lstic] UD : %05d", j_state->lY);		// ���X�e�B�b�N�㉺
	SOZ_locate_print( 2, 15, "[Rstic] LR : %05d", j_state->lZ);		// �E�X�e�B�b�N���E
	SOZ_locate_print( 2, 16, "[Rstic] UD : %05d", j_state->lRz);	// �E�X�e�B�b�N�㉺

	SOZ_locate_print( 2, 17, "[SPEED] X : %05d", ap->VEC_X );
	SOZ_locate_print( 2, 18, "[SPEED] Y : %05d", ap->VEC_Y );

//----------------------------------------------------------------------------
}
void my_ship( void )
{
	TASK *ap;
	ap = TASK_start_MODEL( my_ship_exec, GROUP_MY_SHIP, MODEL_MY_SHIP, TEXTURE_MY_SHIP, "���@3D���f��" );
	ap->grp_mode = WRITE_ZBUFFER | TEST_ZBUFFER | USE_LIGHTING | USE_3DPOS;	//| USE_SPECULAR ;
	ap->pos[ X ] = 0;
	ap->pos[ Y ] = -650.0f;
	ap->pos[ Z ] = -1500.0f;
//	ap->pos[ Z ] = 0.0f;
	ap->ang[ X ] = 0x0200;
//	ap->ang[ Y ] = -0x4000;
	ap->ang[ Z ] = 0x0000;
	ap->angle[ X ] = 0x0000;
	ap->angle[ Y ] = 0x0000;
	ap->angle[ Z ] = 0x0000;
	ap->pri = PRI_JIKI;

	ap->workA[ X ] = 0;				// �o��V�[�� / ����I�t / ���G
	ap->workA[ Y ] = 0;				// ���G�ݒ�p
	ap->workA[ Z ] = 0;				// ���j���o
	ap->workB[ X ] = 0;				// �V���b�g�Ԋu�v�Z
	ap->workB[ Y ] = 0;				// �o�[�i�[�Ԋu�v�Z�p
	ap->workB[ D ] = 0;				// ���G����
	ap->workB[ P ] = 0;				// �ԓ_��
	ap->workC[ D ] = 0x0000;		// ang�ɑ����l
	ap->workC[ E ] = 0;				// �f���v���C���̃~�T�C�����˃t���[���v�Z
	ap->workD[ X ] = 0;				// �{�X�펞�̉��o
	ap->workD[ Y ] = 0;				// �{�X�펞�̉��o
	ap->ATK = SHOT_DAMAGE;
	ap->sphire = 80.0f;
	ap->callback = my_ship_callback;

	jiki = ap;
//	SOZ_camera_set_at_move( 0 );

// 3D���f���̃}�e���A����ݒ�
	ap->specular[ 0 ] = 1.0f;
	ap->specular[ 1 ] = 1.0f;
	ap->specular[ 2 ] = 1.0f;
	ap->ambient[ 0 ] = 0.0f;
	ap->ambient[ 1 ] = 0.0f;
	ap->ambient[ 2 ] = 0.0f;
	ap->emissive[0] = 0.25f;
	ap->emissive[1] = 0.25f;
	ap->emissive[2] = 0.25f;
 	ap->pow = 6.0f;
	SOZ_material_setting( ap );

	shot_break_count = 0;
	life = 3;					// �c�@�̏�����
	stage = 0;					// �X�e�[�W�\�L�̏�����
	demo_mode = 0;
	attack_button = 0;
#if 1
	rest_missile = 30;			// �~�T�C���̎c�e���̏�����
#else
	rest_missile = 999;			// �~�T�C���̎c�e���̏�����
#endif
}
