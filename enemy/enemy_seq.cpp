#ifdef WINDOWS_PC
#include    "C:/project/libs/systemOZ_v4/soz.h"
#else
#include    "D:/project/guardians_2dx/proj.win32/src/systemOZ/soz.h"
#endif

#include    "C:/project/bace/src/game/game_include.h"

SINT32 seq_data[] =
{
	NEXT_STAGE,
#if 0
//#ifdef DEBUG	// 動作テスト用
	NEXT_WAVE,
	SEQ_WARNING,
	WAIT_TIME( 30 * 10 ),
	SUMMON_BOSS,	// ボスの出現
	NEXT_WAVE,
#else
	NEXT_WAVE,
/// STAGE 01	/ 直進してくる敵のみ
	ENE_MOVE( 1 ),			// 出現する敵の動き
	FORMATION( XR_Y ),		// 敵の出現配置
	ENE_GEN( 40, 5, 0 ),	// 敵の出現
	FORMATION( X_Y ),		// 敵の出現配置
	ENE_GEN( 40, 5, 0 ),	// 敵の出現
	FORMATION( XL_Y ),		// 敵の出現配置
	ENE_GEN( 40, 5, 0 ),	// 敵の出現
	FORMATION( X2_YD ),		// 敵の出現配置
	ENE_GEN( 40, 5, 2 ),	// 敵の出現


	FORMATION( X_Y2 ),			// 敵の出現配置
	ENE_GEN( 40, 5, 1 ),	// 敵の出現
	FORMATION( X3_Y ),			// 敵の出現配置
	ENE_GEN( 40, 5, 2 ),	// 敵の出現

	NEXT_WAVE,
	NEXT_STAGE,


/// STAGE 02	/ ミサイルを撃ってくる
	ENE_MOVE( 6 ),			// 出現する敵の動き
	FORMATION( X2_Y ),			// 敵の出現配置
	ENE_GEN( 90, 3, 3 ),	// 敵の出現

	FORMATION( X2_YU ),			// 敵の出現配置
	ENE_GEN( 90, 3, 4 ),	// 敵の出現

	FORMATION( X2_YD ),			// 敵の出現配置
	ENE_GEN( 90, 3, 1 ),	// 敵の出現

	FORMATION( XL_Y3 ),			// 敵の出現配置
	ENE_GEN( 90, 3, 4 ),	// 敵の出現

	FORMATION( XR_Y3 ),			// 敵の出現配置
	ENE_GEN( 90, 3, 4 ),	// 敵の出現

	NEXT_WAVE,
	NEXT_STAGE,

/// STAGE 03	/ 激しく動く敵
	ENE_MOVE( 4 ),			// 出現する敵の動き
	FORMATION( XL_B ),			// 敵の出現配置
	ENE_GEN( 40, 8, 4 ),	// 敵の出現

	ENE_MOVE( 5 ),			// 出現する敵の動き
	FORMATION( XR_B ),			// 敵の出現配置
	ENE_GEN( 40, 8, 4 ),	// 敵の出現

	ENE_MOVE( 2 ),			// 出現する敵の動き
	FORMATION( X2_YU ),			// 敵の出現配置
	ENE_GEN( 40, 4, 2 ),	// 敵の出現

	ENE_MOVE( 3 ),			// 出現する敵の動き
	FORMATION( X2_YD ),			// 敵の出現配置
	ENE_GEN( 40, 4, 2 ),	// 敵の出現

	ENE_MOVE( 4 ),			// 出現する敵の動き
	FORMATION( XL_B ),			// 敵の出現配置
	ENE_GEN( 40, 4, 4 ),	// 敵の出現

	ENE_MOVE( 2 ),			// 出現する敵の動き
	FORMATION( X2_YU ),			// 敵の出現配置
	ENE_GEN( 40, 4, 2 ),	// 敵の出現

	NEXT_WAVE,
	NEXT_STAGE,

/// STAGE 04	/ 大量の敵
	ENE_MOVE( 1 ),			// 出現する敵の動き
	FORMATION( XR_YU ),			// 敵の出現配置
	ENE_GEN( 10, 1, 0 ),	// 敵の出現
	FORMATION( XR_Y ),			// 敵の出現配置
	ENE_GEN( 10, 1, 0 ),	// 敵の出現
	FORMATION( XR_YD ),			// 敵の出現配置
	ENE_GEN( 10, 1, 0 ),	// 敵の出現
	FORMATION( X_YD ),			// 敵の出現配置
	ENE_GEN( 10, 1, 0 ),	// 敵の出現
	FORMATION( XL_YD ),			// 敵の出現配置
	ENE_GEN( 10, 1, 0 ),	// 敵の出現
	FORMATION( XL_Y ),			// 敵の出現配置
	ENE_GEN( 10, 1, 0 ),	// 敵の出現
	FORMATION( XL_YU ),			// 敵の出現配置
	ENE_GEN( 10, 1, 0 ),	// 敵の出現
	FORMATION( X_YU ),			// 敵の出現配置
	ENE_GEN( 10, 1, 0 ),	// 敵の出現

	WAIT_TIME( 20 ),
	ENE_MOVE( 4 ),			// 出現する敵の動き
	FORMATION( XL_B ),			// 敵の出現配置
	ENE_GEN( 40, 4, 4 ),	// 敵の出現
	ENE_MOVE( 5 ),			// 出現する敵の動き
	FORMATION( XR_B ),			// 敵の出現配置
	ENE_GEN( 40, 4, 4 ),	// 敵の出現

	ENE_MOVE( 6 ),			// 出現する敵の動き
	FORMATION( XL2_YU ),			// 敵の出現配置
	ENE_GEN( 40, 4, 3 ),	// 敵の出現
	FORMATION( XR2_YD ),			// 敵の出現配置
	ENE_GEN( 40, 4, 3 ),	// 敵の出現


	ENE_MOVE( 6 ),			// 出現する敵の動き
	FORMATION( XR_YU ),			// 敵の出現配置
	ENE_GEN( 10, 1, 0 ),	// 敵の出現
	FORMATION( XR_Y ),			// 敵の出現配置
	ENE_GEN( 10, 1, 0 ),	// 敵の出現
	FORMATION( XR_YD ),			// 敵の出現配置
	ENE_GEN( 10, 1, 0 ),	// 敵の出現
	FORMATION( X_YD ),			// 敵の出現配置
	ENE_GEN( 10, 1, 0 ),	// 敵の出現
	FORMATION( XL_YD ),			// 敵の出現配置
	ENE_GEN( 10, 1, 0 ),	// 敵の出現
	FORMATION( XL_Y ),			// 敵の出現配置
	ENE_GEN( 10, 1, 0 ),	// 敵の出現
	FORMATION( XL_YU ),			// 敵の出現配置
	ENE_GEN( 10, 1, 0 ),	// 敵の出現
	FORMATION( X_YU ),			// 敵の出現配置
	ENE_GEN( 10, 1, 0 ),	// 敵の出現

	NEXT_WAVE,
	NEXT_STAGE,

// STAGE 05 BOSS
	SEQ_WARNING,
	WAIT_TIME( 60 * 5 ),
	SUMMON_BOSS,	// ボスの出現
#endif
	WAIT_TIME( 60 * 60 * 60 ),
	WAIT_TIME( 60 * 60 * 60 ),
	WAIT_TIME( 60 * 60 * 60 ),
	WAIT_TIME( 60 * 60 * 60 ),
	SEQ_TOP,
};


