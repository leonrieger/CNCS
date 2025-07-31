#pragma once

class MyString {
private:
    char* data_;            // Pointer to string data
    unsigned int size_;     // Current string length
    unsigned int capacity_; // Allocated memory size

    // Static constants
    static const unsigned int npos_ = (unsigned int)-1;

    // Helper methods for memory management
    void reallocate(unsigned int new_capacity) {
        char* new_data = new char[new_capacity];

        // Copy existing data if any
        if (data_ != nullptr) {
            for (unsigned int i = 0; i < size_; ++i) {
                new_data[i] = data_[i];
            }
            delete[] data_;
        }

        data_ = new_data;
        capacity_ = new_capacity;
    }

public:
    // Type definitions
    typedef unsigned int size_type;
    static const size_type npos = npos_;

    // Constructors
    // Default constructor
    MyString() : data_(nullptr), size_(0), capacity_(0) {
        reallocate(1); // Allocate space for null terminator
        data_[0] = '\0';
    }

    // Constructor from C-string
    MyString(const char* str) : data_(nullptr), size_(0), capacity_(0) {
        if (str == nullptr) {
            reallocate(1);
            data_[0] = '\0';
            return;
        }

        // Calculate length
        size_ = 0;
        while (str[size_] != '\0') {
            ++size_;
        }

        // Allocate memory
        reallocate(size_ + 1);

        // Copy data
        for (unsigned int i = 0; i < size_; ++i) {
            data_[i] = str[i];
        }
        data_[size_] = '\0';
    }

    // Constructor from C-string with length
    MyString(const char* str, size_type n)
        : data_(nullptr), size_(0), capacity_(0) {
        if (str == nullptr || n == 0) {
            reallocate(1);
            data_[0] = '\0';
            return;
        }

        size_ = 0;
        while (size_ < n && str[size_] != '\0') {
            ++size_;
        }

        reallocate(size_ + 1);

        for (unsigned int i = 0; i < size_; ++i) {
            data_[i] = str[i];
        }
        data_[size_] = '\0';
    }

    // Constructor from repeated characters
    MyString(size_type n, char c) : data_(nullptr), size_(0), capacity_(0) {
        size_ = n;
        reallocate(size_ + 1);

        for (unsigned int i = 0; i < size_; ++i) {
            data_[i] = c;
        }
        data_[size_] = '\0';
    }

    // Copy constructor
    MyString(const MyString& other) : data_(nullptr), size_(0), capacity_(0) {
        size_ = other.size_;
        reallocate(size_ + 1);

        for (unsigned int i = 0; i < size_; ++i) {
            data_[i] = other.data_[i];
        }
        data_[size_] = '\0';
    }

    // Move constructor
    MyString(MyString&& other) noexcept
        : data_(other.data_), size_(other.size_), capacity_(other.capacity_) {
        other.data_ = nullptr;
        other.size_ = 0;
        other.capacity_ = 0;
    }

    // Substring constructor
    MyString(const MyString& str, size_type pos, size_type len = npos)
        : data_(nullptr), size_(0), capacity_(0) {
        if (pos > str.size_) {
            reallocate(1);
            data_[0] = '\0';
            return;
        }

        size_ = (len == npos || pos + len > str.size_) ? str.size_ - pos : len;
        reallocate(size_ + 1);

        for (unsigned int i = 0; i < size_; ++i) {
            data_[i] = str.data_[pos + i];
        }
        data_[size_] = '\0';
    }

    // Destructor
    ~MyString() { delete[] data_; }

    // Assignment operators
    // Copy assignment
    MyString& operator=(const MyString& other) {
        if (this != &other) {
            delete[] data_;

            size_ = other.size_;
            capacity_ = size_ + 1;
            data_ = new char[capacity_];

            for (unsigned int i = 0; i < size_; ++i) {
                data_[i] = other.data_[i];
            }
            data_[size_] = '\0';
        }
        return *this;
    }

    // Move assignment
    MyString& operator=(MyString&& other) noexcept {
        if (this != &other) {
            delete[] data_;

            data_ = other.data_;
            size_ = other.size_;
            capacity_ = other.capacity_;

            other.data_ = nullptr;
            other.size_ = 0;
            other.capacity_ = 0;
        }
        return *this;
    }

