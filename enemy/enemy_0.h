
// �����̍\����
typedef struct
{
	FUNC exe_func;
	FUNC_CB  callback;
}ENEMY_MOVE;

extern ENEMY_MOVE enemy_move[];

// �擾���� ID �ɂ���ēG�̃��f���ƃ}�e���A����ς��邽��
typedef struct
{
	SINT32	model_no;
	SINT32	tex_no;
	FLOAT	specular[ 3 ];
	FLOAT	ambient[ 3 ];
	FLOAT	emissive[ 3 ];
	FLOAT	diffuse[ 3 ];
	FLOAT	pow;
}ENEMY_APPEARANCE;

extern ENEMY_APPEARANCE enemy_skin[];

extern void boss_bullet_gen( TASK *actp, SINT32 id, FLOAT pos_x, FLOAT pos_y, SINT32 bullet_mode, SINT32 delay_time );
extern void enemy_disp( SINT32 move_id, SINT32 appearance_id, FLOAT pos_x, FLOAT pos_y, FLOAT pos_z, SINT32 hp, SINT32 add_score );
extern void boss_start( void );

//----------------------------------------------------------------------------------------------------------------------------------
// define
//----------------------------------------------------------------------------------------------------------------------------------

#define SEQ_BULLET	10	// �o���J���U��
#define SEQ_MS		20	// �~�T�C���U��
#define SEQ_MS2		21	// �~�T�C���U�� �Q��
#define SEQ_MS4		22	// �~�T�C���U�� �S��
#define SEQ_CT		30	// �U���N�[���^�C��

#define ATTACK_BULLET( pos_x, pos_y, ang_x, ang_y, ang_z )	SEQ_BULLET,pos_x, pos_y, ang_x, ang_y, ang_z	// �o���J���U��
#define ATTACK_MS		SEQ_MS	// �~�T�C���U��
#define ATTACK_MS2		SEQ_MS2	// �~�T�C���U��
#define ATTACK_MS4		SEQ_MS4	// �~�T�C���U��
#define ATTACK_CT( ct )		SEQ_CT, ct	// �U���N�[���^�C��

