#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

#include "InputParser.h"

#define FALSE 0
#define TRUE 1u

#define NUMBER_OF_LINKED_LISTS 2
#define FAILED_VALIDATION_MESSAGE_BUFFER_SIZE 101

typedef enum {
    UNSET,
    DOUBLY,
    CIRCULAR,
} LinkedType;

typedef enum {
    OPERATION_SELECT_STAGE,
    LINKED_SELECT_STAGE,
    LINKED_TYPE_SELECT_STAGE,
    OPERATION_INPUT_STAGE,
    OPERATION_OUTPUT_STAGE,
    GO_BACK_TO_PREVIOUS_STAGE,
    GO_BACK_TO_MAIN_MENU_STAGE
} Stage;

typedef enum {
    NO_OPERATION_SELECTED,
    LINKED_INITIALIZE_AND_INSERT_ONE,
    LINKED_INITIALIZE_AND_INSERT_MULTIPLE,
    LINKED_INSERT_ONE_AT_START,
    LINKED_INSERT_ONE_OR_MORE_AT_START,
    LINKED_INSERT_ONE_AT_END,
    LINKED_INSERT_ONE_OR_MORE_AT_END,
    LINKED_INSERT_AFTER_VALUE,
    LINKED_INSERT_BEFORE_VALUE,
    LINKED_INSERT_AT_POSITION,
    LINKED_DELETE_VALUE,
    LINKED_REVERSE,
    LINKED_CONCATENATE,
    LINKED_CONVERT_LINKED_TYPE,
    DELETE_ENTIRE_LIST,
    INSPECT_LINKS,
    EXIT,
} Operation;

typedef struct Node_s {
    int32_t value;
    struct Node_s *next;
    struct Node_s *prev;
} Node_t;

typedef struct UserStage_s {
    Stage stage;
    struct UserStage_s *prev;

} UserStage_t;

typedef struct {
    Node_t *output;
    Node_t *linked[NUMBER_OF_LINKED_LISTS];
    char **inputs;
    UserStage_t *current_stage;
    Operation operation;
    LinkedType selected_linked_list_type;
    int8_t selected_linked_list;
    uint8_t is_exit_requested;
} ProgramState;

char failed_validation_message[FAILED_VALIDATION_MESSAGE_BUFFER_SIZE];

uint16_t len_linked(Node_t *linked) {
    Node_t *ptr = linked;
    uint16_t counter = 0;

    if (!linked) return counter;

    do {
        counter++;
        ptr = ptr->next;
    } while (ptr != NULL && ptr != linked);
    return counter;
}

// Lec23Pb1
Node_t *doubly_insert_value_start(Node_t *linked, int32_t value) {
    Node_t *temp = linked;
    linked = (Node_t *)malloc(sizeof(Node_t));
    linked->value = value;
    linked->next = temp;
    linked->prev = NULL;
    if (temp) temp->prev = linked;
    return linked;
}

// Lec23Pb2
Node_t *doubly_insert_value_end(Node_t *linked, int32_t value) {
    Node_t *ptr = linked;

    while (ptr->next) ptr = ptr->next;

    Node_t *temp = ptr;
    ptr = (Node_t *)malloc(sizeof(Node_t));
    ptr->value = value;
    ptr->next = NULL;
    ptr->prev = temp;
    if (temp) temp->next = ptr;
    if (!linked) linked = ptr;

    return linked;
}

// Lec23Pb3
Node_t *doubly_insert_value_empty(Node_t *linked, int32_t value) {
    linked = (Node_t *)malloc(sizeof(Node_t));
    linked->value = value;
    linked->next = NULL;
    linked->prev = NULL;
    return linked;
}

// Lec23Pb4
Node_t *doubly_insert_multiple_at_start(Node_t *linked, char **inputs) {
    if (*inputs == NULL) return linked;

    linked = doubly_insert_multiple_at_start(linked, inputs + 1);

    Node_t *temp = linked;
    linked = (Node_t *)malloc(sizeof(Node_t));
    linked->value = eval_int(*inputs);
    linked->next = temp;
    linked->prev = NULL;
    if (temp) temp->prev = linked;

    return linked;
}

// Lec23Pb5 and Lec23Pb14
Node_t *linked_insert_after_value(Node_t *linked, int32_t old, int32_t new) {
    Node_t *ptr = linked;
    do {
        if (ptr && ptr->value == old) {
            Node_t *temp = ptr->next;
            ptr->next = (Node_t *)malloc(sizeof(Node_t));
            ptr->next->value = new;
            ptr->next->next = temp;
            ptr->next->prev = ptr;
            if (temp) temp->prev = ptr->next;
            return linked;
        }
        ptr = ptr->next;
    } while (ptr != NULL && ptr != linked);
}

// Lec23Pb6 and Lec23Pb15
Node_t *linked_insert_before_value(Node_t *linked, int32_t old, int32_t new) {
    Node_t *ptr = linked;

    if (linked->value == old) {
        Node_t *temp = linked;
        linked = (Node_t *)malloc(sizeof(Node_t));
        linked->value = new;
        linked->next = temp;
        if (temp) linked->prev = temp->prev;
        if (temp && temp->prev && temp->prev->next) temp->prev->next = linked;
        if (temp) temp->prev = linked;

        return linked;
    }

    while (ptr != NULL && ptr->next != NULL && ptr->next != linked) {
        if (ptr->next->value == old) {
            Node_t *temp = ptr->next;
            ptr->next = (Node_t *)malloc(sizeof(Node_t));
            ptr->next->value = new;
            ptr->next->next = temp;
            ptr->next->prev = ptr;
            if (temp) temp->prev = ptr->next;
            return linked;
        }
        ptr = ptr->next;
    }
}

