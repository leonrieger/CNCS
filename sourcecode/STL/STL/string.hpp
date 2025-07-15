#pragma once

#pragma once

class MyString {
private:
    char* data_;
    unsigned int length_;
    unsigned int capacity_;

    // Helper: compute strlen
    static unsigned int strlen_(const char* str) {
        unsigned int len = 0;
        while (str[len] != '\0')
            ++len;
        return len;
    }

    // Helper: copy memory
    static void memcpy_(char* dest, const char* src, unsigned int n) {
        for (unsigned int i = 0; i < n; ++i)
            dest[i] = src[i];
    }

    // Helper: compare memory
    static int memcmp_(const char* s1, const char* s2, unsigned int n) {
        for (unsigned int i = 0; i < n; ++i)
            if (s1[i] != s2[i])
                return (unsigned char)s1[i] - (unsigned char)s2[i];
        return 0;
    }

    // Helper: set memory
    static void memset_(char* dest, char val, unsigned int n) {
        for (unsigned int i = 0; i < n; ++i)
            dest[i] = val;
    }

    // Internal: ensure enough capacity
    void ensure_capacity(unsigned int newcap) {
        if (newcap > capacity_) {
            unsigned int new_capacity =
                (newcap > 2 * capacity_) ? newcap : 2 * capacity_ + 8;
            char* newdata = new char[new_capacity + 1];
            memcpy_(newdata, data_, length_);
            newdata[length_] = '\0';
            delete[] data_;
            data_ = newdata;
            capacity_ = new_capacity;
        }
    }

public:
    // Default constructor
    MyString() : data_(new char[1]), length_(0), capacity_(0) {
        data_[0] = '\0';
    }

    // Constructor from C-string
    MyString(const char* str) {
        length_ = strlen_(str);
        capacity_ = length_;
        data_ = new char[capacity_ + 1];
        memcpy_(data_, str, length_);
        data_[length_] = '\0';
    }

    // Constructor from char, n times
    MyString(unsigned int n, char c) {
        length_ = n;
        capacity_ = n;
        data_ = new char[capacity_ + 1];
        for (unsigned int i = 0; i < n; ++i)
            data_[i] = c;
        data_[n] = '\0';
    }

    // Copy constructor
    MyString(const MyString& other) {
        length_ = other.length_;
        capacity_ = length_;
        data_ = new char[capacity_ + 1];
        memcpy_(data_, other.data_, length_);
        data_[length_] = '\0';
    }

    // Move constructor
    MyString(MyString&& other) noexcept
        : data_(other.data_), length_(other.length_),
          capacity_(other.capacity_) {
        other.data_ = nullptr;
        other.length_ = 0;
        other.capacity_ = 0;
    }

    // Destructor
    ~MyString() { delete[] data_; }

    // Copy assignment
    MyString& operator=(const MyString& other) {
        if (this != &other) {
            delete[] data_;
            length_ = other.length_;
            capacity_ = length_;
            data_ = new char[capacity_ + 1];
            memcpy_(data_, other.data_, length_);
            data_[length_] = '\0';
        }
        return *this;
    }

    // Move assignment
    MyString& operator=(MyString&& other) noexcept {
        if (this != &other) {
            delete[] data_;
            data_ = other.data_;
            length_ = other.length_;
            capacity_ = other.capacity_;
            other.data_ = nullptr;
            other.length_ = 0;
            other.capacity_ = 0;
        }
        return *this;
    }

    // Assignment from C-string
    MyString& operator=(const char* str) {
        unsigned int len = strlen_(str);
        ensure_capacity(len);
        length_ = len;
        memcpy_(data_, str, len);
        data_[length_] = '\0';
        return *this;
    }

    // Length & capacity
    unsigned int size() const { return length_; }
    unsigned int length() const { return length_; }
    unsigned int capacity() const { return capacity_; }
    bool empty() const { return length_ == 0; }

    // C-string access
    const char* c_str() const { return data_; }
    char* data() { return data_; }
    const char* data() const { return data_; }

    // Clear
    void clear() {
        length_ = 0;
        if (data_)
            data_[0] = '\0';
    }

    // Reserve
    void reserve(unsigned int n) { ensure_capacity(n); }

    // Shrink to fit
    void shrink_to_fit() {
        if (capacity_ > length_) {
            char* newdata = new char[length_ + 1];
            memcpy_(newdata, data_, length_);
            newdata[length_] = '\0';
            delete[] data_;
            data_ = newdata;
            capacity_ = length_;
        }
    }

    // Push back
    void push_back(char c) {
        ensure_capacity(length_ + 1);
        data_[length_] = c;
        ++length_;
        data_[length_] = '\0';
    }

    // Pop back
    void pop_back() {
        if (length_ > 0) {
            --length_;
            data_[length_] = '\0';
        }
    }

    // Append
    MyString& append(const MyString& other) {
        ensure_capacity(length_ + other.length_);
        memcpy_(data_ + length_, other.data_, other.length_);
        length_ += other.length_;
        data_[length_] = '\0';
        return *this;
    }
    MyString& append(const char* str) {
        unsigned int len = strlen_(str);
        ensure_capacity(length_ + len);
        memcpy_(data_ + length_, str, len);
        length_ += len;
        data_[length_] = '\0';
        return *this;
    }
    MyString& append(unsigned int n, char c) {
        ensure_capacity(length_ + n);
        for (unsigned int i = 0; i < n; ++i)
            data_[length_ + i] = c;
        length_ += n;
        data_[length_] = '\0';
        return *this;
    }

    // Operator +=
    MyString& operator+=(const MyString& rhs) { return append(rhs); }
    MyString& operator+=(const char* rhs) { return append(rhs); }
    MyString& operator+=(char c) { return append(1, c); }

    // Operator +
    MyString operator+(const MyString& rhs) const {
        MyString res(*this);
        res.append(rhs);
        return res;
    }
    MyString operator+(const char* rhs) const {
        MyString res(*this);
        res.append(rhs);
        return res;
    }
    MyString operator+(char c) const {
        MyString res(*this);
        res.append(1, c);
        return res;
    }

    // At (with bounds checking)
    char& at(unsigned int pos) {
        if (pos >= length_)
            throw "out_of_range";
        return data_[pos];
    }
    const char& at(unsigned int pos) const {
        if (pos >= length_)
            throw "out_of_range";
        return data_[pos];
    }

    // Operator []
    char& operator[](unsigned int idx) { return data_[idx]; }
    const char& operator[](unsigned int idx) const { return data_[idx]; }

    // Front/back
    char& front() { return data_[0]; }
    const char& front() const { return data_[0]; }
    char& back() { return data_[length_ - 1]; }
    const char& back() const { return data_[length_ - 1]; }
};
