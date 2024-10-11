#include"pump.h"
#include<iostream>

using namespace std;

pump::pump(int code_, int model_, bool state_, string date_, float amount_, int type_, int method_, int dni_, float total_){
    code = code_;
    model = model_;
    state = state_;
    date = date_;
    amountGas = amount_;
    typeGas = type_;
    methodPay = method_;
    dni = dni_;
    total = total_;
}
pump::~pump(){}//Destructor
//Getters
int pump::getCode(){
    return code;
}
int pump::getModel(){
    return model;
}
bool pump::getState(){
    return state;
}
string pump::getDate(){
    return date;
}
float pump::getAmountGas(){
    return amountGas;
}
int pump::getTypeGas(){
    return typeGas;
}
int pump::getMethodPay(){
    return methodPay;
}
int pump::getDni(){
    return dni;
}
float pump::getTotal(){
    return total;
}

//Setters
void pump::setCode(int _code){
    code = _code;
}
void pump::setModel(int _model){
    model = _model;
}
void pump::setState(bool _state){
    state = _state;
}
void pump::setDate(string _date){
    date = _date;
}
void pump::setAmountgas(float _amount){
    amountGas = _amount;
}
void pump::setTypegas(int _type){
    typeGas = _type;
}
void pump::setMethodPay(int _method){
    methodPay = _method;
}
void pump::setDni(int _dni){
    dni = _dni;
}
void pump::setTotal(float _total){
    total = _total;
}
