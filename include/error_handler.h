#ifndef __ERROR_HANDLER_H__
#define __ERROR_HANDLER_H__

typedef enum {
    none = 0, identifier_too_long,
    number_too_long,
    malformed_assign_operator,
    unexpected_end_of_file,
    invalid_char
} error_t;

void get_error_description(error_t error, char* description);
void get_error_verbose(error_t error, char* message);

#endif
