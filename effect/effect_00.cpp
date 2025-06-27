#ifdef WINDOWS_PC
#include    "C:/project/libs/systemOZ_v4/soz.h"
#else
#include    "D:/project/guardians_2dx/proj.win32/src/systemOZ/soz.h"
#endif

#include    "C:/project/bace/src/game/game_include.h"


//------------------------------------------------------------------------------------------------------------------------------------------------------
// 
//			EFFECT
// 
//------------------------------------------------------------------------------------------------------------------------------------------------------

//------------------------------------------------------------------------------------------------------------------------------------------------------
// ���@���_���[�W���������̐Ԃ��X�N���[��
//------------------------------------------------------------------------------------------------------------------------------------------------------
void bullet_myship_hit_effect_exec( TASK *ap )
{
	if( life > 1 )
	{
		ap->base_color[ 0 ][ 0 ] -= 10;		// �����x��������
		if( ap->base_color[ 0 ][ 0 ] < 10 )	// �����x������̒l�����������^�X�N������
		{
			TASK_end( ap );
			return;
		}
	}
	else		// �_�ŏ���
	{
		ap->work2[ X ] += Rand2( 1, 10 );
		ap->base_color[ 0 ][ 0 ] -= ap->work1[ X ];
		if( ap->base_color[ 0 ][ 0 ] < 0x22 || ap->base_color[ 0 ][ 0 ] > 0x44 )
			ap->work1[ X ] *= -1;

		// �u���̏���
		if( ap->work2[ X ] > 210 )
		{
			switch ( ap->work2[ Y ] )
			{
				case 0:
					ap->pos[ X ] += 50;
					ap->work2[ Y ]++;
					break;

				case 1:
					ap->pos[ X ] -= 100;
					ap->work2[ Y ] = 2;
					break;

				case 2:
					ap->pos[ X ] += 50;
					ap->work2[ X ] = 0;
					ap->work2[ Y ] = 0;
					break;
			}
		}
	}
	if( jiki == NULL )
	{
		TASK_end( ap );
		return;
	}
		
}
void bullet_myship_hit_effect( void )
{
	TASK *ap;
	ap = TASK_start_GRP(bullet_myship_hit_effect_exec, GROUP_UI, TEXTURE_EFFECT, hit_effect_rect, 5, "���@���_���[�W���������̐Ԃ��X�N���[��" );
	ap->pos[ X ] = WINDOW_WIDTH /2;
	ap->pos[ Y ] = WINDOW_HEIGHT /2;
	ap->scale[ X ] = ap->scale[ Y ] = 4.5f;
	ap->base_color[ 0 ][ 0 ] = 0x44;
	SOZ_play_se( SE_DAMAGE, 1.0f, 1, 1.0f );
	ap->work1[ X ] = 2;
	ap->pri = PRI_UI - 100;

//	�u���\���pwork�G���A
	ap->work2[ X ] = 0;
	ap->work2[ Y ] = 0;
}


//------------------------------------------------------------------------------------------------------------------------------------------------------
// ���@����o��Ή�
//------------------------------------------------------------------------------------------------------------------------------------------------------
void my_ship_spark_exec( TASK *ap )
{
	ap->pos[ X ] += ap->vec[ X ];
	ap->pos[ Y ] += ap->vec[ Y ];
	ap->pos[ Z ] += ap->vec[ Z ];
	ap->work1[ X ] ++;
	if( ap->work1[ X ] % 2 == 0 )		// ����t���[�����Ɏc���𐶐�
		illusion_start( ap, 50, BLEND_ADD );
	if( ap->work1[ X ] > 16 )			// ����t���[���o�߂Ń^�X�N������
	{
		TASK_end( ap );
		return;
	}
}
void my_ship_spark_start( FLOAT pos_x, FLOAT pos_y, FLOAT pos_z )
{
	TASK *ap;
	ap = TASK_start_MODEL( my_ship_spark_exec, GROUP_SHOT, MODEL_SHOT, TEXTURE_SPARK, "���@�̉Ή�" );
	ap->grp_mode = TEST_ZBUFFER;
	ap->blend_type = BLEND_ADD;
	ap->pos[ X ] = pos_x + F_Rand2( -50.0f, 50.0f );
	ap->pos[ Y ] = pos_y + F_Rand2( -50.0f, 50.0f );
	ap->pos[ Z ] = pos_z + F_Rand2( -50.0f, 50.0f );
	ap->ang[ Z ] = Rand2( 0x0000, 0xffff );
	ap->vec[ X ] = F_Rand2( -5, 5 );
	ap->vec[ Y ] = F_Rand2( -5, 5 );
	ap->vec[ Z ] = -50.0f;
	ap->pri = PRI_JIKI + Rand2( -10, 10 );
	ap->work1[ X ] = 0;
	if( game_type == TYPE_GAME || game_type == TYPE_GAME +1 )	// �Q�[���V�[���̎��͏�����悤�ɂ���
		SOZ_play_se( SE_SPARK, 1.0f, 1, 1 );
}

