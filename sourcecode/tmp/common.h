struct SharedMemoryBuffer {
    bool process1HasData;     // Flag indicating process 1 has written data
    bool process2HasData;     // Flag indicating process 2 has written data
    char process1to2[1024];   // Data buffer from process 1 to process 2
    char process2to1[1024];   // Data buffer from process 2 to process 1
};