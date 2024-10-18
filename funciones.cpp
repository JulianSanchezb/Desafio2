#include<iostream>
#include <iomanip>
#include <ctime>
#include <cstdlib>
#include <string>
#include <sstream>
#include <fstream>
#include <random>

#include"station.h"
#include"pump.h"
#include"funciones.h"

using namespace std;

//Añadir estacion
void stationin(station *estaciones, int &c){
    random_device rd;
    mt19937 gen(rd());

    ifstream filei;
    string line,aux;
    int l = 1,r = 0;
    unsigned int code;

    string name = "";
    string manager = "";
    string region = "";
    float coordinates[2];
    float tank[3];
    int precios[3];

    filei.open("estaciones.txt");
    if(!filei.is_open()){
        cout<<"Error al abrir Stations.txt\n";
    }

    //Asignacion del codigo de la estacion
    while(getline(filei,line)){
        if(l == 2){
            if(c == 0){
                aux = line.substr(0,(line.find('-')+1));
                code = stoi(aux) + 1;
            }else{
                code = estaciones[c - 1].getStationCode() + 1;
            }
        }
        if(line.empty()){
            l = 0;
        }
        l++;
    }
    //Asignacion de nombre de la estacion
    while(name == ""){
        cout<<"\nIngrese el nombre de la estacion \n";
        getline(cin,name);
        if(name == ""){
            cout<<"\nNombre invalido\n";
        }
    }
    //Asignacion de gerente
    while(manager == ""){
        cout<<"\nIngrese el nombre del gerente\n";
        getline(cin,manager);
        if(manager == ""){
            cout<<"\nNombre invalido\n";
        }
    }
    //Asignacion de region
    while(r < 1 || r > 3){
        cout<<"\nIngrese la region\n1. Norte\n2. Centro\n3. sur\n";
        cin>>r;
        if(r < 1 || r > 3){
            cout<<"\nRegion invalida\n";
        }else if(r == 1){
            region = "norte";
        }else if(r == 2){
            region = "centro";
        }else if(r == 3){
            region = "sur";
        }
    }
    //Asignacion de coordenadas
    for(int i = 0;i<=1;i++){
        uniform_real_distribution<float> distribucion(0.0, 90.0);
        if(i == 0){
            coordinates[i] = round(distribucion(gen) * 100)/100;
        }else{
            coordinates[i] = (round(distribucion(gen) * 100)/100) * (-1);
        }
    }
    //Asignacion de capacidad del tanque
    for(int i = 0;i < 3;i++){
        uniform_real_distribution<float> distribucion(100.0, 200.0);
        tank[i] = {round(distribucion(gen) * 100)/100};
    }
    //Asignacion de surtidores
    unsigned short int cant = 0;
    while(cant < 2 || cant > 12){
        cout<<"Ingrese la cantidad de surtidores en la estacion\n";
        cin>>cant;
        if(cant < 2 || cant > 12){
            cout<<"Fuera de rango, debe ser minimo 2 y maximo 12 surtidores\n";
        }
    }
    //Asignacion precios
    filei.clear();
    filei.seekg(0);
    l = 1;
    while(getline(filei,line)){
        if(l == 1){
            aux = line.substr(0,(line.find('$')));
        }
        if(l == 6){
            if(aux == region){
                size_t firstAsterisk = line.find('*');
                precios[0] = stoi(line.substr(0, firstAsterisk));

                size_t secondAsterisk = line.find('*', firstAsterisk + 1);
                precios[1] = stoi(line.substr(firstAsterisk + 1, secondAsterisk - firstAsterisk - 1));

                precios[2] = stoi(line.substr(secondAsterisk + 1));
            }
        }
        if(line.empty()){
            l = 0;
        }
        l++;
    }

    int *surtidores;
    surtidores = new int [cant];
    for(int i = 0;i < cant;i++){
        cout<<"Ingrese el modelo del surtidor numero "<<i+1<<"\n1. Super fast\n2. Super cool\n3. Super normal\n";
        cin>>surtidores[i];
        if(surtidores[i] < 1 || surtidores[i] > 3){
            cout<<"\n*Opcion invalida*\n";
            i--;
        }
    }

    filei.close();

    station estacion(name,code,manager,region,coordinates[0],coordinates[1],tank[0],tank[1],tank[2],surtidores,cant,precios[0],precios[1],precios[2]);
    estaciones[c] = estacion;
    c++;
}
//Actualizar estaciones en el archivo
void updateStation(station* arr,int& c){
    ofstream file;
    file.open("estaciones.txt",ios::app);
    if(!file.is_open()){
        cout<<"Error al abrir el archivo estaciones.txt"<<endl;
    }
    ofstream file2;
    file2.open("surtidor.txt",ios::app);
    if(!file2.is_open()){
        cout<<"Error al abrir el archivo estaciones.txt"<<endl;
    }

    for(int i = 0;i < c;i++){
        file<<"\n"<<arr[i].getStationRegion()<<"$"<<arr[i].getCoordinatesGps()[0]<<"$"<<arr[i].getCoordinatesGps()[1];
        file<<"\n"<<arr[i].getStationCode()<<"-"<<arr[i].getStationName()<<"-"<<arr[i].getStationManager()<<"\n";
        for(int j = 0;j < 3;j++){
            if(j != 2){
                file<<arr[i].getStationTank()[j]<<",";
            }else{
                file<<arr[i].getStationTank()[j]<<endl;
            }
        }
        int tam = arr[i].getSurtidores();
        for(int j = 0;j < tam;j++){
            if(j < tam-1){
                file<<arr[i].getStationCode()<<"."<<j+1<<"/";
            }else{
                file<<arr[i].getStationCode()<<"."<<j+1<<"\n";
            }
            file2<<arr[i].getStationCode()<<"."<<j+1<<"-"<<"true"<<endl;
        }
        for(int j = 0;j < 3;j++){
            if(j != 2){
                file<<arr[i].getStationTank()[j]<<"#";
            }else{
                file<<arr[i].getStationTank()[j]<<endl;
            }
        }
        for(int j = 0;j < 3;j++){
            if(j != 2){
                file<<arr[i].getPrice()[j]<<"*";
            }else{
                file<<arr[i].getPrice()[j]<<endl;
            }
        }
    }

    file.close();
    file2.close();
    c = 0;
    delete[] arr;
}
//Seleccionar estaciones a elminar
void deleteStation(int* arr, int& c){
    int estacion;
    do{
        cout<<"Ingrese el codigo de la estacion a eliminar\n";
        cin>>estacion;
    }while(estacion < 0);
    arr[c] = estacion;
    c++;
}
//Actualizar archivo con estaciones eliminadas
void definitiveD(int* arr, int& c){
    ifstream file,surtidores;
    ofstream temp("temp.txt");
    ofstream temp2("temp2.txt");
    string line, aux;
    int l = 1, code, count = 1, lineD[c],caux = 0,max = 0;

    file.open("estaciones.txt");
    surtidores.open("surtidor.txt");
    if(!file.is_open() || !temp.is_open() ||!surtidores.is_open()){
        cout<<"Error al abrir el archivo\n";
    }

    while(getline(file,line)){
        if(l == 2){
            aux = line.substr(0,(line.find('-')));
            code = stoi(aux);
            for(int i = 0;i < c;i++){
                if(arr[i] == code){
                    lineD[caux] = count - 1;
                    caux++;
                }
            }
        }
        count++;
        if(line.empty()){
            l = 0;
        }
        l++;
    }

    bool valueS = true,valuea = false;
    while(getline(surtidores,line)){
        aux = line.substr(0,(line.find('-')));
        code = stoi(aux);
        if(valuea == false){
            for(int i = 0;i < c;i++){
                if(arr[i] == code){
                    valuea = true;
                }
            }
        }
        if(valuea == true){
            aux = line.substr(line.find("-"));
            if(aux == "true"){
                valueS = false;
            }
        }
    }

    for (int i = 0; i < c - 1; i++) {
        for (int j = 0; j < c - i - 1; j++) {
            if (lineD[j] > lineD[j + 1]) {
                int temp = lineD[j];
                lineD[j] = lineD[j + 1];
                lineD[j + 1] = temp;
            }
        }
    }

    l = 1;
    count = 1;
    caux = 0;
    bool value = true;
    file.clear();
    file.seekg(0);
    while(getline(file,line)){
        if(l == 1){
            value = true;
            for(int i = caux;i < c;i++){
                if(lineD[i] == count){
                    value = false;
                    caux++;
                }
            }
        }
        if(value == true){
            temp<<line<<"\n";
        }
        if(line.empty()){
            l = 0;
        }
        count++;
        l++;
    }
    temp.close();
    file.close();
    remove("estaciones.txt");
    rename("temp.txt", "estaciones.txt");
    c = 0;
    delete[] arr;
}
//Crear surtidor
void crearSurtidor(float cod,unsigned int code) {
    std::string linea;
    std::streampos posicionGuardada;
    std::ifstream archivo("estaciones.txt");  // Archivo en modo lectura
    std::ofstream archivoTemporal("temp.txt"); // Archivo temporal para escritura
    if (!archivo) {
        std::cerr << "No se pudo abrir el archivo" << std::endl;
        return;
    }
    if (!archivoTemporal) {
        std::cerr << "No se pudo crear el archivo temporal" << std::endl;
        return;
    }

    int c = 0;
    while (std::getline(archivo, linea)) {
        if (linea.empty()) {
            c = 0; // Reiniciar contador si la línea está vacía
        } else {
            c++; // Actualiza el contador solo si la línea no está vacía
        }
        if (c == 2) {
            archivoTemporal << linea << std::endl;

            if (std::stoi(linea.substr(0, linea.find("-"))) == code) {
                posicionGuardada = archivo.tellg();
                archivo.clear(); // Limpiar el estado de EOF
                archivo.seekg(posicionGuardada); // Regresar a la posición guardada
                unsigned int m = 0;
                while (std::getline(archivo, linea)) {
                    m++;
                    if (m == 2){
                        linea += "/" + std::to_string(cod);
                    }
                    archivoTemporal << linea << std::endl; // Escribe la línea en el archivo temporal
                }
            }
        } else {
            archivoTemporal << linea << std::endl; // Escribe la línea en el archivo temporal
        }
    }

    archivo.close();
    archivoTemporal.close();

    // Reemplaza el archivo original con el temporal
    std::remove("estaciones.txt");
    std::rename("temp.txt", "estaciones.txt");
}
//Eliminar surtidor
void deleteSurtidor(float cod, int code) {

    std::string linea;
    std::streampos posicionGuardada;
    std::ifstream archivo("estaciones.txt");  // Archivo en modo lectura
    std::ofstream archivoTemporal("temp.txt"); // Archivo temporal para escritura

    if (!archivo) {
        std::cerr << "No se pudo abrir el archivo" << std::endl;
        return;
    }
    if (!archivoTemporal) {
        std::cerr << "No se pudo crear el archivo temporal" << std::endl;
        return;
    }

    int c = 0;
    while (std::getline(archivo, linea)) {
        if (linea.empty()) {
            c = 0; // Reiniciar contador si la línea está vacía
        } else {
            c++; // Actualiza el contador solo si la línea no está vacía
        }
        if (c == 2) {
            archivoTemporal << linea << std::endl;

            if (std::stoi(linea.substr(0, linea.find("-"))) == code) {
                posicionGuardada = archivo.tellg();
                archivo.clear(); // Limpiar el estado de EOF
                archivo.seekg(posicionGuardada); // Regresar a la posición guardada
                unsigned int m = 0;
                while (std::getline(archivo, linea)) {
                    m++;

                    if (m == 2) {
                        size_t pos = linea.find(std::to_string(cod));
                        if (pos != std::string::npos) {
                            linea.erase(pos, std::to_string(cod).length());
                            // Eliminar la barra anterior si existe
                            if (linea[pos - 1] == '/') {
                                linea.erase(pos - 1, 1);
                            }
                        }
                    }
                    archivoTemporal << linea << std::endl; // Escribe la línea en el archivo temporal
                }
            }
        } else {
            archivoTemporal << linea << std::endl; // Escribe la línea en el archivo temporal
        }
    }

    archivo.close();
    archivoTemporal.close();

    // Reemplaza el archivo original con el temporal
    std::remove("estaciones.txt");
    std::rename("temp.txt", "estaciones.txt");
}
//Mostrar historial de las ventas
void historialVentas() {
    string nombreArchivo = "ventas.txt";
    ifstream archivo(nombreArchivo);

    if (!archivo) {
        cerr << "No se pudo abrir el archivo: " << nombreArchivo << endl;
        return;
    }

    string linea;

    while (getline(archivo, linea)) {
        size_t pos1 = linea.find('-');
        size_t pos2 = linea.find('-', pos1 + 1);
        size_t pos3 = linea.find('-', pos2 + 1);
        size_t pos4 = linea.find('-', pos3 + 1);
        size_t pos5 = linea.find('-', pos4 + 1);
        size_t pos6 = linea.find('-', pos5 + 1);
        size_t pos7 = linea.find('-', pos6 + 1);

        cout << "Venta numero: " << linea.substr(0, pos1) << endl;
        cout << "Codigo de surtidor: " << linea.substr(pos1 + 1, pos2 - pos1 - 1) << endl;
        cout << "Fecha de venta: " << linea.substr(pos2 + 1, pos3 - pos2 - 1) << endl;
        cout << "Litros vendidos: " << linea.substr(pos3 + 1, pos4 - pos3 - 1) << endl;
        cout << "Combustible tipo: " << linea.substr(pos4 + 1, pos5 - pos4 - 1) << endl;
        cout << "Metodo de pago: " << linea.substr(pos5 + 1, pos6 - pos5 - 1) << endl;
        cout << "Identificacion: " << linea.substr(pos6 + 1, pos7 - pos6 - 1) << endl;
        cout << "Pago: " << linea.substr(pos7 + 1) << endl;
        cout << "##################################################################" << endl;
    }

    archivo.close();
}
//Cantidad de gasolina vendida
void registroGas() {
    string nombreArchivo = "ventas.txt";
    ifstream archivo(nombreArchivo);

    if (!archivo) {
        cerr << "No se pudo abrir el archivo: " << nombreArchivo << endl;
        return;
    }

    string linea;
    float eco=0,regular=0,premium=0;


    while (getline(archivo, linea)) {
        size_t pos1 = linea.find('-');
        size_t pos2 = linea.find('-', pos1 + 1);
        size_t pos3 = linea.find('-', pos2 + 1);
        size_t pos4 = linea.find('-', pos3 + 1);
        size_t pos5 = linea.find('-', pos4 + 1);
        size_t pos6 = linea.find('-', pos5 + 1);
        size_t pos7 = linea.find('-', pos6 + 1);
        float  litros=stof(linea.substr(pos3 + 1, pos4 - pos3 - 1));
        string tipo=linea.substr(pos4 + 1, pos5 - pos4 - 1);
        if(tipo=="eco"){
            eco+=litros;
        }
        if(tipo=="regular"){
            regular+=litros;
        }
        if(tipo=="premium"){
            premium+=litros;
        }

    }
    cout<<"De combustible tipo eco se vendieron: "<<eco<<" litros"<<endl;
    cout<<"De combustible tipo regular se vendieron: "<<regular<<" litros"<<endl;
    cout<<"De combustible tipo premium se vendieron: "<<premium<<" litros"<<endl;


    archivo.close();
}

