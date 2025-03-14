#ifndef CONFIG_H
#define CONFIG_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct Config
{
    float screenWidth;
    float screenHeight;
}Config;

void loadConfiguration(Config *config);

#endif