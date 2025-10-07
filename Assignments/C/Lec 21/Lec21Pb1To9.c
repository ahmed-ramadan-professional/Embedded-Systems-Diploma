#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

#include "InputParser.h"

#define FALSE 0
#define TRUE 1u

// i swear i wasn't trying to make a kernal or something
// but things got out of hand so quickly ¯\(°_o)/¯
typedef enum {
    NO_OPERATION_SELECTED,
    INITIALIZE_LINKED_LIST_WITH_MULTIPLE_VALUES,
    INSERT_AFTER_RELATIVE_TO_VALUE,
    INSERT_BEFORE_RELATIVE_TO_VALUE,
    INSERT_AT_POSITION,
    DELETE_VALUE,
    REVERSE_LINKED_LIST,
    RETRIEVE_MIDDLE_VALUES,
    CALCULATE_VALUES_SUM,
    FIND_MAXIMUM_VALUE,
    DELETE_ENTIRE_LIST,
    EXIT,

} Operation;

typedef enum {
    OPERATION_SELECT_STAGE,
    OPERATION_INPUT_STAGE,
    OPERATION_OUTPUT_STAGE,
    GO_BACK_STAGE
} UserStage;

typedef struct Node_s {
    int32_t value;
    struct Node_s *next;
} Node_t;

typedef struct {
    Node_t *linked;
    Node_t *output;
    char **inputs;
    UserStage stage;
    Operation operation;
    uint8_t is_exit_requested;

} ProgramState;

uint8_t in_linked(Node_t *linked, int32_t value) {
    Node_t *ptr = linked;
    while (ptr != NULL) {
        if (ptr->value == value) return (uint8_t)1;
        ptr = ptr->next;
    }
    return 0;
}

uint16_t len_linked(Node_t *linked) {
    Node_t *ptr = linked;
    uint16_t counter = 0;
    while (ptr != NULL) {
        counter++;
        ptr = ptr->next;
    }
    return counter;
}

// the beauty of recursion
// Lec21Pb1
Node_t *linked_insert_multiple_at_start(Node_t *linked, char **inputs) {
    if (*inputs == NULL) return linked;

    linked = linked_insert_multiple_at_start(linked, inputs + 1);

    Node_t *temp = linked;
    linked = (Node_t *)malloc(sizeof(Node_t));
    linked->value = eval_int(*inputs);
    linked->next = temp;
    return linked;
}

// decided to not use recursion in the following implementations
// if the array gets so large the excessive recursion will cause stack overflow
// especially when dealing with embedded system small memory
// Lec21Pb2
Node_t *linked_insert_after_relative(Node_t *linked, int32_t old, int32_t new) {
    Node_t *ptr = linked;
    while (ptr != NULL) {
        if (ptr->value == old) {
            Node_t *temp = ptr->next;
            ptr->next = (Node_t *)malloc(sizeof(Node_t));
            ptr->next->value = new;
            ptr->next->next = temp;
            return linked;
        }
        ptr = ptr->next;
    }
}

// Lec21Pb3
Node_t *linked_insert_before_relative(Node_t *linked, int32_t old, int32_t new) {
    Node_t *ptr = linked;

    if (linked->value == old) {
        linked = (Node_t *)malloc(sizeof(Node_t));
        linked->value = new;
        linked->next = ptr;
        return linked;
    }

    while (ptr != NULL && ptr->next != NULL) {
        if (ptr->next->value == old) {
            Node_t *temp = ptr->next;
            ptr->next = (Node_t *)malloc(sizeof(Node_t));
            ptr->next->value = new;
            ptr->next->next = temp;
            return linked;
        }
        ptr = ptr->next;
    }
}

// Lec21Pb4
Node_t *linked_insert_at_position(Node_t *linked, uint16_t position, int32_t value) {
    uint16_t counter = 1u;
    Node_t *ptr = linked;

    if (position == 1) {
        linked = (Node_t *)malloc(sizeof(Node_t));
        linked->value = value;
        linked->next = ptr;
        return linked;
    }

    while (ptr != NULL) {
        if (counter == position - 1) { // to insert after the position -1
            Node_t *temp = ptr->next;
            ptr->next = (Node_t *)malloc(sizeof(Node_t));
            ptr->next->value = value;
            ptr->next->next = temp;
            return linked;
        }
        ptr = ptr->next;
        counter++;
    }
}

