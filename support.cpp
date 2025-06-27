
#ifdef WINDOWS_PC
#include    "C:/project/libs/systemOZ_v4/soz.h"
#else
#include    "D:/project/guardians_2dx/proj.win32/src/systemOZ/soz.h"
#endif

#include    "C:/project/bace/src/game/game_include.h"
//------------------------------------------------------------------------------------------------------------------------------------------------------
// 補助関数
//------------------------------------------------------------------------------------------------------------------------------------------------------
//	デモプレイでも使用します。
SINT32 button_lr = 0;
SINT32 button_ud = 0;
SINT32 attack_button = 0;
SINT32 demo_mode = OFF;


DEMO_DATA demo_data[ DEMO_DATA_SIZE ];



//-----------------------------------------------------------------------------
// リプレイのデータを構造体に保存する
//-----------------------------------------------------------------------------
void play_data_get_exec( TASK *ap )
{
	ap->work1[ X ]++;
	ap->work2[ X ] = 0;
// 移動を書き込む
	demo_data[ ap->work1[ X ] ].stick_lr = button_lr;
	demo_data[ ap->work1[ X ] ].stick_ud = button_ud;

// 攻撃入力を書き込む
	if( SOZ_Inkey_DAT( DIK_Z ) || SOZ_Inpad_DAT( 0, PADDIK_MAIN_ATTACK ) )
		orFLG( ap->work2[ X ], DEMO_SHOT );
	if( SOZ_Inkey_TRG( DIK_X ) || SOZ_Inpad_TRG( 0, PADDIK_SUB_MISSILE ) )
		orFLG( ap->work2[ X ], DEMO_MISSILE );
	demo_data[ ap->work1[ X ] ].attack = ap->work2[ X ];

// 指定条件でデータをファイルに保存してタスクエンド
	if( game_type == TYPE_CLEAR || game_type == TYPE_OVER || ap->work1[ X ] > DEMO_DATA_SIZE -1 )
	{
		replay_option_save_data( SAVE_MODE );					// リプレイ時の設定を保存
		replay_save_data( SAVE_MODE );	// 保存する
		TASK_end( ap );
		return;
	}
}
void play_data_get( void )
{
	TASK *ap;
	ap = TASK_start( play_data_get_exec, GROUP_UI, "構造体に操作を保存" );
	ap->work1[ X ] = 0;
	ap->work2[ X ] = 0;	// 攻撃入力のフラグ取得
// データを初期化する
	for( SINT32 i = 0; i < DEMO_DATA_SIZE; i++ )
	{
		demo_data[ i ].stick_lr = -9999;
		demo_data[ i ].stick_ud = -9999;
		demo_data[ i ].attack = 0;
	}
}

//-----------------------------------------------------------------------------
// デモプレイ操作
//-----------------------------------------------------------------------------
void demo_play_exec( TASK *ap )
{
	button_lr = 0;
	button_ud = 0;

// ボタンの入力データを取得	デモプレイに反映
	button_lr = demo_data[ ap->work1[ X ] ].stick_lr;
	button_ud = demo_data[ ap->work1[ X ] ].stick_ud;
	attack_button = demo_data[ ap->work1[ X ] ].attack;
	ap->work1[ X ]++;

// ライフが０になるか特定時間が経過した時、タイトル画面に戻す
	if( demo_data[ ap->work1[ X ] + 2 ].stick_lr == -9999 || SOZ_Inpad_TRG( 0, PADDIK_CANCEL )|| SOZ_Inkey_TRG( DIK_X ) || SOZ_Inpad_TRG( 0, PADDIK_DECIDE )|| SOZ_Inkey_TRG( DIK_Z ) || ap->work1[ X ] >= 60 * 60 * 2  || life <= 0 )
	{
		fade( 5, TYPE_TITLE );
		TASK_end( ap );
		return;
	}

// デバッグ表記
	SOZ_locate_print ( 30, 10, "LR:%d", button_lr );
	SOZ_locate_print ( 30, 11, "UD:%d", button_ud );
	SOZ_locate_print ( 30, 13, "mode:%d", demo_mode );
	SOZ_locate_print ( 30, 14, "flag:%d", stick_data );
}
void demo_play( void )
{
	TASK *ap;
	ap = TASK_start( demo_play_exec, GROUP_UI, "オート操作" );
	replay_save_data( LOAD_MODE );
	ap->work1[ X ] = 1;
	demo_mode = 1;
}


