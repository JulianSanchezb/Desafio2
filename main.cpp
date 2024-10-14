#include<iostream>
#include<fstream>
#include <cstdlib>
#include <ctime>
#include <random>

#include"station.h"
#include"pump.h"


using namespace std;

void menu(){
    int opc = 0;
    do{
        cout<<"Ingrese una opción\n1. Gestion de la red\n2. Getion de estaciones de servicio\n3. Verificacion de fugas\n4. Venta\n0. Salir\n";
        cin>>opc;
        switch (opc) {
        case 0:
            opc = opc;
            break;
        case 1:

            break;
        case 2:

            break;
        case 3:

            break;
        case 4:

            break;
        default:
            cout<<"Opcion invalida\n";
            break;
        }
    }while(opc != 0);
}

int gestionRed(){
    int opc = 0,c = 0;
    station *estaciones = new station [20];

    do{
        cout<<"Ingrese una opcion\n1. Agregar estacion\n2. Eliminar estacion\3. Calcular ventas en cada estacion(por combustible)\n4. Precios combustible\n0. Volver\n";
        cin>>opc;
        switch (opc) {
        case 0:
            return 0;
            break;
        case 1:

            break;
        case 2:

            break;
        case 3:

            break;
        case 4:

            break;
        default:
            cout<<"Opcion invalida\n";
            break;
        }
    }while(opc != 0);
}

int main(){

    return 0;
}

void updateFile(pump surtidor1){
    ifstream inputFile("ventas.txt");
    ofstream outputFile("modFile.txt");
    if(!inputFile.is_open()||!outputFile.is_open()){
        cout<<"pailas el archivo no se pudo abrir parce"<<endl;
        return;
    }

    string  line;
    while(getline(inputFile, line)){
        string endLine=line;
        string newSale=to_string(int(endLine[0]) + 1);

        if(line.empty()){
            outputFile<<newSale<<"-"<<surtidor1.getCode()<<"-"<<surtidor1.getDate()<<"-"<<surtidor1.getAmountGas()<<"-"<<surtidor1.getTypeGas()<<"-"<<surtidor1.getMethodPay()<<"-"<<surtidor1.getDni()<<"-"<<surtidor1.getTotal()<<endl;
        }
        else{
            outputFile<<line<<endl;
        }
    }
    inputFile.close();
    outputFile.close();
    remove("ventas.txt");
    rename("modFile.txt","ventas.txt");
    cout<<"parce se modifico el archivo cucho"<<endl;
}

