#ifdef WINDOWS_PC
#include    "C:/project/libs/systemOZ_v4/soz.h"
#else
#include    "D:/project/guardians_2dx/proj.win32/src/systemOZ/soz.h"
#endif

#include    "C:/project/bace/src/game/game_include.h"

SINT32 stage = 0;


//------------------------------------------------------------------------------------------------------------------------------------------------------
// DEMO PLAYの表示
//------------------------------------------------------------------------------------------------------------------------------------------------------
void demo_play_disp_exec( TASK *ap )
{
	ap->base_color[ 0 ][ 0 ] -= ap->work1[ X ];
	if( ap->base_color[ 0 ][ 0 ] < 0x22 || ap->base_color[ 0 ][ 0 ] > 0x88 )
		ap->work1[ X ] *= -1;
}
void demo_play_disp( void )
{
	TASK *ap;
	ap = TASK_start_GRP( demo_play_disp_exec, GROUP_UI, TEXTURE_DEMO_PLAY, demo_rect, 0, "DEMO PLAY表示" );
	ap->pos[ X ] = WINDOW_WIDTH /2;
	ap->pos[ Y ] = WINDOW_HEIGHT /2;
	ap->scale[ Y ] = ap->scale[ X ] = 2.0f;
	ap->pri = PRI_UI + 5000 *WP;
	ap->base_color[ 0 ][ 0 ] = 0x88;
	ap->work1[ X ] = 1;
}

//------------------------------------------------------------------------------------------------------------------------------------------------------
// 
//			game画面のUI
// 
//------------------------------------------------------------------------------------------------------------------------------------------------------

//------------------------------------------------------------------------------------------------------------------------------------------------------
// 攻撃操作方法の表示
//------------------------------------------------------------------------------------------------------------------------------------------------------
void atack_cont_disp_exec( TASK *ap )
{
	// 自機の残基がなくなったらタスクエンド
	if( life == 0 )
	{
		TASK_end( ap );
		return;
	}
}
void atack_cont_disp( void )
{
	TASK *ap;
	ap = TASK_start_GRP( atack_cont_disp_exec, GROUP_UI, TEXTURE_UI_FONT_4, ui_game_rect, 2, "攻撃操作の表示" );
	ap->pos[ X ] = WINDOW_WIDTH - 270.0f;
	ap->pos[ Y ] = WINDOW_HEIGHT - 100.0f;
	ap->scale[ Y ] = ap->scale[ X ] = 0.75f;
	ap->pri = PRI_UI;
}


//------------------------------------------------------------------------------------------------------------------------------------------------------
// ボスのロゴの表示
//------------------------------------------------------------------------------------------------------------------------------------------------------
void boss_logo_exec( TASK *ap )
{
	switch ( ap->workA[ X ] )
	{
	case 0:		// フェードイン
		ap->base_color[ 0 ][ 0 ] += 2;
		if( ap->base_color[ 0 ][ 0 ] > 255 )
			ap->workA[ X ] = 1;
		break;

	case 1:
		ap->base_color[ 0 ][ 0 ] -= 5;
		if( ap->base_color[ 0 ][ 0 ] < 10 )
		{
			boss_start();
			ap->workA[ X ] = 2;
		}
		break;

	case 2:
		ap->base_color[ 0 ][ 0 ] = 0xff;
		ap->scale[ Y ] = ap->scale[ X ] = 0.5f;
		ap->pos[ Y ] = 150.0f;
		ap->workA[ X ] ++;
		break;
	}
}
void boss_logo( void )
{
	TASK *ap;
	ap = TASK_start_GRP( boss_logo_exec, GROUP_UI, TEXTURE_BOSS_LOGO, boss_logo_rect, 0, "ボスのロゴ" );
	ap->delay = 30;
	ap->pos[ X ] = WINDOW_WIDTH /2;
	ap->pos[ Y ] = WINDOW_HEIGHT /2;
	ap->base_color[ 0 ][ 0 ] = 0x00;
	ap->pri = PRI_JIKI -100;
	ap->scale[ Y ] = ap->scale[ X ] = 1.0f;
	ap->workA[ X ] = 0;
}

