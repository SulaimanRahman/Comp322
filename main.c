#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>
#include <ctype.h>

char *addZeros(char *binary);
int convertBinaryToDecimal (char *binary);
char *ParityisOddOrEven(char *binary);
int checkIfItsInteger (char* value);
void ReadTheFileAndPrintTheResults (char* filename);

int main(int argc, char* argv[])
{
    printf("%-10s%-10s%-10s%-10s%-100s\n", "Original", "ASCII", "Decimal", "Parity", "T.Error");
	printf("%-10s%-10s%-10s%-10s%-10s\n", "--------", "--------", "--------", "--------", "--------");

    int i;

    for (i = 1; i < argc; i++) {

        int isdigit = checkIfItsInteger(argv[i]);

        if (isdigit == 0) {
            FILE *fp = fopen(argv[i], "r");
            if (fp == NULL) {
                break;
            } else {
                ReadTheFileAndPrintTheResults(argv[i]);
                break;
            }

        } else if (isdigit == 1) { //if isdigit returns 1
            char *BNumber;


            if (strlen(argv[i]) < 8) {

                BNumber = addZeros(argv[i]);
            } else {
                BNumber = argv[i];
            }
            int decimal = convertBinaryToDecimal(BNumber);
            char *parity = ParityisOddOrEven(BNumber);
            while (decimal > 127) {
                decimal = decimal -128;
            }
            printf("%-8s%10c%10d%10s\n", BNumber, decimal, decimal, parity);
        } else {
            continue;
        }
    }


    return 0;
}

char *addZeros (char *binary) {
    int i;
    char FullBinary[8];
    for (int i = 0; (unsigned) i < strlen(binary); i++) {
        FullBinary[i] = binary[i];
    }
    for (i = strlen(binary); i < 8; i++) {
            FullBinary[i] = '0';
    }

    char *FB = FullBinary;
    return FB;
}
int convertBinaryToDecimal (char *binary) {
    int number = atoi(binary);
    int decimal = 0, i = 0, remainder;

    while (number != 0) {
        remainder = number % 10;
        number /= 10;
        decimal += remainder * pow(2, i);
        ++i;
    }
    return decimal;
}

char *ParityisOddOrEven(char *binary) {
    int decimal = 0;
    int i, j;
    for(i = 0, j = strlen(binary) - 1; (unsigned)i < strlen(binary); i++, j--) {
        if(binary[i] == '1') {
            decimal = decimal + 1;
        }
    }
    if (decimal % 2 == 0) {
        return "Even";
    }
    else {
        return "Odd";
    }
}

int checkIfItsInteger (char* value) {
    int i = 0;
    int isdigitvalue = 0;
    for (i = 0; (unsigned) i < strlen(value); i++) {
        if (strchr(value, '"') || strchr(value, '-')
            || strchr(value, '[') || strchr(value, ']')
            || strchr(value, '{') || strchr(value, ']')
            || strchr(value, ';') || strchr(value, ':')
            || strchr(value, '<') || strchr(value, ',')
            || strchr(value, '>') || strchr(value, '/')
            || strchr(value, '?') || strchr(value, '=')
            || strchr(value, '+') || strchr(value, '-')
            || strchr(value, '_') || strchr(value, ')')
            || strchr(value, '*') || strchr(value, '(')
            || strchr(value, '&') || strchr(value, '^')
            || strchr(value, '$') || strchr(value, '%')
            || strchr(value, '#') || strchr(value, '@')
            || strchr(value, '!') || strchr(value, '`')
            || strchr(value, '~')){

            return 2;
        } else if (isdigit(value[i]) != 0) {
            isdigitvalue = 1;//value is an integer
        } else {
            isdigitvalue = 0;//value is not an integer
            break;
        }
    }
    return isdigitvalue;
}

void ReadTheFileAndPrintTheResults (char* filename) {
    FILE *fp = fopen(filename, "r");
    char buf[10];

    while (fscanf(fp, "%s", buf) != EOF) {
        char *BNumber = buf;
        if (strlen(buf) < 8) {
            BNumber = addZeros(buf);
        }
        int decimal = convertBinaryToDecimal(buf);
        char *parity = ParityisOddOrEven(buf);
        while (decimal > 127) {
            decimal = decimal -128;
        }
        printf("%-8s%10c%10d%10s\n", BNumber, decimal, decimal, parity);
    }

	fclose(fp);
}

