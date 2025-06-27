#ifdef WINDOWS_PC
#include    "C:/project/libs/systemOZ_v4/soz.h"
#else
#include    "D:/project/guardians_2dx/proj.win32/src/systemOZ/soz.h"
#endif

#include    "C:/project/bace/src/game/game_include.h"


//------------------------------------------------------------------------------------------------------------------------------------------------------
//
//			SCORE
//
//------------------------------------------------------------------------------------------------------------------------------------------------------
SINT32 score = 0 , bonus = 0;
SINT32 hi_score[10];

SINT32 chenge_color[ 4 ][ 3 ]=
{
	{ 0xff, 0xff, 0xff },
	{ 0xff, 0xfb, 0x85 },
	{ 0x81, 0xff, 0xff },
	{ 0xff, 0x7e, 0xf3 },
};

//------------------------------------------------------------------------------------------------------------------------------------------------------
// 加算するスコアを表示
//------------------------------------------------------------------------------------------------------------------------------------------------------
void add_score_disp_drawfunc( TASK *ap )
{
	TASK spr;
	SINT8 str[ 32 ];
	sprintf( str, "%d", ap->workF[ X ] );		// 文字列変換
	TASK_init_member_pointer( &spr );	// タスクメンバの初期化
	spr.tex_no = TEXTURE_UI_FONT;
//	spr.blend_type = BLEND_ADD;
	spr.grp_mode = ap->grp_mode;
	spr.uv_rect = ui_font_num_rect;
	spr.pos[ X ] = ap->pos[ X ];
	spr.pos[ Y ] = ap->pos[ Y ];
	spr.pos[ Z ] = ap->pos[ Z ];
	spr.scale[ X ] = ap->scale[ X ];
	spr.scale[ Y ] = ap->scale[ Y ];
	for( int i = 0; i < 10; i++ )
	{
		if( str[ i ] >= '0'&& str[ i ] <= '9' )
		{
			spr.base_color[ 0 ][ 0 ] = ap->base_color[ 0 ][ 0 ];
			spr.anime_no = str[ i ] - '0';
		}
		else
		{
			spr.base_color[ 0 ][ 0 ] = 0x00;
			spr.anime_no = 0;
		}
		spr.base_color[ 0 ][ 1 ] = ap->base_color[ 0 ][ 1 ];
		spr.base_color[ 0 ][ 2 ] = ap->base_color[ 0 ][ 2 ];
		spr.base_color[ 0 ][ 3 ] = ap->base_color[ 0 ][ 3 ];
		SOZ_sprite_draw( &spr );	// 描画の実行
		spr.pos[ X ] += 100.0f;
	}
}
void add_score_disp_exec( TASK *ap )
{
	ap->work1[ X ]++;
	//if( ap->work1[ X ] % 5 == 0 )
	//	ap->work1[ Y ]++;
	ap->base_color[ 0 ][ 1 ] = chenge_color[ ap->work1[ X ] % 4 ][ 0 ];
	ap->base_color[ 0 ][ 1 ] = chenge_color[ ap->work1[ X ] % 4 ][ 1 ];
	ap->base_color[ 0 ][ 1 ] = chenge_color[ ap->work1[ X ] % 4 ][ 2 ];

	ap->pos[ Y ] += 5.0f;
	ap->pos[ Z ] -= 25.0f;
	ap->base_color[ 0 ][ 0 ] -= 5;
	if( ap->base_color[ 0 ][ 0 ] < 5 )
	{
		TASK_end( ap );
	}
	grp_look_camer( ap );				// カメラに向くようになる
}
void add_score_disp( SINT32 add_score, FLOAT pos_x, FLOAT pos_y, FLOAT pos_z )
{
	TASK *ap;
	ap = TASK_start_DRAWFUNC( add_score_disp_exec, add_score_disp_drawfunc, GROUP_UI, "加算するスコア数字の表示" );
	ap->grp_mode = USE_3DPOS | FLIP_LR ;
	ap->pos[ X ] = pos_x;
	ap->pos[ Y ] = pos_y;
	ap->pos[ Z ] = pos_z + 1000.0f;
	ap->pri = PRI_UI;
//	ap->pri = PRI_ENEMY + 10;
	ap->scale[ Y ] = ap->scale[ X ] = 1.0f;
	ap->work1[ X ] = 0;
	ap->workF[ X ] = add_score;
}

//------------------------------------------------------------------------------------------------------------------------------------------------------
// HI-SCORE
//------------------------------------------------------------------------------------------------------------------------------------------------------
void hi_score_disp_exec( TASK *ap )
{
	if( game_type == TYPE_CLEAR || game_type == TYPE_OVER )		// リザルト画面に飛んだらこのタスクを消す
	{
		TASK_end( ap );
		return;
	}
}

