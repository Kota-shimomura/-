#ifdef WINDOWS_PC
#include    "C:/project/libs/systemOZ_v4/soz.h"
#else
#include    "D:/project/guardians_2dx/proj.win32/src/systemOZ/soz.h"
#endif

#include    "C:/project/bace/src/game/game_include.h"

SINT64 tutorial_flag = 0;		// �`���[�g���A���̐i�s�x�̕ۑ��E������x�󂯂�ꍇ�́A��������̕����̂ݏ�����
SINT32 selecter = 0;			// �Z���N�^�[

//------------------------------------------------------------------------------------------------------------------------------------------------------
// 
//			MENU
// 
//------------------------------------------------------------------------------------------------------------------------------------------------------

typedef struct
{
	CHAR	ui_name[64];
	SINT32	anime_no;
	SINT32	chenge_game_type;
	SINT32	lock_flag_id;
} MENU_UI;

MENU_UI menu_ui[]=
{
	{ "START",		3,	TYPE_GAME,		TOTORIAL_NONE	},
	{ "RANKING",	5,	TYPE_RANKING,	TUTORIAL_RANK	},
	{ "OPTION",		6,	TYPE_OPTION,	TOTORIAL_NONE	},
};

//------------------------------------------------------------------------------------------------------------------------------------------------------
// �w�i ��n�Ɛ퓬�@( START������������ )
//------------------------------------------------------------------------------------------------------------------------------------------------------
void menu_base_exec( TASK *ap )
{
	// �����ł͓��ɉ������Ȃ�
}
void menu_base( void )
{
	TASK *ap;
	ap = TASK_start_MODEL( menu_base_exec, GROUP_BG, MODEL_BASE, TEXTURE_BASE, "��n3D���f��" );
	ap->grp_mode = WRITE_ZBUFFER | TEST_ZBUFFER | USE_LIGHTING | USE_3DPOS;	//| USE_SPECULAR ;
	ap->pos[ X ] = 0;
	ap->pos[ Y ] = -64.0f;
	ap->pos[ Z ] = 500.0f;
	ap->scale[ Y ] = 3.0f;
	ap->ang[ X ] = 0x4000;
	ap->pri = PRI_JIKI;

	ap->specular[ 0 ] = 1.3f;
	ap->specular[ 1 ] = 1.3f;
	ap->specular[ 2 ] = 1.3f;
	ap->ambient[ 0 ] = 0.15f;
	ap->ambient[ 1 ] = 0.15f;
	ap->ambient[ 2 ] = 0.2f;
	ap->emissive[0] = 0.15f;
	ap->emissive[1] = 0.15f;
	ap->emissive[2] = 0.15f;
	ap->diffuse[ 0 ] = 1.3f;
	ap->diffuse[ 1 ] = 1.3f;
	ap->diffuse[ 2 ] = 1.6f;
 	ap->pow = 0.78f;
	SOZ_material_setting( ap );
}

void menu_jiki_exec( TASK *ap )
{
	if ( game_type == TYPE_MENU +1 )		// ���j���[��ʂ̎��̂ݕ\��
	{
// �Q�[���X�^�[�g���I������Ă��āA����{�^���������ꂽ��
		if( ( SOZ_Inkey_TRG( DIK_Z ) || SOZ_Inpad_TRG( 0, PADDIK_DECIDE ) ) && ap->work1[ X ] == 0 && selecter == 0 )
		{
//			play_load();
			SOZ_play_se( SE_TAKE_OFF, 4.0f, 1, 0.0f );
			ap->vec[ Z ] = 1.0f;
			ap->work1[ X ] = 1;
		}
		ap->vec[ Z ] *= 1.05f;
		ap->pos[ Z ] += ap->vec[ Z ];
		ap->pos[ Y ] -= ap->vec[ Y ] /2;
		if( ap->vec[ Z ] >= 1.3f )
			camera_y[ 0 ] += 0.5f;

		if( ap->vec[ Z ] > 0 )				// �x�N�g��������̒l�𒴂�����A�A�t�^�[�o�[�i�[�̕\�����n�߂�
		{
			jiki_burner_effect( ap, 50 );
			jiki_burner_effect( ap, -50 );
		}
		SOZ_camera_move( 0 );

		if( ap->pos[ Z ] > 8000.0f )		// ������W�𒴂�����Q�[����ʂɈړ�
		{
			game_type = TYPE_GAME;
			TASK_all_init();
			return;
		}
	}
}
void menu_jiki( void )
{
	TASK *ap;
	ap = TASK_start_MODEL( menu_jiki_exec, GROUP_MY_SHIP, MODEL_MY_SHIP, TEXTURE_MY_SHIP, "���@3D���f��" );
	ap->grp_mode = WRITE_ZBUFFER | TEST_ZBUFFER | USE_LIGHTING | USE_3DPOS;	//| USE_SPECULAR ;
	ap->pos[ X ] = 0;
	ap->pos[ Y ] = -230.0f;
	ap->pos[ Z ] = 0.0f;
	ap->vec[ Z ] = 0.0f;
	ap->ang[ X ] = 0x0200;
	ap->ang[ Z ] = 0x0000;
	ap->pri = PRI_JIKI;
	ap->work1[ X ] = 0;

	ap->specular[ 0 ] = 5.0f;
	ap->specular[ 1 ] = 5.0f;
	ap->specular[ 2 ] = 5.0f;
	ap->ambient[ 0 ] = 0.0f;
	ap->ambient[ 1 ] = 0.0f;
	ap->ambient[ 2 ] = 0.0f;
	ap->emissive[ 0 ] = 0.51f;
	ap->emissive[ 1 ] = 0.51f;
	ap->emissive[ 2 ] = 0.51f;
	ap->diffuse[ 0 ] = 2.0f;
	ap->diffuse[ 1 ] = 2.0f;
	ap->diffuse[ 2 ] = 2.0f;
 	ap->pow = 10.0f;
	SOZ_material_setting( ap );
}

