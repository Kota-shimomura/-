#ifdef WINDOWS_PC
#include    "C:/project/libs/systemOZ_v4/soz.h"
#else
#include    "D:/project/guardians_2dx/proj.win32/src/systemOZ/soz.h"
#endif

#include    "C:/project/bace/src/game/game_include.h"

SINT32 planet_con = 0;
FLOAT bg_speed = 1;

//------------------------------------------------------------------------------------------------------------------------------------------------------
// 飛行している敵の表示
//------------------------------------------------------------------------------------------------------------------------------------------------------
void bg_move_enemy_exec( TASK *ap )
{
	ap->pos[ X ] = ap->vec[ X ];
	ap->pos[ Y ] = ap->vec[ Y ];
	ap->pos[ Z ] = ap->vec[ Z ];
}
void bg_move_enemy( SINT32 skin_id, FLOAT pos_x, FLOAT pos_y, FLOAT pos_z, FLOAT vec_x, FLOAT vec_y, FLOAT vec_z )
{
	TASK *ap;
	ap = TASK_start_MODEL( bg_move_enemy_exec, GROUP_BG, enemy_skin[skin_id].model_no, enemy_skin[skin_id].tex_no, "背景に出てくる敵オブジェクト" )
// 座標やベクトルの初期値を設定する
	ap->pos[ X ] = pos_x;
	ap->pos[ Y ] = pos_y;
	ap->pos[ Z ] = pos_z;
	ap->vec[ X ] = vec_x;
	ap->vec[ Y ] = vec_y;
	ap->vec[ Z ] = vec_z;

// 進行方向を向くようにする
	ap->ang[ X ] = -SOZ_atan2( ap->pos[ Z ], ap->pos[ Y ], ap->pos[ Z ] + ap->vec[ Z ], ap->pos[ Y ] + ap->vec[ Y ] );  
	ap->ang[ Y ] = -SOZ_atan2( ap->pos[ X ], ap->pos[ Z ], ap->pos[ X ] + ap->vec[ X ], ap->pos[ Z ] + ap->vec[ Z ] );  

// マテリアル設定
	ap->specular[ 0 ] = enemy_skin[ skin_id ].specular[ 0 ];
	ap->specular[ 1 ] = enemy_skin[ skin_id ].specular[ 1 ];
	ap->specular[ 2 ] = enemy_skin[ skin_id ].specular[ 2 ];
	ap->ambient[ 0 ]  = enemy_skin[ skin_id ].ambient[ 0 ];
	ap->ambient[ 1 ]  = enemy_skin[ skin_id ].ambient[ 1 ];
	ap->ambient[ 2 ]  = enemy_skin[ skin_id ].ambient[ 2 ];
	ap->emissive[ 0 ] = enemy_skin[ skin_id ].emissive[ 0 ];
	ap->emissive[ 1 ] = enemy_skin[ skin_id ].emissive[ 1 ];
	ap->emissive[ 2 ] = enemy_skin[ skin_id ].emissive[ 2 ];
	ap->diffuse[ 0 ]  = enemy_skin[ skin_id ].diffuse[ 0 ];
	ap->diffuse[ 1 ]  = enemy_skin[ skin_id ].diffuse[ 1 ];
	ap->diffuse[ 2 ]  = enemy_skin[ skin_id ].diffuse[ 2 ];
 	ap->pow = enemy_skin[ skin_id ].pow;
	SOZ_material_setting( ap );
}


