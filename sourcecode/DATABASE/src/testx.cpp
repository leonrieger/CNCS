#include <iostream>
#include <memory>
#include <type_traits>
#include <vector>

// ===== Base Class =====
class Field {
public:
    virtual void process() const = 0;
    virtual std::unique_ptr<Field> clone() const = 0;
    virtual ~Field() = default;
};

// ===== Derived Class A =====
class FieldA : public Field {
private:
    int value;

public:
    FieldA(int v) : value(v) {}

    int getValue() const { return value; }

    void process() const override {
        std::cout << "Processing FieldA with value: " << value << "\n";
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

    std::string getData() const { return data; }

    void process() const override {
        std::cout << "Processing FieldB with data: " << data << "\n";
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

    double getNumber() const { return number; }

    void process() const override {
        std::cout << "Processing FieldC with number: " << number << "\n";
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

    // Process all stored
    for (const auto& field : fieldVec) {
        field->process();
    }
}

// ===== Main Function =====
int main() {
    FieldA a(42);
    FieldB b("Hello");
    FieldC c(3.14);

    std::vector<std::unique_ptr<Field>> storedFields;

    storeAndProcessFields(storedFields, a, b, c);

    // Accessing private members via public getters
    std::cout << "FieldA original value: " << a.getValue() << "\n";
    std::cout << "FieldB original data: " << b.getData() << "\n";
    std::cout << "FieldC original number: " << c.getNumber() << "\n";

    return 0;
}
