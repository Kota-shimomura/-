
extern SINT32 button_lr;
extern SINT32 button_ud;
extern SINT32 attack_button;
extern SINT32 demo_mode;

#define DEMO_DATA_SIZE 60 * 60 * 10
typedef struct
{
	SINT32 stick_lr;
	SINT32 stick_ud;
	SINT32 attack;
}DEMO_DATA;

extern DEMO_DATA demo_data[];

#define ON 1
#define OFF 0
#define DEMO_SHOT 0x0001
#define DEMO_MISSILE 0x0002

extern void fade( SINT32 fade_mode, SINT32 chenge_type );
extern void demo_play( void );
extern void play_data_get( void );

extern void button_data_get( void );

extern void grp_look_camer( TASK *ap );

extern void target_lock_vec( TASK *ap, TASK *actp );
extern void target_look( TASK *ap, TASK *actp );
extern void jiki_look( TASK *ap );
extern void lockon_jiki( TASK *ap );
extern void ang_vec_setting( TASK *ap, FLOAT speed );
extern void bic_illusion_start(TASK *actp, SINT32 speed, SINT32 blend);
extern void illusion_start(TASK *actp, SINT32 speed, SINT32 blend);
extern void camera_move( TASK *ap );
extern void shot_vec_setting( TASK *ap, FLOAT speed );

extern int hi_score_sort( void );
extern void hi_score_all_clear( void );