void hi_score_disp_drawfunc( TASK *ap )
{
	TASK spr;
	SINT8 str[ 32 ];
	sprintf( str, "%10d", hi_score[ 0 ] );		// 文字列変換
	TASK_init_member_pointer( &spr );	// タスクメンバの初期化
	spr.tex_no = TEXTURE_UI_FONT;
	spr.uv_rect = ui_font_num_rect;
	spr.pos[ X ] = ap->pos[ X ];
	spr.pos[ Y ] = ap->pos[ Y ];
	spr.scale[ X ] = ap->scale[ X ];
	spr.scale[ Y ] = ap->scale[ Y ];
	for( int i = 0; i < 10; i++ )
	{
		if( str[ i ] >= '0'&& str[ i ] <= '9' )
		{
			spr.base_color[ 0 ][ 0 ] = 0xff;
			spr.anime_no = str[ i ] - '0';
		}
		else
		{
			spr.base_color[ 0 ][ 0 ] = 0x88;
			spr.anime_no = 0;
		}

		SOZ_sprite_draw( &spr );	// 描画の実行
		spr.pos[ X ] += 30.0f;
	}
}

void hi_score_disp( void )
{
	TASK *ap;
	ap = TASK_start_GRP( hi_score_disp_exec, GROUP_UI, TEXTURE_UI_FONT, ui_font_rect, 9, "HI-SCOREのフォントを表示" );
	ap->pos[ X ] = 120.0f;
	ap->pos[ Y ] = 105.0f;
	ap->pri = PRI_UI_FONT;
	ap->scale[ X ] = 0.3f;
	ap->scale[ Y ] = ap->scale[ X ];

	ap = TASK_start_DRAWFUNC( hi_score_disp_exec, hi_score_disp_drawfunc, GROUP_UI, "ハイスコア数字の表示" );
	ap->pos[ X ] = 250.0f;
	ap->pos[ Y ] = 105.0f;
	ap->pri = PRI_UI_FONT;
	ap->scale[ X ] = 0.3f;
	ap->scale[ Y ] = ap->scale[ X ];

	ap = TASK_start_GRP( hi_score_disp_exec, GROUP_UI, TEXTURE_UI_FONT, ui_selecter_rect, 0, "ハイスコアの下のライン" );
	ap->pos[ X ] = 270.0f;
	ap->pos[ Y ] = 100.0f;
	ap->pri = PRI_UI_FONT -10;
	ap->scale[ X ] = 0.85f;
	ap->scale[ Y ] = ap->scale[ X ];
}



//------------------------------------------------------------------------------------------------------------------------------------------------------
// SCORE
//------------------------------------------------------------------------------------------------------------------------------------------------------
void score_disp_exec( TASK *ap )
{
	if( game_type == TYPE_CLEAR || game_type == TYPE_OVER )		// リザルト画面に飛んだらこのタスクを消す
	{
		TASK_end( ap );
		return;
	}
}

void score_disp_drawfunc( TASK *ap )
{
	TASK spr;
	SINT8 str[ 32 ];
	sprintf( str, "%10d", score );		// 文字列変換
	TASK_init_member_pointer( &spr );	// タスクメンバの初期化
	spr.tex_no = TEXTURE_UI_FONT;
	spr.uv_rect = ui_font_num_rect;
	spr.pos[ X ] = ap->pos[ X ];
	spr.pos[ Y ] = ap->pos[ Y ];
	spr.scale[ X ] = ap->scale[ X ];
	spr.scale[ Y ] = ap->scale[ Y ];
	for( int i = 0; i < 10; i++ )
	{
		if( str[ i ] >= '0'&& str[ i ] <= '9' )
		{
			spr.base_color[ 0 ][ 0 ] = 0xff;
			spr.anime_no = str[ i ] - '0';
		}
		else
		{
			spr.base_color[ 0 ][ 0 ] = 0x88;
			spr.anime_no = 0;
		}

		SOZ_sprite_draw( &spr );	// 描画の実行
		spr.pos[ X ] += 40.0f;
	}
}

void score_disp( void )
{
	TASK *ap;
	ap = TASK_start_GRP( score_disp_exec, GROUP_UI, TEXTURE_UI_FONT, ui_font_rect, 8, "SCOREのフォントを表示" );
	ap->pos[ X ] = 110.0f;
	ap->pos[ Y ] = 32.0f;
	ap->pri = PRI_UI_FONT;
	ap->scale[ X ] = 0.4f;
	ap->scale[ Y ] = ap->scale[ X ];

	ap = TASK_start_DRAWFUNC( score_disp_exec, score_disp_drawfunc, GROUP_UI, "スコア数字の表示" );
	ap->pos[ X ] = 240.0f;
	ap->pos[ Y ] = 32.0f;
	ap->pri = PRI_UI_FONT;
	ap->scale[ X ] = 0.4f;
	ap->scale[ Y ] = ap->scale[ X ];

	ap = TASK_start_GRP( score_disp_exec, GROUP_UI, TEXTURE_UI_FONT, ui_selecter_rect, 0, "スコアの下のライン" );
	ap->pos[ X ] = 300.0f;
	ap->pos[ Y ] = 32.0f;
	ap->pri = PRI_UI_FONT;
	ap->scale[ X ] = 1.05f;
	ap->scale[ Y ] = ap->scale[ X ];
}


