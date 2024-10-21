#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

#define INPUT_FILENAME "hl"
#define MAX_FILE_SIZE 2000000

typedef struct
{
    char *name;
    int filesize;
    int checksum;
    int offset;
    unsigned char oldByte;
    unsigned char newByte;
} Patch;

const Patch patches[] = {
    {"Half-Life Beta 9 Net Test 1 - timebomb", 1171456, 103791551, 269647, 0x22, 0x6B},
    {"Half-Life Beta 12 Net Test 2 - CD check", 1191936, 105952782, 271776, 0x81, 0xC3},
    {"Half-Life Beta 12 Net Test 2 - timebomb", 1191936, 105952782, 277199, 0x22, 0x6B}};

void exitPrompt()
{
    printf("Press any key to exit");
    getchar();
}

void handleError(FILE *file, unsigned char *buffer, const char *message)
{
    if (file)
        fclose(file);
    if (buffer)
        free(buffer);
    fprintf(stderr, "Error: %s\n", message);
    exitPrompt();
    exit(EXIT_FAILURE);
}

int main()
{
    printf("Half-Life Net Test Beta patcher\n"
           "https://github.com/54ac/nettest-patcher\n"
           "=======================================\n\n");

    const char *oldFileName = INPUT_FILENAME ".old";
    FILE *fileCheck = fopen(oldFileName, "r");
    if (fileCheck)
        handleError(fileCheck, NULL, "Backup file already exists");

    const char *inputFileName = INPUT_FILENAME ".exe";
    FILE *inputFile = fopen(inputFileName, "rb");
    if (!inputFile)
        handleError(NULL, NULL, "Input file could not be opened");

    fseek(inputFile, 0, SEEK_END);
    const size_t filesize = ftell(inputFile);
    if (filesize > MAX_FILE_SIZE)
        handleError(inputFile, NULL, "File too large");

    rewind(inputFile);

    unsigned char *buffer = malloc(filesize);
    if (!buffer)
        handleError(inputFile, NULL, "Memory allocation failed");

    if (fread(buffer, 1, filesize, inputFile) != filesize)
        handleError(inputFile, buffer, "File read error");

    fclose(inputFile);

    int fileChecksum = 0;
    for (int i = 0; i < filesize; i++)
        fileChecksum += buffer[i];

    // printf("File checksum: %d\n", fileChecksum);

    bool validFile = false;
    bool alreadyApplied = true;

    for (const Patch *p = patches; p < patches + sizeof(patches) / sizeof(Patch); p++)
    {
        if (filesize == p->filesize && fileChecksum == p->checksum)
        {
            validFile = true;

            if (buffer[p->offset] == p->oldByte)
            {
                buffer[p->offset] = p->newByte;
                alreadyApplied = false;
                printf("%s patch applied\n", p->name);
            }
            else if (buffer[p->offset] == p->newByte)
                printf("%s patch already applied\n", p->name);
            else
                validFile = false;
        }
    }

    if (!validFile)
        handleError(NULL, buffer, "Unknown version");
    if (alreadyApplied)
        handleError(NULL, buffer, "File already patched");

    if (rename(inputFileName, oldFileName) != 0)
        handleError(NULL, buffer, "Can't rename original file");

    FILE *outputFile = fopen(inputFileName, "wb");
    if (!outputFile)
        handleError(NULL, buffer, "Output file could not be opened");

    if (fwrite(buffer, 1, filesize, outputFile) != filesize)
        handleError(outputFile, buffer, "File write error");

    fclose(outputFile);
    free(buffer);

    printf("\nFile patched successfully, original file saved as %s\n", oldFileName);
    exitPrompt();
    return EXIT_SUCCESS;
}
