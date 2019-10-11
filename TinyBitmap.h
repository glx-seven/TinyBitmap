// ------------- MIT-LICENCE -------------
//
//Copyright 2017 Theo Bestenlehner
//
//Permission is hereby granted, free of charge, to any person obtaining a copy of this software and associated documentation files (the "Software"), to deal in the 
//Software without restriction, including without limitation the rights to use, copy, modify, merge, publish, distribute, sublicense, and/or sell copies of the Software, 
//and to permit persons to whom the Software is furnished to do so, subject to the following conditions:
//
//The above copyright notice and this permission notice shall be included in all copies or substantial portions of the Software.
//
//THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY, FITNESS FOR A 
//PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION 
//OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.


#ifndef TINYBITMAP_H_
#define TINYBITMAP_H_


class TinyBitmap
{
private:
    int _IMAGEWIDTH;
    int _IMAGEHEIGHT;
    int _COMMANDBYTES;
    int _BITMAPLAYOUT;
    char *_FRAMEBUFFER;
    
//    const char Bit0 = 0x01;
//    const char Bit1 = 0x02;
//    const char Bit2 = 0x04;
//    const char Bit3 = 0x08;
//    const char Bit4 = 0x10;
//    const char Bit5 = 0x20;
//    const char Bit6 = 0x40;
//    const char Bit7 = 0x80;
    
public:
    TinyBitmap(int width, int height, char *framebuffer, int commandbytes = 0, int bitmaplayout = 0x00);//Constructor; creates a bitmap-handler with the given size and layout, can also leave some space for command-bytes to control a display. The bitmap (char[]) itself has to be created seperately.

    void DrawPixel(int x, int y); //Draws a single pixel
    void DrawLine(int x1, int y1, int x2, int y2);//Draws a line between two points
    void DrawCircle(int x, int y, int radius);//Draws a circle
    void DrawRectangle(int x1, int y1, int x2, int y2); //Draws a rectangle. The coordinates are the opposite corners
    void DrawLineDirection(int x, int y, int degree, int lenght); //Draws a line from a point into a direction with a given length. 0° is from the starting point to the right.
    void DrawText(int x, int y, char *CharArray, bool UseLargeFont = false); //Draws basic text in two different sizes on the given location.
    void ClearScreen(); //Clears the content of the bitmap to zeros
};
#endif
