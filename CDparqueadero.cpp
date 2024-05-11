#include <iostream>
#include <string>
#include <malloc.h>

using namespace std;

struct vehiculo
{
    int placa;
    string tipo_vehiculo; // Coche o Moto
    int idcarro;          // Identificación de carro
    int idmoto;           // Identificación de moto
    vehiculo *sig;
};

vehiculo *aux, *cab;

int Caja_parqueadero = 0;

int registrar()
{
    int volver_registrar = 0;
    int id_actual = 1; // Inicializar la identificación de vehículo

    do
    {
        cout << "Bienvenido al parqueadero el timido" << endl;
        cout << "\n";

        // Pide memoria
        aux = (struct vehiculo *)malloc(sizeof(struct vehiculo));
        cout << "Ingresa la placa del vehiculo: " << endl;
        cin >> aux->placa;

        cout << "Ingresa el tipo de vehiculo (Coche / Moto): " << endl;
        cin >> aux->tipo_vehiculo;

        // Asigna la identificación según el tipo de vehículo
        if (aux->tipo_vehiculo == "Coche")
        {
            aux->idcarro = id_actual++;
            cout << "ID asignado al vehiculo: " << aux->idcarro << endl;
            Caja_parqueadero += 5000; // Sumar al dinero en caja
        }
        else if (aux->tipo_vehiculo == "Moto")
        {
            aux->idmoto = id_actual++;
            cout << "ID asignado al vehiculo: " << aux->idmoto << endl;
            Caja_parqueadero += 2500; // Sumar al dinero en caja
        }

        // Almacenar en LIFO
        if (cab == NULL)
        {
            cab = aux;
            cab->sig = NULL;
        }
        else
        {
            aux->sig = cab;
            cab = aux;
        }
        aux = NULL;
        free(aux);

        cout << "El registro ha sido exitoso" << endl;
        system("pause");
        cout << "Desea hacer otro registro? (1.SI/2.NO)" << endl;
        cin >> volver_registrar;
    } while (volver_registrar != 2);
    return 0;
}

int calcularCostoRetiro(vehiculo *vehiculoRetirar)
{
    int costo_base = (vehiculoRetirar->tipo_vehiculo == "Coche") ? 10000 : 500; // Costo base de retiro

    // Contadores para vehículos con idcarro o idmoto mayor que el vehículo a retirar
    int contador = 0;

    // Contar vehículos con id mayor que el vehículo a retirar
    vehiculo *auxiliar = cab;
    while (auxiliar != NULL)
    {
        if (vehiculoRetirar->tipo_vehiculo == "Coche" && auxiliar->idcarro > vehiculoRetirar->idcarro)
        {
            contador++;
        }
        else if (vehiculoRetirar->tipo_vehiculo == "Moto" && auxiliar->idmoto > vehiculoRetirar->idmoto)
        {
            contador++;
        }
        auxiliar = auxiliar->sig;
    }

    // Calcular costo total de retiro
    int costo_total = costo_base * contador;
    return costo_total;
}

int retirar()
{
    if (cab != NULL)
    {
        // Buscar el vehículo a retirar
        int id_retirar;
        cout << "Ingrese el ID del vehiculo a retirar: ";
        cin >> id_retirar;

        vehiculo *vehiculo_retirar = NULL;
        vehiculo *auxiliar = cab;
        while (auxiliar != NULL)
        {
            if ((auxiliar->tipo_vehiculo == "Coche" && auxiliar->idcarro == id_retirar) ||
                (auxiliar->tipo_vehiculo == "Moto" && auxiliar->idmoto == id_retirar))
            {
                vehiculo_retirar = auxiliar;
                break;
            }
            auxiliar = auxiliar->sig;
        }

        if (vehiculo_retirar != NULL)
        {
            // Calcular costo de retiro
            int costo_retiro = calcularCostoRetiro(vehiculo_retirar);

            // Actualizar la caja
            Caja_parqueadero += costo_retiro;

            // Eliminar el vehículo
            // ...

            cout << "Vehiculo retirado. Costo total: $" << costo_retiro << endl;
            system("pause");
        }
        else
        {
            cout << "Vehiculo no encontrado." << endl;
            system("pause");
        }
    }
    else
    {
        cout << "Vacio..." << endl;
        cout << "No hay Vehiculos en el parqueadero" << endl;
        system("pause");
    }
    return 0;
}

int mostrar()
{
    if (cab != NULL)
    {
        cout << "Datos de los vehiculos:" << endl;
        vehiculo *auxiliar = cab;
        while (auxiliar != NULL)
        {
            cout << "Placa: " << auxiliar->placa << endl;
            cout << "Tipo de vehiculo: " << auxiliar->tipo_vehiculo << endl;
            if (auxiliar->tipo_vehiculo == "Coche")
            {
                cout << "ID: " << auxiliar->idcarro << endl;
            }
            else if (auxiliar->tipo_vehiculo == "Moto")
            {
                cout << "ID: " << auxiliar->idmoto << endl;
            }
            cout << "------------------------------------" << endl;
            auxiliar = auxiliar->sig;
        }

        cout << "Dinero en Caja: $" << Caja_parqueadero << endl;
        system("pause");
    }
    else
    {
        cout << "Vacio..." << endl;
        cout << "No hay Vehiculos en el parqueadero" << endl;
        cout << "Dinero en Caja: $" << Caja_parqueadero << endl;
        system("pause");
    }
    return 0;
}

int main()
{
    int opc = 0;
    do
    {
        cout << "\nMenu" << endl;
        cout << "1. Registrar Vehiculo " << endl;
        cout << "2. Retirar Vehiculo " << endl;
        cout << "3. Mostrar Datos" << endl;
        cout << "4. Salir" << endl;
        cin >> opc;
        switch (opc)
        {
        case 1:
            registrar();
            break;
        case 2:
            retirar();
            break;
        case 3:
            mostrar();
            break;
        case 4:
            cout << "BYE";
            break;
        default:
            cout << "Opcion Invalida.";
            break;
        }
    } while (opc != 4);
}