// Lec23Pb7 and Lec23Pb-
Node_t *linked_delete_value(Node_t *linked, int32_t value) {

    if (len_linked(linked) == 1) {
        free(linked);
        return NULL;
    }

    if (linked != NULL && linked->value == value) {
        Node_t *temp = linked->next;
        temp->prev = linked->prev;
        if (linked->prev) linked->prev->next = temp;
        free(linked);
        return temp;
    }

    Node_t *ptr = linked;
    while (ptr != NULL) {
        if (ptr->next->value == value) {
            Node_t *temp = ptr->next;
            ptr->next = temp->next;
            if (ptr->next) ptr->next->prev = ptr;
            free(temp);
            return linked;
        }
        ptr = ptr->next;
    }
}

// Lec23Pb8 and Lec23Pb-
Node_t *linked_reverse(Node_t *start) {
    if (len_linked(start) < 2) return start;
    Node_t *end = start->prev ? start->prev : NULL;
    Node_t *ptr = start;
    do {
        if (!ptr->next) end = ptr;
        Node_t *temp = ptr->next;
        ptr->next = ptr->prev;
        ptr->prev = temp;
        ptr = temp;
    } while (ptr != NULL && ptr != start);
    return end;
}

// Lec23Pb- and Lec23Pb9
void linked_print(Node_t *start, uint8_t print_extra) {
    Node_t *ptr = start;

    if (!start) return;

    print_extra ? ptr->prev ? printf("[%d<prev]=", ptr->prev->value) : printf("[null]=") : printf("");
    do {
        printf("[%d]", ptr->value);
        if (ptr->next != start && ptr->next != NULL) printf("=");
        print_extra && (ptr->next == start || ptr->next == NULL) ? ptr->next
                                                                       ? printf("=[next>%d]", ptr->next->value)
                                                                       : printf("=[null]")
                                                                 : printf("");
        ptr = ptr->next;
    } while (ptr != NULL && ptr != start);
}

// Lec23Pb10
Node_t *circular_insert_value_start(Node_t *linked, int32_t value) {
    Node_t *temp = linked;
    linked = (Node_t *)malloc(sizeof(Node_t));
    linked->value = value;

    linked->next = temp ? temp : linked;
    linked->prev = temp ? temp->prev : linked;
    if (temp) temp->prev->next = linked;
    if (temp) temp->prev = linked;
    if (temp && temp->next == temp) temp->next = linked;

    return linked;
}

// Lec23Pb11
Node_t *circular_insert_value_empty(Node_t *linked, int32_t value) {
    linked = (Node_t *)malloc(sizeof(Node_t));
    linked->value = value;
    linked->next = linked;
    linked->prev = linked;
    return linked;
}

// Lec23Pb12
Node_t *circular_insert_value_end(Node_t *linked, int32_t value) {
    Node_t *ptr = linked;

    while (ptr->next != linked) ptr = ptr->next;

    Node_t *temp = ptr;
    ptr = (Node_t *)malloc(sizeof(Node_t));
    ptr->value = value;
    ptr->next = temp ? temp->next : ptr;
    ptr->prev = temp;
    if (temp) temp->next = ptr;
    if (temp && temp->prev == temp) temp->prev = ptr;
    if (!linked) linked = ptr;
    linked->prev = ptr;

    return linked;
}

// Lec23Pb13
Node_t *circular_insert_multiple_at_start(Node_t *linked, char **inputs) {
    if (*inputs == NULL) return linked;

    linked = circular_insert_multiple_at_start(linked, inputs + 1);

    Node_t *temp = linked;
    linked = (Node_t *)malloc(sizeof(Node_t));
    linked->value = eval_int(*inputs);

    linked->next = temp ? temp : linked;
    linked->prev = temp ? temp->prev : linked;
    if (temp) temp->prev->next = linked;
    if (temp) temp->prev = linked;
    if (temp && temp->next == temp) temp->next = linked;

    return linked;
}

// Lec23Pb16
Node_t *circular_concatenate(Node_t *result, Node_t *added_list) {
    Node_t *ptr = result->prev;
    Node_t *added_list_first = added_list;
    do {
        Node_t *temp = ptr->next;
        ptr->next = (Node_t *)malloc(sizeof(Node_t));
        ptr->next->value = added_list->value;
        ptr->next->next = temp;
        ptr->next->prev = ptr;
        temp->prev = ptr->next;
        ptr = ptr->next;
        added_list = added_list->next;
    } while (added_list != added_list_first);

    return result;
}

Node_t *doubly_concatenate(Node_t *result, Node_t *added_list) {
    Node_t *ptr = result;
    while (ptr->next != NULL) ptr = ptr->next;
    while (added_list != NULL) {
        ptr->next = (Node_t *)malloc(sizeof(Node_t));
        ptr->next->value = added_list->value;
        ptr->next->next = NULL;
        ptr->next->prev = ptr;
        ptr = ptr->next;
        added_list = added_list->next;
    }
    return result;
}

LinkedType linked_get_type(Node_t *start) {
    return start ? start->prev == NULL ? DOUBLY : CIRCULAR : UNSET;
}

uint8_t linked_is_doubly(Node_t *start) {
    return linked_get_type(start) == DOUBLY;
}

