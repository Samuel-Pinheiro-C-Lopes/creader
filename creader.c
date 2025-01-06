///////////////////////////////////

#pragma region Header

    #include "creader.h"

#pragma endregion

///////////////////////////////////

#pragma region Definitions

    #define ERR (-1) // PATTERN ERROR
    #define C_ERROR (-2) // CHAR ERROR
                         
    // FORMATS
    #define CHR ('a') // char
    #define STR ('A') // string
    #define INT ('i') // int
    #define LNT ('I') // long int
    #define LLI ('l') // long long int
    #define UNT ('u') // unsigned int
    #define ULI ('U') // unsigned long int
    #define LLU ('+') // long long unsigned int
    #define FLT  ('f') // float
    #define LFT ('F') // double (long float)
    #define LLF ('$') // long double (long long float)

#pragma endregion

///////////////////////////////////

#pragma region Lexical analisys

    static const char __format_table[6][9] = 
    {
        //      32       37        100       99       102     108      117       76      115         
        //      ' '      '%'       'd'       'c'      'f'     'l'      'u'      'L'      's'
        // Labels:
        {' ', '%', 'd', 'c', 'f', 'l', 'u', 'L',  's'},
        // initial state 
        {'1', '2', ERR, ERR, ERR, ERR, ERR, ERR, ERR },
        // %
        {ERR, ERR, INT, CHR, FLT, '3', UNT, '4', STR },
        // l (long)
        {ERR, ERR, LNT, ERR, LFT, '5', ULI, ERR, ERR },
        // L (long for double)
        {ERR, ERR, ERR, ERR, LLF, ERR, ERR, ERR, ERR },
        // ll (long long)
        {ERR, ERR, LLI, ERR, ERR, ERR, LLU, ERR, ERR}, 
    };

#pragma endregion

///////////////////////////////////

#pragma region HEADER 

    static int __get_col (char c);
    static void StrReader(char *target, int size);
    static void StrToInt(char* source, long long int* target);
    static void StrToFloat(char *source, float* target);
    //static void StrToDouble(char *source, double *target);
    //static int NumAlgs(double value);
    static void StrToChar(char *source, char* target);
    static void StrToUInt(char* source, unsigned long long int* target);
    static void StrToLDouble(char *source, long double* target);
    static void StrToDouble(char *source, double* target);

#pragma endregion

///////////////////////////////////

