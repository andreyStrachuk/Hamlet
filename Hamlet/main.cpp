#include "general.h"

int main () {
    char *nOfFile = nameOfFile ();

    FILE *onegin = fopen (nOfFile, "r");
    CheckIfFileOpened (onegin);

    size_t fileSize = GetFileSize (onegin);
    int numbOfStrings = NumberOfStrings (onegin);

    char *tmpBuff = BufferAlloc (&fileSize, onegin);

    fclose (onegin);

    poemString **poem = (poemString**)calloc (numbOfStrings, sizeof(poemString*));
    InitializeArrOfPointers (poem, tmpBuff, numbOfStrings);

    FILE *output = fopen ("file_sorted.txt", "w");
    CheckIfFileOpened (output);

    QsortRecursive (poem, 0, numbOfStrings - 1, NORMAL);
    PrintStringElsOfPoemStringToFile (output, poem, numbOfStrings);

    QsortRecursive (poem, 0, numbOfStrings - 1, INVERSE);
    PrintStringElsOfPoemStringToFile (output, poem, numbOfStrings);

    PrintStringToFile (output, tmpBuff, numbOfStrings);

    fclose (output);

    FreeMemory (poem, numbOfStrings);
    free (tmpBuff);
    free (nOfFile);

    return 0;
}
