#include <iostream>
#include <fstream>
#include <iomanip>
#include <string>
#include <vector>
#include <limits>

using namespace std;

struct Empleado {
    string nombre;
    int codigo;
} empleados[2] = {{"Elizabeth Beatriz Requena Alania", 202401}, {"Brandon Jhoel Mendoza Vega", 202402}};

struct Cliente {
    string nombres, apellidos, dni, numeroCelular;
};

struct Autos {
    string marca, modelo;
    float precio;
};

struct Venta {
    string autoModelo;
    float precio;
};

string tiendaNombre = "AUTOS PREMIER", tiendaDireccion = "Jr. Amazonas cuadra: 6", tiendaNumero = "555-1234";

vector<Autos> autosDisponibles = {
    {"Hyundai", "Accent", 19000},
    {"Hyundai", "Elantra", 21000},
    {"Hyundai", "Sonata", 25000},
    {"Nissan", "Versa", 18000},
    {"Nissan", "Sentra", 20000},
    {"Nissan", "Altima", 24000},
    {"Ford", "Fiesta", 17000},
    {"Ford", "Focus", 20000},
    {"Ford", "Mustang", 26000}
};

void generarReporteVentas() {
    string contrasena;
    bool contrasenaCorrecta = false;
    do {
        cout << "Introducir contraseña: ";
        cin >> contrasena;
        
        if (contrasena == "1234") {
            contrasenaCorrecta = true;
        } else {
            cout << "Contraseniaa incorrecta. Por favor, intente nuevamente." << endl;
        }
    } while (!contrasenaCorrecta);

    cout << "Lista de empleados:\n1. Elizabeth Beatriz Requena Alania\n2. Brandon Jhoel Mendoza Vega\nSeleccione un empleado: ";
    int opcionEmpleado;
    cin >> opcionEmpleado;
    Empleado empleadoSeleccionado = empleados[opcionEmpleado - 1];

    vector<Venta> ventasEmpleado = {
        {"HYUNDAI Accent", 19000},
        {"NISSAN Versa", 18000},
        {"FORD Fiesta", 17000}
    };

    float totalVentas = 0.0;
    for (const auto& venta : ventasEmpleado) {
        totalVentas += venta.precio;
    }

  
    float sueldoBase = 1200.0; 
    float comision = 0.05;
    float totalComisiones = totalVentas * comision;
    float sueldoTotal = sueldoBase + totalComisiones;
    
    ofstream archivo("ReporteVentas.txt");
    archivo << "AUTO PREMIER: REPORTE DE VENTAS DEL MES\n";
    archivo << "Empleado: " << empleadoSeleccionado.nombre << "\n\n"; 
    archivo << "Autos Vendidos:\n";
    for (const auto& venta : ventasEmpleado) {
        archivo << venta.autoModelo << "\t s/ " << fixed << setprecision(2) << venta.precio << "\n";
    }
    archivo << "\nGanancia Total: \t s/ " << fixed << setprecision(2) << totalVentas << "\n";
    archivo << "Sueldo Base: \t s/ " << sueldoBase << "\n";
    archivo << "Comisión por ventas: \t s/ " << totalComisiones << "\n";
    archivo << "Sueldo Total del Mes: \t s/ " << sueldoTotal << "\n";
    archivo.close();
    
    cout << "Reporte de ventas generado para " << empleadoSeleccionado.nombre << ".\n";
}

void solicitarDatosCliente(Cliente& cliente) {
    cout << "Ingrese nombres: ";
    cin.ignore();
    getline(cin, cliente.nombres);
    cout << "Ingrese apellidos: ";
    getline(cin, cliente.apellidos);
    cout << "Ingrese numero de celular: ";
    cin >> cliente.numeroCelular;
    cout << "Ingrese DNI: ";
    cin >> cliente.dni;
}

vector<Autos> filtrarAutosPorMarca(const string& marca) {
    vector<Autos> autosFiltrados;
    for (const auto& autoDisponible : autosDisponibles) {
        if (autoDisponible.marca == marca) {
            autosFiltrados.push_back(autoDisponible);
        }
    }
    return autosFiltrados;
}



