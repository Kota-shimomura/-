//------------------------------------------------------------------------------------------------------------------------------------------------------
//                systemOZ Ver4
//									エフェクト
//														programed by Shimomura Kota
//------------------------------------------------------------------------------------------------------------------------------------------------------
#ifdef WINDOWS_PC
#include    "C:/project/libs/systemOZ_v4/soz.h"
#else
#include    "D:/project/guardians_2dx/proj.win32/src/systemOZ/soz.h"
#endif

#include    "C:/project/panzer/src/game/game_include.h"

//----------ランダムで左右反転-----------------
void random_flip( TASK *ap )
{
	ap->workA[ X ] = Rand2( 1, 100 );
	if( ap->workA[ X ] % 2 == 1 )
		orFLG( ap->grp_mode, FLIP_LR );
	else
		clrFLG( ap->grp_mode, FLIP_LR );

}

void smoke_effect_exec( TASK *ap )
{
	ap->world_pos[ X ] += -ap->vec[ X ];
	ap->world_pos[ Y ] += -ap->vec[ Y ];
	ap->pos[ Z ] ++;
	ap->scale[ X ] += F_Rand2( 0.1f, 0.25f );
	ap->scale[ Y ] += F_Rand2( 0.1f, 0.25f );
	ap->pri += 50;
	ap->workB[ Y ]++;
	if( ap->workB[ Y ] % 3 == 1 )
		ap->base_color[ 0 ][ 0 ] -= Rand2( 5, 20 );
	if( ap->base_color[ 0 ][ 0 ] < 5 )
	{
		TASK_end( ap );
		return;
	}
	pos_set( ap );
}
void smoke_effect( FLOAT world_x, FLOAT world_y, SINT32 ang_z )
{
	FLOAT rand_vec_x = SOZ_get_cos( ang_z ) * F_Rand2( -2.0f, 2.0f );
	FLOAT rand_vec_y = SOZ_get_sin( ang_z ) * F_Rand2( -2.0f, 2.0f );
	TASK *ap;
	ap = TASK_start_GRP( smoke_effect_exec, 0, TEX_EFFECT, sand_rect, 1, "砂煙エフェクト" );
	ap->world_pos[ X ] = world_x;
	ap->world_pos[ Y ] = world_y;
	pos_set( ap );
	ap->pos[ Z ] = 0;
	ap->vec[ X ] = rand_vec_x;
	ap->vec[ Y ] = rand_vec_y;
		/*
	ap->world_pos[ X ] = world_x;
	ap->world_pos[ Y ] = world_y;
	pos_set( ap );
	*/
	//vec_setting( ap, 2.0f );
//	ap->delay = Rand2( 0, 30 );
	ap->base_color[ 0 ][ 0 ] = 0xff;
	ap->scale[ X ] += F_Rand2( 0.1f, 0.15f );
	ap->scale[ Y ] += F_Rand2( 0.1f, 0.15f );
	ap->pri = 1970 *WP ;
	ap->workB[ Y ] = 0;
	ap->shader_pass = 101;
}

//--------------------------------------------------------------------------------------------------------------------------------
//	砂煙エフェクト
//--------------------------------------------------------------------------------------------------------------------------------
void sand_effect_exec( TASK *ap )
{
	ap->pri += WP;
	ap->world_pos[ X ] -= ap->vec[ X ];
	ap->world_pos[ Y ] -= ap->vec[ Y ];
	ap->pos[ Z ] ++;
	ap->scale[ X ] *= F_Rand2( 1.01f, 1.03f );//1.01f;
	ap->scale[ Y ] *= F_Rand2( 1.01f, 1.03f );
	ap->base_color[ 0 ][ 0 ] -= 2;
	if( ap->base_color[ 0 ][ 0 ] < 10 )
	{
		TASK_end( ap );
		return;
	}
	pos_set( ap );
}
void sand_effect( FLOAT x, FLOAT y, SINT32 ang )
{
	TASK *ap;
	ap = TASK_start_GRP( sand_effect_exec, 0, TEX_EFFECT, sand_rect, 0, "砂煙エフェクト" );
	ap->world_pos[ X ] = x;
	ap->world_pos[ Y ] = y;
	ap->pos[ Z ] = 0;
	pos_set( ap );
	ap->vec[ X ] = -jiki->vec[ X ];
	ap->vec[ Y ] = -jiki->vec[ Y ];
	//ap->pri = PRI_SMOKE;
	ap->pri = PRI_JIKI - 75 *WP;
	ap->base_color[ 0 ][ 0 ] = Rand2( 0x22, 0x88 );//0xff;
	ap->shader_pass = 101;
	ap->scale[ X ] = F_Rand2( 1.0f, 4.0f );//1.0f;
	ap->scale[ Y ] = ap->scale[ X ];

	ap->workA[ X ] = 0;	//カウント用
}
void sand_smoke( FLOAT x, FLOAT y, SINT32 ang )
{
	if( j_state[0].lRz < -100 || j_state[0].lRz > 100 )
		sand_effect( x, y, ang );
}

