#ifndef __ERROR_HANDLER_H__
#define __ERROR_HANDLER_H__
#include <stdio.h>

typedef enum {
    none = 0, identifier_too_long,
    number_too_long,
    malformed_assign_operator,
    unexpected_end_of_file,
    invalid_char
} error_t;

void display_error(error_t error);
#endif
