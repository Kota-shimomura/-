
#define STICK_LR		0x0001				// �X�e�B�b�N���͂̍��E���]
#define STICK_UD		0x0002				// �X�e�B�b�N���͂̏㉺���]
#define STICK_ANALOG	0x0004
#define STICK_SET		0x0008				// �X�e�B�b�N�֘A�̏����ݒ���������ǂ���

extern	SINT32 stick_data;

extern void new_data_font( void );
extern void opration_setting_system( FLOAT pos_y );
extern void key_disp( FLOAT pos_x, FLOAT pos_y );
extern void back_disp( FLOAT pos_x, FLOAT pos_y );
