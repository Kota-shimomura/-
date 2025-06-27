
#define DELAY_TIME 210


extern void bullet_myship_hit_effect( void );
extern void spark_effect( TASK *ap, SINT32 num );
extern void break_smoke( TASK *actp );
extern void burner_effect( TASK *actp, FLOAT space, FLOAT pos_z,FLOAT vec_z );
extern void boss_code_disp( void );
extern void boss_next_code_disp( void );
extern void ms_lockon_font( FLOAT pos_x, FLOAT pos_y, FLOAT pos_z );
extern void ms_lockon_effect( FLOAT pos_x, FLOAT pos_y, FLOAT pos_z );
extern void break_02_light( FLOAT pos_x, FLOAT pos_y, FLOAT pos_z );
extern void break_02_flash( FLOAT pos_x, FLOAT pos_y, FLOAT pos_z );
extern void hit_flash( TASK *ap );
extern void break_effect_02( FLOAT pos_x, FLOAT pos_y, FLOAT pos_z );
extern void break_bom_effect( FLOAT pos_x, FLOAT pos_y, FLOAT pos_z );
extern void break_effect( FLOAT pos_x, FLOAT pos_y, FLOAT pos_z );
extern void jiki_burner_effect( TASK *actp, FLOAT space );
extern void shot_hit_effect( FLOAT pos_x, FLOAT pos_y, FLOAT pos_z );
extern void shot_effect_start( FLOAT pos_x, FLOAT pos_y, FLOAT pos_z  );
extern void ene_ms_effect_start( FLOAT pos_x, FLOAT pos_y, FLOAT pos_z  );
extern void missile_start_effect( FLOAT pos_x, FLOAT pos_y, FLOAT pos_z  );
extern void missile_effect( FLOAT pos_x, FLOAT pos_y, FLOAT pos_z  );
