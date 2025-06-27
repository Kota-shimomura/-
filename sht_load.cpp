#ifdef WINDOWS_PC
#include    "C:/project/libs/systemOZ_v4/soz.h"
#else
#include    "D:/project/guardians_2dx/proj.win32/src/systemOZ/soz.h"
#endif

#include    "C:/project/bace/src/game/game_include.h"


//------------------------------------------------------------------------------------------------------------------------------------------------------
// �Q�[���p�f�[�^�ǂݍ��� / �J��
//------------------------------------------------------------------------------------------------------------------------------------------------------
void play_load( void )
{
	SOZ_load_texture( TEXTURE_SHOT,			"grp/shooting/jiki/sht_shot");
	SOZ_load_texture( TEXTURE_MISSILE,		"grp/shooting/jiki/missile" );
	SOZ_load_texture( TEXTURE_JIKI_DAMAGE,	"grp/shooting/jiki/jiki_damage" );
	SOZ_load_texture( TEXTURE_JIKI_MUTEKI,	"grp/shooting/jiki/jiki_muteki" );

	SOZ_load_texture( TEXTURE_FLOOR_0,		"grp/shooting/bg/ears");
	SOZ_load_texture( TEXTURE_STONE_0,		"grp/shooting/bg/stone_0");
	SOZ_load_texture( TEXTURE_STONE_1,		"grp/shooting/bg/stone_1");
	SOZ_load_texture( TEXTURE_PLANET,		"grp/shooting/bg/planet");
	SOZ_load_texture( TEXTURE_NEBULA_0,		"grp/shooting/bg/nebula_0" );
	SOZ_load_texture( TEXTURE_NEBULA_1,		"grp/shooting/bg/nebula_1" );

	SOZ_load_texture( TEXTURE_WARNING,		"grp/shooting/effect/warning" );
	SOZ_load_texture( TEXTURE_BURNER_2,		"grp/shooting/effect/burner_enemy" );
	SOZ_load_texture( TEXTURE_HIT_EFF,		"grp/shooting/effect/shot_hit");
	SOZ_load_texture( TEXTURE_BREAK,		"grp/shooting/effect/bom");
	SOZ_load_texture( TEXTURE_SPARK,		"grp/shooting/effect/spark" );

	SOZ_load_texture( TEXTURE_PLANET_1,		"grp/shooting/bg/planet/planet_1" );
	SOZ_load_texture( TEXTURE_PLANET_2,		"grp/shooting/bg/planet/planet_2" );
	SOZ_load_texture( TEXTURE_PLANET_3,		"grp/shooting/bg/planet/planet_3" );

	SOZ_load_texture( TEXTURE_BOSS_LOGO,	"grp/shooting/ui/font/boss_name_logo" );

	SOZ_load_texture( TEXTURE_BULLET_GEN,	"grp/shooting/enemy/bullet_gen" );
	SOZ_load_texture( TEXTURE_BOSS,			"grp/shooting/enemy/sht_boss" );
	SOZ_load_texture( TEXTURE_BULLET,		"grp/shooting/enemy/bullet" );
	SOZ_load_texture( TEXTURE_ENE_MS,		"grp/shooting/enemy/ene_ms" );
	SOZ_load_texture( TEXTURE_ENE_00,		"grp/shooting/enemy/enemy_3D_data/enemy_0" );
	SOZ_load_texture( TEXTURE_ENE_01,		"grp/shooting/enemy/enemy_3D_data/enemy_1" );
	SOZ_load_texture( TEXTURE_ENE_02,		"grp/shooting/enemy/enemy_3D_data/enemy_2" );
	SOZ_load_texture( TEXTURE_ENE_03,		"grp/shooting/enemy/enemy_3D_data/enemy_3" );
	SOZ_load_texture( TEXTURE_ENE_04,		"grp/shooting/enemy/enemy_3D_data/enemy_4" );
}

