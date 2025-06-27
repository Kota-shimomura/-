#ifdef WINDOWS_PC
#include    "C:/project/libs/systemOZ_v4/soz.h"
#else
#include    "D:/project/guardians_2dx/proj.win32/src/systemOZ/soz.h"
#endif

#include    "C:/project/bace/src/game/game_include.h"

//-----------------------------------------------------------------------------------------------
// 
//		GAME CLEAR / GAME OVER の表示
// 
//-----------------------------------------------------------------------------------------------
void game_over_disp_exec( TASK *ap )
{
	ap->work1[ X ] ++;
// 決定ボタンが押されるか、特定時間の経過でリザルト画面に
	if( SOZ_Inkey_TRG( DIK_Z ) || SOZ_Inpad_TRG( 0, PADDIK_DECIDE ) || ap->work1[ X ] > 60 * 30 )
	{
		game_type++;
		TASK_end( ap );
		return;
	}
}
void game_over_disp( void )
{
	TASK *ap;
	ap = TASK_start_GRP( game_over_disp_exec, GROUP_UI, TEXTURE_UI_FONT_2, ui_font_rect, 13, "GAME OVER 表示" );
	ap->pos[ X ] = WINDOW_WIDTH /2;
	ap->pos[ Y ] = WINDOW_HEIGHT/2;
	ap->pri = PRI_UI_FONT;
	ap->work1[ X ] = 0;
}


void game_clear_disp_exec( TASK *ap )
{
	ap->work1[ X ] ++;
// 決定ボタンが押されるか、特定時間の経過でリザルト画面に
	if( SOZ_Inkey_TRG( DIK_Z ) || SOZ_Inpad_TRG( 0, PADDIK_DECIDE ) || ap->work1[ X ] > 60 * 30 )
	{
		game_type = TYPE_CLEAR + 2;
		TASK_end( ap );
		return;
	}
}
void game_clear_disp( void )
{
	TASK *ap;
	ap = TASK_start_GRP( game_clear_disp_exec, GROUP_UI, TEXTURE_UI_FONT_2, ui_font_rect, 12, "GAME CLEAR 表示" );
	ap->pos[ X ] = WINDOW_WIDTH /2;
	ap->pos[ Y ] = WINDOW_HEIGHT/2;
	ap->pri = PRI_UI_FONT;
	ap->work1[ X ] = 0;
}

//-----------------------------------------------------------------------------------------------
// 
//		リザルト画面の表示
// 
//-----------------------------------------------------------------------------------------------

#define GAME_OVER			0
#define GAME_CLEAR			1

#define RESULT_RETRY		0
#define RESULT_MENU			1
#define RESULT_STAFF_ROLL	2

SINT32 result_selecter = 0;		// リザルト画面のセレクター

//-----------------------------------------------------------------------------------------------
// リザルト画面:ボタンの表示
//-----------------------------------------------------------------------------------------------
// ------------- セレクター制御プログラム ----------------------
void result_selecter_exec( TASK *ap )
{
	switch( ap->work1[ X ] )	// GAME OVER か GAME CLEAR で少し動作を変える
	{
		case GAME_OVER:	// GAME OVER
			// キーの上か下もしくは、パッドの上か下が入力されたとき
			if( SOZ_Inkey_TRG( DIK_UP ) || SOZ_Inpad_TRG( 0, PADDIK_UP ) )		// セレクターの上移動
			{
				SOZ_play_se( SE_SERECT, 2.0f, 1, 1.0f );
					result_selecter = 0;
			}
			if( SOZ_Inkey_TRG( DIK_DOWN ) || SOZ_Inpad_TRG( 0, PADDIK_DOWN ) )	// セレクターの下移動
			{
				SOZ_play_se( SE_SERECT, 2.0f, 1, 1.0f );
					result_selecter = 1;
			}
			break;

		case GAME_CLEAR:	// GAME CLEAR
			if( SOZ_Inkey_TRG( DIK_UP ) || SOZ_Inpad_TRG( 0, PADDIK_UP ) )		// セレクターの上移動
			{
				SOZ_play_se( SE_SERECT, 2.0f, 1, 1.0f );
				if( result_selecter > RESULT_RETRY )
					result_selecter--;
			}
			if( SOZ_Inkey_TRG( DIK_DOWN ) || SOZ_Inpad_TRG( 0, PADDIK_DOWN ) )	// セレクターの下移動
			{
				SOZ_play_se( SE_SERECT, 2.0f, 1, 1.0f );
				if( result_selecter < RESULT_STAFF_ROLL )
					result_selecter++;
			}
			break;
	}
}
void result_selecter_start( SINT32 type )
{
	TASK *ap;
	ap = TASK_start( result_selecter_exec, GROUP_UI, "リザルトのセレクター移動" );
	ap->work1[ X ] = type;
	result_selecter = 0;	// セレクターの初期化
}

