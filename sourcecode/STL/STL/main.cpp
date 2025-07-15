#include "string.hpp"

#include <iostream>

// Sample test program for MyString class
int main() {
    // Create strings
    MyString s1;           // Default constructor
    MyString s2("Hello");  // From C-string
    MyString s3(5, 'a');   // 5 copies of 'a'
    MyString s4(s2);       // Copy constructor
    MyString s5(s2, 1, 2); // Substring constructor

    // Assignments
    s1 = "World";
    s1 = s2;
    s1 = 'X';

    // Element access
    char c1 = s2[0];              // operator[]
    char c2 = s2.at(1);           // at()
    char c3 = s2.front();         // front()
    char c4 = s2.back();          // back()
    const char* ptr = s2.c_str(); // c_str()

    // Modifiers
    s1.clear(); // clear()
    s1 = "Hello";
    s1.insert(1, "abc");          // insert()
    s1.erase(1, 3);               // erase()
    s1.push_back('!');            // push_back()
    s1.pop_back();                // pop_back()
    s1.append(" World");          // append()
    s1 += "!";                    // operator+=
    s1.replace(6, 5, "Universe"); // replace()
    s2.swap(s3);                  // swap()
    s1.resize(20, '-');           // resize()

    // String operations
    MyString sub = s1.substr(0, 5); // substr()
    char buffer[10];
    s1.copy(buffer, 5, 0);                    // copy()
    MyString::size_type pos1 = s1.find("lo"); // find()
    MyString::size_type pos2 = s1.rfind('l'); // rfind()

    // Comparison
    bool eq = (s1 == s2);     // operator==
    bool neq = (s1 != s2);    // operator!=
    bool lt = (s1 < s2);      // operator<
    bool gt = (s1 > s2);      // operator>
    int cmp = s1.compare(s2); // compare()

    // Concatenation
    MyString cat1 = s1 + s2; // operator+
    MyString cat2 = s1 + "abc";
    MyString cat3 = "abc" + s1;
    MyString cat4 = s1 + '!';
    MyString cat5 = '!' + s1;

    std::cout << s1.c_str() << "\n"
              << s2.c_str() << "\n"
              << s3.c_str() << "\n"
              << s4.c_str() << "\n"
              << s5.c_str();

    return 0;
}
