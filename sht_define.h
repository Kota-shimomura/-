//------------------------------------------------------------------------------------------------------------------------------------------------------
// define 定義
//------------------------------------------------------------------------------------------------------------------------------------------------------

//------------------------------------------------------------------------------------------------------------------------------------------------------
// GAMETYPE
//------------------------------------------------------------------------------------------------------------------------------------------------------
#define TYPE_CONFIG		 80
#define TYPE_TITLE		100
#define TYPE_MENU		200
#define TYPE_CUSTOM		300
#define TYPE_RANKING	400
#define TYPE_GAME		500
#define TYPE_OPTION		600
#define TYPE_CLEAR		700
#define TYPE_OVER		800
#define TYPE_END		900

#define TYPE_NEW_DATA	1500

#define TYPE_DEMO		10000

//------------------------------------------------------------------------------------------------------------------------------------------------------
// TUTORIAL_FLAG
//------------------------------------------------------------------------------------------------------------------------------------------------------
#define TUTORIAL_ALL_CLEAR	0		// 全チュートリアルデータ初期化
#define TUTORIAL_START		1 << 0	// ゲームスタート選択
#define TUTORIAL_LR			1 << 1	// 左右移動
#define TUTORIAL_UD			1 << 2	// 上下移動
#define TUTORIAL_SHOT		1 << 3	// バルカン攻撃
#define TUTORIAL_MISSILE	1 << 4	// ミサイル攻撃
#define TUTORIAL_CUSTOM		1 << 5	// メニューの CUSTOM 開放
#define TUTORIAL_CUSTOM_END	1 << 6	// CUSTOM チュートリアル完了
#define TUTORIAL_RANK		1 << 7	// メニューの RANKING 開放
#define TUTORIAL_RANK_END	1 << 8	// RANKING チュートリアル完了
#define TOTORIAL_NONE		1 << 20 // 無条件開放


//------------------------------------------------------------------------------------------------------------------------------------------------------
// 効果音
//------------------------------------------------------------------------------------------------------------------------------------------------------
#define SE_SHOT_HIT		0
#define SE_SHOT			1
#define SE_BREAK		2
#define SE_BREAK_BOM	3
#define SE_SERECT		4
#define SE_DECISION		5
#define SE_CANCEL		6
#define SE_TAKE_OFF		7
#define SE_WARNING		8
#define SE_MISSILE		9
#define SE_SHOT_2		10
#define SE_BREAK_2		11
#define SE_BOSS_CODE	12
#define SE_SPARK		13
#define SE_DAMAGE		14
#define SE_BOSS_BIT		15

//------------------------------------------------------------------------------------------------------------------------------------------------------
// 描画優先順位
//------------------------------------------------------------------------------------------------------------------------------------------------------
#define PRI_BG			-9999*WP
#define PRI_SHOT_EFFECT	 200*WP
#define PRI_ENEMY		 400*WP
#define PRI_BREAK_EFFECT 450*WP
#define PRI_HIT_EFFECT	 500*WP
#define PRI_MISSILE		 600*WP
#define PRI_MISSILE_EFFE 630*WP
#define PRI_MISSILE_SHOT 660*WP
#define PRI_SHOT		 900*WP
#define PRI_JIKI		1000*WP
#define PRI_BURNER		1100*WP
#define PRI_JIKI_BREAK	1200*WP

#define PRI_UI		10000*WP
#define PRI_UI_FONT 11000*WP

//------------------------------------------------------------------------------------------------------------------------------------------------------
// 自機関連
//------------------------------------------------------------------------------------------------------------------------------------------------------
#define JIKI_xP	20
#define SPEED	100
#define POS_LIMIT 1600.0f
#define POS_LIMIT2 800.0f
#define ANG_LIMIT 0x2000
#define ANG_LIMIT2	0x0600
#define ANGLE_Z		0x0300
#define ANGLE_X		0x0100
//#define ANG_LIMIT 0x3000

#define SHOT_DAMAGE	50


//------------------------------------------------------------------------------------------------------------------------------------------------------
// キーコンフィグ
//------------------------------------------------------------------------------------------------------------------------------------------------------
#define PADDIK_UP			0		// 上
#define PADDIK_DOWN			1		// 下
#define PADDIK_RIGHT		2		// 右
#define PADDIK_LEFT			3		// 左
#define PADDIK_MAIN_ATTACK	4		// メインのバルカン
#define PADDIK_SUB_MISSILE	5		// ミサイル発射ボタン
#define PADDIK_DECIDE		6		// 決定
#define PADDIK_CANCEL		7		// キャンセル