//------------------------------------------------------------------------------------------------------------------------------------------------------
// 惑星の表示
//------------------------------------------------------------------------------------------------------------------------------------------------------
void planet_exec( TASK *ap )
{
	ap->pos[ Z ] -= ap->vec[ Z ] *bg_speed;			// 移動
	if( ap->pos[ Z ] < -1500 )				// 自機より後ろになったらタスクエンドさせる。
	{
		planet_con--;
		TASK_end( ap );
		return;
	}
}
void planet_start( FLOAT pos_x, FLOAT pos_y, FLOAT pos_z, FLOAT vec_z, SINT32 type, FLOAT scale )
{
	TASK *ap;
	ap = TASK_start_MODEL( planet_exec, GROUP_BG, MODEL_PLANET_BG, TEXTURE_PLANET_1 + type, "惑星" );
	ap->grp_mode = WRITE_ZBUFFER | TEST_ZBUFFER | USE_LIGHTING | USE_3DPOS;
	ap->pos[ X ] = pos_x;
	ap->pos[ Y ] = pos_y;
	ap->pos[ Z ] = pos_z;
	ap->vec[ Z ] = vec_z;
	ap->scale[ Z ] = ap->scale[ Y ] = ap->scale[ X ] = scale;
	ap->pri = PRI_BG;
	ap->ang[ Z ] = Rand2( 0x0000, 0xffff );
//	マテリアルの設定
	ap->emissive[ 0 ] = 0.25f;
	ap->emissive[ 1 ] = 0.25f;
	ap->emissive[ 2 ] = 0.25f;
	ap->diffuse[ 0 ] = 3.0f;
	ap->diffuse[ 1 ] = 3.0f;
	ap->diffuse[ 2 ] = 3.0f;
	ap->ambient[ 0 ] = 0.05f;
	ap->ambient[ 1 ] = 0.05f;
	ap->ambient[ 2 ] = 0.05f;
	ap->pow = 7.5f;
	SOZ_material_setting( ap );
}

//------------------------------------------------------------------------------------------------------------------------------------------------------
// 星雲の表示
//------------------------------------------------------------------------------------------------------------------------------------------------------
void nebula_disp_exec( TASK *ap )
{
	ap->ang[ Z ] += 0x0001;	//	微妙に回転させる。
}

void nebula_disp( FLOAT pos_x, FLOAT pos_y, ANGLE ang_x, ANGLE ang_y, ANGLE ang_z )
{
	 TASK *ap;
	 ap = TASK_start_GRP( nebula_disp_exec, GROUP_BG, TEXTURE_NEBULA_0, nebula_rect, 0, "星雲表示" );
	 ap->grp_mode = USE_3DPOS;
	 ap->blend_type = BLEND_ADD;
// 初期座標　回転の設定
	 ap->pos[ X ] = pos_x;
	 ap->pos[ Y ] = pos_y;
	 ap->pos[ Z ] = 19000;
	 ap->ang[ X ] = ang_x;
	 ap->ang[ Y ] = ang_y;
	 ap->ang[ Z ] = ang_z;
	 ap->vec[ Z ] = F_Rand2( -10, -1 );
	 ap->scale[ X ] = 25.0f;
	 ap->scale[ Y ] = ap->scale[ X ];
	 ap->pri = PRI_BG - 2000;
}

//------------------------------------------------------------------------------------------------------------------------------------------------------
// 岩のモデル表示
//------------------------------------------------------------------------------------------------------------------------------------------------------
void stone_model_disp_exec( TASK *ap )
{
	ap->work1[ X ]++;	// 出現からの時間計測
// 移動と回転をさせる。
	ap->pos[ Z ] -= ap->vec[ Z ]*bg_speed;
	ap->ang[ X ] += ap->angle[ X ];
	ap->ang[ Y ] += ap->angle[ Y ];
	ap->ang[ Z ] += ap->angle[ Z ];

//　特定時間経過したらタスクエンド
	if( ap->work1[ X ] > 900 )
	{
		TASK_end( ap );
		return;
	}
}
void stone_model_disp(  FLOAT pos_x, FLOAT pos_y, ANGLE ang_x, ANGLE ang_y, ANGLE ang_z  )
{
	SINT32 type = Rand2( 0, 100 ) % 2;
	TASK *ap;
	ap = TASK_start_MODEL( stone_model_disp_exec, GROUP_BG, MODEL_STONE_0 +type, TEXTURE_STONE_0 +type, "岩のモデル表示" );
	ap->grp_mode = WRITE_ZBUFFER | TEST_ZBUFFER | USE_3DPOS;
	ap->pos[ X ] = pos_x + F_Rand2( -500.0f, 500.0f );
	ap->pos[ Y ] = pos_y + F_Rand2( -500.0f, 500.0f );
	ap->pos[ Z ] = 20000.0f;
	ap->vec[ X ] = F_Rand2( -10, 10 );
	ap->vec[ Y ] = F_Rand2( -10, 10 );
	ap->vec[ Z ] = 100;
	ap->ang[ X ] = Rand2( -0xffff, 0xffff );
	ap->ang[ Y ] = Rand2( -0xffff, 0xffff );
	ap->ang[ Z ] = Rand2( -0xffff, 0xffff );
	ap->angle[ X ] = Rand2( -0xff, 0xff );
	ap->angle[ Y ] = Rand2( -0xff, 0xff );
	ap->angle[ Z ] = Rand2( -0xff, 0xff );
	ap->work1[ X ] = 0;
	ap->sphire = 300.0f;
	ap->sphire_shift[ X ] = 0;
	ap->sphire_shift[ Y ] = 0;
	ap->sphire_shift[ Z ] = 0;
	ap->HP = 150;
	ap->SCORE = 500;
	ap->pri = PRI_BG + 100;
	ap->callback = enemy_callback;
}