#pragma region FUNCTIONS

    // Summary: Gets the col from the lexical analysis table
    // Parameters: <c: char in the actual indexer of the format>
    // Returns: the index of the column or error if the char doesn't belong to any
    static int __get_col (char c)
    {
        for (int i = 0; i < 9; i++)
            if (__format_table[0][i] == c)
                return i;
        return C_ERROR;
    }

    // Summary: Receives a format and a address for the target variable
    // Parameters: <Format: string passing type of variable, %d, %f...> and <Target: pointer to the
    // variable to be attributed with the input>
    // Returns: Success or error, if there's any
    int cread (char* format, ...)
    {
        va_list ap;
        va_start(ap, format);
        
        int state = 1;
        int col;

        char tempBuffer[255];

        while (format[0] != '\0')
        {   
            // gets the col for the indexed char of the format input or -1 if there's no match
            col = __get_col(format[0]); 

            // if clause as guard
            if (col == C_ERROR)
                return C_ERROR; // invalid char in format error

            // assigns the state accordingly
            state = __format_table[state][col] - '0';

            // if the state represents a valid format or error
            switch (state + '0') 
            {
                /*
                // restart state
                case (0):
                {
                    state = 0;
                    break;
                }
                */
                // INTEGERS
                // int
                case (INT):
                {
                    int* intTarget = (int*) va_arg(ap, int*);  
                    StrReader(tempBuffer, 5);
                    StrToInt(tempBuffer, (long long int*) intTarget);
                    goto next;
                }
                // long int
                case (LNT):
                {
                    long int* lIntTarget = (long int*) va_arg(ap, long int*);
                    StrReader(tempBuffer, 15);
                    StrToInt(tempBuffer, (long long int*) lIntTarget);
                    goto next;
                }
                // long long int
                case (LLI):
                {
                    long long int* llIntTarget = (long long int*) va_arg(ap, long int*);
                    StrReader(tempBuffer, 20);
                    StrToInt(tempBuffer, (long long int*) llIntTarget);
                    goto next;
                }
                // unsigned int
                case (UNT):
                {
                    unsigned int* uIntTarget = (unsigned int*) va_arg(ap, unsigned int*);
                    StrReader(tempBuffer, 9);
                    StrToUInt(tempBuffer, (unsigned long long int*) uIntTarget);
                    goto next;
                }
                // unsigned long int
                case (ULI):
                {
                    unsigned long int* ulIntTarget = 
                        (unsigned long int*) va_arg(ap, unsigned long int*);
                    StrReader(tempBuffer, 10);
                    StrToUInt(tempBuffer, (unsigned long long int*) ulIntTarget);
                    goto next;
                }
                // unsigned long long int
                case (LLU):
                {
                    unsigned long long int* ullIntTarget = 
                        (unsigned long long int*) va_arg(ap, unsigned long long int*);
                    StrReader(tempBuffer, 10);
                    StrToUInt(tempBuffer, (unsigned long long int*) ullIntTarget);
                    goto next;
                }
                // FLOAT
                // float
                case (FLT):
                {
                    printf("\nENTREI EM FLT\n");
                    float* floatTarget = (float*) va_arg(ap, float*);
                    StrReader(tempBuffer, 40);
                    StrToFloat(tempBuffer, floatTarget);
                    goto next;
                }
                // long float (double)
                case (LFT):
                {
                    double* doubleTarget = (double*) va_arg(ap, double*);
                    StrReader(tempBuffer, 50);
                    StrToDouble(tempBuffer, doubleTarget);
                    goto next;
                }
                // long long float (long double)
                case (LLF):
                {
                    long double* lDoubleTarget = (long double*) va_arg(ap, long double*);
                    StrReader(tempBuffer, 50);
                    StrToLDouble(tempBuffer, lDoubleTarget);
                    goto next;
                }
                // char
                case (CHR):
                {
                    char* charTarget = (char*) va_arg(ap, char*);
                    StrReader(tempBuffer, 2);
                    StrToChar(tempBuffer, (char*) charTarget);
                    goto next;
                }
                // string
                case (STR):
                {
                    char* strTarget = (char*) va_arg(ap, char*);
                    int size = (int) va_arg(ap, int);
                    printf("\nSIZE: %d\n",size);
                    StrReader(strTarget, size);
                    goto next;
                }
                // error because of the pattern of the format
                case (ERR):
                {
                    va_end(ap);
                    return ERR; // invalid pattern error
                }
                // commum code to the end of all cases
                next:
                {
                    state = 1;
                    break;
                }
            }

            format += sizeof(char);
        }

        va_end(ap);
        return SUCCESS;
    }

    // Summary: Receives a format and a address for the target variable
    // Parameters: <Format: string passing type of variable, %d, %f...> and <Target: pointer to the
    // variable to be attributed with the input>
    // Returns: Success or error, if there's any
    /*
    int cread(char* format, void* target)
    {
               // Reads the format to know which types of pointer to attribute
        while (format[0] != '\0')
        {
            if (format[0] != '%')
                goto next;

            switch (format[1]) 
            {
                case ('c'): 
                {
                    char* charTarget = (char*) target;
                    char tempBuffer[2];
                    StrReader(tempBuffer, 2);
                    StrToChar(tempBuffer, charTarget);
                    break;
                }
                case ('d'):
                {
                    int* intTarget = (int*) target;
                    char tempBuffer[10];
                    StrReader(tempBuffer, 5);
                    StrToInt(tempBuffer, (long long int*) intTarget);
                    break;
                }
                case ('f'):
                {
                    float* floatTarget = (float*) target;
                    char tempBuffer[20];
                    StrReader(tempBuffer, 3);
                    StrToFloat(tempBuffer, (long double*) floatTarget);
                    break;
                }
                case ('l'):
                {
                    double* doubleTarget = (double*) target;
                    char tempBuffer[2];
                    StrReader(tempBuffer, 2);
                    StrToDouble(tempBuffer, doubleTarget);
                    break;
                }
                case ('F'):
                {
                    break;
                }
                case ('s'):
                {
                    char* strTarget = (char*) target;
                    StrReader(strTarget, 10);
                    break;
                }
            }

            next:
            format += sizeof(char);
        }

       return 1;
    }
    */

