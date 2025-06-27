#ifdef WINDOWS_PC
#include    "C:/project/libs/systemOZ_v4/soz.h"
#else
#include    "D:/project/guardians_2dx/proj.win32/src/systemOZ/soz.h"
#endif

#include    "C:/project/bace/src/game/game_include.h"


//------------------------------------------------------------------------------------------------------------------------------------------------------
// 
//			�G���h���[��
// 
//------------------------------------------------------------------------------------------------------------------------------------------------------

#define END_SPEED	5.0f

//------------------------------------------------------------------------------------------------------------------------------------------------------
// �G���h���[��
//------------------------------------------------------------------------------------------------------------------------------------------------------


void end_roll_stop_exec( TASK *ap )
{
	if( ap->pos[ Y ] >= WINDOW_HEIGHT /2 )		// ����̍��W�𒴂�����^�X�N�G���h
	{
		ap->work1[ X ] ++;						// �t���[���v�Z
		if( ap->work1[ X ] > 180 )				// ����̃t���[���𒴂�����^�C�g����ʂɈړ�
		{
			fade(5, TYPE_TITLE );
			demo_mode = 2;
//			game_type = TYPE_TITLE;
			TASK_end( ap );
			return;
		}
	}
	else
		ap->pos[ Y ] += ap->vec[ Y ];						// ���W�ړ�

}
void end_roll_stop( void )
{
	TASK *ap;
	ap = TASK_start_GRP( end_roll_stop_exec, GROUP_UI, TEXTURE_UI_FONT_5, ui_font_5_rect, 0, "THANK YOU FOR PLAYING" );
	ap->pos[ X ] = WINDOW_WIDTH /2;
	ap->pos[ Y ] = - 256.0f;
	ap->vec[ Y ] = END_SPEED;
	ap->work1[ X ] = 0;
}

void end_roll_move_exec( TASK *ap )
{
	ap->pos[ Y ] += ap->vec[ Y ];						// ���W�ړ�
	if( ap->pos[ Y ] >= WINDOW_HEIGHT + 128.0f )		// ����̍��W�𒴂�����^�X�N�G���h
	{
		end_roll_stop();								// THANK YOU FOR PLAYING ��\��
		TASK_end( ap );
		return;
	}
}
void end_roll_move( void )
{
	TASK *ap;
	ap = TASK_start_GRP( end_roll_move_exec, GROUP_UI, TEXTURE_UI_FONT_5, ui_font_5_rect, 1, "SHIMOMURA KOTA" );
	ap->pos[ X ] = WINDOW_WIDTH /2;
	ap->pos[ Y ] = - 281.0f;
	ap->vec[ Y ] = END_SPEED;
	ap->work1[ X ] = 1;
}

void end_roll_logo_exec( TASK *ap )
{
	switch ( ap->work1[ P ] )
	{
		case 0:
			ap->base_color[ 0 ][ 0 ] += 2;
			if( ap->base_color[ 0 ][ 0 ] > 250 )
			{
				ap->work1[ P ] = 1;
			}
			break;

		case 1:
			if( ap->base_color[ 0 ][ 0 ] > 250 )
			{
				ap->work1[ X ]++;								// �t���[���v�Z	
				if( ap->work1[ X ] > 160 )
				{
					ap->pos[ Y ] += ap->vec[ Y ];				// ���W�ړ�
					if( ap->pos[ Y ] >= WINDOW_HEIGHT *2.2f )	// ����̍��W�𒴂�����^�X�N�G���h
					{
						end_roll_move();
						TASK_end( ap );
						return;
					}
				}
			}
			break;
	}
}
void end_roll_logo( void )
{
	TASK *ap;
	ap = TASK_start_GRP( end_roll_logo_exec, GROUP_UI, TEXTURE_LOGO, ui_font_rect, 0,  "�^�C�g�����S��\��" );
	ap->pos[ X ] = WINDOW_WIDTH /2;
	ap->pos[ Y ] = WINDOW_HEIGHT /2;
	ap->vec[ Y ] = END_SPEED;
	ap->base_color[ 0 ][ 0 ] = 0;
	ap->work1[ X ] = 0;
	ap->work1[ Y ] = 0;
	ap->work1[ P ] = 0;
}

void end_roll_exec( TASK *ap )
{
	if( game_type == TYPE_TITLE )
	{
		TASK_all_init();
		return;
	}
	// ����{�^�����A�߂�{�^���������ꂽ��G���h���[���������I�����ă^�C�g����ʂ�
	if( SOZ_Inkey_TRG( DIK_Z ) || SOZ_Inkey_TRG( DIK_X ) || SOZ_Inpad_TRG( 0, PADDIK_DECIDE) || SOZ_Inpad_TRG( 0, PADDIK_CANCEL ) )
	{
		TASK_all_init();
		game_type = TYPE_TITLE;
		return;
	}
}

void end_roll( void )
{
	TASK *ap;
	ap = TASK_start( end_roll_exec, GROUP_UI, "�G���h���[��" );
	end_roll_logo();
}