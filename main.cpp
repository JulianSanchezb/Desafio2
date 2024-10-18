#include<iostream>

#include"station.h"
#include"pump.h"
#include"funciones.h"

using namespace std;


void menu();
int gestionRed();
int gestionES();

int main(){
    menu();
    return 0;
}

void menu(){
    int opc = 0;
    pump* arreglo = new pump [15];
    int count = 0,estacion;
    int n;
    float* a;
    float* b;
    float sum,total,porcentaje;
    do{
        cout<<"Ingrese una opción\n1. Gestion de la red\n2. Gestion de estaciones de servicio\n3. Verificacion de fugas\n4. Venta\n0. Salir\n";
        cin>>opc;
        switch (opc) {
        case 0:
            opc = opc;
            break;
        case 1:
            gestionRed();
            break;
        case 2:
            gestionES();
            break;
        case 3:
            do{
                cout<<"Ingrese el numero de la estacion\n";
                cin>>n;
                if(n < 0){
                    cout<<"Codigo invalido\n";
                }
            }while(n < 0);
            a = sumCombusVentas(n);
            b = parcialTotal(n);
            sum = a[0]+b[0]+a[1]+b[1]+a[2]+b[2];
            total = b[3]+b[4]+b[5];
            porcentaje = (sum*100)/total;
            if(porcentaje>=95){
                cout<<"No hay fuga"<<endl;
            }
            else if(porcentaje<95){
                cout<<"Si hay fuga"<<endl;
            }
            break;
        case 4:
            do{
                cout<<"Ingrese el codigo de la estacion en la que se simular la venta\n";
                cin>>estacion;
                if(estacion < 0){
                    cout<<"Codigo invalido\n";
                }
            }while(estacion < 0);
            simularVenta(estacion,arreglo,count);
            break;
        default:
            cout<<"Opcion invalida\n";
            break;
        }
    }while(opc != 0);
}


int gestionRed(){
    int opc = 0,c = 0,cD = 0;
    station *estaciones = new station [20];
    int* estacionesD = new int[20];
    int code;
    int precios[3];
    do{
        cout<<"Ingrese una opcion\n1. Agregar estacion\n2. Eliminar estacion\n3. Calcular ventas en cada estacion(por combustible)\n4. Precios combustible\n5. Guardar estaciones creadas\n6. Guardar estaciones eliminadas\n0. Volver\n";
        cin>>opc;
        switch (opc) {
        case 0:
            return 0;
            break;
        case 1:
            stationin(estaciones,c);
            break;
        case 2:
            deleteStation(estacionesD,cD);
            break;
        case 3:
            cout<<"No realizada\n";
            break;
        case 4:
            do{
                cout<<"Ingrese el codigo de la estacion\n";
                cin>>code;
                if(code < 0){
                    cout<<"Codigo invalido\n";
                }
            }while(code < 0);
            modificarPreciosEstacion(code,precios);
            break;
        case 5:
            updateStation(estaciones,c);
            break;
        case 6:
            definitiveD(estacionesD,cD);
            break;
        default:
            cout<<"Opcion invalida\n";
            break;
        }
    }while(opc != 0);
    return 0;
}

int gestionES(){
    unsigned short int opc = 0;
    string surt = "";
    float codeS;
    unsigned int codeE;
    do{
        cout<<"Ingrese una opcion\n1. Agregar surtidor de una estacion\n2. Eliminar surtidor de una estacion\n3. Activar/desactivar surtidor\n4. Consultar historico de transacciones en surtidor\n5. Litros de combustible vendidos\n0. Volver\n";
        cin>>opc;
        switch (opc) {
        case 0:
            return 0;
            break;
        case 1:

            do{
                cout<<"Ingrese el codigo del surtidor\n";
                cin>>codeS;
                cout<<"Ingrese el codigo de la estacion\n";
                cin>>codeE;
                if(codeE < 0 || codeS < 0){
                    cout<<"Codigos invalidos\n";
                }
            }while(codeE < 0 || codeS < 0);
            crearSurtidor(codeS,codeE);
            agregarLinea(codeE);
            break;
        case 2:
            do{
                cout<<"Ingrese el codigo del surtidor\n";
                cin>>codeS;
                cout<<"Ingrese el codigo de la estacion\n";
                cin>>codeE;
                if(codeE < 0 || codeS < 0){
                    cout<<"Codigos invalidos\n";
                }
            }while(codeE < 0 || codeS < 0);
            deleteSurtidor(codeS,codeE);

            break;
        case 3:
            do{
                cout<<"Ingrese el codigo del surtidor\n";
                getline(cin,surt);
                if(surt == ""){
                    cout<<"Ingrese algo\n";
                }
            }while(surt == "");
            cambiarEstado(surt);
            break;
        case 4:
            historialVentas();
            break;
        case 5:
            registroGas();
            break;
        default:
            cout<<"Opcion invalida\n";
            break;
        }
    }while(opc != 0);
    return 0;
}
