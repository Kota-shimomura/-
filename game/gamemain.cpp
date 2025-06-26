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

#include    "C:/project/bace/src/game/game_include.h"

//------------------------------------------------------------------------------------------------------------------------------------------------------
//外部変数定義
//------------------------------------------------------------------------------------------------------------------------------------------------------
SINT32	platform_PC = 1;
SINT32	game_type = 0, game_type2 = 0, game_type3 = 0, game_mode = 0, game_type_old = 0;	//ゲームの進行度


//------------------------------------------------------------------------------------------------------------------------------------------------------
//　修正点
//------------------------------------------------------------------------------------------------------------------------------------------------------
// 敵の見た目を合計８種類にする														!?
// 特定の動きの速度を遅くしてやられ役を作る											!!
// タイトル画面、ランキング画面、オプション画面の背景を自機がいる基地に設定する		!!
// プレイヤーを驚かせる演出を加える
// ボス感が薄い
// ボスの登場時に、名前などを表示する
// ミサイルにロックオンを追加して発射表記をし、使用を促す。							!!
// 敵に隊列を組ませる																!!
// 上下左右のリバース設定をできるようにする。
// 
// バルカンに射程を設定する
// バルカンの打ち方を調整
// ミサイルの所持最大を30にする
// 敵がミサイルアイテムを落とす？-> 敵をミサイルで倒すか
// 
//------------------------------------------------------------------------------------------------------------------------------------------------------

//-----------------------------
// Ver 2.0表記
//-----------------------------
void ver_disp_exec( TASK *ap )
{}
void ver_disp( void )
{
	TASK *ap;
	ap = TASK_start_FONT( ver_disp_exec, GROUP_UI, "Ver 2.06.13", 2 );
	ap->pos[ X ] = WINDOW_WIDTH - 200.0f;
	ap->pos[ Y ] = WINDOW_HEIGHT - 50.0f;
	ap->pri = PRI_UI + 1000;
}