// ------------- ボタンの表示プログラム ----------------------
typedef struct
{
	SINT32	texture_no;				// 画像の番号
	PARTS_RECT *rect;				// 矩形情報
	SINT32	anime_no;				// アニメナンバー
	SINT32	chenge_game_type;		// 画面の変更先
	CHAR	comment[128];			// コメント
} RESULT_BUTTON;

RESULT_BUTTON result_button[]=
{
	{ TEXTURE_UI_FONT_2, ui_font_rect, 14, TYPE_GAME,"リトライ" },	// RETRY
	{ TEXTURE_UI_FONT_2, ui_font_rect, 15, TYPE_MENU,"メニュー" },	// MENU
	{ TEXTURE_UI_FONT_2, ui_font_rect, 16, TYPE_END,"スタッフロール" },	// STAFF ROLL
};


void result_button_exec( TASK *ap )
{
	ap->work2[ X ] ++;
	if( ap->work1[ X ] == result_selecter )	// セレクターが合っているとき
	{
		ap->base_color[ 0 ][ 0 ] = 0xff;
		ap->base_color[ 0 ][ 1 ] = 0xff;
		ap->base_color[ 0 ][ 2 ] = 0xff;
		ap->base_color[ 0 ][ 3 ] = 0xff;
// 決定ボタンが押されたら特定のgame_typeに飛ばす
		if( SOZ_Inkey_TRG( DIK_Z ) || SOZ_Inpad_TRG( 0, PADDIK_DECIDE ) )
		{
			SOZ_play_se( SE_DECISION, 3.0f, 1, 0.0f );
			TASK_all_init();
			game_type = result_button[ ap->work1[ X ] ].chenge_game_type;
			return;
		}
		if( ap->work2[ X ] % 40 == 0 )	// 10fごとに大きくなるタスクを発生させる
		{
			bic_illusion_start( ap, 10, BLEND_ADD );
		}
	}
	else
	{
		ap->base_color[ 0 ][ 0 ] = 0x88;
		ap->base_color[ 0 ][ 1 ] = 0x88;
		ap->base_color[ 0 ][ 2 ] = 0x88;
		ap->base_color[ 0 ][ 3 ] = 0x88;
	}
}
void result_button_disp( FLOAT pos_y, SINT32 id )
{
	TASK *ap;
	ap = TASK_start_GRP( result_button_exec, GROUP_UI, result_button[id].texture_no, result_button[id].rect, result_button[id].anime_no, result_button[id].comment );
	ap->pos[ X ] = WINDOW_WIDTH /2;
	ap->pos[ Y ] = pos_y;
	ap->pri = PRI_UI_FONT;
	ap->scale[ Y ] = ap->scale[ X ] = 0.75f;
	ap->work1[ X ] = id;	// idの保存
}

void result_button_set( SINT32 type )
{
	result_selecter_start( type );
	switch ( type )
	{
		case GAME_OVER:
			result_button_disp( WINDOW_HEIGHT / 2 + 200, 0 );		// リトライ
			result_button_disp( WINDOW_HEIGHT / 2 + 350, 1 );		// メニュー
			break;

		case GAME_CLEAR:
			result_button_disp( WINDOW_HEIGHT / 2 + 200, 0 );		// リトライ
			result_button_disp( WINDOW_HEIGHT / 2 + 300, 1 );		// メニュー
			result_button_disp( WINDOW_HEIGHT / 2 + 400, 2 );		// スタッフロール
			break;
	}
}