void spark_effect( TASK *ap, SINT32 num )
{
	FLOAT rand_pos_x = F_Rand2( -250, 250 );
	FLOAT rand_pos_y = F_Rand2( -150, 150 );
	FLOAT rand_pos_z = F_Rand2( -200, 200 );
	for( SINT32 i = 0; i < num; i++ )
		my_ship_spark_start( ap->pos[ X ] + rand_pos_x, ap->pos[ Y ] + rand_pos_y, ap->pos[ Z ] + rand_pos_z );
}

//------------------------------------------------------------------------------------------------------------------------------------------------------
// ���@����オ���Ă��鉌
//------------------------------------------------------------------------------------------------------------------------------------------------------
void myship_break_smoke_exec( TASK *ap )
{
	ap->pri++;
	ap->pos[ Z ] -= 10.0f;
	ap->base_color[ 0 ][ 0 ] -= 5;
	ap->scale[ Y ] = ap->scale[ X ] += 0.1f;
	if( ap->base_color[ 0 ][ 0 ] < 10 )
	{
		TASK_end( ap );
		return;
	}
}
void break_smoke( TASK *actp )
{
	TASK *ap;
	ap = TASK_start_GRP( myship_break_smoke_exec,GROUP_UI, TEXTURE_EFFECT, effect_rect, 1, "���@����オ�鉌" );
	ap->grp_mode = USE_3DPOS;
	ap->pos[ X ] = actp->pos[ X ] +F_Rand2( -200, 200 );
	ap->pos[ Y ] = actp->pos[ Y ] +F_Rand2( -100, 100 );
	ap->pos[ Z ] = actp->pos[ Z ];
	ap->scale[ Y ] = ap->scale[ X ] = F_Rand2( 0.5f, 4.0f );

	ap->base_color[ 0 ][ 0 ] = 0xdd;
	ap->base_color[ 0 ][ 3 ] = ap->base_color[ 0 ][ 2 ] = ap->base_color[ 0 ][ 1 ] = Rand2( 0x00, 0xac );
	ap->pri = PRI_JIKI+1;
}



void burner_effect_exec( TASK *ap )
{
	ap->work1[ X ] ++;
	if( ap->work1[ X ] % 2 == 0 )						// ����̃t���[�������ƂɎc������������
		illusion_start( ap, 50, BLEND_ADD );
	ap->pos[ Z ] += ap->vec[ Z ];						// ���W���ړ�������
	if( ap->work1[ X ] > 6 )							// �w��t���[���o�ߌ�^�X�N���G���h������
	{
		TASK_end( ap );
		return;
	}
}

void burner_effect( TASK *actp, FLOAT space, FLOAT pos_z,FLOAT vec_z )
{
	TASK *ap;
	ap = TASK_start_MODEL( burner_effect_exec, GROUP_MY_SHIP, MODEL_SHOT, TEXTURE_BURNER_2, "�o�[�i�[�G�t�F�N�g" );
	ap->grp_mode = TEST_ZBUFFER;
	ap->blend_type = BLEND_ADD;
	ap->pos[ X ] = actp->pos[ X ] + SOZ_get_cos( -actp->ang[ Z ] )*space;
	ap->pos[ Y ] = actp->pos[ Y ] + SOZ_get_sin( -actp->ang[ Z ] )*space + 75;
	ap->pos[ Z ] = pos_z;
	ap->vec[ Z ] = vec_z;
	ap->ang[ Z ] = Rand2( 0x0000, 0xffff );
	ap->scale[ X ] = 2.0f;
	ap->scale[ Y ] = ap->scale[ X ];
	ap->pri = PRI_BURNER;
	ap->work1[ X ] = 0;
}