void agregarLinea(int n) {
    string nombreArchivo = "surtidor.txt";
    ifstream archivo(nombreArchivo);
    ofstream archivoTemporal("temporal.txt");

    if (!archivo) {
        cerr << "No se pudo abrir el archivo: " << nombreArchivo << endl;
        return;
    }
    srand(static_cast<unsigned int>(time(0)));
    int numeroAleatorio = rand() % 11 + 2;
    string nuevaLinea=to_string(n)+"."+to_string(numeroAleatorio)+"-"+"true";

    bool lineaAgregada = false;
    string linea;

    while (getline(archivo, linea)) {
        if (linea.empty() && !lineaAgregada) {
            archivoTemporal << nuevaLinea << endl;
            lineaAgregada = true;
        }
        archivoTemporal << linea << endl;
    }

    if (!lineaAgregada) {
        archivoTemporal << nuevaLinea << endl;
    }

    archivo.close();
    archivoTemporal.close();

    remove(nombreArchivo.c_str());
    rename("temporal.txt", nombreArchivo.c_str());

    cout << "Línea agregada exitosamente." << endl;
}

void eliminarLinea(const string& n) {
    string nombreArchivo = "surtidor.txt";
    ifstream archivo(nombreArchivo);
    ofstream archivoTemporal("temporal.txt");

    if (!archivo) {
        cerr << "No se pudo abrir el archivo: " << nombreArchivo << endl;
        return;
    }

    string linea;
    bool lineaEliminada = false;

    while (getline(archivo, linea)) {
        size_t pos = linea.find('-');
        if (pos != string::npos && linea.substr(0, pos) == n) {
            lineaEliminada = true;
            continue;
        }
        archivoTemporal << linea << endl;
    }

    archivo.close();
    archivoTemporal.close();

    remove(nombreArchivo.c_str());
    rename("temporal.txt", nombreArchivo.c_str());

    if (lineaEliminada){
        cout << "Línea eliminada exitosamente." << endl;
    }else{
        cout << "No se encontró ninguna línea con el número: " << n << endl;
    }
}

