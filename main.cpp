 //Universidad Estatal a Distancia
//Escuela de Ciencias Sociales
//Cátedra de Tecnología de Sistemas
//00831 - Introducción a la Programación
//Prof. Johan Manuel Acosta Ibáñez
//Cuatrimestre II - 2020

//Proyecto Programado
//Sistema de Registro de Pagos de Condominio
//Estudiante: Dayron Antony Chaves Sandoval
//Cedula: 0305240018
//Fecha de Entrega: 30 de Agosto del año 2020

//Nota: Este código evita fuera de los comentarios el uso de tildes, la letra ñ, y otros signos presentes solo en el idioma español-
//para mantener la compatibilidad. No deben ser considerados como errores gramaticales.

//Librerías
#include <iostream>
#include <fstream>
#include <iomanip>

using namespace std;
using std::ofstream;
using std::ifstream;

//Prototipos de las funciones
void ingreso_filial();
void generar_cobros();
void registrar_pago();
void listar_pagos_pendientes();
void listar_pagos_realizados();

//Menú principal de la aplicación.
int main()
{
    int Opcion_Menu = 0;
    do
    {
        //Imprimir el menú en pantalla
        system("cls");
        cout << "==Sistema de Administracion de Filiales de Condominios==" << endl;
        cout << "1) Registrar un nuevo duenio" << endl;
        cout << "2) Generar cobros" << endl;
        cout << "3) Consultar Filial | Mostrar Pagos Pendientes | Registrar Pago" << endl;
        cout << "4) Listar los ultimos 20 pagos pendientes" << endl;
        cout << "5) Listar los ultimos 20 pagos realizados" << endl;
        cout << "0) Salir" << endl << endl;
        cout << "Elige una opcion: ";
        cin >> Opcion_Menu;

        //Verificación de la opción elegida
        if (Opcion_Menu < 0 || Opcion_Menu > 5 )
        {
            cout << "Esa opcion no existe, intentelo de nuevo. " << endl << endl;
            system("pause");
        }

        //Acciones a tomar por cada una de las opciones del menú.
        switch( Opcion_Menu )
		{

			case 1:
			    system("cls");
                ingreso_filial();
				break;

			case 2:
			    system("cls");
                generar_cobros();
				break;

            case 3:
			    system("cls");
                registrar_pago();
				break;

            case 4:
			    system("cls");
                listar_pagos_pendientes();
				break;

            case 5:
			    system("cls");
                listar_pagos_realizados();
				break;

			case 0:
				break;

			default:
				break;
		}
    }
    while( Opcion_Menu != 0 );
return 0;
}

//Esta función se encarga de crear el archivo de texto "Duenios.txt", en el cual se registran los dueños de las filiales.
//Nota: Existe un proceso de verificación de filiales con números de identificación duplicados.
void ingreso_filial()
{

    string nombre_duenio;
    int numero_filial = 0;
    int numero_filial_auxiliar = 0;
    double cuota = 0;
    char decision;

    ofstream registro;
    ifstream verificacion;

    do
    {
        //Código para abrir los archivos en modo de lectura/escritura.
        registro.open("Duenios.txt", ios::out | ios::app);
        verificacion.open("Duenios.txt", ios::in);

        if ( registro.is_open() && verificacion.is_open() )
        {

            ///PROCESO DE VERIFICACIÓN DE OCUPACIÓN
            bool filial_ocupada = false;
            cout << "Ingrese el numero de filial: ";
            cin >> numero_filial_auxiliar;

            while ( verificacion >> numero_filial >> nombre_duenio >> cuota )
            {
                if (numero_filial_auxiliar == numero_filial)
                {
                    cout<<"Lo sentimos, esta filial ya esta ocupada." << endl << endl;
                    filial_ocupada = true;
                    break;
                }
            }

            ///PROCESO DE REGISTRO DEL NUEVO DUEÑO
            if ( filial_ocupada == false )
            {
                cout << "Ingresa el nombre del nuevo duenio: ";
                cin >> nombre_duenio;

                cout << "Ingrese la cuota que pagara este duenio: ";
                cin >> cuota;

                registro << numero_filial_auxiliar << " " << nombre_duenio << " " << cuota << endl;
                cout<<"Se ha registrado el nuevo duenio!" << endl << endl;
            }

            cout<<"Desea ingresar otro duenio mas? S/N: ";
            cin >> decision;

        }

        else
        {
            cout << "ERROR CRITICO: No fue posible crear el archivo." << endl;
            decision = 'N';
            system("pause");

        }

        registro.close();
        verificacion.close();

    }
    while ( decision == 'S' || decision == 's' );

}