// �J��
void play_release( void )
{
	SOZ_release_texture( TEXTURE_SHOT );
	SOZ_release_texture( TEXTURE_MISSILE );
	SOZ_release_texture( TEXTURE_JIKI_DAMAGE );
	SOZ_release_texture( TEXTURE_JIKI_MUTEKI );

	SOZ_release_texture( TEXTURE_FLOOR_0 );
	SOZ_release_texture( TEXTURE_STONE_0 );
	SOZ_release_texture( TEXTURE_STONE_1 );
	SOZ_release_texture( TEXTURE_PLANET );
	SOZ_release_texture( TEXTURE_NEBULA_0 );
	SOZ_release_texture( TEXTURE_NEBULA_1 );

	SOZ_release_texture( TEXTURE_WARNING );
	SOZ_release_texture( TEXTURE_BURNER_2 );
	SOZ_release_texture( TEXTURE_HIT_EFF );
	SOZ_release_texture( TEXTURE_BREAK );
	SOZ_release_texture( TEXTURE_SPARK );

	SOZ_release_texture( TEXTURE_PLANET_1 );
	SOZ_release_texture( TEXTURE_PLANET_2 );
	SOZ_release_texture( TEXTURE_PLANET_3 );

	SOZ_release_texture( TEXTURE_BULLET_GEN );
	SOZ_release_texture( TEXTURE_BOSS );
	SOZ_release_texture( TEXTURE_BULLET );
	SOZ_release_texture( TEXTURE_ENE_MS );
	SOZ_release_texture( TEXTURE_ENE_00 );
	SOZ_release_texture( TEXTURE_ENE_01 );
	SOZ_release_texture( TEXTURE_ENE_02 );
	SOZ_release_texture( TEXTURE_ENE_03 );
	SOZ_release_texture( TEXTURE_ENE_04 );
}

//------------------------------------------------------------------------------------------------------------------------------------------------------
// �ǂݍ���
//------------------------------------------------------------------------------------------------------------------------------------------------------
void load_se( void )
{
	SOZ_load_se( SE_SHOT_HIT,	"grp/shooting/se/shot_bullet/shot_hit" );
	SOZ_load_se( SE_SHOT,		"grp/shooting/se/shot_bullet/shot" );
	SOZ_load_se( SE_BREAK,		"grp/shooting/se/break/break" );
	SOZ_load_se( SE_BREAK_BOM,	"grp/shooting/se/break/break_bom" );
	SOZ_load_se( SE_SERECT,		"grp/shooting/se/ui/serect" );
	SOZ_load_se( SE_DECISION,	"grp/shooting/se/ui/decision" );
	SOZ_load_se( SE_CANCEL,		"grp/shooting/se/ui/cancel" );
	SOZ_load_se( SE_TAKE_OFF,	"grp/shooting/se/my_ship/take_off");
	SOZ_load_se( SE_WARNING,	"grp/shooting/se/ui/warning" );
	SOZ_load_se( SE_MISSILE,	"grp/shooting/se/my_ship/missile" );
	SOZ_load_se( SE_SHOT_2,		"grp/shooting/se/shot_bullet/shot_2" );
	SOZ_load_se( SE_BREAK_2,	"grp/shooting/se/break/break_2" );
	SOZ_load_se( SE_BOSS_CODE,	"grp/shooting/se/boss_code" );
	SOZ_load_se( SE_SPARK,		"grp/shooting/se/my_ship/spark" );
	SOZ_load_se( SE_DAMAGE,		"grp/shooting/se/my_ship/damage" );
	SOZ_load_se( SE_BOSS_BIT,	"grp/shooting/se/boss_bit" );
}

void load_texture( void )
{
	SOZ_load_texture( TEXTURE_MY_SHIP,		"grp/shooting/jiki/jiki");

	SOZ_load_texture( TEXTURE_BASE,			"grp/shooting/bg/base");

	SOZ_load_texture( TEXTURE_BURNER,		"grp/shooting/effect/burner" );

	SOZ_load_texture( TEXTURE_UI_GAME,		"grp/shooting/ui/game/game" );
	SOZ_load_texture( TEXTURE_CONTROLL,		"grp/shooting/ui/game/controll" );
	SOZ_load_texture( TEXTURE_UI_FONT,		"grp/shooting/ui/font/font" );
	SOZ_load_texture( TEXTURE_UI_FONT_2,	"grp/shooting/ui/font/font_2" );
	SOZ_load_texture( TEXTURE_UI_FONT_3,	"grp/shooting/ui/font/font_3" );
	SOZ_load_texture( TEXTURE_UI_FONT_4,	"grp/shooting/ui/font/font_4" );
	SOZ_load_texture( TEXTURE_UI_FONT_5,	"grp/shooting/ui/font/font_5" );
	SOZ_load_texture( TEXTURE_LOGO,			"grp/shooting/ui/font/Galactic_Retrieval" );
	SOZ_load_texture( TEXTURE_DEMO_PLAY,	"grp/shooting/ui/font/demo_font" );
}