//------------------------------------------------------------------------------------------------------------------------------------------------------
// �{�X�o���R�[�h�\��
//------------------------------------------------------------------------------------------------------------------------------------------------------
void boss_code_disp_exec( TASK *ap )
{
	ap->base_color[ 0 ][ 1 ] = 0xc6;
	ap->base_color[ 0 ][ 2 ] = 0x28;
	ap->base_color[ 0 ][ 3 ] = 0x28;
	ap->work1[ X ] --;			// �\�����Ԃ��v�Z
	if( ap->work1[ X ] < 1 )	// ���ԂɂȂ�����^�X�N�G���h������
	{
		TASK_end( ap );
		return;
	}
}
void boss_code_disp( void )
{
	TASK *ap;
	ap = TASK_start_FONT( boss_code_disp_exec, GROUP_UI, "<<SYSTEM ALERT>>", 3 );
	ap->pos[ X ] = WINDOW_WIDTH /3;
	ap->pos[ Y ] = 300;
	ap->work1[ X ] = DELAY_TIME;
	ap = TASK_start_FONT( boss_code_disp_exec, GROUP_UI, "RED-CODE PROTOCOL DETECTED", 3 );
	ap->delay = 10;
	ap->pos[ X ] = WINDOW_WIDTH /3;
	ap->pos[ Y ] = 350;
	ap->work1[ X ] = DELAY_TIME - ap->delay;
	ap = TASK_start_FONT( boss_code_disp_exec, GROUP_UI, "AUTONOMOUS WEAPON: SPECTER MK-2", 3 );
	ap->delay = 30;
	ap->pos[ X ] = WINDOW_WIDTH /3;
	ap->pos[ Y ] = 400;
	ap->work1[ X ] = DELAY_TIME - ap->delay;
	ap = TASK_start_FONT( boss_code_disp_exec, GROUP_UI, "STATUS: UNCHAINED", 3 );
	ap->delay = 40;
	ap->pos[ X ] = WINDOW_WIDTH /3;
	ap->pos[ Y ] = 450;
	ap->work1[ X ] = DELAY_TIME - ap->delay;
	ap = TASK_start_FONT( boss_code_disp_exec, GROUP_UI, "<<WARNING: HOSTILE AI ACTIVATION IN PROGRESS>>", 3 );
	ap->delay = 50;
	ap->pos[ X ] = WINDOW_WIDTH /3;
	ap->pos[ Y ] = 500;
	ap->work1[ X ] = DELAY_TIME - ap->delay;

	SOZ_play_se( SE_BOSS_CODE , 2.0f, 0, 1 );
}
void boss_next_code_disp( void )
{
	TASK *ap;
	ap = TASK_start_FONT( boss_code_disp_exec, GROUP_UI, "<<SYSTEM ALERT>>", 3 );
	ap->pos[ X ] = WINDOW_WIDTH /3;
	ap->pos[ Y ] = 300;
	ap->work1[ X ] = DELAY_TIME;
	ap = TASK_start_FONT( boss_code_disp_exec, GROUP_UI, "DOWNGRADED DURABILITY DETECTED", 3 );
	ap->delay = 10;
	ap->pos[ X ] = WINDOW_WIDTH /3;
	ap->pos[ Y ] = 350;
	ap->work1[ X ] = DELAY_TIME - ap->delay;
	ap = TASK_start_FONT( boss_code_disp_exec, GROUP_UI, "AUTONOMOUS WEAPON: SPECTER MK-2", 3 );
	ap->delay = 30;
	ap->pos[ X ] = WINDOW_WIDTH /3;
	ap->pos[ Y ] = 400;
	ap->work1[ X ] = DELAY_TIME - ap->delay;
	ap = TASK_start_FONT( boss_code_disp_exec, GROUP_UI, "ENEMY AI CONTROL SYSTEM DEACTIVATED", 3 );
	ap->delay = 40;
	ap->pos[ X ] = WINDOW_WIDTH /3;
	ap->pos[ Y ] = 450;
	ap->work1[ X ] = DELAY_TIME - ap->delay;
	ap = TASK_start_FONT( boss_code_disp_exec, GROUP_UI, "<<WARNING: MOVING INTO RUNAWAY STATE>>", 3 );
	ap->delay = 50;
	ap->pos[ X ] = WINDOW_WIDTH /3;
	ap->pos[ Y ] = 500;
	ap->work1[ X ] = DELAY_TIME - ap->delay;

	SOZ_play_se( SE_BOSS_CODE , 2.0f, 0, 1 );
}

//------------------------------------------------------------------------------------------------------------------------------------------------------
// �~�T�C�����b�N�I���G�t�F�N�g
//------------------------------------------------------------------------------------------------------------------------------------------------------
void ms_lockon_effect_exec( TASK *ap )
{
	ap->ang[ X ] = 0x0000;
	ap->work1[ X ]++;
	if( ap->work1[ X ] >= 2 )
	{
		TASK_end( ap );
		return;
	}
}
void ms_lockon_effect( FLOAT pos_x, FLOAT pos_y, FLOAT pos_z )
{
	TASK *ap;
	ap = TASK_start_GRP( ms_lockon_effect_exec, GROUP_UI, TEXTURE_HIT_EFF, hit_effect_rect, 1, "���b�N�I���G�t�F�N�g" );
	ap->grp_mode = USE_3DPOS;
	ap->pos[ X ] = pos_x;
	ap->pos[ Y ] = pos_y;
	ap->pos[ Z ] = pos_z - 100;
	ap->pri = PRI_ENEMY + 4;
	ap->work1[ X ] = 0;
	ap->scale[ Y ] = ap->scale[ X ] = 3.0f;
	ap->blend_type = BLEND_ADD;
	ap->base_color[ 0 ][ 0 ] = 0x44;
}
void ms_lockon_font( FLOAT pos_x, FLOAT pos_y, FLOAT pos_z )
{
	TASK *ap;
	ap = TASK_start_GRP( ms_lockon_effect_exec, GROUP_UI, TEXTURE_UI_FONT_2, hit_effect_rect, 3, "[lock on]�\��" );
	ap->grp_mode = USE_3DPOS | FLIP_LR;
	ap->pos[ X ] = pos_x;
	ap->pos[ Y ] = pos_y + 300.0f;
	ap->pos[ Z ] = pos_z - 100;
	ap->base_color[ 0 ][ 0 ] = 0x44;
	ap->base_color[ 0 ][ 1 ] = 0xe5;
	ap->base_color[ 0 ][ 2 ] = 0xfe;
	ap->base_color[ 0 ][ 3 ] = 0xab;
	ap->pri = PRI_ENEMY + 5;
	ap->work1[ X ] = 0;
	ap->scale[ Y ] = ap->scale[ X ] = 1.0f;

	ap = TASK_start_GRP( ms_lockon_effect_exec, GROUP_UI, TEXTURE_UI_FONT_2, hit_effect_rect, 4, "[�~�T�C��������]�\��" );
//	ap->grp_mode = USE_3DPOS | FLIP_LR;
	ap->pos[ X ] = WINDOW_WIDTH /2;
	ap->pos[ Y ] = WINDOW_HEIGHT - WINDOW_HEIGHT /20;
//	ap->pos[ Z ] = jiki->pos[ Z ];
	ap->pri = PRI_JIKI + 5;
	ap->work1[ X ] = 0;
	ap->scale[ Y ] = ap->scale[ X ] = 0.5f;
}


