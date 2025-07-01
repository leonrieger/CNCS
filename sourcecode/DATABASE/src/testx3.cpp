#include <iostream>
#include <memory>
#include <string>
#include <type_traits>
#include <variant>
#include <vector>

// ===== Custom Struct =====
struct MyStruct {
    int id;
    std::string name;
};

// For printing MyStruct
std::ostream& operator<<(std::ostream& os, const MyStruct& s) {
    os << "{id: " << s.id << ", name: " << s.name << "}";
    return os;
}

// ===== Base Class =====
using ValueType = std::variant<std::string, int, double, MyStruct>;

class Field {
public:
    virtual void process() const = 0;
    virtual ValueType getValue() const = 0;
    virtual std::unique_ptr<Field> clone() const = 0;
    virtual ~Field() = default;
};

// ===== Derived Class A (int) =====
class FieldA : public Field {
private:
    int value;

public:
    FieldA(int v) : value(v) {}

    void process() const override { std::cout << "Processing FieldA\n"; }

    ValueType getValue() const override { return value; }

    std::unique_ptr<Field> clone() const override {
        return std::make_unique<FieldA>(*this);
    }
};

// ===== Derived Class B (string) =====
class FieldB : public Field {
private:
    std::string data;

public:
    FieldB(std::string d) : data(std::move(d)) {}

    void process() const override { std::cout << "Processing FieldB\n"; }

    ValueType getValue() const override { return data; }

    std::unique_ptr<Field> clone() const override {
        return std::make_unique<FieldB>(*this);
    }
};

// ===== Derived Class C (double) =====
class FieldC : public Field {
private:
    double number;

public:
    FieldC(double n) : number(n) {}

    void process() const override { std::cout << "Processing FieldC\n"; }

    ValueType getValue() const override { return number; }

    std::unique_ptr<Field> clone() const override {
        return std::make_unique<FieldC>(*this);
    }
};

// ===== Derived Class D (struct) =====
class FieldD : public Field {
private:
    MyStruct info;

public:
    FieldD(MyStruct s) : info(std::move(s)) {}

    void process() const override { std::cout << "Processing FieldD\n"; }

    ValueType getValue() const override { return info; }

    std::unique_ptr<Field> clone() const override {
        return std::make_unique<FieldD>(*this);
    }
};

// ===== Helper: Print a variant =====
void printValue(const ValueType& val) {
    std::visit([](const auto& v) { std::cout << "Value: " << v << "\n"; }, val);
}

// ===== Variadic Function =====
template <typename... Fields>
void storeAndProcessFields(std::vector<std::unique_ptr<Field>>& fieldVec,
                           const Fields&... fields) {
    static_assert((std::is_base_of<Field, Fields>::value && ...),
                  "All arguments must be derived from Field");

    (fieldVec.push_back(fields.clone()), ...);

    for (const auto& field : fieldVec) {
        field->process();
        printValue(field->getValue());
    }
}

// ===== Main =====
int main() {
    FieldA a(42);
    FieldB b("Hello Variant");
    FieldC c(3.14159);
    FieldD d({1, "StructField"});

    std::vector<std::unique_ptr<Field>> storedFields;
    storeAndProcessFields(storedFields, a, b, c, d);

    return 0;
}
