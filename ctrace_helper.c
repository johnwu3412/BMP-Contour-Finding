#include "BMPstructfns.h"
#define COLOR_DIFFERENCE_THRESHOLD 30

//defining structure
struct linkednode{
	int r;
	int c;
	struct linkednode *next;
};

//defining static variables (head and tails of linked list)
static struct linkednode *head = NULL;
static struct linkednode *tail = NULL;

//frees linked list 
void freeNodes(struct linkednode *head){
	if(head != NULL){
		freeNodes(head->next);
	}
	free(head);
}

//bmpfloodfill -- uses floodfill algorithm in order to determine edges of a color region
void bmpfloodfill(int r, int c, uint8_t *mask, struct BMPfile bmfile, struct pixel ogcolor){
	int numR = bmfile.hdr.bitmap_height;
	int numC = bmfile.hdr.bitmap_width;
	
	//edge checking
	if(r >= numR || r < 0){
		return;
	}if(c >= numC || c < 0){
		return;
	}
	
	//already checked
	if(mask[r*numC + c] != 0){
		return;
	}
	
	if(compareColor(ogcolor, bmfile.pix[r*numC + c]) == 0){//colors are the same
		mask[r*numC + c] = 1;
		
		//recursive call to all adjacent pixels
		bmpfloodfill(r+1, c, mask, bmfile, ogcolor);
		bmpfloodfill(r, c+1, mask, bmfile, ogcolor);
		bmpfloodfill(r-1, c, mask, bmfile, ogcolor);
		bmpfloodfill(r, c-1, mask, bmfile, ogcolor);
		
		bmpfloodfill(r-1, c-1, mask, bmfile, ogcolor);
		bmpfloodfill(r+1, c+1, mask, bmfile, ogcolor);
		bmpfloodfill(r+1, c-1, mask, bmfile, ogcolor);
		bmpfloodfill(r-1, c+1, mask, bmfile, ogcolor);
	}else{//colors are different - edge detected, stops recursion
		struct linkednode *newnode = (struct linkednode *)malloc(sizeof(struct linkednode));
		newnode->r = r;
		newnode->c = c;
		newnode->next = NULL;
		if(tail == NULL){
			head = newnode;
			tail = newnode;
		}else{
			tail->next = newnode;
			tail = tail->next;
		}
		mask[r*numC + c] = 2;
	}
}

//compareColor -- compares two colors to see if they are somewhat similar; returns 0 if similar
int compareColor(struct pixel p1, struct pixel p2){
	if(abs(p1.red-p2.red) > COLOR_DIFFERENCE_THRESHOLD ||
	   abs(p1.blue-p2.blue) > COLOR_DIFFERENCE_THRESHOLD ||
	   abs(p1.green-p2.green) > COLOR_DIFFERENCE_THRESHOLD){
		return 1;
	}else{
		return 0;
	}
}

//linkedlistToPix -- turns the linked list into the corresponding pixel array which shows only edges, frees the linked list at the end
struct pixel *linkedlistToPix(int height, int width){
	struct pixel *pix = malloc(sizeof(struct pixel) * height * width);
	struct linkednode *current = head;
	int c = 0;
	for(; c < height*width; c++){
		pix[c].red = 255;
		pix[c].blue = 255;
		pix[c].green = 255;
	}
	
	while(current->next != NULL){
		pix[current->r * width + current->c].blue = 0;
		pix[current->r * width + current->c].green = 0;
		pix[current->r * width + current->c].red = 0;
		current = current->next;
	}
	printf("Returning pixels!");
	freeNodes(head);
	free(tail);
	return pix;
}
