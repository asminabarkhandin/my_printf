#include <stdarg.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

void reverse(char* str)
{
    int length = strlen(str);
    for (int i = 0; i < length / 2; i++)
    {
        char temp = str[i];
        str[i] = str[length - i - 1];
        str[length - i - 1] = temp;
    }
}

char convertHEX(int remainder)
{
    if (remainder == 15)
        return 'F';
    else if (remainder == 14)
        return 'E';
    else if (remainder == 13)
        return 'D';
    else if (remainder == 12)
        return 'C';
    else if (remainder == 11)
        return 'B';
    else if (remainder == 10)
        return 'A';
    else
        return (remainder + '0');
}

char converthex(int remainder)
{
    if (remainder == 15)
        return 'f';
    else if (remainder == 14)
        return 'e';
    else if (remainder == 13)
        return 'd';
    else if (remainder == 12)
        return 'c';
    else if (remainder == 11)
        return 'b';
    else if (remainder == 10)
        return 'a';
    else
        return (remainder + '0');
}

char* convertInt(int num, char base)
{
    char* number;
    int index = 0;
    bool negative = false;
    if (base == 'd')
    {
        if (num < 0)
        {
            num = num * (-1);
            negative = true;
        }
        number = malloc(sizeof(char) * 12);
        int mod = 10;
        while (num >= mod)
        {
            int remainder = num % mod;
            number[index] = remainder + '0';
            index++;
            num = (num - remainder) / mod;
        }
        number[index] = num + '0';
        if (negative)
        {
            index++;
            number[index] = '-';
        }
    }
    else if (base == 'u')
    {
        number = malloc(sizeof(char) * 12);
        int mod = 10;
        while (num >= mod)
        {
            int remainder = num % mod;
            number[index] = remainder + '0';
            index++;
            num = (num - remainder) / mod;
        }
        number[index] = num + '0';
    }
    else if (base == 'o')
    {
        number = malloc(sizeof(char) * 12);
        int mod = 8;
        while (num >= mod)
        {
            int remainder = num % mod;
            number[index] = remainder + '0';
            index++;
            num = (num - remainder) / mod;
        }
        number[index] = num + '0';
    }
    else if (base == 'x')
    {
        number = malloc(sizeof(char) * 12);
        int mod = 16;
        while (num >= mod)
        {
            int remainder = num % mod;
            number[index] = converthex(remainder);
            index++;
            num = (num - remainder) / mod;
        }
        number[index] = converthex(num);
    }
    else if (base == 'X')
    {
        number = malloc(sizeof(char) * 12);
        int mod = 16;
        while (num >= mod)
        {
            int remainder = num % mod;
            number[index] = convertHEX(remainder);
            index++;
            num = (num - remainder) / mod;
        }
        number[index] = convertHEX(num);
    }
    reverse(number);
    return (number);
}

int printArgs(char ch, va_list ap)
{
    char* arg;
    int index = 0;
    if (ch == 'd' || ch == 'o' || ch == 'u' || ch == 'x' || ch == 'X')
    {
        int num = va_arg(ap, int);
        arg = convertInt(num, ch);
        while (arg[index] != '\0')
        {
            putchar(arg[index]);
            index++;
        }
        free(arg);
    }
    else if (ch == 'c')
    {
        arg = malloc(sizeof(char));
        *arg = (char)va_arg(ap, int);
        putchar(*arg);
        index++;
        free(arg);
    }
    else if (ch == 's')
    {
        char* arg = va_arg(ap, char*);
        while (arg[index] != '\0')
        {
            putchar(arg[index]);
            index++;
        }
    }
    else if (ch == 'p')
    {
        unsigned long int mod = 16;
        unsigned long int num = va_arg(ap, unsigned long int);
        arg = malloc(sizeof(char) * 21);
        while (num >= mod)
        {
            int remainder = num % mod;
            arg[index] = converthex(remainder);
            index++;
            num = (num - remainder) / mod;
        }
        arg[index] = converthex(num);
        arg[index + 1] = 'x';
        arg[index + 2] = '0';
        reverse(arg);
        index = 0;
        while (arg[index] != '\0')
        {
            putchar(arg[index]);
            index++;
        }
    }
    return index;
}

int my_printf(char* restrict format, ...)
{
    va_list ap;
    char* string;
    int num_of_chars = 0;
    va_start(ap, format);

    for (string = format; *string != '\0'; string++)
    {
        if (*string == '%')
        {
            string++;
            if (*string != '%')
                num_of_chars = num_of_chars + printArgs(*string, ap);
        }
        else
        {
            putchar(*string);
            num_of_chars++;
        }
    }
    va_end(ap);
    return num_of_chars;
}

int main()
{
    my_printf( "hello hex %x HEX %X char %c string %s dec %d unsigned %u octal %o null %s", 665, 239, 's', "wOrLd", -123, 56, 655, "");
}