#ifndef _MYSTRING
#define _MYSTRING
 
class mystring { 
  char* buffer; 
  int length;
  public: 
    void setbuffer(char* s) { buffer = s; length = strlen(s); } 
    char& operator[ ] (const int index) { return buffer[index]; }
    int size( ) { return length; }
 }; 
 
#endif