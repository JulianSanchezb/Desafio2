#ifndef FUNCIONES_H
#define FUNCIONES_H

#include"station.h"
#include"pump.h"

void stationin(station *estaciones,int& c);
void updateStation(station* arr,int& c);
void deleteStation(int* arr, int& c);
void definitiveD(int* arr, int &c);
void crearSurtidor(float cod, unsigned int code);
void deleteSurtidor(float cod, int code);
void historialVentas();
void registroGas();
void agregarLinea(int n);
void eliminarLinea(const string& n);
void surtidor(float cod,unsigned int code);
void cambiarEstado(const string& n);
float* sumCombusVentas(int cod);
float* parcialTotal(int code);
void modificarPreciosEstacion(int cod, int nuevosPrecios[3]);
void archivoPostventa(int posicion, float resta);
string* surtidoresDisponibles(const string& codigoEstacion, int& cantidadSurtidores);
void archivoPostventa2(float codS, string fecha, int cant, string tip, int dni, float precio);
int precioVenta(int cod, int posicion, int cant);
pump simularVenta(int codStation, pump* arr, int& c);

#endif // FUNCIONES_H