void nebula_disp_random( SINT32 disp_type, FLOAT pos_x, FLOAT pos_y, ANGLE ang_x, ANGLE ang_y, ANGLE ang_z )
{
	stone_model_disp( pos_x, pos_y, ang_x, ang_y, ang_z );
#if 0			// 複数のオブジェクトの中から、ランダムで呼び出す場合はこちらを使用する
	switch( disp_type )
	{
		case 0:		// 隕石
			stone_model_disp( pos_x, pos_y, ang_x, ang_y, ang_z );
			break;

		case 1:
			break;

		case 2:
			break;
	}
#endif
}


void nebula_gen_start( void )
{
	SINT32 disp_type = Rand2( 0, 3 ), pos_type = Rand2( 0, 8 );
	switch( pos_type )		// ある程度座標を指定した場所にオブジェクトを生成する。
	{
		case 0: // 下
			nebula_disp_random( disp_type, 0, -900.0f, 0x8000, 0x0000, 0x0000 );
			break;

		case 1: // 右下
			nebula_disp_random( disp_type, 900.0f, -900.0f, 0x8000, 0x0000, 0x0000 );
			break;

		case 2:	// 右
			nebula_disp_random( disp_type, 900.0f, 0.0f, 0x8000, 0x0000, 0x4000 );
			break;

		case 3:	// 右上
			nebula_disp_random( disp_type, 900.0f, 900.0f, 0x8000, 0x0000, 0x0000 );
			break;

		case 4: // 上
			nebula_disp_random( disp_type, 0, 900.0f, 0x8000, 0x0000, 0x0000 );
			break;

		case 5: // 左上
			nebula_disp_random( disp_type, -900.0f, 900.0f, 0x8000, 0x0000, 0x0000 );
			break;

		case 6: // 左
			nebula_disp_random( disp_type, -900.0f,0.0f, 0x8000, 0x0000, 0x0000 );
			break;

		case 7:	// 左下
			nebula_disp_random( disp_type, -900.0f, -900.0f, 0x8000, 0x0000, 0x0000 );
			break;
	}
}