//------------------------------------------------------------------------------------------------------------------------------------------------------
// グループナンバー
//------------------------------------------------------------------------------------------------------------------------------------------------------
#define GROUP_UI			0
#define GROUP_MY_SHIP		1
#define GROUP_ENEMY			2
#define GROUP_SHOT			3
#define GROUP_BG			4
#define GROUP_BULLET		5

//------------------------------------------------------------------------------------------------------------------------------------------------------
// モデル番号
//------------------------------------------------------------------------------------------------------------------------------------------------------
#define MODEL_MY_SHIP		1
#define MODEL_ENE_00		2
#define MODEL_ENE_01		3
#define MODEL_SHOT			4
#define MODEL_FLOOR			5
#define MODEL_BASE			6
#define MODEL_PLANET		7
#define MODEL_STONE_0		8
#define MODEL_STONE_1		9
#define MODEL_BOSS			10
#define MODEL_ENE_MS		11
#define MODEL_MISSILE		12
#define MODEL_PLANET_BG		13
#define MODEL_BULLET_GEN	14
#define MODEL_ENE_02		15
#define MODEL_ENE_03		16
#define MODEL_ENE_04		17
#define MODEL_ENE_05		18
#define MODEL_ENE_06		19
#define MODEL_ENE_07		20

//------------------------------------------------------------------------------------------------------------------------------------------------------
// テクスチャナンバー
//------------------------------------------------------------------------------------------------------------------------------------------------------
#define TEXTURE_MY_SHIP		1
#define TEXTURE_ENE_00		2
#define TEXTURE_ENE_01		3
#define TEXTURE_SHOT		4
#define TEXTURE_EFFECT		5
#define TEXTURE_HIT_EFF		TEXTURE_EFFECT
#define TEXTURE_FLOOR_0		6
#define TEXTURE_UI_FONT		7
#define TEXTURE_LOGO		8
#define TEXTURE_BASE		9
#define TEXTURE_PLANET		10
#define TEXTURE_STONE_0		11
#define TEXTURE_STONE_1		12
#define TEXTURE_BREAK		13
#define TEXTURE_NEBULA_0	14
#define TEXTURE_NEBULA_1	15
#define TEXTURE_UI_FONT_2	16
#define TEXTURE_BOSS		17
#define TEXTURE_BULLET		18
#define TEXTURE_ENE_MS		19
#define TEXTURE_MISSILE		20
#define TEXTURE_WARNING		21
#define TEXTURE_UI_GAME		22
#define TEXTURE_JIKI_DAMAGE 23
#define TEXTURE_JIKI_MUTEKI 24
#define TEXTURE_PLANET_1	25
#define TEXTURE_PLANET_2	26
#define TEXTURE_PLANET_3	27
#define TEXTURE_CONTROLL	28
#define TEXTURE_BULLET_GEN	29
#define TEXTURE_UI_FONT_3	30
#define TEXTURE_ENE_02		31
#define TEXTURE_ENE_03		32
#define TEXTURE_ENE_04		33
#define TEXTURE_ENE_05		34
#define TEXTURE_ENE_06		35
#define TEXTURE_ENE_07		36
#define TEXTURE_BURNER		37
#define TEXTURE_BURNER_2	38
#define TEXTURE_UI_FONT_4	39
#define TEXTURE_SPARK		40
#define TEXTURE_BOSS_LOGO	41
#define TEXTURE_DEMO_PLAY	42
#define TEXTURE_UI_FONT_5	43

//------------------------------------------------------------------------------------------------------------------------------------------------------
// ステータス
//------------------------------------------------------------------------------------------------------------------------------------------------------
#define ATK		work9[ X ]
#define HP		work9[ Y ]
#define SCORE	work9[ Z ]
#define BONUS	work9[ P ]

#define VEC_X	fworkC[ X ]
#define VEC_Y	fworkC[ Y ]

//------------------------------------------------------------------------------------------------------------------------------------------------------
// データの読み込み・書き込み
//------------------------------------------------------------------------------------------------------------------------------------------------------
#define LOAD_MODE	0
#define SAVE_MODE	1

//------------------------------------------------------------------------------------------------------------------------------------------------------
// エフェクトが流れるスピード
//------------------------------------------------------------------------------------------------------------------------------------------------------
#define EFFECT_SPEED	8