//------------------------------------------------------------------------------------------------------------------------------------------------------
// ランキング用SCORE表示
//------------------------------------------------------------------------------------------------------------------------------------------------------
void ranking_score_disp_exec ( TASK *ap )
{
}

void ranking_score_disp_drawfunc ( TASK *ap )
{
	TASK spr;
	SINT8 str[ 32 ];
	sprintf( str, "%10d", hi_score[ap->work1[ X ] ] );		// 文字列変換
	TASK_init_member_pointer( &spr );	// タスクメンバの初期化
	spr.tex_no = TEXTURE_UI_FONT;
	spr.uv_rect = ui_font_num_rect;
	spr.pos[ X ] = ap->pos[ X ];
	spr.pos[ Y ] = ap->pos[ Y ];
	spr.scale[ X ] = ap->scale[ X ];
	spr.scale[ Y ] = ap->scale[ Y ];
	for( int i = 0; i < 10; i++ )
	{
		if( str[ i ] >= '0'&& str[ i ] <= '9' )
		{
			spr.base_color[ 0 ][ 0 ] = 0xff;
			spr.anime_no = str[ i ] - '0';
		}
		else
		{
			spr.base_color[ 0 ][ 0 ] = 0x88;
			spr.anime_no = 0;
		}

		SOZ_sprite_draw( &spr );	// 描画の実行
		if( ap->work1[ X ] < 3 )
			spr.pos[ X ] += 60.0f;
		else
			spr.pos[ X ] += 40.0f;
	}
}

void ranking_score_disp( SINT32 Rank )
{
	FLOAT scale_size = 0.4f;
	if( Rank < 3 )
		scale_size = 0.6f;
	TASK *ap;
	ap = TASK_start_DRAWFUNC( ranking_score_disp_exec, ranking_score_disp_drawfunc, GROUP_UI, "スコア数字の表示" );
	ap->pos[ X ] = 850.0f;
	ap->pos[ Y ] = 200 + 90.0f * Rank;
	ap->pri = PRI_UI_FONT;
	ap->scale[ Y ] = ap->scale[ X ] = scale_size;
	ap->work1[ X ] = Rank;

	ap = TASK_start_GRP( ranking_score_disp_exec, GROUP_UI, TEXTURE_UI_FONT, ui_font_num_rect, Rank + 1, "順位表示");
	ap->pos[ X ] = 685.0f;
	if( Rank < 3 )
		ap->pos[ X ] = 650.0f;

	ap->pos[ Y ] = 200 + 90.0f * Rank;
	ap->pri = PRI_UI_FONT;
	ap->scale[ Y ] = ap->scale[ X ] = scale_size;
	ap->work1[ X ] = Rank;
	if( Rank + 1 > 9 )
	{
		ap->anime_no = 0;
		ap = TASK_start_GRP( ranking_score_disp_exec, GROUP_UI, TEXTURE_UI_FONT, ui_font_num_rect, 1, "順位表示");
		ap->pos[ X ] = 645.0f;
		ap->pos[ Y ] = 200 + 90.0f * Rank;
		ap->pri = PRI_UI_FONT;
	ap->scale[ Y ] = ap->scale[ X ] = scale_size;
		ap->work1[ X ] = Rank;
	}

	ap = TASK_start_GRP( ranking_score_disp_exec, GROUP_UI, TEXTURE_UI_FONT, ranking_rect, 0, "順位表示");
	ap->pos[ X ] = 750.0f;
	ap->pos[ Y ] = 200 + 90.0f * Rank;
	ap->pri = PRI_UI_FONT;
	switch ( Rank )		// st. nd. rd. と　th. の表示切り替え
	{
		case 0:
		case 1:						
		case 2:
			ap->anime_no = Rank;
			break;

		default:
			ap->anime_no = 3;
			break;
	}
	ap->scale[ Y ] = ap->scale[ X ] = scale_size;
	ap->work1[ X ] = Rank;
}

void ranking_disp_exec( TASK *ap )
{
	if( SOZ_Inkey_TRG( DIK_X ) || SOZ_Inpad_TRG( 0, PADDIK_CANCEL ) )
	{
		game_type = TYPE_MENU;											// 戻るボタンを押すとメニュー画面に戻る
		TASK_all_init();
		bg_base_jiki();
		return;
	}
}
void ranking_disp( void )
{
	SINT32 Rank = 0;
	TASK *ap;
	ap = TASK_start_GRP( ranking_disp_exec, GROUP_UI, TEXTURE_UI_FONT, ui_font_rect, 5, "ランキングの表示");
	ap->pos[ X ] = WINDOW_WIDTH /2;
	ap->pos[ Y ] = 100.0f;
	ap->pri = PRI_UI;
	for( Rank = 0; Rank < 10; Rank++ )		// 10位まで表示
		ranking_score_disp( Rank );
}