uint8_t linked_is_circular(Node_t *start) {
    return linked_get_type(start) == CIRCULAR;
}

Node_t *linked_concatenate_all(ProgramState *state) {
    char **inputs = state->inputs;
    Node_t *result = state->linked[eval_int(*inputs++) - (int32_t)1];
    LinkedType type = linked_get_type(result);
    while (*inputs != NULL) {
        int32_t i = eval_int(*inputs++) - (int32_t)1;
        if (type == DOUBLY)
            result = doubly_concatenate(result, state->linked[i]);
        if (type == CIRCULAR)
            result = circular_concatenate(result, state->linked[i]);
    }
}

Node_t *doubly_insert_multiple_at_end(Node_t *linked, char **inputs) {
    Node_t *ptr = linked;

    while (*inputs != NULL) {
        if (ptr && ptr->next) {
            ptr = ptr->next;
            continue;
        }

        Node_t *temp = ptr;
        ptr = (Node_t *)malloc(sizeof(Node_t));
        ptr->value = eval_int(*inputs);
        ptr->next = NULL;
        ptr->prev = temp;
        if (temp) temp->next = ptr;
        if (!linked) linked = ptr;
        inputs++;
    }

    return linked;
}

Node_t *circular_insert_multiple_at_end(Node_t *linked, char **inputs) {
    Node_t *ptr = linked;

    while (*inputs != NULL) {
        if (ptr && ptr->next != linked) {
            ptr = ptr->next;
            continue;
        }

        Node_t *temp = ptr;
        ptr = (Node_t *)malloc(sizeof(Node_t));
        ptr->value = eval_int(*inputs);
        ptr->next = temp ? temp->next : ptr;
        ptr->prev = temp;
        if (temp) temp->next = ptr;
        if (temp && temp->prev == temp) temp->prev = ptr;
        if (!linked) linked = ptr;
        linked->prev = ptr;
        inputs++;
    }
    return linked;
}

Node_t *linked_insert_at_position(Node_t *linked, uint16_t position, int32_t value) {
    uint16_t counter = 1u;
    Node_t *ptr = linked;

    if (position == 1) {
        Node_t *temp = linked;
        linked = (Node_t *)malloc(sizeof(Node_t));
        linked->value = value;
        linked->next = temp;
        if (temp) linked->prev = temp->prev;
        if (temp && temp->prev && temp->prev->next) temp->prev->next = linked;
        if (temp) temp->prev = linked;

        return linked;
    }

    do {
        if (ptr && counter == position - 1) {
            Node_t *temp = ptr->next;
            ptr->next = (Node_t *)malloc(sizeof(Node_t));
            ptr->next->value = value;
            ptr->next->next = temp;
            ptr->next->prev = ptr;
            if (temp) temp->prev = ptr->next;
            return linked;
        }
        ptr = ptr->next;
        counter++;
    } while (ptr != NULL && ptr != linked);
}

Node_t *convert_doubly_to_circular(Node_t *start) {
    Node_t *ptr = start;
    while (ptr->next != NULL) ptr = ptr->next;
    start->prev = ptr;
    ptr->next = start;
    return start;
}

Node_t *convert_circular_to_doubly(Node_t *start) {
    Node_t *ptr = start->prev;
    ptr->next = NULL;
    start->prev = NULL;
    return start;
}

uint8_t in_linked(Node_t *linked, int32_t value) {
    if(!linked) return 0;

    Node_t *ptr = linked;
    do {
        if (ptr->value == value) return (uint8_t)1;
        ptr = ptr->next;
    } while (ptr != NULL && ptr != linked);
    
    if (!str_len(failed_validation_message)) sprintf(failed_validation_message, "Value is not present in the linked list");
    return 0;
}

Node_t *free_linked(Node_t *start) {
    Node_t *ptr = start;
    do {
        Node_t *temp = ptr->next != start ? ptr->next : NULL;
        free(ptr);
        ptr = temp;
    } while (ptr != NULL);
    return ptr;
}

uint8_t is_linked_required_and_not_null(Node_t *linked, Operation operation) {
    uint8_t is_valid;
    switch (operation) {
        case EXIT:
            return 1u;

        case INSPECT_LINKS:
        case DELETE_ENTIRE_LIST:
        case LINKED_INSERT_ONE_OR_MORE_AT_START:
        case LINKED_INSERT_ONE_OR_MORE_AT_END:
        case LINKED_INSERT_AFTER_VALUE:
        case LINKED_INSERT_BEFORE_VALUE:
        case LINKED_INSERT_AT_POSITION:
        case LINKED_DELETE_VALUE:
        case LINKED_REVERSE:
        case LINKED_CONCATENATE:
        case LINKED_CONVERT_LINKED_TYPE:
        case LINKED_INSERT_ONE_AT_START:
        case LINKED_INSERT_ONE_AT_END:
            is_valid = linked != NULL;
            if (!is_valid && !str_len(failed_validation_message)) sprintf(failed_validation_message, "Linked list must be initialized");
            return is_valid;

        case LINKED_INITIALIZE_AND_INSERT_MULTIPLE:
        case LINKED_INITIALIZE_AND_INSERT_ONE:
            is_valid = linked == NULL;
            if (!is_valid && !str_len(failed_validation_message)) sprintf(failed_validation_message, "Linked list must be deleted first");
            return is_valid;

        // good to return 0 here that means i forgot to add the rule then in that case validation should fail
        // better than forgetting to add the rule and the program runs normal and crashes ¯\(°_o)/¯
        default:
            if (!str_len(failed_validation_message)) sprintf(failed_validation_message, "List validation rule 404");
            return 0;
    }
}

