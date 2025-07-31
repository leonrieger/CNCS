// ipc_linux.h
#pragma once
#include <string>
#include <sys/mman.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include <semaphore.h>

class LinuxIPC {
private:
    std::string shmName;
    std::string mutexName;
    int shmFd;
    sem_t* mutex;
    void* shmPtr;
    SharedMemoryBuffer* buffer;
    bool isCreator;

public:
    // Constructor - pass true for creator process, false for second process
    LinuxIPC(const std::string& name, bool creator) : shmName("/shm_" + name), 
                                                     mutexName("/mutex_" + name),
                                                     isCreator(creator) {
        // Create or open shared memory
        shmFd = shm_open(shmName.c_str(), 
                         O_CREAT | O_RDWR, 
                         S_IRUSR | S_IWUSR);
        
        if (shmFd == -1) {
            throw std::runtime_error("Failed to open shared memory");
        }
        
        // Set size (only creator does this)
        if (isCreator) {
            if (ftruncate(shmFd, sizeof(SharedMemoryBuffer)) == -1) {
                close(shmFd);
                throw std::runtime_error("Failed to set shared memory size");
            }
        }
        
        // Map the shared memory
        shmPtr = mmap(NULL, sizeof(SharedMemoryBuffer), 
                      PROT_READ | PROT_WRITE, MAP_SHARED, 
                      shmFd, 0);
        
        if (shmPtr == MAP_FAILED) {
            close(shmFd);
            throw std::runtime_error("Failed to map shared memory");
        }
        
        buffer = static_cast<SharedMemoryBuffer*>(shmPtr);
        
        // Initialize or open mutex
        if (isCreator) {
            mutex = sem_open(mutexName.c_str(), O_CREAT | O_EXCL, 
                            S_IRUSR | S_IWUSR, 1);
            if (mutex == SEM_FAILED) {
                // Cleanup if failed
                sem_unlink(mutexName.c_str());
                mutex = sem_open(mutexName.c_str(), O_CREAT, 
                                S_IRUSR | S_IWUSR, 1);
            }
            // Initialize shared memory
            buffer->process1HasData = false;
            buffer->process2HasData = false;
        } else {
            mutex = sem_open(mutexName.c_str(), 0);
        }
        
        if (mutex == SEM_FAILED) {
            munmap(shmPtr, sizeof(SharedMemoryBuffer));
            close(shmFd);
            throw std::runtime_error("Failed to create/open mutex");
        }
    }
    
    // Destructor
    ~LinuxIPC() {
        sem_close(mutex);
        munmap(shmPtr, sizeof(SharedMemoryBuffer));
        close(shmFd);
        
        if (isCreator) {
            sem_unlink(mutexName.c_str());
            shm_unlink(shmName.c_str());
        }
    }
    
    // Send message from process 1 to process 2
    bool sendProcess1to2(const std::string& message) {
        sem_wait(mutex);  // Lock mutex
        
        strncpy(buffer->process1to2, message.c_str(), 1023);
        buffer->process1to2[1023] = '\0';  // Ensure null-termination
        buffer->process1HasData = true;
        
        sem_post(mutex);  // Unlock mutex
        return true;
    }
    
    // Send message from process 2 to process 1
    bool sendProcess2to1(const std::string& message) {
        sem_wait(mutex);  // Lock mutex
        
        strncpy(buffer->process2to1, message.c_str(), 1023);
        buffer->process2to1[1023] = '\0';  // Ensure null-termination
        buffer->process2HasData = true;
        
        sem_post(mutex);  // Unlock mutex
        return true;
    }
    
    // Receive message for process 1 (sent from process 2)
    std::string receiveForProcess1(bool& hasData) {
        sem_wait(mutex);  // Lock mutex
        
        std::string result;
        hasData = buffer->process2HasData;
        
        if (hasData) {
            result = buffer->process2to1;
            buffer->process2HasData = false;  // Mark as read
        }
        
        sem_post(mutex);  // Unlock mutex
        return result;
    }
    
    // Receive message for process 2 (sent from process 1)
    std::string receiveForProcess2(bool& hasData) {
        sem_wait(mutex);  // Lock mutex
        
        std::string result;
        hasData = buffer->process1HasData;
        
        if (hasData) {
            result = buffer->process1to2;
            buffer->process1HasData = false;  // Mark as read
        }
        
        sem_post(mutex);  // Unlock mutex
        return result;
    }
};