//-----------------------------------------------------------------------------
// 自機操作のコントローラー上下左右の入力取得
//-----------------------------------------------------------------------------
void button_data_get( void )
{
	button_ud = 0;
	button_lr = 0;
	if( ( stick_data & STICK_ANALOG ) != 0 )		// アナログスティックを使用する
	{
		if( j_state->lY < -200 || j_state->lY > 200 || button_ud < -200 || button_ud > 200 )
		{
			if( demo_mode == 0 )
				button_ud = j_state->lY;
			if( ( stick_data & STICK_UD ) != 0 )		// 上下反転
				button_ud *= -1;
		}
		if( j_state->lX < -200 || j_state->lX > 200 || button_lr < -200 || button_lr > 200 )
		{
			if( demo_mode == 0 )
				button_lr = j_state->lX;
			if( ( stick_data & STICK_LR ) != 0 )		// 左右反転
				button_lr *= -1;
		}
	}
	else											// アナログスティックを使用しない
	{
		if( SOZ_Inkey_DAT( DIK_UP ) || SOZ_Inpad_DAT( 0, PADDIK_UP ) )	// 上が入力された時
		{
//			button_ud = -1000;
			button_ud = -( SOZ_Inkey_DAT( DIK_UP ) + SOZ_Inpad_DAT( 0, PADDIK_UP ) );
			if( ( stick_data & STICK_UD ) != 0 )	// 上下が反転されている
				button_ud *= -1;
		}
		if( SOZ_Inkey_DAT( DIK_DOWN ) || SOZ_Inpad_DAT( 0, PADDIK_DOWN ) )	// 下が入力された時
		{
//			button_ud = 1000;
			button_ud = SOZ_Inkey_DAT( DIK_DOWN ) + SOZ_Inpad_DAT( 0, PADDIK_DOWN );
			if( ( stick_data & STICK_UD ) != 0 )	// LRが反転されている
				button_ud *= -1;
		}

		if( SOZ_Inkey_DAT( DIK_LEFT ) || SOZ_Inpad_DAT( 0, PADDIK_LEFT ) )	// 左が入力された時
		{
//			button_lr = -1000;
			button_lr = -( SOZ_Inkey_DAT( DIK_LEFT ) + SOZ_Inpad_DAT( 0, PADDIK_LEFT ) );
			if( ( stick_data & STICK_LR ) != 0 )	// LRが反転されている
				button_lr *= -1;
		}
		if( SOZ_Inkey_DAT( DIK_RIGHT ) || SOZ_Inpad_DAT( 0, PADDIK_RIGHT ) )	// 右が入力された時
		{
//			button_lr = 1000;
			button_lr = SOZ_Inkey_DAT( DIK_RIGHT ) + SOZ_Inpad_DAT( 0, PADDIK_RIGHT );
			if( ( stick_data & STICK_LR ) != 0 )	// LRが反転されている
				button_lr *= -1;
		}
	}
}

