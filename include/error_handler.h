#pragma once

typedef enum {
    none = 0, identifier_too_long,
    number_too_long,
    malformed_assign_operator,
    unexpected_end_of_file,
    invalid_char
} error_t;
