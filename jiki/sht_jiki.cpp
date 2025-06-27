#ifdef WINDOWS_PC
#include    "C:/project/libs/systemOZ_v4/soz.h"
#else
#include    "D:/project/guardians_2dx/proj.win32/src/systemOZ/soz.h"
#endif

#include    "C:/project/bace/src/game/game_include.h"
TASK *jiki;
SINT32 life = 3;
SINT32 rest_missile = 0;	// ミサイルの残弾数
SINT32 j_state_mode = 0;	// アナログスティックを使用するか
SINT32 missile_ok = 0;		// ロックオン状態を検知
SINT32 shot_break_count = 0;		// ショットで破壊した敵の数をカウントする

SINT32 sphire_hit_check( TASK *ap, TASK *actp )				// 球どうしの判定確認
{
	FLOAT sa_x, sa_y, sa_z;
	FLOAT length;

	sa_x = ap->pos[ X ] - actp->pos[ X ];
	sa_y = ap->pos[ Y ] - actp->pos[ Y ];
	sa_z = ap->pos[ Z ] - actp->pos[ Z ];
	length = ( FLOAT )sqrt( ( sa_x * sa_x ) + ( sa_y * sa_y ) + ( sa_z * sa_z ) );

	if( length <= ( ap->sphire + actp->sphire ) )
		return 1;

	return 0;
}

void shot_hit_check( TASK *ap )								// 自機の攻撃が持っているヒット確認
{
	TASK *actp;
	for( actp = ap_start; actp != NULL; actp = actp->next )
		switch( actp->task_group )
		{
			case  GROUP_ENEMY:
				if( sphire_hit_check( ap, actp ) != 0 )
				{
					actp->callback( ap, actp );
					ap->callback( ap, actp );
				}
				break;
		}
}

void myship_hit_check( TASK *ap )							// 自機本体が持つヒット確認
{
	TASK *actp;
	for( actp = ap_start; actp != NULL; actp = actp->next )
		switch( actp->task_group )			// 敵の本体もしくは攻撃に当たった時
		{
			case GROUP_BULLET:
			case  GROUP_ENEMY:
				if( sphire_hit_check( ap, actp ) != 0 )
				{
					bullet_myship_hit_effect();		// 画面が赤くなるエフェクト
					ap->callback( ap, actp );
					bonus = 0;					// SCOREボーナスを初期化する
				}
				break;
		}
}

//------------------------------------------------------------------------------------------------------------------------------------------------------
// 自機ミサイル　
//------------------------------------------------------------------------------------------------------------------------------------------------------

// 一番近い敵を狙うプログラム( 一応動作する )
void missile_lock_on ( TASK *ap )
{
	TASK *actp, *tp{};
	FLOAT sa = 0, sa_x = 0, sa_y = 0, sa_z = 0;
	for( actp = ap_start; actp != NULL; actp = actp->next )	// タスクの全捜査
		if( actp->task_group == GROUP_ENEMY )	// タスクグループがGOUP_ENEMYのものを探す
		{
			// ミサイルと敵の距離を計算
			sa_x = ( ap->pos[ X ] - actp->pos[ X ] ) * ( ap->pos[ X ] - actp->pos[ X ] );
			sa_y = ( ap->pos[ Y ] - actp->pos[ Y ] ) * ( ap->pos[ Y ] - actp->pos[ Y ] );
			sa_z = ( ap->pos[ Z ] - actp->pos[ Z ] ) * ( ap->pos[ Z ] - actp->pos[ Z ] );
			ap->fwork1[ X ] = FLOAT( sqrtf( sa_x + sa_y + sa_z ) );
			if( sa < ap->fwork1[ X ] && actp->pos[ Z ] < 20000 )		// 一番距離が近い敵を狙う
			{
				if( ap != jiki )
					target_lock_vec( ap, actp );
				tp = actp;
				sa = ap->fwork1[ X ];
			}
		}
	if( tp != NULL )
	{
			ms_lockon_effect( tp->pos[ X ], tp->pos[ Y ], tp->pos[ Z ] );		// ロックオンエフェクトの表示
			if( ap == jiki && tp->pos[ Z ] < 20000.0f && tp->pos[ Z ] > 500.0f )
			{
				missile_ok = 1;
				ms_lockon_font( tp->pos[ X ], tp->pos[ Y ], tp->pos[ Z ] );		// ロックオン関連のフォントの表示
			}
			else
				missile_ok = 0;
	}
}

