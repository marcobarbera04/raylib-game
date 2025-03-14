#include "config.h"

void loadConfiguration(Config *config)
{
    FILE *file = fopen("config.txt", "r");      // Path relative to the .exe
    if(file == NULL)
    {
        printf("[ERROR]: could not open config file\n");
        return;
    }

    printf("[SUCCESS]: successfully opened config file\n");
    char line[256];
    while(fgets(line, sizeof(line), file))
    {
        char key[50];
        char value[50];
        sscanf(line, "%49[^=]=%49s", key, value);

        if(strcmp(key, "screenWidth") == 0)
        {
            config->screenWidth = atoi(value);
        }else
        if(strcmp(key, "screenHeight") == 0)
        {
            config->screenHeight = atoi(value);
        }
    }
    fclose(file);
}