uint8_t is_min_linked_required_and_not_null(ProgramState *state, Operation operation) {
    uint16_t min_number = 1, counter = 0;
    switch (operation) {
        case LINKED_CONCATENATE:
            min_number = 2;
            break;

        default:
            break;
    }
    for (int8_t i = 0; i < NUMBER_OF_LINKED_LISTS; i++) {
        if (is_linked_required_and_not_null(state->linked[i], operation)) counter++;
    }
    return counter >= min_number;
}

uint8_t is_all_list_not_null_and_same_type(ProgramState *state) {
    char **inputs = state->inputs;
    LinkedType type = UNSET;
    while (*inputs != NULL) {
        int32_t i = eval_int(*inputs) - (int32_t)1;
        if (!state->linked[i]) {
            if (!str_len(failed_validation_message)) sprintf(failed_validation_message, "Uninitialized lists are not allowed");
            return 0;
        }

        if (!type) {
            type = linked_get_type(state->linked[i]);
        }

        if (type) {
            if (linked_get_type(state->linked[i]) != type) {
                if (!str_len(failed_validation_message)) sprintf(failed_validation_message, "Lists with different types are not allowed");
                return 0;
            }
        }
        inputs++;
    }
    return 1u;
}

uint8_t validate(ProgramState *state) {
    uint8_t stage_validation = FALSE, is_operation_validation_required = TRUE, operation_validation = FALSE;

    if (basic_validator(state->inputs, ONE_INPUT_AND_ONE_CHARACTER_PRESENT) &&
        in_str("EeBbMm", *state->inputs[0])) return 1;

    switch (state->current_stage->stage) {
        case LINKED_SELECT_STAGE:
            stage_validation = basic_validator(state->inputs, ONE_NUMERIC_VALUE) &&
                               (Operation)eval_int(state->inputs[0]) >= 1 &&
                               (Operation)eval_int(state->inputs[0]) <= NUMBER_OF_LINKED_LISTS &&
                               is_linked_required_and_not_null(state->linked[eval_int(state->inputs[0]) - (int32_t)1], state->operation);
            is_operation_validation_required = FALSE;
            if (!stage_validation && !str_len(failed_validation_message)) sprintf(failed_validation_message, "Input value must be between 1 and %d", NUMBER_OF_LINKED_LISTS);
            break;

        case LINKED_TYPE_SELECT_STAGE:
            stage_validation = basic_validator(state->inputs, ONE_NUMERIC_VALUE) &&
                               (Operation)eval_int(state->inputs[0]) > UNSET &&
                               (Operation)eval_int(state->inputs[0]) <= CIRCULAR;
            if (!stage_validation && !str_len(failed_validation_message)) sprintf(failed_validation_message, "Input value must be between 1 and 2");
            is_operation_validation_required = FALSE;
            break;

        case OPERATION_SELECT_STAGE:
        case OPERATION_INPUT_STAGE:
            stage_validation = TRUE;
            break;

        case OPERATION_OUTPUT_STAGE:
            stage_validation = basic_validator(state->inputs, ONE_INPUT_AND_ONE_CHARACTER_PRESENT) &&
                               in_str("EeBbMm", *state->inputs[0]);
            if (!stage_validation && !str_len(failed_validation_message)) sprintf(failed_validation_message, "You must choose a destination");
            break;

        case GO_BACK_TO_MAIN_MENU_STAGE:
        case GO_BACK_TO_PREVIOUS_STAGE:
            stage_validation = TRUE;
            is_operation_validation_required = FALSE;
            break;

        default:
            // good to return 0 here that means i forgot to add the rule then in that case validation should fail
            // better than forgetting to add the rule and the program runs normal and crashes ¯\(°_o)/¯
            stage_validation = FALSE;
            if (!stage_validation && !str_len(failed_validation_message)) sprintf(failed_validation_message, "Stage validation rule 404");
            break;
    }

    if (!is_operation_validation_required) return stage_validation;

    switch (state->operation) {
        case NO_OPERATION_SELECTED:
            operation_validation = basic_validator(state->inputs, ONE_NUMERIC_VALUE) &&
                                   (Operation)eval_int(state->inputs[0]) > 0 &&
                                   (Operation)eval_int(state->inputs[0]) <= EXIT &&
                                   is_min_linked_required_and_not_null(state, (Operation)eval_int(state->inputs[0]));
            if (!operation_validation && !str_len(failed_validation_message)) sprintf(failed_validation_message, "Input value must be between 1 and 16");
            break;

        case LINKED_INITIALIZE_AND_INSERT_ONE:
        case LINKED_INSERT_ONE_AT_START:
        case LINKED_INSERT_ONE_AT_END:
            operation_validation = basic_validator(state->inputs, ONE_NUMERIC_VALUE);
            if (!operation_validation && !str_len(failed_validation_message)) sprintf(failed_validation_message, "Input must be one numeric value");
            break;

        case LINKED_INITIALIZE_AND_INSERT_MULTIPLE:
        case LINKED_INSERT_ONE_OR_MORE_AT_START:
        case LINKED_INSERT_ONE_OR_MORE_AT_END:
            operation_validation = basic_validator(state->inputs, ONE_OR_MORE_NUMERIC_VALUES);
            if (!operation_validation && !str_len(failed_validation_message)) sprintf(failed_validation_message, "Input must be one or more than one numeric values");
            break;

        case LINKED_INSERT_AFTER_VALUE:
        case LINKED_INSERT_BEFORE_VALUE:
            operation_validation = basic_validator(state->inputs, TWO_NUMERIC_VALUES) && in_linked(state->linked[state->selected_linked_list], eval_int(state->inputs[0]));
            if (!operation_validation && !str_len(failed_validation_message)) sprintf(failed_validation_message, "Input must be two numeric values");
            break;

        case LINKED_INSERT_AT_POSITION:
            operation_validation = basic_validator(state->inputs, TWO_NUMERIC_VALUES);
            if (!operation_validation && !str_len(failed_validation_message)) sprintf(failed_validation_message, "Input must be two numeric values");
            operation_validation = operation_validation && eval_int(state->inputs[0]) > 0 &&
                                   eval_int(state->inputs[0]) <= len_linked(state->linked[state->selected_linked_list]);
            if (!operation_validation && !str_len(failed_validation_message)) sprintf(failed_validation_message, "Position doesn't exist");
            break;

        case LINKED_DELETE_VALUE:
            operation_validation = basic_validator(state->inputs, ONE_NUMERIC_VALUE) && in_linked(state->linked[state->selected_linked_list], eval_int(state->inputs[0]));
            if (!operation_validation && !str_len(failed_validation_message)) sprintf(failed_validation_message, "Input must be one numeric value");
            break;

        case LINKED_CONCATENATE:
            operation_validation = basic_validator(state->inputs, TWO_OR_MORE_NUMERIC_VALUES);
            if (!operation_validation && !str_len(failed_validation_message)) sprintf(failed_validation_message, "Input must be two or more than two numeric values");
            operation_validation = operation_validation && get_maximum_value(state->inputs) < (int32_t)NUMBER_OF_LINKED_LISTS + (int32_t)1 && get_minimum_value >= (int32_t)1;
            if (!operation_validation && !str_len(failed_validation_message)) sprintf(failed_validation_message, "Some lists you entered doesn't exist");
            operation_validation = operation_validation && is_all_list_not_null_and_same_type(state);
            break;

        case INSPECT_LINKS:
        case DELETE_ENTIRE_LIST:
        case LINKED_REVERSE:
        case LINKED_CONVERT_LINKED_TYPE:
            operation_validation = 1u;
            break;

        default:
            // good to return 0 here that means i forgot to add the rule then in that case validation should fail
            // better than forgetting to add the rule and the program runs normal and crashes ¯\(°_o)/¯
            operation_validation = 0;
            if (!operation_validation && !str_len(failed_validation_message)) sprintf(failed_validation_message, "Operation Validation rule 404");
            break;
    }
    return stage_validation && operation_validation;
}