// 自機ミサイルの実行部分
void jiki_missile_exec( TASK *ap )
{
	ap->work2[ X ] ++;
// 座標移動
	ap->pos[ X ] += ap->vec[ X ];
	ap->pos[ Y ] += ap->vec[ Y ];
	ap->pos[ Z ] += ap->vec[ Z ];

// 特定時間経過したら
	if( ap->work2[ X ] >= 150 )
	{
		TASK_end( ap );
		return;
	}

	shot_hit_check( ap );		// ヒット確認

	if( ap->work2[ X ] % 2 == 0 )	// 特定フレームごとにミサイルのエフェクトを発生させる
		missile_effect( ap->pos[ X ], ap->pos[ Y ], ap->pos[ Z ] );
}
void jiki_missile( void )
{
	TASK *ap;
	ap = TASK_start_MODEL( jiki_missile_exec, GROUP_SHOT, MODEL_MISSILE, TEXTURE_MISSILE, "自機のミサイル" );
	ap->grp_mode = WRITE_ZBUFFER | TEST_ZBUFFER | USE_LIGHTING;
	ap->pos[ X ] = jiki->pos[ X ];
	ap->pos[ Y ] = jiki->pos[ Y ];
	ap->pos[ Z ] = jiki->pos[ Z ];
	ap->fwork1[ X ] = 9999.0f;
	ap->work2[ X ] = 0;
	ap->work2[ D ] = 1000;
	ap->sphire = 180.0f;
	ap->sphire_shift[ X ] = 0;
	ap->sphire_shift[ Y ] = 0;
	ap->sphire_shift[ Z ] = 0;
	ap->callback = missile_callback;
	ap->vec[ X ] = 0;
	ap->vec[ Y ] = 0;
	ap->vec[ Z ] = 250;
	ap->ATK = jiki->ATK * 6;
	ap->BONUS = 50;
	missile_start_effect( ap->pos[ X ], ap->pos[ Y ], ap->pos[ Z ] );			// ミサイル発射のエフェクト
	SOZ_play_se( SE_MISSILE, 3.0f, 1, 0.0f );
	missile_lock_on( ap );			// 一番近い敵をロックオン
}

//------------------------------------------------------------------------------------------------------------------------------------------------------
// 自機ショット
//------------------------------------------------------------------------------------------------------------------------------------------------------
void shot_exec( TASK *ap )
{
	ap->work1[ X ] ++;
	if( ap->pos[ Z ] < 12000 )
	{
		shot_hit_check( ap );								// ヒット確認
	}

	if( ap->work1[ X ] % 2 == 0 )
		illusion_start( ap, 75, BLEND_ADD );
// 座標移動
	ap->pos[ X ] += ap->vec[ X ];
	ap->pos[ Y ] += ap->vec[ Y ];
	ap->pos[ Z ] += ap->vec[ Z ];
// 射程制限まで移動したらタスクエンドさせる。
	if( ap->pos[ Z ] > 300000 )
	{
		TASK_end( ap );
		return;
	}
}
void shot( FLOAT pos_x, FLOAT pos_y,FLOAT pos_z )
{
	TASK *ap;
	ap = TASK_start_MODEL( shot_exec, GROUP_SHOT, MODEL_SHOT, TEXTURE_SHOT, "自機の攻撃" );
	ap->grp_mode = TEST_ZBUFFER;
	ap->pos[ X ] = pos_x;
	ap->pos[ Y ] = pos_y;
	ap->pos[ Z ] = pos_z;
	ap->pri = PRI_SHOT;
	shot_vec_setting( ap, 400 * 1.5f );
	ap->ang[ Z ] = Rand2( 0x0000, 0xffff );
	ap->sphire = 240.0f;
	ap->sphire_shift[ X ] = 0;
	ap->sphire_shift[ Y ] = 0;
	ap->sphire_shift[ Z ] = 0;
	ap->base_color[ 0 ][ 0 ] = 0xaa;
	ap->blend_type = BLEND_ADD;
	ap->work1[ X ];
	ap->ATK = jiki->ATK;
	ap->BONUS = 25;
	ap->callback = shot_callback;
	shot_effect_start( ap->pos[ X ], ap->pos[ Y ], ap->pos[ Z ] );
//	SOZ_play_se( SE_SHOT, 2.0f, 1, 1 );
}

