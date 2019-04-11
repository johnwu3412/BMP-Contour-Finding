#include "BMPstructfns.h"
struct linkednode{
	int r;
	int c;
	struct linkednode *next;
};

//bmpfloodfill -- uses floodfill algorithm in order to determine edges of a color region
void bmpfloodfill(int r, int c, uint8_t *mask, struct BMPfile bmfile, struct pixel ogcolor);

//compareColor -- compares two colors to see if they are somewhat similar; returns 0 if similar
int compareColor(struct pixel p1, struct pixel p2);

//linkedlistToPix -- turns the linked list into the corresponding pixel array which shows only edges 
struct pixel *linkedlistToPix(int height, int width);

void freeNodes(struct linkednode *head);