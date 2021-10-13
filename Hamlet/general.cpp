#include "general.h"

void InitializeArrOfPointers (poemString **ptrToStrArr, char *sourceString, const int numbOfStrings) {
    for (int indexOfStruct = 0; indexOfStruct < numbOfStrings; indexOfStruct++) {
        assert (ptrToStrArr + indexOfStruct);

        *(ptrToStrArr + indexOfStruct) = (struct poemString *)calloc (1, sizeof(struct poemString));
        *(ptrToStrArr + indexOfStruct) = GetLine(sourceString, *(ptrToStrArr + indexOfStruct));

        sourceString += (*(ptrToStrArr + indexOfStruct))->length;
    }
}

int GetFileSize (FILE *input) {
    assert (input);

    int numberOfSymbols = 0;

    fseek (input, 0, SEEK_END);

    numberOfSymbols = ftell (input);

    fseek (input, 0, SEEK_SET);

    return numberOfSymbols;
}

int NumberOfStrings (FILE *input) {
    assert (input);

    int number = 0;

    char symbol = (char)getc (input);

    while (symbol != EOF) {
        if (symbol == '\n') {
            number++;
        }

        symbol = (char)getc (input);
    }

    fseek (input, 0, SEEK_SET);

    return number;
}

struct poemString *GetLine (char *str, struct poemString *structPtr) {
    assert (str);
    assert (structPtr);

    structPtr->str = str;

    while (*str != '\n') {
        structPtr->length++;
        str++;
    }

    *str = '\0';
    (structPtr->length)++;

    return structPtr;
}

void PrintStringElsOfPoemStringToFile (FILE *output, struct poemString **ptrToStrArr, const int numbOfStrings) {
    assert (ptrToStrArr);
    assert (output);

    for (int indexOfStruct = 0; indexOfStruct < numbOfStrings; indexOfStruct++) {
        fprintf (output, "%s\n", (*(ptrToStrArr + indexOfStruct))->str);
    }

    fprintf (output, "\n\n\n\n\n\n\n\n\n------------------------------------------------------------------\n\n\n\n\n\n\n\n\n");
}

void CheckIfFileOpened (FILE *file) {
    if (file == nullptr) {
        printf ("Couldn't open the file.\n");
    }
}

char *BufferAlloc (size_t *fileS, FILE *input) {
    assert (fileS);
    assert (input);

    char *src = (char*)calloc (*fileS, sizeof (char));

    if (src == nullptr) {
        return nullptr;
    }

    *fileS = fread (src, sizeof (char), *fileS, input);
    fseek (input, 0, SEEK_SET);

    return src;
}

void PrintStringToFile (FILE *output, char *src, const int numbOfStrings) {
    int lengthOfString = 0;

    for (int indexOfStruct = 0; indexOfStruct < numbOfStrings; indexOfStruct++) {
        lengthOfString = fprintf (output, "%s\n", src);

        src += lengthOfString;
    }
}

char *SkipNonLetters (char *src, const int typeOfSkip) {
    assert (src);

    switch (typeOfSkip) {
        case NORMAL : {
            while (!isalpha((int)*src) && *src != '\0') {
                src++;
            }

            break;
        }
        case INVERSE : {
            while (!isalpha((int)*src) && *src != '\0') {
                src--;
            }

            break;
        }
        default : {
            printf ("Unknown type of sort: %d\n", typeOfSkip);
        }
    }

    return src;
}

int StringStructComp (poemString *struct1, poemString *struct2, const int typeOfCompare) {
    assert (struct1);
    assert (struct2);

    if (typeOfCompare != NORMAL && typeOfCompare != INVERSE) {
        printf ("Error occured in line %d in function %s: invalid type of sort %d\n", __LINE__, __func__, typeOfCompare);
        return -1;
    }

    char *str1 = struct1->str;
    char *str2 = struct2->str;

    assert (str1);
    assert (str2);

    if (typeOfCompare == INVERSE) {
        str1 += (struct1->length - 2);
        str2 += (struct2->length - 2);
    }

    str1 = SkipNonLetters (str1, typeOfCompare);
    str2 = SkipNonLetters (str2, typeOfCompare);

    int diff = 0;

    while (*str1 != '\0' || *str2 != '\0') {
        str1 = SkipNonLetters (str1, typeOfCompare);
        str2 = SkipNonLetters (str2, typeOfCompare);

        diff = toupper ((int)*str1) - toupper ((int)*str2);

        if (diff > 0) {

            return MORE;

        } else if (diff < 0) {

            return LESS;

        }

        if (typeOfCompare == NORMAL) {

            str1++;
            str2++;

        } else if (typeOfCompare == INVERSE) {

            str1--;
            str2--;

        }
    }

    if (struct1->length == struct2->length) {

        return EQUAL;

    }

    return LESS;
}

int MinOf2Integers (const int value1, const int value2) {
    if (value1 > value2) {

        return value2;

    } else if (value1 < value2) {

        return value1;

    } else {

        return value1;

    }
}

void PoemStringSwap (poemString *struct1, poemString *struct2) {
    assert (struct1);
    assert (struct2);

    poemString tmp = *struct1;
    *struct1 = *struct2;
    *struct2 = tmp;
}

void QsortRecursive (poemString **ptrToStrArr, const int left, const int right, const int typeOfSort) {
    assert (ptrToStrArr);

    if (typeOfSort != NORMAL && typeOfSort != INVERSE) {
        printf ("Error: invalid type of sort: %d\n", typeOfSort);
        return;
    }

    int i = 0;
    int last = left;

    if (left >= right) {
        return;
    }

    for (i = left + 1; i <= right; i++) {
        if (StringStructComp (ptrToStrArr[i], ptrToStrArr[left], typeOfSort) == LESS) {
            PoemStringSwap (ptrToStrArr[++last], ptrToStrArr[i]);
        }
    }
    PoemStringSwap (ptrToStrArr[left], ptrToStrArr[last]);

    QsortRecursive (ptrToStrArr, left, last - 1, typeOfSort);
    QsortRecursive (ptrToStrArr, last + 1, right, typeOfSort);
}

void FreeMemory (poemString **ptr, const int numbOfStrings) {

    for (int indexOfStruct = 0; indexOfStruct < numbOfStrings; indexOfStruct++) {
        free (ptr[indexOfStruct]);
    }

    free (ptr);
}

 char *nameOfFile () {
     printf ("Please, enter the name of file!\n");

     char *nameOfF = (char*)calloc (1, sizeof(char));
     scanf ("%s", nameOfF);

     return nameOfF;
 }

