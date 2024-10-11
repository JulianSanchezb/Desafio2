#ifndef STATION_H
#define STATION_H

#include<string>

class station{
    //atributos de la estación
private:
    std::string stationName;
    int stationCode;
    std::string stationManager;
    std::string  stationRegion;
    float coordinatesGps[2];
    float stationTank[3];
    int *stationSuppliers=nullptr;


public:
    //métodos de la estación
    station(std::string,int,std::string,std::string,float,float,float,float,float,int);//constructor
    ~station();//destructor
    //getters
    std::string getStationName();
    int getStationCode();
    std::string getStationManager();
    std::string getStationRegion();
    float*  getCoordinatesGps();
    float*  getStationTank();
    int*    getSuppliers();
    //setters
    void setStationName(std::string stationname);
    void setStationCode(int code);
    void setStationManager(std::string managerName);
    void setStationRegion(std::string regionName);
    void setCoordinatesGps(float lat,float lon);
    void setStationTank(float reg ,float ec,float ex);
    void setSuppliers(int maxsuppliers);

};
#endif // STATION_H
