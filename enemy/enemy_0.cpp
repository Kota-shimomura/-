#ifdef WINDOWS_PC
#include    "C:/project/libs/systemOZ_v4/soz.h"
#else
#include    "D:/project/guardians_2dx/proj.win32/src/systemOZ/soz.h"
#endif

#include    "C:/project/bace/src/game/game_include.h"
//------------------------------------------------------------------------------------------------------------------------------------------------------
// 
//			ENEMY
// 
//------------------------------------------------------------------------------------------------------------------------------------------------------

//------------------------------------------------------------------------------------------------------------------------------------------------------
// �G�̒e
//------------------------------------------------------------------------------------------------------------------------------------------------------
void lock_on_exec( TASK *ap )
{
#if 1
//	if( ap->pos[ Z ] > 500.0f )
		jiki_look( ap );					// ���@�̕���������
#endif
	ap->work2[ X ] ++;

// ���W�ړ�
	ap->pos[ X ] += ap->vec[ X ];
	ap->pos[ Y ] -= ap->vec[ Y ];
	ap->pos[ Z ] -= ap->vec[ Z ];

// �~�T�C���G�t�F�N�g�̔���
	if( ap->work2[ X ] % 8 == 0 )
		ene_ms_effect_start( ap->pos[ X ], ap->pos[ Y ], ap->pos[ Z ] + 100 );
	if( ap->work2[ X ] > 60 * 10 )			// ���莞�Ԍo�߂Ń^�X�N�G���h
	{
		TASK_end( ap );
		return;
	}
}
void ene_ms( FLOAT pos_x, FLOAT pos_y, FLOAT pos_z )
{
	TASK *ap;
	ap = TASK_start_MODEL( lock_on_exec, GROUP_BULLET, MODEL_ENE_MS, TEXTURE_ENE_MS, "�G�̃~�T�C��( ���@�ǔ� )" );
	ap->grp_mode = WRITE_ZBUFFER | TEST_ZBUFFER | USE_LIGHTING | USE_3DPOS;	//| USE_SPECULAR ;
	ap->pos[ X ] = pos_x;
	ap->pos[ Y ] = pos_y;
	ap->pos[ Z ] = pos_z;
	ap->vec[ X ] = 0;
	ap->vec[ Y ] = 0;
	ap->vec[ Z ] = 0;
	ap->pri = PRI_ENEMY + 10;
	ap->scale[ X ] = 0.5f;
	ap->scale[ Y ] = 0.5f;
	ap->ang[ X ] = 0x0000;
	ap->ang[ Y ] = 0x0000;
	ap->ang[ Z ] = 0x0000;
	ap->HP = 20000;
	ap->SCORE = 100;
	ap->callback = enemy_callback;
	ap->work2[ D ] = 90;	// �~�T�C���̈ړ����x
//	lockon_jiki( ap );
//�@���̔���g��ݒ�
	ap->sphire = 200.0f;
	ap->sphire_shift[ X ] = 0;
	ap->sphire_shift[ Y ] = 0;
	ap->sphire_shift[ Z ] = 0;
	missile_start_effect( ap->pos[ X ], ap->pos[ Y ], ap->pos[ Z ] );

	ap->specular[ 0 ] = 1.0f;
	ap->specular[ 1 ] = 1.0f;
	ap->specular[ 2 ] = 1.0f;
	ap->ambient[ 0 ] = 0.2f;
	ap->ambient[ 1 ] = 0.0f;
	ap->ambient[ 2 ] = 0.3f;
	ap->emissive[0] = 0.25f;
	ap->emissive[1] = 0.25f;
	ap->emissive[2] = 0.25f;
 	ap->pow = 6.0f;
	SOZ_material_setting( ap );
}


void bullet_exec( TASK *ap )
{
// ���W�v�Z
	ap->pos[ X ] += ap->vec[ X ];
	ap->pos[ Y ] += ap->vec[ Y ];
	ap->pos[ Z ] -= ap->vec[ Z ];

	if( ap->pos[ Z ] <= -10000 )	// ������W�𒴂����^�X�N�G���h
	{
		TASK_end( ap );
		return;
	}
}
void bullet_start( FLOAT pos_x, FLOAT pos_y, FLOAT pos_z, SINT32 ang_x, ANGLE ang_y, FLOAT speed  )
{
	TASK *ap;
	ap = TASK_start_MODEL( bullet_exec, GROUP_BULLET, MODEL_SHOT, TEXTURE_BULLET, "�G�̒e" );
	ap->grp_mode = TEST_ZBUFFER;
	ap->blend_type = BLEND_ADD;
	ap->pos[ X ] = pos_x;
	ap->pos[ Y ] = pos_y;
	ap->pos[ Z ] = pos_z;
	ap->vec[ X ] = 0;
	ap->vec[ Y ] = 0;
	ap->vec[ Z ] = 0;
	ap->ang[ X ] = ang_x;
	ap->ang[ Y ] = ang_y;
	ap->ang[ Z ] = 0x0000;
	ap->pri = PRI_ENEMY + 8;

	ap->scale[ Z ] = ap->scale[ Y ] = ap->scale[ X ] = 1.5f;
	ap->fwork1[ X ] = speed;

	ap->callback = enemy_callback;
	ap->sphire = 100.0f;
	ap->sphire_shift[ X ] = 0;
	ap->sphire_shift[ Y ] = 0;
	ap->sphire_shift[ Z ] = 0;

	ang_vec_setting( ap, ap->fwork1[ X ] );	// ang����i�ރx�N�g�����Z�o����
	if( ap->vec[ Z ] < 0 )
		ap->vec[ Z ] *= -1;
}

/// -------------------- �G�̓��� ----------------------------------------------------------------------------------------------------------------------
//------------------------------------------------------------------------------------------------------------------------------------------------------
// �O�j���O�j���i�ޓG
//------------------------------------------------------------------------------------------------------------------------------------------------------
void move_left_right( TASK *ap )
{
	hit_flash( ap );	// �q�b�g���ɔ��ɓ_��
	ap->work2[ X ]++;
// �x�N�g���v�Z
	ap->vec[ X ] = ap->vec[ Z ] /4;
	if( ap->work2[ X ] > 60 )
		ap->work2[ X ] = 0;
	else if( ap->work2[ X ] > 30 )
		ap->vec[ X ] *= -1;

// ���W�ړ�
	ap->pos[ Z ] += ap->vec[ Z ]/2;
	ap->pos[ X ] += ap->vec[ X ];

// ������W�𒴂�����^�X�N�G���h
	if( ap->pos[ Z ] <= -3000 )
	{
		TASK_end( ap );
		return;
	}
}