//-----------------------------------------------------------------------------
// 白いフェードイン / フェードアウト
//-----------------------------------------------------------------------------
void fade_exec( TASK *ap )
{
	ap->work2[ X ] ++;
	if( ap->work2[ X ] % 2 == 0 )
		ap->base_color[ 0 ][ 0 ] += ap->work1[ X ];
	if( ap->work1[ X ] > 0 )
	{
		if( ap->base_color[ 0 ][ 0 ] > 250 )
		{
			game_type = ap->work1[ Y ];
			TASK_all_init();
			return;
		}
	}
	else
	{
		if( ap->base_color[ 0 ][ 0 ] < 10 )
		{
			TASK_end( ap );
			return;
		}
	}
}
void fade( SINT32 fade_mode, SINT32 chenge_type )
{
	TASK *ap;
	ap = TASK_start_GRP( fade_exec, GROUP_UI, TEXTURE_EFFECT, fade_rect, 0, "フェードエフェクト" );
	ap->pos[ X ] = WINDOW_WIDTH /2;
	ap->pos[ Y ] = WINDOW_HEIGHT /2;
	ap->pri = PRI_UI + 10000 *WP;
	ap->scale[ Y ] = ap->scale[ X ] = 100.0f;
	ap->work1[ X ] = fade_mode;
	ap->work1[ Y ] = chenge_type;
	ap->work2[ X ] = 0;
	ap->base_color[ 0 ][ 0 ] = 0x00;
	if( fade_mode < 0 )
		ap->base_color[ 0 ][ 0 ] = 0xff;
}


//-----------------------------------------------------------------------------
// ２Dグラフィックがカメラを向くように
//-----------------------------------------------------------------------------
void grp_look_camer( TASK *ap )
{
	ap->ang[ X ] = SOZ_atan2( ap->pos[ Z ], ap->pos[ Y ], camera_z[ 0 ], camera_y[ 0 ] );
	ap->ang[ X ] = SOZ_atan2( ap->pos[ Z ], ap->pos[ Y ], camera_z[ 0 ], camera_y[ 0 ] );
}

//-----------------------------------------------------------------------------
// ターゲット移動ベクトル設定 初期化
//-----------------------------------------------------------------------------
void target_lock_vec( TASK *ap, TASK *actp )
{
	ANGLE ans_x, ans_y; //,ans_z;
// 目標との座標をみて、角度を算出する。
	ans_x = SOZ_atan2( ap->pos[ Z ], ap->pos[ Y ], actp->pos[ Z ], actp->pos[ Y ] );
	ans_y = SOZ_atan2( ap->pos[ Z ], ap->pos[ X ], actp->pos[ Z ], actp->pos[ X ] );
	ap->ang[ X ] = ans_x;
	ap->ang[ Y ] = -ans_y;
	// 角度に合わせて進めるようにベクトルを算出する。
	ap->vec[ X ] = SOZ_get_sin( -ap->ang[ Y ] ) *ap->work2[ D ];
	ap->vec[ Y ] = SOZ_get_sin( ap->ang[ X ] ) *ap->work2[ D ];
	ap->vec[ Z ] = ( SOZ_get_cos( ap->ang[ X ] ) *ap->work2[ D ] + SOZ_get_cos( ap->ang[ Y ] ) *ap->work2[ D ] ) /2;

}

void target_look( TASK *ap, TASK *actp )	// 注意！！　何かしらの変数に代入する
{
	ANGLE ans_x, ans_y, ans_z;
// 目標との座標をみて、角度を算出する。
	ans_x = SOZ_atan2( ap->pos[ Z ], ap->pos[ Y ], actp->pos[ Z ], actp->pos[ Y ] );
	ans_y = SOZ_atan2( ap->pos[ Z ], ap->pos[ X ], actp->pos[ Z ], actp->pos[ X ] );
	ans_z = SOZ_atan2( ap->pos[ X ], ap->pos[ Y ], actp->pos[ X ], actp->pos[ Y ] );
// 今の角度と本来向きたい角度をいれる	ansの中に左右どっちの方向にずれているか( プラスかマイナスか )
 	ans_x = SOZ_angle_diff( ap->ang[ X ], ans_x );
 	ans_y = SOZ_angle_diff( ap->ang[ Y ], ans_y );
 	ans_z = SOZ_angle_diff( ap->ang[ Z ], ans_z );
	switch ( SOZ_sgn( ans_x ) )	//数値の単位化　単位化すると 1 から -1 の整数の数値になる
	{
		case 1:
			ap->ang[ X ] -= 0x45;
			break;

		case -1:
			ap->ang[ X ] += 0x45;
			break;
	} 
	switch ( SOZ_sgn( ans_y ) )	//数値の単位化　単位化すると 1 から -1 の整数の数値になる
	{
		case 1:
			ap->ang[ Y ] += 0x45;
			break;

		case -1:
			ap->ang[ Y ] -= 0x45;
			break;
	} 
	// 角度に合わせて進めるようにベクトルを算出する。
	ap->vec[ X ] = SOZ_get_sin( ap->ang[ Y ] ) *ap->work2[ D ];
	ap->vec[ Y ] =  SOZ_get_sin( ap->ang[ X ] ) *ap->work2[ D ];
	ap->vec[ Z ] = SOZ_get_cos( ap->ang[ X ] ) *ap->work2[ D ] + SOZ_get_cos( ap->ang[ Y ] ) *ap->work2[ D ];
}

