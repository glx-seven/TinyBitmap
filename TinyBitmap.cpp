#define M_PI 3.14159265358979323846  //Pi

#include "mbed.h"
#include <math.h>
#include "TinyBitmap.h"

TinyBitmap::TinyBitmap(int width, int height, char *framebuffer, int commandbytes, int bitmaplayout) //Constructor
{
    _IMAGEWIDTH = width;
    _IMAGEHEIGHT = height;
    _COMMANDBYTES = commandbytes;
    _BITMAPLAYOUT = bitmaplayout;
    _FRAMEBUFFER = framebuffer;

    Bit0 = 0x01;
    Bit1 = 0x02;
    Bit2 = 0x04;
    Bit3 = 0x08;
    Bit4 = 0x10;
    Bit5 = 0x20;
    Bit6 = 0x40;
    Bit7 = 0x80;
}

void TinyBitmap::DrawPixel(int x, int y)
{
    bool InsideBorders = true;
    if (x < 0 | y < 0 | x > _IMAGEWIDTH - 1 | y > _IMAGEHEIGHT - 1) InsideBorders = false;

    if(_BITMAPLAYOUT == 0x00 && InsideBorders) {
        int pixelnumber = (y * _IMAGEWIDTH) + x; //get the 1D pixel-position
        int bytecount = pixelnumber / 8; //the byte-number
        int offset = pixelnumber % 8; //the bit inside the byte
        char modifier = 0;

        if (offset == 0) modifier = Bit7;
        if (offset == 1) modifier = Bit6;
        if (offset == 2) modifier = Bit5;
        if (offset == 3) modifier = Bit4;
        if (offset == 4) modifier = Bit3;
        if (offset == 5) modifier = Bit2;
        if (offset == 6) modifier = Bit1;
        if (offset == 7) modifier = Bit0;

        _FRAMEBUFFER[bytecount + _COMMANDBYTES] = (char)(_FRAMEBUFFER[bytecount + _COMMANDBYTES] | modifier);
    }

    if (_BITMAPLAYOUT == 0x02 && InsideBorders) 
    {
        int MemPage = y / 8;
        int bytecount = x + (_IMAGEWIDTH * MemPage); //the byte-number
        int offset = y % 8; //the bit inside the byte
        //int pixelnumber = (bytecount * 8) + offset; //get the 1D pixel-position
        char modifier = 0;

        if (offset == 7) modifier = Bit7;
        if (offset == 6) modifier = Bit6;
        if (offset == 5) modifier = Bit5;
        if (offset == 4) modifier = Bit4;
        if (offset == 3) modifier = Bit3;
        if (offset == 2) modifier = Bit2;
        if (offset == 1) modifier = Bit1;
        if (offset == 0) modifier = Bit0;

        _FRAMEBUFFER[bytecount + _COMMANDBYTES] = (char)(_FRAMEBUFFER[bytecount + _COMMANDBYTES] | modifier);
    }

    if (_BITMAPLAYOUT == 0x04 && InsideBorders) 
    {
        int pixelnumber = (y * _IMAGEWIDTH) + x; //get the 1D pixel-position
        int bytecount = pixelnumber / 8; //the byte-number
        int offset = pixelnumber % 8; //the bit inside the byte
        char modifier = 0;

        if (offset == 7) modifier = Bit7;
        if (offset == 6) modifier = Bit6;
        if (offset == 5) modifier = Bit5;
        if (offset == 4) modifier = Bit4;
        if (offset == 3) modifier = Bit3;
        if (offset == 2) modifier = Bit2;
        if (offset == 1) modifier = Bit1;
        if (offset == 0) modifier = Bit0;

        _FRAMEBUFFER[bytecount + _COMMANDBYTES] = (char)(_FRAMEBUFFER[bytecount + _COMMANDBYTES] | modifier);
    }

}

void TinyBitmap::DrawLine(int x1, int y1, int x2, int y2)
{
    float xdiff_abs = abs(x2 - x1);
    float ydiff_abs = abs(y2 - y1);

    float steps;
    if (xdiff_abs >= ydiff_abs) steps = xdiff_abs;
    else steps = ydiff_abs;

    for (float i = 0; i <= (int)steps; i++) 
    {
        float corrector = 0;
        if (i == 0 && steps == 0) {
            corrector = 1;
        }
        //X-Values:
        float pX = x1 + ((x2 - x1) / (steps + corrector) * i);
        //Y-Values:
        float pY = y1 + ((y2 - y1) / (steps + corrector) * i);
        DrawPixel((int)pX, (int)pY);
    }
}

void TinyBitmap::DrawCircle(int x, int y, int radius)
{
    if(radius < 1) radius = 1;

    for (float rad = 0; rad < M_PI * 2 ; rad += (float)(5 / (2 * M_PI * radius))) 
    {
        DrawPixel(x + (int)(radius * cos(rad)), y + (int)(radius * sin(rad)));
    }
}

