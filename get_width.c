#include "main.h"

/**
 * calculate_print_width - Calculates the width for printing
 * @format_str: Formatted string in which to print the arguments.
 * @arg_index: List of arguments to be printed.
 * @arg_list: list of arguments.
 *
 * Return: width.
 */
int calculate_print_width(const char *format_str, int *arg_index, va_list arg_list)
{
    int curr_index;
    int width = 0;

    for (curr_index = *arg_index + 1; format_str[curr_index] != '\0'; curr_index++)
    {
        if (is_digit(format_str[curr_index]))
        {
            width *= 10;
            width += format_str[curr_index] - '0';
        }
        else if (format_str[curr_index] == '*')
        {
            curr_index++;
            width = va_arg(arg_list, int);
            break;
        }
        else
            break;
    }

    *arg_index = curr_index - 1;

    return width;
}