//--------------------------------------------------------------------------------------------------------------------------------
//	砲撃ヒットエフェクト
//--------------------------------------------------------------------------------------------------------------------------------
void hit_flash_exec( TASK * ap )
{
	ap->pri--;
	ap->workA[ X ]++;
	if( ap->workA[ X ] >= 10 )
	{
		TASK_end( ap );
		return;
	}
	pos_set( ap );
}
void hit_flash( FLOAT pos_x, FLOAT pos_y )
{
	TASK *ap;
	ap = TASK_start_GRP( hit_flash_exec, 0, TEX_EFFECT, hit_effect_rect, 2, "砲撃ヒット時のフラッシュエフェクト" );
	ap->world_pos[ X ] = pos_x;
	ap->world_pos[ Y ] = pos_y;
	ap->scale[ X ] = 6.0f;
	ap->scale[ Y ] = ap->scale[ X ];
	ap->pri = 12000*WP;
	ap->base_color[ 0 ][ 0 ] = 100;
	ap->workA[X] = 0;
	ap->shader_pass = 100;
	SOZ_play_se( SE_HIT, 1.0f, 0, 0 );
	pos_set( ap );
}

void hit_effect_exec( TASK * ap )
{
	ap->pri-= WP;
	ap->workA[ X ]++;
	if( ap->workA[ X ] == 5 )
		ap->anime_no = 1;
	if( ap->anime_no == 1 )
		ap->base_color[ 0 ][ 0 ] -= 25;
	if( ap->base_color[ 0 ][ 0 ] < 10 )
	{
		TASK_end( ap );
		return;
	}
	pos_set( ap );
}
void hit_effect( FLOAT world_x, FLOAT world_y ) 
{
	TASK *ap;
	ap = TASK_start_GRP( hit_effect_exec, 0, TEX_EFFECT, hit_effect_rect, 0, "砲撃ヒット時のエフェクト" );
	ap->world_pos[ X ] = world_x;
	ap->world_pos[ Y ] = world_y;
	ap->scale[ X ] = 2.0f;
	ap->scale[ Y ] = ap->scale[ X ];
	ap->pri = PRI_HIT_EFFECT;
	ap->base_color[ 0 ][ 0 ] = 255;
	ap->workA[X] = 0;
	hit_flash( world_x, world_y );
	pos_set( ap );
}

//--------------------------------------------------------------------------------------------------------------------------------
//	砲撃エフェクト
//--------------------------------------------------------------------------------------------------------------------------------
void shot_bom_effect_exec( TASK *ap )
{
	ap->pri++;
	ap->base_color[0][0] -= 5;
	if( ap->base_color[ 0 ][ 0 ] < 10 )
	{
		TASK_end( ap );
		return;
	}
}

void shot_bom_effect( FLOAT pos_x, FLOAT pos_y )
{
	TASK *ap;
	ap = TASK_start_GRP( shot_bom_effect_exec, 0, TEX_EFFECT, shot_bom_rect, 0, "砲撃爆発のエフェクト" );
	ap->pos[ X ] = pos_x + F_Rand2( -32.0f, 32.0f );
	ap->pos[ Y ] = pos_y + F_Rand2( -32.0f, 32.0f );
	ap->ang[ Z ] = Rand2( 0x0000, 0xffff );
	ap->pri = PRI_SHOT_EFFECTT + 10;
}