//Esta función se encarga de generar el cobro por mes de todas las filiales previamente existentes en "Duenios.txt".
//Crea el archivo "Pendientes.txt".
void generar_cobros()
{
    string nombre_duenio;
    int numero_filial = 0;
    double cuota = 0;
    int anio = 0;
    int mes = 0;
    bool anio_valido = false;
    bool mes_valido = false;

    ifstream leer;
    ofstream generar_cobro;

    //Código para abrir los archivos en modo de lectura/escritura.
    leer.open("Duenios.txt", ios::in);
    generar_cobro.open("Pendientes.txt", ios::out | ios::app);

    if ( generar_cobro.is_open() && leer.is_open() )
    {
        do
        {
            system("cls");
            ///Introducir Fecha de Cobro
            cout << "Ingrese el anio del cobro que desea generar: ";
            cin >> anio;

            cout << "Ingrese el mes del cobro que desea generar: ";
            cin >> mes;

            ///Verificar la fecha introducida por el usuario
            if ( (anio > 2019) && (anio < 2101)  ) anio_valido = true;

            if ( (mes < 13) && (mes > 0)  ) mes_valido = true;

            if ( (mes_valido == false) || (anio_valido == false) )
            {
                cout << "Esta seguro de que a escrito la fecha correctamente?, por favor intentelo de nuevo." << endl << endl;
                system("pause");
            }

        }
        while ( (mes_valido == false) || (anio_valido == false) );

        ///Generar el archivo Pendientes.txt
        while ( leer >> numero_filial >> nombre_duenio >> cuota )
        {
            generar_cobro << numero_filial << " " << anio << "-" << mes << " " << cuota << endl;
        }

        cout<<"Se a generado el cobro exitosamente!" << endl << endl;
        system("pause");
    }

    else
    {
        cout << "ATENCION: Usted no a registrado ningun duenio!, regrese al menu principal y seleccione la opcion 1." << endl << endl;
        system("pause");
    }

    leer.close();
    generar_cobro.close();

}

