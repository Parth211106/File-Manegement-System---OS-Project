#include <iostream>
#include <windows.h>
#include <string>
#include <sddl.h>
#include <AclAPI.h>
using namespace std;

class FileSecurity {
private:
    string filePath_;
    HANDLE hFile_;
    PSECURITY_DESCRIPTOR pSecurityDescriptor_;

public:
    FileSecurity(string filePath) : filePath_(filePath), hFile_(NULL), pSecurityDescriptor_(NULL) {}
    ~FileSecurity() { Cleanup(); }

    bool Open() {
        hFile_ = CreateFile(filePath_.c_str(),
                            GENERIC_READ | GENERIC_WRITE,
                            FILE_SHARE_READ, NULL,
                            OPEN_EXISTING,
                            FILE_ATTRIBUTE_NORMAL,
                            NULL);
        if (hFile_ == INVALID_HANDLE_VALUE) {
            cout << "Error opening file" << endl;
            return false;
        }
        return true;
    }

    bool GetSecurityInfo() {
        if (!hFile_) {
            cout << "File handle is not open" << endl;
            return false;
        }
        DWORD dwLength = 0;
        if (GetFileSecurity(filePath_.c_str(),
                            DACL_SECURITY_INFORMATION,
                            NULL,
                            0,
                            &dwLength) == ERROR_INSUFFICIENT_BUFFER) {
            pSecurityDescriptor_ = LocalAlloc(LPTR, dwLength);
            if (pSecurityDescriptor_ == NULL) {
                cout << "Error allocating memory for security descriptor" << endl;
                return false;
            }
            if (GetFileSecurity(filePath_.c_str(),
                                DACL_SECURITY_INFORMATION,
                                pSecurityDescriptor_,
                                dwLength,
                                &dwLength) != ERROR_SUCCESS) {
                cout << "Error getting security descriptor" << endl;
                return false;
            }
        }
        else {
            cout << "Error getting security descriptor" << endl;
            return false;
        }
        return true;
    }

    bool PrintCurrentAccessRights() {
        if (!pSecurityDescriptor_) {
            cout << "Security descriptor is not available" << endl;
            return false;
        }
        DWORD dwLength = 0;
        LPTSTR lpStringSecurityDescriptor = NULL;
        if (!ConvertSecurityDescriptorToStringSecurityDescriptor(pSecurityDescriptor_,
                                                                 SDDL_REVISION_1,
                                                                 DACL_SECURITY_INFORMATION,
                                                                 &lpStringSecurityDescriptor,
                                                                 &dwLength)) {
            cout << "Error converting security descriptor to string format" << endl;
            return false;
        }
        cout << "Current access rights: " << lpStringSecurityDescriptor << endl;
        LocalFree(lpStringSecurityDescriptor);
        return true;
    }

    bool SetNewAccessRights(string sNewSecurityDescriptor) {
        PSECURITY_DESCRIPTOR pNewSecurityDescriptor = NULL;
        if (!ConvertStringSecurityDescriptorToSecurityDescriptor(sNewSecurityDescriptor.c_str(),
                                                                 SDDL_REVISION_1,
                                                                 &pNewSecurityDescriptor,
                                                                 NULL)) {
            cout << "Error converting new security descriptor to binary format" << endl;
            return false;
        }
        if (SetFileSecurity(filePath_.c_str(),
                            DACL_SECURITY_INFORMATION,
                            pNewSecurityDescriptor) != ERROR_SUCCESS) {
            cout << "Error setting new security descriptor" << endl;
            LocalFree(pNewSecurityDescriptor);
            return false;
        }
        LocalFree(pNewSecurityDescriptor);
        return true;
    }

    bool Cleanup() {
        if (pSecurityDescriptor_) {
            LocalFree(pSecurityDescriptor_);
            pSecurityDescriptor_ = NULL;
        }
        if (hFile_ != NULL) {
            CloseHandle(hFile_);
            hFile_ = NULL;
        }
        return true;
    }
};

/*
int main() {
    string filePath = "C:\\Users\\ipart\\OneDrive\\Desktop\\test.txt";
    FileSecurity fileSecurity(filePath);

    // Open the file
    if (!fileSecurity.Open()) {
        return 1;
    }

    // Get the security information for the file
    if (!fileSecurity.GetSecurityInfo()) {
        return 1;
    }

    // Print the current access rights for the file
    if (!fileSecurity.PrintCurrentAccessRights()) {
        return 1;
    }

    // Set new access rights for the file
    string sNewSecurityDescriptor = "D:(A;OICI;GRGW;;;WD)";
    if (!fileSecurity.SetNewAccessRights(sNewSecurityDescriptor)) {
        return 1;
    }

    // Cleanup and exit
    fileSecurity.Cleanup();
    return 0;
}
*/