void surtidor(float cod,unsigned int code){
    std::string linea;
    std::streampos posicionGuardada;
    std::ifstream archivo("estaciones.txt");  // Archivo en modo lectura
    std::ofstream archivoTemporal("temp.txt"); // Archivo temporal para escritura

    if (!archivo) {
        std::cerr << "No se pudo abrir el archivo" << std::endl;
        return;
    }
    if (!archivoTemporal) {
        std::cerr << "No se pudo crear el archivo temporal" << std::endl;
        return;
    }

    int c = 0;
    while (std::getline(archivo, linea)) {
        if (linea.empty()) {
            c = 0; // Reiniciar contador si la línea está vacía
        } else {
            c++; // Actualiza el contador solo si la línea no está vacía
        }
        if (c == 2) {
            archivoTemporal << linea << std::endl;

            if (std::stoi(linea.substr(0, linea.find("-"))) == code) {
                posicionGuardada = archivo.tellg();
                archivo.clear(); // Limpiar el estado de EOF
                archivo.seekg(posicionGuardada); // Regresar a la posición guardada
                int m = 0;
                while (std::getline(archivo, linea)) {
                    m++;
                    if (m == 2) {
                        // Remueve el número 12.3 de la línea
                        size_t pos = linea.find(std::to_string(cod));
                        if (pos != std::string::npos) {
                            linea.erase(pos, std::to_string(cod).length());
                            // Eliminar la barra anterior si existe
                            if (linea[pos - 1] == '/') {
                                linea.erase(pos - 1, 1);
                            }
                        }
                    }
                    archivoTemporal << linea << std::endl; // Escribe la línea en el archivo temporal
                }
            }
        } else {
            archivoTemporal << linea << std::endl; // Escribe la línea en el archivo temporal
        }
    }

    archivo.close();
    archivoTemporal.close();

    // Reemplaza el archivo original con el temporal
    std::remove("estaciones.txt");
    std::rename("temp.txt", "estaciones.txt");
}
//Cambiar estado el surtidor
void cambiarEstado(const string& n){
    string nombreArchivo = "surtidor.txt";
    ifstream archivo(nombreArchivo);
    ofstream archivoTemporal("temp.txt");

    if (!archivo) {
        cerr << "No se pudo abrir el archivo: " << nombreArchivo << endl;
        return;
    }

    string linea;
    bool estadoCambiado = false;

    while (getline(archivo, linea)) {
        size_t pos = linea.find('-');
        if (pos != string::npos && linea.substr(0, pos) == n) {
            string estadoActual = linea.substr(pos + 1);
            string nuevoEstado;

            if (estadoActual == "true") {
                nuevoEstado = "false";
            } else {
                nuevoEstado = "true";
            }
            linea = linea.substr(0, pos + 1) + nuevoEstado;
            estadoCambiado = true;
        }
        archivoTemporal << linea << endl;
    }

    archivo.close();
    archivoTemporal.close();

    remove(nombreArchivo.c_str());
    rename("temp.txt", nombreArchivo.c_str());

    if (estadoCambiado){
        cout << "Estado cambiado exitosamente." << endl;
    } else {
        cout << "No se encontró ninguna línea con el número: " << n << endl;
        remove("temp.txt");
    }
}
//Verificacion fugas
float* sumCombusVentas(int cod){
    ifstream archivo("ventas.txt");

    if (!archivo) {
        cerr << "No se pudo abrir el archivo." << endl;
        return nullptr;
    }

    float regular = 0, eco = 0, premium = 0;
    string linea;

    while (getline(archivo, linea)) {
        if (!linea.empty()) {
            unsigned short int firstSlash = linea.find('/');
            unsigned short int secondSlash = linea.find('/', firstSlash + 1);
            unsigned short int firstDash = linea.find('-', secondSlash + 1);
            unsigned short int secondDash = linea.find('-', firstDash + 1);

            string cantidadStr = linea.substr(firstDash + 1, secondDash - firstDash - 1);
            float cant = stof(cantidadStr);

            string type = linea.substr(secondDash + 1, linea.find('-', secondDash + 1) - secondDash - 1);

            if (stoi(linea.substr(linea.find('-') + 1, linea.find('.'))) == cod) {
                if (type == "eco") {
                    eco += cant;
                } else if (type == "regular") {
                    regular += cant;
                } else if (type == "premium") {
                    premium += cant;
                }
            }
        }
    }

    archivo.close();
    static float orr[3] = {eco, regular, premium};
    return orr;
}
float* parcialTotal(int code){
    std::string linea;
    std::streampos posicionGuardada;
    std::ifstream archivo("estaciones.txt");
    std::ofstream archivoTemporal("temp.txt");

    if (!archivo) {
        std::cerr << "No se pudo abrir el archivo" << std::endl;
        return nullptr;
    }
    if (!archivoTemporal) {
        std::cerr << "No se pudo crear el archivo temporal" << std::endl;
        return nullptr;
    }

    float eco = 0, regular = 0, premium = 0, maxEco = 0, maxRegular = 0, maxPremium = 0;
    int c = 0;
    while (std::getline(archivo, linea)) {
        if (linea.empty()) {
            c = 0;
        } else {
            c++;
        }

        if (c == 2) {
            archivoTemporal << linea << std::endl;
            if (std::stoi(linea.substr(0, linea.find("-"))) == code) {
                posicionGuardada = archivo.tellg();
                archivo.clear();
                archivo.seekg(posicionGuardada);

                unsigned int m = 0;
                while (std::getline(archivo, linea)) {
                    m++;
                    if (m == 1) {
                        std::stringstream ss(linea);
                        std::string numeroStr;
                        float numeros[3];
                        int contador = 0;

                        while (std::getline(ss, numeroStr, ',')) {
                            if (contador < 3) {
                                numeros[contador] = std::stof(numeroStr);
                                contador++;
                            }
                        }

                        eco = numeros[0];
                        regular = numeros[1];
                        premium = numeros[2];
                        std::cout << "Eco: " << eco << std::endl;
                        std::cout << "Regular: " << regular << std::endl;
                        std::cout << "Premium: " << premium << std::endl;
                    }
                    archivoTemporal << linea << std::endl;

                    if (m == 3) {
                        std::stringstream ss(linea);
                        std::string numeroStr;
                        float capacidadTotal[3];
                        int contador = 0;

                        while (std::getline(ss, numeroStr, '#')){
                            if (contador < 3){
                                capacidadTotal[contador] = std::stof(numeroStr);
                                contador++;
                            }
                        }
                        maxEco = capacidadTotal[0];
                        maxRegular = capacidadTotal[1];
                        maxPremium = capacidadTotal[2];
                        std::cout << "MaxEco: " << maxEco << std::endl;
                        std::cout << "MaxRegular: " << maxRegular << std::endl;
                        std::cout << "MaxPremium: " << maxPremium << std::endl;
                    }
                }
            }
        } else {
            archivoTemporal << linea << std::endl;
        }
    }

    archivo.close();
    archivoTemporal.close();

    std::remove("estaciones.txt");
    std::rename("temp.txt", "estaciones.txt");

    static float arr[6] = {eco, regular, premium, maxEco, maxRegular, maxPremium};
    return arr;
}
//Modificar precio gasolina
void modificarPreciosEstacion(int cod, int nuevosPrecios[3]) {
    std::ifstream archivoEntrada("estaciones.txt");
    std::ofstream archivoTemporal("temp.txt");

    if (!archivoEntrada || !archivoTemporal) {
        std::cerr << "No se pudo abrir el archivo" << std::endl;
    }

    std::string linea;
    bool estacionEncontrada = false;
    bool preciosModificados = false;
    int c = 0;

    while (std::getline(archivoEntrada, linea)) {
        if (linea.empty()) {
            archivoTemporal << linea << std::endl;
            c = 0;  // Reiniciar el contador
            continue;
        }

        c++;

        if (c == 2) {  // Línea que contiene el código de la estación
            std::string codigoStr = linea.substr(0, linea.find("-"));

            if (std::stoi(codigoStr) == cod){  // Si el código coincide
                estacionEncontrada = true;
            }
        }

        if (estacionEncontrada && c == 6){
            std::stringstream ss(linea);
            std::string numeroStr;
            int contador = 0;

            std::ostringstream nuevaLinea;

            while (std::getline(ss, numeroStr, '*')) {
                if (contador < 3) {
                    nuevaLinea << nuevosPrecios[contador];
                } else {
                    nuevaLinea << numeroStr;
                }
                if (contador < 2) {
                    nuevaLinea << "*";
                }
                contador++;
            }

            archivoTemporal << nuevaLinea.str() << std::endl;
            preciosModificados = true;
            estacionEncontrada = false;
        } else {
            archivoTemporal << linea << std::endl;
        }
    }

    archivoEntrada.close();
    archivoTemporal.close();

    if(preciosModificados){
        std::cout << "Precios modificados correctamente." << std::endl;
        std::remove("estaciones.txt");
        std::rename("temp.txt", "estaciones.txt");
    }else {
        std::cout << "No se encontraron coincidencias o no se modificaron los precios." << std::endl;
        std::remove("temp.txt");
    }
}

