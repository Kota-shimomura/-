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
#define ANNIHILATION_CHECK		SEQ_ANNIHILATION	// �S�Ń`�F�b�N
#define ENE_MOVE( ene_move )			SEQ_ENE_MOVE, ene_move
#define SUMMON_BOSS			SEQ_BOSS
#define NEXT_STAGE			SEQ_NEXT_STAGE


#define XR_YD	0		// �E��
#define X_YD	1		// ��
#define XL_YD	2		// ����
#define XR_Y	3		// �E
#define X_Y		4		// ���S
#define XL_Y	5		// ��
#define XR_YU	6		// �E��
#define X_YU	7		// ��
#define XL_YU	8		// ����

#define XR2_YD	9		// �E�� | ��
#define X2_YD	10		// �E�� | ����
#define XL2_YD	11		// ���� | ��
#define XR2_Y	12		// �E�@ | ���S
#define X2_Y	13		// �E�@ | ��
#define XL2_Y	14		// ���@ | ���S
#define XR2_YU	15		// �E�� | ��
#define X2_YU	16		// �E�� | ����
#define XL2_YU	17		// ���� | ��

#define XR_YD2	18		// �E��	| �E
#define X_YD2	19		// ��	| ���S
#define XL_YD2	20		// ����	| ��
#define XR_Y2	21		// �E	| �E��
#define X_Y2	22		// ��	| ��
#define XL_Y2	23		// ��	| ����
#define XR_YU2	24		// �E��	| �E
#define X_YU2	25		// ��	| ���S
#define XL_YU2	26		// ����	| ��

#define X3_YU	27		// ����� | ��
#define X3_Y	28		// ����� | ���S
#define X3_YD	29		// ����� | ��

#define XR_Y3	30		// �E	| �c���
#define X_Y3	31		// ���S	| �c���
#define XL_Y3	32		// ��	| �c���

#define XL_B	33		// �����
#define XR_B	34		// �E���



