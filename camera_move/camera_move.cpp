#ifdef WINDOWS_PC
#include    "C:/project/libs/systemOZ_v4/soz.h"
#else
#include    "D:/project/guardians_2dx/proj.win32/src/systemOZ/soz.h"
#endif

#include    "C:/project/bace/src/game/game_include.h"

//---------------------------------------------------------------------------------------------------------------------------------------
// カメラの振動を発生させる
//---------------------------------------------------------------------------------------------------------------------------------------

//---------------------------------------------------------------------------------------------------------------------------------------
// カメラ振動　強
//---------------------------------------------------------------------------------------------------------------------------------------
void camera_vibration_strength_exec( TASK *ap )
{
	ap->work1[ Z ] ++;					// フレーム計算
	camera_x[ 0 ] += ap->work1[ X ];	// カメラの座標をずらす
	camera_y[ 0 ] += ap->work1[ Y ];
	ap->work1[ X ] *= -1;
	ap->work1[ Y ] *= -1;
	if( ap->work1[ Z ] >= 12 )			// 特定フレームを超えたらタスクを終わらせる
	{
		TASK_end( ap );
		return;
	}
	SOZ_camera_move( 0 );
}
void camera_vibration_strength( void )
{
	TASK *ap;
	ap = TASK_start( camera_vibration_strength_exec, GROUP_UI, "カメラ振動　強" );
	ap->work1[ X ] = 200;	// カメラの座標計算で使用する値
	ap->work1[ Y ] = 50;	// カメラの座標計算で使用する値
	ap->work1[ Z ] = 0;		// 振動時間計測用
}

//---------------------------------------------------------------------------------------------------------------------------------------
// カメラ振動　中
//---------------------------------------------------------------------------------------------------------------------------------------
void camera_vibration_medium_exec( TASK *ap )
{
	ap->work1[ Z ] ++;					// フレーム計算
	camera_x[ 0 ] += ap->work1[ X ];	// カメラの座標をずらす
	camera_y[ 0 ] += ap->work1[ Y ];
	ap->work1[ X ] *= -1;
	ap->work1[ Y ] *= -1;
	if( ap->work1[ Z ] >= 10 )			// 特定フレームを超えたらタスクを終わらせる
	{
		TASK_end( ap );
		return;
	}
	SOZ_camera_move( 0 );
}
void camera_vibration_medium( void )
{
	TASK *ap;
	ap = TASK_start( camera_vibration_medium_exec, GROUP_UI, "カメラ振動　中" );
	ap->work1[ X ] = 100;	// カメラの座標計算で使用する値
	ap->work1[ Y ] = 25;		// カメラの座標計算で使用する値
	ap->work1[ Z ] = 0;		// 振動時間計測用
}

//---------------------------------------------------------------------------------------------------------------------------------------
// カメラ振動　弱
//---------------------------------------------------------------------------------------------------------------------------------------
void camera_vibration_weak_exec( TASK *ap )
{
	ap->work1[ Z ] ++;					// フレーム計算
	camera_x[ 0 ] += ap->work1[ X ];	// カメラの座標移動
	ap->work1[ X ] *= -1;
	if( ap->work1[ Z ] >= 6 )			// 特定フレームを超えたらタスクを終わらせる
	{
		TASK_end( ap );
		return;
	}
	SOZ_camera_move( 0 );
}
void camera_vibration_weak( void )
{
	TASK *ap;
	ap = TASK_start( camera_vibration_weak_exec, GROUP_UI, "カメラ振動　弱" );
	ap->work1[ X ] = 10;	// カメラの座標計算で使用する値
	ap->work1[ Z ] = 0;		// 振動時間計測用
}
