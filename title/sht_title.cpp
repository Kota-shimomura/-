#ifdef WINDOWS_PC
#include    "C:/project/libs/systemOZ_v4/soz.h"
#else
#include    "D:/project/guardians_2dx/proj.win32/src/systemOZ/soz.h"
#endif

#include    "C:/project/bace/src/game/game_include.h"


//------------------------------------------------------------------------------------------------------------------------------------------------------
// 
//			TITLE
// 
//------------------------------------------------------------------------------------------------------------------------------------------------------

//------------------------------------------------------------------------------------------------------------------------------------------------------
// GAME START�\��
//------------------------------------------------------------------------------------------------------------------------------------------------------
void game_start_disp_exec( TASK *ap )
{
// �_�ŏ���
	ap->base_color[ 0 ][ 0 ] -= 4;
	if( ap->base_color[ 0 ][ 0 ] < 128 )
		ap->base_color[ 0 ][ 0 ] = 255;


// ����{�^���������ꂽ�烁�j���[��ʂ�
	if( SOZ_Inkey_TRG( DIK_Z ) || SOZ_Inpad_TRG( 0, PADDIK_DECIDE ) )
	{
		SOZ_play_se( SE_DECISION, 3.0f, 1, 0.0f );
		TASK_end( ap );
		return;
	}
}

void game_start_disp( void )
{
	TASK *ap;
	ap = TASK_start_GRP( game_start_disp_exec, GROUP_UI, TEXTURE_UI_FONT, ui_font_rect, 1, "GAME START�@�\��" );
	ap->pos[ X ] = WINDOW_WIDTH / 2;
	ap->pos[ Y ] = WINDOW_HEIGHT / 2 + 400.0f;
	ap->scale[ X ] = 0.5f;
	ap->scale[ Y ] = ap->scale[ X ];
	ap->pri = PRI_UI_FONT;
	ap->work1[ X ] = 0;
}


//------------------------------------------------------------------------------------------------------------------------------------------------------
// �^�C�g�����S�\��
//------------------------------------------------------------------------------------------------------------------------------------------------------

void title_disp_exec( TASK *ap )
{
	ap->work1[ X ]++;
	if( ap->work1[ X ] >= 60 *20 )	// ���莞�Ԍo�ߌ�
	{
		ap->work1[ Y ] = 1;
	}
	if( ap->work1[ Y ] == 1 )
	{
		fade( 5, TYPE_DEMO );
		ap->work1[ Y ]++;
	}
// ����{�^���������ꂽ��^�X�N�G���h������B
	if( SOZ_Inkey_TRG( DIK_Z ) || SOZ_Inpad_TRG( 0, PADDIK_DECIDE ) )
	{
		SOZ_play_se( SE_DECISION, 3.0f, 1, 0.0f );
		if( ( stick_data & STICK_SET ) == 0 )
			game_type = TYPE_NEW_DATA;
		else							// �f�[�^���Ȃ��ꍇ�͏����ݒ�ɔ�΂��B
			game_type = TYPE_MENU;
		//if( ( stick_data & STICK_SET ) != 0 )
		//	game_type = TYPE_MENU;
		//else							// �f�[�^���Ȃ��ꍇ�͏����ݒ�ɔ�΂��B
		//	game_type = TYPE_NEW_DATA;
		TASK_end( ap );
		return;
	}
}

void title_disp( void )
{
	TASK *ap;
	ap = TASK_start_GRP( title_disp_exec, GROUP_UI, TEXTURE_LOGO, ui_font_rect, 0, "�^�C�g�����S" );
	ap->pos[ X ] = WINDOW_WIDTH /2;
	ap->pos[ Y ] = WINDOW_HEIGHT /2;
	ap->scale[ X ] = 1.1f;
	ap->scale[ Y ] = ap->scale[ X ];
	ap->pri = PRI_UI;
	ap->work1[ X ] = 0;
	ap->work1[ Y ] = 0;

	option_save_data( LOAD_MODE );				// �I�v�V�����̐ݒ��ǂݍ���
	game_start_disp();		// �uGAME START�v�̕\�����Ăяo��
}

void kottan_disp_exec( TASK *ap )
{
// ���Ԍo�߂�����{�^���������ꂽ�烁�j���[��ʂ�
	ap->work1[ X ] ++;
	if( ap->work1[ X ] > 240 || SOZ_Inkey_TRG( DIK_Z ) || SOZ_Inpad_TRG( 0, PADDIK_DECIDE ) )
	{
		title_disp();
		TASK_end( ap );
		return;
	}

}

void kottan_disp( void )
{
	TASK *ap;
	ap = TASK_start_FONT( kottan_disp_exec, GROUP_UI, "KOTTAN", 4 );
	ap->pos[ X ] = WINDOW_WIDTH /2;
	ap->pos[ Y ] = WINDOW_HEIGHT /2;
	ap->work1[ X ] = 0;
	ap->pri = PRI_UI_FONT;
}