//-----------------------------------------------------------------------------
// 自機ターゲット移動ベクトル設定 初期化
//-----------------------------------------------------------------------------
void jiki_look( TASK *ap )	// 注意！！　何かしらの変数に代入する
{
	ANGLE ans_x, ans_y, ans_z;
// 自機との座標をみて、角度を算出する。
	ans_x = SOZ_atan2( ap->pos[ Z ], ap->pos[ Y ], jiki->pos[ Z ], jiki->pos[ Y ] );
	ans_y = SOZ_atan2( ap->pos[ Z ], ap->pos[ X ], jiki->pos[ Z ], jiki->pos[ X ] );
	ans_z = SOZ_atan2( ap->pos[ X ], ap->pos[ Y ], jiki->pos[ X ], jiki->pos[ Y ] );
// 今の角度と本来向きたい角度をいれる	ansの中に左右どっちの方向にずれているか( プラスかマイナスか )
 	ans_x = SOZ_angle_diff( ap->ang[ X ], ans_x );
 	ans_y = SOZ_angle_diff( ap->ang[ Y ], ans_y );
 	ans_z = SOZ_angle_diff( ap->ang[ Z ], ans_z );
	switch ( SOZ_sgn( ans_x ) )	//数値の単位化　単位化すると 1 から -1 の整数の数値になる
	{
		case 1:
			ap->ang[ X ] -= 0x45;
			break;

		case -1:
			ap->ang[ X ] += 0x45;
			break;
	} 
	switch ( SOZ_sgn( ans_y ) )	//数値の単位化　単位化すると 1 から -1 の整数の数値になる
	{
		case 1:
			ap->ang[ Y ] += 0x45;
			break;

		case -1:
			ap->ang[ Y ] -= 0x45;
			break;
	} 
	// 角度に合わせて進めるようにベクトルを算出する。
	ap->vec[ X ] = SOZ_get_sin( ap->ang[ Y ] ) *ap->work2[ D ];
	ap->vec[ Y ] =  SOZ_get_sin( ap->ang[ X ] ) *ap->work2[ D ];
	ap->vec[ Z ] = SOZ_get_cos( ap->ang[ X ] ) *ap->work2[ D ] + SOZ_get_cos( ap->ang[ Y ] ) *ap->work2[ D ];
}

//-----------------------------------------------------------------------------
// 自機ターゲット移動ベクトル設定 初期化
//-----------------------------------------------------------------------------
void lockon_jiki( TASK *ap )
{
	// 自機との座標をみて、角度を算出する。
	ap->ang[ X ] = -SOZ_atan2( ap->pos[ Z ], ap->pos[ Y ], jiki->pos[ Z ], jiki->pos[ Y ] );
	ap->ang[ Y ] = -SOZ_atan2( ap->pos[ Z ], ap->pos[ X ], jiki->pos[ Z ], jiki->pos[ X ] );
	ap->ang[ Z ] = SOZ_atan2( ap->pos[ X ], ap->pos[ Y ], jiki->pos[ X ], jiki->pos[ Y ] ) + 0x8000;
	// 角度に合わせて進めるようにベクトルを算出する。
	ap->vec[ X ] = SOZ_get_sin( -ap->ang[ Y ] ) *ap->work2[ D ] + SOZ_get_cos( ap->ang[ Z ] ) *ap->work2[ D ];
	ap->vec[ Y ] = SOZ_get_sin( ap->ang[ Z ] ) *ap->work2[ D ] + SOZ_get_cos( -ap->ang[ X ] ) *ap->work2[ D ];
	ap->vec[ Z ] = SOZ_get_sin( -ap->ang[ X ] ) *ap->work2[ D ] + SOZ_get_cos( -ap->ang[ Y ] ) *ap->work2[ D ];
}