void print_positions(Node_t *start, uint16_t offset) {
    for (uint16_t i = 0; i < offset; i++) {
        printf(" ");
    }
}

void linked_inspect_links(Node_t *start) {
    Node_t *ptr = start;
    uint16_t counter = 1;

    if (linked_is_doubly(start)) {
        while (ptr != NULL) {
            printf(" Node [%02d] : \n", counter++);
            printf("  value -> %d\n", ptr->value);
            printf("  next  -> ");
            ptr->next != NULL ? printf("%d\n", ptr->next->value) : printf("null\n");
            printf("  prev  -> ");
            ptr->prev != NULL ? printf("%d\n", ptr->prev->value) : printf("null\n");
            printf("\n");
            ptr = ptr->next;
        }
    }
    if (linked_is_circular(start)) {
        do {
            printf(" Node [%02d] : \n", counter++);
            printf("  value -> %d\n", ptr->value);
            printf("  next  -> %d\n", ptr->next->value);
            printf("  prev  -> %d\n", ptr->prev->value);
            printf("\n");
            ptr = ptr->next;
        } while (ptr != start);
    }
}

UserStage_t *stage_push(UserStage_t *current, Stage stage) {
    UserStage_t *temp = (UserStage_t *)malloc(sizeof(UserStage_t));
    temp->stage = stage;
    temp->prev = current;
    return temp;
}

UserStage_t *stage_pop(UserStage_t *current) {
    UserStage_t *temp = current;
    current = current->prev;
    free(temp);
    return current;
}

UserStage_t *stage_reset(UserStage_t *current) {
    UserStage_t *ptr = current;
    while (ptr != NULL) {
        UserStage_t *temp = ptr;
        ptr = ptr->prev;
        free(temp);
    }
    return stage_push(NULL, OPERATION_SELECT_STAGE);
}

void set_failed_validation_message(char *str) {
    str_cpy(str, failed_validation_message, FAILED_VALIDATION_MESSAGE_BUFFER_SIZE);
}

