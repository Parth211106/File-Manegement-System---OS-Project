#include <iostream>
#include <cstring>
#include <windows.h>
#include <string>
#include <vector>
#include <dirent.h>
using namespace std;

class cDirectory{   // Abstract Base Class
public:
    virtual bool createFile(const char* fileName) = 0;
    virtual bool readFile(const char* fileName, char* buffer, int bufferSize) = 0;
    virtual bool editFile(const char* fileName, const char* newData, int newSize) = 0;
    virtual bool deleteFile(const char* fileName) = 0;
    virtual bool writeFile(const char* fileName, const char* data, int dataSize) = 0;
    virtual bool renameFile(const char* oldFileName, const char* newFileName) = 0;
    virtual bool findLocationOfFile(const char* fileName, string& filePath) = 0;
    virtual bool findSpaceTakenByFile(const char* fileName, unsigned long long& fileSize) = 0;

};
