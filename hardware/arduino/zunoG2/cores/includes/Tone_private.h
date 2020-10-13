#ifndef TONE_PRIVATE_H
#define TONE_PRIVATE_H

#define PWM_TIMER						TIMER1
#define PWM_TIMER_CLOCK					cmuClock_TIMER1
#define PWM_HGZ							0x1EA
#define PWM_DISABLED					0x0
#define PWM_ENABLED						0xFF
#define PWM_PIN_DISABLED				0x0
#define PWM_PIN_ENABLED					0x1
#define PWM_PIN_PULSE					0x2
#define PWM_TIMER_BLOCK					g_bit_field.bLockTimer1

#define TONE_DISABLED		0x0
#define TONE_CHANNEL		0x0
#define TONE_TIMER			TIMER0
#define TONE_TIMER_CLOCK	cmuClock_TIMER0
#define TONE_HGZ_INVALID	0x0
#define TONE_TIMER_BLOCK	g_bit_field.bLockTimer0

#endif //TONE_PRIVATE_H