    // Assign from C-string
    MyString& operator=(const char* str) {
        delete[] data_;

        if (str == nullptr) {
            size_ = 0;
            capacity_ = 1;
            data_ = new char[1];
            data_[0] = '\0';
            return *this;
        }

        size_ = 0;
        while (str[size_] != '\0') {
            ++size_;
        }

        capacity_ = size_ + 1;
        data_ = new char[capacity_];

        for (unsigned int i = 0; i < size_; ++i) {
            data_[i] = str[i];
        }
        data_[size_] = '\0';

        return *this;
    }

    // Assign from character
    MyString& operator=(char c) {
        delete[] data_;

        size_ = 1;
        capacity_ = 2;
        data_ = new char[capacity_];

        data_[0] = c;
        data_[1] = '\0';

        return *this;
    }

    // Assign method
    MyString& assign(const MyString& str) { return *this = str; }

    MyString& assign(const char* str) { return *this = str; }

    MyString& assign(const char* str, size_type n) {
        delete[] data_;

        size_ = 0;
        while (size_ < n && str[size_] != '\0') {
            ++size_;
        }

        capacity_ = size_ + 1;
        data_ = new char[capacity_];

        for (unsigned int i = 0; i < size_; ++i) {
            data_[i] = str[i];
        }
        data_[size_] = '\0';

        return *this;
    }

    MyString& assign(size_type n, char c) {
        delete[] data_;

        size_ = n;
        capacity_ = size_ + 1;
        data_ = new char[capacity_];

        for (unsigned int i = 0; i < size_; ++i) {
            data_[i] = c;
        }
        data_[size_] = '\0';

        return *this;
    }

    // Element access
    char& operator[](size_type pos) { return data_[pos]; }

    const char& operator[](size_type pos) const { return data_[pos]; }

    char& at(size_type pos) {
        if (pos >= size_) {
            // Out of range - in real implementation would throw an exception
            // For this implementation, we'll return a reference to a null
            // terminator
            return data_[size_];
        }
        return data_[pos];
    }

    const char& at(size_type pos) const {
        if (pos >= size_) {
            // Out of range - in real implementation would throw an exception
            return data_[size_];
        }
        return data_[pos];
    }

    char& front() { return data_[0]; }

    const char& front() const { return data_[0]; }

    char& back() { return data_[size_ - 1]; }

    const char& back() const { return data_[size_ - 1]; }

    const char* c_str() const { return data_; }

    const char* data() const { return data_; }

    // Capacity
    bool empty() const { return size_ == 0; }

    size_type size() const { return size_; }

    size_type length() const { return size_; }

    size_type max_size() const { return npos - 1; }

    void reserve(size_type new_cap = 0) {
        if (new_cap > capacity_) {
            reallocate(new_cap);
        }
    }

    size_type capacity() const { return capacity_; }

    void shrink_to_fit() {
        if (capacity_ > size_ + 1) {
            reallocate(size_ + 1);
        }
    }

    // Modifiers
    void clear() {
        size_ = 0;
        data_[0] = '\0';
    }

    MyString& insert(size_type pos, const MyString& str) {
        if (pos > size_) {
            return *this; // Invalid position
        }

        size_type new_size = size_ + str.size_;
        if (new_size + 1 > capacity_) {
            // Need to reallocate - we'll do it in a way that we don't lose data
            char* new_data = new char[new_size + 1];

            // Copy first part
            for (size_type i = 0; i < pos; ++i) {
                new_data[i] = data_[i];
            }

            // Copy inserted string
            for (size_type i = 0; i < str.size_; ++i) {
                new_data[pos + i] = str.data_[i];
            }

            // Copy second part
            for (size_type i = pos; i < size_; ++i) {
                new_data[i + str.size_] = data_[i];
            }

            new_data[new_size] = '\0';

            delete[] data_;
            data_ = new_data;
            size_ = new_size;
            capacity_ = new_size + 1;
        } else {
            // We have enough capacity, just shift and insert
            for (size_type i = size_; i > pos; --i) {
                data_[i + str.size_ - 1] = data_[i - 1];
            }

            for (size_type i = 0; i < str.size_; ++i) {
                data_[pos + i] = str.data_[i];
            }

            size_ = new_size;
            data_[size_] = '\0';
        }

        return *this;
    }

