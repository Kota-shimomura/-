extern void enemy_seq( void );

#define SEQ_WAIT			0
#define SEQ_TOP				1
#define SEQ_ENE_GEN			2
#define SEQ_FORMATION		3
#define SEQ_ANNIHILATION	4
#define SEQ_ENE_MOVE		5
#define SEQ_BOSS			6
#define SEQ_NEXT_STAGE		7
#define SEQ_WARNING			8

#define WAIT_TIME( wait_time ) SEQ_WAIT, wait_time
#define NEXT_WAVE	SEQ_WAIT, 240
#define ENE_GEN( ct, summon_num, skin_id ) SEQ_ENE_GEN, ct, summon_num, skin_id
#define FORMATION( type )	SEQ_FORMATION, type
#define ANNIHILATION_CHECK		SEQ_ANNIHILATION	// 全滅チェック
#define ENE_MOVE( ene_move )			SEQ_ENE_MOVE, ene_move
#define SUMMON_BOSS			SEQ_BOSS
#define NEXT_STAGE			SEQ_NEXT_STAGE


#define XR_YD	0		// 右下
#define X_YD	1		// 下
#define XL_YD	2		// 左下
#define XR_Y	3		// 右
#define X_Y		4		// 中心
#define XL_Y	5		// 左
#define XR_YU	6		// 右上
#define X_YU	7		// 上
#define XL_YU	8		// 左上

#define XR2_YD	9		// 右下 | 下
#define X2_YD	10		// 右下 | 左下
#define XL2_YD	11		// 左下 | 下
#define XR2_Y	12		// 右　 | 中心
#define X2_Y	13		// 右　 | 左
#define XL2_Y	14		// 左　 | 中心
#define XR2_YU	15		// 右上 | 上
#define X2_YU	16		// 右上 | 左上
#define XL2_YU	17		// 左上 | 上

#define XR_YD2	18		// 右下	| 右
#define X_YD2	19		// 下	| 中心
#define XL_YD2	20		// 左下	| 左
#define XR_Y2	21		// 右	| 右上
#define X_Y2	22		// 下	| 上
#define XL_Y2	23		// 左	| 左上
#define XR_YU2	24		// 右上	| 右
#define X_YU2	25		// 上	| 中心
#define XL_YU2	26		// 左上	| 左

#define X3_YU	27		// 横一列 | 上
#define X3_Y	28		// 横一列 | 中心
#define X3_YD	29		// 横一列 | 下

#define XR_Y3	30		// 右	| 縦一列
#define X_Y3	31		// 中心	| 縦一列
#define XL_Y3	32		// 左	| 縦一列

#define XL_B	33		// 左後ろ
#define XR_B	34		// 右後ろ



