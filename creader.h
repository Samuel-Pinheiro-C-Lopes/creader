///////////////////////////////////

#pragma region DEPENDENCIES

    #include <stdio.h>
    #include <limits.h>
    #include <float.h>
    #include <unistd.h>
    #include <stdarg.h>

#pragma endregion

///////////////////////////////////

#pragma region DEFINITIONS

    // For now, consider the maximum size of a string readed to be 255
    #define STR_MAX_SIZE (255)

    // Results of funcions that succeded in the task provided
    #define SUCCESS (1)

    // Expected errors
    #define INVALID_FORMAT (-10) // in case the <char* format> is invalid in <int CRead([...])>

    // in case the string source is empty in any of the 
    // <int StrTo[...]([...])> auxiliary functions
    #define STR_EMPTY (-30) 

    // in case the string source has any char that is invalid to the target in any of the 
    // <int StrTo[...]([...])> auxiliary functions
    #define INVALID_CHAR (-31) 

#pragma endregion

///////////////////////////////////

#pragma region FUNCTIONS

    // Main function for this project, reads based on format provided to the target variable
    // in case of the format specifying a string, the maximum size is needed
    int cread(char* format, void* target);
 int _cread (char* format, ...);

#pragma endregion

///////////////////////////////////

#pragma region AUXILIARY FUNCTIONS

    // Reads from input until size of string is reached or 'enter' key is pressed
    void StrReader(char* target, int size);
    
    // Tries to parse a string source to an int target
    void StrToInt(char* source, long long int* target);

    // Tries to parse a string source to a float target
    void StrToFloat(char* source, float* target);
    
    // Tries to parse a string source to a double target
    void StrToDouble(char* source, double* target);

    // Tries to parse a string source to a char target
    void StrToChar(char* source, char* target);

    // Gets the number of algarisms of an integer value
    int NumAlgs(double value);
    
#pragma endregion

///////////////////////////////////