//------------------------------------------------------------------------------------------------------------------------------------------------------
// �~�T�C���G���W���G�t�F�N�g
//------------------------------------------------------------------------------------------------------------------------------------------------------
void ms_effect_exec( TASK *ap )
{
	ap->pos[ Z ] -= 25.0f*EFFECT_SPEED;				// ���W�ړ�
	ap->pri--;							// �`��D��x��������
	grp_look_camer( ap );				// �J�����Ɍ����悤�ɂȂ�
	illusion_start( ap, 5, BLEND_ADD );	// �c����\������
	ap->base_color[ 0 ][ 0 ] -= 96;		// �����������x���グ��
	ap->base_color[ 0 ][ 1 ] = ap->base_color[ 0 ][ 2 ] = ap->base_color[ 0 ][ 3 ] -= 75;
	if( ap->base_color[ 0 ][ 0 ] < 10 )	// ����̓����x�𒴂�����^�X�N�G���h
	{
		TASK_end( ap );
		return;
	}
}
void ms_effect_start( FLOAT pos_x, FLOAT pos_y, FLOAT pos_z  )		// �G�~�T�C���G�t�F�N�g
{
	TASK *ap;
	ap = TASK_start_GRP( ms_effect_exec, GROUP_UI, TEXTURE_EFFECT, effect_rect, 1, "�~�T�C���G�t�F�N�g" );
	ap->grp_mode = USE_3DPOS;
	ap->pos[ X ] = pos_x;
	ap->pos[ Y ] = pos_y;
	ap->pos[ Z ] = pos_z;
	ap->ang[ Z ] = Rand2( 0x0000, 0xffff );
	ap->pri = PRI_MISSILE_EFFE + 1;
	ap->scale[ Y ] = ap->scale[ X ] = 3.0f;
	ap->base_color[ 0 ][ 0 ] = 0xf0;
}

void missile_effect_exec( TASK *ap )
{
	ap->pos[ Z ] -= 25.0f*EFFECT_SPEED;					// ���W�ړ�
	ap->base_color[ 0 ][ 0 ] -= 5;
	ap->base_color[ 0 ][ 2 ] -= 5;
	ap->base_color[ 0 ][ 3 ] -= 5;
	if( ap->base_color[ 0 ][ 0 ] < 10 )		// �����x�����̒l�����������^�X�N�G���h
	{
		TASK_end( ap );
		return;
	}
	grp_look_camer( ap );					// �J�����������悤�ɂȂ�
}
void missile_effect( FLOAT pos_x, FLOAT pos_y, FLOAT pos_z  )
{
	TASK *ap;
	ap = TASK_start_GRP( missile_effect_exec,  GROUP_UI, TEXTURE_EFFECT, effect_rect, 8, "�~�T�C�����˃G�t�F�N�g" );
	ap->grp_mode = USE_3DPOS;
	ap->pos[ X ] = pos_x;
	ap->pos[ Y ] = pos_y;
	ap->pos[ Z ] = pos_z;
	ap->pri = PRI_MISSILE_EFFE;
	ap->blend_type = BLEND_ADD;
	ap->scale[ Y ] = ap->scale[ X ] = 2.0f;

	ms_effect_start( ap->pos[ X ], ap->pos[ Y ], ap->pos[ Z ] );
}

//------------------------------------------------------------------------------------------------------------------------------------------------------
// �~�T�C�����˃G�t�F�N�g
//------------------------------------------------------------------------------------------------------------------------------------------------------
void missile_start_effect_exec( TASK *ap )
{
	ap->pos[ Z ] -= 25.0f*EFFECT_SPEED;			// ���W�ړ�
	ap->work1[ X ] ++;				// ���Ԍv��
	if( ap->work1[ X ] == 5 )		// ����̎��ԂɂȂ�����\���摜��ς���
		ap->anime_no++;
	if( ap->work1[ X ] == 10 )		// ����̎��ԂɂȂ�����^�X�N�G���h����
	{
		TASK_end( ap );
		return;
	}
}
void missile_start_effect( FLOAT pos_x, FLOAT pos_y, FLOAT pos_z  )
{
	TASK *ap;
	ap = TASK_start_GRP( missile_start_effect_exec,  GROUP_UI, TEXTURE_EFFECT, effect_rect, 6, "�~�T�C�����ˎ��̃G�t�F�N�g" );
	ap->grp_mode = USE_3DPOS;
	ap->pos[ X ] = pos_x;
	ap->pos[ Y ] = pos_y;
	ap->pos[ Z ] = pos_z;
	ap->pri = PRI_MISSILE_SHOT;
	ap->blend_type = BLEND_ADD;
	ap->scale[ Y ] = ap->scale[ X ] = 2.0f; 
	if( ap->pos[ Z ] > 7000 )
	{
		ap->pri = PRI_ENEMY + 15;
		ap->scale[ Y ] = ap->scale[ X ] = 4.0f; 
	}
}

