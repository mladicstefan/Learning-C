#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>

int main(int argc, char *argv[]) {
    if (argc < 2) {
        fprintf(stderr, "Usage: %s <filename>\n", argv[0]);
        return 1;
    }

    FILE *file = fopen(argv[1], "r");
    if (file == NULL) {
        perror("Error opening file");
        return 1;
    }

    int ch;             // Variable to store each character read.
    int charCount = 0;  // Counter for characters.
    int wordCount = 0;  // Counter for words.
    int lineCount = 0;  // Counter for lines.
    int inWord = 0;     // Flag to track if we're inside a word.

    while ((ch = fgetc(file)) != EOF) {
        charCount++; // Every character read is counted.

        // Count new lines.
        if (ch == '\n') {
            lineCount++;
        }

        // If the character is a whitespace, we're not in a word.
        if (isspace(ch)) {
            inWord = 0;
        } else if (inWord == 0) { 
            // Transitioning from whitespace to non-whitespace means a new word starts.
            inWord = 1;
            wordCount++;
        }
    }

    fclose(file);

    printf("Characters: %d\n", charCount);
    printf("Words: %d\n", wordCount);
    printf("Lines: %d\n", lineCount);

    return 0;
}