void inner_frame(ProgramState *state) {
    switch (state->current_stage->stage) {
        case OPERATION_SELECT_STAGE:
            printf("(01) [Initialize] a doubly or a circular linked list with a [single] [value]\n");
            printf("(02) [Initialize] a doubly or a circular linked list using a [set] of [values]\n");
            printf("(03) [Insert] [one] [value] at the [start] of one of the two linked lists above\n");
            printf("(04) [Insert] [multiple] [values] at the [start] of one of the two linked lists above\n");
            printf("(05) [Insert] [one] [value] at the [end] of one of the two linked lists above\n");
            printf("(06) [Insert] [multiple] [values] at the [end] of one of the two linked lists above\n");
            printf("(07) [Insert] a node [after] another [value] present in one of the two linked lists above\n");
            printf("(08) [Insert] a node [before] another [value] present in one of the two linked lists above\n");
            printf("(09) [Insert] a node at a certain [postion] in one of the two linked lists above\n");
            printf("(10) [Delete] a [value] from one of the two linked lists above\n");
            printf("(11) [Reverse] one of the two linked lists above\n");
            printf("(12) [Concatenate] the two linked lists above\n");
            printf("(13) [Convert] the type of one of the two linked lists above\n");
            printf("(14) [Delete] one of the two [linked] lists above\n");
            printf("(15) [Inspect] one of the two [linked] list [links] above\n");
            printf("(16) [Exit]\n\n");
            break;

        case LINKED_SELECT_STAGE:
            switch (state->operation) {
                case LINKED_INITIALIZE_AND_INSERT_MULTIPLE:
                case LINKED_INITIALIZE_AND_INSERT_ONE:
                    printf("- Which linked list do you want to initialize\n\n");
                    break;

                case LINKED_INSERT_AFTER_VALUE:
                case LINKED_INSERT_BEFORE_VALUE:
                case LINKED_INSERT_AT_POSITION:
                case LINKED_INSERT_ONE_AT_START:
                case LINKED_INSERT_ONE_AT_END:
                    printf("- Which linked list do you want to perform insertion to : \n\n");
                    break;

                case LINKED_REVERSE:
                    printf("- Which linked list do you want to reverse : \n\n");
                    break;

                case LINKED_DELETE_VALUE:
                    printf("- Which linked list do you want to delete from : \n\n");
                    break;

                case DELETE_ENTIRE_LIST:
                    printf("- Which linked list do you want to be entirely deleted: \n\n");
                    break;

                case INSPECT_LINKS:
                    printf("- Which linked list do you want to inspect its links : \n\n");
                    break;

                case LINKED_CONVERT_LINKED_TYPE:
                    printf("- Which linked list do you want to convert its type : \n");
                    printf("- If the list type is doubly it will be converted to circular : \n");
                    printf("- And if the list type is circular it will be converted to doubly : \n\n");
                    break;

                default:
                    printf("- 404 \n\n");
                    break;
            }
            for (uint8_t i = 0; i < NUMBER_OF_LINKED_LISTS; i++) {
                printf("  (%d) Linked List %d \n", i + 1, i + 1);
            }
            printf("\n");
            break;

        case LINKED_TYPE_SELECT_STAGE:
            printf("- Which type of linked list do you want it to be : \n\n");
            printf("  (1) Doubly Type \n");
            printf("  (2) Circular Type \n");
            printf("\n");
            break;

        case OPERATION_INPUT_STAGE:
            switch (state->operation) {
                case LINKED_INITIALIZE_AND_INSERT_ONE:
                case LINKED_INSERT_ONE_AT_START:
                case LINKED_INSERT_ONE_AT_END:
                    printf("- Enter a value to be inserted\n");
                    break;

                case LINKED_INITIALIZE_AND_INSERT_MULTIPLE:
                case LINKED_INSERT_ONE_OR_MORE_AT_START:
                case LINKED_INSERT_ONE_OR_MORE_AT_END:
                    printf("- Enter a list of values on the same line each separated by a space\n");
                    break;

                case LINKED_INSERT_AFTER_VALUE:
                    printf("- Enter a value you want to insert the new node after\n");
                    printf("- Then enter the new value, All on the same line separated by a space\n");
                    break;

                case LINKED_INSERT_BEFORE_VALUE:
                    printf("- Enter a value you want to insert the new node before\n");
                    printf("- Then enter the new value, All on the same line separated by a space\n");
                    break;

                case LINKED_INSERT_AT_POSITION:
                    printf("- Enter a position you want to insert the new node at\n");
                    printf("- Then enter the new value, All on the same line separated by a space\n");
                    break;

                case LINKED_DELETE_VALUE:
                    printf("- Enter a value you want to delete\n");
                    break;

                case LINKED_CONCATENATE:
                    printf("- Enter list of linked lists numbers you want to concatenate them together\n");
                    printf("- All values must be entered on the same line each separated by a space\n");
                    printf("- [CAUTION] the first linked list entered will be used to store the result\n");
                    break;

                default:
                    printf("INPUT 404\n");
                    break;
            }
            printf("\n");
            printf("- Enter \"b\" to go back to previous menu\n");
            printf("- Enter \"m\" to to main menu\n");
            printf("- Enter \"e\" to exit the program\n\n");
            break;

        case OPERATION_OUTPUT_STAGE:
            switch (state->operation) {
                case INSPECT_LINKS:
                    printf("Linked List [%d] : \n\n", state->selected_linked_list + 1);
                    linked_inspect_links(state->linked[state->selected_linked_list]);
                    break;

                default:
                    printf("OUTPUT 404\n");
                    break;
            }

            printf("\n");
            printf("- Enter \"b\" to go back to previous menu\n");
            printf("- Enter \"m\" to to main menu\n");
            printf("- Enter \"e\" to exit the program\n\n");
            printf("\n");
            free(state->output);
            state->output = NULL;
            break;

        default:
            printf("STAGE 404\n");
            break;
    }
}