//------------------------------------------------------------------------------------------------------------------------------------------------------
// ������
//------------------------------------------------------------------------------------------------------------------------------------------------------
void break_smoke_exec( TASK *ap )
{
	ap->pos[ Z ] -= 25.0f*EFFECT_SPEED;						// ���W�ړ�
	ap->base_color[ 0 ][ 0 ] -= 2;				// �����x��������
	ap->scale[ Y ] = ap->scale[ X ] += 0.005f;	// �������傫������
	if( ap->base_color[ 0 ][ 0 ] < 5 )			// �����x������̒l�����������^�X�N�G���h
	{
		TASK_end( ap );
		return;
	}
}
void break_smoke( FLOAT pos_x, FLOAT pos_y, FLOAT pos_z )
{
	TASK *ap;
	ap = TASK_start_GRP( break_smoke_exec, GROUP_UI, TEXTURE_EFFECT, effect_rect, 1, "������" );
	ap->grp_mode = USE_3DPOS;
	ap->pos[ X ] = pos_x;
	ap->pos[ Y ] = pos_y;
	ap->pos[ Z ] = pos_z;
	ap->ang[ Z ] = Rand2( 0x0000, 0xffff );
	ap->pri =  PRI_HIT_EFFECT-2;
	ap->scale[ Y ] = ap->scale[ X ] = 5.0f;
	ap->base_color[ 0 ][ 0 ] = 0xe0;

	ap = TASK_start_GRP( break_smoke_exec, GROUP_UI, TEXTURE_EFFECT, effect_rect, 5, "������" );
	ap->grp_mode = USE_3DPOS;
	ap->pos[ X ] = pos_x;
	ap->pos[ Y ] = pos_y;
	ap->pos[ Z ] = pos_z;
	ap->ang[ Z ] = Rand2( 0x0000, 0xffff );
	ap->pri = PRI_SHOT_EFFECT-1;
	ap->scale[ Y ] = ap->scale[ X ] = 5.0f;
	ap->base_color[ 0 ][ 0 ] = 0xe0;
}

//------------------------------------------------------------------------------------------------------------------------------------------------------
// �����G�t�F�N�g02
//------------------------------------------------------------------------------------------------------------------------------------------------------
void break_02_bom_exec( TASK *ap )
{
	ap->pos[ Z ] -= 25.0f*EFFECT_SPEED;				// ���W�ړ�
	ap->work1[ X ]++;

// �A�j���[�V��������
	if( ap->work1[ X ] % 3 == 0 )
		ap->anime_no++;
	if( ap->anime_no > 11 )				// ����̃A�j���i���o�[�ɂȂ�����^�X�N�G���h
	{
		TASK_end( ap );
		return;
	}
	grp_look_camer( ap );				// �J�����������悤�ɂ���
}
void break_effect_02_bom( FLOAT pos_x, FLOAT pos_y, FLOAT pos_z )
{
	TASK *ap;
	ap = TASK_start_GRP( break_02_bom_exec, GROUP_UI, TEXTURE_BREAK, break_bom_effect_rect, 0, "���j���̔���" );
	ap->grp_mode = USE_3DPOS;
	ap->pos[ X ] = pos_x;
	ap->pos[ Y ] = pos_y;
	ap->pos[ Z ] = pos_z;
	ap->scale[ X ] = 16.0f;
	ap->scale[ Z ] = ap->scale[ Y ] = ap->scale[ X ];
	SOZ_play_se( SE_BREAK_BOM, 1.0f, 0, 1.0f );
	ap->pri = PRI_HIT_EFFECT;
	ap->base_color[ 0 ][ 0 ] = 180;
	ap->delay = 10;
	ap->scale[ Y ] = ap->scale[ X ] = 4.0f;
}
void effect_02_bom_core( TASK *ap )
{
	ap->work1[ Y ] ++;			// �t���[���v�Z
	if( ap->work1[ Y ] % 10 == 1 )
	{
		break_effect_02_bom(	ap->pos[ X ] + F_Rand2( -300.0f, 300.0f ), 
								ap->pos[ Y ] + F_Rand2( -300.0f, 300.0f ), 
								ap->pos[ Z ] );
		ap->work1[ X ] --;
	}
	if( ap->work1[ X ] <= 0 )
	{
		TASK_end( ap );
		return;
	}
	ap->pos[ Z ] -= 25.0f*EFFECT_SPEED;				// ���W�ړ�
}
void effect_02_bom_gen( FLOAT pos_x, FLOAT pos_y, FLOAT pos_z, SINT32 count )
{
	TASK *ap;
	ap = TASK_start( effect_02_bom_core, GROUP_UI, "�G�t�F�N�g�W�F�l���[�^�[" );
	ap->pos[ X ] = pos_x;
	ap->pos[ Y ] = pos_y;
	ap->pos[ Z ] = pos_z;
	ap->work1[ X ] = count;
	ap->work1[ Y ] = 0;
}


