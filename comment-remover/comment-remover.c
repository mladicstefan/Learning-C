#include <stdio.h>
#include <stdbool.h>

#define STATE_NORMAL 0
#define STATE_SINGLE_LINE_COMMENT 1
#define STATE_MULTI_LINE_COMMENT 2
#define STATE_STRING_LITERAL 3
#define STATE_CHAR_LITERAL 4

int main(void)
{

    FILE *inFile = fopen("sample.c", "r");
    if (inFile == NULL)
    {
        perror("Error opening input file");
        return 1;
    }

    FILE *outFile = fopen("file_copy.c", "w");
    if (outFile == NULL)
    {
        perror("Error opening output file");
        fclose(inFile);
        return 1;
    }

    int ch, next_ch;
    int state = STATE_NORMAL;
    bool was_backslash = false;

    while ((ch = fgetc(inFile)) != EOF)
    {
        switch (state)
        {
        case STATE_NORMAL:
            if (ch == '/')
            {

                next_ch = fgetc(inFile);
                if (next_ch == '/')
                {

                    state = STATE_SINGLE_LINE_COMMENT;
                }
                else if (next_ch == '*')
                {

                    state = STATE_MULTI_LINE_COMMENT;
                }
                else
                {

                    if (next_ch != EOF)
                    {
                        fputc(ch, outFile);
                        fputc(next_ch, outFile);
                    }
                    else
                    {

                        fputc(ch, outFile);
                    }
                }
            }
            else if (ch == '"')
            {

                state = STATE_STRING_LITERAL;
                was_backslash = false;
                fputc(ch, outFile);
            }
            else if (ch == '\'')
            {

                state = STATE_CHAR_LITERAL;
                was_backslash = false;
                fputc(ch, outFile);
            }
            else
            {

                fputc(ch, outFile);
            }
            break;

        case STATE_SINGLE_LINE_COMMENT:
            if (ch == '\n')
            {
                state = STATE_NORMAL;
                fputc(ch, outFile);
            }
            break;

        case STATE_MULTI_LINE_COMMENT:

            if (ch == '*')
            {
                next_ch = fgetc(inFile);
                if (next_ch == '/')
                {
                    state = STATE_NORMAL;
                }
                else
                {
                    if (next_ch != EOF)
                    {
                        ungetc(next_ch, inFile);
                    }
                }
            }
            break;

        case STATE_STRING_LITERAL:

            fputc(ch, outFile);
            if (was_backslash)
            {
                was_backslash = false;
            }
            else
            {
                if (ch == '\\')
                {
                    was_backslash = true;
                }
                else if (ch == '"')
                {

                    state = STATE_NORMAL;
                }
            }
            break;

        case STATE_CHAR_LITERAL:

            fputc(ch, outFile);
            if (was_backslash)
            {
                was_backslash = false;
            }
            else
            {
                if (ch == '\\')
                {
                    was_backslash = true;
                }
                else if (ch == '\'')
                {

                    state = STATE_NORMAL;
                }
            }
            break;

        default:
            state = STATE_NORMAL;
            break;
        }
    }

    fclose(inFile);
    fclose(outFile);
    return 0;
}