//------------------------------------------------------------------------------------------------------------------------------------------------------
// スティック操作スイッチの表示
//------------------------------------------------------------------------------------------------------------------------------------------------------
void stick_switch_exec( TASK *ap )
{
	ap->anime_no = j_state_mode + 1;
}
void stick_font_exec( TASK *ap )
{
//	何もしない
}
void stick_switch_disp( void )
{
	TASK *ap;
	ap = TASK_start_GRP( stick_font_exec, GROUP_UI, TEXTURE_UI_FONT_3, ui_font_2_rect, 0, "[stick operation]フォント表示" );
	ap->pos[ X ] = WINDOW_WIDTH /2;
	ap->pos[ Y ] = 132.0f;
	ap->scale[ Y ] = ap->scale[ X ] = 0.5f;
	ap->pri = PRI_UI;

	ap = TASK_start_GRP( stick_switch_exec, GROUP_UI, TEXTURE_UI_GAME,  ui_cont_rect, 1, "スイッチの画像" );
	ap->pos[ X ] = 1600.0f;
	ap->pos[ Y ] = 132.0f;
	ap->scale[ Y ] = ap->scale[ X ] = 1.0f;
	ap->pri = PRI_UI;
}

//------------------------------------------------------------------------------------------------------------------------------------------------------
// 操作説明用グラフィックの表示
//------------------------------------------------------------------------------------------------------------------------------------------------------

void ui_cont_disp_exec( TASK *ap )
{
	if( SOZ_Inkey_TRG( DIK_X ) || SOZ_Inpad_TRG( 0, PADDIK_CANCEL ) )			// 戻るボタンが押されたらメニュー画面に戻る
	{
		game_type = TYPE_MENU;
		TASK_all_init();
		bg_base_jiki();
		return;
	}
}
void ui_cont_disp( FLOAT pos_x, FLOAT pos_y, FLOAT scale )
{
	TASK *ap;
	ap = TASK_start_GRP( ui_cont_disp_exec, GROUP_UI, TEXTURE_CONTROLL, ui_cont_rect, 0, "操作説明" );
	ap->pos[ X ] = pos_x;
	ap->pos[ Y ] = pos_y;
	ap->scale[ X ] = ap->scale[ Y ] = scale;
	//ap->pos[ X ] = WINDOW_WIDTH / 2 + 50.0f;	// 画面中心に表示する
	//ap->pos[ Y ] = WINDOW_HEIGHT /2 + 250.0f;
	//ap->scale[ X ] = ap->scale[ Y ] = 0.8f;
	ap->pri = PRI_UI;
}





//------------------------------------------------------------------------------------------------------------------------------------------------------
// ゲーム画面　ENGAGE( GAME START )の表示
//------------------------------------------------------------------------------------------------------------------------------------------------------
void engage_exec( TASK *ap )
{
	ap->work1[ X ] ++;	// フレーム計算

// 少しの間表示する画像を切り替える
	if( ap->work1[ X ] > 110 )
		ap->anime_no = 0;
	else if( ap->work1[ X ] > 90 )
	{
		ap->scale[ Y ] = ap->scale[ X ] = 2.0f;
		ap->tex_no = TEXTURE_UI_FONT;
		ap->anime_no = 1;
	}

	if( ap->work1[ X ] > 140 )	// 特定フレーム経過したか
	{
		ap->base_color[ 0 ][ 0 ] -= 5;
		if( ap->base_color[ 0 ][ 0 ] < 10 )	// 透明度が特定の値を下回ったらタスクエンド
		{
			TASK_end( ap );
			return;
		}
	}
}
void engage_disp( void )
{
	TASK *ap;
	ap = TASK_start_GRP( engage_exec, GROUP_UI, TEXTURE_UI_FONT_3, engage_rect, 2, "ENGAGE を表示" );
	ap->pos[ X ] = WINDOW_WIDTH /2;
	ap->pos[ Y ] = WINDOW_HEIGHT /2;
	ap->pri = PRI_UI;
	ap->work1[ X ] = 0;
	ap->scale[ Y ] = ap->scale[ X ] = 0.7f;
}