void move_up_down( TASK *ap )
{
	hit_flash( ap );	// �q�b�g���ɔ��ɓ_��
	ap->work2[ X ]++;

// �x�N�g���v�Z
	ap->vec[ Y ] = ap->vec[ Z ] /4;
	if( ap->work2[ X ] > 60 )
		ap->work2[ X ] = 0;
	else if( ap->work2[ X ] > 30 )
		ap->vec[ Y ] *= -1;

// ���W�ړ�
	ap->pos[ Z ] += ap->vec[ Z ]/2;
	ap->pos[ Y ] += ap->vec[ Y ];

// ������W�𒴂�����^�X�N�G���h
	if( ap->pos[ Z ] <= -3000 )
	{
		TASK_end( ap );
		return;
	}
}

//------------------------------------------------------------------------------------------------------------------------------------------------------
// �e�����܂������i�ޓG
//------------------------------------------------------------------------------------------------------------------------------------------------------
void move_straight_bullet_on( TASK *ap )
{
	hit_flash( ap );	// �q�b�g���ɔ��ɓ_��
	ap->pos[ Z ] += ap->vec[ Z ];
	if( life > 0 )		// ���@�̎c��Ȃ��Ȃ�����^�X�N������
		switch ( ap->work2[ X ] )
		{
			case 0:	// ����̒n�_�ɂ�����e�����������ƈړ����x���オ��
				if( ap->pos[ Z ] <= 12000 )
				{
					ene_ms( ap->pos[ X ], ap->pos[ Y ], ap->pos[ Z ] );
					ap->work2[ X ] = 1;
				}
				break;

			case 1:	// ����̒n�_�𒴂�����^�X�N�G���h������
				if( ap->pos[ Z ] <= -1000.0f )
				{
					TASK_end( ap );
					return;
				}
				break;
		}

}

//------------------------------------------------------------------------------------------------------------------------------------------------------
// �E���o�� �����Ɍ������Đi��
//------------------------------------------------------------------------------------------------------------------------------------------------------
void move_left_back( TASK *ap )
{
	hit_flash( ap );	// �q�b�g���ɔ��ɓ_��
	switch ( ap->work2[ X ] )
	{
		case 0:
			ap->vec[ X ] = -20.0f;
			ap->work2[ X ]++;
			break;

		case 1:
			if( ap->pos[ Z ] >= 8000.0f)	// ����̍��W�𒴂�����
			{
				if( life > 0 )		// ���@�̎c��Ȃ��Ȃ�����^�X�N������
					ene_ms( ap->pos[ X ], ap->pos[ Y ], ap->pos[ Z ] );	// �~�T�C���𔭎�
				ap->work2[ X ] = 2;	// �~�T�C�����ꔭ�����o�Ȃ��悤��
			}
			break;

		case 2:	// ������W�𒴂�����^�X�N�G���h������
			if( ap->pos[ Z ] >= 30000 )
			{
				TASK_end( ap );
				return;
			}
			break;
	}

// ���W�ړ�
	ap->pos[ Z ] += 200.0f;
	ap->pos[ X ] += ap->vec[ X ];
	ap->ang[ X ] += 0x0020;
	ap->ang[ Y ] = 0xc000;	// �ʏ�̓G�Ɣ��Ε�������������
	ap->vec[ X ] -= 0.1f;
}

//------------------------------------------------------------------------------------------------------------------------------------------------------
// �����o�� �E���Ɍ������Đi��
//------------------------------------------------------------------------------------------------------------------------------------------------------
void move_right_back( TASK *ap )
{
	hit_flash( ap );	// �q�b�g���ɔ��ɓ_��
	switch ( ap->work2[ X ] )
	{
		case 0:
			ap->vec[ X ] = 20.0f;
			ap->work2[ X ]++;
			break;

		case 1:
			if( ap->pos[ Z ] >= 8000.0f)	// ����̍��W�𒴂�����
			{
				if( life > 0 )		// ���@�̎c��Ȃ��Ȃ�����^�X�N������
					ene_ms( ap->pos[ X ], ap->pos[ Y ], ap->pos[ Z ] );	// �~�T�C���𔭎�
				ap->work2[ X ] = 2;	// �~�T�C�����ꔭ�����o�Ȃ��悤��
			}
			break;

		case 2:		// ������W�𒴂�����^�X�N�G���h
			if( ap->pos[ Z ] >= 30000 )
			{
				TASK_end( ap );
				return;
			}
			break;
	}
	ap->pos[ Z ] += 200.0f;
	ap->pos[ X ] += ap->vec[ X ];
	ap->ang[ X ] -= 0x0020;
	ap->ang[ Y ] = 0xc000;	// �ʏ�̓G�Ɣ��Ε�������������
	ap->vec[ X ] += 0.1f;
}

//------------------------------------------------------------------------------------------------------------------------------------------------------
// �オ��Ȃ��璼�i
//------------------------------------------------------------------------------------------------------------------------------------------------------
void move_up_straight_exec( TASK *ap )
{
	hit_flash( ap );	// �q�b�g���ɔ��ɓ_��
// ���W�ړ�
	ap->pos[ Y ] += 1.5f;
	ap->pos[ Z ] += ap->vec[ Z ];

// ������W�𒴂�����^�X�N�G���h
	if( ap->pos[ Z ] < -3000.0f )
	{
		TASK_end( ap );
		return;
	}
}

//------------------------------------------------------------------------------------------------------------------------------------------------------
// ����Ȃ��璼�i
//------------------------------------------------------------------------------------------------------------------------------------------------------
void move_down_straight_exec( TASK *ap )
{
	hit_flash( ap );	// �q�b�g���ɔ��ɓ_��

// ���W�ړ�
	ap->pos[ Y ] -= 1.5f;
	ap->pos[ Z ] += ap->vec[ Z ];

// ������W�𒴂�����^�X�N�G���h
	if( ap->pos[ Z ] < -3000.0f )
	{
		TASK_end( ap );
		return;
	}
}