//------------------------------------------------------------------------------------------------------------------------------------------------------
// mini���S�\��
//------------------------------------------------------------------------------------------------------------------------------------------------------
void mini_logo_disp_exec( TASK *ap )
{
	// �������Ȃ�
}
void mini_logo_disp( void )
{
	TASK *ap;
	ap = TASK_start_GRP( mini_logo_disp_exec, GROUP_UI, TEXTURE_LOGO, ui_font_rect, 0, "���������S" );
	ap->pos[ X ] = 200.0f;
	ap->pos[ Y ] = 200.0f;
	ap->scale[ X ] = 0.4f;
	ap->scale[ Y ] = ap->scale[ X ];
	ap->pri = PRI_UI_FONT + 5000 *WP;
}


//------------------------------------------------------------------------------------------------------------------------------------------------------
// �Z���N�^�[
//------------------------------------------------------------------------------------------------------------------------------------------------------
void menu_selecter_line( TASK *ap )
{
	if( SOZ_Inkey_TRG( DIK_Z ) || SOZ_Inpad_TRG( 0, PADDIK_DECIDE ) )
		if( ap->work1[ Y ] == 0 )
			ap->work1[ Y ] = 1;
	if( ap->work1[ Y ] == 0 )
	{
		if( ap->work1[ X ] == 1 )
			ap->ang[ Z ] += 0x0100;
		else
		{
			// �Z���N�^�[����ɓ�����
			if( SOZ_Inkey_TRG( DIK_UP ) || SOZ_Inpad_TRG( 0, PADDIK_UP ) )
			{
				SOZ_play_se( SE_SERECT, 2.0f, 1, 1.0f );
				selecter--;
				if( selecter < 0 )
					selecter = 2;
			}
			// �Z���N�^�[�����ɓ�����
			if( SOZ_Inkey_TRG( DIK_DOWN ) || SOZ_Inpad_TRG( 0, PADDIK_DOWN ) )
			{
				SOZ_play_se( SE_SERECT, 2.0f, 1, 1.0f );
				selecter++;
				if( selecter > 2 )
					selecter = 0;
			}
		}
		SOZ_locate_print( 1, 1, "[selecter] %d ", selecter );
	// ���W�̍X�V
		ap->pos[ Y ] = FLOAT( WINDOW_HEIGHT / 2.6f + 10.0f + ( WINDOW_HEIGHT/7 ) * selecter );
	}
}
void menu_selecter( void )
{
	TASK *line, *ap;
	line = TASK_start_GRP( menu_selecter_line, GROUP_UI, TEXTURE_UI_FONT, ui_selecter_rect, 0, "�Z���N�^�[�̃��C������" );
	line->pri = PRI_UI_FONT;
	line->pos[ X ] = WINDOW_WIDTH /2;
	line->work1[ X ] = 0;
	line->work1[ Y ] = 0;

	ap = TASK_start_GRP( menu_selecter_line, GROUP_UI, TEXTURE_UI_FONT, ui_selecter_rect, 1, "�Z���N�^�[�̃��C������" );
	ap->pos[ X ] = WINDOW_WIDTH /2 - 350;
	ap->pri = PRI_UI_FONT+1;
	ap->work1[ X ] = 1;
	ap->work1[ Y ] = 0;
}

