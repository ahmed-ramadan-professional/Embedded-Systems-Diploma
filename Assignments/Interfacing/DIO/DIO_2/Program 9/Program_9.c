#include <avr/io.h>
#include <util/delay.h>

#include <Library/BIT_MATH/BIT_MATH.h>
#include <Library/DOUBLE_7_SEGMENT/DOUBLE_7_SEGMENTS.h>

#define BLINK_CYCLE 300

void main(void) {
    double_7_segments_init(&PORTA, &DDRA, &PORTC, &DDRC, 7, 6);
    while (1) {
        CLEAR_BIT(PORTC,2);
        SET_BIT(DDRC,0);
        SET_BIT(PORTC,0);
        double_7_segments_count_down(0,1,0,0);
        CLEAR_BIT(PORTC,0);
        SET_BIT(DDRC,1);
        SET_BIT(PORTC,1);
        double_7_segments_count_down(0,1,0,0);
        CLEAR_BIT(PORTC,1);
        SET_BIT(DDRC,2);
        SET_BIT(PORTC,2);
        double_7_segments_count_down(0,3,0,0);
       
    }
}