void summon_formation( SINT32 formation_id, SINT32 move_id, SINT32 skin_id )
{
	switch( formation_id )
	{
		case XR_YD:			//　X右		Y下
		enemy_disp( move_id, skin_id, 700, -500, 30000, 250, 500 );
			break;

		case X_YD:			//　X中心	Y下
		enemy_disp( move_id, skin_id, 0, -500, 30000, 250, 500 );
			break;

		case XL_YD:			//　X左		Y下
		enemy_disp( move_id, skin_id, -700, -500, 30000, 250, 500 );
			break;

		case XR_Y:			//　X右		Y中心
		enemy_disp( move_id, skin_id, 700, 0, 30000, 250, 500 );
			break;

		case X_Y:			//　X中心	Y中心
		enemy_disp( move_id, skin_id, 0, 0, 30000, 250, 500 );
			break;

		case XL_Y:			//　X左		Y中心
		enemy_disp( move_id, skin_id, -700, 0, 30000, 250, 500 );
			break;

		case XR_YU:			//　X右		Y上
		enemy_disp( move_id, skin_id, 700, 500, 30000, 250, 500 );
			break;

		case X_YU:			//　X中心	Y上
		enemy_disp( move_id, skin_id, 0, 500, 30000, 250, 500 );
			break;

		case XL_YU:			//　X左		Y上
		enemy_disp( move_id, skin_id, -700, 500, 30000, 250, 500 );
			break;


		case XR2_YD:			//	X右２	Y下
		enemy_disp( move_id, skin_id, 700, -500, 30000, 250, 500 );
		enemy_disp( move_id, skin_id, 0, -500, 30000, 250, 500 );
			break;

		case X2_YD:		//	Xサイド	Y下
		enemy_disp( move_id, skin_id, 700, -500, 30000, 250, 500 );
		enemy_disp( move_id, skin_id, -700, -500, 30000, 250, 500 );
			break;

		case XL2_YD:		//	X左２	Y下
		enemy_disp( move_id, skin_id, 0, -500, 30000, 250, 500 );
		enemy_disp( move_id, skin_id, -700, -500, 30000, 250, 500 );
			break;

		case XR2_Y:		//	X右２	Y中心
		enemy_disp( move_id, skin_id, 700, 0, 30000, 250, 500 );
		enemy_disp( move_id, skin_id, 0, 0, 30000, 250, 500 );
			break;

		case X2_Y:		//	Xサイド	Y中心
		enemy_disp( move_id, skin_id, 700, 0, 30000, 250, 500 );
		enemy_disp( move_id, skin_id, -700, 0, 30000, 250, 500 );
			break;

		case XL2_Y:		//	X左２	Y中心
		enemy_disp( move_id, skin_id, 0, 0, 30000, 250, 500 );
		enemy_disp( move_id, skin_id, -700, 0, 30000, 250, 500 );
			break;

		case XR2_YU:		//	X右２	Y上
		enemy_disp( move_id, skin_id, 700, 500, 30000, 250, 500 );
		enemy_disp( move_id, skin_id, 0, 500, 30000, 250, 500 );
			break;

		case X2_YU:			//	Xサイド	Y上
		enemy_disp( move_id, skin_id, 700, 500, 30000, 250, 500 );
		enemy_disp( move_id, skin_id, -700, 500, 30000, 250, 500 );
			break;

		case XL2_YU:		//	X左２	Y上
		enemy_disp( move_id, skin_id, 0, 500, 30000, 250, 500 );
		enemy_disp( move_id, skin_id, -700, 500, 30000, 250, 500 );
			break;

		case XR_YD2:		//	X右	Y下2
		enemy_disp( move_id, skin_id, 700, -500, 30000, 250, 500 );
		enemy_disp( move_id, skin_id, 700, 0, 30000, 250, 500 );
			break;

		case X_YD2:			//	X中心	Y下2
		enemy_disp( move_id, skin_id, 0, -500, 30000, 250, 500 );
		enemy_disp( move_id, skin_id, 0, 0, 30000, 250, 500 );
			break;

		case XL_YD2:		//	X左	Y下2
		enemy_disp( move_id, skin_id, -700, -500, 30000, 250, 500 );
		enemy_disp( move_id, skin_id, -700, 0, 30000, 250, 500 );
			break;

		case XR_Y2:			//	X右	Yサンド
		enemy_disp( move_id, skin_id, 700, -500, 30000, 250, 500 );
		enemy_disp( move_id, skin_id, 700, 500, 30000, 250, 500 );
			break;

		case X_Y2:			//	X中心	Yサンド
		enemy_disp( move_id, skin_id, 0, -500, 30000, 250, 500 );
		enemy_disp( move_id, skin_id, 0, 500, 30000, 250, 500 );
			break;

		case XL_Y2:			//	X左	Yサンド
		enemy_disp( move_id, skin_id, -700, -500, 30000, 250, 500 );
		enemy_disp( move_id, skin_id, -700, 500, 30000, 250, 500 );
			break;

		case XR_YU2:		//	X右	Y上2
		enemy_disp( move_id, skin_id, 700, 0, 30000, 250, 500 );
		enemy_disp( move_id, skin_id, 700, 500, 30000, 250, 500 );
			break;

		case X_YU2:			//	X中心	Y上2
		enemy_disp( move_id, skin_id, 0, 0, 30000, 250, 500 );
		enemy_disp( move_id, skin_id, 0, 500, 30000, 250, 500 );
			break;

		case XL_YU2:		//	X左	Y上2
		enemy_disp( move_id, skin_id, -700, 0, 30000, 250, 500 );
		enemy_disp( move_id, skin_id, -700, 500, 30000, 250, 500 );
			break;

		case X3_Y:	// Y座標の真ん中に横一列に３体敵を召喚
		enemy_disp( move_id, skin_id, 700, 0, 30000, 250, 500 );
		enemy_disp( move_id, skin_id, 0, 0, 30000, 250, 500 );
		enemy_disp( move_id, skin_id, -700, 0, 30000, 250, 500 );
			break;

		case X3_YU:	// 半分より上に横一列に３体敵を召喚
			enemy_disp( move_id, skin_id, 700, -500, 30000, 250, 500 );
			enemy_disp( move_id, skin_id, 0, -500, 30000, 250, 500 );
			enemy_disp( move_id, skin_id, -700, -500, 30000, 250, 500 );
			break;

		case X3_YD:	// 半分より下に横一列に３体敵を召喚
			enemy_disp( move_id, skin_id, 700, 500, 30000, 250, 500 );
			enemy_disp( move_id, skin_id, 0, 500, 30000, 250, 500 );
			enemy_disp( move_id, skin_id, -700, 500, 30000, 250, 500 );
			break;

		case X_Y3: // 真ん中に縦一列に３体敵を召喚
			enemy_disp( move_id, skin_id, 0, 0, 30000, 250, 500 );
			enemy_disp( move_id, skin_id, 0, -500, 30000, 250, 500 );
			enemy_disp( move_id, skin_id, 0, 500, 30000, 250, 500 );
			break;

		case XR_Y3: // 右側に縦一列に３体敵を召喚
			enemy_disp( move_id, skin_id, 700, 0, 30000, 250, 500 );
			enemy_disp( move_id, skin_id, 700, -500, 30000, 250, 500 );
			enemy_disp( move_id, skin_id, 700, 500, 30000, 250, 500 );
			break;

		case XL_Y3: // 左側に縦一列に３体敵を召喚
			enemy_disp( move_id, skin_id, -700, 0, 30000, 250, 500 );
			enemy_disp( move_id, skin_id, -700, -500, 30000, 250, 500 );
			enemy_disp( move_id, skin_id, -700, 500, 30000, 250, 500 );
			break;

		case 33:	// 自機の左後ろに敵を一体召喚
			enemy_disp( move_id, skin_id, -1600, 0, -5000, 100, 400 );
			break;

		case 34:	// 自機の右後ろに敵を一体召喚
			enemy_disp( move_id, skin_id, 1600, 0, -5000, 100, 400 );
			break;

/*
	case 8:	// 敵を５体召喚
		enemy_disp( move_id, skin_id, -700, -500, 30000, 250, 500 );
		enemy_disp( move_id, skin_id, -700, 500, 30000, 250, 500 );
		enemy_disp( move_id, skin_id, 0, 0, 30000, 250, 500 );
		enemy_disp( move_id, skin_id, 700, -500, 30000, 250, 500 );
		enemy_disp( move_id, skin_id, 700, 500, 30000, 250, 500 );
		break;
*/
	case 999:	// テスト用
		enemy_disp( move_id, skin_id, 0, 0, 30000, 250, 1 );
		break;
	}
}

