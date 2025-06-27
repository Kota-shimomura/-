#ifdef WINDOWS_PC
#include    "C:/project/libs/systemOZ_v4/soz.h"
#else
#include    "D:/project/guardians_2dx/proj.win32/src/systemOZ/soz.h"
#endif

#include    "C:/project/bace/src/game/game_include.h"

//--------------------------------------------------------------------------------------
// ����ݒ�@�֘A
//--------------------------------------------------------------------------------------
SINT32 stick_data;					// �X�e�B�b�N����̔��]���Ǘ�����ϐ�
SINT32 option_selecter = 0;

typedef struct
{
	SINT8  task_name[128];
	SINT32 texture_no;
	PARTS_RECT *rect;
	SINT32 anime_no;
	SINT32 check_flag;
	FLOAT  pos_x;
	FLOAT  scale;
} OPTION_SETTING;

OPTION_SETTING setting_menu[]= 
{
	{ "analog stick", TEXTURE_UI_FONT_3, ui_font_2_rect, 0, STICK_ANALOG, 0, 0.5f },	// �A�i���O�X�e�B�b�N���g�p���邩
	{ "lr flip", TEXTURE_UI_FONT_4, ui_cont_rect, 3, STICK_LR, -150.0f, 0.7f },	// ����̍��E���]
	{ "ud flip", TEXTURE_UI_FONT_4, ui_cont_rect, 4, STICK_UD, -190.0f, 0.7f },	// ����̏㉺���]
	{ "menu", TEXTURE_UI_FONT, ui_font_rect, 2, 0x8000, 0, 0.7f },	// ����̏㉺���]
};



// �����̕\��
void new_data_font_exec( TASK *ap )
{

}
void new_data_font( void )
{
	TASK *ap;
	ap = TASK_start_GRP( new_data_font_exec, GROUP_UI, TEXTURE_UI_FONT_4, ui_cont_rect, 6, "�ꕶ����");
	ap->pos[ X ] = FLOAT( WINDOW_WIDTH /2 ) - 90.0f;
	ap->pos[ Y ] = FLOAT( WINDOW_HEIGHT - 300 );
	ap->scale[ Y ] = ap->scale[ X ] = 0.5f;
	ap->pri = PRI_UI;
	ap = TASK_start_GRP( new_data_font_exec, GROUP_UI, TEXTURE_UI_FONT_4, ui_cont_rect, 7, "��������");
	ap->pos[ X ] = FLOAT( WINDOW_WIDTH /2 ) - 40.0f;
	ap->pos[ Y ] = FLOAT( WINDOW_HEIGHT - 200 ) ;
	ap->scale[ Y ] = ap->scale[ X ] = 0.5f;
	ap->pri = PRI_UI;
	ap = TASK_start_GRP( new_data_font_exec, GROUP_UI, TEXTURE_UI_FONT_4, ui_cont_rect, 5, "�����ݒ�");
	ap->pos[ X ] = FLOAT( WINDOW_WIDTH /2 );
	ap->pos[ Y ] = 200.0f ;
	ap->scale[ Y ] = ap->scale[ X ] = 0.8f;
	ap->pri = PRI_UI;

	orFLG( stick_data, STICK_SET);
	option_save_data( SAVE_MODE );
}

