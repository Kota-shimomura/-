#ifdef WINDOWS_PC
#include    "C:/project/libs/systemOZ_v4/soz.h"
#else
#include    "D:/project/guardians_2dx/proj.win32/src/systemOZ/soz.h"
#endif

#include    "C:/project/bace/src/game/game_include.h"

//---------------------------------------------------------------------------------------------------------------------------------------
// �J�����̐U���𔭐�������
//---------------------------------------------------------------------------------------------------------------------------------------

//---------------------------------------------------------------------------------------------------------------------------------------
// �J�����U���@��
//---------------------------------------------------------------------------------------------------------------------------------------
void camera_vibration_strength_exec( TASK *ap )
{
	ap->work1[ Z ] ++;					// �t���[���v�Z
	camera_x[ 0 ] += ap->work1[ X ];	// �J�����̍��W�����炷
	camera_y[ 0 ] += ap->work1[ Y ];
	ap->work1[ X ] *= -1;
	ap->work1[ Y ] *= -1;
	if( ap->work1[ Z ] >= 12 )			// ����t���[���𒴂�����^�X�N���I��点��
	{
		TASK_end( ap );
		return;
	}
	SOZ_camera_move( 0 );
}
void camera_vibration_strength( void )
{
	TASK *ap;
	ap = TASK_start( camera_vibration_strength_exec, GROUP_UI, "�J�����U���@��" );
	ap->work1[ X ] = 200;	// �J�����̍��W�v�Z�Ŏg�p����l
	ap->work1[ Y ] = 50;	// �J�����̍��W�v�Z�Ŏg�p����l
	ap->work1[ Z ] = 0;		// �U�����Ԍv���p
}

//---------------------------------------------------------------------------------------------------------------------------------------
// �J�����U���@��
//---------------------------------------------------------------------------------------------------------------------------------------
void camera_vibration_medium_exec( TASK *ap )
{
	ap->work1[ Z ] ++;					// �t���[���v�Z
	camera_x[ 0 ] += ap->work1[ X ];	// �J�����̍��W�����炷
	camera_y[ 0 ] += ap->work1[ Y ];
	ap->work1[ X ] *= -1;
	ap->work1[ Y ] *= -1;
	if( ap->work1[ Z ] >= 10 )			// ����t���[���𒴂�����^�X�N���I��点��
	{
		TASK_end( ap );
		return;
	}
	SOZ_camera_move( 0 );
}
void camera_vibration_medium( void )
{
	TASK *ap;
	ap = TASK_start( camera_vibration_medium_exec, GROUP_UI, "�J�����U���@��" );
	ap->work1[ X ] = 100;	// �J�����̍��W�v�Z�Ŏg�p����l
	ap->work1[ Y ] = 25;		// �J�����̍��W�v�Z�Ŏg�p����l
	ap->work1[ Z ] = 0;		// �U�����Ԍv���p
}

//---------------------------------------------------------------------------------------------------------------------------------------
// �J�����U���@��
//---------------------------------------------------------------------------------------------------------------------------------------
void camera_vibration_weak_exec( TASK *ap )
{
	ap->work1[ Z ] ++;					// �t���[���v�Z
	camera_x[ 0 ] += ap->work1[ X ];	// �J�����̍��W�ړ�
	ap->work1[ X ] *= -1;
	if( ap->work1[ Z ] >= 6 )			// ����t���[���𒴂�����^�X�N���I��点��
	{
		TASK_end( ap );
		return;
	}
	SOZ_camera_move( 0 );
}
void camera_vibration_weak( void )
{
	TASK *ap;
	ap = TASK_start( camera_vibration_weak_exec, GROUP_UI, "�J�����U���@��" );
	ap->work1[ X ] = 10;	// �J�����̍��W�v�Z�Ŏg�p����l
	ap->work1[ Z ] = 0;		// �U�����Ԍv���p
}
