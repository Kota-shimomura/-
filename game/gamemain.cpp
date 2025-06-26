//------------------------------------------------------------------------------------------------------------------------------------------------------
//                systemOZ Ver4
//							ゲームメインプログラム
//														programed by Shimomura Kota
//------------------------------------------------------------------------------------------------------------------------------------------------------
#ifdef WINDOWS_PC
#include    "C:/project/libs/systemOZ_v4/soz.h"
#else
#include    "D:/project/guardians_2dx/proj.win32/src/systemOZ/soz.h"
#endif

#include    "C:/project/panzer/src/game/game_include.h"


//------------------------------------------------------------------------------------------------------------------------------------------------------
//外部変数定義
//------------------------------------------------------------------------------------------------------------------------------------------------------
SINT32	platform_PC = 1;
SINT32	game_type = 0, game_type2 = 0, game_type3 = 0, game_mode = 0, game_type_old = 0;	//ゲームの進行度

#if 0
//----------------------------------------------------------------------------------
// メモリの管理
//----------------------------------------------------------------------------------
typedef struct
{
	int x, y;
	char name[ 100 ];
	float height, waight;
} HUMAN;

int main( void )
{
	HUMAN *m, *hum;
	//メモリを確保
	m = (HUMAN * )calloc( 10000, sizeof( HUMAN ) );
//	m = (HUMAN * )malloc( 10000 * sizeof( HUMAN ) );

	//メモリの使用
	hum = m;					//0人目を指す
	hum += 100;					//100人目を指す
	hum->height = 182.5f;		//100人目の身長を変更

	//メモリの開放
	free( m );
}
#endif



//------------------------------------------------------------------------------------------------------------------------------------------------------
//   メインルーチン (1/60秒に　1回呼び出される)	※注釈をつけてください
//------------------------------------------------------------------------------------------------------------------------------------------------------
void GAMEMAIN_Routine( void )
{
	switch( game_type )
	{
		case GT_LOAD:	//読み込み
			hi_score_rank_read();
			load_set();
			INKEY_keyconfig_data_load();	//キーコンフィグのデータをロード
			bg_color_r = 0x00;
			bg_color_g = 0x00;
			bg_color_b = 0x00;
			MAP_DATA_LOAD
			game_type++;
			break;

		case GT_GAME_TYPE_SERECT:	//それぞれデバッグ用シーン移動
//			game_type = GT_TEAM;
			game_type = GT_STAFF_ROLL;
			break;

		case GT_TEAM:	//チーム名表示
			team_name_disp();
			game_type++;
			break;

		case GT_TITLE:	//タイトル画面
			SOZ_Music_Stop( 0 );
			SOZ_Music_Load( 0, "grp/BGM/panzer_menu_BGM", 1 );
			title_set();
			game_type++;
			break;

		case GT_MENU:	//操作説明
			navigation_set();
			game_type++;
			break;

		case GT_SCORE:	//スコア画面
			record_set();
			game_type++;
			break;

		case GT_KEYCON:	//キーコンフィグ
			if( INKEY_keyconfig() < 0 )
			{
				INKEY_keyconfig_data_save();
				game_type = GT_TITLE;
			}
			break;

		case GT_GAME_MODE:	//ゲーム画面
//			enemy_read_the_file();
			enemy_setting( ENEMY_SET_DISP, 8, 11 );	//敵のデータの読み込み
			map_read_the_file();
			map_setting(MAP_DISP, 18, 11 );		//マップチップ
			scr_x = GAME_MAP_SIZE_X/2;
			scr_y = GAME_MAP_SIZE_Y/2;
			jiki_start();			//自機
			hp_ui();
			score_disp();			//スコア
			hi_score_disp();		//ハイスコア
			SOZ_Music_Stop( 0 );
			SOZ_Music_Load( 0, "grp/BGM/panzer_BGM", 1 );
			game_type++;
			break;

		case 101:
			countdown_start();
			game_type++;
				break;

		case 102:
			game_type++;
			break;



		case GT_GAME_OVER:		//ゲームオーバー画面
			disp_rizaruto( GAME_OVER );
			hi_score_reload();					//ハイスコアの更新
			map_setting( MAP_DISP, 34, 19 );	//マップチップ
			game_type++;
			break;

		case GT_GAME_CLEAR:
			disp_rizaruto( GAME_CLEAR );
			hi_score_reload();					//ハイスコアの更新
			map_setting( MAP_DISP, 34, 19 );	//マップチップ
			game_type++;
			break;

		case GT_STAFF_ROLL:						// エンドロール/スタッフロール
			TASK_all_init();
			staff_roll_seqence();
			game_type++;
			break;


		case TEST_GT_MAP_EDIT:		//マップエディタ
			scr_x = GAME_MAP_SIZE_X / 2;
			scr_y = GAME_MAP_SIZE_Y / 2;
#if 0
			map_setting( MAP_ALL_0, 7, 9 );
#else
			map_setting( MAP_DISP, 9, 10 );
#endif
			map_edit();
			game_type++;
			break;

		case TEST_GT_ENEMY_SET:		//敵配置
			jiki_start();			//自機
			game_type++;
			break;

		case TEST_GT_SYSTEM:
			map_setting( MAP_DISP, 34, 19 );
			scr_tester();
			game_type++;
			break;

		case TEST_GT_ENEMY_MAP:	//敵のマップ配置
#if 0
			enemy_setting( ENEMY_ALL_NULL, 8, 11 );
#else
			enemy_setting( ENEMY_SET_DISP, 8, 11 );
#endif
			jiki_start();
			enemy_data_list();
			enemy_map_set_mouse();
			//scr_x = 0;
			//scr_y = 0;
			scr_x = GAME_MAP_SIZE_X / 2;
			scr_y = GAME_MAP_SIZE_Y / 2;
			game_type++;
			break;

		case TEST_GT_ENEMY_MAP+1:
			if( SOZ_Inkey_TRG( DIK_Q ) )
			{
				game_type = GT_GAME_TYPE_SERECT;
				TASK_all_init();
			}

			if( SOZ_Inkey_TRG( DIK_G ) )
			{
				game_type = GT_GAME_MODE;
				TASK_all_init();
			}
			break;

		case TEST_MODE:
			scr_x = GAME_MAP_SIZE_X / 2;
			scr_y = GAME_MAP_SIZE_Y / 2;
			map_read_the_file();
			jiki_start();
			map_setting( MAP_DISP, 18, 11 );		//マップチップ
			game_type++;
			break;

		case TEST_MODE + 1:
			break;
	}

	game_type_old = game_type;
}