void archivoPostventa(int posicion, float resta) {
    int cod = 1;
    if (posicion < 0 || posicion > 2) {
        cerr << "La posición debe estar entre 0 y 2." << endl;
        return;
    }

    string linea;
    ifstream archivo("estaciones.txt");
    ofstream archivoTemporal("temp.txt");

    if (!archivo) {
        cerr << "No se pudo abrir el archivo" << endl;
        return;
    }
    if (!archivoTemporal) {
        cerr << "No se pudo crear el archivo temporal" << endl;
        return;
    }

    int c = 0;
    while (getline(archivo, linea)) {
        if (linea.empty()) {
            c = 0;
        } else {
            c++;
        }
        archivoTemporal << linea << endl;

        if (c == 2) {
            if (stoi(linea.substr(0, linea.find("-"))) == cod) {
                stringstream ss(linea);
                string numeroStr;
                int numeros[3] = {0};

                // Leer los números de la línea
                int contador = 0;
                while (getline(ss, numeroStr, ',')) {
                    if (contador < 3) {
                        numeros[contador] = stoi(numeroStr);
                        contador++;
                    }
                }
                numeros[posicion] -= resta;

                // Escribir los nuevos valores en el archivo temporal
                for (int i = 0; i < 3; i++) {
                    archivoTemporal << numeros[i];
                    if (i < 2) {
                        archivoTemporal << ",";
                    }
                }
                archivoTemporal << endl;
            }
        }
    }

    archivo.close();
    archivoTemporal.close();
    remove("estaciones.txt");
    rename("temp.txt", "estaciones.txt");
}