#pragma endregion

///////////////////////////////////

#pragma region AUXILIARY FUNCTIONS

    // Summary: Reads from stdin buffer until size is reached or 'enter' key is pressed
    // Parameters: <target: pointer to the target to be filled with the input> and 
    // <size: maximum size that the target must receive>
    // Return: <void> 
    static void StrReader(char *target, int size)
    {
        char input = getchar();

        while (input != 10)
        {
            if (size > sizeof(char))
            {
                target[0] = input;
                target += sizeof(char);
                size -= sizeof(char);
            }
            input = getchar();
        }

        target[0] = '\0';
    }

    // Summary: Tries to parse a string source to an int target
    // Parameters: <source: string to be readed and parsed> and
    // <target: integer target to be attributed based on the string source>
    // Returns: Success or error, if there were any
    static void StrToInt(char* source, long long int* target)
    {
        // initialization
        *target = 0;
        int negativo = 0;

        // if the string starts with the negative number sign
        if (source[0] == '-')
        {
            *target = (source[1] - '0'); 
            source += 2 * sizeof(char);
            negativo = 1;
        }

        // while the end of string isn't reached
        while (source[0] != '\0')
        {
            *target *= 10;
            *target += (int) (source[0] - '0');
            source += sizeof(char);
        }
        
        // if the string represents a negative number
        if (negativo)
            *target *= -1;
    }

    static void StrToUInt(char* source, unsigned long long int* target)
    {
     
        // initialization
        *target = 0;

        // if the string starts with the negative number sign
        if (source[0] == '-')
        {
            return;
        }

        // while the end of string isn't reached
        while (source[0] != '\0')
        {
            *target *= 10;
            *target += (int) (source[0] - '0');
            source += sizeof(char);
        }
    }

    // Summary: Tries to parse a string source to a float target
    // Parameters: <source: string to be readed and parsed> and
    // <target: float target to be attributed based on the string source>
    // Returns: Success or error, if there were any
    static void StrToFloat(char *source, float* target)
    {
        // initialization
        *target = 0;
        int negativo = 0;

        // if the string starts with the negative number sign
        if (source[0] == '-')
        {
            *target = (source[1] - '0'); 
            source += 2 * sizeof(char);
            negativo = 1;
        }

        // while the end of string isn't reached
        while (source[0] != '\0' && source[0] != '.')
        {
            *target *= 10;
            *target += (float) (source[0] - '0');
            source += sizeof(char);
        }
        
        // for the fractionary part of the number
        if (source[0] == '.')
        {
            int div = 10;
            source += sizeof(char);
            while (source[0] != '\0')
            {
                *target += (float) (source[0] - '0')/div;
                div *= 10;
                source += sizeof(char);
            }
        }
        
        // if the string represents a negative number
        if (negativo)
            *target *= (float) -1;
        
    }



    // Summary: Tries to parse a string source to a float target
    // Parameters: <source: string to be readed and parsed> and
    // <target: float target to be attributed based on the string source>
    // Returns: Success or error, if there were any
    static void StrToDouble(char *source, double* target)
    {
        // initialization
        *target = 0;
        int negativo = 0;

        // if the string starts with the negative number sign
        if (source[0] == '-')
        {
            *target = (source[1] - '0'); 
            source += 2 * sizeof(char);
            negativo = 1;
        }

        // while the end of string isn't reached
        while (source[0] != '\0' && source[0] != '.')
        {
            *target *= 10;
            *target += (double) (source[0] - '0');
            source += sizeof(char);
        }
        
        // for the fractionary part of the number
        if (source[0] == '.')
        {
            int div = 10;
            source += sizeof(char);
            while (source[0] != '\0')
            {
                *target += (double) (source[0] - '0')/div;
                div *= 10;
                source += sizeof(char);
            }
        }
        
        // if the string represents a negative number
        if (negativo)
            *target *= (double) -1;
        
    }



    // Summary: Tries to parse a string source to a float target
    // Parameters: <source: string to be readed and parsed> and
    // <target: float target to be attributed based on the string source>
    // Returns: Success or error, if there were any
    static void StrToLDouble(char *source, long double* target)
    {
        // initialization
        *target = (long double) 0;
        int negativo = 0;

        // if the string starts with the negative number sign
        if (source[0] == '-')
        {
            *target = (source[1] - '0'); 
            source += 2 * sizeof(char);
            negativo = 1;
        }

        // while the end of string isn't reached
        while (source[0] != '\0' && source[0] != '.')
        {
            *target *= 10;
            *target += (long double) (source[0] - '0');
            source += sizeof(char);
        }
        
        // for the fractionary part of the number
        if (source[0] == '.')
        {
            int div = 10;
            source += sizeof(char);
            while (source[0] != '\0')
            {
                *target += (long double) (source[0] - '0')/div;
                div *= 10;
                source += sizeof(char);
            }
        }
        
        // if the string represents a negative number
        if (negativo)
            *target *= (long double) -1;
        
    }

    // Summary: Tries to parse a string source to a double target
    // Parameters: <source: string to be readed and parsed> and 
    // <target: double target to be attributed based on the string source>
    // Returns: Success or error, if there were any
    /*
    static void StrToDouble(char *source, double *target)
    {
        // initialization
        *target = 0;
        int negativo = 0;

        // if the string starts with the negative number sign
        if (source[0] == '-')
        {
            *target = (source[1] - '0'); 
            source += 2 * sizeof(char);
            negativo = 1;
        }

        // while the end of string isn't reached
        while (source[0] != '\0' && source[0] != '.')
        {
            *target *= 10;
            *target += (double) (source[0] - '0');
            source += sizeof(char);
        }
        
        // for the fractionary part of the number
        if (source[0] == '.')
        {
            int div = 10;
            source += sizeof(char);
            while (source[0] != '\0')
            {
                *target += (double) (source[0] - '0')/div;
                div *= 10;
                source += sizeof(char);
            }
        }
        
        // if the string represents a negative number
        if (negativo)
            *target *= -1;    
    }
    */

    // Summary: Tries to parse a string source to a char target
    // Parameters: <source: string to be readed and parsed> and
    // <target: char target to be attributed based on the string source>
    // Returns: Succes or error, if there were any
    static void StrToChar(char *source, char* target)
    {
        *target = source[0];
    }

    // Summary: divides a value until it reaches 0 to know how many algarisms it has
    // Parameters: <value: int value to be multiplied for 0.1 until it's value is 0>
    // Returns: <int: number of algarisms the value has>
    /*
    static int NumAlgs(double value)
    {
        double actual;
        int result = 1;
        
        //while (value > 1)
        //{
        //    actual = value%(double)10.00
        //}
        

        while ((value /= 10) != 0)
        {
            result++;
        }
        
        return result;
    }
    */

#pragma endregion

///////////////////////////////////