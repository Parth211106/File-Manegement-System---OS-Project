#include <iostream>
#include <cstring>
#include<windows.h>
#include "C:\Users\ipart\OneDrive\Desktop\B-Tech CSE\Semester 4\Operating System Lab\Project\FileManagerClass_211106.cpp"
using namespace std;

int main() {

    FileManager fileManager;

    // Test createFile()
    if (fileManager.createFile("test.txt")) {
        cout << "File created successfully!" << endl;
    }

    // Test writeFile()
    const char* data = "Hello, world!";
    int dataSize = strlen(data);
    if (fileManager.writeFile("test.txt", data, dataSize)) {
        cout << "Data written to file successfully!" << endl;
    }

    // Test readFile()
    char buffer[100];
    int bufferSize = sizeof(buffer);
    if (fileManager.readFile("test.txt", buffer, bufferSize)) {
        cout << "Data read from file: " << buffer << endl;
    }

    // Test editFile()
    const char* newData = "Hello Parth Sharma!";
    int newSize = strlen(newData);
    if (fileManager.editFile("test.txt", newData, newSize)) {
        cout << "Data edited in file successfully!" << endl;
    }

    /*
    // Test findLocationOfFile()
    string filePath;
    if (fileManager.findLocationOfFile("test.txt", filePath)) {
        cout << "File found at location: " << filePath << endl;
    }

    // Test findSpaceTakenByFile()
    unsigned long long fileSize;
    if (fileManager.findSpaceTakenByFile("test.txt", fileSize)) {
        cout << "File size: " << fileSize << " bytes" << endl;
    }

    // Test renameFile()
    if (fileManager.renameFile("test.txt", "test_renamed.txt")) {
        cout << "File renamed successfully!" << endl;
    }


    // Test deleteFile()
    if (fileManager.deleteFile("test_renamed.txt")) {
        cout << "File deleted successfully!" << endl;
    }
    */
    return 0;
}
