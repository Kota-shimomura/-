
#ifdef WINDOWS_PC
#include    "C:/project/libs/systemOZ_v4/soz.h"
#else
#include    "D:/project/guardians_2dx/proj.win32/src/systemOZ/soz.h"
#endif

#include    "C:/project/bace/src/game/game_include.h"
//------------------------------------------------------------------------------------------------------------------------------------------------------
// �⏕�֐�
//------------------------------------------------------------------------------------------------------------------------------------------------------
//	�f���v���C�ł��g�p���܂��B
SINT32 button_lr = 0;
SINT32 button_ud = 0;
SINT32 attack_button = 0;
SINT32 demo_mode = OFF;


DEMO_DATA demo_data[ DEMO_DATA_SIZE ];



//-----------------------------------------------------------------------------
// ���v���C�̃f�[�^���\���̂ɕۑ�����
//-----------------------------------------------------------------------------
void play_data_get_exec( TASK *ap )
{
	ap->work1[ X ]++;
	ap->work2[ X ] = 0;
// �ړ�����������
	demo_data[ ap->work1[ X ] ].stick_lr = button_lr;
	demo_data[ ap->work1[ X ] ].stick_ud = button_ud;

// �U�����͂���������
	if( SOZ_Inkey_DAT( DIK_Z ) || SOZ_Inpad_DAT( 0, PADDIK_MAIN_ATTACK ) )
		orFLG( ap->work2[ X ], DEMO_SHOT );
	if( SOZ_Inkey_TRG( DIK_X ) || SOZ_Inpad_TRG( 0, PADDIK_SUB_MISSILE ) )
		orFLG( ap->work2[ X ], DEMO_MISSILE );
	demo_data[ ap->work1[ X ] ].attack = ap->work2[ X ];

// �w������Ńf�[�^���t�@�C���ɕۑ����ă^�X�N�G���h
	if( game_type == TYPE_CLEAR || game_type == TYPE_OVER || ap->work1[ X ] > DEMO_DATA_SIZE -1 )
	{
		replay_option_save_data( SAVE_MODE );					// ���v���C���̐ݒ��ۑ�
		replay_save_data( SAVE_MODE );	// �ۑ�����
		TASK_end( ap );
		return;
	}
}
void play_data_get( void )
{
	TASK *ap;
	ap = TASK_start( play_data_get_exec, GROUP_UI, "�\���̂ɑ����ۑ�" );
	ap->work1[ X ] = 0;
	ap->work2[ X ] = 0;	// �U�����͂̃t���O�擾
// �f�[�^������������
	for( SINT32 i = 0; i < DEMO_DATA_SIZE; i++ )
	{
		demo_data[ i ].stick_lr = -9999;
		demo_data[ i ].stick_ud = -9999;
		demo_data[ i ].attack = 0;
	}
}

//-----------------------------------------------------------------------------
// �f���v���C����
//-----------------------------------------------------------------------------
void demo_play_exec( TASK *ap )
{
	button_lr = 0;
	button_ud = 0;

// �{�^���̓��̓f�[�^���擾	�f���v���C�ɔ��f
	button_lr = demo_data[ ap->work1[ X ] ].stick_lr;
	button_ud = demo_data[ ap->work1[ X ] ].stick_ud;
	attack_button = demo_data[ ap->work1[ X ] ].attack;
	ap->work1[ X ]++;

// ���C�t���O�ɂȂ邩���莞�Ԃ��o�߂������A�^�C�g����ʂɖ߂�
	if( demo_data[ ap->work1[ X ] + 2 ].stick_lr == -9999 || SOZ_Inpad_TRG( 0, PADDIK_CANCEL )|| SOZ_Inkey_TRG( DIK_X ) || SOZ_Inpad_TRG( 0, PADDIK_DECIDE )|| SOZ_Inkey_TRG( DIK_Z ) || ap->work1[ X ] >= 60 * 60 * 2  || life <= 0 )
	{
		fade( 5, TYPE_TITLE );
		TASK_end( ap );
		return;
	}

// �f�o�b�O�\�L
	SOZ_locate_print ( 30, 10, "LR:%d", button_lr );
	SOZ_locate_print ( 30, 11, "UD:%d", button_ud );
	SOZ_locate_print ( 30, 13, "mode:%d", demo_mode );
	SOZ_locate_print ( 30, 14, "flag:%d", stick_data );
}
void demo_play( void )
{
	TASK *ap;
	ap = TASK_start( demo_play_exec, GROUP_UI, "�I�[�g����" );
	replay_save_data( LOAD_MODE );
	ap->work1[ X ] = 1;
	demo_mode = 1;
}


