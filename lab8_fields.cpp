#include <iostream>
#include <cmath>

// Physical constants
const double EPSILON_0 = 8.854e-12;   // Permittivity of free space (C^2 / N·m^2)
const double MU_0 = 4 * M_PI * 1e-7;  // Permeability of free space (T·m / A)



// Base class: Field

class Field {
protected:
    double *value; // pointer to array of 3 components (x, y, z)

public:
    // Default constructor: initializes components to zero
    Field() {
        value = new double[3];
        value[0] = 0.0;
        value[1] = 0.0;
        value[2] = 0.0;
    }

    // Parameterized constructor
    Field(double x, double y, double z) {
        value = new double[3];
        value[0] = x;
        value[1] = y;
        value[2] = z;
    }

    // Copy constructor
    Field(const Field &other) {
        value = new double[3];
        for (int i = 0; i < 3; i++) value[i] = other.value[i];
    }

    // Destructor
    virtual ~Field() {
        delete[] value;
    }

    // Prints vector components
    virtual void printMagnitude() const {
        std::cout << "Components: ("
                  << value[0] << ", "
                  << value[1] << ", "
                  << value[2] << ")" << std::endl;
    }
};



// Derived class: Electric Field

class ElectricField : public Field {
private:
    double E_calculated; // stores computed electric field magnitude

public:
    // Default constructor
    ElectricField() : Field(), E_calculated(0.0) {}

    // Parameterized constructor calls base class constructor
    ElectricField(double x, double y, double z)
        : Field(x, y, z), E_calculated(0.0) {}

    // Copy constructor
    ElectricField(const ElectricField &other)
        : Field(other), E_calculated(other.E_calculated) {}

    // Calculates Electric Field using Gauss's Law
    void calculateE(double Q, double r) {
        E_calculated = Q / (4 * M_PI * r * r * EPSILON_0);
    }

    double getE() const { return E_calculated; }

    // Overload '+' operator
    ElectricField operator+(const ElectricField &rhs) const {
        ElectricField result;
        for (int i = 0; i < 3; i++)
            result.value[i] = this->value[i] + rhs.value[i];
        return result;
    }

    // Overload '<<' operator
    friend std::ostream &operator<<(std::ostream &os, const ElectricField &ef) {
        os << "Electric Field components: ("
           << ef.value[0] << ", "
           << ef.value[1] << ", "
           << ef.value[2] << ")";
        return os;
    }
};



// Derived class: Magnetic Field

class MagneticField : public Field {
private:
    double B_calculated; // stores computed magnetic field magnitude

public:
    // Default constructor
    MagneticField() : Field(), B_calculated(0.0) {}

    // Parameterized constructor calls base class constructor
    MagneticField(double x, double y, double z)
        : Field(x, y, z), B_calculated(0.0) {}

    // Copy constructor
    MagneticField(const MagneticField &other)
        : Field(other), B_calculated(other.B_calculated) {}

    // Calculates Magnetic Field using Ampere's Law
    void calculateB(double I, double r) {
        B_calculated = I / (2 * M_PI * r * MU_0);
    }

    double getB() const { return B_calculated; }

    // Overload '+' operator
    MagneticField operator+(const MagneticField &rhs) const {
        MagneticField result;
        for (int i = 0; i < 3; i++)
            result.value[i] = this->value[i] + rhs.value[i];
        return result;
    }

    // Overload '<<' operator
    friend std::ostream &operator<<(std::ostream &os, const MagneticField &mf) {
        os << "Magnetic Field components: ("
           << mf.value[0] << ", "
           << mf.value[1] << ", "
           << mf.value[2] << ")";
        return os;
    }
};



// Main Function (Demonstration)

int main() {
    // Create objects using constructors
    ElectricField e1(0, 1e5, 1e3);
    ElectricField e2(1e3, 2e3, 3e3);
    MagneticField m1(2.0, 4.0, 6.0);
    MagneticField m2(1.0, 1.0, 1.0);

    std::cout << "---- Field Components ----" << std::endl;
    e1.printMagnitude();
    m1.printMagnitude();

    // Calculate Electric and Magnetic fields using laws
    e1.calculateE(2e-6, 0.05); // Q=2μC, r=5cm
    m1.calculateB(10.0, 0.01); // I=10A, r=1cm

    std::cout << "\n---- Calculated Values ----" << std::endl;
    std::cout << "Electric Field (Gauss's Law): " << e1.getE() << " N/C" << std::endl;
    std::cout << "Magnetic Field (Ampere's Law): " << m1.getB() << " T" << std::endl;

    // Demonstrate operator overloads
    ElectricField e3 = e1 + e2;
    MagneticField m3 = m1 + m2;

    std::cout << "\n---- Operator Overload Demonstrations ----" << std::endl;
    std::cout << e3 << std::endl;
    std::cout << m3 << std::endl;

    return 0;
}