//------------------------------------------------------------------------------------------------------------------------------------------------------
// ゲーム画面　ミサイル残弾数の表示
//------------------------------------------------------------------------------------------------------------------------------------------------------
void missile_num_disp_exec( TASK *ap )
{
	// 特に何もしない
}
void missile_num_drawfunc( TASK *ap )
{
	TASK spr;
	SINT8 str[ 32 ];
	sprintf( str, "%02d", rest_missile );		// 文字列変換
	TASK_init_member_pointer( &spr );	// タスクメンバの初期化
	spr.tex_no = TEXTURE_UI_FONT;
	spr.uv_rect = ui_font_num_rect;
	spr.pos[ X ] = ap->pos[ X ];
	spr.pos[ Y ] = ap->pos[ Y ];
	spr.scale[ X ] = ap->scale[ X ];
	spr.scale[ Y ] = ap->scale[ Y ];
//	spr.pri = PRI_UI;
	for( int i = 0; i < 2; i++ )
	{
		if( str[ i ] >= '0'&& str[ i ] <= '9' )
			spr.anime_no = str[ i ] - '0';
		else
			spr.anime_no = 0;

		SOZ_sprite_draw( &spr );	// 描画の実行
		spr.pos[ X ] += 64.0f;
	}
}
void missile_num_disp( void )
{
	TASK *ap;
	ap = TASK_start_GRP( missile_num_disp_exec, GROUP_UI, TEXTURE_UI_GAME, ui_game_rect, 0, "残弾数表示" );
	ap->pos[ X ] = 150.0f;
	ap->pos[ Y ] = WINDOW_HEIGHT -100.0f;
	ap->pri = PRI_UI_FONT;
	ap->scale[ Y ] = ap->scale[ X ] = 0.8f;

	ap = TASK_start_GRP( missile_num_disp_exec, GROUP_UI, TEXTURE_UI_FONT, ui_font_num_rect, 10, "xの表示" );
	ap->pos[ X ] = 250.0f;
	ap->pos[ Y ] = WINDOW_HEIGHT -80.0f;
	ap->pri = PRI_UI_FONT;
	ap->scale[ Y ] = ap->scale[ X ] = 0.8f;

	ap = TASK_start_DRAWFUNC( missile_num_disp_exec, missile_num_drawfunc, GROUP_UI, "残弾の数字を表示");
	ap->pos[ X ] = 330.0f;
	ap->pos[ Y ] = WINDOW_HEIGHT -80.0f;
	ap->pri = PRI_UI_FONT;
	ap->scale[ Y ] = ap->scale[ X ] = 0.6f;
}

//------------------------------------------------------------------------------------------------------------------------------------------------------
// ゲーム画面　残り残機の表示
//------------------------------------------------------------------------------------------------------------------------------------------------------
void life_disp_exec( TASK *ap )
{
	// 特に何もしない
}
void life_count_exec( TASK *ap )
{
	ap->anime_no = life;					// 残機に応じて表示グラフィックの変更
	if( ap->anime_no == 1 )					// 残機が１になったら、色を赤にする
	{
		ap->base_color[ 0 ][ 2 ] = 0x0f;
		ap->base_color[ 0 ][ 3 ] = 0x08;
	}
}
void life_disp( void )
{
	TASK *ap;
	ap = TASK_start_GRP( life_disp_exec, GROUP_UI, TEXTURE_UI_GAME, ui_game_rect, 1, "残機表示" );
	ap->pos[ X ] = WINDOW_WIDTH - 400.0f;
	ap->pos[ Y ] = 200.0f;
	ap->pri = PRI_UI_FONT;

	ap = TASK_start_GRP( life_disp_exec, GROUP_UI, TEXTURE_UI_FONT, ui_font_num_rect, 10, "xの表示" );
	ap->pos[ X ] = WINDOW_WIDTH - 290.0f;
	ap->pos[ Y ] = 220.0f;
	ap->pri = PRI_UI_FONT;
	
	ap = TASK_start_GRP( life_count_exec, GROUP_UI, TEXTURE_UI_FONT, ui_font_num_rect, 10, "残機の数字を表示" );
	ap->pos[ X ] = WINDOW_WIDTH - 200.0f;
	ap->pos[ Y ] = 220.0f;
	ap->scale[ X ] = ap->scale[ Y ] = 0.8f;
	ap->pri = PRI_UI_FONT;
}

//------------------------------------------------------------------------------------------------------------------------------------------------------
// ゲーム画面右上stageの表示
//------------------------------------------------------------------------------------------------------------------------------------------------------
void stage_disp_drawfunc( TASK *ap )
{
	TASK spr;
	SINT8 str[ 32 ];
	sprintf( str, "%02d", stage );		// 文字列変換
	TASK_init_member_pointer( &spr );	// タスクメンバの初期化
	spr.tex_no = TEXTURE_UI_FONT;
	spr.uv_rect = ui_font_num_rect;
	spr.pos[ X ] = ap->pos[ X ];
	spr.pos[ Y ] = ap->pos[ Y ];
	spr.scale[ X ] = ap->scale[ X ];
	spr.scale[ Y ] = ap->scale[ Y ];
	for( int i = 0; i < 2; i++ )
	{
		if( str[ i ] >= '0'&& str[ i ] <= '9' )
			spr.anime_no = str[ i ] - '0';

		SOZ_sprite_draw( &spr );	// 描画の実行
		spr.pos[ X ] += 64.0f;
	}
}

void stage_disp_exec( TASK *ap )
{
	// 特に何もしない
}