void load_3Dmodel( void )
{
	SOZ_load_model( MODEL_MY_SHIP,		"grp/shooting/jiki/jiki" );
	SOZ_load_model( MODEL_SHOT,			"grp/shooting/jiki/sht_shot" );
	SOZ_load_model( MODEL_MISSILE,		"grp/shooting/jiki/missile" );

	SOZ_load_model( MODEL_FLOOR,		"grp/shooting/bg/bg" );
	SOZ_load_model( MODEL_BASE,			"grp/shooting/bg/base" );
	SOZ_load_model( MODEL_STONE_0,		"grp/shooting/bg/stone_0");
	SOZ_load_model( MODEL_STONE_1,		"grp/shooting/bg/stone_1");
	SOZ_load_model( MODEL_PLANET,		"grp/shooting/bg/planet");
	SOZ_load_model( MODEL_PLANET_BG,	"grp/shooting/bg/planet/planet" );

	SOZ_load_model( MODEL_BULLET_GEN,	"grp/shooting/enemy/bullet_gen" );
	SOZ_load_model( MODEL_BOSS,			"grp/shooting/enemy/sht_boss" );
	SOZ_load_model( MODEL_ENE_MS,		"grp/shooting/enemy/ene_ms" );
	SOZ_load_model( MODEL_ENE_00,		"grp/shooting/enemy/enemy_3D_data/enemy_0" );
	SOZ_load_model( MODEL_ENE_01,		"grp/shooting/enemy/enemy_3D_data/enemy_1" );
	SOZ_load_model( MODEL_ENE_02,		"grp/shooting/enemy/enemy_3D_data/enemy_2" );
	SOZ_load_model( MODEL_ENE_03,		"grp/shooting/enemy/enemy_3D_data/enemy_3" );
	SOZ_load_model( MODEL_ENE_04,		"grp/shooting/enemy/enemy_3D_data/enemy_4" );

}

void load_set( void )
{
	load_3Dmodel();							//���f���̓ǂݍ���
	load_texture();							//�摜�ǂݍ���
	load_se();								//���ʉ��ǂݍ���
	INKEY_keyconfig_data_load();			//�L�[�R���t�B�O�f�[�^�̃��[�h
}

//------------------------------------------------------------------------------------------------------------------------------------------------------
// �f�[�^�̏�����
//------------------------------------------------------------------------------------------------------------------------------------------------------
void data_set( void )
{
///-------- �f�[�^�̏����� --------
	tutorial_flag = 0xffffff;
//	tutorial_flag = TUTORIAL_ALL_CLEAR;		// �f�[�^��ǂݍ��ޑO�ɕϐ��̏�����
	//orFLG( tutorial_flag, TOTORIAL_NONE );	// ����̋@�\���J������

///-------- �f�[�^�̓ǂݍ��� --------
	load_set();
}

//------------------------------------------------------------------------------------------------------------------------------------------------------
// �I�v�V�����f�[�^�̕ۑ��E�ǂݍ���
//------------------------------------------------------------------------------------------------------------------------------------------------------
SINT32 option_save_data( SINT32 mode )
{
	FILE *fp;
	SINT32 fsize;
	fsize = sizeof stick_data;
	switch( mode )
	{
		case LOAD_MODE:		// �f�[�^�̓ǂݍ���
			fp = SOZ_FILE_open( "grp/shooting/save_data/option_data.dat", "rb" );	//�t�H���_���J����
			if( fp == NULL )
				return 0;

			SOZ_FILE_read( &stick_data, fsize, 1, fp );	//�t�H���_�ɏ�������
			SOZ_FILE_close( fp );	//�t�H���_�����
			return 1;										//���폑���o��

			break;

		case SAVE_MODE:		// �f�[�^�̏�������
			fp = SOZ_FILE_open( "grp/shooting/save_data/option_data.dat", "wb" );	//�t�H���_���J����
			if( fp == NULL )
				return 0;

			SOZ_FILE_write( &stick_data, fsize, 1, fp );	//�t�H���_�ɏ�������
			SOZ_FILE_close( fp );	//�t�H���_�����
			return 1;										//���폑���o��
			break;
	}
	return 0;
}

