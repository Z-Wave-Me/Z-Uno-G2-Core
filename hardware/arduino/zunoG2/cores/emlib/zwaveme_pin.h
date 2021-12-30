#ifndef ZWAVEME_PIN_H
#define ZWAVEME_PIN_H

#ifdef __cplusplus
extern "C" {
#endif

#if ZUNO_PIN_V == 3
	#define PWM1				13
	#define PWM2                14
	#define PWM3                15
	#define PWM4                16

	#define A0                  3
	#define A1                  4
	#define A2                  5
	#define A3                  6

	#define SCL                 9
	#define SDA                 10
	#define SCL1                2
	#define SDA1                24

	#define RX0					25
	#define TX0					24
	#define RX1					8
	#define TX1					7
	#define RX2					27
	#define TX2					26

	#define SCK					0//by default USART1
	#define MISO				1//by default USART1 - RX
	#define MOSI				2//by default USART1 - TX
	#define SS					8//by default
	#define SCK2				3
	#define MISO2				4
	#define MOSI2				7
	#define SS2					8

	#define LED_BUILTIN			15
	#define LED_GREEN			28
	#define LED_RED				29

	#define ZUNO_PIN_LAST_INDEX	29
#elif ZUNO_PIN_V == 4
	#define PWM1				13
	#define PWM2                14
	#define PWM3                15
	#define PWM4                16

	#define A0                  3
	#define A1                  4
	#define A2                  5
	#define A3                  6

	#define SCL                 9
	#define SDA                 10
	#define SCL1                23
	#define SDA1                25

	#define RX0					25
	#define TX0					24
	#define RX1					8
	#define TX1					7
	#define RX2					27
	#define TX2					26

	#define SCK					0//by default USART1
	#define MISO				1//by default USART1 - RX
	#define MOSI				2//by default USART1 - TX
	#define SS					8//by default
	#define SCK2				3
	#define MISO2				4
	#define MOSI2				7
	#define SS2					8

	#define LED_BUILTIN			13
	#define LED_GREEN			28
	#define LED_RED				29

	#define ZUNO_PIN_LAST_INDEX	29
#elif ZUNO_PIN_V == 6
	#define PWM1				13
	#define PWM2                14
	#define PWM3                15
	#define PWM4                16

	#define A0                  3
	#define A1                  4
	#define A2                  5
	#define A3                  6

	#define SCL                 9
	#define SDA                 10
	#define SCL1                23
	#define SDA1                25

	#define RX0					25
	#define TX0					24
	#define RX1					8
	#define TX1					7
	#define RX2					27
	#define TX2					26

	#define SCK					0//by default USART1
	#define MISO				1//by default USART1 - RX
	#define MOSI				2//by default USART1 - TX
	#define SS					8//by default
	#define SCK2				3
	#define MISO2				4
	#define MOSI2				7
	#define SS2					8

	#define LED_BUILTIN			13
	#define LED_GREEN			28
	#define LED_RED				29

	#define ZUNO_PIN_LAST_INDEX	29
#elif ZUNO_PIN_V == 1000
	#define RX0					1
	#define TX0					0

	#define LED_GREEN			3
	#define LED_RED				2

	#define ZUNO_PIN_LAST_INDEX	5
#else
	#error ZUNO_PIN_V
#endif

#ifdef __cplusplus
}
#endif

#endif//ZWAVEME_PIN_H