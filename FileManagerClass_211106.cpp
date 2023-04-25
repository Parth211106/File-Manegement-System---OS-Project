#include <iostream>
#include <cstring>
#include <windows.h>

using namespace std;

// Please make sure to update the 'FILE_PATH' constant in the code with the appropriate file path on your system before running the program.
const string FILE_PATH = "C:\\Users\\ipart\\OneDrive\\Desktop\\";

class FileManager {
public:
    bool createFile(const char* fileName) {

        // Construct the full file path
        string filePath = FILE_PATH + string(fileName);

        // Create a file using Windows API function
        HANDLE fileHandle = CreateFile(filePath.c_str(), GENERIC_WRITE, 0, NULL, CREATE_NEW, FILE_ATTRIBUTE_NORMAL, NULL);
        if (fileHandle == INVALID_HANDLE_VALUE) {
            cout << "Failed to create file: " << fileName << endl;
            return false;
        }

        CloseHandle(fileHandle);
        cout << "File created successfully: " << fileName << endl;
        return true;
    }

    bool readFile(const char* fileName, char* buffer, int bufferSize) {

        // Construct the full file path
        string filePath = FILE_PATH + string(fileName);

        // Read from file using Windows API function
        HANDLE fileHandle = CreateFile(filePath.c_str(), GENERIC_READ, 0, NULL, OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, NULL);
        if (fileHandle == INVALID_HANDLE_VALUE) {
            cout << "Failed to read file: " << fileName << endl;
            return false;
        }

        DWORD bytesRead;
        if (!ReadFile(fileHandle, buffer, bufferSize, &bytesRead, NULL)) {
            cout << "Failed to read file: " << fileName << endl;
            CloseHandle(fileHandle);
            return false;
        }

        CloseHandle(fileHandle);
        cout << "Read " << bytesRead << " bytes from file: " << fileName << endl;
        return true;
    }

    bool editFile(const char* fileName, const char* newData, int newSize) {

        // Construct the full file path
        string filePath = FILE_PATH + string(fileName);

        // Edit file using Windows API function
        HANDLE fileHandle = CreateFile(filePath.c_str(), GENERIC_WRITE, 0, NULL, OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, NULL);
        if (fileHandle == INVALID_HANDLE_VALUE) {
            cout << "Failed to edit file: " << fileName << endl;
            return false;
        }

        DWORD bytesWritten;
        if (!WriteFile(fileHandle, newData, newSize, &bytesWritten, NULL)) {
            cout << "Failed to edit file: " << fileName << endl;
            CloseHandle(fileHandle);
            return false;
        }

        CloseHandle(fileHandle);
        cout << "Edited " << bytesWritten << " bytes in file: " << fileName << endl;
        return true;
    }

    bool deleteFile(const char* fileName) {

        // Construct the full file path
        string filePath = FILE_PATH + string(fileName);

        // Delete file using Windows API function
        if (!DeleteFile(filePath.c_str())) {
            cout << "Failed to delete file: " << fileName << endl;
            return false;
        }

        cout << "File deleted successfully: " << fileName << endl;
        return true;
    }

    bool writeFile(const char* fileName, const char* data, int dataSize) {

        // Construct the full file path
        string filePath = FILE_PATH + string(fileName);

        // Write to file using Windows API function
        HANDLE fileHandle = CreateFile(filePath.c_str(), GENERIC_WRITE, 0, NULL, CREATE_ALWAYS, FILE_ATTRIBUTE_NORMAL, NULL);
        if (fileHandle == INVALID_HANDLE_VALUE) {
            cout << "Failed to write to file: " << fileName << endl;
            return false;
        }

        DWORD bytesWritten;
        if (!WriteFile(fileHandle, data, dataSize, &bytesWritten, NULL)) {
            cout << "Failed to write to file: " << fileName << endl;
            CloseHandle(fileHandle);
            return false;
        }

        CloseHandle(fileHandle);
        cout << "Wrote " << bytesWritten << " bytes to file: " << fileName << endl;
        return true;
    }

    bool renameFile(const char* oldFileName, const char* newFileName) {

        // Construct the full file paths for old and new files
        string oldFilePath = FILE_PATH + string(oldFileName);
        string newFilePath = FILE_PATH + string(newFileName);

        // Rename file using Windows API function
        if (!MoveFile(oldFilePath.c_str(), newFilePath.c_str())) {
            cout << "Failed to rename file: " << oldFileName << " to " << newFileName << endl;
            return false;
        }

        cout << "Renamed file: " << oldFileName << " to " << newFileName << endl;
        return true;
    }

    bool findLocationOfFile(const char* fileName, string& filePath) {

        WIN32_FIND_DATAA fileData;
        HANDLE hFind;

        // Construct the search pattern with the file name
        string searchPattern = FILE_PATH + string(fileName);

        // Find the first file that matches the search pattern
        hFind = FindFirstFileA(searchPattern.c_str(), &fileData);
        if (hFind == INVALID_HANDLE_VALUE) {
            cout << "File not found: " << fileName << endl;
            return false;
        }

        // Extract the file path from the file data
        filePath = fileData.cFileName;

        // Close the file search handle
        FindClose(hFind);

        cout << "File found: " << fileName << " at location: " << filePath << endl;
        return true;
    }

    bool findSpaceTakenByFile(const char* fileName, unsigned long long& fileSize) {

        string filePath;
        if (!findLocationOfFile(fileName, filePath)) {
            return false;
        }

        // Construct the full file path
        string fullPath = FILE_PATH + filePath;

        // Get file size using GetFileSizeEx Windows API
        HANDLE hFile = CreateFileA(fullPath.c_str(), GENERIC_READ, FILE_SHARE_READ, NULL, OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, NULL);
        if (hFile == INVALID_HANDLE_VALUE) {
            cout << "Failed to get file size: " << fileName << endl;
            return false;
        }

        LARGE_INTEGER liFileSize;
        if (!GetFileSizeEx(hFile, &liFileSize)) {
            cout << "Failed to get file size: " << fileName << endl;
            CloseHandle(hFile);
            return false;
        }

        fileSize = liFileSize.QuadPart;
        CloseHandle(hFile);

        cout << "File size of " << fileName << ": " << fileSize << " bytes" << endl;
        return true;
    }

};

/*
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
}
*/