//Esta función permite consultar los pagos pendientes de una filial, para posteriormente pagarlos.
//Crea el archivo "Pagados.txt" y "NuevoPendientes.txt".
void registrar_pago()
{

    int numero_filial = 0;
    int filial_consultada = 0;
    bool filial_existe = false;
    bool fecha_existe = false;
    bool mes_valido = false;
    bool anio_valido = false;
    bool dia_valido = false;
    int anio = 0;
    int anio_de_pago = 0;
    int anio_actual = 0;
    int mes = 0;
    int mes_de_pago = 0;
    int mes_actual = 0;
    int mes_absoluto = 0;
    int dia_actual = 0;
    int cantidad_dias1 = 0;
    int cantidad_dias2 = 0;
    int total_dias = 0;
    double cuota = 0;
    double cuota_auxiliar = 0;
    double nueva_cuota = 0;
    char decision_pago;
    char confirmar_pago;

    ofstream pago;
    ofstream escribir_NuevoPendientes;
    ifstream consulta;

    //Código para abrir los archivos en modo de lectura/escritura.
    pago.open("Pagados.txt", ios::out | ios::app);
    escribir_NuevoPendientes.open( "NuevoPendientes.txt", ios::out );
    consulta.open("Pendientes.txt", ios::in);

    if ( pago.is_open() && consulta.is_open() && escribir_NuevoPendientes.is_open() )
    {
        ///Proceso de Consulta de Filial
        cout << "Ingrese el numero de filial que desea consultar: ";
        cin >> filial_consultada;

        while ( consulta >> numero_filial >> anio >> mes >> cuota )
        {
            if ( filial_consultada == numero_filial )
            {
                mes_absoluto = abs(mes);
                filial_existe = true;
                ///Proceso para imprimir los pagos pendientes del cliente en pantalla
                cout << "" << endl;
                cout << "Numero de filial:      " << filial_consultada << endl;
                cout << "anio:                  " << anio << endl;
                cout << "Mes:                   " << mes_absoluto << endl;
                cout << fixed << setprecision(2) << "Cuota:                 " << cuota << endl;
                cout << "______________________________________________________" << endl << endl;
            }
        }

        if (filial_existe == true)
        {
            ///Proceso de pago
            cout << "Desea realizar el pago? S/N: ";
            cin >> decision_pago;

            while (decision_pago == 'S' || decision_pago == 's' )
            {
                consulta.clear();
                consulta.seekg(0, ios::beg);

                ///Proceso de digitacion de la fecha que corresponde a la cuota.
                cout << "" << endl;
                cout << " = FECHA DE CUOTA = " << endl;
                cout << "Ingrese el anio que desea pagar: ";
                cin >> anio_de_pago;

                cout << "Ingrese el mes del anio " << anio_de_pago << " que desea pagar: ";
                cin >> mes_de_pago;

                ///Proceso de digitacion de la fecha en que se pago la cuota
                while ( consulta >> numero_filial >> anio >> mes >> cuota )
                {
                    if (numero_filial == filial_consultada)
                    {
                        mes_absoluto = abs(mes);
                        if ( anio == anio_de_pago && mes_absoluto == mes_de_pago )
                        {
                            fecha_existe = true;
                            cout << "______________________________________________________" << endl << endl;
                            do
                            {
                                cout << " = FECHA ACTUAL = " << endl;
                                cout << "Ingrese el anio actual: ";
                                cin >> anio_actual;

                                cout << "Ingrese el mes actual: ";
                                cin >> mes_actual;

                                cout << "Ingrese el dia actual: ";
                                cin >> dia_actual;

                                ///Verificación de Fecha
                                if ( (anio_actual > 2019) && (anio_actual < 2101)  ) anio_valido = true;

                                if ( (mes_actual < 13) && (mes_actual > 0)  ) mes_valido = true;

                                if ( (dia_actual < 32) && (dia_actual > 0)  ) dia_valido = true;

                                if ( (mes_valido == false) || (anio_valido == false) || (dia_valido == false) )
                                {
                                    cout << "Esta seguro de que a escrito la fecha correctamente?, por favor intentelo de nuevo." << endl << endl;
                                    system("pause");
                                }
                            }
                            while ( (mes_valido == false) || (anio_valido == false) || (dia_valido == false) );

                            cout << "______________________________________________________" << endl << endl;
                            cout << "La fecha actual es: " << anio_actual << "/" << mes_actual << "/" << dia_actual << endl;
                            cout << "Usted quiere pagar la cuota: " << anio_de_pago << "/" << mes_de_pago << endl;

                            ///Calculo de días
                            cantidad_dias1 = ( anio_de_pago * 365 ) + ( ( mes_de_pago - 1 ) * 30 );

                            cantidad_dias2 = ( anio_actual * 365 ) + ( ( mes_actual - 1 ) * 30 ) + ( dia_actual );

                            total_dias = cantidad_dias2 - cantidad_dias1;

                            ///Calculo de la cuota
                            if (total_dias >= 11)
                            {
                                cuota_auxiliar = cuota;
                                nueva_cuota = ( ( cuota * 10 ) / 100 ) + cuota_auxiliar;
                            }

                            else
                            {
                                nueva_cuota = cuota;
                            }

                            cout <<  "El monto a pagar es de: " << fixed << setprecision(2) << nueva_cuota << endl << endl;
                            cout << "Aun desea realizar el pago? S/N: ";
                            cin >> confirmar_pago;

                                ///Proceso para escribir Pagados.txt y Nuevo Pendientes.txt
                                if ( confirmar_pago == 'S' || confirmar_pago == 's' )
                                {
                                    consulta.clear();
                                    consulta.seekg(0, ios::beg);

                                    while ( consulta >> numero_filial >> anio >> mes >> cuota )
                                    {
                                        //Escribir Pagados.txt
                                        mes_absoluto = abs(mes);
                                        if ( numero_filial == filial_consultada && anio == anio_de_pago && mes_absoluto == mes_de_pago )
                                        {
                                            pago << filial_consultada << " " << anio_de_pago << "-" << mes_de_pago << " " << nueva_cuota << endl;
                                        }

                                        else if ( numero_filial != filial_consultada || anio != anio_de_pago || mes_absoluto != mes_de_pago )
                                        {
                                            //Escribir NuevoPendientes.txt
                                            escribir_NuevoPendientes << numero_filial << " " << anio << mes << " " << cuota << endl;
                                        }
                                    }

                                    cout << "Se ha registrado el pago exitosamente!" << endl << endl;
                                    system("pause");
                                    decision_pago = 'N';
                                    break;
                                }

                                else
                                {
                                    decision_pago = 'N';
                                    break;
                                }
                        }
                    }
                }

                if ( fecha_existe == false )
                {
                cout << "Lo sentimos, esa fecha no existe en la filial " << filial_consultada << ". Intentelo de nuevo." << endl;
                system("pause");
                }
            }
        }

        else
        {
            cout << "Lo sentimos, esa filial aun no existe o no ha recibido cobros." << endl << endl;
            system("pause");
        }

    }

    else
    {
        cout << "ATENCION: Usted aun no a generado los cobros!. Regrese al menu principal y seleccione la opcion 2." << endl << endl;
        system("pause");
    }

    consulta.close();
    pago.close();
    escribir_NuevoPendientes.close();
    if ( confirmar_pago == 'S' || confirmar_pago == 'S')
    {
        remove("Pendientes.txt");
        rename("NuevoPendientes.txt","Pendientes.txt");
    }
}