//------------------------------------------------------------------------------------------------------------------------------------------------------
// ���i
//------------------------------------------------------------------------------------------------------------------------------------------------------
void move_straight_exec( TASK *ap )
{
	hit_flash( ap );	// �q�b�g���ɔ��ɓ_��
	ap->pos[ Z ] += ap->vec[ Z ];
	if( ap->pos[ Z ] < -3000.0f )
	{
		TASK_end( ap );
		return;
	}
}
/// ----------------------------------------------------------------------------------------------------------------------------------------------------
void test_move( TASK *ap )
{
	ap->ang[ Y ] += 0x0010;
	hit_flash( ap );	// �q�b�g���ɔ��ɓ_��
	ap->pos[ Z ] = 3000.0f;
	SOZ_locate_print( 1,1, " %d", ap->HP );
	if( SOZ_Inkey_TRG( DIK_T ) )
		ap->HP = 30000;
}


//------------------------------------------------------------------------------------------------------------------------------------------------------
// �G�̃f�[�^�\����
//------------------------------------------------------------------------------------------------------------------------------------------------------
ENEMY_MOVE enemy_move[]=
{
	{ test_move, enemy_callback},

	{ move_straight_exec, enemy_callback },
	{ move_down_straight_exec, enemy_callback },
	{ move_up_straight_exec, enemy_callback },
	{ move_right_back, enemy_callback },
	{ move_left_back, enemy_callback },
	{ move_straight_bullet_on, enemy_callback },
	{ move_up_down, enemy_callback },
	{ move_left_right, enemy_callback },
};

ENEMY_APPEARANCE boss_skin[]=
{
	{ MODEL_BOSS, TEXTURE_BOSS, { 1.0f, 1.0f, 1.0f }, { 0.0f, 0.0f, 0.0f }, { 0.0f, 0.0f, 0.0f }, { 1.3f, 1.3f, 1.3f }, 5.0f },
};

ENEMY_APPEARANCE enemy_skin[]=
{
//	�@���f���̔ԍ��@�摜�̔ԍ��@�@�@ specular[ RGB ] �̒l      ambient[ RGB ] �̒l     emissive[ RGB ]�@�̒l     diffuse[ RGB ]�@�̒l    pow�̒l
	{ MODEL_ENE_00, TEXTURE_ENE_00, { 0.7f, 0.7f, 1.5f }, { 0.15f, 0.15f, 0.15f }, { 0.5f, 0.5f, 0.5f }, { 1.45f, 1.45f, 1.45f, }, 3.0f },
	{ MODEL_ENE_01, TEXTURE_ENE_01, { 0.7f, 0.7f, 1.5f }, { 0.15f, 0.15f, 0.15f }, { 0.5f, 0.5f, 0.5f }, { 1.45f, 1.45f, 1.45f, }, 3.0f },
	{ MODEL_ENE_02, TEXTURE_ENE_02, { 0.7f, 0.7f, 1.5f }, { 0.15f, 0.15f, 0.15f }, { 0.5f, 0.5f, 0.5f }, { 1.45f, 1.45f, 1.45f, }, 3.0f },
	{ MODEL_ENE_03, TEXTURE_ENE_03, { 0.7f, 0.7f, 1.5f }, { 0.15f, 0.15f, 0.15f }, { 0.5f, 0.5f, 0.5f }, { 1.45f, 1.45f, 1.45f, }, 3.0f },
	{ MODEL_ENE_04, TEXTURE_ENE_04, { 0.7f, 0.7f, 1.5f }, { 0.15f, 0.15f, 0.15f }, { 0.5f, 0.5f, 0.5f }, { 1.45f, 1.45f, 1.45f, }, 3.0f },
//	{ MODEL_ENE_MS, TEXTURE_ENE_MS, { 2.02f, 2.02f, 2.02f }, { 0.6f, 0.6f, 0.6f }, { 0.06f, 0.06f, 0.06f }, { 1.0f, 1.0f, 1.0f, }, 2.4f },
//	{ MODEL_ENE_07, TEXTURE_ENE_07, { 2.02f, 2.02f, 2.02f }, { 0.6f, 0.6f, 0.6f }, { 0.06f, 0.06f, 0.06f }, { 1.0f, 1.0f, 1.0f, }, 2.4f },
};

//------------------------------------------------------------------------------------------------------------------------------------------------------
// �G���ʏ�������
//------------------------------------------------------------------------------------------------------------------------------------------------------
void enemy_disp( SINT32 move_id, SINT32 appearance_id, FLOAT pos_x, FLOAT pos_y, FLOAT pos_z, SINT32 hp, SINT32 add_score )
{
	TASK *ap;
	ap = TASK_start_MODEL( enemy_move[move_id].exe_func, GROUP_ENEMY, enemy_skin[appearance_id].model_no, enemy_skin[appearance_id].tex_no, "���i����G" );
	ap->grp_mode = WRITE_ZBUFFER | TEST_ZBUFFER | USE_LIGHTING | USE_3DPOS;	//| USE_SPECULAR;
	ap->pos[ X ] = pos_x;
	ap->pos[ Y ] = pos_y;
	ap->pos[ Z ] = pos_z;
	ap->vec[ Z ] = -150.0f;
	ap->ang[ Y ] = 0x4000;
	ap->callback = enemy_move[ move_id ].callback;

//�@���̔���g��ݒ�
	ap->sphire = 200.0f;
//�@���̔���g��ݒ�
	ap->sphire_shift[ X ] = 0;
	ap->sphire_shift[ Y ] = 0;
	ap->sphire_shift[ Z ] = 0;

	ap->HP = hp;		// work9[ Y ]�ɑ̗̖͂�����������
	ap->SCORE = add_score;	// work9[ Z ]�ɓ|���ꂽ���ɉ��Z����X�R�A

	ap->pri = PRI_ENEMY;

// �}�e���A���̐ݒ�
	ap->specular[ 0 ] = enemy_skin[ appearance_id ].specular[ 0 ];
	ap->specular[ 1 ] = enemy_skin[ appearance_id ].specular[ 1 ];
	ap->specular[ 2 ] = enemy_skin[ appearance_id ].specular[ 2 ];
	ap->ambient[ 0 ]  = enemy_skin[ appearance_id ].ambient[ 0 ];
	ap->ambient[ 1 ]  = enemy_skin[ appearance_id ].ambient[ 1 ];
	ap->ambient[ 2 ]  = enemy_skin[ appearance_id ].ambient[ 2 ];
	ap->emissive[ 0 ] = enemy_skin[ appearance_id ].emissive[ 0 ];
	ap->emissive[ 1 ] = enemy_skin[ appearance_id ].emissive[ 1 ];
	ap->emissive[ 2 ] = enemy_skin[ appearance_id ].emissive[ 2 ];
	ap->diffuse[ 0 ]  = enemy_skin[ appearance_id ].diffuse[ 0 ];
	ap->diffuse[ 1 ]  = enemy_skin[ appearance_id ].diffuse[ 1 ];
	ap->diffuse[ 2 ]  = enemy_skin[ appearance_id ].diffuse[ 2 ];
 	ap->pow = enemy_skin[ appearance_id ].pow;
	SOZ_material_setting( ap );
// ------------ MOVE�p ----------------
	ap->work2[ X ] = 0;
	ap->work2[ Y ] = 0;
	ap->work2[ Z ] = 0;
	ap->work2[ P ] = 0;
	ap->work2[ D ] = 200;
// ------------ ��e���o�p ----------------
	ap->workE[ D ] = 100;
// ------------ ���j���o�p ----------------
	ap->workE[ X ] = 0;
	ap->workE[ Y ] = 0;
	ap->workE[ Z ] = 0;
// ----------------------------------------
}


