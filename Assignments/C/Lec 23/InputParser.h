#include <stdint.h>

#ifndef INPUT_PARSER_H
#define INPUT_PARSER_H

#define STR_EXPLODE_BUFFER_SIZE 50

typedef enum {
    ANY,
    NUMERIC,
    ALPHABETIC,
} InputType;

typedef enum {
    ONE_NUMERIC_VALUE,
    ONE_OR_MORE_NUMERIC_VALUES,
    ONE_INPUT_AND_ONE_CHARACTER_PRESENT,
    TWO_NUMERIC_VALUES,
    TWO_OR_MORE_NUMERIC_VALUES,
} ValidationRule;

void str_cpy(char *str_1, char *str_2, uint16_t size);
char **str_explode(char *str, char separator);
uint8_t is_number(char *str);
uint8_t is_positive_number(char *str);
int32_t eval_int(char *str);
uint8_t is_inputs_count(char **inputs, InputType type, char sign, uint8_t input_count);
void flush_stdin();
uint8_t basic_validator(char **inputs, ValidationRule rule);
uint8_t in_str(char *str, char c);
void free_inputs(char **inputs);
uint16_t str_len(char *str);
uint16_t digits_count(int num);
uint16_t digits_plus_sign_count(int num);
int32_t get_maximum_value(char **inputs);
int32_t get_minimum_value(char **inputs);

#endif