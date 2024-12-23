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
    // Return: Success or error, if there were any
    int StrReader(char *target, int size)
    {
        int result;
        char input = getchar();

        while (input != 10)
        {
            if (size > sizeof(char))
            {
                *target = input;
                target += sizeof(char);
                size -= sizeof(char);
            }
            input = getchar();
        }

        *target = '\0';
               
        return result;
    }

    // Summary: Tries to parse a string source to an int target
    // Parameters: <source: string to be readed and parsed> and
    // <target: integer target to be attributed based on the string source>
    // Returns: Success or error, if there were any
    int StrToInt(char* source, int* target)
    {
        int result;

        // [...]

        return result;
    }

    // Summary: Tries to parse a string source to a float target
    // Parameters: <source: string to be readed and parsed> and
    // <target: float target to be attributed based on the string source>
    // Returns: Success or error, if there were any
    int StrToFloat(char *source, float* target)
    {
        int result;

        // [...]
        
        return result;
    }

    // Summary: Tries to parse a string source to a double target
    // Parameters: <source: string to be readed and parsed> and 
    // <target: double target to be attributed based on the string source>
    // Returns: Success or error, if there were any
    int StrToDouble(char *source, float *target)
    {
        int result;

        // [...]
        
        return result;
    }

    // Summary: Tries to parse a string source to a char target
    // Parameters: <source: string to be readed and parsed> and
    // <target: char target to be attributed based on the string source>
    // Returns: Succes or error, if there were any
    int StrToChar(char *source, char* target)
    {
        int result;

        // [...]
        
        return result;
    }

#pragma endregion

///////////////////////////////////