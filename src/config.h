#ifndef CONFIG_H
#define CONFIG_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct Config
{
    int screenWidth;
    int screenHeight;
};

void loadConfiguration(struct Config *config);

#endif