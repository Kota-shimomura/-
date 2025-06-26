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

#include    "C:/project/bace/src/game/game_include.h"

//------------------------------------------------------------------------------------------------------------------------------------------------------
//�O���ϐ���`
//------------------------------------------------------------------------------------------------------------------------------------------------------
SINT32	platform_PC = 1;
SINT32	game_type = 0, game_type2 = 0, game_type3 = 0, game_mode = 0, game_type_old = 0;	//�Q�[���̐i�s�x


//------------------------------------------------------------------------------------------------------------------------------------------------------
//�@�C���_
//------------------------------------------------------------------------------------------------------------------------------------------------------
// �G�̌����ڂ����v�W��ނɂ���														!?
// ����̓����̑��x��x�����Ă���������											!!
// �^�C�g����ʁA�����L���O��ʁA�I�v�V������ʂ̔w�i�����@�������n�ɐݒ肷��		!!
// �v���C���[���������鉉�o��������
// �{�X��������
// �{�X�̓o�ꎞ�ɁA���O�Ȃǂ�\������
// �~�T�C���Ƀ��b�N�I����ǉ����Ĕ��˕\�L�����A�g�p�𑣂��B							!!
// �G�ɑ����g�܂���																!!
// �㉺���E�̃��o�[�X�ݒ���ł���悤�ɂ���B
// 
// �o���J���Ɏ˒���ݒ肷��
// �o���J���̑ł����𒲐�
// �~�T�C���̏����ő��30�ɂ���
// �G���~�T�C���A�C�e���𗎂Ƃ��H-> �G���~�T�C���œ|����
// 
//------------------------------------------------------------------------------------------------------------------------------------------------------

//-----------------------------
// Ver 2.0�\�L
//-----------------------------
void ver_disp_exec( TASK *ap )
{}
void ver_disp( void )
{
	TASK *ap;
	ap = TASK_start_FONT( ver_disp_exec, GROUP_UI, "Ver 2.06.13", 2 );
	ap->pos[ X ] = WINDOW_WIDTH - 200.0f;
	ap->pos[ Y ] = WINDOW_HEIGHT - 50.0f;
	ap->pri = PRI_UI + 1000;
}