    MyString& insert(size_type pos, const char* s) {
        if (pos > size_) {
            return *this; // Invalid position
        }

        size_type len = 0;
        while (s[len] != '\0') {
            ++len;
        }

        size_type new_size = size_ + len;
        if (new_size + 1 > capacity_) {
            // Need to reallocate
            char* new_data = new char[new_size + 1];

            // Copy first part
            for (size_type i = 0; i < pos; ++i) {
                new_data[i] = data_[i];
            }

            // Copy inserted string
            for (size_type i = 0; i < len; ++i) {
                new_data[pos + i] = s[i];
            }

            // Copy second part
            for (size_type i = pos; i < size_; ++i) {
                new_data[i + len] = data_[i];
            }

            new_data[new_size] = '\0';

            delete[] data_;
            data_ = new_data;
            size_ = new_size;
            capacity_ = new_size + 1;
        } else {
            // We have enough capacity
            for (size_type i = size_; i > pos; --i) {
                data_[i + len - 1] = data_[i - 1];
            }

            for (size_type i = 0; i < len; ++i) {
                data_[pos + i] = s[i];
            }

            size_ = new_size;
            data_[size_] = '\0';
        }

        return *this;
    }

    MyString& insert(size_type pos, size_type n, char c) {
        if (pos > size_) {
            return *this; // Invalid position
        }

        size_type new_size = size_ + n;
        if (new_size + 1 > capacity_) {
            // Need to reallocate
            char* new_data = new char[new_size + 1];

            // Copy first part
            for (size_type i = 0; i < pos; ++i) {
                new_data[i] = data_[i];
            }

            // Insert repeated character
            for (size_type i = 0; i < n; ++i) {
                new_data[pos + i] = c;
            }

            // Copy second part
            for (size_type i = pos; i < size_; ++i) {
                new_data[i + n] = data_[i];
            }

            new_data[new_size] = '\0';

            delete[] data_;
            data_ = new_data;
            size_ = new_size;
            capacity_ = new_size + 1;
        } else {
            // We have enough capacity
            for (size_type i = size_; i > pos; --i) {
                data_[i + n - 1] = data_[i - 1];
            }

            for (size_type i = 0; i < n; ++i) {
                data_[pos + i] = c;
            }

            size_ = new_size;
            data_[size_] = '\0';
        }

        return *this;
    }

    MyString& erase(size_type pos = 0, size_type len = npos) {
        if (pos >= size_) {
            return *this; // Invalid position
        }

        size_type count =
            (len == npos || pos + len > size_) ? size_ - pos : len;
        for (size_type i = pos; i < size_ - count; ++i) {
            data_[i] = data_[i + count];
        }

        size_ -= count;
        data_[size_] = '\0';

        return *this;
    }

    void push_back(char c) {
        if (size_ + 1 >= capacity_) {
            reallocate(capacity_ * 2);
        }

        data_[size_] = c;
        ++size_;
        data_[size_] = '\0';
    }

    void pop_back() {
        if (size_ > 0) {
            --size_;
            data_[size_] = '\0';
        }
    }

    MyString& append(const MyString& str) {
        if (size_ + str.size_ >= capacity_) {
            reallocate((size_ + str.size_) * 2);
        }

        for (size_type i = 0; i < str.size_; ++i) {
            data_[size_ + i] = str.data_[i];
        }

        size_ += str.size_;
        data_[size_] = '\0';

        return *this;
    }

    MyString& append(const char* s) {
        size_type len = 0;
        while (s[len] != '\0') {
            ++len;
        }

        if (size_ + len >= capacity_) {
            reallocate((size_ + len) * 2);
        }

        for (size_type i = 0; i < len; ++i) {
            data_[size_ + i] = s[i];
        }

        size_ += len;
        data_[size_] = '\0';

        return *this;
    }

