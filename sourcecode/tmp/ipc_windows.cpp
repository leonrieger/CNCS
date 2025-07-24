// ipc_windows.h
#pragma once
#include <string>
#include <windows.h>

class WindowsIPC {
private:
    std::string shmName;
    std::string mutexName;
    HANDLE hMapFile;
    HANDLE hMutex;
    void* shmPtr;
    SharedMemoryBuffer* buffer;
    bool isCreator;

public:
    // Constructor - pass true for creator process, false for second process
    WindowsIPC(const std::string& name, bool creator) : shmName("Global\\shm_" + name), 
                                                       mutexName("Global\\mutex_" + name),
                                                       isCreator(creator) {
        // Create or open mutex
        hMutex = CreateMutexA(NULL, FALSE, mutexName.c_str());
        if (hMutex == NULL) {
            throw std::runtime_error("Failed to create/open mutex");
        }
        
        // Create or open shared memory
        if (isCreator) {
            hMapFile = CreateFileMappingA(
                INVALID_HANDLE_VALUE,   // Use paging file
                NULL,                   // Default security
                PAGE_READWRITE,         // Read/write access
                0,                      // High-order DWORD of size
                sizeof(SharedMemoryBuffer), // Low-order DWORD of size
                shmName.c_str());       // Name of mapping object
        } else {
            hMapFile = OpenFileMappingA(
                FILE_MAP_ALL_ACCESS,    // Read/write access
                FALSE,                  // Do not inherit name
                shmName.c_str());       // Name of mapping object
        }
        
        if (hMapFile == NULL) {
            CloseHandle(hMutex);
            throw std::runtime_error("Failed to create/open shared memory");
        }
        
        // Map view of the file
        shmPtr = MapViewOfFile(
            hMapFile,                   // Handle to map object
            FILE_MAP_ALL_ACCESS,        // Read/write permission
            0,                          // High-order DWORD of offset
            0,                          // Low-order DWORD of offset
            sizeof(SharedMemoryBuffer));// Number of bytes to map
        
        if (shmPtr == NULL) {
            CloseHandle(hMapFile);
            CloseHandle(hMutex);
            throw std::runtime_error("Failed to map view of file");
        }
        
        buffer = static_cast<SharedMemoryBuffer*>(shmPtr);
        
        // Initialize shared memory if creator
        if (isCreator) {
            WaitForSingleObject(hMutex, INFINITE);  // Lock mutex
            buffer->process1HasData = false;
            buffer->process2HasData = false;
            ReleaseMutex(hMutex);  // Unlock mutex
        }
    }
    
    // Destructor
    ~WindowsIPC() {
        UnmapViewOfFile(shmPtr);
        CloseHandle(hMapFile);
        CloseHandle(hMutex);
    }
    
    // Send message from process 1 to process 2
    bool sendProcess1to2(const std::string& message) {
        WaitForSingleObject(hMutex, INFINITE);  // Lock mutex
        
        strncpy_s(buffer->process1to2, 1024, message.c_str(), _TRUNCATE);
        buffer->process1HasData = true;
        
        ReleaseMutex(hMutex);  // Unlock mutex
        return true;
    }
    
    // Send message from process 2 to process 1
    bool sendProcess2to1(const std::string& message) {
        WaitForSingleObject(hMutex, INFINITE);  // Lock mutex
        
        strncpy_s(buffer->process2to1, 1024, message.c_str(), _TRUNCATE);
        buffer->process2HasData = true;
        
        ReleaseMutex(hMutex);  // Unlock mutex
        return true;
    }
    
    // Receive message for process 1 (sent from process 2)
    std::string receiveForProcess1(bool& hasData) {
        WaitForSingleObject(hMutex, INFINITE);  // Lock mutex
        
        std::string result;
        hasData = buffer->process2HasData;
        
        if (hasData) {
            result = buffer->process2to1;
            buffer->process2HasData = false;  // Mark as read
        }
        
        ReleaseMutex(hMutex);  // Unlock mutex
        return result;
    }
    