//------------------------------------------------------------------------------------------------------------------------------------------------------
//   ���C�����[�`�� (1/60�b�Ɂ@1��Ăяo�����)	�����߂����Ă�������
//------------------------------------------------------------------------------------------------------------------------------------------------------
void GAMEMAIN_Routine( void )
{
	switch( game_type )
	{
		case 0:	// �f�[�^�̓ǂݍ���
			hi_score_all_clear();																// �n�C�X�R�A�̔z�񏉊���
			data_set();
			play_load();				// �v���C�p�̃f�[�^��ǂݍ���
			bg_color_r = 0x11;	// �w�i�F�̐ݒ�
			bg_color_g = 0x11;	// �w�i�F�̐ݒ�
			bg_color_b = 0x11;	// �w�i�F�̐ݒ�
			demo_mode = 0;
			game_type = TYPE_TITLE;
			break;

		case TYPE_CONFIG:	//�L�[�R���t�B�O���
			if (INKEY_keyconfig() < 0 )
			{
				INKEY_keyconfig_data_save();	//�ݒ肵���L�[�R���t�B�O�f�[�^�̃Z�[�u
				game_type = TYPE_TITLE;		//�^�C�g����ʂɍs��
			}
			break;
///------- �^�C�g�� ------------------
		case TYPE_TITLE:
			if( demo_mode != 0 )
				fade( -5, 0 );
			SOZ_Music_Stop( 0 );		// BGM���~�߂�
			SOZ_Music_Load( 0, "grp/shooting/bgm/bace_menu", 1 );	// BGM�̍Đ�
			ver_disp();
#ifdef DEBUG
//			game_type = TYPE_END;			// �G���h���[���m�F
			game_type = TYPE_GAME;			// �Q�[����ʊm�F
//			game_type = TYPE_DEMO;			// �f���v���C�m�F
//			game_type = TYPE_NEW_DATA;
			play_load();					// �f�o�b�O���̓ǂݍ���
			//title_disp();
			//SOZ_camera( 0, 0, 0, 4000, 0x0000, 0x0000, 0x0000, 0 );								// �J�����̍��W�Ɗp�x�ݒ�
			//SOZ_set_light_pos(  41300.0f, 7800.0f, 15300.0f, -3500.0f, -47200.0f, -22000.0f );	// ���C�g�̐ݒ�
			//bg_base_jiki();
			//game_type++;
#else
			title_disp();
//			SOZ_camera( 0, 0, 50, 2000, 0x0000, 0x0000, 0x0000, 0 );								// �J�����̍��W�Ɗp�x�ݒ�
			SOZ_camera( 0, 0, 50, -1000, 0x0000, 0x0000, 0x0000, 0 );								// �J�����̍��W�Ɗp�x�ݒ�
			SOZ_set_light_pos(  41300.0f, 7800.0f, 15300.0f, -3500.0f, -47200.0f, -22000.0f );	// ���C�g�̐ݒ�
			bg_base_jiki();
			game_type++;
#endif
			break;

		case TYPE_TITLE +1:
			if( SOZ_Inkey_TRG( DIK_F1 ) )		// ����̃L�[����������R���g���[���[�̃L�[�R���t�B�O��ʂɔ��
			{
				TASK_all_init();
				game_type = TYPE_CONFIG;
			}
			break;

///------- ���j���[ ------------------
		case TYPE_MENU:
//			play_release();
			SOZ_camera( 0, 0, 50, -1000, 0x0000, 0x0000, 0x0000, 0 );								// �J�����̍��W�Ɗp�x�ݒ�
			option_save_data( LOAD_MODE );							// �ݒ�̃f�[�^��ǂݍ���
			SOZ_Music_Load( 0, "grp/shooting/bgm/bace_menu", 1 );	// BGM�̍Đ�
			key_disp( WINDOW_WIDTH /2, WINDOW_HEIGHT -50.0f );
			bg_base_jiki();
			hi_score_data( LOAD_MODE );															// �n�C�X�R�A�̃f�[�^��݂���
			menu_disp();																		// ���j���[�\��
			game_type++;
			break;

		case TYPE_MENU +1:
			SOZ_locate_print( 10, 3, "[STICK_DATA]:%04d", stick_data );
			if( SOZ_Inkey_TRG( DIK_F1 ) )		// ����̃L�[����������R���g���[���[�̃L�[�R���t�B�O��ʂɔ��
			{
				TASK_all_init();
				game_type = TYPE_CONFIG;
			}
			break;

///------- �I�v�V������� ----------------
		case TYPE_OPTION:
			TASK_all_init();
			key_disp( WINDOW_WIDTH /2, WINDOW_HEIGHT -50.0f );
			bg_base_jiki();
			ui_cont_disp( WINDOW_WIDTH / 2 + 50.0f, WINDOW_HEIGHT /2 + 250.0f, 0.8f );
			mini_logo_disp();		// ����̏��������S��\��
			opration_setting_system( 70.0f );					// �I�v�V�����ݒ�^�X�N
			game_type++;
			break;

		case TYPE_OPTION +1:
			if( SOZ_Inkey_TRG( DIK_X ) || SOZ_Inpad_TRG( 0, PADDIK_CANCEL ) )			// �߂�{�^���������ꂽ�烁�j���[��ʂɖ߂�
			{
				game_type = TYPE_MENU;
				TASK_all_init();
				bg_base_jiki();
				return;
			}
			break;

///------- �����L���O��� ----------------
		case TYPE_RANKING:
			TASK_all_init();
			bg_base_jiki();
			ranking_disp();
			back_disp( WINDOW_WIDTH - 300.0f, WINDOW_HEIGHT -50.0f );
			mini_logo_disp();		// ����̏��������S��\��
			game_type++;
			break;
///------- �Q�[����� ----------------
		case TYPE_GAME:
			SOZ_Music_Stop( 0 );
			TASK_all_init();
			score = 0;
			SOZ_camera( 0, 0, 0, 100, 0x0000, 0x0000, 0x0000, 0 );
//			SOZ_camera( 0, 0, 0, 4000, 0x0000, 0x0000, 0x0000, 0 );
			SOZ_set_light_pos(  41300.0f, 7800.0f, 15300.0f, -3500.0f, -47200.0f, -22000.0f );
			atack_cont_disp();										// �U��������@�̕\��
			score_disp();											// �X�R�A�̕\��
			hi_score_disp();										// �n�C�X�R�A�̕\��
			stage_disp();											// �X�e�[�W�̕\��
			life_disp();											// �c�@�̕\��
			missile_num_disp();										// �~�T�C���c�e���̕\��
			my_ship();												// ���@�̕\��
			universe_gen();											// �n�ʂ̕\��
//#ifdef MASTER
			enemy_seq();											// �G�V�[�P���X�̋N��
//#endif
			engage_disp();											// ENGAGE �̕\��
			play_data_get();	// ����̕ۑ�
			SOZ_Music_Load( 0, "grp/shooting/bgm/bace_bgm", 1 );	// BGM�̍Đ�

			// �f������
			game_type++;
			break;

///------- �N���A��� ---------------
		case TYPE_CLEAR:
			SOZ_Music_Stop( 0 );		// BGM���~�߂�
//			TASK_end_group( GROUP_ENEMY );	// �G�����ׂď���
			game_clear_disp();
			game_type++;
			break;

		case TYPE_CLEAR + 2:
			TASK_end_group( GROUP_UI );
			result_disp();
			result_button_set( 1 );
			hi_score_data( SAVE_MODE );		// �n�C�X�R�A�̃f�[�^��������
			game_type++;
			break;

///------- �Q�[���I�[�o�[��� -------
		case TYPE_OVER:
			SOZ_Music_Stop( 0 );		// BGM���~�߂�
			game_over_disp();
			game_type++;
			break;
		case TYPE_OVER + 2:
			TASK_end_group( GROUP_UI );
			result_disp();
			result_button_set( 0 );
			hi_score_data( SAVE_MODE );		// �n�C�X�R�A�̃f�[�^��������
			game_type++;
			break;

///------- �G���h���[�� ------------------
		case TYPE_END:
			SOZ_Music_Stop( 0 );		// BGM���~�߂�
			SOZ_Music_Load( 0, "grp/shooting/bgm/ending", 0 );	// BGM�̍Đ�
			end_roll();
			game_type++;
			break;


///------- ���߂ăv���C ------------------
		case TYPE_NEW_DATA:
			new_data_font();
			key_disp( WINDOW_WIDTH /2, WINDOW_HEIGHT -50.0f );
			ui_cont_disp( WINDOW_WIDTH - 310.0f, WINDOW_HEIGHT - 200.0f, 0.3f );
			opration_setting_system( 400.0f );					// �I�v�V�����ݒ�^�X�N
			game_type++;
			break;

		case TYPE_NEW_DATA + 1:
			button_data_get();
			SOZ_locate_print( 10, 3, "[STICK_DATA]:%04d", stick_data );
			//SOZ_locate_print( 10, 3, "[button_lr]:%04d", button_lr );
			//SOZ_locate_print( 10, 4, "[button_ud]:%04d", button_ud );
			if( SOZ_Inkey_TRG( DIK_F1 ) )		// ����̃L�[����������R���g���[���[�̃L�[�R���t�B�O��ʂɔ��
			{
				TASK_all_init();
				game_type = TYPE_NEW_DATA + 5;
			}
			break;

		case TYPE_NEW_DATA + 5:
			if (INKEY_keyconfig() < 0 )
			{
				INKEY_keyconfig_data_save();	//�ݒ肵���L�[�R���t�B�O�f�[�^�̃Z�[�u
				game_type = TYPE_NEW_DATA;		//���̉�ʂɖ߂�
				bg_base_jiki();
			}
			break;

// �f���v���C
		case TYPE_DEMO:
			score = 0;
			SOZ_Music_Stop( 0 );		// BGM���~�߂�
			fade( -5, 0 );
			SOZ_camera( 0, 0, 0, 100, 0x0000, 0x0000, 0x0000, 0 );
//			SOZ_camera( 0, 0, 0, 4000, 0x0000, 0x0000, 0x0000, 0 );
			SOZ_set_light_pos(  41300.0f, 7800.0f, 15300.0f, -3500.0f, -47200.0f, -22000.0f );
			replay_option_save_data( LOAD_MODE );					// ���v���C���̐ݒ�ǂݍ���
			atack_cont_disp();										// �U��������@�̕\��
			stage_disp();											// �X�e�[�W�̕\��
			life_disp();											// �c�@�̕\��
			missile_num_disp();										// �~�T�C���c�e���̕\��
			my_ship();												// ���@�̕\��
			universe_gen();											// �n�ʂ̕\��
			enemy_seq();											// �G�V�[�P���X�̋N��
			engage_disp();											// ENGAGE �̕\��
			SOZ_Music_Load( 0, "grp/shooting/bgm/bace_bgm", 1 );	// BGM�̍Đ�
			mini_logo_disp();		// ����̏��������S��\��
			demo_play();
			demo_play_disp();
			game_type++;
			break;
	}

	game_type_old = game_type;
}