//-----------------------------------------------------------------------------------------------
// リザルト画面:STAGEの表示
//-----------------------------------------------------------------------------------------------
void result_stage_exec( TASK *ap )
{}
void result_stage_drawfunc( TASK *ap )
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
void result_stage_disp( void )
{
	TASK *ap;
	ap = TASK_start_GRP( result_stage_exec, GROUP_UI, TEXTURE_UI_FONT, ui_font_rect, 10, "「STAGE」フォント表示" );
	ap->pos[ X ] = WINDOW_WIDTH/2 - 96;
	ap->pos[ Y ] = 380;
	ap->pri = PRI_UI_FONT;
	ap->scale[ X ] = 0.65f;
	ap->scale[ Y ] = ap->scale[ X ];

	ap = TASK_start_DRAWFUNC( result_stage_exec, result_stage_drawfunc, GROUP_UI, "「STAGE」数字表示" );
	ap->pos[ X ] = WINDOW_WIDTH/2 + 120;
	ap->pos[ Y ] = 380;
	ap->pri = PRI_UI_FONT;
	ap->scale[ X ] = 0.65f;
	ap->scale[ Y ] = ap->scale[ X ];
}

//-----------------------------------------------------------------------------------------------
// リザルト画面:ハイスコアの表示
//-----------------------------------------------------------------------------------------------
void result_hi_score_exec( TASK *ap )
{}
void result_hi_score_drawfunc( TASK *ap )
{
	TASK spr;
	SINT8 str[ 32 ];
	sprintf( str, "%10d", hi_score[0] );		// 文字列変換
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
			spr.anime_no = str[ i ] - '0';
		else
			spr.anime_no = 0;

		SOZ_sprite_draw( &spr );	// 描画の実行
		spr.pos[ X ] += 45.0f;
	}
}
void result_hi_score_disp( void )
{
	TASK *ap;
	ap = TASK_start_GRP( result_hi_score_exec, GROUP_UI, TEXTURE_UI_FONT, ui_font_rect, 9, "HI-SCOREのフォントを表示" );
	ap->pos[ X ] = 690.0f;
	ap->pos[ Y ] = 600.0f;
	ap->pri = PRI_UI_FONT;
	ap->scale[ X ] = 0.5f;
	ap->scale[ Y ] = ap->scale[ X ];

	ap = TASK_start_DRAWFUNC( result_hi_score_exec, result_hi_score_drawfunc, GROUP_UI, "ハイスコア数字の表示" );
	ap->pos[ X ] = 900.0f;
	ap->pos[ Y ] = 600.0f;
	ap->pri = PRI_UI_FONT;
	ap->scale[ X ] = 0.5f;
	ap->scale[ Y ] = ap->scale[ X ];
}

//-----------------------------------------------------------------------------------------------
// リザルト画面:スコアの表示
//-----------------------------------------------------------------------------------------------
void result_score_exec( TASK *ap )
{}
void result_score_drawfunc( TASK *ap )
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
			spr.anime_no = str[ i ] - '0';
		else
			spr.anime_no = 0;

		SOZ_sprite_draw( &spr );	// 描画の実行
		spr.pos[ X ] += 55.0f;
	}

}
void result_score_disp( void )
{
	TASK *ap;
	ap = TASK_start_GRP( result_score_exec, GROUP_UI, TEXTURE_UI_FONT, ui_font_rect, 8, "SCOREのフォントを表示" );
	ap->pos[ X ] = 640.0f;
	ap->pos[ Y ] = 500.0f;
	ap->pri = PRI_UI_FONT;
	ap->scale[ X ] = 0.6f;
	ap->scale[ Y ] = ap->scale[ X ];

	ap = TASK_start_DRAWFUNC( result_score_exec, result_score_drawfunc, GROUP_UI, "スコア数字の表示" );
	ap->pos[ X ] = 850.0f;
	ap->pos[ Y ] = 500.0f;
	ap->pri = PRI_UI_FONT;
	ap->scale[ X ] = 0.6f;
	ap->scale[ Y ] = ap->scale[ X ];
}

//-----------------------------------------------------------------------------------------------
// リザルト画面:[ RECULT ] の表示
//-----------------------------------------------------------------------------------------------
void result_disp_exec( TASK *ap )
{
}
void result_disp( void )
{
	TASK *ap;
	ap = TASK_start_GRP( result_disp_exec, GROUP_UI, TEXTURE_UI_FONT_2, ui_font_rect, 11, "RESULT の表示" );
	ap->pos[ X ] = WINDOW_WIDTH / 2;//400.0f;
	ap->pos[ Y ] = 250.0f;
	ap->pri = PRI_UI_FONT;

	result_stage_disp();	// リザルト画面のSTAGEの表示
	result_score_disp();	// リザルト画面のSCORE表示
	result_hi_score_disp();	// リザルト画面のHI-SCORE表示
}


