#ifdef WINDOWS_PC
#include    "C:/project/libs/systemOZ_v4/soz.h"
#else
#include    "D:/project/guardians_2dx/proj.win32/src/systemOZ/soz.h"
#endif

#include    "C:/project/bace/src/game/game_include.h"

//--------------------------------------------------------------------------------------
// 操作設定　関連
//--------------------------------------------------------------------------------------
SINT32 stick_data;					// スティック操作の反転を管理する変数
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
	{ "analog stick", TEXTURE_UI_FONT_3, ui_font_2_rect, 0, STICK_ANALOG, 0, 0.5f },	// アナログスティックを使用するか
	{ "lr flip", TEXTURE_UI_FONT_4, ui_cont_rect, 3, STICK_LR, -150.0f, 0.7f },	// 操作の左右反転
	{ "ud flip", TEXTURE_UI_FONT_4, ui_cont_rect, 4, STICK_UD, -190.0f, 0.7f },	// 操作の上下反転
	{ "menu", TEXTURE_UI_FONT, ui_font_rect, 2, 0x8000, 0, 0.7f },	// 操作の上下反転
};



// 文字の表示
void new_data_font_exec( TASK *ap )
{

}
void new_data_font( void )
{
	TASK *ap;
	ap = TASK_start_GRP( new_data_font_exec, GROUP_UI, TEXTURE_UI_FONT_4, ui_cont_rect, 6, "一文説明");
	ap->pos[ X ] = FLOAT( WINDOW_WIDTH /2 ) - 90.0f;
	ap->pos[ Y ] = FLOAT( WINDOW_HEIGHT - 300 );
	ap->scale[ Y ] = ap->scale[ X ] = 0.5f;
	ap->pri = PRI_UI;
	ap = TASK_start_GRP( new_data_font_exec, GROUP_UI, TEXTURE_UI_FONT_4, ui_cont_rect, 7, "長い説明");
	ap->pos[ X ] = FLOAT( WINDOW_WIDTH /2 ) - 40.0f;
	ap->pos[ Y ] = FLOAT( WINDOW_HEIGHT - 200 ) ;
	ap->scale[ Y ] = ap->scale[ X ] = 0.5f;
	ap->pri = PRI_UI;
	ap = TASK_start_GRP( new_data_font_exec, GROUP_UI, TEXTURE_UI_FONT_4, ui_cont_rect, 5, "初期設定");
	ap->pos[ X ] = FLOAT( WINDOW_WIDTH /2 );
	ap->pos[ Y ] = 200.0f ;
	ap->scale[ Y ] = ap->scale[ X ] = 0.8f;
	ap->pri = PRI_UI;

	orFLG( stick_data, STICK_SET);
	option_save_data( SAVE_MODE );
}

// スイッチの表示
void switch_disp_exec( TASK *ap )
{
	ap->base_color[0][0] = 0xff;
	if( option_selecter != ap->work1[ X ] )
		ap->base_color[0][0] = 0xcc;
	ap->base_color[ 0 ][ 3 ] = ap->base_color[ 0 ][ 2 ] = ap->base_color[ 0 ][ 1 ] = ap->base_color[ 0 ][ 0 ];

	if( ( stick_data & ap->work1[ Y ] ) != 0 )		// フラグが立っていたら、スイッチオン状態のグラフィックを表示する
		ap->anime_no = 2;
	else
		ap->anime_no = 1;
}
void switch_disp( SINT32 id, FLOAT pos_y, SINT32 check_flag )
{
	TASK *ap;
	ap = TASK_start_GRP( switch_disp_exec, GROUP_UI, TEXTURE_UI_GAME,  ui_cont_rect, 1, "スイッチの画像" );
	ap->pos[ X ] = 1600.0f;
	ap->pos[ Y ] = pos_y;
	ap->scale[ Y ] = ap->scale[ X ] = 1.0f;
	ap->pri = PRI_UI;
	ap->work1[ X ] = id;
	ap->work1[ Y ] = check_flag;
}
//	文章の表示
void stick_option_exec( TASK *ap )
{
	ap->base_color[0][0] = 0xff;
	if( option_selecter != ap->work1[ X ] )
		ap->base_color[0][0] = 0xbb;
	ap->base_color[ 0 ][ 3 ] = ap->base_color[ 0 ][ 2 ] = ap->base_color[ 0 ][ 1 ] = ap->base_color[ 0 ][ 0 ];
	if( SOZ_Inkey_REP( DIK_Z ) || SOZ_Inpad_REP( 0, PADDIK_DECIDE ) )	// 決定ボタンが押されたら、機能をオン・オフする
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
	ap->work1[ Y ] = setting_menu[ id ].check_flag;		// 確認したいフラグの値を入れておく
	if( id <= 2 )
	{
		switch_disp( id, ap->pos[ Y ], ap->work1[ Y ] );		// 視覚敵にわかりやすいように、スイッチのグラフィックを付ける
	}
}

//--------------------------------------------------------------------------------------
// 操作初期設定
//--------------------------------------------------------------------------------------
void option_selecter_cont( TASK *ap )
{
	if( SOZ_Inkey_REP( DIK_UP ) || SOZ_Inpad_REP( 0, PADDIK_UP ) )	// セレクターを移動させる
		option_selecter--;
	if( SOZ_Inkey_REP( DIK_DOWN ) || SOZ_Inpad_REP( 0, PADDIK_DOWN ) )	// セレクターを移動させる
		option_selecter++;
//リミッター
	if( option_selecter < 0 )
		option_selecter = 3;
	if( option_selecter > 3 )
		option_selecter = 0;
	if( SOZ_Inkey_REP( DIK_Z ) || SOZ_Inpad_REP( 0, PADDIK_DECIDE ) )	// 決定ボタンが押されたら、機能をオン・オフする
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
	ap = TASK_start( option_selecter_cont, GROUP_UI, "オプション画面のセレクターの操作" );
// アナログスティックを使用するか
	stick_option( 0, pos_y );
	stick_option( 1, pos_y );
	stick_option( 2, pos_y );
	stick_option( 3, pos_y );
	option_selecter = 0;
}

// 決定ボタン　戻るボタン　の表記
void key_disp_exec( TASK *ap )
{
	// 何もしない
}
void key_disp( FLOAT pos_x, FLOAT pos_y )
{
	TASK *ap;
	ap = TASK_start_GRP( key_disp_exec, GROUP_UI, TEXTURE_UI_FONT_4, ui_cont_rect, 8, " 決定　戻る　ボタン表記");
	ap->pos[ X ] = pos_x;
	ap->pos[ Y ] = pos_y;
	ap->pri = PRI_UI;
}

// 戻るボタン　の表記
void back_disp_exec( TASK *ap )
{
	// 何もしない
}
void back_disp( FLOAT pos_x, FLOAT pos_y )
{
	TASK *ap;
	ap = TASK_start_GRP( back_disp_exec, GROUP_UI, TEXTURE_UI_FONT_4, ui_cont_rect, 9, " 戻る　ボタン表記");
	ap->pos[ X ] = pos_x;
	ap->pos[ Y ] = pos_y;
	ap->pri = PRI_UI;
}
