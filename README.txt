In this directory, there is the /src/ directory which contains the helper functions for a BMP struct and 
the helper functions for producing a contour line.

Inside the src contains:
	- ctrace_helper.h -- function prototypes for contour tracing
	- ctrace_helper.c -- function implementations for contour tracing
	- BMPstructfns.h -- function prototypes for creating a BMP struct
	- BMPstructures.h -- contains the declarations of the fields for the BMP related structures
	- BMPstructfns.c -- function implementations for reading, writing, and creating a BMP struct/BMP file
	- contour_trace.c -- contains the main function which utilizes aforementioned helper functions

The executable 'contour.out' takes in arguments for: 
- the name of the original BMP file for input (string)
- the name of the contour BMP file for output (string)
- the row coordinate of the pixel desired (integer)
- the column coordinate of the pixel desired (integer)

contour.out <original bmp file name> <contour bmp file name> <row desired> <column desired>

Example: 
contour.out bigbf.bmp outline.bmp 105 210

contour.out will output the contour line as a black line on a white background onto outline.bmp which will be the same
size of the original bmp file. It will also output the information of the bmp file header onto standard output.

NOTE: This program will just output a white bmp file if the rows and columns are out of bounds