// Lec21Pb5
Node_t *linked_delete_value(Node_t *linked, int32_t value) {

    if (linked != NULL && linked->value == value) {
        Node_t *temp = linked->next;
        free(linked);
        return temp;
    }

    Node_t *ptr = linked;
    while (ptr != NULL) {
        if (ptr->next->value == value) {
            Node_t *temp = ptr->next;
            ptr->next = ptr->next->next;
            free(temp);
            return linked;
        }
        ptr = ptr->next;
    }
}

// Lec21Pb6
Node_t *linked_reverse(Node_t *linked) {
    Node_t *previous = linked, *ptr = linked->next;
    previous->next = NULL;
    while (ptr != NULL) {
        Node_t *temp = ptr->next;
        ptr->next = previous;
        previous = ptr;
        ptr = temp;
    }
    return previous;
}

// Lec21Pb7
Node_t *linked_get_subsection(Node_t *linked, uint16_t position_1, uint16_t position_2) {
    uint16_t counter = 1u;
    Node_t *linked_ptr = linked, *output = NULL, *output_ptr = NULL;

    while (linked_ptr != NULL && counter <= position_2) {
        if (counter == position_1) {
            output = (Node_t *)malloc(sizeof(Node_t));
            output->value = linked_ptr->value;
            output->next = NULL;
            output_ptr = output;
        }

        if (counter > position_1) {
            output_ptr->next = (Node_t *)malloc(sizeof(Node_t));
            output_ptr->next->value = linked_ptr->value;
            output_ptr->next->next = NULL;
            output_ptr = output_ptr->next;
        }

        linked_ptr = linked_ptr->next;
        counter++;
    }
    return output;
}

// Lec21Pb7
Node_t *linked_get_middle_values(Node_t *linked) {
    uint16_t len = len_linked(linked);
    if (len % 2 == 0) return linked_get_subsection(linked, len / 2, len / 2 + 1);
    return linked_get_subsection(linked, len / 2u + 1u, len / 2u + 1u);
}

// Lec21Pb8
Node_t *linked_calculate_sum(Node_t *linked) {
    Node_t *output = (Node_t *)malloc(sizeof(Node_t)), *ptr = linked;
    output->value = 0;
    output->next = NULL;

    while (ptr != NULL) {
        output->value += ptr->value;
        ptr = ptr->next;
    }

    return output;
}

// Lec21Pb9
Node_t *linked_find_maximum_value(Node_t *linked) {
    Node_t *output = (Node_t *)malloc(sizeof(Node_t)), *ptr = linked;
    output->value = linked->value;
    output->next = NULL;

    while (ptr != NULL) {
        if (ptr->value > output->value) output->value = ptr->value;
        ptr = ptr->next;
    }

    return output;
}

void free_linked(Node_t *linked) {
    Node_t *ptr = linked;
    while (ptr != NULL) {
        Node_t *temp = ptr;
        ptr = ptr->next;
        free(temp);
    }
    linked = NULL;
}

uint8_t is_linked_required_and_not_null(Node_t *linked, Operation operation) {
    switch (operation) {
        case INITIALIZE_LINKED_LIST_WITH_MULTIPLE_VALUES:
        case INSERT_AT_POSITION:
        case EXIT:
            return 1u;

        case INSERT_AFTER_RELATIVE_TO_VALUE:
        case INSERT_BEFORE_RELATIVE_TO_VALUE:
        case DELETE_VALUE:
        case REVERSE_LINKED_LIST:
        case RETRIEVE_MIDDLE_VALUES:
        case FIND_MAXIMUM_VALUE:
        case CALCULATE_VALUES_SUM:
        case DELETE_ENTIRE_LIST:
            return linked != NULL;

        default:
            return 0;
    }
}