void enemy_gen_exec( TASK *ap )
{
	ap->work2[ X ]--;
	if( ap->work3[ X ] <= 0 )	// 指定数敵を発生させたらタスクエンドする。
	{
		TASK_end( ap );
		return;
	}
	else if( ap->work2[ X ] <= 0 )	// 特定の時間経過したら
	{
		if( ap->work3[ X ] > 0 )	// 指定数敵を発生させていない場合
		{
			summon_formation( ap->work1[ X ], ap->work1[ Y ], ap->work1[ Z ] );
			ap->work3[ X ]--;					// 敵を発生させたらカウントダウンする 
			ap->work2[ X ] = ap->work2[ Y ];					// 敵を発生させてら値を初期化する
		}
	}
	if( life == 0 )		// 自機の残基がなくなったらタスクを消す
	{
		TASK_end( ap );
		return;
	}
}

void enemy_gen( SINT32 ct, SINT32 summon_num, SINT32 formation_id, SINT32 move_id, SINT32 skin_id )
{
	TASK *ap;
	ap = TASK_start( enemy_gen_exec, GROUP_UI, "敵のジェネレーター" );
	ap->work1[ X ] = formation_id;
	ap->work1[ Y ] = move_id;
	ap->work1[ Z ] = skin_id;
// 敵の発生のクールタイム
	ap->work2[ X ] = 0;
	ap->work2[ Y ] = ct;
// 敵の連続発生数
	ap->work3[ X ] = summon_num;
}