    // Receive message for process 2 (sent from process 1)
    std::string receiveForProcess2(bool& hasData) {
        WaitForSingleObject(hMutex, INFINITE);  // Lock mutex
        
        std::string result;
        hasData = buffer->process1HasData;
        
        if (hasData) {
            result = buffer->process1to2;
            buffer->process1HasData = false;  // Mark as read
        }
        
        ReleaseMutex(hMutex);  // Unlock mutex
        return result;
    }
};



//_------------------------

// SecureWindowsIPC.h
#pragma once
#include <string>
#include <windows.h>
#include <stdexcept>
#include <ctime>

// Reduced size for smaller file transfers
#define MAX_FILE_SIZE 4096

// Structure representing a process authorization
struct ProcessAuth {
    DWORD creatorProcessId;    // Creator process ID
    DWORD clientProcessId;     // Authorized client process ID
    char creatorUsername[64];  // Creator username
    char clientUsername[64];   // Authorized client username
    FILETIME creationTime;     // When the shared memory was created
};

// Main shared memory structure
struct SharedMemoryBuffer {
    ProcessAuth auth;          // Authentication information
    bool process1HasData;      // Flag for creator process data
    bool process2HasData;      // Flag for client process data
    int dataSize;              // Size of the actual data
    char buffer[MAX_FILE_SIZE]; // Buffer for file data
};

class SecureWindowsIPC {
private:
    std::string shmName;
    std::string mutexName;
    HANDLE hMapFile;
    HANDLE hMutex;
    void* shmPtr;
    SharedMemoryBuffer* buffer;
    bool isCreator;
    DWORD processId;           // Current process ID (assigned by OS)
    char username[64];         // Current username

    // Helper function to get current username
    bool getCurrentUsername() {
        DWORD size = sizeof(username);
        return GetUserNameA(username, &size) != 0;
    }

public:
    // Constructor using OS-assigned process ID
    SecureWindowsIPC(const std::string& name, bool creator) : 
        shmName("Global\\shm_" + name), 
        mutexName("Global\\mutex_" + name),
        isCreator(creator) {
        
        // Get current process ID assigned by OS
        processId = GetCurrentProcessId();
        
        // Get current username
        if (!getCurrentUsername()) {
            strcpy_s(username, "unknown");
        }
        
        // Create or open mutex
        hMutex = CreateMutexA(NULL, FALSE, mutexName.c_str());
        if (hMutex == NULL) {
            throw std::runtime_error("Failed to create/open mutex");
        }
        
        // Create or open shared memory
        if (isCreator) {
            hMapFile = CreateFileMappingA(
                INVALID_HANDLE_VALUE,   // Use paging file
                NULL,                   // Default security
                PAGE_READWRITE,         // Read/write access
                0,                      // High-order DWORD of size
                sizeof(SharedMemoryBuffer), // Low-order DWORD of size
                shmName.c_str());       // Name of mapping object
        } else {
            hMapFile = OpenFileMappingA(
                FILE_MAP_ALL_ACCESS,    // Read/write access
                FALSE,                  // Do not inherit name
                shmName.c_str());       // Name of mapping object
        }
        
        if (hMapFile == NULL) {
            CloseHandle(hMutex);
            DWORD error = GetLastError();
            throw std::runtime_error("Failed to create/open shared memory. Error: " + std::to_string(error));
        }
        
        // Map view of the file
        shmPtr = MapViewOfFile(
            hMapFile,                   // Handle to map object
            FILE_MAP_ALL_ACCESS,        // Read/write permission
            0,                          // High-order DWORD of offset
            0,                          // Low-order DWORD of offset
            sizeof(SharedMemoryBuffer));// Number of bytes to map
        
        if (shmPtr == NULL) {
            CloseHandle(hMapFile);
            CloseHandle(hMutex);
            throw std::runtime_error("Failed to map view of file");
        }
        
        buffer = static_cast<SharedMemoryBuffer*>(shmPtr);
        
        // Initialize or verify process authorization
        WaitForSingleObject(hMutex, INFINITE);
        
        if (isCreator) {
            // Initialize shared memory with process auth info
            buffer->auth.creatorProcessId = processId;
            buffer->auth.clientProcessId = 0; // Not yet assigned
            strcpy_s(buffer->auth.creatorUsername, username);
            buffer->auth.clientUsername[0] = '\0';
            GetSystemTimeAsFileTime(&buffer->auth.creationTime);
            
            buffer->process1HasData = false;
            buffer->process2HasData = false;
            buffer->dataSize = 0;
            
            char timeStr[20];
            SYSTEMTIME st;
            FileTimeToSystemTime(&buffer->auth.creationTime, &st);
            sprintf_s(timeStr, "%04d-%02d-%02d %02d:%02d:%02d", 
                      st.wYear, st.wMonth, st.wDay, st.wHour, st.wMinute, st.wSecond);
            
            printf("Shared memory initialized by creator process %lu (user: %s) at %s\n", 
                   processId, username, timeStr);
        } else {
            // Verify we're connecting to a valid creator process
            if (buffer->auth.creatorProcessId == 0) {
                ReleaseMutex(hMutex);
                UnmapViewOfFile(shmPtr);
                CloseHandle(hMapFile);
                CloseHandle(hMutex);
                throw std::runtime_error("Invalid shared memory - not properly initialized");
            }
            
            // If no client is registered yet, register ourselves
            if (buffer->auth.clientProcessId == 0) {
                buffer->auth.clientProcessId = processId;
                strcpy_s(buffer->auth.clientUsername, username);
                printf("Client process %lu (user: %s) registered with creator process %lu (user: %s)\n",
                       processId, username, buffer->auth.creatorProcessId, buffer->auth.creatorUsername);
            }
            // Otherwise verify we are the registered client
            else if (buffer->auth.clientProcessId != processId) {
                ReleaseMutex(hMutex);
                UnmapViewOfFile(shmPtr);
                CloseHandle(hMapFile);
                CloseHandle(hMutex);
                throw std::runtime_error("Unauthorized access - another client is already registered");
            }
        }
        
        ReleaseMutex(hMutex);
    }
    