//------------------------------------------------------------------------------------------------------------------------------------------------------
// �X�e�[�W�{�X
//------------------------------------------------------------------------------------------------------------------------------------------------------

// �o��V�[���̃t�@���l���̂悤�ȉ��o
void start_bullet_gen_exec( TASK *ap )
{
	SOZ_play_se( SE_BOSS_BIT, 1.0f, 1, 1.0f );
	ap->ang[ Z ] = ap->angle[ Z ];
	burner_effect( ap,    0.0f, ap->pos[ Z ] -500.0f, -150.0f );
	burner_effect( ap, -100.0f, ap->pos[ Z ] -500.0f, -150.0f );
	burner_effect( ap,  100.0f, ap->pos[ Z ] -500.0f, -150.0f );
	ap->ang[ Z ] = 0x0000;
	if( ap->work1[ X ]++ % 10 == 0 )
		illusion_start( ap, 25, BLEND_ADD );

	ap->pos[ Z ] += ap->vec[ Z ];
	ap->vec[ Z ] *= 1.1f;
	if( ap->pos[ Z ] > 30000 )	// �w����W�𒴂�����^�X�N�G���h
	{
		TASK_end( ap );
		return;
	}
}
void start_bullet_gen( SINT32 id, ANGLE ang_y, FLOAT pos_x, FLOAT pos_y )
{
	TASK *ap;
	ap = TASK_start_MODEL( start_bullet_gen_exec, GROUP_UI, MODEL_BULLET_GEN, TEXTURE_BULLET_GEN, "�G�̒e�̔����I�u�W�F�N�g" );
	ap->grp_mode = WRITE_ZBUFFER | TEST_ZBUFFER | USE_LIGHTING | USE_3DPOS;
	ap->delay = 15 * id;					// �I�u�W�F�N�g��x�点�Ĕ���������
	ap->pos[ X ] = pos_x;
	ap->pos[ Y ] = pos_y;
	ap->pos[ Z ] = -10000;
	ap->vec[ Z ] = 100;
	ap->ang[ Y ] = 0x4000;
	ap->ang[ X ] = ang_y;
	ap->ang[ Z ] = -ang_y;
	ap->angle[ Z ] = -ap->ang[ Z ];
	ap->work1[ X ] = 0;
// 3D���f���̃}�e���A����ݒ�
	ap->specular[ 0 ] = 5.0f;
	ap->specular[ 1 ] = 5.0f;
	ap->specular[ 2 ] = 5.0f;
	ap->ambient[ 0 ] = 0.0f;
	ap->ambient[ 1 ] = 0.0f;
	ap->ambient[ 2 ] = 0.0f;
	ap->emissive[0] = 3.25f;
	ap->emissive[1] = 3.25f;
	ap->emissive[2] = 3.25f;
 	ap->pow = 8.0f;
	SOZ_material_setting( ap );
}