// �X�C�b�`�̕\��
void switch_disp_exec( TASK *ap )
{
	ap->base_color[0][0] = 0xff;
	if( option_selecter != ap->work1[ X ] )
		ap->base_color[0][0] = 0xcc;
	ap->base_color[ 0 ][ 3 ] = ap->base_color[ 0 ][ 2 ] = ap->base_color[ 0 ][ 1 ] = ap->base_color[ 0 ][ 0 ];

	if( ( stick_data & ap->work1[ Y ] ) != 0 )		// �t���O�������Ă�����A�X�C�b�`�I����Ԃ̃O���t�B�b�N��\������
		ap->anime_no = 2;
	else
		ap->anime_no = 1;
}
void switch_disp( SINT32 id, FLOAT pos_y, SINT32 check_flag )
{
	TASK *ap;
	ap = TASK_start_GRP( switch_disp_exec, GROUP_UI, TEXTURE_UI_GAME,  ui_cont_rect, 1, "�X�C�b�`�̉摜" );
	ap->pos[ X ] = 1600.0f;
	ap->pos[ Y ] = pos_y;
	ap->scale[ Y ] = ap->scale[ X ] = 1.0f;
	ap->pri = PRI_UI;
	ap->work1[ X ] = id;
	ap->work1[ Y ] = check_flag;
}
//	���͂̕\��
void stick_option_exec( TASK *ap )
{
	ap->base_color[0][0] = 0xff;
	if( option_selecter != ap->work1[ X ] )
		ap->base_color[0][0] = 0xbb;
	ap->base_color[ 0 ][ 3 ] = ap->base_color[ 0 ][ 2 ] = ap->base_color[ 0 ][ 1 ] = ap->base_color[ 0 ][ 0 ];
	if( SOZ_Inkey_REP( DIK_Z ) || SOZ_Inpad_REP( 0, PADDIK_DECIDE ) )	// ����{�^���������ꂽ��A�@�\���I���E�I�t����
		if( ap->work1[ X ] == 3  && option_selecter == 3 )
		{
			TASK_end( ap );
			return;
		}
}
void stick_option( SINT32 id, FLOAT pos_y )
{
	TASK *ap;
	ap = TASK_start_GRP( stick_option_exec, GROUP_UI, setting_menu[ id ].texture_no, setting_menu[ id ].rect, setting_menu[ id ].anime_no, setting_menu[ id ].task_name );
	ap->pos[ X ] = WINDOW_WIDTH /2 + setting_menu[ id ].pos_x;
	ap->pos[ Y ] = pos_y + 100 *id;
	ap->pri = PRI_UI;
	ap->scale[ Y ] = ap->scale[ X ] = setting_menu[ id ].scale;
	ap->work1[ X ] = id;
	ap->work1[ Y ] = setting_menu[ id ].check_flag;		// �m�F�������t���O�̒l�����Ă���
	if( id <= 2 )
	{
		switch_disp( id, ap->pos[ Y ], ap->work1[ Y ] );		// ���o�G�ɂ킩��₷���悤�ɁA�X�C�b�`�̃O���t�B�b�N��t����
	}
}

//--------------------------------------------------------------------------------------
// ���쏉���ݒ�
//--------------------------------------------------------------------------------------
void option_selecter_cont( TASK *ap )
{
	if( SOZ_Inkey_REP( DIK_UP ) || SOZ_Inpad_REP( 0, PADDIK_UP ) )	// �Z���N�^�[���ړ�������
		option_selecter--;
	if( SOZ_Inkey_REP( DIK_DOWN ) || SOZ_Inpad_REP( 0, PADDIK_DOWN ) )	// �Z���N�^�[���ړ�������
		option_selecter++;
//���~�b�^�[
	if( option_selecter < 0 )
		option_selecter = 3;
	if( option_selecter > 3 )
		option_selecter = 0;
	if( SOZ_Inkey_REP( DIK_Z ) || SOZ_Inpad_REP( 0, PADDIK_DECIDE ) )	// ����{�^���������ꂽ��A�@�\���I���E�I�t����
	{
		if( option_selecter == 3 )
		{
			option_save_data( SAVE_MODE );
			option_save_data( LOAD_MODE );
			TASK_all_init();
			game_type = TYPE_MENU;
			return;
		}
		else
		{
			if( ( stick_data & setting_menu[ option_selecter ].check_flag ) != 0 )
				clrFLG( stick_data, setting_menu[ option_selecter ].check_flag );
			else
				orFLG( stick_data, setting_menu[ option_selecter ].check_flag );
		}
	}

}
void opration_setting_system( FLOAT pos_y )
{
	TASK *ap;
	ap = TASK_start( option_selecter_cont, GROUP_UI, "�I�v�V������ʂ̃Z���N�^�[�̑���" );
// �A�i���O�X�e�B�b�N���g�p���邩
	stick_option( 0, pos_y );
	stick_option( 1, pos_y );
	stick_option( 2, pos_y );
	stick_option( 3, pos_y );
	option_selecter = 0;
}

// ����{�^���@�߂�{�^���@�̕\�L
void key_disp_exec( TASK *ap )
{
	// �������Ȃ�
}
void key_disp( FLOAT pos_x, FLOAT pos_y )
{
	TASK *ap;
	ap = TASK_start_GRP( key_disp_exec, GROUP_UI, TEXTURE_UI_FONT_4, ui_cont_rect, 8, " ����@�߂�@�{�^���\�L");
	ap->pos[ X ] = pos_x;
	ap->pos[ Y ] = pos_y;
	ap->pri = PRI_UI;
}

// �߂�{�^���@�̕\�L
void back_disp_exec( TASK *ap )
{
	// �������Ȃ�
}
void back_disp( FLOAT pos_x, FLOAT pos_y )
{
	TASK *ap;
	ap = TASK_start_GRP( back_disp_exec, GROUP_UI, TEXTURE_UI_FONT_4, ui_cont_rect, 9, " �߂�@�{�^���\�L");
	ap->pos[ X ] = pos_x;
	ap->pos[ Y ] = pos_y;
	ap->pri = PRI_UI;
}
