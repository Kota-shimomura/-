#ifdef WINDOWS_PC
#include    "C:/project/libs/systemOZ_v4/soz.h"
#else
#include    "D:/project/guardians_2dx/proj.win32/src/systemOZ/soz.h"
#endif

#include    "C:/project/bace/src/game/game_include.h"


//------------------------------------------------------------------------------------------------------------------------------------------------------
// 
//			エンドロール
// 
//------------------------------------------------------------------------------------------------------------------------------------------------------

#define END_SPEED	5.0f

//------------------------------------------------------------------------------------------------------------------------------------------------------
// エンドロール
//------------------------------------------------------------------------------------------------------------------------------------------------------


void end_roll_stop_exec( TASK *ap )
{
	if( ap->pos[ Y ] >= WINDOW_HEIGHT /2 )		// 特定の座標を超えたらタスクエンド
	{
		ap->work1[ X ] ++;						// フレーム計算
		if( ap->work1[ X ] > 180 )				// 特定のフレームを超えたらタイトル画面に移動
		{
			fade(5, TYPE_TITLE );
			demo_mode = 2;
//			game_type = TYPE_TITLE;
			TASK_end( ap );
			return;
		}
	}
	else
		ap->pos[ Y ] += ap->vec[ Y ];						// 座標移動

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
	ap->pos[ Y ] += ap->vec[ Y ];						// 座標移動
	if( ap->pos[ Y ] >= WINDOW_HEIGHT + 128.0f )		// 特定の座標を超えたらタスクエンド
	{
		end_roll_stop();								// THANK YOU FOR PLAYING を表示
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
				ap->work1[ X ]++;								// フレーム計算	
				if( ap->work1[ X ] > 160 )
				{
					ap->pos[ Y ] += ap->vec[ Y ];				// 座標移動
					if( ap->pos[ Y ] >= WINDOW_HEIGHT *2.2f )	// 特定の座標を超えたらタスクエンド
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
	ap = TASK_start_GRP( end_roll_logo_exec, GROUP_UI, TEXTURE_LOGO, ui_font_rect, 0,  "タイトルロゴを表示" );
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
	// 決定ボタンか、戻るボタンが押されたらエンドロールを強制終了してタイトル画面に
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
	ap = TASK_start( end_roll_exec, GROUP_UI, "エンドロール" );
	end_roll_logo();
}