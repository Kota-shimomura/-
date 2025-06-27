#ifdef WINDOWS_PC
#include    "C:/project/libs/systemOZ_v4/soz.h"
#else
#include    "D:/project/guardians_2dx/proj.win32/src/systemOZ/soz.h"
#endif

#include    "C:/project/bace/src/game/game_include.h"

SINT64 tutorial_flag = 0;		// チュートリアルの進行度の保存・もう一度受ける場合は、操作説明の部分のみ初期化
SINT32 selecter = 0;			// セレクター

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
// 背景 基地と戦闘機( STARTを押したら飛ぶ )
//------------------------------------------------------------------------------------------------------------------------------------------------------
void menu_base_exec( TASK *ap )
{
	// ここでは特に何もしない
}
void menu_base( void )
{
	TASK *ap;
	ap = TASK_start_MODEL( menu_base_exec, GROUP_BG, MODEL_BASE, TEXTURE_BASE, "基地3Dモデル" );
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
	if ( game_type == TYPE_MENU +1 )		// メニュー画面の時のみ表示
	{
// ゲームスタートが選択されていて、決定ボタンが押された時
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

		if( ap->vec[ Z ] > 0 )				// ベクトルが特定の値を超えたら、アフターバーナーの表示を始める
		{
			jiki_burner_effect( ap, 50 );
			jiki_burner_effect( ap, -50 );
		}
		SOZ_camera_move( 0 );

		if( ap->pos[ Z ] > 8000.0f )		// 特定座標を超えたらゲーム画面に移動
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
	ap = TASK_start_MODEL( menu_jiki_exec, GROUP_MY_SHIP, MODEL_MY_SHIP, TEXTURE_MY_SHIP, "自機3Dモデル" );
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
// miniロゴ表示
//------------------------------------------------------------------------------------------------------------------------------------------------------
void mini_logo_disp_exec( TASK *ap )
{
	// 何もしない
}
void mini_logo_disp( void )
{
	TASK *ap;
	ap = TASK_start_GRP( mini_logo_disp_exec, GROUP_UI, TEXTURE_LOGO, ui_font_rect, 0, "小さいロゴ" );
	ap->pos[ X ] = 200.0f;
	ap->pos[ Y ] = 200.0f;
	ap->scale[ X ] = 0.4f;
	ap->scale[ Y ] = ap->scale[ X ];
	ap->pri = PRI_UI_FONT + 5000 *WP;
}


//------------------------------------------------------------------------------------------------------------------------------------------------------
// セレクター
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
			// セレクターを上に動かす
			if( SOZ_Inkey_TRG( DIK_UP ) || SOZ_Inpad_TRG( 0, PADDIK_UP ) )
			{
				SOZ_play_se( SE_SERECT, 2.0f, 1, 1.0f );
				selecter--;
				if( selecter < 0 )
					selecter = 2;
			}
			// セレクターを下に動かす
			if( SOZ_Inkey_TRG( DIK_DOWN ) || SOZ_Inpad_TRG( 0, PADDIK_DOWN ) )
			{
				SOZ_play_se( SE_SERECT, 2.0f, 1, 1.0f );
				selecter++;
				if( selecter > 2 )
					selecter = 0;
			}
		}
		SOZ_locate_print( 1, 1, "[selecter] %d ", selecter );
	// 座標の更新
		ap->pos[ Y ] = FLOAT( WINDOW_HEIGHT / 2.6f + 10.0f + ( WINDOW_HEIGHT/7 ) * selecter );
	}
}
void menu_selecter( void )
{
	TASK *line, *ap;
	line = TASK_start_GRP( menu_selecter_line, GROUP_UI, TEXTURE_UI_FONT, ui_selecter_rect, 0, "セレクターのライン部分" );
	line->pri = PRI_UI_FONT;
	line->pos[ X ] = WINDOW_WIDTH /2;
	line->work1[ X ] = 0;
	line->work1[ Y ] = 0;

	ap = TASK_start_GRP( menu_selecter_line, GROUP_UI, TEXTURE_UI_FONT, ui_selecter_rect, 1, "セレクターのライン部分" );
	ap->pos[ X ] = WINDOW_WIDTH /2 - 350;
	ap->pri = PRI_UI_FONT+1;
	ap->work1[ X ] = 1;
	ap->work1[ Y ] = 0;
}

//------------------------------------------------------------------------------------------------------------------------------------------------------
// start/custom/ranking表示
//------------------------------------------------------------------------------------------------------------------------------------------------------
void menu_ui_disp_exec( TASK *ap )
{
	ap->work2[ X ] ++;
	SOZ_locate_print(20, 3, "%d", selecter );
	if( ap->work1[ Z ] == selecter )	// セレクターが合っているとき
	{
		ap->base_color[ 0 ][ 0 ] = 0xff;
		ap->base_color[ 0 ][ 1 ] = 0xff;
		ap->base_color[ 0 ][ 2 ] = 0xff;
		ap->base_color[ 0 ][ 3 ] = 0xff;
		if( ap->work2[ X ] % 40 == 0 )	// 10fごとに大きくなるタスクを発生させる
			bic_illusion_start( ap, 10, BLEND_ADD );
		if( SOZ_Inkey_TRG( DIK_Z ) || SOZ_Inpad_TRG( 0, PADDIK_DECIDE ) )			// 決定ボタンが押された時
		{
			if( menu_ui[ selecter ].chenge_game_type != TYPE_GAME )
				game_type = menu_ui[ selecter ].chenge_game_type;					// game_type を変える
		}		
	}
	else
	{
		ap->base_color[ 0 ][ 0 ] = 0x88;
		ap->base_color[ 0 ][ 1 ] = 0x88;
		ap->base_color[ 0 ][ 2 ] = 0x88;
		ap->base_color[ 0 ][ 3 ] = 0x88;
	}

//	ロックされているときはグレーで半透明にする
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

	ap->work1[ X ] = ui->lock_flag_id;		// 選択に必要なフラグを保存
	ap->work1[ Y ] = ui->chenge_game_type;	// 選択された時に変更するgame_typeを保存
	ap->work1[ Z ] = id;
	ap->work2[ X ] = 0;						// 残像表示頻度の計算用
}
void menu_ui_set( void )
{
	SINT32 disp_num;
	for( disp_num = 0; disp_num < 3; disp_num++ )
		menu_ui_disp( disp_num, &menu_ui[ disp_num ] );
}

//------------------------------------------------------------------------------------------------------------------------------------------------------
// MENU表示
//------------------------------------------------------------------------------------------------------------------------------------------------------
void menu_disp_exec( TASK *ap )
{
	if( ap->work1[ X ] == 0 )
	{
		ap->work1[ Y ]++;
		if( SOZ_Inkey_TRG( DIK_Z ) || SOZ_Inpad_TRG( 0, PADDIK_DECIDE ) )		// 決定ボタンが押されたら
		{
			ap->work1[ X ] = 1;
			SOZ_play_se( SE_DECISION, 3.0f, 1, 0.0f );							// 決定の効果音を鳴らす
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
		if( ap->work1[ Y ] > 60 * 60 * 10 )		// 特定時間経過したらタイトル画面に戻る
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

	mini_logo_disp();		// 左上の小さいロゴを表示
	menu_ui_set();			// メニューの選択肢を表示
	menu_selecter();		// メニュー画面のセレクター
//	menu_jiki();			// 背景用の自機を表示
//	menu_base();			// 背景用の基地を表示
}

void bg_base_jiki( void )
{
	menu_jiki();			// 背景用の自機を表示
	menu_base();			// 背景用の基地を表示
}