void TinyBitmap::DrawRectangle(int x1, int y1, int x2, int y2)
{
    DrawLine(x1, y1, x1, y2);
    DrawLine(x1, y1, x2, y1);
    DrawLine(x2, y1, x2, y2);
    DrawLine(x2, y2, x1, y2);
}

void TinyBitmap::DrawLineDirection(int x, int y, int degree, int lenght)
{
    float rad = degree * (float)M_PI / 180;
    for (int radius = 0; radius <= lenght; radius++) 
    {
        DrawPixel(x + (int)(radius * cos(rad)), y + (int)(radius * sin(rad)));
    }
}


//Textrendering
void TinyBitmap::DrawText(int x, int y, char *CharArray, bool UseLargeFont) //removed: string text
{

    const char Letter_A[] = { 0x41, 0x05, 0x0E, 0x11, 0x11, 0x11, 0x1F, 0x11, 0x11, 0x00 };
    const char Letter_B[] = { 0x42, 0x05, 0x0F, 0x11, 0x11, 0x0F, 0x11, 0x11, 0x0F, 0x00 };
    const char Letter_C[] = { 0x43, 0x05, 0x0E, 0x11, 0x01, 0x01, 0x01, 0x11, 0x0E, 0x00 };
    const char Letter_D[] = { 0x44, 0x05, 0x07, 0x09, 0x11, 0x11, 0x11, 0x09, 0x07, 0x00 };
    const char Letter_E[] = { 0x45, 0x05, 0x1F, 0x01, 0x01, 0x0F, 0x01, 0x01, 0x1F, 0x00 };
    const char Letter_F[] = { 0x46, 0x05, 0x1F, 0x01, 0x01, 0x0F, 0x01, 0x01, 0x01, 0x00 };
    const char Letter_G[] = { 0x47, 0x05, 0x0E, 0x11, 0x01, 0x1D, 0x11, 0x11, 0x1E, 0x00 };
    const char Letter_H[] = { 0x48, 0x05, 0x11, 0x11, 0x11, 0x1F, 0x11, 0x11, 0x11, 0x00 };
    const char Letter_I[] = { 0x49, 0x05, 0x0E, 0x04, 0x04, 0x04, 0x04, 0x04, 0x0E, 0x00 };
    const char Letter_J[] = { 0x4A, 0x05, 0x1C, 0x08, 0x08, 0x08, 0x08, 0x09, 0x06, 0x00 };
    const char Letter_K[] = { 0x4B, 0x05, 0x11, 0x09, 0x05, 0x03, 0x05, 0x09, 0x11, 0x00 };
    const char Letter_L[] = { 0x4C, 0x05, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x1F, 0x00 };
    const char Letter_M[] = { 0x4D, 0x05, 0x11, 0x1B, 0x15, 0x15, 0x11, 0x11, 0x11, 0x00 };
    const char Letter_N[] = { 0x4E, 0x05, 0x11, 0x11, 0x13, 0x15, 0x19, 0x11, 0x11, 0x00 };
    const char Letter_O[] = { 0x4F, 0x05, 0x0E, 0x11, 0x11, 0x11, 0x11, 0x11, 0x0E, 0x00 };
    const char Letter_P[] = { 0x50, 0x05, 0x0F, 0x11, 0x11, 0x0F, 0x01, 0x01, 0x01, 0x00 };
    const char Letter_Q[] = { 0x51, 0x05, 0x0E, 0x11, 0x11, 0x11, 0x15, 0x09, 0x16, 0x00 };
    const char Letter_R[] = { 0x52, 0x05, 0x0F, 0x11, 0x11, 0x0F, 0x05, 0x09, 0x11, 0x00 };
    const char Letter_S[] = { 0x53, 0x05, 0x1E, 0x01, 0x01, 0x0E, 0x10, 0x10, 0x0F, 0x00 };
    const char Letter_T[] = { 0x54, 0x05, 0x1F, 0x04, 0x04, 0x04, 0x04, 0x04, 0x04, 0x00 };
    const char Letter_U[] = { 0x55, 0x05, 0x11, 0x11, 0x11, 0x11, 0x11, 0x11, 0x0E, 0x00 };
    const char Letter_V[] = { 0x56, 0x05, 0x11, 0x11, 0x11, 0x11, 0x11, 0x0A, 0x04, 0x00 };
    const char Letter_W[] = { 0x57, 0x05, 0x11, 0x11, 0x11, 0x15, 0x15, 0x15, 0x0A, 0x00 };
    const char Letter_X[] = { 0x58, 0x05, 0x11, 0x11, 0x0A, 0x04, 0x0A, 0x11, 0x11, 0x00 };
    const char Letter_Y[] = { 0x59, 0x05, 0x11, 0x11, 0x0A, 0x04, 0x04, 0x04, 0x04, 0x00 };
    const char Letter_Z[] = { 0x5A, 0x05, 0x1F, 0x10, 0x08, 0x04, 0x02, 0x01, 0x1F, 0x00 };

    const char Letter_a[] = { 0x61, 0x05, 0x00, 0x00, 0x0E, 0x10, 0x1E, 0x11, 0x1E, 0x00 };
    const char Letter_b[] = { 0x62, 0x05, 0x01, 0x01, 0x01, 0x0F, 0x11, 0x11, 0x0F, 0x00 };
    const char Letter_c[] = { 0x63, 0x05, 0x00, 0x00, 0x1E, 0x01, 0x01, 0x01, 0x1E, 0x00 };
    const char Letter_d[] = { 0x64, 0x05, 0x10, 0x10, 0x10, 0x1E, 0x11, 0x11, 0x1E, 0x00 };
    const char Letter_e[] = { 0x65, 0x05, 0x00, 0x00, 0x0E, 0x11, 0x1F, 0x01, 0x1E, 0x00 };
    const char Letter_f[] = { 0x66, 0x05, 0x08, 0x14, 0x04, 0x0E, 0x04, 0x04, 0x04, 0x00 };
    const char Letter_g[] = { 0x67, 0x05, 0x00, 0x00, 0x1E, 0x11, 0x1E, 0x10, 0x0F, 0x00 };
    const char Letter_h[] = { 0x68, 0x05, 0x01, 0x01, 0x01, 0x0F, 0x11, 0x11, 0x11, 0x00 };
    const char Letter_i[] = { 0x69, 0x05, 0x00, 0x04, 0x00, 0x06, 0x04, 0x04, 0x0E, 0x00 };
    const char Letter_j[] = { 0x6A, 0x05, 0x08, 0x00, 0x08, 0x08, 0x08, 0x09, 0x06, 0x00 };
    const char Letter_k[] = { 0x6B, 0x05, 0x02, 0x02, 0x12, 0x0A, 0x06, 0x0A, 0x12, 0x00 };
    const char Letter_l[] = { 0x6C, 0x05, 0x06, 0x04, 0x04, 0x04, 0x04, 0x04, 0x0E, 0x00 };
    const char Letter_m[] = { 0x6D, 0x05, 0x00, 0x00, 0x1B, 0x15, 0x15, 0x11, 0x11, 0x00 };
    const char Letter_n[] = { 0x6E, 0x05, 0x00, 0x00, 0x0D, 0x13, 0x11, 0x11, 0x11, 0x00 };
    const char Letter_o[] = { 0x6F, 0x05, 0x00, 0x00, 0x0E, 0x11, 0x11, 0x11, 0x0E, 0x00 };
    const char Letter_p[] = { 0x70, 0x05, 0x00, 0x00, 0x0F, 0x11, 0x0F, 0x01, 0x01, 0x00 };
    const char Letter_q[] = { 0x71, 0x05, 0x00, 0x00, 0x1E, 0x11, 0x1E, 0x10, 0x10, 0x00 };
    const char Letter_r[] = { 0x72, 0x05, 0x00, 0x00, 0x0D, 0x13, 0x01, 0x01, 0x01, 0x00 };
    const char Letter_s[] = { 0x73, 0x05, 0x00, 0x00, 0x1E, 0x01, 0x0E, 0x10, 0x0F, 0x00 };
    const char Letter_t[] = { 0x74, 0x05, 0x04, 0x04, 0x1F, 0x04, 0x04, 0x14, 0x08, 0x00 };
    const char Letter_u[] = { 0x75, 0x05, 0x00, 0x00, 0x11, 0x11, 0x11, 0x11, 0x0E, 0x00 };
    const char Letter_v[] = { 0x76, 0x05, 0x00, 0x00, 0x11, 0x11, 0x11, 0x0A, 0x04, 0x00 };
    const char Letter_w[] = { 0x77, 0x05, 0x00, 0x00, 0x11, 0x11, 0x15, 0x15, 0x0A, 0x00 };
    const char Letter_x[] = { 0x78, 0x05, 0x00, 0x00, 0x11, 0x0A, 0x04, 0x0A, 0x11, 0x00 };
    const char Letter_y[] = { 0x79, 0x05, 0x00, 0x00, 0x11, 0x0A, 0x04, 0x04, 0x02, 0x00 };
    const char Letter_z[] = { 0x7A, 0x05, 0x00, 0x00, 0x1F, 0x08, 0x04, 0x02, 0x1F, 0x00 };

    const char Letter_0[] = { 0x30, 0x05, 0x0E, 0x11, 0x19, 0x15, 0x13, 0x11, 0x0E, 0x00 };
    const char Letter_1[] = { 0x31, 0x05, 0x04, 0x06, 0x04, 0x04, 0x04, 0x04, 0x0E, 0x00 };
    const char Letter_2[] = { 0x32, 0x05, 0x0E, 0x11, 0x10, 0x08, 0x04, 0x02, 0x1F, 0x00 };
    const char Letter_3[] = { 0x33, 0x05, 0x1F, 0x08, 0x04, 0x08, 0x10, 0x11, 0x0E, 0x00 };
    const char Letter_4[] = { 0x34, 0x05, 0x08, 0x0C, 0x0A, 0x09, 0x1F, 0x08, 0x08, 0x00 };
    const char Letter_5[] = { 0x35, 0x05, 0x1F, 0x01, 0x0F, 0x10, 0x10, 0x11, 0x0E, 0x00 };
    const char Letter_6[] = { 0x36, 0x05, 0x0C, 0x02, 0x01, 0x0F, 0x11, 0x11, 0x0E, 0x00 };
    const char Letter_7[] = { 0x37, 0x05, 0x1F, 0x10, 0x08, 0x04, 0x02, 0x02, 0x02, 0x00 };
    const char Letter_8[] = { 0x38, 0x05, 0x0E, 0x11, 0x11, 0x0E, 0x11, 0x11, 0x0E, 0x00 };
    const char Letter_9[] = { 0x39, 0x05, 0x0E, 0x11, 0x11, 0x1E, 0x10, 0x08, 0x06, 0x00 };

    const char Letter_CH21[] = { 0x21, 0x05, 0x04, 0x04, 0x04, 0x04, 0x00, 0x00, 0x04, 0x00 };
    const char Letter_CH22[] = { 0x22, 0x05, 0x0A, 0x0A, 0x0A, 0x00, 0x00, 0x00, 0x00, 0x00 };
    const char Letter_CH23[] = { 0x23, 0x05, 0x0A, 0x0A, 0x1F, 0x0A, 0x1F, 0x0A, 0x0A, 0x00 };
    const char Letter_CH24[] = { 0x24, 0x05, 0x04, 0x1E, 0x05, 0x0E, 0x14, 0x0F, 0x04, 0x00 };
    const char Letter_CH25[] = { 0x25, 0x05, 0x03, 0x13, 0x08, 0x04, 0x02, 0x19, 0x18, 0x00 };
    const char Letter_CH26[] = { 0x26, 0x05, 0x06, 0x09, 0x05, 0x02, 0x15, 0x09, 0x16, 0x00 };
    const char Letter_CH27[] = { 0x27, 0x05, 0x06, 0x04, 0x02, 0x00, 0x00, 0x00, 0x00, 0x00 };
    const char Letter_CH28[] = { 0x28, 0x05, 0x08, 0x04, 0x02, 0x02, 0x02, 0x04, 0x08, 0x00 };
    const char Letter_CH29[] = { 0x29, 0x05, 0x02, 0x04, 0x08, 0x08, 0x08, 0x04, 0x02, 0x00 };
    const char Letter_CH2A[] = { 0x2A, 0x05, 0x00, 0x04, 0x15, 0x0E, 0x15, 0x04, 0x00, 0x00 };
    const char Letter_CH2B[] = { 0x2B, 0x05, 0x00, 0x04, 0x04, 0x1F, 0x04, 0x04, 0x00, 0x00 };
    const char Letter_CH2C[] = { 0x2C, 0x05, 0x00, 0x00, 0x00, 0x00, 0x06, 0x04, 0x02, 0x00 };
    const char Letter_CH2D[] = { 0x2D, 0x05, 0x00, 0x00, 0x00, 0x1F, 0x00, 0x00, 0x00, 0x00 };
    const char Letter_CH2E[] = { 0x2E, 0x05, 0x00, 0x00, 0x00, 0x00, 0x00, 0x06, 0x06, 0x00 };
    const char Letter_CH2F[] = { 0x2F, 0x05, 0x00, 0x10, 0x08, 0x04, 0x02, 0x01, 0x00, 0x00 };

    const char Letter_CH3A[] = { 0x3A, 0x05, 0x00, 0x06, 0x06, 0x00, 0x06, 0x06, 0x00, 0x00 };
    const char Letter_CH3B[] = { 0x3B, 0x05, 0x00, 0x06, 0x06, 0x00, 0x06, 0x04, 0x02, 0x00 };
    const char Letter_CH3C[] = { 0x3C, 0x05, 0x08, 0x04, 0x02, 0x01, 0x02, 0x04, 0x08, 0x00 };
    const char Letter_CH3D[] = { 0x3D, 0x05, 0x00, 0x00, 0x1F, 0x00, 0x1F, 0x00, 0x00, 0x00 };
    const char Letter_CH3E[] = { 0x3E, 0x05, 0x02, 0x04, 0x08, 0x10, 0x08, 0x04, 0x02, 0x00 };
    const char Letter_CH3F[] = { 0x3F, 0x05, 0x0E, 0x11, 0x10, 0x08, 0x04, 0x00, 0x04, 0x00 };
    const char Letter_CH40[] = { 0x40, 0x05, 0x0E, 0x11, 0x10, 0x16, 0x15, 0x15, 0x0E, 0x00 };

    const char unArray[] = { 0x00, 0x05, 0x00, 0x00, 0x0A, 0x04, 0x0A, 0x00, 0x00, 0x00 };

    const char Letter_Space[] = { 0x20, 0x05, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00 };


    //char CharArray[text.size()];
    //strncpy(CharArray, text.c_str(), sizeof(CharArray));
    //CharArray[sizeof(CharArray) - 1] = 0;

    int xOffset = 0;

    for (int i = 0; i < 255; i++) {
        char ArrayToUse[10] = { 0 };
        char cha = CharArray[i];
        int LetterHeigth = 8;
        int LetterWidth;

        switch (cha) { //Select char-pattern
            case 'A':
                for(int i = 0; i < 10; i++) {
                    ArrayToUse[i] = Letter_A[i];
                }
                break;
            case 'B':
                for(int i = 0; i < 10; i++) {
                    ArrayToUse[i] = Letter_B[i];
                }
                break;
            case 'C':
                for(int i = 0; i < 10; i++) {
                    ArrayToUse[i] = Letter_C[i];
                }
                break;
            case 'D':
                for(int i = 0; i < 10; i++) {
                    ArrayToUse[i] = Letter_D[i];
                }
                break;
            case 'E':
                for(int i = 0; i < 10; i++) {
                    ArrayToUse[i] = Letter_E[i];
                }
                break;
            case 'F':
                for(int i = 0; i < 10; i++) {
                    ArrayToUse[i] = Letter_F[i];
                }
                break;
            case 'G':
                for(int i = 0; i < 10; i++) {
                    ArrayToUse[i] = Letter_G[i];
                }
                break;
            case 'H':
                for(int i = 0; i < 10; i++) {
                    ArrayToUse[i] = Letter_H[i];
                }
                break;
            case 'I':
                for(int i = 0; i < 10; i++) {
                    ArrayToUse[i] = Letter_I[i];
                }
                break;
            case 'J':
                for(int i = 0; i < 10; i++) {
                    ArrayToUse[i] = Letter_J[i];
                }
                break;
            case 'K':
                for(int i = 0; i < 10; i++) {
                    ArrayToUse[i] = Letter_K[i];
                }
                break;
            case 'L':
                for(int i = 0; i < 10; i++) {
                    ArrayToUse[i] = Letter_L[i];
                }
                break;
            case 'M':
                for(int i = 0; i < 10; i++) {
                    ArrayToUse[i] = Letter_M[i];
                }
                break;
            case 'N':
                for(int i = 0; i < 10; i++) {
                    ArrayToUse[i] = Letter_N[i];
                }
                break;
            case 'O':
                for(int i = 0; i < 10; i++) {
                    ArrayToUse[i] = Letter_O[i];
                }
                break;
            case 'P':
                for(int i = 0; i < 10; i++) {
                    ArrayToUse[i] = Letter_P[i];
                }
                break;
            case 'Q':
                for(int i = 0; i < 10; i++) {
                    ArrayToUse[i] = Letter_Q[i];
                }
                break;
            case 'R':
                for(int i = 0; i < 10; i++) {
                    ArrayToUse[i] = Letter_R[i];
                }
                break;
            case 'S':
                for(int i = 0; i < 10; i++) {
                    ArrayToUse[i] = Letter_S[i];
                }
                break;
            case 'T':
                for(int i = 0; i < 10; i++) {
                    ArrayToUse[i] = Letter_T[i];
                }
                break;
            case 'U':
                for(int i = 0; i < 10; i++) {
                    ArrayToUse[i] = Letter_U[i];
                }
                break;
            case 'V':
                for(int i = 0; i < 10; i++) {
                    ArrayToUse[i] = Letter_V[i];
                }
                break;
            case 'W':
                for(int i = 0; i < 10; i++) {
                    ArrayToUse[i] = Letter_W[i];
                }
                break;
            case 'X':
                for(int i = 0; i < 10; i++) {
                    ArrayToUse[i] = Letter_X[i];
                }
                break;
            case 'Y':
                for(int i = 0; i < 10; i++) {
                    ArrayToUse[i] = Letter_Y[i];
                }
                break;
            case 'Z':
                for(int i = 0; i < 10; i++) {
                    ArrayToUse[i] = Letter_Z[i];
                }
                break;

            case 'a':
                for(int i = 0; i < 10; i++) {
                    ArrayToUse[i] = Letter_a[i];
                }
                break;
            case 'b':
                for(int i = 0; i < 10; i++) {
                    ArrayToUse[i] = Letter_b[i];
                }
                break;
            case 'c':
                for(int i = 0; i < 10; i++) {
                    ArrayToUse[i] = Letter_c[i];
                }
                break;
            case 'd':
                for(int i = 0; i < 10; i++) {
                    ArrayToUse[i] = Letter_d[i];
                }
                break;
            case 'e':
                for(int i = 0; i < 10; i++) {
                    ArrayToUse[i] = Letter_e[i];
                }
                break;
            case 'f':
                for(int i = 0; i < 10; i++) {
                    ArrayToUse[i] = Letter_f[i];
                }
                break;
            case 'g':
                for(int i = 0; i < 10; i++) {
                    ArrayToUse[i] = Letter_g[i];
                }
                break;
            case 'h':
                for(int i = 0; i < 10; i++) {
                    ArrayToUse[i] = Letter_h[i];
                }
                break;
            case 'i':
                for(int i = 0; i < 10; i++) {
                    ArrayToUse[i] = Letter_i[i];
                }
                break;
            case 'j':
                for(int i = 0; i < 10; i++) {
                    ArrayToUse[i] = Letter_j[i];
                }
                break;
            case 'k':
                for(int i = 0; i < 10; i++) {
                    ArrayToUse[i] = Letter_k[i];
                }
                break;
            case 'l':
                for(int i = 0; i < 10; i++) {
                    ArrayToUse[i] = Letter_l[i];
                }
                break;
            case 'm':
                for(int i = 0; i < 10; i++) {
                    ArrayToUse[i] = Letter_m[i];
                }
                break;
            case 'n':
                for(int i = 0; i < 10; i++) {
                    ArrayToUse[i] = Letter_n[i];
                }
                break;
            case 'o':
                for(int i = 0; i < 10; i++) {
                    ArrayToUse[i] = Letter_o[i];
                }
                break;
            case 'p':
                for(int i = 0; i < 10; i++) {
                    ArrayToUse[i] = Letter_p[i];
                }
                break;
            case 'q':
                for(int i = 0; i < 10; i++) {
                    ArrayToUse[i] = Letter_q[i];
                }
                break;
            case 'r':
                for(int i = 0; i < 10; i++) {
                    ArrayToUse[i] = Letter_r[i];
                }
                break;
            case 's':
                for(int i = 0; i < 10; i++) {
                    ArrayToUse[i] = Letter_s[i];
                }
                break;
            case 't':
                for(int i = 0; i < 10; i++) {
                    ArrayToUse[i] = Letter_t[i];
                }
                break;
            case 'u':
                for(int i = 0; i < 10; i++) {
                    ArrayToUse[i] = Letter_u[i];
                }
                break;
            case 'v':
                for(int i = 0; i < 10; i++) {
                    ArrayToUse[i] = Letter_v[i];
                }
                break;
            case 'w':
                for(int i = 0; i < 10; i++) {
                    ArrayToUse[i] = Letter_w[i];
                }
                break;
            case 'x':
                for(int i = 0; i < 10; i++) {
                    ArrayToUse[i] = Letter_x[i];
                }
                break;
            case 'y':
                for(int i = 0; i < 10; i++) {
                    ArrayToUse[i] = Letter_y[i];
                }
                break;
            case 'z':
                for(int i = 0; i < 10; i++) {
                    ArrayToUse[i] = Letter_z[i];
                }
                break;

            case '0':
                for(int i = 0; i < 10; i++) {
                    ArrayToUse[i] = Letter_0[i];
                }
                break;
            case '1':
                for(int i = 0; i < 10; i++) {
                    ArrayToUse[i] = Letter_1[i];
                }
                break;
            case '2':
                for(int i = 0; i < 10; i++) {
                    ArrayToUse[i] = Letter_2[i];
                }
                break;
            case '3':
                for(int i = 0; i < 10; i++) {
                    ArrayToUse[i] = Letter_3[i];
                }
                break;
            case '4':
                for(int i = 0; i < 10; i++) {
                    ArrayToUse[i] = Letter_4[i];
                }
                break;
            case '5':
                for(int i = 0; i < 10; i++) {
                    ArrayToUse[i] = Letter_5[i];
                }
                break;
            case '6':
                for(int i = 0; i < 10; i++) {
                    ArrayToUse[i] = Letter_6[i];
                }
                break;
            case '7':
                for(int i = 0; i < 10; i++) {
                    ArrayToUse[i] = Letter_7[i];
                }
                break;
            case '8':
                for(int i = 0; i < 10; i++) {
                    ArrayToUse[i] = Letter_8[i];
                }
                break;
            case '9':
                for(int i = 0; i < 10; i++) {
                    ArrayToUse[i] = Letter_9[i];
                }
                break;

            case '!':
                for(int i = 0; i < 10; i++) {
                    ArrayToUse[i] = Letter_CH21[i];
                }
                break;
            case '"':
                for(int i = 0; i < 10; i++) {
                    ArrayToUse[i] = Letter_CH22[i];
                }
                break;
            case '#':
                for(int i = 0; i < 10; i++) {
                    ArrayToUse[i] = Letter_CH23[i];
                }
                break;
            case '$':
                for(int i = 0; i < 10; i++) {
                    ArrayToUse[i] = Letter_CH24[i];
                }
                break;
            case '%':
                for(int i = 0; i < 10; i++) {
                    ArrayToUse[i] = Letter_CH25[i];
                }
                break;
            case '&':
                for(int i = 0; i < 10; i++) {
                    ArrayToUse[i] = Letter_CH26[i];
                }
                break;
            case '\'':
                for(int i = 0; i < 10; i++) {
                    ArrayToUse[i] = Letter_CH27[i];
                }
                break;
            case '(':
                for(int i = 0; i < 10; i++) {
                    ArrayToUse[i] = Letter_CH28[i];
                }
                break;
            case ')':
                for(int i = 0; i < 10; i++) {
                    ArrayToUse[i] = Letter_CH29[i];
                }
                break;
            case '*':
                for(int i = 0; i < 10; i++) {
                    ArrayToUse[i] = Letter_CH2A[i];
                }
                break;
            case '+':
                for(int i = 0; i < 10; i++) {
                    ArrayToUse[i] = Letter_CH2B[i];
                }
                break;
            case ',':
                for(int i = 0; i < 10; i++) {
                    ArrayToUse[i] = Letter_CH2C[i];
                }
                break;
            case '-':
                for(int i = 0; i < 10; i++) {
                    ArrayToUse[i] = Letter_CH2D[i];
                }
                break;
            case '.':
                for(int i = 0; i < 10; i++) {
                    ArrayToUse[i] = Letter_CH2E[i];
                }
                break;
            case '/':
                for(int i = 0; i < 10; i++) {
                    ArrayToUse[i] = Letter_CH2F[i];
                }
                break;

            case ':':
                for(int i = 0; i < 10; i++) {
                    ArrayToUse[i] = Letter_CH3A[i];
                }
                break;
            case ';':
                for(int i = 0; i < 10; i++) {
                    ArrayToUse[i] = Letter_CH3B[i];
                }
                break;
            case '<':
                for(int i = 0; i < 10; i++) {
                    ArrayToUse[i] = Letter_CH3C[i];
                }
                break;
            case '=':
                for(int i = 0; i < 10; i++) {
                    ArrayToUse[i] = Letter_CH3D[i];
                }
                break;
            case '>':
                for(int i = 0; i < 10; i++) {
                    ArrayToUse[i] = Letter_CH3E[i];
                }
                break;
            case '?':
                for(int i = 0; i < 10; i++) {
                    ArrayToUse[i] = Letter_CH3F[i];
                }
                break;
            case '@':
                for(int i = 0; i < 10; i++) {
                    ArrayToUse[i] = Letter_CH40[i];
                }
                break;

            case ' ':
                for(int i = 0; i < 10; i++) {
                    ArrayToUse[i] = Letter_Space[i];
                }
                break;

            case '\0': //if the end of string char is found, end function
                return;


            default:
                for(int i = 0; i < 10; i++) {
                    ArrayToUse[i] = unArray[i];
                }
                break;
        }
        //              ASCII Width 1stR  2ndR  3rdR  4thR  5thR  6thR  7thR  8thR
        // Letter_A = { 0x41, 0x05, 0x0E, 0x11, 0x11, 0x11, 0x1F, 0x11, 0x11, 0x00 }
        LetterWidth = ArrayToUse[1];

        if (UseLargeFont) {
            for (int LetterRow = 0; LetterRow < sizeof ArrayToUse - 2; LetterRow++) {
                if (((ArrayToUse[LetterRow + 2] & Bit0) == Bit0) && LetterWidth > 0) {
                    DrawPixel(x + xOffset + 0, y + (LetterRow * 2) + 1);
                    DrawPixel(x + xOffset + 1, y + (LetterRow * 2) + 1);
                    DrawPixel(x + xOffset + 0, y + (LetterRow * 2) + 0);
                    DrawPixel(x + xOffset + 1, y + (LetterRow * 2) + 0);
                }
                if (((ArrayToUse[LetterRow + 2] & Bit1) == Bit1) && LetterWidth > 1) {
                    DrawPixel(x + xOffset + 2, y + (LetterRow * 2) + 1);
                    DrawPixel(x + xOffset + 3, y + (LetterRow * 2) + 1);
                    DrawPixel(x + xOffset + 2, y + (LetterRow * 2) + 0);
                    DrawPixel(x + xOffset + 3, y + (LetterRow * 2) + 0);
                }
                if (((ArrayToUse[LetterRow + 2] & Bit2) == Bit2) && LetterWidth > 2) {
                    DrawPixel(x + xOffset + 4, y + (LetterRow * 2) + 1);
                    DrawPixel(x + xOffset + 5, y + (LetterRow * 2) + 1);
                    DrawPixel(x + xOffset + 4, y + (LetterRow * 2) + 0);
                    DrawPixel(x + xOffset + 5, y + (LetterRow * 2) + 0);
                }
                if (((ArrayToUse[LetterRow + 2] & Bit3) == Bit3) && LetterWidth > 3) {
                    DrawPixel(x + xOffset + 6, y + (LetterRow * 2) + 1);
                    DrawPixel(x + xOffset + 7, y + (LetterRow * 2) + 1);
                    DrawPixel(x + xOffset + 6, y + (LetterRow * 2) + 0);
                    DrawPixel(x + xOffset + 7, y + (LetterRow * 2) + 0);
                }
                if (((ArrayToUse[LetterRow + 2] & Bit4) == Bit4) && LetterWidth > 4) {
                    DrawPixel(x + xOffset + 8, y + (LetterRow * 2) + 1);
                    DrawPixel(x + xOffset + 9, y + (LetterRow * 2) + 1);
                    DrawPixel(x + xOffset + 8, y + (LetterRow * 2) + 0);
                    DrawPixel(x + xOffset + 9, y + (LetterRow * 2) + 0);
                }
                if (((ArrayToUse[LetterRow + 2] & Bit5) == Bit5) && LetterWidth > 5) {
                    DrawPixel(x + xOffset + 10, y + (LetterRow * 2) + 1);
                    DrawPixel(x + xOffset + 11, y + (LetterRow * 2) + 1);
                    DrawPixel(x + xOffset + 10, y + (LetterRow * 2) + 0);
                    DrawPixel(x + xOffset + 11, y + (LetterRow * 2) + 0);
                }
                if (((ArrayToUse[LetterRow + 2] & Bit6) == Bit6) && LetterWidth > 6) {
                    DrawPixel(x + xOffset + 12, y + (LetterRow * 2) + 1);
                    DrawPixel(x + xOffset + 13, y + (LetterRow * 2) + 1);
                    DrawPixel(x + xOffset + 12, y + (LetterRow * 2) + 0);
                    DrawPixel(x + xOffset + 13, y + (LetterRow * 2) + 0);
                }
                if (((ArrayToUse[LetterRow + 2] & Bit7) == Bit7) && LetterWidth > 7) {
                    DrawPixel(x + xOffset + 14, y + (LetterRow * 2) + 1);
                    DrawPixel(x + xOffset + 15, y + (LetterRow * 2) + 1);
                    DrawPixel(x + xOffset + 14, y + (LetterRow * 2) + 0);
                    DrawPixel(x + xOffset + 15, y + (LetterRow * 2) + 0);
                }
            }

            xOffset += (LetterWidth * 2) + 1;
        }

        else {
            for (int LetterRow = 2; LetterRow < sizeof ArrayToUse; LetterRow++) {
                if (((ArrayToUse[LetterRow] & Bit0) == Bit0) && LetterWidth > 0)
                    DrawPixel(x + xOffset + 0, y + LetterRow - 2);
                if (((ArrayToUse[LetterRow] & Bit1) == Bit1) && LetterWidth > 1)
                    DrawPixel(x + xOffset + 1, y + LetterRow - 2);
                if (((ArrayToUse[LetterRow] & Bit2) == Bit2) && LetterWidth > 2)
                    DrawPixel(x + xOffset + 2, y + LetterRow - 2);
                if (((ArrayToUse[LetterRow] & Bit3) == Bit3) && LetterWidth > 3)
                    DrawPixel(x + xOffset + 3, y + LetterRow - 2);
                if (((ArrayToUse[LetterRow] & Bit4) == Bit4) && LetterWidth > 4)
                    DrawPixel(x + xOffset + 4, y + LetterRow - 2);
                if (((ArrayToUse[LetterRow] & Bit5) == Bit5) && LetterWidth > 5)
                    DrawPixel(x + xOffset + 5, y + LetterRow - 2);
                if (((ArrayToUse[LetterRow] & Bit6) == Bit6) && LetterWidth > 6)
                    DrawPixel(x + xOffset + 6, y + LetterRow - 2);
                if (((ArrayToUse[LetterRow] & Bit7) == Bit7) && LetterWidth > 7)
                    DrawPixel(x + xOffset + 7, y + LetterRow - 2);
            }

            xOffset += LetterWidth + 1;
        }
    }

}

void TinyBitmap::ClearScreen()
{
    int size = (_IMAGEWIDTH * _IMAGEHEIGHT / 8) + _COMMANDBYTES;

    for (int i = _COMMANDBYTES; i < size; i++) {
        _FRAMEBUFFER[i] = 0x00;
    }
}