void linked_print_positions(Node_t *start, uint16_t starter_offset, uint16_t repeating_offset, uint8_t is_extra_printed) {
    uint8_t line = 1;
    if (!start) return;

    if (is_extra_printed) starter_offset += start->prev ? str_len("[<prev]=[") + digits_plus_sign_count(start->prev->value)
                                                        : str_len("[null]=[");

    while (line <= 2) {
        Node_t *ptr = start;

        for (uint16_t i = 0; i < starter_offset; i++) {
            printf(" ");
        }

        uint16_t position = 1;
        do {
            line == 1 ? printf("^") : printf("%d", position++);
            for (uint16_t j = 0; j < repeating_offset + digits_plus_sign_count(ptr->value) - 1u; j++) {
                printf(" ");
            }

            ptr = ptr->next;
        } while (ptr != NULL && ptr != start);
        line++;
        printf("\n");
    }
    printf("\n");
}

void linked_custom_print(Node_t *start) {
    if (!start) {
        printf("[NOT-INITALIZED]");
        return;
    }

    linked_is_doubly(start) ? printf("Type : Doubly  ") : printf("Type : Circular");
    printf("         Values : ");
    linked_print(start, TRUE);
}

void main_frame(ProgramState *state, uint16_t failed_validation_counter) {
    char input_str[101];

    system("cls");

    for (uint8_t i = 0; i < NUMBER_OF_LINKED_LISTS; i++) {
        i == state->selected_linked_list ? printf(">") : printf(" ");
        printf(" Linked List %02d : ", i + 1);
        linked_custom_print(state->linked[i]);
        printf("\n");
        if (state->operation == LINKED_INSERT_AT_POSITION && state->selected_linked_list == i)
            linked_print_positions(state->linked[i], (uint16_t)51 + digits_plus_sign_count(i + 1), str_len("[]="), TRUE);
    }
    printf("\n");

    inner_frame(state);

    if (failed_validation_counter) printf("Invalid Input! ");
    if (failed_validation_counter > 1) printf("[%d] ", failed_validation_counter);
    if (failed_validation_counter && str_len(failed_validation_message)) printf(":\n- %s\n", failed_validation_message);
    if (str_len(failed_validation_message)) failed_validation_message[0] = '\0';

    printf("> ");
    scanf(" %100[^\n]", input_str);
    flush_stdin();

    state->inputs = str_explode(input_str, ' ');
}

void operator(ProgramState *state) {
    switch (state->operation) {
        case LINKED_INITIALIZE_AND_INSERT_ONE:
            state->linked[state->selected_linked_list] = state->selected_linked_list_type == DOUBLY
                                                             ? doubly_insert_value_empty(state->linked[state->selected_linked_list], eval_int(state->inputs[0]))
                                                             : circular_insert_value_empty(state->linked[state->selected_linked_list], eval_int(state->inputs[0]));

            break;

        case LINKED_INITIALIZE_AND_INSERT_MULTIPLE:
            state->linked[state->selected_linked_list] = state->selected_linked_list_type == DOUBLY
                                                             ? doubly_insert_multiple_at_start(state->linked[state->selected_linked_list], state->inputs)
                                                             : circular_insert_multiple_at_start(state->linked[state->selected_linked_list], state->inputs);

            break;

        case LINKED_INSERT_ONE_AT_START:
            state->linked[state->selected_linked_list] = linked_is_doubly(state->linked[state->selected_linked_list])
                                                             ? doubly_insert_value_start(state->linked[state->selected_linked_list], eval_int(state->inputs[0]))
                                                             : circular_insert_value_start(state->linked[state->selected_linked_list], eval_int(state->inputs[0]));
            break;

        case LINKED_INSERT_ONE_OR_MORE_AT_START:
            state->linked[state->selected_linked_list] = linked_is_doubly(state->linked[state->selected_linked_list])
                                                             ? doubly_insert_multiple_at_start(state->linked[state->selected_linked_list], state->inputs)
                                                             : circular_insert_multiple_at_start(state->linked[state->selected_linked_list], state->inputs);
            break;

        case LINKED_INSERT_ONE_AT_END:
            state->linked[state->selected_linked_list] = linked_is_doubly(state->linked[state->selected_linked_list])
                                                             ? doubly_insert_value_end(state->linked[state->selected_linked_list], eval_int(state->inputs[0]))
                                                             : circular_insert_value_end(state->linked[state->selected_linked_list], eval_int(state->inputs[0]));
            break;

        case LINKED_INSERT_ONE_OR_MORE_AT_END:
            state->linked[state->selected_linked_list] = linked_is_doubly(state->linked[state->selected_linked_list])
                                                             ? doubly_insert_multiple_at_end(state->linked[state->selected_linked_list], state->inputs)
                                                             : circular_insert_multiple_at_end(state->linked[state->selected_linked_list], state->inputs);
            break;

        case LINKED_INSERT_AFTER_VALUE:
            state->linked[state->selected_linked_list] = linked_insert_after_value(state->linked[state->selected_linked_list], eval_int(state->inputs[0]), eval_int(state->inputs[1]));
            break;

        case LINKED_INSERT_BEFORE_VALUE:
            state->linked[state->selected_linked_list] = linked_insert_before_value(state->linked[state->selected_linked_list], eval_int(state->inputs[0]), eval_int(state->inputs[1]));
            break;

        case LINKED_INSERT_AT_POSITION:
            state->linked[state->selected_linked_list] = linked_insert_at_position(state->linked[state->selected_linked_list], eval_int(state->inputs[0]), eval_int(state->inputs[1]));
            break;

        case LINKED_DELETE_VALUE:
            state->linked[state->selected_linked_list] = linked_delete_value(state->linked[state->selected_linked_list], eval_int(state->inputs[0]));
            break;

        case LINKED_REVERSE:
            state->linked[state->selected_linked_list] = linked_reverse(state->linked[state->selected_linked_list]);
            break;

        case LINKED_CONCATENATE:
            linked_concatenate_all(state);
            break;

        case LINKED_CONVERT_LINKED_TYPE:
            if (linked_get_type(state->linked[state->selected_linked_list]) == DOUBLY)
                state->linked[state->selected_linked_list] = convert_doubly_to_circular(state->linked[state->selected_linked_list]);
            else if (linked_get_type(state->linked[state->selected_linked_list]) == CIRCULAR)
                state->linked[state->selected_linked_list] = convert_circular_to_doubly(state->linked[state->selected_linked_list]);
            break;

        case DELETE_ENTIRE_LIST:
            free_linked(state->linked[state->selected_linked_list]);
            state->linked[state->selected_linked_list] = NULL;
            break;

        case INSPECT_LINKS:
            state->output = (Node_t *)malloc(sizeof(Node_t));
            break;

        default:
            break;
    }
}