void annihilation_check( TASK *ap )		// 敵が残っているかを確認
{

}

void enemy_seq_exec( TASK *ap )
{
	TASK *actp;
	SINT32 time;
	SINT32 ct, summon_num, formation_id, move_id, skin_id;
	ap->work1[Y]--;
	if( ap->work1[ Y ] > 0 )	// WAIT TIME 計算
		return;

	if( life <= 0 )				// GAME OVER になったらタスクエンドさせる
	{
		TASK_end( ap );
		return;
	}

	if( game_type == TYPE_CLEAR || game_type == TYPE_OVER )		// リザルト画面に飛んだらこのタスクを消す
	{
		TASK_end( ap );
		return;
	}


	switch ( *ap->work_p[X]++ )
	{
		case SEQ_WAIT:	// wait timeの設定
			time = *ap->work_p[ X ]++;
			ap->work1[ Y ] = time;
			break;

		case SEQ_TOP:	// シーケンスを最初に戻す
			ap->work_p[ X ] = ap->work_p[ Y ];
			break;

		case SEQ_FORMATION:	// 敵の配置番号の指定
			ap->workF[ P ] = *ap->work_p[ X ]++;
			break;

		case SEQ_ENE_MOVE:	// 敵の動きの設定
			ap->workF[ D ] = *ap->work_p[ X ]++;
			break;

		case SEQ_ANNIHILATION: // 敵の全滅確認
			for( actp = ap_start; actp != NULL; actp = actp->next )
				if( actp->task_group == GROUP_ENEMY )
				{
					ap->work_p[ X ]--;
					return;
				}
			break;

		case SEQ_ENE_GEN:	// 敵の出現
			ct = *ap->work_p[ X ]++;
			summon_num = *ap->work_p[ X ]++;
			formation_id = ap->workF[ P ];
			move_id = ap->workF[ D ];
			skin_id = *ap->work_p[ X ]++;
			ap->work1[ Y ] = ct * summon_num + 60;
			enemy_gen( ct, summon_num, formation_id, move_id, skin_id );	// 敵の隊列召喚
			break;

		case SEQ_WARNING:
			warning();
			break;

		case SEQ_BOSS:	// ボスを召喚したあと、シーケンスをタスクエンドさせる
			boss_logo();
//			boss_start();		// ボスの召喚
			TASK_end( ap );
			return;
			break;

		case SEQ_NEXT_STAGE:
			switch( Rand2( 0, 4 ) )
			{
			case 0:
				planet_start(  -5700,  -5780, 32000,   5, Rand2( 0, 3 ), 1.0f );
				break;
			case 1:
				planet_start( -10000,   9000, 34000,   4, Rand2( 0, 3 ), 1.0f );
				break;
			case 2:
				planet_start(   9000,  -9470, 36000,   4, Rand2( 0, 3 ), 1.0f );
				break;
			case 3:
				planet_start(  -5700,   6980, 38000,   5, Rand2( 0, 3 ),  1.0f );
				break;
			}

			stage++;
			break;
	}
}
void enemy_seq( void )
{
	TASK *ap;
	ap = TASK_start( enemy_seq_exec, GROUP_UI, "シーケンス" );
	ap->work_p[ X ] = seq_data;
	ap->work_p[ Y ] = ap->work_p[ X ];
	ap->work1[ Y ] = 0;

// フォーメーションナンバー保存先
	ap->workF[ P ] = 0;
// 敵の動きの番号保存先
	ap->workF[ D ] = 0;

// 背景の流れる速度を初期化
	bg_speed = 1;
}