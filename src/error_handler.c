#include <error_handler.h>

void display_error(error_t error) {
    switch(error) {
        case none:
            break;
        case identifier_too_long:
            printf("The identifier is too long!\n");
            break;
        case number_too_long:
            printf("The number is too long!\n");
            break;
        case malformed_assign_operator:
            printf("Found a malformed assign operator!\n");
            break;
        case unexpected_end_of_file:
            printf("Found an unexpected end of file!\n");
            break;
        case invalid_char:
            printf("The character is invalid!\n");
            break;
    }
}
