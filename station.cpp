#include"station.h"
#include<iostream>

using namespace std;

station::station(string name, int codeOne, string manager, string region, float latitude, float length, float regular, float eco, float extra, int *Suppliers, int cant, int precioR, int precioE, int precioEx){
    stationName=name;
    stationCode=codeOne;
    stationManager=manager;
    stationRegion=region;
    coordinatesGps[0]=latitude;
    coordinatesGps[1]=length;
    stationTank[0]=regular;
    stationTank[1]=eco;
    stationTank[2]=extra;
    stationSuppliers = new int [cant];
    for(int i = 0;i < cant;i++){
        stationSuppliers[i] = Suppliers[i];
    }
    cantidadsurtidores = cant;
    precioGas[0] = precioR;
    precioGas[1] = precioE;
    precioGas[2] = precioEx;
}
//destructor
station::~station(){
    delete[] stationSuppliers;
}

//getters
string station::getStationName(){
    return stationName;
}
int station::getStationCode(){
    return stationCode;
}
string station::getStationManager(){
    return stationManager;
}
string station::getStationRegion(){
    return stationRegion;
}
float* station::getCoordinatesGps(){
    return coordinatesGps;
}
float* station::getStationTank(){
    return stationTank;
}
int* station::getSuppliers(){
    return stationSuppliers;
}
int station::getSurtidores(){
    return cantidadsurtidores;
}
int* station::getPrice(){
    return precioGas;
}
//setters
void station::setStationName(string stationname){
    stationName=stationname;
}
void station::setStationCode(int code){
    stationCode=code;

}
void station:: setStationManager(string managerName){
    stationManager=managerName;
}
void station:: setStationRegion(string regionName){
    stationRegion=regionName;
}
void station::setCoordinatesGps(float lat,float lon){
    coordinatesGps[0]=lat;
    coordinatesGps[1]=lon;
}
void station::setStationTank(float reg ,float ec,float ex){
    stationTank[0]=reg;
    stationTank[1]=ec;
    stationTank[2]=ex;
}

void station::setSuppliers(int *Suppliers,int cant){
    if (stationSuppliers != nullptr) {
        delete[] stationSuppliers;  // Libera memoria anterior
    }
    stationSuppliers = new int [cant];
    for(int i = 0;i < cant;i++){
        stationSuppliers[i] = Suppliers[i];
    }
    cantidadsurtidores = cant;
}
void station::setPrecioGas(int precioR, int precioE, int precioEx){
    precioGas[0] = precioE;
    precioGas[1] = precioR;
    precioGas[2] = precioEx;
}