void user_input_resolver(ProgramState *state) {
    switch (state->current_stage->stage) {
        case OPERATION_SELECT_STAGE:
            state->operation = eval_int(state->inputs[0]);
            state->current_stage = state->operation == LINKED_CONCATENATE ? stage_push(state->current_stage, OPERATION_INPUT_STAGE)
                                                                          : stage_push(state->current_stage, LINKED_SELECT_STAGE);
            break;

        case LINKED_SELECT_STAGE:
            state->selected_linked_list = eval_int(state->inputs[0]) - (int32_t)1;
            state->current_stage = state->operation == LINKED_INITIALIZE_AND_INSERT_MULTIPLE || state->operation == LINKED_INITIALIZE_AND_INSERT_ONE
                                       ? stage_push(state->current_stage, LINKED_TYPE_SELECT_STAGE)
                                       : stage_push(state->current_stage, OPERATION_INPUT_STAGE);
            break;

        case LINKED_TYPE_SELECT_STAGE:
            state->selected_linked_list_type = eval_int(state->inputs[0]);
            state->current_stage = stage_push(state->current_stage, OPERATION_INPUT_STAGE);
            break;

        case OPERATION_INPUT_STAGE:
            operator(state);
            state->current_stage = state->output != NULL ? stage_push(state->current_stage, OPERATION_OUTPUT_STAGE)
                                                         : stage_push(state->current_stage, GO_BACK_TO_MAIN_MENU_STAGE);
            break;

        case OPERATION_OUTPUT_STAGE:
            state->current_stage = stage_push(state->current_stage, GO_BACK_TO_MAIN_MENU_STAGE);
            break;

        case GO_BACK_TO_PREVIOUS_STAGE:
            if (state->inputs) goto FREE_INPUTS_AND_EXIT;
            state->current_stage = stage_pop(state->current_stage);
            do {
                if (state->current_stage->stage == OPERATION_SELECT_STAGE ||
                    state->current_stage->prev->stage == OPERATION_SELECT_STAGE) {
                    state->current_stage = stage_push(state->current_stage, GO_BACK_TO_MAIN_MENU_STAGE);
                    break;
                }
                state->current_stage = stage_pop(state->current_stage);
            } while (state->current_stage->stage != OPERATION_SELECT_STAGE && validate(state));
            break;

        case GO_BACK_TO_MAIN_MENU_STAGE:
            state->current_stage = stage_reset(state->current_stage);
            state->operation = NO_OPERATION_SELECTED;
            state->selected_linked_list_type = UNSET;
            state->selected_linked_list = -1;
            break;

        default:
            break;
    }
FREE_INPUTS_AND_EXIT:
    free_inputs(state->inputs);
    state->inputs = NULL;
}

void user_input_output_handler(ProgramState *state) {
    uint16_t failed_validation_counter = (uint16_t)0;

    while ((state->output != NULL || !validate(state)) &&
           state->current_stage->stage != GO_BACK_TO_MAIN_MENU_STAGE) {
        main_frame(state, failed_validation_counter++);
    }

    if (state->inputs != NULL && in_str("Ee", *(state->inputs)[0])) state->is_exit_requested = TRUE;
    if (state->inputs != NULL && in_str("Bb", *(state->inputs)[0])) state->current_stage = stage_push(state->current_stage, GO_BACK_TO_PREVIOUS_STAGE);
    if (state->inputs != NULL && in_str("Mm", *(state->inputs)[0])) state->current_stage = stage_push(state->current_stage, GO_BACK_TO_MAIN_MENU_STAGE);

    user_input_resolver(state);
}

int main(int argc, char const *argv[]) {
    ProgramState state;
    state.operation = NO_OPERATION_SELECTED;
    state.current_stage = stage_reset(NULL);
    state.current_stage->prev = NULL;
    state.current_stage->stage = OPERATION_SELECT_STAGE;
    state.inputs = NULL;
    state.is_exit_requested = FALSE;
    for (uint16_t i = 0; i < NUMBER_OF_LINKED_LISTS; i++) state.linked[i] = NULL;
    state.output = NULL;
    state.selected_linked_list_type = UNSET;
    state.selected_linked_list = -1;

    while (TRUE) {
        user_input_output_handler(&state);
        if (state.operation == EXIT || state.is_exit_requested) break;
    }

    return 0;
}