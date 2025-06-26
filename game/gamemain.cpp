//------------------------------------------------------------------------------------------------------------------------------------------------------
//                systemOZ Ver4
//							�Q�[�����C���v���O����
//														programed by Shimomura Kota
//------------------------------------------------------------------------------------------------------------------------------------------------------
#ifdef WINDOWS_PC
#include    "C:/project/libs/systemOZ_v4/soz.h"
#else
#include    "D:/project/guardians_2dx/proj.win32/src/systemOZ/soz.h"
#endif

#include    "C:/project/panzer/src/game/game_include.h"


//------------------------------------------------------------------------------------------------------------------------------------------------------
//�O���ϐ���`
//------------------------------------------------------------------------------------------------------------------------------------------------------
SINT32	platform_PC = 1;
SINT32	game_type = 0, game_type2 = 0, game_type3 = 0, game_mode = 0, game_type_old = 0;	//�Q�[���̐i�s�x

#if 0
//----------------------------------------------------------------------------------
// �������̊Ǘ�
//----------------------------------------------------------------------------------
typedef struct
{
	int x, y;
	char name[ 100 ];
	float height, waight;
} HUMAN;

int main( void )
{
	HUMAN *m, *hum;
	//���������m��
	m = (HUMAN * )calloc( 10000, sizeof( HUMAN ) );
//	m = (HUMAN * )malloc( 10000 * sizeof( HUMAN ) );

	//�������̎g�p
	hum = m;					//0�l�ڂ��w��
	hum += 100;					//100�l�ڂ��w��
	hum->height = 182.5f;		//100�l�ڂ̐g����ύX

	//�������̊J��
	free( m );
}
#endif



//------------------------------------------------------------------------------------------------------------------------------------------------------
//   ���C�����[�`�� (1/60�b�Ɂ@1��Ăяo�����)	�����߂����Ă�������
//------------------------------------------------------------------------------------------------------------------------------------------------------
void GAMEMAIN_Routine( void )
{
	switch( game_type )
	{
		case GT_LOAD:	//�ǂݍ���
			hi_score_rank_read();
			load_set();
			INKEY_keyconfig_data_load();	//�L�[�R���t�B�O�̃f�[�^�����[�h
			bg_color_r = 0x00;
			bg_color_g = 0x00;
			bg_color_b = 0x00;
			MAP_DATA_LOAD
			game_type++;
			break;

		case GT_GAME_TYPE_SERECT:	//���ꂼ��f�o�b�O�p�V�[���ړ�
//			game_type = GT_TEAM;
			game_type = GT_STAFF_ROLL;
			break;

		case GT_TEAM:	//�`�[�����\��
			team_name_disp();
			game_type++;
			break;

		case GT_TITLE:	//�^�C�g�����
			SOZ_Music_Stop( 0 );
			SOZ_Music_Load( 0, "grp/BGM/panzer_menu_BGM", 1 );
			title_set();
			game_type++;
			break;

		case GT_MENU:	//�������
			navigation_set();
			game_type++;
			break;

		case GT_SCORE:	//�X�R�A���
			record_set();
			game_type++;
			break;

		case GT_KEYCON:	//�L�[�R���t�B�O
			if( INKEY_keyconfig() < 0 )
			{
				INKEY_keyconfig_data_save();
				game_type = GT_TITLE;
			}
			break;

		case GT_GAME_MODE:	//�Q�[�����
//			enemy_read_the_file();
			enemy_setting( ENEMY_SET_DISP, 8, 11 );	//�G�̃f�[�^�̓ǂݍ���
			map_read_the_file();
			map_setting(MAP_DISP, 18, 11 );		//�}�b�v�`�b�v
			scr_x = GAME_MAP_SIZE_X/2;
			scr_y = GAME_MAP_SIZE_Y/2;
			jiki_start();			//���@
			hp_ui();
			score_disp();			//�X�R�A
			hi_score_disp();		//�n�C�X�R�A
			SOZ_Music_Stop( 0 );
			SOZ_Music_Load( 0, "grp/BGM/panzer_BGM", 1 );
			game_type++;
			break;

		case 101:
			countdown_start();
			game_type++;
				break;

		case 102:
			game_type++;
			break;



		case GT_GAME_OVER:		//�Q�[���I�[�o�[���
			disp_rizaruto( GAME_OVER );
			hi_score_reload();					//�n�C�X�R�A�̍X�V
			map_setting( MAP_DISP, 34, 19 );	//�}�b�v�`�b�v
			game_type++;
			break;

		case GT_GAME_CLEAR:
			disp_rizaruto( GAME_CLEAR );
			hi_score_reload();					//�n�C�X�R�A�̍X�V
			map_setting( MAP_DISP, 34, 19 );	//�}�b�v�`�b�v
			game_type++;
			break;

		case GT_STAFF_ROLL:						// �G���h���[��/�X�^�b�t���[��
			TASK_all_init();
			staff_roll_seqence();
			game_type++;
			break;


		case TEST_GT_MAP_EDIT:		//�}�b�v�G�f�B�^
			scr_x = GAME_MAP_SIZE_X / 2;
			scr_y = GAME_MAP_SIZE_Y / 2;
#if 0
			map_setting( MAP_ALL_0, 7, 9 );
#else
			map_setting( MAP_DISP, 9, 10 );
#endif
			map_edit();
			game_type++;
			break;

		case TEST_GT_ENEMY_SET:		//�G�z�u
			jiki_start();			//���@
			game_type++;
			break;

		case TEST_GT_SYSTEM:
			map_setting( MAP_DISP, 34, 19 );
			scr_tester();
			game_type++;
			break;

		case TEST_GT_ENEMY_MAP:	//�G�̃}�b�v�z�u
#if 0
			enemy_setting( ENEMY_ALL_NULL, 8, 11 );
#else
			enemy_setting( ENEMY_SET_DISP, 8, 11 );
#endif
			jiki_start();
			enemy_data_list();
			enemy_map_set_mouse();
			//scr_x = 0;
			//scr_y = 0;
			scr_x = GAME_MAP_SIZE_X / 2;
			scr_y = GAME_MAP_SIZE_Y / 2;
			game_type++;
			break;

		case TEST_GT_ENEMY_MAP+1:
			if( SOZ_Inkey_TRG( DIK_Q ) )
			{
				game_type = GT_GAME_TYPE_SERECT;
				TASK_all_init();
			}

			if( SOZ_Inkey_TRG( DIK_G ) )
			{
				game_type = GT_GAME_MODE;
				TASK_all_init();
			}
			break;

		case TEST_MODE:
			scr_x = GAME_MAP_SIZE_X / 2;
			scr_y = GAME_MAP_SIZE_Y / 2;
			map_read_the_file();
			jiki_start();
			map_setting( MAP_DISP, 18, 11 );		//�}�b�v�`�b�v
			game_type++;
			break;

		case TEST_MODE + 1:
			break;
	}

	game_type_old = game_type;
}