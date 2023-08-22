#include "main.h"

/**
 * custom_print_handler - Prints an argument based on its type
 * @format: Formatted string in which to print the arguments.
 * @index: Index of the current character in the format string.
 * @arg_list: List of arguments to be printed.
 * @buffer: Buffer array to handle print.
 * @active_flags: Calculates active flags
 * @field_width: Field width specifier
 * @precision_spec: Precision specification
 * @size_spec: Size specifier
 * Return: 1 or 2;
 */
int custom_print_handler(const char *format, int *index, va_list arg_list,
                         char buffer[], int active_flags,
                         int field_width, int precision_spec, int size_spec) {
    int i, unknown_len = 0, printed_chars = -1;
    format_type_t format_types[] = {
        {'c', print_char}, {'s', print_string}, {'%', print_percent},
        {'i', print_int}, {'d', print_int}, {'b', print_binary},
        {'u', print_unsigned}, {'o', print_octal}, {'x', print_hexadecimal},
        {'X', print_hexa_upper}, {'p', print_pointer},
        {'S', print_non_printable}, {'r', print_reverse},
        {'R', print_rot13string}, {'\0', NULL}
    };
    
    for (i = 0; format_types[i].format_char != '\0'; i++) {
        if (format[*index] == format_types[i].format_char) {
            return (format_types[i].format_fn(arg_list, buffer, active_flags,
                                              field_width, precision_spec, size_spec));
        }
    }
    
    if (format_types[i].format_char == '\0') {
        if (format[*index] == '\0') {
            return (-1);
        }
        unknown_len += write(1, "%%", 1);
        
        if (format[*index - 1] == ' ') {
            unknown_len += write(1, " ", 1);
        } else if (field_width) {
            --(*index);
            while (format[*index] != ' ' && format[*index] != '%') {
                --(*index);
            }
            if (format[*index] == ' ') {
                --(*index);
            }
            return (1);
        }
        
        unknown_len += write(1, &format[*index], 1);
        return (unknown_len);
    }
    
    return (printed_chars);
}

