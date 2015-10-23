
#ifndef TIMER_H
#define TIMER_H

// �^�C�}�[��I/O���W�X�^�Ɋւ���ݒ�
/*
 #define REG_TM0D       *(u16*)0x4000100
 #define REG_TM0CNT     *(u16*)0x4000102
 #define REG_TM1D       *(u16*)0x4000104
 #define REG_TM1CNT     *(u16*)0x4000106
 #define REG_TM2D       *(u16*)0x4000108
 #define REG_TM2CNT     *(u16*)0x400010A
 #define REG_TM3D       *(u16*)0x400010C
 #define REG_TM3CNT     *(u16*)0x400010E
 */

// REG_TMxCNT
// �^�C�}�[���i�ގ����@���N���b�N��1��i�ނ�
#define TM_FREQ_PER_1	0
#define TM_FREQ_PER_64	1
#define TM_FREQ_PER_256	2
#define TM_FREQ_PER_1024	3
// �J�X�P�[�h
// ���ʂ̃^�C�}�[�̃I�[�o�[�t���[����1��i��
// �����͖��������
#define TM_CASCADE	(1<<2)
// ���̃^�C�}�[�Ŋ��荞�݂𔭐�������
#define TM_USEIRQ	(1<<6)
// ���̃^�C�}�[���g���i�}�X�^�[�j
#define TM_ENABLE	(1<<7)
#define TM_DISABLE	(0<<7)	// �g��Ȃ�

#endif

