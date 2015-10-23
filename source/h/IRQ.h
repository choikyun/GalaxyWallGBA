#ifndef IRQ_H
#define IRQ_H

/* ---------- ���荞�ݐݒ� ----------- */

// REG_INTERUPT
// ���荞�ݔ������ɌĂяo���֐��̃A�h���X���Z�b�g
#define SetIRQ(x)	REG_INTERUPT = (u32)x

// REG_IME
// ���荞�݃}�X�^�[

// ���荞�݃}�X�^�[�I���A�I�t
#define IRQ_MASTER_ON	1
#define IRQ_MASTER_OFF	0

// REG_IE, REG_IF
// ���荞�݃Z�b�g�E����

// �ǂ̊��荞�݂��g�p�E������
#define IRQ_BIT_VBLANK	(1<<0)
#define IRQ_BIT_HBLANK	(1<<1)
#define IRQ_BIT_VCOUNT	(1<<2)
#define IRQ_BIT_TIMER0	(1<<3)
#define IRQ_BIT_TIMER1	(1<<4)
#define IRQ_BIT_TIMER2	(1<<5)
#define IRQ_BIT_TIMER3	(1<<6)
#define IRQ_BIT_SERIAL	(1<<7)
#define IRQ_BIT_DMA0	(1<<8)
#define IRQ_BIT_DMA1	(1<<9)
#define IRQ_BIT_DMA2	(1<<10)
#define IRQ_BIT_DMA3	(1<<11)
#define IRQ_BIT_KEYS	(1<<12)
#define IRQ_BIT_CART	(1<<13)

#endif