string* surtidoresDisponibles(const string& codigoEstacion, int& cantidadSurtidores) {
    string nombreArchivo = "surtidor.txt";
    ifstream archivo(nombreArchivo);

    if (!archivo) {
        cerr << "No se pudo abrir el archivo: " << nombreArchivo << endl;
        return nullptr;
    }

    string linea;
    int capacidad = 2;
    cantidadSurtidores = 0;
    string* surtidores = new string[capacidad];

    while (getline(archivo, linea)) {
        size_t pos = linea.find('-');
        if (pos != string::npos) {
            string codigoSurtidor = linea.substr(0, pos);
            string estado = linea.substr(pos + 1);
            if (codigoSurtidor.substr(0, codigoEstacion.length()) == codigoEstacion && estado == "true") {
                if (cantidadSurtidores == capacidad) {
                    capacidad *= 2;
                    string* nuevoArray = new string[capacidad];
                    for (int i = 0; i < cantidadSurtidores; i++) {
                        nuevoArray[i] = surtidores[i];
                    }
                    delete[] surtidores;
                    surtidores = nuevoArray;
                }
                surtidores[cantidadSurtidores] = codigoSurtidor;
                cantidadSurtidores++;
            }
        }
    }

    archivo.close();
    return surtidores;
}

void archivoPostventa2(float codS, string fecha, int cant, string tip, int dni, float precio) {
    ifstream archivoOriginal("ventas.txt");
    ofstream archivoTemporal("temp.txt");

    if (!archivoOriginal || !archivoTemporal) {
        cerr << "Error al abrir uno de los archivos." << endl;
        return;
    }

    string linea;
    bool ultimaLineaVacia = false;
    int venta = 0;

    while (getline(archivoOriginal, linea)) {
        archivoTemporal << linea << endl;
        if (linea.empty()) {
            ultimaLineaVacia = true;
        } else {
            ultimaLineaVacia = false;
            venta += stoi(linea.substr(0, linea.find('-')));
        }
    }
    if (!ultimaLineaVacia) {
        archivoTemporal << endl;
    }

    archivoTemporal << to_string(venta) + "-" + to_string(codS) + "-" + fecha + "-" + to_string(cant) + "-" + tip + "-" + to_string(dni) + "-" + to_string(precio) << endl;
    archivoOriginal.close();
    archivoTemporal.close();
    remove("ventas.txt");
    rename("temp.txt", "ventas.txt");

    cout << "Contenido añadido correctamente en la última línea vacía." << endl;
}