void generarProformaAuto() {
   
    int codigoEmpleado;
    bool empleadoEncontrado = false;
    Empleado empleadoSeleccionado;
    
    do {
    cout << "Introducir su codigo de empleado: ";
    cin >> codigoEmpleado;

    for (const auto& empleado : empleados) {
            if (empleado.codigo == codigoEmpleado) {
                empleadoSeleccionado = empleado;
                empleadoEncontrado = true;
                break;
            }
        }
        
        if (!empleadoEncontrado) {
            cout << "Empleado no registrado. Por favor, intente nuevamente." << endl;
        }
    } while (!empleadoEncontrado);
    
    Cliente cliente;
    solicitarDatosCliente(cliente);

    cout << "Presione cualquier tecla para continuar...";
    cin.ignore(); cin.get();

    cout << "Marcas de auto disponibles:\n1. Hyundai\n2. Nissan\n3. Ford\nSeleccione una marca: ";
    int opcionMarca;
    cin >> opcionMarca;
    string marcaSeleccionada;
    switch(opcionMarca) {
        case 1: marcaSeleccionada = "Hyundai"; break;
        case 2: marcaSeleccionada = "Nissan"; break;
        case 3: marcaSeleccionada = "Ford"; break;
        default: cout << "Opción no válida.\n"; return;
    }

    vector<Autos> autosFiltrados = filtrarAutosPorMarca(marcaSeleccionada);
    cout << "Seleccione el modelo de auto para la proforma:\n";
    for (size_t i = 0; i < autosFiltrados.size(); ++i) {
        cout << i + 1 << ". " << autosFiltrados[i].modelo <<"\n";
    }
    int opcionModelo;
    cin >> opcionModelo;
    if(opcionModelo < 1 || opcionModelo > autosFiltrados.size()) {
        cout << "Opción no válida.\n";
        return;
    }

    Autos autoSeleccionado = autosFiltrados[opcionModelo - 1];

    float precioContado = autoSeleccionado.precio;
    float interesCredito = precioContado * 0.1; 
    int meses = 12; 
    float pagoMensual = (precioContado + interesCredito) / meses;
    float precioTotal = precioContado + interesCredito;
    
    ofstream archivoProforma("Proforma.txt");
    archivoProforma << tiendaNombre << endl;
    archivoProforma << tiendaDireccion << endl;
    archivoProforma << "Contactenos al " << tiendaNumero << endl << endl;

    archivoProforma << "DATOS CLIENTE:\n";
    archivoProforma << "Cliente\t: " << cliente.nombres << " " << cliente.apellidos << endl;
    archivoProforma << "DNI\t\t: " << cliente.dni << endl;
    archivoProforma << "Numero\t: " << cliente.numeroCelular << endl << endl;

    archivoProforma << "DATOS EMPLEADO:\n";
    archivoProforma << "Empleado\t: " << empleadoSeleccionado.nombre << endl;
    archivoProforma << "Codigo\t\t: " << codigoEmpleado << endl << endl;

    archivoProforma << "DETALLES DEL AUTO:\n";
    archivoProforma << "Marca: " << autoSeleccionado.marca << endl;
    archivoProforma << "Modelo: " << autoSeleccionado.modelo << endl;
    archivoProforma << "Precio: $" << fixed << setprecision(2) << autoSeleccionado.precio << endl;

    archivoProforma << "Descripcion\t\t\t: " << autoSeleccionado.marca << " " << autoSeleccionado.modelo << endl;
    archivoProforma << "Precio Contado\t\t: " << fixed << setprecision(2) << precioContado << endl;
    archivoProforma << "Interes Credito\t\t: " << interesCredito << endl;
    archivoProforma << "Pago mensual\t\t: " << pagoMensual << endl;
    archivoProforma << "Precio Total\t\t: " << precioTotal << endl;

    archivoProforma.close();
    cout<< "Proforma generada con exito.\n";
}

int main() {
    int opcion = 0; 

    while (opcion != 3) {
        cout << "Seleccione la operacion a realizar:\n";
        cout << "1. Reporte de ventas\n";
        cout << "2. Proforma de un auto\n";
        cout << "3. Salir\n"; 
        cout << "Opcion: ";
        cin >> opcion;
        
        switch (opcion) {
            case 1:
                generarReporteVentas();
                break;
            case 2:
                generarProformaAuto();
                break;
            case 3: 
                cout << "Saliendo del programa.\n";
                break;
            default:
                cout << "Opción no valida. Por favor, intente nuevamente.\n";
                break;
        }


        cin.ignore(numeric_limits<streamsize>::max(), '\n');
    }

    return 0;
}