void stationin(station *estaciones,int &c){
    random_device rd;
    mt19937 gen(rd());

    ifstream filei;
    string line,aux;
    int l = 1,r = 0, code;

    string name = "";
    string manager = "";
    string region = "";
    float coordinates[2];
    float tank[3];

    filei.open("estaciones.txt");
    if(!filei.is_open()){
        cout<<"Error al abrir Stations.txt\n";
    }

    //Asignacion del codigo de la estacion
    while(getline(filei,line)){
        if(l == 2){
            aux = line.substr(0,(line.find('-')+1));
            code = stoi(aux) + 1;
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
    for(int i = 0;i<=3;i++){
        uniform_real_distribution<float> distribucion(100.0, 200.0);
        tank[i] = {round(distribucion(gen) * 100)/100};
    }
    //Asignacion de surtidores
    int cant = 0;
    while(cant < 2 || cant > 12){
        cout<<"Ingrese la cantidad de surtidores en la estacion\n";
        cin>>cant;
        if(cant < 2 || cant > 12){
            cout<<"Fuera de rango, debe ser minimo 2 y maximo 12 surtidores\n";
        }
    }

    int *surtidores;
    surtidores = new int [cant];
    for(int i = 0;i < cant;i++){
        cout<<"Ingrese el modelo del surtidor numero "<<i<<"\n1. Super fast\n2. Super cool\n3. Super normal";
        cin>>surtidores[i];
        if(surtidores[i] < 1 || surtidores[i] > 3){
            cout<<"\n*Opcion invalida*\n";
            i--;
        }
    }

    station estacion(name,code,manager,region,coordinates[0],coordinates[1],tank[0],tank[1],tank[2],surtidores,cant);
    estaciones[c] = estacion;
    c++;
}

void updateStation(station* arr,int& c){
    ofstream file;
    file.open("estaciones.txt",ios::app);
    if(!file.is_open()){
        cout<<"Error al abrir el archivo estaciones.txt"<<endl;

    }

    for(int i = 0;i < c;i++){
        file<<"\n"<<arr[i].getStationRegion()<<"$"<<arr[i].getCoordinatesGps()[0]<<"$"<<arr[i].getCoordinatesGps()[1];
        file<<"\n"<<arr[i].getStationCode()<<"-"<<arr[i].getStationName()<<"-"<<arr[i].getStationManager()<<"\n";
        for(int j = 0;j < 3;j++){
            if(j != 2){
                file<<arr[i].getStationTank()[j]<<",";
            }else{
                file<<arr[i].getStationTank()[j];
            }
        }
        file<<endl;
        int tam = arr[i].getSurtidores();

        for(int j = 0;j < tam;j++){
            if(j < tam-1){
                file<<arr[i].getStationCode()<<j+1<<"/";
            }else{
                file<<arr[i].getStationCode()<<j+1<<"\n";
            }
        }
        file2<<arr[i].getStationCode()<<"."<<j+1<<"-"<<"true"<<endl;
    }
    c = 0;
}
void manageStation(pump surtidorOne, int choice) { // Eliminar, agregar, activar, desactivar
    int choiceTwo;

    if (choice == 1) {
        do {
            cout << "para agregar un surtidor ingrese 1, para eliminarlo ingrese 0" << endl;
            cin >> choiceTwo;
        } while (choiceTwo != 1 && choiceTwo != 0);

        if (choiceTwo == 1) {
            ifstream originalFile("surtidor.txt");
            ofstream newFile("modFile.txt");
            if (!originalFile.is_open() || !newFile.is_open()) {
                cout << "pailas el archivo no se pudo abrir parce" << endl;
                return;
            }

            string line;
            // Agregar el nuevo surtidor
            newFile << surtidorOne.getCode() << "-" << surtidorOne.getModel() << "-" << surtidorOne.getState() << endl;

            while (getline(originalFile, line)) {
                newFile << line << endl; // Copiar las líneas existentes
            }
            originalFile.close();
            newFile.close();
            remove("surtidor.txt");
            rename("modFile.txt", "surtidor.txt");
            cout << "parce se modifico el archivo cucho" << endl;
        }

        else if (choiceTwo == 0) {
            ifstream originalFile("surtidor.txt");
            ofstream newFile("modFile.txt");
            if (!originalFile.is_open() || !newFile.is_open()) {
                cout << "pailas el archivo no se pudo abrir parce" << endl;
                return;
            }

            string line;
            while (getline(originalFile, line)) {
                if (line.substr(0, to_string(surtidorOne.getCode()).length()) != to_string(surtidorOne.getCode())) {
                    newFile << line << endl; // Escribir líneas que no corresponden al surtidor
                }
            }
            originalFile.close();
            newFile.close();
            remove("surtidor.txt");
            rename("modFile.txt", "surtidor.txt");
            cout << "parce se modifico el archivo cucho" << endl;
            // falta hacer lo mismo pero actualizando los archivos de la estación
        }
    }

    else if (choice == 2) {
        do {
            cout << "para activar un surtidor ingrese 1, para desactivarlo ingrese 0" << endl;
            cin >> choiceTwo;
        } while (choiceTwo != 1 && choiceTwo != 0);

        if (choiceTwo == 1) {
            ifstream originalFile("surtidor.txt");
            ofstream newFile("modFile.txt");
            if (!originalFile.is_open() || !newFile.is_open()) {
                cout << "pailas el archivo no se pudo abrir parce" << endl;
                return;
            }

            string line;
            while (getline(originalFile, line)) {
                if (line.substr(0, to_string(surtidorOne.getCode()).length()) == to_string(surtidorOne.getCode())) {
                    string estado = line.substr(line.find_last_of('-') + 1); // Obtener el estado actual
                    if (estado == "false") {
                        line.replace(line.find_last_of('-') + 1, 4, "true"); // Cambiar a "true"
                    } else {
                        cout << "parce, la vuelta ya está activa, así que revisa la próxima vez listo, sapa" << endl;
                    }
                }
                newFile << line << endl; // Escribir la línea modificada
            }
            originalFile.close();
            newFile.close();
            remove("surtidor.txt");
            rename("modFile.txt", "surtidor.txt");
            cout << "parce se modifico el archivo cucho" << endl;
        }

        else if (choiceTwo == 0) {
            ifstream originalFile("surtidor.txt");
            ofstream newFile("modFile.txt");
            if (!originalFile.is_open() || !newFile.is_open()) {
                cout << "pailas el archivo no se pudo abrir parce" << endl;
                return;
            }

            string line;
            while (getline(originalFile, line)) {
                if (line.substr(0, to_string(surtidorOne.getCode()).length()) == to_string(surtidorOne.getCode())) {
                    string estado = line.substr(line.find_last_of('-') + 1); // Obtener el estado actual
                    if (estado == "true") {
                        line.replace(line.find_last_of('-') + 1, 4, "false"); // Cambiar a "false"
                    } else {
                        cout << "parce, la vuelta ya está desactivada, así que revisa la próxima vez listo, sapa" << endl;
                    }
                }
                newFile << line << endl; // Escribir la línea modificada
            }
            originalFile.close();
            newFile.close();
            remove("surtidor.txt");
            rename("modFile.txt", "surtidor.txt");
            cout << "parce se modifico el archivo cucho" << endl;
        }
    }
}