//------------------------------------------------------------------------------------------------------------------------------------------------------
// 自機
//------------------------------------------------------------------------------------------------------------------------------------------------------

// 無敵時間用テクスチャ表示	/今後もしかしたら改善して使うかも
void my_ship_tex_chenge( TASK *ap )
{
	//ap->workB[ D ] = 0;				// 無敵時間
	//ap->workB[ P ] = 0;				// 赤点滅
	ap->workB[ D ]++;
	if( ap->workB[ D ] % 20 == 0 )
	{
		if( ap->base_color[ 0 ][ 0 ] == 0x88 )
			ap->base_color[ 0 ][ 0 ] = 0xff;
		else
			ap->base_color[ 0 ][ 0 ] = 0x88;
	}

	if( ap->workA[ Y ] <= 0 )	// 時間経過で無敵解除
	{
		ap->base_color[ 0 ][ 0 ] = 0xff;
		ap->workB[ D ] = 0;
	}
}

// アナログスティックの値を取得し、スピードの値に変換する
void state_chenge_speed( TASK *ap )
{
	if( demo_mode == 0 )
	{
		ap->VEC_X = FLOAT( j_state->lX ) / 20.0f;
		ap->VEC_Y = FLOAT( -j_state->lY ) / 20;
	}
	else
	{
		ap->VEC_X = FLOAT( button_lr ) / 20.0f;
		ap->VEC_Y = -FLOAT( button_ud ) / 20;
	}
}

