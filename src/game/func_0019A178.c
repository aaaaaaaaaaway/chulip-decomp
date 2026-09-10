/* SDK callback formatter. Arguments occupy eight-byte EABI save slots. */
#define NEXT_ARGUMENT(type) (arguments += 8, *(type *)(arguments - 8))
extern void (*D_001E5AF0)(int character);
extern void func_0019A010(double value);

void func_0019A178(char *format, char *arguments) {
    char buffer[32];
    char *minimum;
    char *text;
    unsigned long number;
    long signed_number;
    int modifier;
    int width;
    char character;
    float real;

    while (*format) {
        character = *format;
        minimum = 0;
        modifier = 0;
        if (character == '%') {
        next_modifier:
            ++format;
            switch (*format) {
            case '0': {
                int second = format[2];

                width = format[1] - '0';
                if ((unsigned char)width < 10) {
                    if ((unsigned int)(second - '0') < 10) {
                        {
                            int tens = width * 10;

                            tens -= '0';
                            width = tens + second;
                        }
                        format += 2;
                        if (width > 31)
                            width = 31;
                    } else {
                        ++format;
                    }
                    minimum = &buffer[31 - width];
                    while (width > 0) {
                        buffer[31 - width] = '0';
                        --width;
                    }
                }
                goto next_modifier;
            }
            case 'l':
                modifier = 'l';
                goto next_modifier;
            case 'h':
                modifier = 'h';
                goto next_modifier;
            case 'o':
                if (modifier == 'l')
                    number = NEXT_ARGUMENT(unsigned long);
                else if (modifier == 'h')
                    number = NEXT_ARGUMENT(unsigned short);
                else
                    number = NEXT_ARGUMENT(unsigned int);
                text = buffer + 31;
                *text = 0;
                if (number == 0)
                    *--text = '0';
                else {
                    while (number != 0) {
                        *--text = (unsigned char)((number & 7) + '0');
                        number >>= 3;
                    }
                }
                if (minimum && minimum < text)
                    text = minimum;
                while (*text)
                    D_001E5AF0(*text++);
                break;
            case 'x':
                if (modifier == 'l')
                    number = NEXT_ARGUMENT(unsigned long);
                else if (modifier == 'h')
                    number = NEXT_ARGUMENT(unsigned short);
                else
                    number = NEXT_ARGUMENT(unsigned int);
                text = buffer + 31;
                *text = 0;
                if (number == 0)
                    *--text = '0';
                else {
                    while (number != 0) {
                        unsigned long digit = number & 15;
                        unsigned char converted;

                        if (digit < 10) {
                            --text;
                            converted = digit + '0';
                        } else {
                            --text;
                            converted = digit + 'a' - 10;
                        }
                        *text = converted;
                        number >>= 4;
                    }
                }
                if (minimum && minimum < text)
                    text = minimum;
                while (*text)
                    D_001E5AF0(*text++);
                break;
            case 'd':
                if (modifier == 'l')
                    signed_number = NEXT_ARGUMENT(long);
                else if (modifier == 'h')
                    signed_number = NEXT_ARGUMENT(short);
                else
                    signed_number = NEXT_ARGUMENT(int);
                text = buffer + 31;
                *text = 0;
                if (signed_number == 0)
                    *--text = '0';
                else {
                    if (signed_number < 0) {
                        signed_number = -signed_number;
                        D_001E5AF0('-');
                    }
                    while (signed_number != 0) {
                        *--text = (unsigned char)(signed_number % 10 + '0');
                        signed_number /= 10;
                    }
                }
                if (minimum && minimum < text)
                    text = minimum;
                while (*text)
                    D_001E5AF0(*text++);
                break;
            case 'u':
                if (modifier == 'l')
                    number = NEXT_ARGUMENT(unsigned long);
                else if (modifier == 'h')
                    number = NEXT_ARGUMENT(unsigned short);
                else
                    number = NEXT_ARGUMENT(unsigned int);
                text = buffer + 31;
                *text = 0;
                if (number == 0)
                    *--text = '0';
                else {
                    while (number != 0) {
                        *--text = (unsigned char)(number % 10 + '0');
                        number /= 10;
                    }
                }
                if (minimum && minimum < text)
                    text = minimum;
                while (*text)
                    D_001E5AF0(*text++);
                break;
            case 'e':
            case 'f':
                real = NEXT_ARGUMENT(float);
                if (real == 0)
                    D_001E5AF0('0');
                else
                    func_0019A010((double)real);
                break;
            case 's': {
                char *argument;

                argument = NEXT_ARGUMENT(char *);
                if (*argument == 0) {
                    D_001E5AF0('(');
                    D_001E5AF0('n');
                    D_001E5AF0('u');
                    D_001E5AF0('l');
                    D_001E5AF0('l');
                    D_001E5AF0(')');
                } else {
                    text = argument;
                    for (; *text; ++text)
                        D_001E5AF0(*text);
                }
                break;
            }
            case 'c':
                signed_number = NEXT_ARGUMENT(char);
                D_001E5AF0((int)signed_number);
                break;
            }
        } else {
            D_001E5AF0(character);
        }
        ++format;
    }
}
