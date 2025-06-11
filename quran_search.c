#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>

#define MAX_VERSE_LENGTH 2000
#define MAX_LINE_LENGTH 2100

// Convert string to lowercase (helper function)
void to_lowercase(char *str)
{
    for (int i = 0; str[i]; i++)
    {
        str[i] = tolower((unsigned char)str[i]);
    }
}

void find_verse_in_quran_file(const char *search_term_original)
{
    FILE *file = fopen("quran.txt", "r");
    if (file == NULL)
    {
        printf("Error: Could not open 'quran.txt'.\n");
        return;
    }

    char line[MAX_LINE_LENGTH];
    int found = 0;

    // Create lowercase copy of search term
    char search_term[MAX_VERSE_LENGTH];
    strncpy(search_term, search_term_original, MAX_VERSE_LENGTH);
    to_lowercase(search_term);

    while (fgets(line, sizeof(line), file))
    {
        line[strcspn(line, "\n")] = 0; // Remove newline

        char *first_colon = strchr(line, ':');
        if (!first_colon)
            continue;

        char *second_colon = strchr(first_colon + 1, ':');
        if (!second_colon)
            continue;

        char *verse_text = second_colon + 1;

        // Make a lowercase copy of verse text for comparison
        char verse_text_copy[MAX_VERSE_LENGTH];
        strncpy(verse_text_copy, verse_text, MAX_VERSE_LENGTH);
        to_lowercase(verse_text_copy);

        if (strstr(verse_text_copy, search_term) != NULL)
        {
            char chapter[10], verse[10];
            sscanf(line, "%[^:]:%[^:]:", chapter, verse);

            printf("\n--- Match Found! ---\n");
            printf("Surah: %s\n", chapter);
            printf("Ayah:  %s\n", verse);
            printf("Verse: %s\n", verse_text);
            printf("--------------------\n");

            found = 1;
            break;
        }
    }

    if (!found)
    {
        printf("\nSorry, that verse could not be found. Please check your input.\n");
    }

    fclose(file);
}
int main()
{
    char user_verse[MAX_VERSE_LENGTH];

    printf("======================================\n");
    printf("          Quran Verse Finder \n");
    printf("======================================\n");
    printf("Enter part of the verse you're looking for:\n> ");

    if (fgets(user_verse, sizeof(user_verse), stdin) != NULL)
    {
        user_verse[strcspn(user_verse, "\n")] = 0;

        if (strlen(user_verse) > 5)
        {
            find_verse_in_quran_file(user_verse);
        }
        else
        {
            printf("The text you entered is too short. Please enter a more complete verse.\n");
        }
    }

    return 0;
}