void boss_bullet_gen_exec( TASK *ap )
{
	ap->pos[ Z ] = ap->parent->pos[ Z ] + 1000.0f;
	if( ap->parent->workA[ X ] == 3 )
		ap->work2[ X ] ++;
	ap->work2[ Y ] ++;
	ap->ang[ Z ] += ap->angle[ Z ];		// ���f������]������B
	switch( ap->work1[ X ] )
	{
	case 0:
		if( ap->work2[ X ] > 60 && ap->work2[ X ] < 210 )
			bullet_start( ap->pos[ X ], ap->pos[ Y ], ap->pos[ Z ], 0x0000, 0x0000, 100 );
		else if( ap->work2[ X ] > 420 )
			ap->work2[ X ] = 0;
		break;

	case 1:
		if( ap->work2[ X ] % 260 == 0 )
		{
			bullet_start( ap->pos[ X ], ap->pos[ Y ], ap->pos[ Z ],  0x00f0,  0x0000, 75 +75 *bg_speed );
			bullet_start( ap->pos[ X ], ap->pos[ Y ], ap->pos[ Z ], -0x00f0,  0x0000, 75 +75 *bg_speed );
			bullet_start( ap->pos[ X ], ap->pos[ Y ], ap->pos[ Z ],  0x0000,  0x00f0, 75 +75 *bg_speed );
			bullet_start( ap->pos[ X ], ap->pos[ Y ], ap->pos[ Z ],  0x0000, -0x00f0, 75 +75 *bg_speed );
			ap->work2[ X ] ++;
		}
		else if( ap->work2[ X ] % 240 == 0 )
		{
			bullet_start( ap->pos[ X ], ap->pos[ Y ], ap->pos[ Z ],  0x00f0,  0x00f0, 50 +50 *bg_speed );
			bullet_start( ap->pos[ X ], ap->pos[ Y ], ap->pos[ Z ],  0x00f0, -0x00f0, 50 +50 *bg_speed );
			bullet_start( ap->pos[ X ], ap->pos[ Y ], ap->pos[ Z ], -0x00f0,  0x00f0, 50 +50 *bg_speed );
			bullet_start( ap->pos[ X ], ap->pos[ Y ], ap->pos[ Z ], -0x00f0, -0x00f0, 50 +50 *bg_speed );
			ap->work2[ X ] ++;
		}
		break;

	case 2:
		if( ap->work2[ X ] % 150 == 0 )
		{
			ene_ms( ap->pos[ X ], ap->pos[ Y ], ap->pos[ Z ] + 150.0f );
			ap->work2[ X ] ++;
		}
		break;
	}
	if( ap->parent->HP < 0 )
	{
		break_effect_02( ap->pos[ X ] + F_Rand2( -200.0f, 200.0f ), ap->pos[ Y ] + F_Rand2( -200.0f, 200.0f ), ap->pos[ Z ] + F_Rand2( -200.0f, 200.0f ) );
		break_effect_02( ap->pos[ X ] + F_Rand2( -200.0f, 200.0f ), ap->pos[ Y ] + F_Rand2( -200.0f, 200.0f ), ap->pos[ Z ] + F_Rand2( -200.0f, 200.0f ) );		
		TASK_end( ap );
		return;
	}
	else if( ap->parent->workA[ X ] == 100 )
	{
		ap->pos[ Z ] += ap->parent->vec[ Z ];
		if( ap->pos[ Z ] > 30000 )
		{
			TASK_end( ap );
			return;
		}
	}
}
// �G�̒e�@�����I�u�W�F�N�g		( �E��]: ���[�U�[ / ����]: �U�e / ����]: �~�T�C�� )
void boss_bullet_gen( TASK *actp, SINT32 id, FLOAT pos_x, FLOAT pos_y, SINT32 bullet_mode, SINT32 delay_time )
{
	TASK *ap;
	ap = TASK_start_MODEL( boss_bullet_gen_exec, GROUP_ENEMY, MODEL_BULLET_GEN, TEXTURE_BULLET_GEN, "�G�̒e�̔����I�u�W�F�N�g" );
	ap->grp_mode = WRITE_ZBUFFER | TEST_ZBUFFER | USE_LIGHTING | USE_3DPOS;
	ap->pos[ X ] = pos_x;
	ap->pos[ Y ] = pos_y;
	ap->pos[ Z ] = 7500.0f;
	ap->delay = delay_time;
	ap->work1[ X ] = bullet_mode;
	ap->work2[ X ] = 0;					// �e���˃t���[���v��
	ap->work2[ Y ] = 0;
	ap->pri = PRI_ENEMY + 5;
	ap->parent = actp;
	actp->child[id] = ap;
	switch ( bullet_mode )
	{
	case 0:
		ap->angle[ Z ] = 0x200;
		break;

	case 1:
		ap->angle[ Z ] = -0x200;
		break;

	case 2:
		ap->angle[ Z ] = 0x0000;
		break;
	}

	ap->callback = bullet_gen_callback;
	ap->sphire = 200.0f;				// ���̓����蔻��̐ݒ�
//�@���̔���g��ݒ�
	ap->sphire_shift[ X ] = 0;
	ap->sphire_shift[ Y ] = 0;
	ap->sphire_shift[ Z ] = 0;
	ap->HP = 4500;
	ap->SCORE = 1000;
// 3D���f���̃}�e���A����ݒ�
	ap->specular[ 0 ] = 5.0f;
	ap->specular[ 1 ] = 5.0f;
	ap->specular[ 2 ] = 5.0f;
	ap->ambient[ 0 ] = 0.0f;
	ap->ambient[ 1 ] = 0.0f;
	ap->ambient[ 2 ] = 0.0f;
	ap->emissive[0] = 3.25f;
	ap->emissive[1] = 3.25f;
	ap->emissive[2] = 3.25f;
 	ap->pow = 8.0f;
	SOZ_material_setting( ap );
}




void boss_fase1( TASK *ap )	// �t�F�[�Y1�̓���
{
	switch( ap->workB[ X ] )
	{
		case 0:
			ap->ang[ Z ] -= 0x0010;
			ap->pos[ X ] -= 20.0f;
			if( ap->pos[ X ]  < -750.0f )
				ap->workB[ X ] = 1;
			break;

		case 1:
			if( ap->ang[ Z ] != 0x0000 )
				ap->ang[ Z ] += 0x0010;
			else
				ap->workB[ X ] = 2;
			break;

		case 2:
			ap->ang[ Z ] += 0x0010;
			ap->pos[ X ] += 20.0f;
			if( ap->pos[ X ]  > 750.0f )
				ap->workB[ X ] = 3;
			break;

		case 3:
			if( ap->ang[ Z ] != 0x0000 )
				ap->ang[ Z ] -= 0x0010;
			else
				ap->workB[ X ] = 0;
			break;
	}
}

SINT32 VS_boss[2][100]=
{
	{
		ATTACK_MS,
		ATTACK_CT( 60 ),
		ATTACK_MS,
		ATTACK_CT( 60 ),
		ATTACK_MS2,
		ATTACK_CT( 60 ),
		ATTACK_MS,
		ATTACK_CT( 60 ),
		ATTACK_MS2,
		ATTACK_CT( 60 *2 ),
		ATTACK_MS2,
		ATTACK_CT( 10 ),
		ATTACK_MS2,
		ATTACK_CT( 60 ),
		SEQ_TOP
	},
	{
		ATTACK_MS,
		ATTACK_CT( 60 ),
		ATTACK_MS,
		ATTACK_CT( 60 ),
		ATTACK_MS2,
		ATTACK_CT( 30 ),
		ATTACK_MS2,
		ATTACK_CT( 30 ),
		ATTACK_MS,
		ATTACK_CT( 60 ),
		ATTACK_MS,
		ATTACK_CT( 10 ),
		ATTACK_MS,
		ATTACK_CT( 10 ),
		ATTACK_MS,
		ATTACK_CT( 10 ),
		ATTACK_MS2,
		ATTACK_CT( 60 ),
		SEQ_TOP

	},
};

