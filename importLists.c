#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "shortPath.h"

struct energyList* importEnergyFile()
{
    char fileScanner[255];
    //store start and end cities with energy expended between them
    char start[150];
    char end[150];
    int energy;

    //pointer to saved energy file
    char* filename = "energy.txt";
    FILE *filePointer;

    filePointer = fopen(filename, "r");

    struct energyList* energyList;
    energyList = energyListConstructor();

    struct CityList* cityList;
    cityList = cityListConstructor();

    //returns a fail case if opening the file is unsuccessful
    if (filePointer == NULL)
    {
        return 0;
    }
    else
    {
        //Read the data from the file
        while(fgets(fileScanner, sizeof(fileScanner), filePointer) != NULL)
        {
            //scanning each line and passing the value to
            sscanf(fileScanner, "%s\t%s\t%d\n", start, end, &energy);
            energyListAdd(energyList, start, end, energy);
            //printf("%s\n", start);
        }
        while(fgets(fileScanner, sizeof(fileScanner), filePointer) != NULL)
        {
            //scanning each line and passing the value to
            sscanf(fileScanner, "%s\t%s\t%d\n", start, end, &energy);
            cityListAdd(cityList, start);
        }

    fclose(filePointer);
    }
    energyListDisplay(energyList);
    cityListDisplay(cityList);
    return energyList;
}