void break_02_light_exec( TASK *ap )
{
	ap->pos[ Z ] -= 25.0f*EFFECT_SPEED;				// ���W�ړ�
	ap->scale[ X ] += 1.0f;				// �\���T�C�Y���������g�傷��
	ap->scale[ Y ] = ap->scale[ X ];
	if( ap->scale[ X ] > 8.0f )			// �\���T�C�Y������̒l������ƃ^�X�N�G���h
	{
		TASK_end( ap );
		return;
	}
	grp_look_camer( ap );				// �J�����Ɍ����悤�ɂ���
}
void break_02_flash_exec( TASK *ap )
{
	ap->pos[ Z ] -= 25.0f*EFFECT_SPEED;				// ���W�ړ�
	ap->work1[ X ]++;
	if( ap->work1[ X ] > 7 )			// ���莞�Ԍo�߂Ń^�X�N�G���h
	{
		effect_02_bom_gen(  ap->pos[ X ], ap->pos[ Y ], ap->pos[ Z ], 10 );
		TASK_end( ap );
		return;
	}
	grp_look_camer( ap );				// �J�����̕����������悤�ɂ���B
}
void break_effect_02_exec( TASK *ap )
{
	ap->pos[ Z ] -= 25.0f*EFFECT_SPEED;				// ���W�ړ�
	ap->work1[ X ]++;

// �A�j���[�V��������
	if( ap->work1[ X ] % 3 == 0 )
		ap->anime_no++;
	if( ap->anime_no > 11 )				// ����̃A�j���i���o�[�ɂȂ�����^�X�N�G���h
	{
		TASK_end( ap );
		return;
	}
	grp_look_camer( ap );				// �J�����������悤�ɂ���
}

void break_02_flash( FLOAT pos_x, FLOAT pos_y, FLOAT pos_z )
{
	TASK *ap;
	ap = TASK_start_GRP( break_02_flash_exec, GROUP_UI, TEXTURE_EFFECT, effect_rect, 3, "�����t���b�V��" );
	ap->grp_mode = USE_3DPOS;
	ap->pos[ X ] = pos_x;
	ap->pos[ Y ] = pos_y;
	ap->pos[ Z ] = pos_z;
	ap->scale[ X ] = 9.0f;
	ap->scale[ Z ] = ap->scale[ Y ] = ap->scale[ X ];
	ap->base_color[ 0 ][ 0 ] = 180;
	ap->pri = PRI_HIT_EFFECT + 1;
}

void break_02_light( FLOAT pos_x, FLOAT pos_y, FLOAT pos_z )
{
	TASK *ap;
	ap = TASK_start_GRP( break_02_light_exec, GROUP_UI, TEXTURE_EFFECT, effect_rect, 4, "�M���t���b�V��" );
	ap->grp_mode = USE_3DPOS;
	ap->pos[ X ] = pos_x;
	ap->pos[ Y ] = pos_y;
	ap->pos[ Z ] = pos_z;
	ap->scale[ X ] = 0.0f;
	ap->scale[ Z ] = ap->scale[ Y ] = ap->scale[ X ];
	ap->pri = PRI_HIT_EFFECT + 2;

}

void break_effect_02( FLOAT pos_x, FLOAT pos_y, FLOAT pos_z )
{
	TASK *ap;
	ap = TASK_start_GRP( break_effect_02_exec, GROUP_UI, TEXTURE_BREAK, break_bom_effect_rect, 0, "���j���̔���" );
	ap->grp_mode = USE_3DPOS;
	ap->pos[ X ] = pos_x;
	ap->pos[ Y ] = pos_y;
	ap->pos[ Z ] = pos_z;
	ap->scale[ X ] = 16.0f;
	ap->scale[ Z ] = ap->scale[ Y ] = ap->scale[ X ];
	SOZ_play_se( SE_BREAK_BOM, 1.0f, 0, 1.0f );
	ap->pri = PRI_HIT_EFFECT;
	ap->base_color[ 0 ][ 0 ] = 180;
	ap->delay = 10;

	break_02_flash( pos_x, pos_y, pos_z );
	break_02_light( pos_x, pos_y, pos_z );
	break_smoke( pos_x, pos_y, pos_z );
	break_smoke( ap );
}


//------------------------------------------------------------------------------------------------------------------------------------------------------
// �����G�t�F�N�g01
//------------------------------------------------------------------------------------------------------------------------------------------------------
void break_bom_effect_exec( TASK *ap )
{
	ap->work1[ X ]++;

// �A�j���[�V��������
	if( ap->work1[ X ] % 5 == 0 )
		ap->anime_no++;
// ����̃A�j���i���o�[�ɂȂ�����^�X�N�G���h����B
	if( ap->anime_no > 11 )
	{
		TASK_end( ap );
		return;
	}
	ap->pos[ Z ] -= 25.0f*EFFECT_SPEED;		// ���W�ړ�
}
void break_bom_effect( FLOAT pos_x, FLOAT pos_y, FLOAT pos_z )
{
	TASK *ap;
	ap = TASK_start_GRP( break_bom_effect_exec, GROUP_UI, TEXTURE_BREAK, break_bom_effect_rect, 0, "���j���̔���" );
	ap->grp_mode = USE_3DPOS;
	ap->pos[ X ] = pos_x;
	ap->pos[ Y ] = pos_y;
	ap->pos[ Z ] = pos_z;
	ap->scale[ X ] = 4.0f;
	ap->scale[ Z ] = ap->scale[ Y ] = ap->scale[ X ];
	SOZ_play_se( SE_BREAK_BOM, 1.0f, 0, 1.0f );
	ap->pri = PRI_HIT_EFFECT;
	ap->base_color[ 0 ][ 0 ] = 180;
}