//-----------------------------------------------------------------------------
// ���@����̃R���g���[���[�㉺���E�̓��͎擾
//-----------------------------------------------------------------------------
void button_data_get( void )
{
	button_ud = 0;
	button_lr = 0;
	if( ( stick_data & STICK_ANALOG ) != 0 )		// �A�i���O�X�e�B�b�N���g�p����
	{
		if( j_state->lY < -200 || j_state->lY > 200 || button_ud < -200 || button_ud > 200 )
		{
			if( demo_mode == 0 )
				button_ud = j_state->lY;
			if( ( stick_data & STICK_UD ) != 0 )		// �㉺���]
				button_ud *= -1;
		}
		if( j_state->lX < -200 || j_state->lX > 200 || button_lr < -200 || button_lr > 200 )
		{
			if( demo_mode == 0 )
				button_lr = j_state->lX;
			if( ( stick_data & STICK_LR ) != 0 )		// ���E���]
				button_lr *= -1;
		}
	}
	else											// �A�i���O�X�e�B�b�N���g�p���Ȃ�
	{
		if( SOZ_Inkey_DAT( DIK_UP ) || SOZ_Inpad_DAT( 0, PADDIK_UP ) )	// �オ���͂��ꂽ��
		{
//			button_ud = -1000;
			button_ud = -( SOZ_Inkey_DAT( DIK_UP ) + SOZ_Inpad_DAT( 0, PADDIK_UP ) );
			if( ( stick_data & STICK_UD ) != 0 )	// �㉺�����]����Ă���
				button_ud *= -1;
		}
		if( SOZ_Inkey_DAT( DIK_DOWN ) || SOZ_Inpad_DAT( 0, PADDIK_DOWN ) )	// �������͂��ꂽ��
		{
//			button_ud = 1000;
			button_ud = SOZ_Inkey_DAT( DIK_DOWN ) + SOZ_Inpad_DAT( 0, PADDIK_DOWN );
			if( ( stick_data & STICK_UD ) != 0 )	// LR�����]����Ă���
				button_ud *= -1;
		}

		if( SOZ_Inkey_DAT( DIK_LEFT ) || SOZ_Inpad_DAT( 0, PADDIK_LEFT ) )	// �������͂��ꂽ��
		{
//			button_lr = -1000;
			button_lr = -( SOZ_Inkey_DAT( DIK_LEFT ) + SOZ_Inpad_DAT( 0, PADDIK_LEFT ) );
			if( ( stick_data & STICK_LR ) != 0 )	// LR�����]����Ă���
				button_lr *= -1;
		}
		if( SOZ_Inkey_DAT( DIK_RIGHT ) || SOZ_Inpad_DAT( 0, PADDIK_RIGHT ) )	// �E�����͂��ꂽ��
		{
//			button_lr = 1000;
			button_lr = SOZ_Inkey_DAT( DIK_RIGHT ) + SOZ_Inpad_DAT( 0, PADDIK_RIGHT );
			if( ( stick_data & STICK_LR ) != 0 )	// LR�����]����Ă���
				button_lr *= -1;
		}
	}
}

//-----------------------------------------------------------------------------
// �����t�F�[�h�C�� / �t�F�[�h�A�E�g
//-----------------------------------------------------------------------------
void fade_exec( TASK *ap )
{
	ap->work2[ X ] ++;
	if( ap->work2[ X ] % 2 == 0 )
		ap->base_color[ 0 ][ 0 ] += ap->work1[ X ];
	if( ap->work1[ X ] > 0 )
	{
		if( ap->base_color[ 0 ][ 0 ] > 250 )
		{
			game_type = ap->work1[ Y ];
			TASK_all_init();
			return;
		}
	}
	else
	{
		if( ap->base_color[ 0 ][ 0 ] < 10 )
		{
			TASK_end( ap );
			return;
		}
	}
}
void fade( SINT32 fade_mode, SINT32 chenge_type )
{
	TASK *ap;
	ap = TASK_start_GRP( fade_exec, GROUP_UI, TEXTURE_EFFECT, fade_rect, 0, "�t�F�[�h�G�t�F�N�g" );
	ap->pos[ X ] = WINDOW_WIDTH /2;
	ap->pos[ Y ] = WINDOW_HEIGHT /2;
	ap->pri = PRI_UI + 10000 *WP;
	ap->scale[ Y ] = ap->scale[ X ] = 100.0f;
	ap->work1[ X ] = fade_mode;
	ap->work1[ Y ] = chenge_type;
	ap->work2[ X ] = 0;
	ap->base_color[ 0 ][ 0 ] = 0x00;
	if( fade_mode < 0 )
		ap->base_color[ 0 ][ 0 ] = 0xff;
}