    // Destructor
    ~SecureWindowsIPC() {
        if (shmPtr) UnmapViewOfFile(shmPtr);
        if (hMapFile) CloseHandle(hMapFile);
        if (hMutex) CloseHandle(hMutex);
        
        // If creator, we could optionally clean up shared resources here
        // However, in production you might want the resources to persist for reconnection
    }
    
    // Get info about the connection
    std::string getConnectionInfo() {
        WaitForSingleObject(hMutex, INFINITE);
        
        char timeStr[20];
        SYSTEMTIME st;
        FileTimeToSystemTime(&buffer->auth.creationTime, &st);
        sprintf_s(timeStr, "%04d-%02d-%02d %02d:%02d:%02d", 
                  st.wYear, st.wMonth, st.wDay, st.wHour, st.wMinute, st.wSecond);
        
        std::string info = "Shared Memory Connection Info:\n";
        info += "  Created: " + std::string(timeStr) + "\n";
        info += "  Creator Process: " + std::to_string(buffer->auth.creatorProcessId) + 
                " (User: " + buffer->auth.creatorUsername + ")\n";
        
        if (buffer->auth.clientProcessId != 0) {
            info += "  Client Process: " + std::to_string(buffer->auth.clientProcessId) + 
                    " (User: " + buffer->auth.clientUsername + ")\n";
        } else {
            info += "  Client Process: Not yet connected\n";
        }
        
        ReleaseMutex(hMutex);
        return info;
    }
    
    // Send file from creator process to client
    bool sendFileFromCreator(const std::string& filePath) {
        if (!isCreator) {
            throw std::runtime_error("Only creator process can use this method");
        }
        
        // Read file into memory
        FILE* file = NULL;
        fopen_s(&file, filePath.c_str(), "rb");
        if (!file) {
            throw std::runtime_error("Failed to open file for reading: " + filePath);
        }
        
        // Get file size
        fseek(file, 0, SEEK_END);
        long fileSize = ftell(file);
        fseek(file, 0, SEEK_SET);
        
        if (fileSize > MAX_FILE_SIZE) {
            fclose(file);
            throw std::runtime_error("File too large for shared memory buffer (max: " + 
                                     std::to_string(MAX_FILE_SIZE) + " bytes)");
        }
        
        // Read file into local buffer
        char* fileBuffer = new char[fileSize];
        size_t bytesRead = fread(fileBuffer, 1, fileSize, file);
        fclose(file);
        
        if (bytesRead != fileSize) {
            delete[] fileBuffer;
            throw std::runtime_error("Failed to read entire file");
        }
        
        // Acquire mutex and write to shared memory
        WaitForSingleObject(hMutex, INFINITE);
        
        // Verify we are the creator process
        if (buffer->auth.creatorProcessId != processId) {
            ReleaseMutex(hMutex);
            delete[] fileBuffer;
            throw std::runtime_error("Process ID verification failed");
        }
        
        // Copy file data to shared memory
        memcpy(buffer->buffer, fileBuffer, fileSize);
        buffer->dataSize = fileSize;
        buffer->process1HasData = true;
        
        ReleaseMutex(hMutex);
        delete[] fileBuffer;
        
        return true;
    }
    