int precioVenta(int cod, int posicion, int cant) {
    if (posicion < 0 || posicion > 2) {
        cerr << "La posición debe estar entre 0 y 2." << endl;
        return -1;
    }

    string linea;
    ifstream archivo("estaciones.txt");

    if (!archivo) {
        cerr << "No se pudo abrir el archivo" << endl;
        return -1;
    }

    int c = 0;
    int precio = 0;
    while (getline(archivo, linea)) {
        if (linea.empty()) {
            c = 0;
        } else {
            c++;
        }

        if (c == 2) {
            string codigoStr = linea.substr(0, linea.find("-"));

            if (stoi(codigoStr) == cod) {
                int m = 0;
                while (getline(archivo, linea)) {
                    m++;
                    if (m == 4) {
                        stringstream ss(linea);
                        string numeroStr;
                        int numeros[3] = {0};
                        int contador = 0;

                        while (getline(ss, numeroStr, '*')) {
                            if (contador < 3) {
                                numeros[contador] = stoi(numeroStr);
                                contador++;
                            }
                        }

                        precio = numeros[posicion] * cant;
                        break;
                    }
                }
                break;
            }
        }
    }

    archivo.close();
    return precio;
}

pump simularVenta(int codStation, pump* arr, int& c) {
    time_t tiempoActual = std::time(nullptr);
    srand(static_cast<unsigned int>(std::time(0)));

    int cantidadSurtidores;
    string* disponibles = surtidoresDisponibles(to_string(codStation), cantidadSurtidores);
    if (disponibles == nullptr || cantidadSurtidores == 0) {
        cerr << "No hay surtidores disponibles para la estación " << codStation << endl;
        return pump (); // Devuelve un objeto pump vacío si no hay surtidores disponibles
    }

    int pos = rand() % cantidadSurtidores; // Cambia a cantidadSurtidores
    int codRamdom = rand() % 12 + 1;
    string codSurtidor = to_string(codStation) + "." + to_string(codRamdom);
    int cant = rand() % 20 + 1;
    string tipo = "Gasolina";
    stringstream ss;
    ss << tiempoActual;
    int dni = rand() % 100000000 + 1;
    string fecha = ss.str();
    int precio = precioVenta(codStation, pos, cant);
    float total = precio; // Se asume que el precio calculado es el total de la venta.

    // Convertimos a float los valores que el constructor espera como float
    pump objetoVenta(static_cast<float>(codRamdom), true, fecha, static_cast<float>(cant), pos, dni, dni, total);

    arr[c] = objetoVenta;
    c++;
    archivoPostventa2(codRamdom, fecha, cant, tipo, dni, total);
    archivoPostventa(pos, cant);

    delete[] disponibles; // Liberar la memoria
    return objetoVenta;
}