//------------------------------------------------------------------------------------------------------------------------------------------------------
// �����G�t�F�N�g00
//------------------------------------------------------------------------------------------------------------------------------------------------------
void break_effect_exec( TASK *ap )
{
	ap->work1[ X ]++;
// �A�j���[�V��������
	if( ap->work1[ X ] % 3 == 0 )
		ap->anime_no++;
// ����̃A�j���i���o�[�ɂȂ�����^�X�N�G���h����B
	if( ap->anime_no >= 2 )
	{
		TASK_end( ap );
		return;
	}
	ap->pos[ Z ] -= 25.0f*EFFECT_SPEED;			// ���W�ړ�
}
void break_effect( FLOAT pos_x, FLOAT pos_y, FLOAT pos_z )
{
	TASK *ap;
	ap = TASK_start_GRP( break_effect_exec, GROUP_UI, TEXTURE_BREAK, break_effect_rect, 0, "���j���̊ۂ�����" );
	ap->delay = Rand2( 0, 30 );
	ap->grp_mode = USE_3DPOS;
	ap->pos[ X ] = pos_x;
	ap->pos[ Y ] = pos_y;
	ap->pos[ Z ] = pos_z;
	ap->work1[ X ] = 0;
	ap->scale[ X ] = 10.0f;
	ap->scale[ Z ] = ap->scale[ Y ] = ap->scale[ X ];
	ap->pri = PRI_HIT_EFFECT;
	ap->base_color[ 0 ][ 0 ] = 180;
	if( life <= 0 )
		ap->pri = PRI_JIKI + 10;
}

//------------------------------------------------------------------------------------------------------------------------------------------------------
// ���@�o�[�i�[�G�t�F�N�g
//------------------------------------------------------------------------------------------------------------------------------------------------------
void jiki_burner_effect_exec( TASK *ap )
{
	if( life <= 0 )								// ���@�̎c�@���Ȃ��Ȃ�����^�X�N�G���h������
	{
		TASK_end( ap );
		return;
	}
	ap->base_color[ 0 ][ 0 ] -= 16;				// �����x��������
	if( ap->base_color[ 0 ][ 0 ] % 2 == 0 )
		illusion_start( ap, 50, BLEND_ADD );
	switch ( ap->work1[ X ] )
	{
		case 0:									// �X�P�[�������������傫���Ȃ�
			ap->scale[ X ] += ap->fwork1[ X ];
			if( ap->scale[ X ] > 0.9f )
				ap->work1[ X ] = 1;
			ap->base_color[ 0 ][ 2 ] -= 0x4;
			break;

		case 1:									// ���t���[���X�P�[��������������B���̒l�����������^�X�N�G���h�B
			ap->scale[ X ] -= ap->fwork1[ X ];
			ap->base_color[ 0 ][ 2 ] -= 8;
			ap->base_color[ 0 ][ 3 ] -= 8;
			if( ap->scale[ X ] <= 0.8f )
			{
				TASK_end( ap );
				return;
			}
			break;
	}
	ap->scale[ Z ] = ap->scale[ Y ] = ap->scale[ X ];
	ap->pos[ Z ] -= 40;
	grp_look_camer( ap );
}

void jiki_burner_effect( TASK *actp, FLOAT space )
{
	TASK *ap;
	ap = TASK_start_MODEL( jiki_burner_effect_exec, GROUP_MY_SHIP, MODEL_SHOT, TEXTURE_BURNER, "���@�̃o�[�i�[�G�t�F�N�g" );
	ap->grp_mode = TEST_ZBUFFER;
	ap->blend_type = BLEND_ADD;
	ap->pos[ X ] = actp->pos[ X ] + SOZ_get_cos( -actp->ang[ Z ] )*space;
	ap->pos[ Y ] = actp->pos[ Y ] + SOZ_get_sin( -actp->ang[ Z ] )*space - 10;
	ap->pos[ Z ] = actp->pos[ Z ] - 400.0f;
	ap->ang[ Z ] = Rand2( 0x0000, 0xffff );
	ap->base_color[ 0 ][ 0 ] = 0xff;
	ap->base_color[ 0 ][ 1 ] = 0x08;
	ap->base_color[ 0 ][ 2 ] = 0x88;
	ap->base_color[ 0 ][ 3 ] = 0xff;
	ap->work1[ X ] = 0;
	ap->fwork1[ X ] = 0.05f;
	ap->scale[ X ] = 0.8f;
	ap->scale[ Y ] = ap->scale[ X ];
	ap->pri = PRI_BURNER;
}

//------------------------------------------------------------------------------------------------------------------------------------------------------
// �G�~�T�C���G�t�F�N�g
//------------------------------------------------------------------------------------------------------------------------------------------------------

