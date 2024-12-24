///////////////////////////////////

#pragma region Header

    #include "CReader.h"

#pragma endregion

///////////////////////////////////

#pragma region Definitions



#pragma endregion

///////////////////////////////////

#pragma region FUNCTIONS

    // Summary: Receives a format and a address for the target variable
    // Parameters: <Format: string passing type of variable, %d, %f...> and <Target: pointer to the
    // variable to be attributed with the input>
    // Returns: Success or error, if there's any
    int CRead(char* format, void* target)
    {
        // using the max algarisms of each type to use as sentinel for the max size of 
        // char* readed from the user
        static unsigned int algs_int = 0; 
        static unsigned int algs_float = 0;
        static unsigned int algs_double = 0;
        if (algs_int == 0)
            algs_int = NumAlgs(INT_MAX);
        if (algs_float == 0)
            algs_float = NumAlgs(FLT_MAX);
        if (algs_double == 0)
            algs_double = NumAlgs(DBL_MAX);

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
                    char tempBuffer[20];
                    StrReader(tempBuffer, 20);
                    StrToInt(tempBuffer, intTarget);
                    break;
                }
                case ('f'):
                {
                    float* floatTarget = (float*) target;
                    char tempBuffer[30];
                    StrReader(tempBuffer, 30);
                    StrToFloat(tempBuffer, floatTarget);
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

#pragma endregion

///////////////////////////////////

#pragma region AUXILIARY FUNCTIONS

    // Summary: Reads from stdin buffer until size is reached or 'enter' key is pressed
    // Parameters: <target: pointer to the target to be filled with the input> and 
    // <size: maximum size that the target must receive>
    // Return: <void> 
    void StrReader(char *target, int size)
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
    void StrToInt(char* source, int* target)
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

    // Summary: Tries to parse a string source to a float target
    // Parameters: <source: string to be readed and parsed> and
    // <target: float target to be attributed based on the string source>
    // Returns: Success or error, if there were any
    void StrToFloat(char *source, float* target)
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
            *target *= -1;
    }

    // Summary: Tries to parse a string source to a double target
    // Parameters: <source: string to be readed and parsed> and 
    // <target: double target to be attributed based on the string source>
    // Returns: Success or error, if there were any
    void StrToDouble(char *source, double *target)
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

    // Summary: Tries to parse a string source to a char target
    // Parameters: <source: string to be readed and parsed> and
    // <target: char target to be attributed based on the string source>
    // Returns: Succes or error, if there were any
    void StrToChar(char *source, char* target)
    {
        *target = source[0];
    }

    // Summary: divides a value until it reaches 0 to know how many algarisms it has
    // Parameters: <value: int value to be multiplied for 0.1 until it's value is 0>
    // Returns: <int: number of algarisms the value has>
    int NumAlgs(unsigned long long int value)
    {
        int result = 1;

        while ((value /= 10) != 0)
        {
            result++;
        }
        
        return result;
    }

#pragma endregion

///////////////////////////////////