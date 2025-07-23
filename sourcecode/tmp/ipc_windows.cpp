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