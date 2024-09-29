#include <stdio.h>
#include <stdlib.h>

#define INPUT_FILE "hl.exe"
#define OUTPUT_FILE "hlpatch.exe"
#define FILE_SIZE 1191936

typedef struct
{
    long location;
    unsigned char oldByte;
    unsigned char newByte;
} Patch;

Patch patches[] = {
    {271776, 0x81, 0xC3}, // CD check
    {277199, 0x22, 0x6B}  // timebomb
};

void handle_error(const char *message)
{
    fprintf(stderr, "Error: %s", message);
    getchar();
    exit(EXIT_FAILURE);
}

FILE *open_file(const char *filename, const char *mode)
{
    FILE *file = fopen(filename, mode);
    if (!file)
    {
        handle_error("Could not open file");
    }
    return file;
}

void replace_byte(unsigned char *buffer, Patch patch)
{
    if (buffer[patch.location] != patch.oldByte)
    {
        handle_error("Wrong byte");
    }
    buffer[patch.location] = patch.newByte;
}

int main()
{
    printf("Half-Life Net Test 2 beta timebomb & CD check patcher\n");
    printf("https://github.com/54ac/nettest-patcher\n");
    printf("=====================================================\n\n");

    // read file, check filesize
    FILE *inputFile = open_file(INPUT_FILE, "rb");
    fseek(inputFile, 0, SEEK_END);
    int fileSize = ftell(inputFile);
    if (fileSize != FILE_SIZE)
    {
        handle_error("Wrong file size");
    }

    // read file into memory
    fseek(inputFile, 0, SEEK_SET);
    unsigned char *buffer = malloc(fileSize);
    if (!buffer)
    {
        handle_error("Memory allocation failed");
    }
    fread(buffer, 1, fileSize, inputFile);
    fclose(inputFile);

    // check if already patched before replacing bytes
    int alreadyPatched = 1;
    int numPatches = sizeof(patches) / sizeof(Patch);
    for (int i = 0; i < numPatches; i++)
    {
        if (buffer[patches[i].location] != patches[i].newByte)
        {
            alreadyPatched = 0;
            replace_byte(buffer, patches[i]);
        }
    }
    if (alreadyPatched)
    {
        handle_error("File already patched");
    }

    // write patched file
    FILE *outputFile = open_file(OUTPUT_FILE, "wb");
    fwrite(buffer, 1, fileSize, outputFile);
    fclose(outputFile);
    free(buffer);

    printf("File patched successfully\n");
    printf("Output written to %s", OUTPUT_FILE);
    getchar();
    return EXIT_SUCCESS;
}