void stage_disp( void )
{
	TASK *ap;
	ap = TASK_start_GRP( stage_disp_exec, GROUP_UI, TEXTURE_UI_FONT, ui_font_rect, 10, "「STAGE」フォント表示" );
	ap->pos[ X ] = WINDOW_WIDTH -340.0f;
	ap->pos[ Y ] = 44;
	ap->pri = PRI_UI_FONT;
	ap->scale[ X ] = 0.65f;
	ap->scale[ Y ] = ap->scale[ X ];

	ap = TASK_start_DRAWFUNC( stage_disp_exec, stage_disp_drawfunc, GROUP_UI, "「STAGE」フォント表示" );
	ap->pos[ X ] = WINDOW_WIDTH -140.0f;
	ap->pos[ Y ] = 44;
	ap->pri = PRI_UI_FONT;
	ap->scale[ X ] = 0.65f;
	ap->scale[ Y ] = ap->scale[ X ];



	ap = TASK_start_GRP( stage_disp_exec, GROUP_UI, TEXTURE_UI_FONT, ui_selecter_rect, 0, "STAGE の下のライン" );
	ap->grp_mode = FLIP_LR;
	ap->pos[ X ] = WINDOW_WIDTH -100.0f;
	ap->pos[ Y ] = 40.0f;
	ap->pri = PRI_UI_FONT -10;
	ap->scale[ X ] = 1.4f;
	ap->scale[ Y ] = ap->scale[ X ];
}

//------------------------------------------------------------------------------------------------------------------------------------------------------
// WARNING表示
//------------------------------------------------------------------------------------------------------------------------------------------------------
//------------------------------------------------------------------------------------------------------------------------------------------------------
// WARNING_の上下のライン
//------------------------------------------------------------------------------------------------------------------------------------------------------
void warning_line_exec( TASK *ap )
{
	ap->pos[ X ] += ap->vec[ X ];
	switch ( ap->work1[ X ] )	// 上と下どちらに表示するかで、タスクエンドさせる座標を変更する。
	{
		case 0:
			if( ap->pos[ X ] < ap->fwork1[ X ] )
			{
				TASK_end( ap );
				return;
			}
			break;

		case 1:
			if( ap->pos[ X ] > ap->fwork1[ X ] )
			{
				TASK_end( ap );
				return;
			}
			break;
	}
}
void warning_line( SINT32 type )
{
	TASK *ap;
	ap = TASK_start_GRP( warning_line_exec, GROUP_UI, TEXTURE_WARNING, warning_rect, 0, "warningの上下ライン" );
	switch ( type )
	{
		case 0:	// 上
			ap->pos[ X ] = WINDOW_WIDTH + 128.0f;
			ap->pos[ Y ] = WINDOW_HEIGHT /2 - 128.0f;
			ap->vec[ X ] = -32.0f;
			ap->fwork1[ X ] = -132.0f;
			break;
		case 1:	// 下
			ap->pos[ X ] = -128.0f;
			ap->pos[ Y ] = WINDOW_HEIGHT /2 + 128.0f;
			ap->vec[ X ] = 32.0f;
			ap->fwork1[ X ] = WINDOW_WIDTH + 132.0f;
			ap->grp_mode = FLIP_UD | FLIP_LR;
			break;
	}
	ap->pri = PRI_UI;
	ap->work1[ X ] = type;
}

void line_gen_core( TASK *ap )
{
	ap->work1[ X ] ++;
	if( ap->work1[ X ] % 4 == 0 )	// 特定フレームごとにラインのタスクを生成する。
	{
		warning_line( 0 );
		warning_line( 1 );
	}
	if( ap->work1[ X ] > 60 * 4 )	// 特定フレーム経過したらタスクエンド
	{
		TASK_end( ap );
		return;
	}
}
void warning_line_gen( void )
{
	TASK *ap;
	ap = TASK_start( line_gen_core, 0, "warningのライン発生関数" );
	ap->work1[ X ];
}

void warning_font_exec( TASK *ap )
{
	ap->work1[ X ] ++;
	if( ap->work1[ X ] % 10 == 0 )	// 特定フレームごとにラインのタスクを生成する。
		bic_illusion_start( ap, 25, BLEND_ADD );
	if( ap->work1[ X ] > 60 * 4 )	// 特定フレーム経過したらタスクエンド
	{
		boss_code_disp();
		TASK_end( ap );
		return;
	}
}
void warning_font( void )
{
	TASK *ap;
	ap = TASK_start_GRP( warning_font_exec, GROUP_UI, TEXTURE_WARNING, warning_rect, 1, "WARNING フォント表示" );
	ap->pos[ X ] = WINDOW_WIDTH /2;
	ap->pos[ Y ] = WINDOW_HEIGHT /2;
	ap->scale[ Y ] = ap->scale[ X ] = 2.0f;
	ap->pri = PRI_UI;
}

void warning( void )
{
	warning_line_gen();
	warning_font();
	SOZ_play_se( SE_WARNING, 3.0f, 1, 0.0f );
}