//-----------------------------------------------------------------------------
// �QD�O���t�B�b�N���J�����������悤��
//-----------------------------------------------------------------------------
void grp_look_camer( TASK *ap )
{
	ap->ang[ X ] = SOZ_atan2( ap->pos[ Z ], ap->pos[ Y ], camera_z[ 0 ], camera_y[ 0 ] );
	ap->ang[ X ] = SOZ_atan2( ap->pos[ Z ], ap->pos[ Y ], camera_z[ 0 ], camera_y[ 0 ] );
}

//-----------------------------------------------------------------------------
// �^�[�Q�b�g�ړ��x�N�g���ݒ� ������
//-----------------------------------------------------------------------------
void target_lock_vec( TASK *ap, TASK *actp )
{
	ANGLE ans_x, ans_y; //,ans_z;
// �ڕW�Ƃ̍��W���݂āA�p�x���Z�o����B
	ans_x = SOZ_atan2( ap->pos[ Z ], ap->pos[ Y ], actp->pos[ Z ], actp->pos[ Y ] );
	ans_y = SOZ_atan2( ap->pos[ Z ], ap->pos[ X ], actp->pos[ Z ], actp->pos[ X ] );
	ap->ang[ X ] = ans_x;
	ap->ang[ Y ] = -ans_y;
	// �p�x�ɍ��킹�Đi�߂�悤�Ƀx�N�g�����Z�o����B
	ap->vec[ X ] = SOZ_get_sin( -ap->ang[ Y ] ) *ap->work2[ D ];
	ap->vec[ Y ] = SOZ_get_sin( ap->ang[ X ] ) *ap->work2[ D ];
	ap->vec[ Z ] = ( SOZ_get_cos( ap->ang[ X ] ) *ap->work2[ D ] + SOZ_get_cos( ap->ang[ Y ] ) *ap->work2[ D ] ) /2;

}

void target_look( TASK *ap, TASK *actp )	// ���ӁI�I�@��������̕ϐ��ɑ������
{
	ANGLE ans_x, ans_y, ans_z;
// �ڕW�Ƃ̍��W���݂āA�p�x���Z�o����B
	ans_x = SOZ_atan2( ap->pos[ Z ], ap->pos[ Y ], actp->pos[ Z ], actp->pos[ Y ] );
	ans_y = SOZ_atan2( ap->pos[ Z ], ap->pos[ X ], actp->pos[ Z ], actp->pos[ X ] );
	ans_z = SOZ_atan2( ap->pos[ X ], ap->pos[ Y ], actp->pos[ X ], actp->pos[ Y ] );
// ���̊p�x�Ɩ{�����������p�x�������	ans�̒��ɍ��E�ǂ����̕����ɂ���Ă��邩( �v���X���}�C�i�X�� )
 	ans_x = SOZ_angle_diff( ap->ang[ X ], ans_x );
 	ans_y = SOZ_angle_diff( ap->ang[ Y ], ans_y );
 	ans_z = SOZ_angle_diff( ap->ang[ Z ], ans_z );
	switch ( SOZ_sgn( ans_x ) )	//���l�̒P�ʉ��@�P�ʉ������ 1 ���� -1 �̐����̐��l�ɂȂ�
	{
		case 1:
			ap->ang[ X ] -= 0x45;
			break;

		case -1:
			ap->ang[ X ] += 0x45;
			break;
	} 
	switch ( SOZ_sgn( ans_y ) )	//���l�̒P�ʉ��@�P�ʉ������ 1 ���� -1 �̐����̐��l�ɂȂ�
	{
		case 1:
			ap->ang[ Y ] += 0x45;
			break;

		case -1:
			ap->ang[ Y ] -= 0x45;
			break;
	} 
	// �p�x�ɍ��킹�Đi�߂�悤�Ƀx�N�g�����Z�o����B
	ap->vec[ X ] = SOZ_get_sin( ap->ang[ Y ] ) *ap->work2[ D ];
	ap->vec[ Y ] =  SOZ_get_sin( ap->ang[ X ] ) *ap->work2[ D ];
	ap->vec[ Z ] = SOZ_get_cos( ap->ang[ X ] ) *ap->work2[ D ] + SOZ_get_cos( ap->ang[ Y ] ) *ap->work2[ D ];
}