    // Send file from client process to creator
    bool sendFileFromClient(const std::string& filePath) {
        if (isCreator) {
            throw std::runtime_error("Only client process can use this method");
        }
        
        // Read file into memory
        FILE* file = NULL;
        fopen_s(&file, filePath.c_str(), "rb");
        if (!file) {
            throw std::runtime_error("Failed to open file for reading: " + filePath);
        }
        
        // Get file size
        fseek(file, 0, SEEK_END);
        long fileSize = ftell(file);
        fseek(file, 0, SEEK_SET);
        
        if (fileSize > MAX_FILE_SIZE) {
            fclose(file);
            throw std::runtime_error("File too large for shared memory buffer (max: " + 
                                     std::to_string(MAX_FILE_SIZE) + " bytes)");
        }
        
        // Read file into local buffer
        char* fileBuffer = new char[fileSize];
        size_t bytesRead = fread(fileBuffer, 1, fileSize, file);
        fclose(file);
        
        if (bytesRead != fileSize) {
            delete[] fileBuffer;
            throw std::runtime_error("Failed to read entire file");
        }
        
        // Acquire mutex and write to shared memory
        WaitForSingleObject(hMutex, INFINITE);
        
        // Verify we are the registered client
        if (buffer->auth.clientProcessId != processId) {
            ReleaseMutex(hMutex);
            delete[] fileBuffer;
            throw std::runtime_error("Process ID verification failed");
        }
        
        // Copy file data to shared memory
        memcpy(buffer->buffer, fileBuffer, fileSize);
        buffer->dataSize = fileSize;
        buffer->process2HasData = true;
        
        ReleaseMutex(hMutex);
        delete[] fileBuffer;
        
        return true;
    }
    
    // Receive file for creator (sent from client)
    bool receiveFileForCreator(const std::string& outputPath, bool& hasData) {
        if (!isCreator) {
            throw std::runtime_error("Only creator process can use this method");
        }
        
        WaitForSingleObject(hMutex, INFINITE);
        
        // Verify we are the creator process
        if (buffer->auth.creatorProcessId != processId) {
            ReleaseMutex(hMutex);
            throw std::runtime_error("Process ID verification failed");
        }
        
        hasData = buffer->process2HasData;
        
        if (!hasData) {
            ReleaseMutex(hMutex);
            return false;
        }
        
        // Get file data and size
        int fileSize = buffer->dataSize;
        char* fileData = new char[fileSize];
        memcpy(fileData, buffer->buffer, fileSize);
        
        // Mark as read
        buffer->process2HasData = false;
        
        ReleaseMutex(hMutex);
        
        // Write to output file
        FILE* file = NULL;
        fopen_s(&file, outputPath.c_str(), "wb");
        if (!file) {
            delete[] fileData;
            throw std::runtime_error("Failed to open output file for writing: " + outputPath);
        }
        
        size_t bytesWritten = fwrite(fileData, 1, fileSize, file);
        fclose(file);
        delete[] fileData;
        
        if (bytesWritten != fileSize) {
            throw std::runtime_error("Failed to write entire file");
        }
        
        return true;
    }
    