void shot_bom( FLOAT pos_x, FLOAT pos_y )
{
	int time;
	for( time = 0; time < 60;time += 2 )
	{
		time--;
	}
	for( int con = 0; con < 50; con++ )
		shot_bom_effect( pos_x, pos_y );
	return;
}

void shot_effect_e_exec( TASK *ap )
{
	ap->work1[ X ] ++;
	if( ap->work1[ X ] % 7 == 1 )
		ap->anime_no++;
	if ( ap->anime_no > 2 )
		task_end_set( ap );
}
void shot_effect_e( FLOAT pos_x, FLOAT pos_y, SINT32 ang )
{
	TASK *ap;
	ap = TASK_start_GRP( shot_effect_e_exec, 0, TEX_EFFECT, shot_effect_rect, 0, "弾発射時の煙" );
	ap->ang[ Z ] = ang;
	ap->pos[ X ] = pos_x - SOZ_get_sin( -ap->ang[Z] ) * 75;
	ap->pos[ Y ] = pos_y - SOZ_get_cos( -ap->ang[Z] ) * 75;
	ap->scale[ X ] = 2.0f;
	ap->scale[ Y ] = ap->scale[ X ];
	ap->pri = PRI_SHOT_EFFECTT;

	ap->work1[ X ] = 0; 
}

//--------------------------------------------------------------------------------------------------------------------------------
//	弾を撃ったときの煙
//--------------------------------------------------------------------------------------------------------------------------------
void shot_effect_exec( TASK *ap )
{
	ap->work1[ X ] ++;
	if( ap->work1[ X ] % 3 == 1 )
	{
		random_flip( ap );
//-----------アニメーションを次へ--------------
		ap->anime_no++;
	}

//----アニメーションが最後ならタスクエンド-----
	if ( ap->anime_no > 4 )
		task_end_set( ap );
	pos_set( ap );
}
void shot_effect( FLOAT world_pos_x, FLOAT world_pos_y, SINT32 ang )
{
	TASK *ap;
	ap = TASK_start_GRP( shot_effect_exec, 0, TEX_EFFECT, shot_effect_rect, 0, "弾発射時の煙" );
	ap->delay = 1;
	ap->ang[ Z ] = ang + 0x4000;
	ap->world_pos[ X ] = world_pos_x - SOZ_get_sin( -ap->ang[Z] ) * 200;
	ap->world_pos[ Y ] = world_pos_y - SOZ_get_cos( -ap->ang[Z] ) * 200;
	ap->scale[ X ] = 3.5f;
	ap->scale[ Y ] = ap->scale[ X ];
	ap->pri = PRI_SHOT_EFFECTT;
	ap->blend_type = BLEND_ADD;
	ap->work1[ X ] = 0; 
	random_flip( ap );
	pos_set( ap );
}


//--------------------------------------------------------------------------------------------------------------------------------
//	爆発
//--------------------------------------------------------------------------------------------------------------------------------
void break_bom_exec( TASK *ap )
{
	ap->pri--;
	ap->work1[ X ] ++;
	if ( ap->work1[X] == 7 )
	{
		ap->anime_no++;
		ap->work1[ X ] = 0;
	}
	if( ap->anime_no >= 12 )
		task_end_set( ap );
	pos_set( ap );
}
void break_bom( FLOAT x, FLOAT y, FLOAT scale )
{
	TASK *ap;
	ap = TASK_start_GRP( break_bom_exec, 0, TEX_HIT_BOM, break_rect, 0, "攻撃ヒット時と敵撃破時の爆発エフェクト" );
	ap->world_pos[ X ] = x;
	ap->world_pos[ Y ] = y;
	ap->pri = PRI_HIT_EFFECT;
	ap->work1[ X ] = 0;
	ap->scale[ X ] = scale;
	ap->scale[ Y ] = ap->scale[ X ]; 
	SOZ_play_se( SE_BREAK, 1.0f, 0, 0 );
	pos_set( ap );
}