uint8_t validate(ProgramState *state) {
    if (basic_validator(state->inputs, ONE_INPUT_AND_ONE_CHARACTER_PRESENT) &&
        in_str("EeBb", *state->inputs[0])) return 1;

    switch (state->operation) {
        case NO_OPERATION_SELECTED:
            return basic_validator(state->inputs, ONE_NUMERIC_VALUE) &&
                   (Operation)eval_int(state->inputs[0]) > 0 &&
                   (Operation)eval_int(state->inputs[0]) <= EXIT &&
                   is_linked_required_and_not_null(state->linked, (Operation)eval_int(state->inputs[0]));

        case INITIALIZE_LINKED_LIST_WITH_MULTIPLE_VALUES:
            return basic_validator(state->inputs, ONE_OR_MORE_NUMERIC_VALUES);

        case INSERT_BEFORE_RELATIVE_TO_VALUE:
        case INSERT_AFTER_RELATIVE_TO_VALUE:
            return basic_validator(state->inputs, TWO_NUMERIC_VALUES) && in_linked(state->linked, eval_int(state->inputs[0]));

        case INSERT_AT_POSITION:
            return basic_validator(state->inputs, TWO_NUMERIC_VALUES) &&
                   eval_int(state->inputs[0]) > 0 &&
                   eval_int(state->inputs[0]) <= len_linked(state->linked) + (uint16_t)1;

        case DELETE_VALUE:
            return basic_validator(state->inputs, ONE_NUMERIC_VALUE) && in_linked(state->linked, eval_int(state->inputs[0]));

        case REVERSE_LINKED_LIST:
        case RETRIEVE_MIDDLE_VALUES:
        case FIND_MAXIMUM_VALUE:
        case CALCULATE_VALUES_SUM:
        case DELETE_ENTIRE_LIST:
            return 1u;

        default:
            return 0;
    }
}

void print_linked(Node_t *linked, uint8_t print_null) {
    while (linked != NULL) {
        printf("[%d]", linked->value);
        if (linked->next != NULL || print_null) printf("-");
        linked = linked->next;
    }
    if (print_null) printf("[null]");
}

void inner_frame(ProgramState *state) {
    switch (state->stage) {
        case OPERATION_SELECT_STAGE:
            printf("(01) Initialize a linked list using a set of values or insert multiple values at start\n");
            printf("(02) Insert a node after another value present in the linked list above\n");
            printf("(03) Insert a node before another value present in the linked list above\n");
            printf("(04) Insert a node at a certain postion in the linked list above\n");
            printf("(05) Delete a value from the linked list above\n");
            printf("(06) Reverse the linked list above\n");
            printf("(07) Retrieve middle value/values in the linked list above\n");
            printf("(08) Calculate the sum of all the values present in the linked list above\n");
            printf("(09) Find the maximum value of all the values in the linked list above\n");
            printf("(10) Delete the entire linked list above\n");
            printf("(11) Exit\n\n");
            break;

        case OPERATION_INPUT_STAGE:
            switch (state->operation) {
                case INITIALIZE_LINKED_LIST_WITH_MULTIPLE_VALUES:
                    printf("- Enter a list of values on the same line each separated by a space\n");
                    break;

                case INSERT_AFTER_RELATIVE_TO_VALUE:
                    printf("- Enter a value you want to insert the new node after\n");
                    printf("- Then enter the new value, All on the same line separated by a space\n");
                    break;

                case INSERT_BEFORE_RELATIVE_TO_VALUE:
                    printf("- Enter a value you want to insert the new node before\n");
                    printf("- Then enter the new value, All on the same line separated by a space\n");
                    break;

                case INSERT_AT_POSITION:
                    printf("- Enter a position you want to insert the new node at\n");
                    printf("- Then enter the new value, All on the same line separated by a space\n");
                    break;

                case DELETE_VALUE:
                    printf("- Enter a value you want to delete\n");
                    break;

                default:

                    break;
            }
            printf("- Or enter \"b\" to go back or \"e\" to exit\n\n");
            break;

        case OPERATION_OUTPUT_STAGE:
            switch (state->operation) {
                case RETRIEVE_MIDDLE_VALUES:
                    printf("- Linked list middle values are : ");
                    print_linked(state->output, FALSE);
                    printf("\n");
                    break;

                case FIND_MAXIMUM_VALUE:
                    printf("- Linked list maximum value is : ");
                    print_linked(state->output, FALSE);
                    printf("\n");
                    break;

                case CALCULATE_VALUES_SUM:
                    printf("- Linked list values sum is : ");
                    print_linked(state->output, FALSE);
                    printf("\n");
                    break;

                default:
                    break;
            }
            printf("- Enter \"b\" to go back or \"e\" to exit\n\n");
            printf("\n");
            free(state->output);
            state->output = NULL;
            break;

        default:
            break;
    }
}

