///////////////////////////////////

#pragma region Header

    #include "CReader.h"

#pragma endregion

///////////////////////////////////

#pragma region FUNCTIONS

    // Summary: Receives a format and a address for the target variable
    // Parameters: <Format: string passing type of variable, %d, %f...> and <Target: pointer to the
    // variable to be attributed with the input>
    // Returns: Success or error, if there's any
    int CRead(char* format, void* target)
    {
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
        // inicializa
        *target = 0;
        int negativo = 0;

        // se a string representar um inteiro negativo...
        if (source[0] == '-')
        {
            *target = (source[1] - '0'); 
            source += 2 * sizeof(char);
            negativo = 1;
        }

        // enquanto não encontrar o final da string
        while (source[0] != '\0')
        {
            *target *= 10;
            *target += (source[0] - '0');
            source += sizeof(char);
        }
        
        // se o número representado pela string era negativo
        if (negativo)
            *target *= -1;
    }

    // Summary: Tries to parse a string source to a float target
    // Parameters: <source: string to be readed and parsed> and
    // <target: float target to be attributed based on the string source>
    // Returns: Success or error, if there were any
    void StrToFloat(char *source, float* target)
    {
        // inicializa
        *target = 0;
        int negativo = 0;

        // se a string representar um inteiro negativo...
        if (source[0] == '-')
        {
            *target = (source[1] - '0'); 
            source += 2 * sizeof(char);
            negativo = 1;
        }

        // enquanto não encontrar o final da string
        while (source[0] != '\0' && source[0] != '.')
        {
            *target *= 10;
            *target += (source[0] - '0');
            source += sizeof(char);
        }
        
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
        
        // se o número representado pela string era negativo
        if (negativo)
            *target *= -1;
    }

    // Summary: Tries to parse a string source to a double target
    // Parameters: <source: string to be readed and parsed> and 
    // <target: double target to be attributed based on the string source>
    // Returns: Success or error, if there were any
    void StrToDouble(char *source, float *target)
    {
        int result;

        // [...]
    }

    // Summary: Tries to parse a string source to a char target
    // Parameters: <source: string to be readed and parsed> and
    // <target: char target to be attributed based on the string source>
    // Returns: Succes or error, if there were any
    void StrToChar(char *source, char* target)
    {
        int result;

        *target = source[0];
    }

#pragma endregion

///////////////////////////////////