// �{�X�̃o�[�i�[�G�t�F�N�g�̊֐�
void boss_burner( TASK *ap )
{
	burner_effect( ap,  150.0f, ap->pos[ Z ] -1000.0f, -150.0f );
	burner_effect( ap, -150.0f, ap->pos[ Z ] -1000.0f, -150.0f );
	burner_effect( ap,  400.0f, ap->pos[ Z ] -1000.0f, -150.0f );
	burner_effect( ap, -400.0f, ap->pos[ Z ] -1000.0f, -150.0f );
	burner_effect( ap,  650.0f, ap->pos[ Z ] -1000.0f, -150.0f );
	burner_effect( ap, -650.0f, ap->pos[ Z ] -1000.0f, -150.0f );
}

void boss_atk_seq( TASK *ap )	// �{�X�̍U���V�[�P���X
{
	SINT32 pos_x = 0, pos_y = 0, time = 0;
	ANGLE  ang_x = 0x0000, ang_y = 0x0000, ang_z = 0x0000;
//	�U���N�[���^�C��
	ap->work1[ X ] --;
	if( ap->work1[ X ] > 0 )
		return;

	switch( *ap->work_p[ X ]++ )
	{
		case SEQ_BULLET:	// �o���J���U��
			pos_x = *ap->work_p[ X ];
			pos_y = *ap->work_p[ X ];
			ang_x = *ap->work_p[ X ];
			ang_y = *ap->work_p[ X ];
			ang_z = *ap->work_p[ X ];
			break;

		case SEQ_MS:		// �ǔ��~�T�C��
			ene_ms( ap->pos[ X ], ap->pos[ Y ], ap->pos[ Z ] + 150.0f );
			break;

		case SEQ_MS2:		// �ǔ��~�T�C��
			ene_ms( ap->pos[ X ] + 150.0f, ap->pos[ Y ], ap->pos[ Z ] + 150.0f );
			ene_ms( ap->pos[ X ] - 150.0f, ap->pos[ Y ], ap->pos[ Z ] + 150.0f );
			break;

		case SEQ_MS4:		// �ǔ��~�T�C��
			ene_ms( ap->pos[ X ] + 200.0f, ap->pos[ Y ], ap->pos[ Z ] + 150.0f );
			ene_ms( ap->pos[ X ] + 100.0f, ap->pos[ Y ], ap->pos[ Z ] + 150.0f );
			ene_ms( ap->pos[ X ] - 100.0f, ap->pos[ Y ], ap->pos[ Z ] + 150.0f );
			ene_ms( ap->pos[ X ] - 200.0f, ap->pos[ Y ], ap->pos[ Z ] + 150.0f );
			break;

		case SEQ_CT:		// �U���N�[���^�C���̐ݒ�
			time = *ap->work_p[ X ];
			ap->work1[ X ] = time;
			break;

		case SEQ_TOP:		// �U���V�[�P���X���ŏ��ɖ߂�
			ap->work_p[ X ] = ap->work_p[ Y ];
			break;
	}
}

// �{�X�̓o��V�[��
void boss_entry_1( TASK *ap )
{
	if( ap->pos[ Z ] >= 29000 )	// ����̍��W�ɂ�����퓬�V�[��1�Ƀ��[�h��ύX����
	{
		ap->workA[ X ] = 10;
		ap->pos[ Y ] = 0;
		start_bullet_gen( 0, 0x3000,  1000, -1000 );
		start_bullet_gen( 1, 0x6000, -1000, -1000 );
		start_bullet_gen( 2, 0x0000, -1500,  0 );
		start_bullet_gen( 3, 0x0000,  1500,  0 );
		start_bullet_gen( 4, 0x3000, -1000, 1000 );
		start_bullet_gen( 5, 0x6000,  1000, 1000 );
	}
	else 						// ����̍��W�܂ňړ�����
	{
		ap->pos[ Z ] += ap->vec[ Z ];
		ap->vec[ Z ] += 10;
		ap->pos[ Y ] += 5;
	}
}
void boss_entry_2( TASK *ap )
{
	if( ap->pos[ Z ] <= 9000 )
		ap->workA[ X ] = 1;
	else 						// ����̍��W�܂ňړ�����
		ap->pos[ Z ] -= 50;
}

// �t�F�[�Y�ڍs�V�[��
void boss_next_fase_1( TASK *ap )
{
	if( ap->pos[ Z ] >= 58000 )	// ����̍��W�ɂ�����퓬�V�[���Ƀ��[�h��ύX����
	{
		jiki->workA[ X ] = 50;
		boss_next_code_disp();
		ap->workA[ X ]++;
		ap->pos[ Y ] = 0;
		ap->ang[ Z ] = 0x0000;
	}
	else
	{
		bg_speed += 0.2f;
		ap->pos[ Z ] += ap->vec[ Z ];
		ap->vec[ Z ] *= 1.05f;
		ap->ang[ Z ] += 0x00f0;
	}
}
void boss_next_fase_2( TASK *ap )
{
	if( ap->pos[ Z ] <= 9000 )
		ap->workA[ X ] = 2;
	else 						// ����̍��W�܂ňړ�����
	{
		bg_speed -= 0.05f;
		ap->pos[ Z ] -= 75;
	}
}
// �퓬�V�[�P���X�f�[�^
void boss_battle_data_1( TASK *ap )
{
	boss_bullet_gen( ap, 0, 350.0f,-350.0f, 1, 180 );			// �U���r�b�g�̏���
	boss_bullet_gen( ap, 1, -350.0f,-350.0f, 1, 180 );
	boss_bullet_gen( ap, 2,  350.0f, 350.0f, 1, 300 );
	boss_bullet_gen( ap, 3, -350.0f, 350.0f, 1, 300 );
	ap->work_p[ Y ] = ap->work_p[ X ] = VS_boss[ 0 ];
	ap->workA[ X ] = 3;
}
void boss_battle_data_2( TASK *ap )
{
	boss_bullet_gen( ap, 4, 0.0f, 350.0f, 0, 180 );			// �U���r�b�g�̏���
	boss_bullet_gen( ap, 5, 0.0f,-350.0f, 0, 180 );
	ap->work_p[ Y ] = ap->work_p[ X ] = VS_boss[ 1 ];
	ap->workA[ X ] = 3;
	ap->workA[ D ]++;
}
// �퓬�V�[��
void boss_battle_scene( TASK *ap )
{
	boss_atk_seq( ap );
	boss_fase1( ap );
	if( ap->HP <= 0 )
	{
		ap->workA[ X ] = 4;
	}
	else if( ap->HP < 20000 && ap->workA[ D ] <= 0 )
	{
		camera_vibration_strength();
		break_effect_02( ap->pos[ X ] + F_Rand2( -200.0f, 200.0f ), ap->pos[ Y ] + F_Rand2( -200.0f, 200.0f ), ap->pos[ Z ] + F_Rand2( -200.0f, 200.0f ) );
		break_effect_02( ap->pos[ X ] + F_Rand2( -200.0f, 200.0f ), ap->pos[ Y ] + F_Rand2( -200.0f, 200.0f ), ap->pos[ Z ] + F_Rand2( -200.0f, 200.0f ) );
		break_effect_02( ap->pos[ X ] + F_Rand2( -200.0f, 200.0f ), ap->pos[ Y ] + F_Rand2( -200.0f, 200.0f ), ap->pos[ Z ] + F_Rand2( -200.0f, 200.0f ) );
		break_effect_02( ap->pos[ X ] + F_Rand2( -200.0f, 200.0f ), ap->pos[ Y ] + F_Rand2( -200.0f, 200.0f ), ap->pos[ Z ] + F_Rand2( -200.0f, 200.0f ) );
		ap->workA[ X ] = 20;
		ap->vec[ Z ] = 5;
	}
	if( life == 0 )
	{
		ap->vec[ Z ] = 2.0f;
		ap->workA[ X ] = 100;
	}
}


