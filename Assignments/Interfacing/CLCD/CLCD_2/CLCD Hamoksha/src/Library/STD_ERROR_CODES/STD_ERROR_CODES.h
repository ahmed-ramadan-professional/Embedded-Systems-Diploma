#ifndef STD_ERROR_CODES
#define STD_ERROR_CODES

// defined enum to be able to cast it to any value
typedef enum {
    UNEXPECTED_ERROR = 0,       // to support backward compatibility as value 0 is known to be a failed operation
    NO_ERROR = 1,               // to support backward compatibility as value 1 is known to be a successful operation
    ERROR_NULL_POINTER,
    ERROR_NOT_A_NUMBER,
    ERROR_VALUE_OUT_OF_BOUND,
} u8ERROR_CODES;

#endif