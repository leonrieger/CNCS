#include <iostream>
#include <memory>
#include <sstream>
#include <string>
#include <type_traits>
#include <vector>

// ===== Base Class =====
class Field {
public:
    virtual void process() const = 0;
    virtual std::string getValueAsString() const = 0;
    virtual std::unique_ptr<Field> clone() const = 0;
    virtual ~Field() = default;
};

// ===== Derived Class A =====
class FieldA : public Field {
private:
    int value;

public:
    FieldA(int v) : value(v) {}

    std::string getValueAsString() const override {
        return std::to_string(value);
    }

    void process() const override {
        std::cout << "Processing FieldA: " << value << "\n";
    }

    std::unique_ptr<Field> clone() const override {
        return std::make_unique<FieldA>(*this);
    }
};

// ===== Derived Class B =====
class FieldB : public Field {
private:
    std::string data;

public:
    FieldB(std::string d) : data(std::move(d)) {}

    std::string getValueAsString() const override { return data; }

    void process() const override {
        std::cout << "Processing FieldB: " << data << "\n";
    }

    std::unique_ptr<Field> clone() const override {
        return std::make_unique<FieldB>(*this);
    }
};

// ===== Derived Class C =====
class FieldC : public Field {
private:
    double number;

public:
    FieldC(double n) : number(n) {}

    std::string getValueAsString() const override {
        std::ostringstream oss;
        oss << number;
        return oss.str();
    }

    void process() const override {
        std::cout << "Processing FieldC: " << number << "\n";
    }

    std::unique_ptr<Field> clone() const override {
        return std::make_unique<FieldC>(*this);
    }
};

// ===== Function to Store and Process =====
template <typename... Fields>
void storeAndProcessFields(std::vector<std::unique_ptr<Field>>& fieldVec,
                           const Fields&... fields) {
    static_assert((std::is_base_of<Field, Fields>::value && ...),
                  "All arguments must be derived from Field");

    // Clone and store
    (fieldVec.push_back(fields.clone()), ...);

    // Process and access values
    for (const auto& field : fieldVec) {
        field->process();
        std::cout << "Value (as string): " << field->getValueAsString() << "\n";
    }
}

// ===== Main Function =====
int main() {
    FieldA a(123);
    FieldB b("Hello World");
    FieldC c(3.14159);

    std::vector<std::unique_ptr<Field>> storedFields;
    storeAndProcessFields(storedFields, a, b, c);

    return 0;
}