//------------------------------------------------------------------------------------------------------------------------------------------------------
// 
//			背景/地面
// 
//------------------------------------------------------------------------------------------------------------------------------------------------------
void universe_planet_disp_exec( TASK *ap )
{
	ap->work1[ X ]++;						// 時間計測
	illusion_start( ap, 25, BLEND_ADD );	// 残像表示
	ap->pos[ Z ] -= 500.0f *bg_speed;					// 座標移動
	if( ap->work1[ X ] > 360 )				// 特定時間経過後にタスクエンド
	{
		TASK_end( ap );
		return;
	}
	if( ap->work1[ X ] == ap->work1[ Y ] )
		switch ( Rand2( 0, 4 ) )
		{
			case 0:
				break_bom_effect( ap->pos[ X ] + F_Rand2( -EFF_RAND_POS, EFF_RAND_POS ), ap->pos[ Y ] + F_Rand2( -EFF_RAND_POS, EFF_RAND_POS ), ap->pos[ Z ] + F_Rand2( -EFF_RAND_POS, EFF_RAND_POS ) );
				break;

			case 1:
				break_effect( ap->pos[ X ] + F_Rand2( -EFF_RAND_POS, EFF_RAND_POS ), ap->pos[ Y ] + F_Rand2( -EFF_RAND_POS, EFF_RAND_POS ), ap->pos[ Z ] + F_Rand2( -EFF_RAND_POS, EFF_RAND_POS ) );
				break;

			case 2:
				break_effect_02( ap->pos[ X ] + F_Rand2( -EFF_RAND_POS, EFF_RAND_POS ), ap->pos[ Y ] + F_Rand2( -EFF_RAND_POS, EFF_RAND_POS ), ap->pos[ Z ] + F_Rand2( -EFF_RAND_POS, EFF_RAND_POS ) );
				break;

			case 3:
				break;
		}
}
void universe_planet_disp( FLOAT pos_x, FLOAT pos_y )
{
	TASK *ap;
	ap = TASK_start_MODEL( universe_planet_disp_exec, GROUP_BG, MODEL_PLANET, TEXTURE_PLANET, "飛んでる惑星" );
	ap->grp_mode = WRITE_ZBUFFER | TEST_ZBUFFER | USE_3DPOS;// | USE_LIGHTING;
	ap->blend_type = BLEND_ADD;
	ap->pos[ X ] = pos_x;
	ap->pos[ Y ] = pos_y;
	ap->pos[ Z ] = 30000.0f;
	ap->pri = PRI_BG -100;
	ap->work1[ X ] = 0;
	ap->work1[ Y ] = Rand2( 2, 300 );
	ap->scale[ X ] = F_Rand2( 2.0f, 4.0f );
	ap->scale[ Z ] = ap->scale[ Y ] = ap->scale[ X ];
}

void universe_gen_exec( TASK *ap )	// 宇宙空間の演出
{
	ap->work1[ X ] ++;					// フレーム計算
	if( ap->work1[ X ] % 16 == 0 )		// 周りの飛んでくる星を召喚する
	{
		universe_planet_disp( F_Rand2(	-7000,	-5000 ), F_Rand2(	-1500,  1500 ) );
		universe_planet_disp( F_Rand2(	 5000,	 7000 ), F_Rand2(	-1500,  1500 ) );
		universe_planet_disp( F_Rand2(	-4000,	 4000 ), F_Rand2(	-5000, -3000 ) );
		universe_planet_disp( F_Rand2(	-4000,	 4000 ), F_Rand2(	 5000,  3000 ) );
	}
	if( planet_con < 3 )
	{
		do
		ap->work2[ X ] = Rand2( 0, 4 );
		while( ap->work2[ X ] != ap->work2[ Y ] );
		if( ap->work2[ X ] != ap->work2[ Y ] )
		{
			ap->work2[ Y ] = ap->work2[ X ];
			switch( ap->work2[ X ] )
			{
			case 0:
				planet_start(  F_Rand2( -10000, -5700 ),  F_Rand2( -10000, -5700 ), F_Rand2( 32000.0f, 42000.0f ) ,   5, Rand2( 0, 3 ), 1.0f );
				break;
			case 1:
				planet_start(  F_Rand2( -10000, -5700 ),  F_Rand2( 57000, -10000 ), F_Rand2( 32000.0f, 42000.0f ) ,   5, Rand2( 0, 3 ), 1.0f );
				break;
			case 2:
				planet_start(  F_Rand2( 57000, 10000 ),  F_Rand2( -10000, -5700 ), F_Rand2( 32000.0f, 42000.0f ) ,   5, Rand2( 0, 3 ), 1.0f );
				break;
			case 3:
				planet_start(  F_Rand2( 57000, 10000 ),  F_Rand2( 5700, 10000 ), F_Rand2( 32000.0f, 42000.0f ) ,   5, Rand2( 0, 3 ), 1.0f );
				break;
			}
			planet_con++;
		}
	}

	if( life == 0 )
	{
		TASK_end( ap );
		return;
	}
}
void universe_gen( void )
{
	TASK *ap;
	ap = TASK_start( universe_gen_exec, GROUP_BG, "宇宙空間のジェネレーター" );
//	univers_model_disp( 5000 );
	nebula_gen_start();
	ap->work1[ X ] = 350;
	ap->work2[ X ] = 0;
	ap->work2[ Y ] = 0;
	nebula_disp( -900.0f, -900.0f, 0x8000, 0x0000, 0x0000 );		// 巨大な星雲を表示させる
}

