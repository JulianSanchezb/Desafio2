#include<iostream>
#include<limits>
#include<fstream>

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
    int opc = 0;
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

    //int code_;
    //int model_;
    //bool state_;
    //string date_;
    //float amount_;
    //int type_;
    //int method_;
    //int dni_;
    //float total_;

    //cout<<"Ingrese codigo\n";
    //cin>>code_;
    //cout<<"Ingrese Modelo\n";
    //cin>>model_;
    //cout<<"Ingrese estado\n";
    //cin>>state_;
    //cout<<"Ingrese fecha";
    //cin.ignore(numeric_limits<streamsize>::max(), '\n');
    //getline(cin,date_);
    //cout<<"\nIngrese cantidad\n";
    //cin>>amount_;
    //cout<<"Ingrese tipo gas\n";
    //cin>>type_;
    //cout<<"Ingrese motodo de pago\n";
    //cin>>method_;
    //cout<<"Ingrese documento\n";
    //cin>>dni_;
    //cout<<"Ingrese total\n";
    //cin>>total_;

    //station(name,codeOne,manager,region,latitude,length,regular,eco,extra,sizeSuppliers)
    pump surtidor = pump(code_, model_, state_, date_, amount_, type_, method_, dni_, total_);

    cout<<"Codigo: "<<surtidor.getCode();
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
/*
void stationin(station estacion){
    ifstream filei;
    ofstream fileo;
    string aux,line;
    bool value = false;
    filei.open("Stations.txt");
    if(!filei.is_open()){
        cout<<"Error al abrir Stations.txt\n";
        break;
    }

    while(getline(filei,aux)){
        line =aux;
    }
    aux = "";
    for(char c: line){
        if(c == ' '){
            aux = c;
        }
    }
    int codigo =stoi(line[])
                 file<<estacion.getStationName()<<" "<<estacion.getStationCode()<<"-"<<estacion.getStationManager()<<","<<estacion.getStationRegion()<<"<"<<estacion.getCoordinatesGps()<<"."

}*/

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
