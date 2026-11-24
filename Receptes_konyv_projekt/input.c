#include "input.h"

#include <ctype.h>
#include <errno.h>
#include <limits.h>
#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int input_read_text(const char *prompt, char *buffer, size_t size)
{
    if (size < 2)
        return 0;

    while (1)
    {
        printf("%s", prompt);
        if (fgets(buffer, (int)size, stdin) == NULL)
        {
            printf("A bemenet megszakadt.\n");
            return 0;
        }

        char *newline = strchr(buffer, '\n');
        if (newline == NULL)
        {
            int character = getchar();
            if (character == '\r')
                character = getchar();
            if (character != EOF && character != '\n')
            {
                while (character != '\n' && character != EOF)
                    character = getchar();
                printf("A megadott adat túl hosszú. Próbálja újra.\n");
                continue;
            }
        }
        if (newline != NULL)
            *newline = '\0';

        char *start = buffer;
        while (isspace((unsigned char)*start))
            start++;
        char *end = start + strlen(start);
        while (end > start && isspace((unsigned char)end[-1]))
            end--;
        *end = '\0';
        if (start != buffer)
            memmove(buffer, start, (size_t)(end - start) + 1);

        if (buffer[0] == '\0')
        {
            printf("Az adat nem lehet üres. Próbálja újra.\n");
            continue;
        }
        return 1;
    }
}

int input_parse_int(const char *text, int *value)
{
    char *end;
    errno = 0;
    long parsed = strtol(text, &end, 10);
    if (text[0] == '\0' || errno == ERANGE || *end != '\0' ||
        parsed < (long)INT_MIN || parsed > (long)INT_MAX)
        return 0;
    *value = (int)parsed;
    return 1;
}

int input_read_int(const char *prompt, int minimum, int maximum, int *value)
{
    char buffer[128];
    while (input_read_text(prompt, buffer, sizeof(buffer)))
    {
        int parsed;
        if (input_parse_int(buffer, &parsed) && parsed >= minimum && parsed <= maximum)
        {
            *value = parsed;
            return 1;
        }
        printf("Érvénytelen érték. Adjon meg egy egész számot %d és %d között.\n", minimum, maximum);
    }
    return 0;
}

int input_read_positive_double(const char *prompt, double *value)
{
    char buffer[128];
    while (input_read_text(prompt, buffer, sizeof(buffer)))
    {
        const char *cursor = buffer;
        if (*cursor == '+' || *cursor == '-')
            cursor++;
        int digits = 0;
        while (isdigit((unsigned char)*cursor))
        {
            cursor++;
            digits++;
        }
        if (*cursor == '.')
        {
            cursor++;
            while (isdigit((unsigned char)*cursor))
            {
                cursor++;
                digits++;
            }
        }
        if (digits == 0)
        {
            printf("Érvénytelen érték. Pozitív, véges számot adjon meg.\n");
            continue;
        }
        if (*cursor == 'e' || *cursor == 'E')
        {
            cursor++;
            if (*cursor == '+' || *cursor == '-')
                cursor++;
            int exponent_digits = 0;
            while (isdigit((unsigned char)*cursor))
            {
                cursor++;
                exponent_digits++;
            }
            if (exponent_digits == 0)
            {
                printf("Érvénytelen érték. Pozitív, véges számot adjon meg.\n");
                continue;
            }
        }
        if (*cursor != '\0')
        {
            printf("Érvénytelen érték. Pozitív, véges számot adjon meg.\n");
            continue;
        }

        char *end;
        errno = 0;
        double parsed = strtod(buffer, &end);
        if (*end == '\0' && errno != ERANGE && isfinite(parsed) && parsed > 0.0)
        {
            *value = parsed;
            return 1;
        }
        printf("Érvénytelen érték. Pozitív, véges számot adjon meg.\n");
    }
    return 0;
}

int input_read_yes_no(const char *prompt, char *value)
{
    char buffer[128];
    while (input_read_text(prompt, buffer, sizeof(buffer)))
    {
        if (buffer[1] == '\0' &&
            (buffer[0] == 'y' || buffer[0] == 'Y' || buffer[0] == 'n' || buffer[0] == 'N'))
        {
            *value = (char)tolower((unsigned char)buffer[0]);
            return 1;
        }
        printf("Érvénytelen válasz. Csak y vagy n adható meg.\n");
    }
    return 0;
}