//------------------------------------------------------------------------------------------------------------------------------------------------------
//   メインルーチン (1/60秒に　1回呼び出される)	※注釈をつけてください
//------------------------------------------------------------------------------------------------------------------------------------------------------
void GAMEMAIN_Routine( void )
{
	switch( game_type )
	{
		case 0:	// データの読み込み
			hi_score_all_clear();																// ハイスコアの配列初期化
			data_set();
			play_load();				// プレイ用のデータを読み込む
			bg_color_r = 0x11;	// 背景色の設定
			bg_color_g = 0x11;	// 背景色の設定
			bg_color_b = 0x11;	// 背景色の設定
			demo_mode = 0;
			game_type = TYPE_TITLE;
			break;

		case TYPE_CONFIG:	//キーコンフィグ画面
			if (INKEY_keyconfig() < 0 )
			{
				INKEY_keyconfig_data_save();	//設定したキーコンフィグデータのセーブ
				game_type = TYPE_TITLE;		//タイトル画面に行く
			}
			break;
///------- タイトル ------------------
		case TYPE_TITLE:
			if( demo_mode != 0 )
				fade( -5, 0 );
			SOZ_Music_Stop( 0 );		// BGMを止める
			SOZ_Music_Load( 0, "grp/shooting/bgm/bace_menu", 1 );	// BGMの再生
			ver_disp();
#ifdef DEBUG
//			game_type = TYPE_END;			// エンドロール確認
			game_type = TYPE_GAME;			// ゲーム画面確認
//			game_type = TYPE_DEMO;			// デモプレイ確認
//			game_type = TYPE_NEW_DATA;
			play_load();					// デバッグ時の読み込み
			//title_disp();
			//SOZ_camera( 0, 0, 0, 4000, 0x0000, 0x0000, 0x0000, 0 );								// カメラの座標と角度設定
			//SOZ_set_light_pos(  41300.0f, 7800.0f, 15300.0f, -3500.0f, -47200.0f, -22000.0f );	// ライトの設定
			//bg_base_jiki();
			//game_type++;
#else
			title_disp();
//			SOZ_camera( 0, 0, 50, 2000, 0x0000, 0x0000, 0x0000, 0 );								// カメラの座標と角度設定
			SOZ_camera( 0, 0, 50, -1000, 0x0000, 0x0000, 0x0000, 0 );								// カメラの座標と角度設定
			SOZ_set_light_pos(  41300.0f, 7800.0f, 15300.0f, -3500.0f, -47200.0f, -22000.0f );	// ライトの設定
			bg_base_jiki();
			game_type++;
#endif
			break;

		case TYPE_TITLE +1:
			if( SOZ_Inkey_TRG( DIK_F1 ) )		// 特定のキーを押したらコントローラーのキーコンフィグ画面に飛ぶ
			{
				TASK_all_init();
				game_type = TYPE_CONFIG;
			}
			break;

///------- メニュー ------------------
		case TYPE_MENU:
//			play_release();
			SOZ_camera( 0, 0, 50, -1000, 0x0000, 0x0000, 0x0000, 0 );								// カメラの座標と角度設定
			option_save_data( LOAD_MODE );							// 設定のデータを読み込む
			SOZ_Music_Load( 0, "grp/shooting/bgm/bace_menu", 1 );	// BGMの再生
			key_disp( WINDOW_WIDTH /2, WINDOW_HEIGHT -50.0f );
			bg_base_jiki();
			hi_score_data( LOAD_MODE );															// ハイスコアのデータよみこみ
			menu_disp();																		// メニュー表示
			game_type++;
			break;

		case TYPE_MENU +1:
			SOZ_locate_print( 10, 3, "[STICK_DATA]:%04d", stick_data );
			if( SOZ_Inkey_TRG( DIK_F1 ) )		// 特定のキーを押したらコントローラーのキーコンフィグ画面に飛ぶ
			{
				TASK_all_init();
				game_type = TYPE_CONFIG;
			}
			break;

///------- オプション画面 ----------------
		case TYPE_OPTION:
			TASK_all_init();
			key_disp( WINDOW_WIDTH /2, WINDOW_HEIGHT -50.0f );
			bg_base_jiki();
			ui_cont_disp( WINDOW_WIDTH / 2 + 50.0f, WINDOW_HEIGHT /2 + 250.0f, 0.8f );
			mini_logo_disp();		// 左上の小さいロゴを表示
			opration_setting_system( 70.0f );					// オプション設定タスク
			game_type++;
			break;

		case TYPE_OPTION +1:
			if( SOZ_Inkey_TRG( DIK_X ) || SOZ_Inpad_TRG( 0, PADDIK_CANCEL ) )			// 戻るボタンが押されたらメニュー画面に戻る
			{
				game_type = TYPE_MENU;
				TASK_all_init();
				bg_base_jiki();
				return;
			}
			break;

///------- ランキング画面 ----------------
		case TYPE_RANKING:
			TASK_all_init();
			bg_base_jiki();
			ranking_disp();
			back_disp( WINDOW_WIDTH - 300.0f, WINDOW_HEIGHT -50.0f );
			mini_logo_disp();		// 左上の小さいロゴを表示
			game_type++;
			break;
///------- ゲーム画面 ----------------
		case TYPE_GAME:
			SOZ_Music_Stop( 0 );
			TASK_all_init();
			score = 0;
			SOZ_camera( 0, 0, 0, 100, 0x0000, 0x0000, 0x0000, 0 );
//			SOZ_camera( 0, 0, 0, 4000, 0x0000, 0x0000, 0x0000, 0 );
			SOZ_set_light_pos(  41300.0f, 7800.0f, 15300.0f, -3500.0f, -47200.0f, -22000.0f );
			atack_cont_disp();										// 攻撃操作方法の表示
			score_disp();											// スコアの表示
			hi_score_disp();										// ハイスコアの表示
			stage_disp();											// ステージの表示
			life_disp();											// 残機の表示
			missile_num_disp();										// ミサイル残弾数の表示
			my_ship();												// 自機の表示
			universe_gen();											// 地面の表示
//#ifdef MASTER
			enemy_seq();											// 敵シーケンスの起動
//#endif
			engage_disp();											// ENGAGE の表示
			play_data_get();	// 操作の保存
			SOZ_Music_Load( 0, "grp/shooting/bgm/bace_bgm", 1 );	// BGMの再生

			// 惑星発生
			game_type++;
			break;

///------- クリア画面 ---------------
		case TYPE_CLEAR:
			SOZ_Music_Stop( 0 );		// BGMを止める
//			TASK_end_group( GROUP_ENEMY );	// 敵をすべて消す
			game_clear_disp();
			game_type++;
			break;

		case TYPE_CLEAR + 2:
			TASK_end_group( GROUP_UI );
			result_disp();
			result_button_set( 1 );
			hi_score_data( SAVE_MODE );		// ハイスコアのデータ書き込み
			game_type++;
			break;

///------- ゲームオーバー画面 -------
		case TYPE_OVER:
			SOZ_Music_Stop( 0 );		// BGMを止める
			game_over_disp();
			game_type++;
			break;
		case TYPE_OVER + 2:
			TASK_end_group( GROUP_UI );
			result_disp();
			result_button_set( 0 );
			hi_score_data( SAVE_MODE );		// ハイスコアのデータ書き込み
			game_type++;
			break;

///------- エンドロール ------------------
		case TYPE_END:
			SOZ_Music_Stop( 0 );		// BGMを止める
			SOZ_Music_Load( 0, "grp/shooting/bgm/ending", 0 );	// BGMの再生
			end_roll();
			game_type++;
			break;


///------- 初めてプレイ ------------------
		case TYPE_NEW_DATA:
			new_data_font();
			key_disp( WINDOW_WIDTH /2, WINDOW_HEIGHT -50.0f );
			ui_cont_disp( WINDOW_WIDTH - 310.0f, WINDOW_HEIGHT - 200.0f, 0.3f );
			opration_setting_system( 400.0f );					// オプション設定タスク
			game_type++;
			break;

		case TYPE_NEW_DATA + 1:
			button_data_get();
			SOZ_locate_print( 10, 3, "[STICK_DATA]:%04d", stick_data );
			//SOZ_locate_print( 10, 3, "[button_lr]:%04d", button_lr );
			//SOZ_locate_print( 10, 4, "[button_ud]:%04d", button_ud );
			if( SOZ_Inkey_TRG( DIK_F1 ) )		// 特定のキーを押したらコントローラーのキーコンフィグ画面に飛ぶ
			{
				TASK_all_init();
				game_type = TYPE_NEW_DATA + 5;
			}
			break;

		case TYPE_NEW_DATA + 5:
			if (INKEY_keyconfig() < 0 )
			{
				INKEY_keyconfig_data_save();	//設定したキーコンフィグデータのセーブ
				game_type = TYPE_NEW_DATA;		//元の画面に戻る
				bg_base_jiki();
			}
			break;

// デモプレイ
		case TYPE_DEMO:
			score = 0;
			SOZ_Music_Stop( 0 );		// BGMを止める
			fade( -5, 0 );
			SOZ_camera( 0, 0, 0, 100, 0x0000, 0x0000, 0x0000, 0 );
//			SOZ_camera( 0, 0, 0, 4000, 0x0000, 0x0000, 0x0000, 0 );
			SOZ_set_light_pos(  41300.0f, 7800.0f, 15300.0f, -3500.0f, -47200.0f, -22000.0f );
			replay_option_save_data( LOAD_MODE );					// リプレイ時の設定読み込み
			atack_cont_disp();										// 攻撃操作方法の表示
			stage_disp();											// ステージの表示
			life_disp();											// 残機の表示
			missile_num_disp();										// ミサイル残弾数の表示
			my_ship();												// 自機の表示
			universe_gen();											// 地面の表示
			enemy_seq();											// 敵シーケンスの起動
			engage_disp();											// ENGAGE の表示
			SOZ_Music_Load( 0, "grp/shooting/bgm/bace_bgm", 1 );	// BGMの再生
			mini_logo_disp();		// 左上の小さいロゴを表示
			demo_play();
			demo_play_disp();
			game_type++;
			break;
	}

	game_type_old = game_type;
}