//-----------------------------------------------------------------------------
// ���@�^�[�Q�b�g�ړ��x�N�g���ݒ� ������
//-----------------------------------------------------------------------------
void jiki_look( TASK *ap )	// ���ӁI�I�@��������̕ϐ��ɑ������
{
	ANGLE ans_x, ans_y, ans_z;
// ���@�Ƃ̍��W���݂āA�p�x���Z�o����B
	ans_x = SOZ_atan2( ap->pos[ Z ], ap->pos[ Y ], jiki->pos[ Z ], jiki->pos[ Y ] );
	ans_y = SOZ_atan2( ap->pos[ Z ], ap->pos[ X ], jiki->pos[ Z ], jiki->pos[ X ] );
	ans_z = SOZ_atan2( ap->pos[ X ], ap->pos[ Y ], jiki->pos[ X ], jiki->pos[ Y ] );
// ���̊p�x�Ɩ{�����������p�x�������	ans�̒��ɍ��E�ǂ����̕����ɂ���Ă��邩( �v���X���}�C�i�X�� )
 	ans_x = SOZ_angle_diff( ap->ang[ X ], ans_x );
 	ans_y = SOZ_angle_diff( ap->ang[ Y ], ans_y );
 	ans_z = SOZ_angle_diff( ap->ang[ Z ], ans_z );
	switch ( SOZ_sgn( ans_x ) )	//���l�̒P�ʉ��@�P�ʉ������ 1 ���� -1 �̐����̐��l�ɂȂ�
	{
		case 1:
			ap->ang[ X ] -= 0x45;
			break;

		case -1:
			ap->ang[ X ] += 0x45;
			break;
	} 
	switch ( SOZ_sgn( ans_y ) )	//���l�̒P�ʉ��@�P�ʉ������ 1 ���� -1 �̐����̐��l�ɂȂ�
	{
		case 1:
			ap->ang[ Y ] += 0x45;
			break;

		case -1:
			ap->ang[ Y ] -= 0x45;
			break;
	} 
	// �p�x�ɍ��킹�Đi�߂�悤�Ƀx�N�g�����Z�o����B
	ap->vec[ X ] = SOZ_get_sin( ap->ang[ Y ] ) *ap->work2[ D ];
	ap->vec[ Y ] =  SOZ_get_sin( ap->ang[ X ] ) *ap->work2[ D ];
	ap->vec[ Z ] = SOZ_get_cos( ap->ang[ X ] ) *ap->work2[ D ] + SOZ_get_cos( ap->ang[ Y ] ) *ap->work2[ D ];
}

//-----------------------------------------------------------------------------
// ���@�^�[�Q�b�g�ړ��x�N�g���ݒ� ������
//-----------------------------------------------------------------------------
void lockon_jiki( TASK *ap )
{
	// ���@�Ƃ̍��W���݂āA�p�x���Z�o����B
	ap->ang[ X ] = -SOZ_atan2( ap->pos[ Z ], ap->pos[ Y ], jiki->pos[ Z ], jiki->pos[ Y ] );
	ap->ang[ Y ] = -SOZ_atan2( ap->pos[ Z ], ap->pos[ X ], jiki->pos[ Z ], jiki->pos[ X ] );
	ap->ang[ Z ] = SOZ_atan2( ap->pos[ X ], ap->pos[ Y ], jiki->pos[ X ], jiki->pos[ Y ] ) + 0x8000;
	// �p�x�ɍ��킹�Đi�߂�悤�Ƀx�N�g�����Z�o����B
	ap->vec[ X ] = SOZ_get_sin( -ap->ang[ Y ] ) *ap->work2[ D ] + SOZ_get_cos( ap->ang[ Z ] ) *ap->work2[ D ];
	ap->vec[ Y ] = SOZ_get_sin( ap->ang[ Z ] ) *ap->work2[ D ] + SOZ_get_cos( -ap->ang[ X ] ) *ap->work2[ D ];
	ap->vec[ Z ] = SOZ_get_sin( -ap->ang[ X ] ) *ap->work2[ D ] + SOZ_get_cos( -ap->ang[ Y ] ) *ap->work2[ D ];
}

