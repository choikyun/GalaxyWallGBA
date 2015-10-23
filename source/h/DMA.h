// DMA�̐ݒ�

#ifndef DMA_H
#define DMA_H

// DMA0�]��
#define DMA0TRANSFER(sad,dad,size,mode)	\
	REG_DM0SAD = sad;	\
	REG_DM0DAD = dad;	\
	REG_DM0CNT_L = size;	\
	REG_DM0CNT_H = mode

// DMA1�]��
#define DMA1TRANSFER(sad,dad,size,mode)	\
	REG_DM1SAD = sad;	\
	REG_DM1DAD = dad;	\
	REG_DM1CNT_L = size;	\
	REG_DM1CNT_H = mode

// DMA2�]��
#define DMA2TRANSFER(sad,dad,size,mode)	\
	REG_DM2SAD = sad;	\
	REG_DM2DAD = dad;	\
	REG_DM2CNT_L = size;	\
	REG_DM2CNT_H = mode

// DMA3�]��
#define DMA3TRANSFER(sad,dad,size,mode)	\
	REG_DM3SAD = sad;	\
	REG_DM3DAD = dad;	\
	REG_DM3CNT_L = size;	\
	REG_DM3CNT_H = mode

// �]���J�n�E���~
#define DMA_TRANSFER_ON		(1<<15)
#define DMA_TRANSFER_OFF	(0<<15)

// ���荞�ݎg�p�E�s�g�p
#define DMA_INTR_ON		(1<<14)
#define DMA_INTR_OFF	(0<<14)

// �]���^�C�~���O
#define DMA_TIMING_NOW		(0<<12) // �����ɊJ�n
#define DMA_TIMING_VBLANK	(1<<12) // Vblank�ɊJ�n
#define DMA_TIMING_HBLANK	(2<<12) // Hblank�ɊJ�n
#define DMA_TIMING_FIFO		(3<<12) // FIFO���N�G�X�g�ŊJ�n DMA1CNT_H �̂�
#define DMA_TIMING_DRAWLINE	(3<<12) // ���C���`�掞�ɊJ�n DMA3CNT_H �̂�

#define DMA_ROM_REQUEST		(1<<11) // ROM���烊�N�G�X�g�ŊJ�n DMA3CNT_H �̂�

// ��x�̓]���T�C�Y
#define DMA_SIZE_16		(0<<10) // 16bit���� size/2
#define DMA_SIZE_32		(1<<10) // 32bit���� size/4

// ���s�[�g�ݒ�
#define DMA_REPEAT_ON	(1<<9)
#define DMA_REPEAT_OFF	(0<<9)

// �]�����A�h���X�̑����ݒ�
#define DMA_SAD_INC		(0<<7) // �]�����ƂɃC���N�������g
#define DMA_SAD_DEC		(1<<7) // �]�����ƂɃf�N�������g
#define DMA_SAD_FIX		(2<<7) // �Œ�

// �]����A�h���X�̑����ݒ�
#define DMA_DAD_INC		(0<<5) // �]�����ƂɃC���N�������g
#define DMA_DAD_DEC		(1<<5) // �]�����ƂɃf�N�������g
#define DMA_DAD_FIX		(2<<5) // �Œ�
#define DMA_DAD_RESET	(3<<5) // �C���N�������g�A�]���I�����Ƀ��Z�b�g

#endif