    MyString& append(size_type n, char c) {
        if (size_ + n >= capacity_) {
            reallocate((size_ + n) * 2);
        }

        for (size_type i = 0; i < n; ++i) {
            data_[size_ + i] = c;
        }

        size_ += n;
        data_[size_] = '\0';

        return *this;
    }

    MyString& operator+=(const MyString& str) { return append(str); }

    MyString& operator+=(const char* s) { return append(s); }

    MyString& operator+=(char c) {
        push_back(c);
        return *this;
    }

    MyString& replace(size_type pos, size_type len, const MyString& str) {
        erase(pos, len);
        insert(pos, str);
        return *this;
    }

    MyString& replace(size_type pos, size_type len, const char* s) {
        erase(pos, len);
        insert(pos, s);
        return *this;
    }

    MyString& replace(size_type pos, size_type len, size_type n, char c) {
        erase(pos, len);
        insert(pos, n, c);
        return *this;
    }

    void swap(MyString& other) {
        char* temp_data = data_;
        size_type temp_size = size_;
        size_type temp_capacity = capacity_;

        data_ = other.data_;
        size_ = other.size_;
        capacity_ = other.capacity_;

        other.data_ = temp_data;
        other.size_ = temp_size;
        other.capacity_ = temp_capacity;
    }

    void resize(size_type n, char c = '\0') {
        if (n < size_) {
            size_ = n;
            data_[size_] = '\0';
        } else if (n > size_) {
            if (n >= capacity_) {
                reallocate(n + 1);
            }

            for (size_type i = size_; i < n; ++i) {
                data_[i] = c;
            }

            size_ = n;
            data_[size_] = '\0';
        }
    }

    // String operations
    MyString substr(size_type pos = 0, size_type len = npos) const {
        return MyString(*this, pos, len);
    }

    size_type copy(char* s, size_type len, size_type pos = 0) const {
        if (pos >= size_) {
            return 0;
        }

        size_type count = (pos + len > size_) ? size_ - pos : len;
        for (size_type i = 0; i < count; ++i) {
            s[i] = data_[pos + i];
        }

        return count;
    }

    size_type find(const MyString& str, size_type pos = 0) const {
        if (pos >= size_ || str.size_ > size_ - pos) {
            return npos;
        }

        for (size_type i = pos; i <= size_ - str.size_; ++i) {
            size_type j;
            for (j = 0; j < str.size_; ++j) {
                if (data_[i + j] != str.data_[j]) {
                    break;
                }
            }

            if (j == str.size_) {
                return i;
            }
        }

        return npos;
    }

    size_type find(const char* s, size_type pos = 0) const {
        size_type len = 0;
        while (s[len] != '\0') {
            ++len;
        }

        if (pos >= size_ || len > size_ - pos) {
            return npos;
        }

        for (size_type i = pos; i <= size_ - len; ++i) {
            size_type j;
            for (j = 0; j < len; ++j) {
                if (data_[i + j] != s[j]) {
                    break;
                }
            }

            if (j == len) {
                return i;
            }
        }

        return npos;
    }

    size_type find(char c, size_type pos = 0) const {
        for (size_type i = pos; i < size_; ++i) {
            if (data_[i] == c) {
                return i;
            }
        }

        return npos;
    }

    size_type rfind(const MyString& str, size_type pos = npos) const {
        if (str.size_ > size_) {
            return npos;
        }

        if (pos >= size_) {
            pos = size_ - 1;
        }

        pos = (pos > size_ - str.size_) ? size_ - str.size_ : pos;

        for (int i = (int)pos; i >= 0; --i) {
            size_type j;
            for (j = 0; j < str.size_; ++j) {
                if (data_[i + j] != str.data_[j]) {
                    break;
                }
            }

            if (j == str.size_) {
                return i;
            }
        }

        return npos;
    }

    size_type rfind(const char* s, size_type pos = npos) const {
        size_type len = 0;
        while (s[len] != '\0') {
            ++len;
        }

        if (len > size_) {
            return npos;
        }

        if (pos >= size_) {
            pos = size_ - 1;
        }

        pos = (pos > size_ - len) ? size_ - len : pos;

        for (int i = (int)pos; i >= 0; --i) {
            size_type j;
            for (j = 0; j < len; ++j) {
                if (data_[i + j] != s[j]) {
                    break;
                }
            }

            if (j == len) {
                return i;
            }
        }

        return npos;
    }