//------------------------------------------------------------------------------------------------------------------------------------------------------
// start/custom/ranking�\��
//------------------------------------------------------------------------------------------------------------------------------------------------------
void menu_ui_disp_exec( TASK *ap )
{
	ap->work2[ X ] ++;
	SOZ_locate_print(20, 3, "%d", selecter );
	if( ap->work1[ Z ] == selecter )	// �Z���N�^�[�������Ă���Ƃ�
	{
		ap->base_color[ 0 ][ 0 ] = 0xff;
		ap->base_color[ 0 ][ 1 ] = 0xff;
		ap->base_color[ 0 ][ 2 ] = 0xff;
		ap->base_color[ 0 ][ 3 ] = 0xff;
		if( ap->work2[ X ] % 40 == 0 )	// 10f���Ƃɑ傫���Ȃ�^�X�N�𔭐�������
			bic_illusion_start( ap, 10, BLEND_ADD );
		if( SOZ_Inkey_TRG( DIK_Z ) || SOZ_Inpad_TRG( 0, PADDIK_DECIDE ) )			// ����{�^���������ꂽ��
		{
			if( menu_ui[ selecter ].chenge_game_type != TYPE_GAME )
				game_type = menu_ui[ selecter ].chenge_game_type;					// game_type ��ς���
		}		
	}
	else
	{
		ap->base_color[ 0 ][ 0 ] = 0x88;
		ap->base_color[ 0 ][ 1 ] = 0x88;
		ap->base_color[ 0 ][ 2 ] = 0x88;
		ap->base_color[ 0 ][ 3 ] = 0x88;
	}

//	���b�N����Ă���Ƃ��̓O���[�Ŕ������ɂ���
	//if( ( tutorial_flag & ap->work1[ X ] ) != 0 )
	//{
	//	ap->base_color[ 0 ][ 0 ] = 0xff;
	//	ap->base_color[ 0 ][ 1 ] = 0xff;
	//	ap->base_color[ 0 ][ 2 ] = 0xff;
	//	ap->base_color[ 0 ][ 3 ] = 0xff;
	//}
	//else
	//{
	//	ap->base_color[ 0 ][ 0 ] = 0x44;
	//	ap->base_color[ 0 ][ 1 ] = 0x66;
	//	ap->base_color[ 0 ][ 2 ] = 0x66;
	//	ap->base_color[ 0 ][ 3 ] = 0x66;
	//}
	ap->scale[ Y ] = ap->scale[ X ];
}
void menu_ui_disp( SINT32 id, MENU_UI *ui )
{
	TASK *ap;
	ap = TASK_start_GRP( menu_ui_disp_exec, GROUP_UI, TEXTURE_UI_FONT, ui_font_rect, ui->anime_no, ui->ui_name );
	ap->pos[ X ] = FLOAT( WINDOW_WIDTH /2 );
	ap->pos[ Y ] = FLOAT( WINDOW_HEIGHT / 2.6f + ( WINDOW_HEIGHT/7 ) * id );
	ap->scale[ X ] = 0.7f;
	ap->scale[ Y ] = ap->scale[ X ];
	ap->pri = PRI_UI_FONT;

	ap->work1[ X ] = ui->lock_flag_id;		// �I���ɕK�v�ȃt���O��ۑ�
	ap->work1[ Y ] = ui->chenge_game_type;	// �I�����ꂽ���ɕύX����game_type��ۑ�
	ap->work1[ Z ] = id;
	ap->work2[ X ] = 0;						// �c���\���p�x�̌v�Z�p
}
void menu_ui_set( void )
{
	SINT32 disp_num;
	for( disp_num = 0; disp_num < 3; disp_num++ )
		menu_ui_disp( disp_num, &menu_ui[ disp_num ] );
}

//------------------------------------------------------------------------------------------------------------------------------------------------------
// MENU�\��
//------------------------------------------------------------------------------------------------------------------------------------------------------
void menu_disp_exec( TASK *ap )
{
	if( ap->work1[ X ] == 0 )
	{
		ap->work1[ Y ]++;
		if( SOZ_Inkey_TRG( DIK_Z ) || SOZ_Inpad_TRG( 0, PADDIK_DECIDE ) )		// ����{�^���������ꂽ��
		{
			ap->work1[ X ] = 1;
			SOZ_play_se( SE_DECISION, 3.0f, 1, 0.0f );							// ����̌��ʉ���炷
			return;
		}
		if( SOZ_Inkey_TRG( DIK_X ) || SOZ_Inpad_TRG( 0, PADDIK_CANCEL ) )
		{
			ap->work1[ X ] = 1;
			SOZ_play_se( SE_CANCEL, 3.0f, 1, 0.0f );
			TASK_all_init();
			game_type = TYPE_TITLE;
			return;
		}
		if( ap->work1[ Y ] > 60 * 60 * 10 )		// ���莞�Ԍo�߂�����^�C�g����ʂɖ߂�
		{
			TASK_all_init();
			game_type = TYPE_TITLE;
			TASK_end( ap );
			return;
		}
	}
}

void menu_disp( void )
{
	TASK *ap;
	ap = TASK_start_GRP( menu_disp_exec, GROUP_UI, TEXTURE_UI_FONT, ui_font_rect, 2, "MENU" );
	ap->pos[ X ] = WINDOW_WIDTH /2;
	ap->pos[ Y ] = WINDOW_HEIGHT /7;
	ap->pri = PRI_UI_FONT;

	ap->work1[ X ] = 0;
	ap->work1[ Y ] = 0;

	mini_logo_disp();		// ����̏��������S��\��
	menu_ui_set();			// ���j���[�̑I������\��
	menu_selecter();		// ���j���[��ʂ̃Z���N�^�[
//	menu_jiki();			// �w�i�p�̎��@��\��
//	menu_base();			// �w�i�p�̊�n��\��
}

void bg_base_jiki( void )
{
	menu_jiki();			// �w�i�p�̎��@��\��
	menu_base();			// �w�i�p�̊�n��\��
}