//-----------------------------------------------------------------------------
// 移動ベクトル設定
//-----------------------------------------------------------------------------
void ang_vec_setting( TASK *ap, FLOAT speed )
{
	ap->vec[ Z ] = ap->vec[ Y ] = ap->vec[ X ] = 0;

	//ap->vec[ X ] = ( ( SOZ_get_sin(  -ap->ang[ Y ] ) *speed ) + ( SOZ_get_cos(  -ap->ang[ Z ] ) *speed ) )/2;
	//ap->vec[ Y ] = ( ( SOZ_get_sin(  -ap->ang[ Z ] ) *speed ) + ( SOZ_get_cos(  -ap->ang[ X ] ) *speed ) )/2;
	//ap->vec[ Z ] = ( ( SOZ_get_sin(  -ap->ang[ X ] ) *speed ) + ( SOZ_get_cos(  -ap->ang[ Y ] ) *speed ) )/2;

	ap->vec[ X ] = SOZ_get_sin( ap->ang[ Y ] ) *speed;
	ap->vec[ Y ] =  SOZ_get_sin( ap->ang[ X ] ) *speed;
	ap->vec[ Z ] = SOZ_get_cos( ap->ang[ X ] ) *speed + SOZ_get_cos( ap->ang[ Y ] ) *speed;
}


//-----------------------------------------------------------------------------
//残像付与
//-----------------------------------------------------------------------------
void illusion_exec(TASK *ap)
{
	ap->base_color[0][0] -= ap->work1[X];//透明度を下げていく
	ap->pri += 2;//プライオリティ( 描画優先順位 )を上げる
	if (ap->base_color[0][0] < 10)//ある程度透明度が下がったらタスクエンド
	{
		TASK_end(ap);
		return;
	}
}
void illusion_start(TASK *actp, SINT32 speed, SINT32 blend)
{
	TASK *ap;
	ap = TASK_start(illusion_exec, 0, "残像");
	TASK_copy(ap, actp);//タスクのコピーを作る( ap に actp をコピーする )
	ap->work1[X] = speed;//ap->bace_collor[0][0]から引く値
}

void bic_illusion_exec(TASK *ap)
{
	ap->pri++;
	ap->pos[ Z ]++;
	ap->scale[ Y ] = ap->scale[ X ] += 0.005f;	// 大きくする
	ap->base_color[0][0] -= ap->work1[X];//透明度を下げていく
	ap->pri += 2;//プライオリティ( 描画優先順位 )を上げる
	if (ap->base_color[0][0] < 10)//ある程度透明度が下がったらタスクエンド
	{
		TASK_end(ap);
		return;
	}
}
void bic_illusion_start(TASK *actp, SINT32 speed, SINT32 blend)
{
	TASK *ap;
	ap = TASK_start(bic_illusion_exec, 0, "残像");
	TASK_copy(ap, actp);//タスクのコピーを作る( ap に actp をコピーする )
	ap->work1[X] = speed;//ap->bace_collor[0][0]から引く値
}