    size_type rfind(char c, size_type pos = npos) const {
        if (size_ == 0) {
            return npos;
        }

        if (pos >= size_) {
            pos = size_ - 1;
        }

        for (int i = (int)pos; i >= 0; --i) {
            if (data_[i] == c) {
                return i;
            }
        }

        return npos;
    }

    size_type find_first_of(const MyString& str, size_type pos = 0) const {
        for (size_type i = pos; i < size_; ++i) {
            for (size_type j = 0; j < str.size_; ++j) {
                if (data_[i] == str.data_[j]) {
                    return i;
                }
            }
        }

        return npos;
    }

    size_type find_first_of(const char* s, size_type pos = 0) const {
        for (size_type i = pos; i < size_; ++i) {
            for (size_type j = 0; s[j] != '\0'; ++j) {
                if (data_[i] == s[j]) {
                    return i;
                }
            }
        }

        return npos;
    }

    size_type find_first_of(char c, size_type pos = 0) const {
        return find(c, pos);
    }

    size_type find_last_of(const MyString& str, size_type pos = npos) const {
        if (size_ == 0) {
            return npos;
        }

        if (pos >= size_) {
            pos = size_ - 1;
        }

        for (int i = (int)pos; i >= 0; --i) {
            for (size_type j = 0; j < str.size_; ++j) {
                if (data_[i] == str.data_[j]) {
                    return i;
                }
            }
        }

        return npos;
    }

    size_type find_last_of(const char* s, size_type pos = npos) const {
        if (size_ == 0) {
            return npos;
        }

        if (pos >= size_) {
            pos = size_ - 1;
        }

        for (int i = (int)pos; i >= 0; --i) {
            for (size_type j = 0; s[j] != '\0'; ++j) {
                if (data_[i] == s[j]) {
                    return i;
                }
            }
        }

        return npos;
    }

    size_type find_last_of(char c, size_type pos = npos) const {
        return rfind(c, pos);
    }

    size_type find_first_not_of(const MyString& str, size_type pos = 0) const {
        for (size_type i = pos; i < size_; ++i) {
            bool found = false;
            for (size_type j = 0; j < str.size_; ++j) {
                if (data_[i] == str.data_[j]) {
                    found = true;
                    break;
                }
            }

            if (!found) {
                return i;
            }
        }

        return npos;
    }

    size_type find_first_not_of(const char* s, size_type pos = 0) const {
        for (size_type i = pos; i < size_; ++i) {
            bool found = false;
            for (size_type j = 0; s[j] != '\0'; ++j) {
                if (data_[i] == s[j]) {
                    found = true;
                    break;
                }
            }

            if (!found) {
                return i;
            }
        }

        return npos;
    }

    size_type find_first_not_of(char c, size_type pos = 0) const {
        for (size_type i = pos; i < size_; ++i) {
            if (data_[i] != c) {
                return i;
            }
        }

        return npos;
    }

    size_type find_last_not_of(const MyString& str,
                               size_type pos = npos) const {
        if (size_ == 0) {
            return npos;
        }

        if (pos >= size_) {
            pos = size_ - 1;
        }

        for (int i = (int)pos; i >= 0; --i) {
            bool found = false;
            for (size_type j = 0; j < str.size_; ++j) {
                if (data_[i] == str.data_[j]) {
                    found = true;
                    break;
                }
            }

            if (!found) {
                return i;
            }
        }

        return npos;
    }

    size_type find_last_not_of(const char* s, size_type pos = npos) const {
        if (size_ == 0) {
            return npos;
        }

        if (pos >= size_) {
            pos = size_ - 1;
        }

        for (int i = (int)pos; i >= 0; --i) {
            bool found = false;
            for (size_type j = 0; s[j] != '\0'; ++j) {
                if (data_[i] == s[j]) {
                    found = true;
                    break;
                }
            }

            if (!found) {
                return i;
            }
        }

        return npos;
    }

