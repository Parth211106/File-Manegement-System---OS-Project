#include <iostream>
#include <cstring>
#include<windows.h>
#include<vector>
#include<dirent.h>

#include "cDirectory_BaseClass_211106.cpp"
#include "FileManagerClass_211106.cpp"
#include "DirectoryIndexingServices_211110.cpp"
/*
#include "C:\Users\ipart\OneDrive\Desktop\B-Tech CSE\Semester 4\Operating System Lab\Project\FileManagerClass_211106.cpp"
#include "C:\Users\ipart\OneDrive\Desktop\B-Tech CSE\Semester 4\Operating System Lab\Project\DirectoryIndexingServices_211110.cpp"
*/

using namespace std;

int main(){
    cDirectory *objDirectory ;        // Abstract Base Class Object
    FileManager fileManager ;
    cManager *managerObj = new cManager;
    objDirectory = &fileManager;

    while(true){
        cout << "File Manager : " << endl;
        cout << "1. Create File" << endl;
        cout << "2. Write File" << endl;
        cout << "3. Read File" << endl;
        cout << "4. Edit File" << endl;
        cout << "5. Location of File" << endl;
        cout << "6. Space taken by File(File Size)" << endl;
        cout << "7. Rename File" << endl;
        cout << "8. Delete File" << endl;
        cout << "9. Check whether file is present in Directory ? " << endl;
        cout << "10. To view all files in Directory " << endl;
        cout << "11. Exiting Program..." << endl << endl;

        int ichoice;
        cout << "Enter the File Operation you want Perform : " ;
        cin >> ichoice;
        cout << "\n" ;

        switch (ichoice){
            case 1:
                {
                    try {
                        if (objDirectory->createFile("test.txt")) {
                        cout << "File created successfully!" << endl;
                        }
                    }
                    catch (const exception& ex) {
                    cerr << "Error occurred: " << ex.what() << endl;
                    }
                    cout << "\n";
                    break;
                }

            case 2 :
                {
                    const char* data = "Hello, world!";
                    int dataSize = strlen(data);
                    try {
                        if (objDirectory->writeFile("test.txt", data, dataSize)) {
                        cout << "Data written to file successfully!" << endl;
                        }
                    }
                    catch (const exception& ex) {
                        cerr << "Error occurred: " << ex.what() << endl;
                    }
                    cout << "\n";
                    break;
                }

            case 3 :
                {
                    char buffer[100];
                    int bufferSize = sizeof(buffer);
                    try {
                        if (objDirectory->readFile("test.txt", buffer, bufferSize)) {
                            cout << "Data read from file: " << buffer << endl;
                        }
                    }
                    catch (const exception& ex) {
                        cerr << "Error occurred: " << ex.what() << endl;
                    }
                    cout << "\n";
                    break;
                }

             case 4 :
                {
                    const char* newData = "Hello Parth Sharma!";
                    int newSize = strlen(newData);
                    try {
                        if (objDirectory->editFile("test.txt", newData, newSize)) {
                            cout << "Data edited in file successfully!" << endl;
                        }
                    }
                    catch (const exception& ex) {
                        cerr << "Error occurred: " << ex.what() << endl;
                    }
                    cout << "\n";
                    break;
                }

            case 5 :
                {
                    string filePath;
                    try {
                        if (objDirectory->findLocationOfFile("test.txt", filePath)) {
                            cout << "File found at location: " << filePath << endl;
                        }
                    }
                    catch (const exception& ex) {
                        cerr << "Error occurred: " << ex.what() << endl;
                    }
                    cout << "\n";
                    break;
                }

            case 6 :
                {
                    unsigned long long fileSize;
                        try {
                            if (objDirectory->findSpaceTakenByFile("test.txt", fileSize)) {
                                cout << "File size: " << fileSize << " bytes" << endl;
                            }
                        }
                        catch (const exception& ex) {
                            cerr << "Error occurred: " << ex.what() << endl;
                        }
                        cout << "\n";
                        break;
                }

            case 7 :
                {
                    try {
                        if (objDirectory->renameFile("test.txt", "test_renamed.txt")) {
                            cout << "File renamed successfully!" << endl;
                        }
                    }
                    catch (const exception& ex) {
                        cerr << "Error occurred: " << ex.what() << endl;
                    }
                    cout << "\n";
                    break;
                }

            case 8 :
                {
                    try {
                        if (objDirectory->deleteFile("test_renamed.txt")) {
                            cout << "File deleted successfully!" << endl;
                        }
                    }
                    catch (const exception& ex) {
                        cerr << "Error occurred: " << ex.what() << endl;
                    }
                    cout << "\n";
                    break;
                }

            case 9:
                {
                    try {
                        managerObj->Indexing("C:\\Users\\ipart\\OneDrive\\Desktop\\");
                        // Search for a file
                        if (managerObj->Searchfile("test.txt")) {
                            cout << "File found!" << endl;
                        } else {
                            cout << "File not found." << endl;
                        }
                    }
                    catch(const char* msg) {
                        cerr << "Error: " << msg << endl;
                    }
                    cout << "\n";
                    break;
                }

            case 10 :
                {
                    // Print the file index
                    managerObj->Index();
                    cout << "\n";
                    break;
                }

            case 11 :
                {
                    cout << "Exiting program...\n";
                    cout << "\n";
                    return 0;
                }

            default :
                {
                    cout << "Invalid input, please try again.\n\n";
                    cout << "\n";
                }
        }
    }
}

    // Code without Exception Handling
    /*
        switch (ichoice){
            case 1:
            {
                if (objDirectory->createFile("test.txt")) {
                    cout << "File created successfully!" << endl;
                }
                cout << "\n";
                break;
            }

            case 2 :
            {
                const char* data = "Hello, world!";
                int dataSize = strlen(data);
                if (objDirectory->writeFile("test.txt", data, dataSize)) {
                    cout << "Data written to file successfully!" << endl;
                }
                cout << "\n";
                break;
            }

            case 3 :
            {
                char buffer[100];
                int bufferSize = sizeof(buffer);
                if (objDirectory->readFile("test.txt", buffer, bufferSize)) {
                    cout << "Data read from file: " << buffer << endl;
                }
                cout << "\n";
                break;
            }

            case 4 :
            {
                const char* newData = "Hello Parth Sharma!";
                int newSize = strlen(newData);
                if (objDirectory->editFile("test.txt", newData, newSize)) {
                    cout << "Data edited in file successfully!" << endl;
                }
                cout << "\n";
                break;
            }

            case 5 :{
                string filePath;
                if (objDirectory->findLocationOfFile("test.txt", filePath)) {
                    cout << "File found at location: " << filePath << endl;
                }
                cout << "\n";
                break;
            }

            case 6 :
            {
                unsigned long long fileSize;
                if (objDirectory->findSpaceTakenByFile("test.txt", fileSize)) {
                    cout << "File size: " << fileSize << " bytes" << endl;
                }
                cout << "\n";
                break;
            }

            case 7 :
            {
                if (objDirectory->renameFile("test.txt", "test_renamed.txt")) {
                    cout << "File renamed successfully!" << endl;
                }
                cout << "\n";
                break;
            }

            case 8 :
            {
                if (objDirectory->deleteFile("test_renamed.txt")) {
                    cout << "File deleted successfully!" << endl;
                }
                cout << "\n";
                break;
            }

            case 9 :
            {
                managerObj->Indexing("C:\\Users\\ipart\\OneDrive\\Desktop\\");
                // Search for a file
                if (managerObj->Searchfile("test.txt")) {
                    cout << "File found!" << endl;
                } else {
                    cout << "File not found." << endl;
                }
                cout << "\n";
                break;
            }

            case 10 :
            {
                // Print the file index
                managerObj->Index();
                cout << "\n";
                break;
            }

            case 11 :
            {
                cout << "Exiting program...\n";
                cout << "\n";
                return 0;
            }

            default :
            {
                cout << "Invalid input, please try again.\n\n";
                cout << "\n";
            }
        }
    */
