#ifdef WINDOWS_PC
#include    "C:/project/libs/systemOZ_v4/soz.h"
#else
#include    "D:/project/guardians_2dx/proj.win32/src/systemOZ/soz.h"
#endif

#include    "C:/project/bace/src/game/game_include.h"

//------------------------------------------------------------------------------------------------------------------------------------------------------
// 
//			�j�󎞂�callback
// 
//------------------------------------------------------------------------------------------------------------------------------------------------------
void bullet_gen_callback( TASK *actp, TASK *gen ) //( TASK *gen, TASK *actp )
{
	break_effect( gen->pos[ X ], gen->pos[ Y ], gen->pos[ Z ] );
	gen->HP -= actp->ATK;
	if( gen->HP <= 0 )
	{
		score += gen->SCORE + bonus;	// SCORE�𑝂₷
		bonus += gen->SCORE/100;		// SCOREBONUS������
		break_effect_02( gen->pos[ X ], gen->pos[ Y ], gen->pos[ Z ] );
		TASK_end( gen );
	}
//	TASK_end( actp );
	return;
}

// ���@�̔j�󉉏o
void my_ship_callback( TASK *ap, TASK *actp )
{
	if( ap->workA[ X ] == 1 )
	{
		life--;															// ���C�t�����炷
		ap->workA[ X ] = 2;
		ap->workA[ Y ] = 120; 
		if( life > 0 )
		{
			my_ship_tex_chenge( ap );
			camera_vibration_medium();									// �J�����U���@��
			SOZ_play_se( SE_BREAK, 2.0f, 1, 1.0f );						// ���ʉ���炷
			break_effect( ap->pos[ X ], ap->pos[ Y ], ap->pos[ Z ] );	// �����G�t�F�N�g
		}
		else
		{
			camera_vibration_strength();								// �J�����U���@��
			ap->workA[ X ] = 3;
		}
	}
}

// �~�T�C���̔j�󉉏o
void missile_callback( TASK *missile, TASK *none )
{
	if( rest_missile < 99 )
		rest_missile++;												// �~�T�C���q�b�g���@��[����
	camera_vibration_weak();									// �J�����U���@��
	break_effect_02( missile->pos[ X ], missile->pos[ Y ], missile->pos[ Z ] );		// ���j�G�t�F�N�g
	TASK_end( missile );
	return;
}

// �e�̔j�󉉏o
void shot_callback( TASK *shot, TASK *none )
{
	TASK_end( shot );
	return;
}

// �G�̌��j���o
void enemy_callback( TASK *shot, TASK *enemy )
{
	SINT32 add_score = 0;
	switch ( enemy->task_group )
	{
		case GROUP_ENEMY:	// ���@�̒e�ƓG�����������Ƃ�
			enemy->HP -= shot->ATK;	// �G�Ƀ_���[�W��^����
			if( enemy->HP < 0 )	// �G�̗̑͂�0�ȉ��ɂȂ�����
			{
				add_score = SINT32( ( enemy->SCORE + enemy->pos[ Z ] + bonus ) *( 1 + life*10 ) );
				// �w��̐��V���b�g�œG��|������~�T�C�����[
				if( shot->model_no == MODEL_SHOT )
					shot_break_count++;
				else
					add_score *=2;
				if( shot_break_count % 5 == 0 && rest_missile < 99 )
					rest_missile++;

				score += add_score;						// SCORE�𑝂₷
				add_score_disp( add_score, enemy->pos[ X ], enemy->pos[ Y ], enemy->pos[ Z ] );	// ������X�R�A��\��
				bonus += enemy->SCORE/shot->BONUS;		// SCOREBONUS������
				SOZ_play_se( SE_BREAK, 4.0f, 1, 1.0f );	// ���ʉ���炷
				SOZ_play_se( SE_BREAK_2, 4.0f, 1, 1.0f );	// ���ʉ���炷
				break_effect_02( enemy->pos[ X ], enemy->pos[ Y ], enemy->pos[ Z ] );	// �j��̃G�t�F�N�g��\��
//				break_bom_effect( enemy->pos[ X ], enemy->pos[ Y ], enemy->pos[ Z ] );	// �j��̃G�t�F�N�g��\��
				TASK_end( enemy );
			}
			else
			{
				enemy->workE[ D ] = 0;
				shot_hit_effect( shot->pos[ X ], shot->pos[ Y ], shot->pos[ Z ] );	// �q�b�g�G�t�F�N�g�̕\��
				SOZ_play_se( SE_SHOT, 5.0f, 1, 1 );									// �q�b�g���̌��ʉ���炷
			}
			return;
			break;
	}
}

// �{�X�̌��j���o
void boss_callback( TASK *shot, TASK *enemy )
{
		enemy->HP -= shot->ATK;	// �G�Ƀ_���[�W��^����
		if( enemy->HP < 0 )	// �G�̗̑͂�0�ȉ��ɂȂ�����
		{
			enemy->workA[ X ] = 4;
			jiki->workA[ X ] = 4;
			game_type = TYPE_CLEAR;
		}
		else
		{
			enemy->workE[ D ] = 0;
			shot_hit_effect( shot->pos[ X ], shot->pos[ Y ], shot->pos[ Z ] );	// �q�b�g�G�t�F�N�g�̕\��
			SOZ_play_se( SE_SHOT, 5.0f, 1, 1 );									// �q�b�g���̌��ʉ���炷
		}
		return;
}