    size_type find_last_not_of(char c, size_type pos = npos) const {
        if (size_ == 0) {
            return npos;
        }

        if (pos >= size_) {
            pos = size_ - 1;
        }

        for (int i = (int)pos; i >= 0; --i) {
            if (data_[i] != c) {
                return i;
            }
        }

        return npos;
    }

    int compare(const MyString& str) const {
        size_type min_size = size_ < str.size_ ? size_ : str.size_;

        for (size_type i = 0; i < min_size; ++i) {
            if (data_[i] < str.data_[i]) {
                return -1;
            } else if (data_[i] > str.data_[i]) {
                return 1;
            }
        }

        if (size_ < str.size_) {
            return -1;
        } else if (size_ > str.size_) {
            return 1;
        } else {
            return 0;
        }
    }

    int compare(const char* s) const {
        size_type len = 0;
        while (s[len] != '\0') {
            ++len;
        }

        size_type min_size = size_ < len ? size_ : len;

        for (size_type i = 0; i < min_size; ++i) {
            if (data_[i] < s[i]) {
                return -1;
            } else if (data_[i] > s[i]) {
                return 1;
            }
        }

        if (size_ < len) {
            return -1;
        } else if (size_ > len) {
            return 1;
        } else {
            return 0;
        }
    }
};

// Non-member functions
MyString operator+(const MyString& lhs, const MyString& rhs) {
    MyString result(lhs);
    result += rhs;
    return result;
}

MyString operator+(const MyString& lhs, const char* rhs) {
    MyString result(lhs);
    result += rhs;
    return result;
}

MyString operator+(const char* lhs, const MyString& rhs) {
    MyString result(lhs);
    result += rhs;
    return result;
}

MyString operator+(const MyString& lhs, char rhs) {
    MyString result(lhs);
    result += rhs;
    return result;
}

MyString operator+(char lhs, const MyString& rhs) {
    MyString result(1, lhs);
    result += rhs;
    return result;
}

// Comparison operators
bool operator==(const MyString& lhs, const MyString& rhs) {
    return lhs.compare(rhs) == 0;
}

bool operator==(const MyString& lhs, const char* rhs) {
    return lhs.compare(rhs) == 0;
}

bool operator==(const char* lhs, const MyString& rhs) {
    return rhs.compare(lhs) == 0;
}

bool operator!=(const MyString& lhs, const MyString& rhs) {
    return lhs.compare(rhs) != 0;
}

bool operator!=(const MyString& lhs, const char* rhs) {
    return lhs.compare(rhs) != 0;
}

bool operator!=(const char* lhs, const MyString& rhs) {
    return rhs.compare(lhs) != 0;
}

bool operator<(const MyString& lhs, const MyString& rhs) {
    return lhs.compare(rhs) < 0;
}

bool operator<(const MyString& lhs, const char* rhs) {
    return lhs.compare(rhs) < 0;
}

bool operator<(const char* lhs, const MyString& rhs) {
    return rhs.compare(lhs) > 0;
}

bool operator<=(const MyString& lhs, const MyString& rhs) {
    return lhs.compare(rhs) <= 0;
}

bool operator<=(const MyString& lhs, const char* rhs) {
    return lhs.compare(rhs) <= 0;
}

bool operator<=(const char* lhs, const MyString& rhs) {
    return rhs.compare(lhs) >= 0;
}

bool operator>(const MyString& lhs, const MyString& rhs) {
    return lhs.compare(rhs) > 0;
}

bool operator>(const MyString& lhs, const char* rhs) {
    return lhs.compare(rhs) > 0;
}

bool operator>(const char* lhs, const MyString& rhs) {
    return rhs.compare(lhs) < 0;
}

bool operator>=(const MyString& lhs, const MyString& rhs) {
    return lhs.compare(rhs) >= 0;
}

bool operator>=(const MyString& lhs, const char* rhs) {
    return lhs.compare(rhs) >= 0;
}

bool operator>=(const char* lhs, const MyString& rhs) {
    return rhs.compare(lhs) <= 0;
}

// Swap function
void swap(MyString& lhs, MyString& rhs) { lhs.swap(rhs); }