void main_frame(ProgramState *state, uint16_t failed_validation_counter) {
    char input_str[101];

    system("cls");
    printf("Linked List : ");
    print_linked(state->linked, TRUE);
    printf("\n\n");

    inner_frame(state);

    // maybe in the future we could implement a custom message for every validation rule
    if (failed_validation_counter) printf("Invalid Input! ");
    if (failed_validation_counter > 1) printf("[%d] ", failed_validation_counter);

    printf("> ");
    scanf(" %100[^\n]", input_str);
    flush_stdin();

    state->inputs = str_explode(input_str, ' ');
}

void operator(ProgramState *state) {
    switch (state->operation) {
        case INITIALIZE_LINKED_LIST_WITH_MULTIPLE_VALUES:
            state->linked = linked_insert_multiple_at_start(state->linked, state->inputs);
            break;

        case INSERT_AFTER_RELATIVE_TO_VALUE:
            state->linked = linked_insert_after_relative(state->linked, eval_int(state->inputs[0]), eval_int(state->inputs[1]));
            break;

        case INSERT_BEFORE_RELATIVE_TO_VALUE:
            state->linked = linked_insert_before_relative(state->linked, eval_int(state->inputs[0]), eval_int(state->inputs[1]));
            break;

        case INSERT_AT_POSITION:
            state->linked = linked_insert_at_position(state->linked, eval_int(state->inputs[0]), eval_int(state->inputs[1]));
            break;

        case DELETE_VALUE:
            state->linked = linked_delete_value(state->linked, eval_int(state->inputs[0]));
            break;

        case REVERSE_LINKED_LIST:
            state->linked = linked_reverse(state->linked);
            break;

        case RETRIEVE_MIDDLE_VALUES:
            state->output = linked_get_middle_values(state->linked);
            break;

        case FIND_MAXIMUM_VALUE:
            state->output = linked_find_maximum_value(state->linked);
            break;

        case CALCULATE_VALUES_SUM:
            state->output = linked_calculate_sum(state->linked);
            break;

        case DELETE_ENTIRE_LIST:
            free_linked(state->linked);
            state->linked = NULL;
            break;

        default:
            break;
    }
}

void user_input_resolver(ProgramState *state) {
    switch (state->stage) {
        case OPERATION_SELECT_STAGE:
            state->operation = eval_int(state->inputs[0]);
            state->stage = OPERATION_INPUT_STAGE;
            break;

        case OPERATION_INPUT_STAGE:
            operator(state);
            state->stage = state->output != NULL ? OPERATION_OUTPUT_STAGE : OPERATION_SELECT_STAGE;
            state->operation = state->output != NULL ? state->operation : NO_OPERATION_SELECTED;
            break;

        case OPERATION_OUTPUT_STAGE:
            state->operation = NO_OPERATION_SELECTED;
            state->stage = OPERATION_SELECT_STAGE;

        case GO_BACK_STAGE:
            state->stage = OPERATION_SELECT_STAGE;
            state->operation = NO_OPERATION_SELECTED;
            break;

        default:
            break;
    }

    free_inputs(state->inputs);
    state->inputs = NULL;
}

void user_input_output_handler(ProgramState *state) {
    uint16_t failed_validation_counter = (uint16_t)0;

    while (state->output != NULL || !validate(state)) {
        main_frame(state, failed_validation_counter++);
    }

    if (state->inputs != NULL && in_str("Ee", *(state->inputs)[0])) state->is_exit_requested = TRUE;
    if (state->inputs != NULL && in_str("Bb", *(state->inputs)[0])) state->stage = GO_BACK_STAGE;

    user_input_resolver(state);
}

int main(int argc, char const *argv[]) {
    ProgramState state;

    state.operation = NO_OPERATION_SELECTED;
    state.stage = OPERATION_SELECT_STAGE;
    state.inputs = NULL;
    state.is_exit_requested = FALSE;
    state.linked = NULL;
    state.output = NULL;

    while (TRUE) {
        user_input_output_handler(&state);
        if (state.operation == EXIT || state.is_exit_requested) break;
    }

    return 0;
}