    // Receive file for client (sent from creator)
    bool receiveFileForClient(const std::string& outputPath, bool& hasData) {
        if (isCreator) {
            throw std::runtime_error("Only client process can use this method");
        }
        
        WaitForSingleObject(hMutex, INFINITE);
        
        // Verify we are the registered client
        if (buffer->auth.clientProcessId != processId) {
            ReleaseMutex(hMutex);
            throw std::runtime_error("Process ID verification failed");
        }
        
        hasData = buffer->process1HasData;
        
        if (!hasData) {
            ReleaseMutex(hMutex);
            return false;
        }
        
        // Get file data and size
        int fileSize = buffer->dataSize;
        char* fileData = new char[fileSize];
        memcpy(fileData, buffer->buffer, fileSize);
        
        // Mark as read
        buffer->process1HasData = false;
        
        ReleaseMutex(hMutex);
        
        // Write to output file
        FILE* file = NULL;
        fopen_s(&file, outputPath.c_str(), "wb");
        if (!file) {
            delete[] fileData;
            throw std::runtime_error("Failed to open output file for writing: " + outputPath);
        }
        
        size_t bytesWritten = fwrite(fileData, 1, fileSize, file);
        fclose(file);
        delete[] fileData;
        
        if (bytesWritten != fileSize) {
            throw std::runtime_error("Failed to write entire file");
        }
        
        return true;
    }
    
    // Send message from creator to client
    bool sendMessageFromCreator(const std::string& message) {
        if (!isCreator) {
            throw std::runtime_error("Only creator process can use this method");
        }
        
        WaitForSingleObject(hMutex, INFINITE);
        
        // Verify we are the creator process
        if (buffer->auth.creatorProcessId != processId) {
            ReleaseMutex(hMutex);
            throw std::runtime_error("Process ID verification failed");
        }
        
        if (message.size() > MAX_FILE_SIZE - 1) {
            ReleaseMutex(hMutex);
            throw std::runtime_error("Message too large for buffer");
        }
        
        // Copy message to shared memory
        strcpy_s(buffer->buffer, MAX_FILE_SIZE, message.c_str());
        buffer->dataSize = message.size() + 1;  // Include null terminator
        buffer->process1HasData = true;
        
        ReleaseMutex(hMutex);
        return true;
    }
    
    // Send message from client to creator
    bool sendMessageFromClient(const std::string& message) {
        if (isCreator) {
            throw std::runtime_error("Only client process can use this method");
        }
        
        WaitForSingleObject(hMutex, INFINITE);
        
        // Verify we are the registered client
        if (buffer->auth.clientProcessId != processId) {
            ReleaseMutex(hMutex);
            throw std::runtime_error("Process ID verification failed");
        }
        
        if (message.size() > MAX_FILE_SIZE - 1) {
            ReleaseMutex(hMutex);
            throw std::runtime_error("Message too large for buffer");
        }
        
        // Copy message to shared memory
        strcpy_s(buffer->buffer, MAX_FILE_SIZE, message.c_str());
        buffer->dataSize = message.size() + 1;  // Include null terminator
        buffer->process2HasData = true;
        
        ReleaseMutex(hMutex);
        return true;
    }
    
    // Receive message for creator (sent from client)
    std::string receiveMessageForCreator(bool& hasData) {
        if (!isCreator) {
            throw std::runtime_error("Only creator process can use this method");
        }
        
        WaitForSingleObject(hMutex, INFINITE);
        
        // Verify we are the creator process
        if (buffer->auth.creatorProcessId != processId) {
            ReleaseMutex(hMutex);
            throw std::runtime_error("Process ID verification failed");
        }
        
        hasData = buffer->process2HasData;
        std::string result;
        
        if (hasData) {
            result = buffer->buffer;
            buffer->process2HasData = false;  // Mark as read
        }
        
        ReleaseMutex(hMutex);
        return result;
    }
    
    // Receive message for client (sent from creator)
    std::string receiveMessageForClient(bool& hasData) {
        if (isCreator) {
            throw std::runtime_error("Only client process can use this method");
        }
        
        WaitForSingleObject(hMutex, INFINITE);
        
        // Verify we are the registered client
        if (buffer->auth.clientProcessId != processId) {
            ReleaseMutex(hMutex);
            throw std::runtime_error("Process ID verification failed");
        }
        
        hasData = buffer->process1HasData;
        std::string result;
        
        if (hasData) {
            result = buffer->buffer;
            buffer->process1HasData = false;  // Mark as read
        }
        
        ReleaseMutex(hMutex);
        return result;
    }
};
