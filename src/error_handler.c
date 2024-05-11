#include <error_handler.h>
#include <string.h>

void get_error_description(error_t error, char* description) {
    switch(error) {
        case none:
            break;
        case identifier_too_long:
            strcpy(description, "The identifier is too long!");
            break;
        case number_too_long:
            strcpy(description, "The number is too long!");
            break;
        case malformed_assign_operator:
            strcpy(description, "Found a malformed assign operator!");
            break;
        case unexpected_end_of_file:
            strcpy(description, "Found an unexpected end of file!");
            break;
        case invalid_char:
            strcpy(description, "The character is invalid!");
            break;
    }
}

void get_error_verbose(error_t error, char* message) {
    switch(error) {
        case none:
            break;
        case identifier_too_long:
            strcpy(message, "The identifier must be made up of a maximum of 100 characters!");
            break;
        case number_too_long:
            strcpy(message, "The number be a maximum of 100 digits!");
            break;
        case malformed_assign_operator:
            strcpy(message, "An assign operator should be like ( := ) !");
            break;
        case unexpected_end_of_file:
            strcpy(message, "You probably forgot to close a comment started at the line indicated above!\nRemember, comments start with ( { ) and end with ( } ),  like: { this is a comment }");
            break;
        case invalid_char:
            strcpy(message, "The accepted characters are:\n\t- letters (capitalize or not) from a to z ([a-z] and [A-Z])\n\t- digits from 0 to 9\n\t- math symbols ( +, -, >, =, <, /, * )\n\t- ponctuation symbols like: the comma [ , ] and [ ), (, ., ;, :, }, { ]\n\t- invisible characters ('\\n', '\\r', '\\t', ' ')");
            break;
    }
}