void boss_exec( TASK *ap )
{
	if( ap->HP > 0 )						// �ϋv�͂��c���Ă���Ȃ�
		boss_burner( ap );					// �o�[�i�[�̕���

	switch( ap->workA[ X ] )
	{
		case 0:	// �o��V�[��
			boss_entry_1( ap );
			break;

		case 10:
			boss_entry_2( ap );
			break;

		case 20:		// �Q�t�F�[�Y�ڂɈڍs�V�[��
			boss_next_fase_1( ap );
			break;

		case 21:
			boss_next_fase_2( ap );
			break;

		case 1:	// �퓬�V�[�� 1	/ �V�[�P���X�̍X�V
			boss_battle_data_1( ap );
			break;

		case 2:	// �퓬�V�[�� 2	/ �V�[�P���X�̍X�V
			boss_battle_data_2( ap );
			break;

		case 3:	// �퓬�V�[��	/ �V�[�P���X���s����
			boss_battle_scene( ap );
			break;

		case 4:	// �ޏ�V�[��
			ap->workA[ P ] ++;
			break_effect( ap->pos[ X ] + F_Rand2( -200.0f, 200.0f ), ap->pos[ Y ] + F_Rand2( -200.0f, 200.0f ), ap->pos[ Z ] + F_Rand2( -200.0f, 200.0f ) );
			if( ap->workA[ P ] == 1 )	// ��񂾂�SCORE�𑝂₷
				score += ( ap->SCORE + bonus ) * ( 1 + rest_missile ) * ( 1+ life );	// SCORE�𑝂₷
			if( ap->workA[ P ] > 30 )
			{
				camera_vibration_strength();	// �J�����������h�炷
				break_effect_02( ap->pos[ X ] + F_Rand2( -400.0f, 400.0f ), ap->pos[ Y ] + F_Rand2( -200.0f, 200.0f ), ap->pos[ Z ] + F_Rand2( -200.0f, 200.0f ) );
				break_effect_02( ap->pos[ X ] + F_Rand2( -400.0f, 400.0f ), ap->pos[ Y ] + F_Rand2( -200.0f, 200.0f ), ap->pos[ Z ] + F_Rand2( -200.0f, 200.0f ) );
				break_effect_02( ap->pos[ X ] + F_Rand2( -400.0f, 400.0f ), ap->pos[ Y ] + F_Rand2( -200.0f, 200.0f ), ap->pos[ Z ] + F_Rand2( -200.0f, 200.0f ) );
				break_effect_02( ap->pos[ X ] + F_Rand2( -400.0f, 400.0f ), ap->pos[ Y ] + F_Rand2( -200.0f, 200.0f ), ap->pos[ Z ] + F_Rand2( -200.0f, 200.0f ) );
				ap->workA[ X ] = 50;
				ap->workA[ P ] = 0;
			}
			break;

		case 50:	// ���j���o
			ap->workA[ P ] ++;
			if( ap->workA[ P ] > 30 )
			{
				camera_vibration_strength();	// �J�����������h�炷
				break_effect_02( ap->pos[ X ] + F_Rand2( -700.0f, -200.0f ), ap->pos[ Y ] + F_Rand2( -200.0f, 200.0f ), ap->pos[ Z ] + F_Rand2( -200.0f, 200.0f ) );
				break_effect_02( ap->pos[ X ] + F_Rand2( -700.0f, -200.0f ), ap->pos[ Y ] + F_Rand2( -200.0f, 200.0f ), ap->pos[ Z ] + F_Rand2( -200.0f, 200.0f ) );
				break_effect_02( ap->pos[ X ] + F_Rand2( -700.0f, -200.0f ), ap->pos[ Y ] + F_Rand2( -200.0f, 200.0f ), ap->pos[ Z ] + F_Rand2( -200.0f, 200.0f ) );
				break_effect_02( ap->pos[ X ] + F_Rand2( -700.0f, -200.0f ), ap->pos[ Y ] + F_Rand2( -200.0f, 200.0f ), ap->pos[ Z ] + F_Rand2( -200.0f, 200.0f ) );
				ap->workA[ X ]++;
				ap->workA[ P ] = 0;
			}
			break;

		case 51:	// ���j���o
			ap->workA[ P ] ++;
			if( ap->workA[ P ] > 30 )
			{
				camera_vibration_strength();	// �J�����������h�炷
				break_effect_02( ap->pos[ X ] + F_Rand2( 200.0f, 700.0f ), ap->pos[ Y ] + F_Rand2( -200.0f, 200.0f ), ap->pos[ Z ] + F_Rand2( -200.0f, 200.0f ) );
				break_effect_02( ap->pos[ X ] + F_Rand2( 200.0f, 700.0f ), ap->pos[ Y ] + F_Rand2( -200.0f, 200.0f ), ap->pos[ Z ] + F_Rand2( -200.0f, 200.0f ) );
				break_effect_02( ap->pos[ X ] + F_Rand2( 200.0f, 700.0f ), ap->pos[ Y ] + F_Rand2( -200.0f, 200.0f ), ap->pos[ Z ] + F_Rand2( -200.0f, 200.0f ) );
				break_effect_02( ap->pos[ X ] + F_Rand2( 200.0f, 700.0f ), ap->pos[ Y ] + F_Rand2( -200.0f, 200.0f ), ap->pos[ Z ] + F_Rand2( -200.0f, 200.0f ) );
				ap->workA[ X ]++;
				ap->workA[ P ] = 0;
			}
			break;

		case 52:	// ���j���o
			ap->workA[ P ] ++;
			if( ap->workA[ P ] > 120 )
			{
				camera_vibration_strength();	// �J�����������h�炷
				break_effect_02( ap->pos[ X ] + F_Rand2( -400.0f, 400.0f ), ap->pos[ Y ] + F_Rand2( -200.0f, 200.0f ), ap->pos[ Z ] + F_Rand2( -200.0f, 200.0f ) );
				break_effect_02( ap->pos[ X ] + F_Rand2( -400.0f, 400.0f ), ap->pos[ Y ] + F_Rand2( -200.0f, 200.0f ), ap->pos[ Z ] + F_Rand2( -200.0f, 200.0f ) );
				break_effect_02( ap->pos[ X ] + F_Rand2( -400.0f, 400.0f ), ap->pos[ Y ] + F_Rand2( -200.0f, 200.0f ), ap->pos[ Z ] + F_Rand2( -200.0f, 200.0f ) );
				break_effect_02( ap->pos[ X ] + F_Rand2( -400.0f, 400.0f ), ap->pos[ Y ] + F_Rand2( -200.0f, 200.0f ), ap->pos[ Z ] + F_Rand2( -200.0f, 200.0f ) );
				break_effect_02( ap->pos[ X ] + F_Rand2( -700.0f, -200.0f ), ap->pos[ Y ] + F_Rand2( -200.0f, 200.0f ), ap->pos[ Z ] + F_Rand2( -200.0f, 200.0f ) );
				break_effect_02( ap->pos[ X ] + F_Rand2( -700.0f, -200.0f ), ap->pos[ Y ] + F_Rand2( -200.0f, 200.0f ), ap->pos[ Z ] + F_Rand2( -200.0f, 200.0f ) );
				break_effect_02( ap->pos[ X ] + F_Rand2( -700.0f, -200.0f ), ap->pos[ Y ] + F_Rand2( -200.0f, 200.0f ), ap->pos[ Z ] + F_Rand2( -200.0f, 200.0f ) );
				break_effect_02( ap->pos[ X ] + F_Rand2( -700.0f, -200.0f ), ap->pos[ Y ] + F_Rand2( -200.0f, 200.0f ), ap->pos[ Z ] + F_Rand2( -200.0f, 200.0f ) );
				break_effect_02( ap->pos[ X ] + F_Rand2( 200.0f, 700.0f ), ap->pos[ Y ] + F_Rand2( -200.0f, 200.0f ), ap->pos[ Z ] + F_Rand2( -200.0f, 200.0f ) );
				break_effect_02( ap->pos[ X ] + F_Rand2( 200.0f, 700.0f ), ap->pos[ Y ] + F_Rand2( -200.0f, 200.0f ), ap->pos[ Z ] + F_Rand2( -200.0f, 200.0f ) );
				break_effect_02( ap->pos[ X ] + F_Rand2( 200.0f, 700.0f ), ap->pos[ Y ] + F_Rand2( -200.0f, 200.0f ), ap->pos[ Z ] + F_Rand2( -200.0f, 200.0f ) );
				break_effect_02( ap->pos[ X ] + F_Rand2( 200.0f, 700.0f ), ap->pos[ Y ] + F_Rand2( -200.0f, 200.0f ), ap->pos[ Z ] + F_Rand2( -200.0f, 200.0f ) );
				ap->workA[ X ]++;
				ap->workA[ P ] = 0;
				TASK_end( ap );
				return;
			}
			break;

		case 100:		// �Q�[���I�[�o�[��
			ap->pos[ Z ] += ap->vec[ Z ];
			ap->vec[ Z ] *= 1.05f;
			if( ap->pos[ Z ] > 30000 )
			{
				TASK_end( ap );
				return;
			}
			break;
	}
}