//------------------------------------------------------------------------------------------------------------------------------------------------------
// 自機が画面の半分より大きくなった時にカメラの角度を変える
//------------------------------------------------------------------------------------------------------------------------------------------------------
void camera_move( TASK *ap )
{
	ap->angle[ Z ] = 0x0000;
	ap->angle[ X ] = 0x0000;
// 特定のフレーム以上入力があった場合カメラの角度が変わる
	if( SOZ_Inkey_DAT( DIK_RIGHT ) >= 15 || SOZ_Inpad_DAT( 0, PADDIK_RIGHT ) >= 15 )
		ap->angle[ Z ] = 0x1000;
	if( SOZ_Inkey_DAT( DIK_LEFT ) >= 15 || SOZ_Inpad_DAT( 0, PADDIK_LEFT ) >= 15 )
		ap->angle[ Z ] = -0x1000;
	if( SOZ_Inkey_DAT( DIK_UP ) >= 15 || SOZ_Inpad_DAT( 0, PADDIK_UP ) >= 15 )
		ap->angle[ X ] = -0x0500;
	if( SOZ_Inkey_DAT( DIK_DOWN ) >= 15 || SOZ_Inpad_DAT( 0, PADDIK_DOWN ) >= 15 )
		ap->angle[ X ] = 0x0500;

	if( ap->angle[ Z ] < camera_ang_z[ 0 ] )
		camera_ang_z[ 0 ] -= 0x0075;
	else if ( ap->angle[ Z ] > camera_ang_z[ 0 ] )
		camera_ang_z[ 0 ] += 0x0075;

	if( ap->angle[ X ] < camera_ang_x[ 0 ] )
		camera_ang_x[ 0 ] -= 0x0050;
	else if ( ap->angle[ X ] > camera_ang_x[ 0 ] )
		camera_ang_x[ 0 ] += 0x00050;

	if( ap->pos[ Y ] > -100 &&  ap->pos[ Y ] < 300 )
	{
		if( camera_y[ 0 ] < 300 )
			camera_y[ 0 ] += 5;
	}
	else
	{
		if( camera_y[ 0 ] > 0 )
			camera_y[ 0 ] -= 5;
	}
}


//------------------------------------------------------------------------------------------------------------------------------------------------------
// 自機の弾のvec設定
//------------------------------------------------------------------------------------------------------------------------------------------------------
void shot_vec_setting( TASK *ap, FLOAT speed )
{
	ap->vec[ X ] = 0;
	ap->vec[ Y ] = SOZ_get_sin( ap->ang[ X ] ) *speed;
	ap->vec[ Z ] = SOZ_get_cos( ap->ang[ X ] ) *speed + speed;
	return;
}

///------------------------------------------------------------------------------------------------------------------------------------------------------
/// ハイスコア関連
///------------------------------------------------------------------------------------------------------------------------------------------------------

//------------------------------------------------------------------------------------------------------------------------------------------------------
// ハイスコアの並べ替え
//------------------------------------------------------------------------------------------------------------------------------------------------------

int hi_score_sort( void )
{
	SINT32 for_rank = 9, score_slot;
	if( score > hi_score[ 9 ] )											// ランキングの最下位のSCOREを下回っていたら何もせずタスクエンド
	{
		hi_score[ 9 ] = score;											// とりあえず10位にいれる
		for( for_rank = 9; for_rank > 0; for_rank-- )					// 確認
		{
			if( hi_score[ for_rank ] > hi_score[ for_rank - 1 ] )		// もし、ランクが下の方が上よりSCOREが高かったら
			{
				// 入れ替える
				score_slot = hi_score[ for_rank -1 ];
				hi_score[ for_rank - 1 ] = hi_score[ for_rank ];
				hi_score[ for_rank ] = score_slot;
			}
		}
#if 0
		// 新しいハイスコアの順位を探す
		for( now_rank = 9; now_rank > 0; now_rank -- )
			if( score > hi_score[ now_rank ] )
				sort_rank = now_rank;
		// ソートをする
		for( for_rank = 9; for_rank > sort_rank; for_rank-- )
			hi_score[ for_rank ] = hi_score[ for_rank -1 ];
		hi_score[ sort_rank-1 ] = score;
#endif
		return 1;
	}
	else
		return 0;
}


//------------------------------------------------------------------------------------------------------------------------------------------------------
// ハイスコア/ランキングの初期化
//------------------------------------------------------------------------------------------------------------------------------------------------------

void hi_score_all_clear( void )
{
	SINT32 rank_no;
	for( rank_no = 0; rank_no < 10; rank_no++ )
	{
		hi_score[ rank_no ] = 0;
	}
}
