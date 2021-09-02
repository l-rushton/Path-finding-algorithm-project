#ifndef SHORTPATH_H_INCLUDED
#define SHORTPATH_H_INCLUDED

struct energyList;

struct energyList* energyListConstructor();
void energyListDestructor(struct energyList* linkedList);

int energyListSize(struct energyList* list);
int energyListIsEmpty(struct energyList* list);
int energyListAdd(struct energyList* list, char* start, char* end, int energy);
void energyListDisplay(struct energyList* list);
int energyListRead(struct energyList* list, int index, char* start, char* end, int* energy);
int energyListRemove(struct energyList* list, int index);
int energyListSearch(struct energyList* list, char start, char end, int energy);


struct CityList;
struct CityList* cityListConstructor();
void cityListDestructor(struct CityList* linkedList);

int cityListAdd(struct CityList* list, char* city);
void cityListDisplay(struct CityList* list);
int cityListSearch(struct CityList* list, char city);
//struct energyListNode* energyListNodeConstructor(char* start, char* end, int energy);
#endif // SHORTPATH_H_INCLUDED
