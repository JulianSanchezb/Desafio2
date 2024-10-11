#ifndef PUMP_H
#define PUMP_H

#include<string>

class pump{
private:
    int code;
    int model;
    bool state;
    std::string date;
    float amountGas;
    int typeGas;
    int methodPay;
    int dni;
    float total;
public:
    pump(int,int,bool,std::string,float,int,int,int,float);//Constructor
    ~pump();//Destructor
    //Getters
    int getCode();
    int getModel();
    bool getState();
    std::string getDate();
    float getAmountGas();
    int getTypeGas();
    int getMethodPay();
    int getDni();
    float getTotal();
    //Setters
    void setCode(int _code);
    void setModel(int _model);
    void setState(bool _state);
    void setDate(std::string _date);
    void setAmountgas(float _amount);
    void setTypegas(int _type);
    void setMethodPay(int _method);
    void setDni(int _dni);
    void setTotal(float _total);
};
#endif // PUMP_H