//-----------------------------------------------------------------------------
// �ړ��x�N�g���ݒ�
//-----------------------------------------------------------------------------
void ang_vec_setting( TASK *ap, FLOAT speed )
{
	ap->vec[ Z ] = ap->vec[ Y ] = ap->vec[ X ] = 0;

	//ap->vec[ X ] = ( ( SOZ_get_sin(  -ap->ang[ Y ] ) *speed ) + ( SOZ_get_cos(  -ap->ang[ Z ] ) *speed ) )/2;
	//ap->vec[ Y ] = ( ( SOZ_get_sin(  -ap->ang[ Z ] ) *speed ) + ( SOZ_get_cos(  -ap->ang[ X ] ) *speed ) )/2;
	//ap->vec[ Z ] = ( ( SOZ_get_sin(  -ap->ang[ X ] ) *speed ) + ( SOZ_get_cos(  -ap->ang[ Y ] ) *speed ) )/2;

	ap->vec[ X ] = SOZ_get_sin( ap->ang[ Y ] ) *speed;
	ap->vec[ Y ] =  SOZ_get_sin( ap->ang[ X ] ) *speed;
	ap->vec[ Z ] = SOZ_get_cos( ap->ang[ X ] ) *speed + SOZ_get_cos( ap->ang[ Y ] ) *speed;
}


//-----------------------------------------------------------------------------
//�c���t�^
//-----------------------------------------------------------------------------
void illusion_exec(TASK *ap)
{
	ap->base_color[0][0] -= ap->work1[X];//�����x�������Ă���
	ap->pri += 2;//�v���C�I���e�B( �`��D�揇�� )���グ��
	if (ap->base_color[0][0] < 10)//������x�����x������������^�X�N�G���h
	{
		TASK_end(ap);
		return;
	}
}
void illusion_start(TASK *actp, SINT32 speed, SINT32 blend)
{
	TASK *ap;
	ap = TASK_start(illusion_exec, 0, "�c��");
	TASK_copy(ap, actp);//�^�X�N�̃R�s�[�����( ap �� actp ���R�s�[���� )
	ap->work1[X] = speed;//ap->bace_collor[0][0]��������l
}

void bic_illusion_exec(TASK *ap)
{
	ap->pri++;
	ap->pos[ Z ]++;
	ap->scale[ Y ] = ap->scale[ X ] += 0.005f;	// �傫������
	ap->base_color[0][0] -= ap->work1[X];//�����x�������Ă���
	ap->pri += 2;//�v���C�I���e�B( �`��D�揇�� )���グ��
	if (ap->base_color[0][0] < 10)//������x�����x������������^�X�N�G���h
	{
		TASK_end(ap);
		return;
	}
}
void bic_illusion_start(TASK *actp, SINT32 speed, SINT32 blend)
{
	TASK *ap;
	ap = TASK_start(bic_illusion_exec, 0, "�c��");
	TASK_copy(ap, actp);//�^�X�N�̃R�s�[�����( ap �� actp ���R�s�[���� )
	ap->work1[X] = speed;//ap->bace_collor[0][0]��������l
}


