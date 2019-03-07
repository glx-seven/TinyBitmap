//Helper-functions to convert an int to a displayable char[]

void IntToChar(char *CharBuffer, int Number) //Only works for positive numbers
{
    
    char TempBuffer[32];
    char index = 0;
    
    do
    {
        char Rest = Number % 10;
        Number = Number / 10;
        
        TempBuffer[index] = Rest + 0x30;
        index++;
    }
    while (Number > 0);
    
    for (int i = 0; i < index; i++)
    {
        CharBuffer[i] = TempBuffer[index - i - 1];
    }
    CharBuffer[index] = '\0';
}


void IntToChar(char *CharBuffer, int Number, char Digits) //Only works for positive numbers, adds leading 0s to numbers
{
    
    char TempBuffer[32];
    char index = 0;
        
    do
    {
        char Rest = Number % 10;
        Number = Number / 10;
        
        TempBuffer[index] = Rest + 0x30;
        index++;
    }
    while (Number > 0);
    
    while (index < Digits)
    {
        TempBuffer[index + 1] = TempBuffer[index];
        TempBuffer[index] = 0x30;
        index++;
    }
    
    for (int i = 0; i < index; i++)
    {
        CharBuffer[i] = TempBuffer[index - i - 1];
    }
    
    CharBuffer[index] = '\0';
}

void CombineChars(char *Destination, char *Source) //Combines two char[]
{
    int ArrayIndex = 0;
    
    while(ArrayIndex < 255)
    {
        if(Destination[ArrayIndex] == '\0') break;
        ArrayIndex++;
    }
    
    for(int i = 0; i < 255; i++)
    {
        if(Source[i] == '\0') break;
        else Destination[ArrayIndex] = Source[i];
        ArrayIndex++;
    }
    
    Destination[ArrayIndex] = '\0';    
    
}

void FloatToChar(char *CharBuffer, float Number)
{
    float temp = Number * 1000;
    int whole = (int)temp / 1000;
    int fract = (int)temp % 1000;
    
    char f[8];
    
    IntToChar(CharBuffer, whole);
    IntToChar(f, fract);
    
    char dotchar[2] = { '.', '\0' };
    
    CombineChars(CharBuffer, dotchar);
    CombineChars(CharBuffer, f);
}