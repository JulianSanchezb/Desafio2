#ifndef STATION_H
#define STATION_H

#include<string>

using namespace std;

class station{
    //atributos de la estación
private:
    string stationName;
    int stationCode;
    string stationManager;
    string  stationRegion;
    float coordinatesGps[2];
    float stationTank[3];
    int *stationSuppliers;
    int cantidadsurtidores;
    int precioGas[3];

public:
    //métodos de la estación
    station() {
        stationName = "";
        stationCode = 0;
        stationManager = "";
        stationRegion = "";
        coordinatesGps[0] = 0.0;
        coordinatesGps[1] = 0.0;
        stationTank[0] = 0.0;
        stationTank[1] = 0.0;
        stationTank[2] = 0.0;
        stationSuppliers = nullptr;
        cantidadsurtidores = 0;
        precioGas[0]= 0;
        precioGas[1]= 0;
        precioGas[2]= 0;
    }
    station(string, int, string, string, float, float, float, float, float, int*, int,int,int,int);//constructor
    ~station();//destructor
    //getters
    string getStationName();
    int getStationCode();
    string getStationManager();
    string getStationRegion();
    float* getCoordinatesGps();
    float* getStationTank();
    int* getSuppliers();
    int getSurtidores();
    int *getPrice();
    //setters
    void setStationName(string stationname);
    void setStationCode(int code);
    void setStationManager(string managerName);
    void setStationRegion(string regionName);
    void setCoordinatesGps(float lat,float lon);
    void setStationTank(float reg ,float ec,float ex);
    void setSuppliers(int *suppliers, int cant);
    void setPrecioGas(int precioR, int precioE, int precioEx);
};
#endif // STATION_H