void ene_ms_effect_exec( TASK *ap )
{
	ap->pri--;
	if( ap->pri % 3 == 0 )
		illusion_start( ap, 5, BLEND_ADD );
	ap->base_color[ 0 ][ 0 ] -= 96;		// �����������x���グ��
	ap->base_color[ 0 ][ 1 ] = ap->base_color[ 0 ][ 2 ] = ap->base_color[ 0 ][ 3 ] -= 75;
	if( ap->base_color[ 0 ][ 0 ] < 10 )	// ����̓����x�𒴂�����^�X�N�G���h
	{
		TASK_end( ap );
		return;
	}
}
void ene_ms_effect_start( FLOAT pos_x, FLOAT pos_y, FLOAT pos_z  )		// �G�~�T�C���G�t�F�N�g
{
	TASK *ap;
	ap = TASK_start_GRP( ene_ms_effect_exec, GROUP_UI, TEXTURE_EFFECT, effect_rect, 1, "�G�~�T�C���G�t�F�N�g" );
	ap->grp_mode = USE_3DPOS;
	ap->pos[ X ] = pos_x;
	ap->pos[ Y ] = pos_y;
	ap->pos[ Z ] = pos_z;
	ap->ang[ Z ] = Rand2( 0x0000, 0xffff );
	ap->pri = PRI_SHOT_EFFECT;
	ap->scale[ Y ] = ap->scale[ X ] = 3.0f;
	ap->base_color[ 0 ][ 0 ] = 0xf0;
	ap->work1[ X ] = 0;
}

//------------------------------------------------------------------------------------------------------------------------------------------------------
// ���@�V���b�g�G�t�F�N�g
//------------------------------------------------------------------------------------------------------------------------------------------------------
void shot_effect_exec( TASK *ap )
{
	illusion_start( ap, 50, BLEND_ADD );
	ap->base_color[ 0 ][ 0 ] -= 96;		// �����������x��������
	if( ap->base_color[ 0 ][ 0 ] < 10 )	// ����̓����x�𒴂�����^�X�N�G���h
	{
		TASK_end( ap );
		return;
	}
}
void shot_effect_start( FLOAT pos_x, FLOAT pos_y, FLOAT pos_z  )
{
	TASK *ap;
	ap = TASK_start_GRP( shot_effect_exec, GROUP_UI, TEXTURE_EFFECT, effect_rect, 2, "�ˌ��G�t�F�N�g" );
	ap->grp_mode = USE_3DPOS;
	ap->pos[ X ] = pos_x;
	ap->pos[ Y ] = pos_y;
	ap->pos[ Z ] = pos_z;
	ap->ang[ Z ] = Rand2( 0x0000, 0xffff );
	ap->pri = PRI_ENEMY -100;
	ap->scale[ Y ] = ap->scale[ X ] = 3.0f;
}

//------------------------------------------------------------------------------------------------------------------------------------------------------
// ���@�V���b�g�q�b�g�G�t�F�N�g
//------------------------------------------------------------------------------------------------------------------------------------------------------
void hit_flash( TASK *ap )
{
	/*
	ap->workE[ D ] ++;
	if( ap->workE[ D ] < 5 )
		ap->shader_pass = SHADER_WHITE;
	else
		ap->shader_pass = 0;
		*/
}

//------------------------------------------------------------------------------------------------------------------------------------------------------
// ���@�V���b�g�q�b�g�G�t�F�N�g
//------------------------------------------------------------------------------------------------------------------------------------------------------

void shot_hit_effect_core_exec( TASK *ap )
{
	ap->base_color[ 0 ][ 0 ] -= 10;	// ���t���[�������x��������
	ap->pos[ X ] += ap->vec[ X ];
	ap->pos[ Y ] += ap->vec[ Y ];
	ap->pos[ Z ] += ap->vec[ Z ];
	if( ap->base_color[ 0 ][ 0 ] < 10 )	// ����̓����x�����������^�X�N�G���h
	{
		TASK_end( ap );
		return;
	}
}

void shot_hit_effect_core( FLOAT pos_x, FLOAT pos_y, FLOAT pos_z )
{
	TASK *ap;
	ap = TASK_start_GRP( shot_hit_effect_core_exec, GROUP_UI, TEXTURE_HIT_EFF, hit_effect_rect, 0, "���@�V���b�g�q�b�g���G�t�F�N�g" );
	ap->pos[ X ] = pos_x;
	ap->pos[ Y ] = pos_y;
	ap->pos[ Z ] = pos_z;
	ap->grp_mode = USE_3DPOS;
	ap->vec[ X ] = F_Rand2( -20, 20 );
	ap->vec[ Y ] = F_Rand2( -20, 20 );
	ap->vec[ Z ] = F_Rand2( -20, 20 );
	ap->work1[ X ] = 0;
	ap->blend_type = BLEND_ADD;
	ap->scale[ X ] = 0.5f;
	ap->scale[ Y ] = ap->scale[ X ];
	ap->pri = PRI_HIT_EFFECT;
}

void shot_hit_effect( FLOAT pos_x, FLOAT pos_y, FLOAT pos_z )
{
	SINT32 num = 0;
	for( num = 0; num < 10; num++ )
		shot_hit_effect_core( pos_x, pos_y, pos_z );	// �q�b�g���̉��F���G�t�F�N�g�𐶐�����
}