void boss_start( void )
{
	TASK *ap;
	ap = TASK_start_MODEL( boss_exec, GROUP_ENEMY, MODEL_BOSS, TEXTURE_BOSS, "�{�X" );
	ap->grp_mode = WRITE_ZBUFFER | TEST_ZBUFFER | USE_LIGHTING | USE_3DPOS;
	ap->pos[ X ] = 0;
	ap->pos[ Y ] = -3000;
	ap->pos[ Z ] = -10000;
	ap->vec[ Z ] = 100;
	ap->pri = PRI_ENEMY;
	ap->HP = 40000;
	ap->SCORE = 500000;
//�@���̔���g��ݒ�
	ap->sphire = 250.0f;
//�@���̔���g��ݒ�
	ap->sphire_shift[ X ] = 0;
	ap->sphire_shift[ Y ] = 0;
	ap->sphire_shift[ Z ] = 0;
	ap->callback = boss_callback;
	ap->workA[ D ] = 0;
	ap->workA[ P ] = 0;		// ���j���o�p
	ap->workA[ X ] = 0;		// �s���X�C�b�`
	ap->workB[ X ] = 0;		// �s���X�C�b�`

	ap->specular[ 0 ] = 1.0f;
	ap->specular[ 1 ] = 1.0f;
	ap->specular[ 2 ] = 1.0f;
	ap->ambient[ 0 ] = 0.2f;
	ap->ambient[ 1 ] = 0.0f;
	ap->ambient[ 2 ] = 0.0f;
	ap->emissive[0] = 0.25f;
	ap->emissive[1] = 0.25f;
	ap->emissive[2] = 0.25f;
 	ap->pow = 6.0f;
	SOZ_material_setting( ap );
}


