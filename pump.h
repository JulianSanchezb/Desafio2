#ifndef PUMP_H
#define PUMP_H

#include <string>

using namespace std;

class pump {
private:
    float code;
    bool state;
    string date;
    float amountGas;
    int typeGas;
    int paymentMethod;
    int dni;
    float total;

public:
    // Constructor por defecto
    pump();

    // Constructor con parámetros
    pump(float code_, bool state_, string date_, float amount_, int type_, int method_, int dni_, float total_);

    // Getters
    float getCode() const;
    bool getState() const;
    string getDate() const;
    float getAmountGas() const;
    int getTypeGas() const;
    int getPaymentMethod() const;
    int getDni() const;
    float getTotal() const;

    // Setters
    void setCode(float code_);
    void setState(bool state_);
    void setDate(const string& date_);
    void setAmountGas(float amountGas_);
    void setTypeGas(int typeGas_);
    void setPaymentMethod(int paymentMethod_);
    void setDni(int dni_);
    void setTotal(float total_);
};

#endif // PUMP_H