//------------------------------------------------------------------------------------------------------------------------------------------------------
// ���@����ʂ̔������傫���Ȃ������ɃJ�����̊p�x��ς���
//------------------------------------------------------------------------------------------------------------------------------------------------------
void camera_move( TASK *ap )
{
	ap->angle[ Z ] = 0x0000;
	ap->angle[ X ] = 0x0000;
// ����̃t���[���ȏ���͂��������ꍇ�J�����̊p�x���ς��
	if( SOZ_Inkey_DAT( DIK_RIGHT ) >= 15 || SOZ_Inpad_DAT( 0, PADDIK_RIGHT ) >= 15 )
		ap->angle[ Z ] = 0x1000;
	if( SOZ_Inkey_DAT( DIK_LEFT ) >= 15 || SOZ_Inpad_DAT( 0, PADDIK_LEFT ) >= 15 )
		ap->angle[ Z ] = -0x1000;
	if( SOZ_Inkey_DAT( DIK_UP ) >= 15 || SOZ_Inpad_DAT( 0, PADDIK_UP ) >= 15 )
		ap->angle[ X ] = -0x0500;
	if( SOZ_Inkey_DAT( DIK_DOWN ) >= 15 || SOZ_Inpad_DAT( 0, PADDIK_DOWN ) >= 15 )
		ap->angle[ X ] = 0x0500;

	if( ap->angle[ Z ] < camera_ang_z[ 0 ] )
		camera_ang_z[ 0 ] -= 0x0075;
	else if ( ap->angle[ Z ] > camera_ang_z[ 0 ] )
		camera_ang_z[ 0 ] += 0x0075;

	if( ap->angle[ X ] < camera_ang_x[ 0 ] )
		camera_ang_x[ 0 ] -= 0x0050;
	else if ( ap->angle[ X ] > camera_ang_x[ 0 ] )
		camera_ang_x[ 0 ] += 0x00050;

	if( ap->pos[ Y ] > -100 &&  ap->pos[ Y ] < 300 )
	{
		if( camera_y[ 0 ] < 300 )
			camera_y[ 0 ] += 5;
	}
	else
	{
		if( camera_y[ 0 ] > 0 )
			camera_y[ 0 ] -= 5;
	}
}


//------------------------------------------------------------------------------------------------------------------------------------------------------
// ���@�̒e��vec�ݒ�
//------------------------------------------------------------------------------------------------------------------------------------------------------
void shot_vec_setting( TASK *ap, FLOAT speed )
{
	ap->vec[ X ] = 0;
	ap->vec[ Y ] = SOZ_get_sin( ap->ang[ X ] ) *speed;
	ap->vec[ Z ] = SOZ_get_cos( ap->ang[ X ] ) *speed + speed;
	return;
}

///------------------------------------------------------------------------------------------------------------------------------------------------------
/// �n�C�X�R�A�֘A
///------------------------------------------------------------------------------------------------------------------------------------------------------

//------------------------------------------------------------------------------------------------------------------------------------------------------
// �n�C�X�R�A�̕��בւ�
//------------------------------------------------------------------------------------------------------------------------------------------------------

int hi_score_sort( void )
{
	SINT32 for_rank = 9, score_slot;
	if( score > hi_score[ 9 ] )											// �����L���O�̍ŉ��ʂ�SCORE��������Ă����牽�������^�X�N�G���h
	{
		hi_score[ 9 ] = score;											// �Ƃ肠����10�ʂɂ����
		for( for_rank = 9; for_rank > 0; for_rank-- )					// �m�F
		{
			if( hi_score[ for_rank ] > hi_score[ for_rank - 1 ] )		// �����A�����N�����̕�������SCORE������������
			{
				// ����ւ���
				score_slot = hi_score[ for_rank -1 ];
				hi_score[ for_rank - 1 ] = hi_score[ for_rank ];
				hi_score[ for_rank ] = score_slot;
			}
		}
#if 0
		// �V�����n�C�X�R�A�̏��ʂ�T��
		for( now_rank = 9; now_rank > 0; now_rank -- )
			if( score > hi_score[ now_rank ] )
				sort_rank = now_rank;
		// �\�[�g������
		for( for_rank = 9; for_rank > sort_rank; for_rank-- )
			hi_score[ for_rank ] = hi_score[ for_rank -1 ];
		hi_score[ sort_rank-1 ] = score;
#endif
		return 1;
	}
	else
		return 0;
}


//------------------------------------------------------------------------------------------------------------------------------------------------------
// �n�C�X�R�A/�����L���O�̏�����
//------------------------------------------------------------------------------------------------------------------------------------------------------

void hi_score_all_clear( void )
{
	SINT32 rank_no;
	for( rank_no = 0; rank_no < 10; rank_no++ )
	{
		hi_score[ rank_no ] = 0;
	}
}
