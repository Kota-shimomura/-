#ifdef WINDOWS_PC
#include    "C:/project/libs/systemOZ_v4/soz.h"
#else
#include    "D:/project/guardians_2dx/proj.win32/src/systemOZ/soz.h"
#endif

#include    "C:/project/bace/src/game/game_include.h"

//------------------------------------------------------------------------------------------------------------------------------------------------------
// 
//			破壊時のcallback
// 
//------------------------------------------------------------------------------------------------------------------------------------------------------
void bullet_gen_callback( TASK *actp, TASK *gen ) //( TASK *gen, TASK *actp )
{
	break_effect( gen->pos[ X ], gen->pos[ Y ], gen->pos[ Z ] );
	gen->HP -= actp->ATK;
	if( gen->HP <= 0 )
	{
		score += gen->SCORE + bonus;	// SCOREを増やす
		bonus += gen->SCORE/100;		// SCOREBONUSをつける
		break_effect_02( gen->pos[ X ], gen->pos[ Y ], gen->pos[ Z ] );
		TASK_end( gen );
	}
//	TASK_end( actp );
	return;
}

// 自機の破壊演出
void my_ship_callback( TASK *ap, TASK *actp )
{
	if( ap->workA[ X ] == 1 )
	{
		life--;															// ライフを減らす
		ap->workA[ X ] = 2;
		ap->workA[ Y ] = 120; 
		if( life > 0 )
		{
			my_ship_tex_chenge( ap );
			camera_vibration_medium();									// カメラ振動　中
			SOZ_play_se( SE_BREAK, 2.0f, 1, 1.0f );						// 効果音を鳴らす
			break_effect( ap->pos[ X ], ap->pos[ Y ], ap->pos[ Z ] );	// 爆発エフェクト
		}
		else
		{
			camera_vibration_strength();								// カメラ振動　強
			ap->workA[ X ] = 3;
		}
	}
}

// ミサイルの破壊演出
void missile_callback( TASK *missile, TASK *none )
{
	if( rest_missile < 99 )
		rest_missile++;												// ミサイルヒット時　補充する
	camera_vibration_weak();									// カメラ振動　弱
	break_effect_02( missile->pos[ X ], missile->pos[ Y ], missile->pos[ Z ] );		// 爆破エフェクト
	TASK_end( missile );
	return;
}

// 弾の破壊演出
void shot_callback( TASK *shot, TASK *none )
{
	TASK_end( shot );
	return;
}

// 敵の撃破演出
void enemy_callback( TASK *shot, TASK *enemy )
{
	SINT32 add_score = 0;
	switch ( enemy->task_group )
	{
		case GROUP_ENEMY:	// 自機の弾と敵があたったとき
			enemy->HP -= shot->ATK;	// 敵にダメージを与える
			if( enemy->HP < 0 )	// 敵の体力が0以下になった時
			{
				add_score = SINT32( ( enemy->SCORE + enemy->pos[ Z ] + bonus ) *( 1 + life*10 ) );
				// 指定の数ショットで敵を倒したらミサイル一個補充
				if( shot->model_no == MODEL_SHOT )
					shot_break_count++;
				else
					add_score *=2;
				if( shot_break_count % 5 == 0 && rest_missile < 99 )
					rest_missile++;

				score += add_score;						// SCOREを増やす
				add_score_disp( add_score, enemy->pos[ X ], enemy->pos[ Y ], enemy->pos[ Z ] );	// 増えるスコアを表示
				bonus += enemy->SCORE/shot->BONUS;		// SCOREBONUSをつける
				SOZ_play_se( SE_BREAK, 4.0f, 1, 1.0f );	// 効果音を鳴らす
				SOZ_play_se( SE_BREAK_2, 4.0f, 1, 1.0f );	// 効果音を鳴らす
				break_effect_02( enemy->pos[ X ], enemy->pos[ Y ], enemy->pos[ Z ] );	// 破壊のエフェクトを表示
//				break_bom_effect( enemy->pos[ X ], enemy->pos[ Y ], enemy->pos[ Z ] );	// 破壊のエフェクトを表示
				TASK_end( enemy );
			}
			else
			{
				enemy->workE[ D ] = 0;
				shot_hit_effect( shot->pos[ X ], shot->pos[ Y ], shot->pos[ Z ] );	// ヒットエフェクトの表示
				SOZ_play_se( SE_SHOT, 5.0f, 1, 1 );									// ヒット時の効果音を鳴らす
			}
			return;
			break;
	}
}

// ボスの撃破演出
void boss_callback( TASK *shot, TASK *enemy )
{
		enemy->HP -= shot->ATK;	// 敵にダメージを与える
		if( enemy->HP < 0 )	// 敵の体力が0以下になった時
		{
			enemy->workA[ X ] = 4;
			jiki->workA[ X ] = 4;
			game_type = TYPE_CLEAR;
		}
		else
		{
			enemy->workE[ D ] = 0;
			shot_hit_effect( shot->pos[ X ], shot->pos[ Y ], shot->pos[ Z ] );	// ヒットエフェクトの表示
			SOZ_play_se( SE_SHOT, 5.0f, 1, 1 );									// ヒット時の効果音を鳴らす
		}
		return;
}

