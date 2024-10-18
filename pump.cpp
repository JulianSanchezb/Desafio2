#include "pump.h"

// Constructor por defecto
pump::pump() : code(0), state(false), date(""), amountGas(0), typeGas(0), paymentMethod(0), dni(0), total(0) {}

// Constructor con parámetros
pump::pump(float code_, bool state_, string date_, float amount_, int type_, int method_, int dni_, float total_)
    : code(code_), state(state_), date(date_), amountGas(amount_), typeGas(type_), paymentMethod(method_), dni(dni_), total(total_) {}

// Getters
float pump::getCode() const { return code; }
bool pump::getState() const { return state; }
string pump::getDate() const { return date; }
float pump::getAmountGas() const { return amountGas; }
int pump::getTypeGas() const { return typeGas; }
int pump::getPaymentMethod() const { return paymentMethod; }
int pump::getDni() const { return dni; }
float pump::getTotal() const { return total; }

// Setters
void pump::setCode(float code_) { code = code_; }
void pump::setState(bool state_) { state = state_; }
void pump::setDate(const string& date_) { date = date_; }
void pump::setAmountGas(float amountGas_) { amountGas = amountGas_; }
void pump::setTypeGas(int typeGas_) { typeGas = typeGas_; }
void pump::setPaymentMethod(int paymentMethod_) { paymentMethod = paymentMethod_; }
void pump::setDni(int dni_) { dni = dni_; }
void pump::setTotal(float total_) { total = total_; }
