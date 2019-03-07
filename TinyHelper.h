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


#ifndef TINYHELPER_H_
#define TINYHELPER_H_
//Helper-functions to convert an int to a displayable char[]

void IntToChar(char *CharBuffer, int Number); //Only works for positive numbers

void IntToChar(char *CharBuffer, int Number, char Digits); //Only works for positive numbers, adds leading 0s to numbers

void CombineChars(char *Destination, char *Source); //Combines two char[]

void FloatToChar(char *CharBuffer, float Number);

#endif