//Esta función lee las ultimas 20 lineas de "Pendientes.txt" y las imprime en pantalla.
void listar_pagos_pendientes()
{

    int numero_filial = 0;
    int anio = 0;
    int mes = 0;
    double cuota = 0;
    int posicion_actual = 0;
    int limite = 21;
    int total_de_lineas = 0;
    int total_auxiliar = 0;

    ifstream leer_pendientes;

    //Código para abrir el archivo en modo de lectura.
    leer_pendientes.open("Pendientes.txt", ios::in);

    if (leer_pendientes.is_open())
    {
            //Contador de lineas
            while (leer_pendientes >> numero_filial >> anio >> mes >> cuota)
            {
                total_de_lineas++;
            }

            if (total_de_lineas == 0)
            {
                cout << "Esta lista esta en blanco." << endl;
            }

            //Calculo del numero correcto de lineas para cumplir la tarea.
            if (total_de_lineas > 20)
            {
                total_auxiliar = total_de_lineas;
                total_auxiliar = total_auxiliar - limite;
            }

            leer_pendientes.clear();
            leer_pendientes.seekg(0, ios::beg);

            if (total_de_lineas > 20)
            {
                //Establecer la posición adecuada en el archivo para imprimir los últimos 20
                for (; posicion_actual < total_auxiliar; posicion_actual++)
                {
                    leer_pendientes >> numero_filial >> anio >> mes >> cuota;
                }
            }

            //Imprimir en pantalla los últimos 20.
            for (; posicion_actual < total_de_lineas; posicion_actual++)
            {
                leer_pendientes >> numero_filial >> anio >> mes >> cuota;
                cout << numero_filial << " " << anio << mes << " " << fixed << setprecision(2) << cuota << endl;
            }
        cout << endl;
        system("pause");
    }

    else
    {
        cout << "ATENCION: Usted aun no a generado los cobros!. Regrese al menu principal y seleccione la opcion 2." << endl << endl;
        system("pause");
    }

    leer_pendientes.close();
}

//Esta función lee las ultimas 20 lineas de "Pagados.txt" y las imprime en pantalla.
//Nota: Es idéntica a la de pendientes, por lo tanto, no contiene comentarios.
void listar_pagos_realizados()
{

    int numero_filial = 0;
    int anio = 0;
    int mes = 0;
    double cuota = 0;
    int posicion_actual = 0;
    int limite = 21;
    int total_de_lineas = 0;
    int total_auxiliar = 0;

    ifstream leer_pagados;

    leer_pagados.open("Pagados.txt", ios::in);

    if (leer_pagados.is_open())
    {
            while ( leer_pagados >> numero_filial >> anio >> mes >> cuota)
            {
                total_de_lineas++;
            }

            if (total_de_lineas == 0)
            {
                cout << "Esta lista esta en blanco." << endl;
            }

            if (total_de_lineas > 20)
            {
                total_auxiliar = total_de_lineas;
                total_auxiliar = total_auxiliar - limite;
            }

            leer_pagados.clear();
            leer_pagados.seekg(0, ios::beg);

            if (total_de_lineas > 20)
            {
                for (; posicion_actual < total_auxiliar; posicion_actual++)
                {
                    leer_pagados >> numero_filial >> anio >> mes >> cuota;
                }
            }

            for (; posicion_actual < total_de_lineas; posicion_actual++)
            {
                leer_pagados >> numero_filial >> anio >> mes >> cuota;
                cout << numero_filial << " " << anio << mes << " " << fixed << setprecision(2) << cuota << endl;
            }
        cout << endl;
        system("pause");
    }

    else
    {
        cout << "ATENCION: Usted aun no a recibido ningun pago!. Regrese al menu principal y seleccione la opcion 3." << endl << endl;
        system("pause");
    }

    leer_pagados.close();
}
