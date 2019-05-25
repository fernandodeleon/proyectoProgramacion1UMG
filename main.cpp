#include <iostream>
#include <fstream>
#include <Windows.h>
#include "SerialClass.cpp"
using namespace std;

int main(){
	SetConsoleTitle("Reloj|Temporizador|Cronometro|Temperatura");
	Serial* Puerto = new Serial("COM5");

	char reloj[] = "reloj";
	char cronometro[] = "cronometro";
	char temporizador[] = "temporizador";
	char temperatura[] = "temperatura";
	char salir[] = "salir";

	int opc;

	while (Puerto->IsConnected()){
		cout << endl;
		cout << "--------Bienvenido--------" << endl;
		cout << "1) Reloj"<< endl;
		cout << "2) Cronometro" << endl;
		cout << "3) Temporizador" << endl;
		cout << "4) Temperatura" << endl;
		cout << "0) Salir de un proceso" << endl;
		cout << "--------------------------" << endl;
		cout << "Que quiere hacer?: ";
		cin >> opc;

		switch (opc){
		    case 0:
                cout << "Proceso finalizado" << endl;
                Puerto->WriteData(salir, sizeof(salir)-1);
                break;

            case 1:
                cout << "Reloj" << endl;
                Puerto->WriteData(reloj, sizeof(reloj)-1);
                break;

            case 2:
                cout << "Cronometro" << endl;
                Puerto->WriteData(cronometro, sizeof(cronometro)-1);
                break;

            case 3:
                cout << "Temporizador" << endl;
                Puerto->WriteData(temporizador, sizeof(temporizador)-1);
                break;

            case 4:
                cout << "Temperatura" << endl;
                Puerto->WriteData(temperatura, sizeof(temperatura)-1);
                break;

            default:
                cout << "Seleccione opciones del 0 al 4" << endl;
            }
            Sleep(100);
	}
	return 0;
}
