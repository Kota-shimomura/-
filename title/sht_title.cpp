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
// GAME START表示
//------------------------------------------------------------------------------------------------------------------------------------------------------
void game_start_disp_exec( TASK *ap )
{
// 点滅処理
	ap->base_color[ 0 ][ 0 ] -= 4;
	if( ap->base_color[ 0 ][ 0 ] < 128 )
		ap->base_color[ 0 ][ 0 ] = 255;


// 決定ボタンが押されたらメニュー画面へ
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
	ap = TASK_start_GRP( game_start_disp_exec, GROUP_UI, TEXTURE_UI_FONT, ui_font_rect, 1, "GAME START　表示" );
	ap->pos[ X ] = WINDOW_WIDTH / 2;
	ap->pos[ Y ] = WINDOW_HEIGHT / 2 + 400.0f;
	ap->scale[ X ] = 0.5f;
	ap->scale[ Y ] = ap->scale[ X ];
	ap->pri = PRI_UI_FONT;
	ap->work1[ X ] = 0;
}


//------------------------------------------------------------------------------------------------------------------------------------------------------
// タイトルロゴ表示
//------------------------------------------------------------------------------------------------------------------------------------------------------

void title_disp_exec( TASK *ap )
{
	ap->work1[ X ]++;
	if( ap->work1[ X ] >= 60 *20 )	// 特定時間経過後
	{
		ap->work1[ Y ] = 1;
	}
	if( ap->work1[ Y ] == 1 )
	{
		fade( 5, TYPE_DEMO );
		ap->work1[ Y ]++;
	}
// 決定ボタンが押されたらタスクエンドさせる。
	if( SOZ_Inkey_TRG( DIK_Z ) || SOZ_Inpad_TRG( 0, PADDIK_DECIDE ) )
	{
		SOZ_play_se( SE_DECISION, 3.0f, 1, 0.0f );
		if( ( stick_data & STICK_SET ) == 0 )
			game_type = TYPE_NEW_DATA;
		else							// データがない場合は初期設定に飛ばす。
			game_type = TYPE_MENU;
		//if( ( stick_data & STICK_SET ) != 0 )
		//	game_type = TYPE_MENU;
		//else							// データがない場合は初期設定に飛ばす。
		//	game_type = TYPE_NEW_DATA;
		TASK_end( ap );
		return;
	}
}

void title_disp( void )
{
	TASK *ap;
	ap = TASK_start_GRP( title_disp_exec, GROUP_UI, TEXTURE_LOGO, ui_font_rect, 0, "タイトルロゴ" );
	ap->pos[ X ] = WINDOW_WIDTH /2;
	ap->pos[ Y ] = WINDOW_HEIGHT /2;
	ap->scale[ X ] = 1.1f;
	ap->scale[ Y ] = ap->scale[ X ];
	ap->pri = PRI_UI;
	ap->work1[ X ] = 0;
	ap->work1[ Y ] = 0;

	option_save_data( LOAD_MODE );				// オプションの設定を読み込む
	game_start_disp();		// 「GAME START」の表示を呼び出す
}

void kottan_disp_exec( TASK *ap )
{
// 時間経過か決定ボタンが押されたらメニュー画面へ
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