void my_ship_cont( TASK *ap )	// 自機入力動作
{
	if( demo_mode == 0 )
		button_data_get();				// ボタンの入力取得
// 最初に移動ベクトルの初期化
	ap->vec[ X ] = 0;
	ap->vec[ Y ] = 0;

// アナログスティックの値をスピードの値に変換
	if( ( stick_data & STICK_ANALOG ) != 0 )
		state_chenge_speed( ap );

	if( button_ud < 0 )						// 上入力:上昇
	{
		if( ap->pos[ Y ] < POS_LIMIT2 )
			if( ap->ang[ X ] > 0 )
			{
				if( ( stick_data &  STICK_ANALOG ) == 0 )
					ap->vec[ Y ] = SPEED /2;
				else if( j_state->lY < -200 || button_ud < -200 )// アナログスティックの値を適応させる
					ap->vec[ Y ] = ap->VEC_Y;
				ap->vec[ X ] = SOZ_get_sin( ap->ang[ Z ] ) *ap->vec[ X ];
				ap->vec[ Y ] = SOZ_get_cos( -ap->ang[ Z ] ) *ap->vec[ Y ];
			}

		if( ap->ang[ X ] < ANG_LIMIT2 )
		{
			ap->ang[ X ] += ANGLE_X;
		}
		else
			ap->ang[ X ] = ANG_LIMIT2;
	}
	else if( button_ud > 0 )				// 下入力:下降
	{
		if( ap->pos[ Y ] > -POS_LIMIT2 )
			if( ap->ang[ X ] < 0 )
			{
				if( ( stick_data &  STICK_ANALOG ) == 0 )
					ap->vec[ Y ] = -SPEED /2;
				else if( j_state->lY > 200 || button_ud > 200 )	// アナログスティックの値を適応させる
					ap->vec[ Y ] = ap->VEC_Y;
				ap->vec[ X ] = SOZ_get_sin( -ap->ang[ Z ] ) *ap->vec[ X ];
				ap->vec[ Y ] = SOZ_get_cos( -ap->ang[ Z ] ) *ap->vec[ Y ];
			}

		if( ap->ang[ X ] > -ANG_LIMIT2 )
		{
			ap->ang[ X ] += -ANGLE_X;
		}
		else
			ap->ang[ X ] = -ANG_LIMIT2;
	}
	else
	{
		if( ap->ang[ X ] < ANGLE_X && ap->ang[ X ] > -ANGLE_X )
			ap->ang[ X ] = 0x0000;
		else if( ap->ang[ X ] >= ANGLE_X )
			ap->ang[ X ] += -ANGLE_X;
		else if( ap->ang[ X ] <= -ANGLE_X )
			ap->ang[ X ] += ANGLE_X;
	}


	if( button_lr < 0 )	//左旋回・左移動
	{
		if( ap->pos[ X ] > -POS_LIMIT )
			if( ap->ang[ Z ] < 0 )
			{
				if( ( stick_data & STICK_ANALOG ) == 0 )
					ap->vec[ X ] = -SPEED /2;
				else if( j_state->lX < -200 || button_lr < -200 )	// アナログスティックの値を適応させる
					ap->vec[ X ] = ap->VEC_X;
				ap->vec[ X ] += SOZ_get_sin( -ap->ang[ Z ] ) *ap->vec[ X ];
				ap->vec[ Y ] += SOZ_get_cos( -ap->ang[ Z ] ) *ap->vec[ Y ];
			}
		if( ap->ang[ Z ] > -ANG_LIMIT )
			ap->ang[ Z ] += -ANGLE_Z;
		else
			ap->ang[ Z ] = -ANG_LIMIT;
	}

	else if( button_lr > 0 )	//右旋回・右移動
	{
		if( ap->pos[ X ] < POS_LIMIT )
			if( ap->ang[ Z ] > 0 )
			{
				if ( ( stick_data & STICK_ANALOG ) == 0 )
					ap->vec[ X ] = SPEED /2;
				else if( j_state->lX > 200 || button_lr > 200 )	// アナログスティックの値を適応させる
					ap->vec[ X ] = ap->VEC_X;
				ap->vec[ X ] += SOZ_get_sin( ap->ang[ Z ] ) *ap->vec[ X ];
				ap->vec[ Y ] += SOZ_get_cos( -ap->ang[ Z ] ) *ap->vec[ Y ];
			}
		if( ap->ang[ Z ] < ANG_LIMIT )
			ap->ang[ Z ] += ANGLE_Z;
		else
			ap->ang[ Z ] = ANG_LIMIT;
	}

	else
	{
		if( ap->ang[ Z ] < ANGLE_Z && ap->ang[ Z ] > -ANGLE_Z )
		{
			ap->ang[ Z ] = 0x0000;
		}
		else if( ap->ang[ Z ] >= ANGLE_Z )
		{
			ap->ang[ Z ] += -ANGLE_Z;
		}
		else if( ap->ang[ Z ] <= -ANGLE_Z )
		{
			ap->ang[ Z ] += ANGLE_Z;
		}
	}

	ap->pos[ X ] += ap->vec[ X ];
	ap->pos[ Y ] += ap->vec[ Y ];
}
void shot_system( TASK *ap )	// 射撃操作
{
// 弾のズレを作る
	SINT32 rand_pos_x, rand_pos_y;
	rand_pos_x = rand_pos_y = Rand2( 45, 90 );
	ANGLE rand_ang = Rand2( 0x0000, 0xffff );
	rand_pos_x = SINT32 ( SOZ_get_sin( rand_ang ) * rand_pos_x );
	rand_pos_y = SINT32 ( SOZ_get_cos( rand_ang ) * rand_pos_y );
// 射撃
	if( SOZ_Inkey_TRG( DIK_X ) || SOZ_Inpad_TRG( 0, PADDIK_SUB_MISSILE ) || ( ( attack_button & DEMO_MISSILE ) != 0 && demo_mode == 1 ) )			// ボタンが押されたらミサイルを発射
	{
		if( missile_ok == 1 )
			if( rest_missile > 0 )			// 残弾があればミサイルを発射する1
			{
				jiki_missile();
				rest_missile --;			// 残弾を減らす
				clrFLG( attack_button, DEMO_MISSILE );	// ミサイルのフラグを寝かす。
				ap->workC[ E ] = Rand2( 1, 30 );
			}
	}
	if( SOZ_Inkey_DAT( DIK_Z ) || SOZ_Inpad_DAT( 0, PADDIK_MAIN_ATTACK ) || ( attack_button & DEMO_SHOT ) != 0 )			// ボタンが押されている間、バルカンを発射
	{

		ap->workB[ X ]++;
		if( ap->workB[ X ] % 2 == 0 )	// 一定時間おきに弾を発射する
		{
			shot( ap->pos[ X ] + rand_pos_x, ap->pos[ Y ] + rand_pos_y, ap->pos[ Z ] + 900.0f );	// 座標を少しバラつかせる
			if( ap->workB[ X ] % 4 == 0 )
				SOZ_play_se( SE_SHOT, 1.0f, 1, 1 );
			else
				SOZ_play_se( SE_SHOT_2, 1.0f, 1, 1 );
		}
	}
}
void my_ship_break( TASK *ap )		// 自機撃墜演出
{
	ap->workA[Z] ++;
	bg_speed /= 10;
	if( ap->workA[ Z ] == 5 )
		camera_vibration_medium();								// カメラ振動　強
	if( ap->workA[ Z ] % 10 == 0 && ap->workA[ Z ] < 30 )
	{
		SOZ_play_se( SE_BREAK, 2.0f, 1, 1.0f );	// 効果音を鳴らす
		break_effect( ap->pos[ X ], ap->pos[ Y ], ap->pos[ Z ] );	// 爆発エフェクト
	}
	if( ap->workA[ Z ] == 30 )
	{
		SOZ_play_se( SE_BREAK_BOM, 2.0f, 1, 1.0f );	// 効果音を鳴らす
		break_bom_effect( ap->pos[ X ], ap->pos[ Y ], ap->pos[ Z ] );	// 爆発エフェクト
		game_type = TYPE_OVER;
	}
	else if( ap->workA[ Z ] > 30 )
	{
		if( ap->workA[ Z ] % 30 == 0 )
		{
			break_effect( ap->pos[ X ] +F_Rand2( -600.0f, 600.0f ), ap->pos[ Y ] +F_Rand2( -100.0f, 100.0f ), ap->pos[ Z ] );	// 破壊のエフェクトを表示
			break_effect( ap->pos[ X ] +F_Rand2( -600.0f, 600.0f ), ap->pos[ Y ] +F_Rand2( -100.0f, 100.0f ), ap->pos[ Z ] );	// 破壊のエフェクトを表示
			break_effect( ap->pos[ X ] +F_Rand2( -600.0f, 600.0f ), ap->pos[ Y ] +F_Rand2( -100.0f, 100.0f ), ap->pos[ Z ] );	// 破壊のエフェクトを表示
			break_effect( ap->pos[ X ] +F_Rand2( -600.0f, 600.0f ), ap->pos[ Y ] +F_Rand2( -100.0f, 100.0f ), ap->pos[ Z ] );	// 破壊のエフェクトを表示
		}
		if( ap->workA[ Z ] % 40 == 0 || ap->workA[ Z ] % 35 == 0 )
		{
			break_effect_02( ap->pos[ X ] +F_Rand2( -600.0f, 600.0f ), ap->pos[ Y ] +F_Rand2( -100.0f, 100.0f ), ap->pos[ Z ] );
		}
		if( ap->workA[ Z ] > 300 )
		{
			break_effect_02( ap->pos[ X ] +F_Rand2( -600.0f, 600.0f ), ap->pos[ Y ] +F_Rand2( -100.0f, 100.0f ), ap->pos[ Z ] );
			break_effect_02( ap->pos[ X ] +F_Rand2( -600.0f, 600.0f ), ap->pos[ Y ] +F_Rand2( -100.0f, 100.0f ), ap->pos[ Z ] );
			break_effect_02( ap->pos[ X ] +F_Rand2( -600.0f, 600.0f ), ap->pos[ Y ] +F_Rand2( -100.0f, 100.0f ), ap->pos[ Z ] );
			break_effect_02( ap->pos[ X ] +F_Rand2( -600.0f, 600.0f ), ap->pos[ Y ] +F_Rand2( -100.0f, 100.0f ), ap->pos[ Z ] );
			break_effect_02( ap->pos[ X ] +F_Rand2( -600.0f, 600.0f ), ap->pos[ Y ] +F_Rand2( -100.0f, 100.0f ), ap->pos[ Z ] );
			TASK_end( ap );
			return;
		}
	}
}
void my_ship_game_clear( TASK *ap )
{
}
void my_ship_exec( TASK *ap )
{
	ap->workB[ Y ]++;
	switch ( ap->workA[ X ] )
	{
		case 0:	// 登場シーン
			ap->pos[ Z ] += 50.0f;
			if( ap->pos[ Z ] >= 0 )
				ap->workA[ X ] = 1;
			break;

		case 1:	// プレイヤー操作モード
			shot_system( ap );		// ショット射撃
			my_ship_cont( ap );		// 機体の操縦
//			myship_hit_check( ap);	// 敵と自機の当たり判定チェック
			camera_move( ap );
			SOZ_camera_move( 0 );
			missile_lock_on( ap );			// 一番近い敵をロックオン
			break;

		case 2:	// 無敵モード
			missile_lock_on( ap );			// 一番近い敵をロックオン
			shot_system( ap );		// ショット射撃
			my_ship_cont( ap );		// 機体の操縦
			ap->workA[ Y ]--;
			if( ap->workA[ Y ] <= 0 )	// 時間経過で無敵解除
			{
				ap->workA[ X ] = 1;
			}
			camera_move( ap );
			SOZ_camera_move( 0 );
			break;

		case 3:	// 爆破演出/GAME OVER
			my_ship_break( ap );
			break;

		case 4:	// クリア演出/GAME CLEAR
			my_ship_game_clear( ap );
			break;

		case 50:	// ボス第２フェーズ移行シーン
			ap->pos[ Z ] += ap->workD[ X ];
			ap->workD[ X ] += 4;
			if( ap->pos[ Z ] > 30000 )
				ap->workA[ X ]++;
			break;

		case 51:
			ap->pos[ Z ] -= ap->workD[ X ];
			ap->workD[ X ] -= 2;
			if( ap->pos[ Z ] <= 10 )
				ap->workA[ X ] = 1;
			break;
	}

	// アフターバーナー
	if( ap->workB[ Y ] % 2 == 0 )
	{
		jiki_burner_effect( ap, 50 );
		jiki_burner_effect( ap, -50 );
		if( life < 2 )
		{
			break_smoke( ap );
			if( ap->workB[ Y ] % 20 == 0 )
				spark_effect( ap, 10 );
		}
	}

//------------- 自機のデバッグ情報 -------------------------------------------

	SOZ_locate_print( 2,  5, "[JIKI] pos X:	%f", ap->pos[ X ] );
	SOZ_locate_print( 2,  6, "[JIKI] pos X:	%f", ap->pos[ Y ] );
	SOZ_locate_print( 2,  7, "[JIKI] pos X:	%f", ap->pos[ Z ] );

	SOZ_locate_print( 2,  9, "[JIKI] vec X:	%f", ap->vec[ X ] );
	SOZ_locate_print( 2, 10, "[JIKI] vec X:	%f", ap->vec[ Y ] );
	SOZ_locate_print( 2, 11, "[JIKI] vec X:	%f", ap->vec[ Z ] );

	SOZ_locate_print( 2, 13, "[Lstic] LR : %05d", j_state->lX);		// 左スティック左右
	SOZ_locate_print( 2, 14, "[Lstic] UD : %05d", j_state->lY);		// 左スティック上下
	SOZ_locate_print( 2, 15, "[Rstic] LR : %05d", j_state->lZ);		// 右スティック左右
	SOZ_locate_print( 2, 16, "[Rstic] UD : %05d", j_state->lRz);	// 右スティック上下

	SOZ_locate_print( 2, 17, "[SPEED] X : %05d", ap->VEC_X );
	SOZ_locate_print( 2, 18, "[SPEED] Y : %05d", ap->VEC_Y );

//----------------------------------------------------------------------------
}
void my_ship( void )
{
	TASK *ap;
	ap = TASK_start_MODEL( my_ship_exec, GROUP_MY_SHIP, MODEL_MY_SHIP, TEXTURE_MY_SHIP, "自機3Dモデル" );
	ap->grp_mode = WRITE_ZBUFFER | TEST_ZBUFFER | USE_LIGHTING | USE_3DPOS;	//| USE_SPECULAR ;
	ap->pos[ X ] = 0;
	ap->pos[ Y ] = -650.0f;
	ap->pos[ Z ] = -1500.0f;
//	ap->pos[ Z ] = 0.0f;
	ap->ang[ X ] = 0x0200;
//	ap->ang[ Y ] = -0x4000;
	ap->ang[ Z ] = 0x0000;
	ap->angle[ X ] = 0x0000;
	ap->angle[ Y ] = 0x0000;
	ap->angle[ Z ] = 0x0000;
	ap->pri = PRI_JIKI;

	ap->workA[ X ] = 0;				// 登場シーン / 操作オフ / 無敵
	ap->workA[ Y ] = 0;				// 無敵設定用
	ap->workA[ Z ] = 0;				// 爆破演出
	ap->workB[ X ] = 0;				// ショット間隔計算
	ap->workB[ Y ] = 0;				// バーナー間隔計算用
	ap->workB[ D ] = 0;				// 無敵時間
	ap->workB[ P ] = 0;				// 赤点滅
	ap->workC[ D ] = 0x0000;		// angに足す値
	ap->workC[ E ] = 0;				// デモプレイ時のミサイル発射フレーム計算
	ap->workD[ X ] = 0;				// ボス戦時の演出
	ap->workD[ Y ] = 0;				// ボス戦時の演出
	ap->ATK = SHOT_DAMAGE;
	ap->sphire = 80.0f;
	ap->callback = my_ship_callback;

	jiki = ap;
//	SOZ_camera_set_at_move( 0 );

// 3Dモデルのマテリアルを設定
	ap->specular[ 0 ] = 1.0f;
	ap->specular[ 1 ] = 1.0f;
	ap->specular[ 2 ] = 1.0f;
	ap->ambient[ 0 ] = 0.0f;
	ap->ambient[ 1 ] = 0.0f;
	ap->ambient[ 2 ] = 0.0f;
	ap->emissive[0] = 0.25f;
	ap->emissive[1] = 0.25f;
	ap->emissive[2] = 0.25f;
 	ap->pow = 6.0f;
	SOZ_material_setting( ap );

	shot_break_count = 0;
	life = 3;					// 残機の初期化
	stage = 0;					// ステージ表記の初期化
	demo_mode = 0;
	attack_button = 0;
#if 1
	rest_missile = 30;			// ミサイルの残弾数の初期化
#else
	rest_missile = 999;			// ミサイルの残弾数の初期化
#endif
}