//------------------------------------------------------------------------------------------------------------------------------------------------------
// �n�C�X�R�A�̕ۑ��E�ǂݍ���
//------------------------------------------------------------------------------------------------------------------------------------------------------
SINT32 hi_score_data( SINT32 mode )
{
	FILE *fp;
	SINT32 fsize;
	fsize = sizeof hi_score[ 0 ] *10;
	switch( mode )
	{
		case LOAD_MODE:		// �f�[�^�̓ǂݍ���
			fp = SOZ_FILE_open( "grp/shooting/save_data/hi_score_data.dat", "rb" );	//�t�H���_���J����
			if( fp == NULL )
				return 0;

			SOZ_FILE_read( &hi_score, fsize, 1, fp );	//�t�H���_�ɏ�������
			SOZ_FILE_close( fp );	//�t�H���_�����
			return 1;										//���폑���o��

			break;

		case SAVE_MODE:		// �f�[�^�̏�������
			if( hi_score_sort() == 1 )		// �\�[�g�m�F
			{
				fp = SOZ_FILE_open( "grp/shooting/save_data/hi_score_data.dat", "wb" );	//�t�H���_���J����
				if( fp == NULL )
					return 0;

				SOZ_FILE_write( &hi_score, fsize, 1, fp );	//�t�H���_�ɏ�������
				SOZ_FILE_close( fp );	//�t�H���_�����
				return 1;										//���폑���o��
			}
			break;
	}
	return 0;
}

//------------------------------------------------------------------------------------------------------------------------------------------------------
// ���v���C�̕ۑ��E�ǂݍ���
//------------------------------------------------------------------------------------------------------------------------------------------------------
SINT32 replay_save_data( SINT32 mode )
{
	FILE *fp;
	SINT32 fsize;
	fsize = sizeof DEMO_DATA;
	switch( mode )
	{
		case LOAD_MODE:		// �f�[�^�̓ǂݍ���
			fp = SOZ_FILE_open( "grp/shooting/save_data/replay_data.dat", "rb" );	//�t�H���_���J����
			if( fp == NULL )
				return 0;

			SOZ_FILE_read( &demo_data, fsize, DEMO_DATA_SIZE, fp );	//�t�H���_�ɏ�������
			SOZ_FILE_close( fp );	//�t�H���_�����
			return 1;										//���폑���o��

			break;

		case SAVE_MODE:		// �f�[�^�̏�������
			fp = SOZ_FILE_open( "grp/shooting/save_data/replay_data.dat", "wb" );	//�t�H���_���J����
			if( fp == NULL )
				return 0;

			SOZ_FILE_write( &demo_data, fsize, DEMO_DATA_SIZE, fp );	//�t�H���_�ɏ�������
			SOZ_FILE_close( fp );	//�t�H���_�����
			return 1;										//���폑���o��
			break;
	}
	return 0;
}
//------------------------------------------------------------------------------------------------------------------------------------------------------
// ���v���C�̃I�v�V�����f�[�^�̕ۑ��E�ǂݍ���
//------------------------------------------------------------------------------------------------------------------------------------------------------
SINT32 replay_option_save_data( SINT32 mode )
{
	FILE *fp;
	SINT32 fsize;
	fsize = sizeof stick_data;
	switch( mode )
	{
		case LOAD_MODE:		// �f�[�^�̓ǂݍ���
			fp = SOZ_FILE_open( "grp/shooting/save_data/replay_option_data.dat", "rb" );	//�t�H���_���J����
			if( fp == NULL )
				return 0;

			SOZ_FILE_read( &stick_data, fsize, 1, fp );	//�t�H���_�ɏ�������
			SOZ_FILE_close( fp );	//�t�H���_�����
			return 1;										//���폑���o��

			break;

		case SAVE_MODE:		// �f�[�^�̏�������
			fp = SOZ_FILE_open( "grp/shooting/save_data/replay_option_data.dat", "wb" );	//�t�H���_���J����
			if( fp == NULL )
				return 0;

			SOZ_FILE_write( &stick_data, fsize, 1, fp );	//�t�H���_�ɏ�������
			SOZ_FILE_close( fp );	//�t�H���_�����
			return 1;										//���폑���o��
			break;
	}
	return 0;
}


