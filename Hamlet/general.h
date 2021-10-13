#ifndef GENERAL_H_INCLUDED
#define GENERAL_H_INCLUDED

#include <stdio.h>
#include <string.h>
#include <assert.h>
#include <ctype.h>
#include <stdlib.h>

/**
    Structure contains 2 elements string and length
 */
struct poemString {
    char *str;
    int length;
};

/// Enum type for choosing the way of sort
enum typeOfSort {
    INVERSE,                ///< sorting from the last symbol
    NORMAL                  ///< sortingg from the first symbol
};

/// Enum type for compairing 2 strings
enum resultOfStringCompare {
    LESS,                   ///< 2nd string is more than 1st
    EQUAL,                  ///< strings are equal
    MORE                    ///< 1st is more than 2nd
};

/**
    \brief This function allocates memory for char
 */
char *BufferAlloc (size_t *fileSize, FILE *input);

/**
    \brief This function calculates number of strings in the file.
    \param [out] input file
 */
int NumberOfStrings (FILE *input);

/**
    \brief This function calculates the file size in bytes.
    \param [out] input file
 */
int GetFileSize (FILE *input);

/**
    \brief This function gets 1 line from the string and puts it into the string element of the structure.
    \param [out] str string value
    \param [out] structPtr pointer to the structure
 */
struct poemString *GetLine (char *str, struct poemString *structPtr);

/**
    \brief This function initializes the elements of pointers array
    \param [in] ptrToStrArr pointer to the array of pointers to the structure
    \param [in] sourceString string used to initialize string elements of structure
    \param [in] numbOfStrings number of elements in pointers array
    Function initializes array of pointers to the structure
 */
void InitializeArrOfPointers (struct poemString **ptrToStrArr, char *sourceString, const int numbOfStrings);

/**
    \brief This function puts all string elements of all given structures to the file.
    \param [out] output pointer to the file
    \param [in] ptrToStrArr pointer to the array of pointers to the structure
    \param [in] numbOfStrings size of pointer array
 */
void PrintStringElsOfPoemStringToFile (FILE *output, struct poemString **ptrToStrArr, const int numbOfStrings);

/**
    \brief This function checks if the file is opened.
    \param [in] file
    If the file isn't opened, program terminates saying file couldn't be opened
 */
void CheckIfFileOpened (FILE *file);

/**
    \brief This function prints modified string to the file
    \param [in] output file
    \param [out] src string whis is needed to be printed to the file
    \param [out] numbOfStrings number of strings
    Function prints modified buffer to the file
 */
void PrintStringToFile (FILE *output, char *src, const int numbOfStrings);

/**
    \brief This function move the pointer to the first letter in string
    \param [out] pointer to the string
    \param [out] type of skip (inverse or normal)
 */
char *SkipNonLetters (char *src, const int typeOfSkip);

/**
    \brief This function compares string elements of structures
    \param [in] struct1 1st structure
    \param [in] struct2 2nd structure
    \param [out] typeOfCompare type of compare
 */
int StringStructComp (poemString *struct1, poemString *struct2, const int typeOfCompare);

/**
    \brief This function returns min of two values
 */
int MinOf2Integers (const int value1, const int value2);

/**
    \brief This function swaps 2 poemStrings structures
 */
void PoemStringSwap (poemString *struct1, poemString *struct2);

/**
    \brief This function sorts poemString structures in special order using quicksort
    \param [in] ptrToStrArr pointer to the array of pointers
    \param [out] left index of 1st element
    \param [out] right index of last element
    \param [out] typeOfSort type of sort
    This function sorts structures in their strings alphabetical order starting from the first symbol in NORMAL mode.
    If it is INVERSE, it is done starting from last symbol in string
 */
void QsortRecursive (poemString **ptrToStrArr, const int left, const int right, const int typeOfSort);

/**
    \brief This function frees memory allocated for array of structures
 */
void FreeMemory (poemString **ptr, const int numbOfStrings);

/**
    \brief This function returns name of file which is needed to be sorted
 */
 char *nameOfFile ();

#endif // GENERAL_H_INCLUDED
