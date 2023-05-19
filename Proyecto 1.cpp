/*Programa para generar una contraseña o codigo con una longitud especificada por el usuario para luego proteger un archivo
nuevamente indicado por el usuario con el codigo creado anteriormente*/

//Probado en Windows 10

#include <iostream>  // Librería para entrada y salida estándar
#include <cstdlib>   // Librería para funciones generales de C
#include <ctime>     // Librería para manipulación de tiempo
#include <fstream>   // Librería para operaciones de entrada/salida de archivos
#include <string>    // Librería para manipulación de cadenas de texto

using namespace std;

//Función para generar el codigo
void GenerarCodigo(int longitud, string* pContrasena){

    //Cadena de caracteres cuya posicion de estos será correspondida por un numero generado posteriormente
    string caracteres = "abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ0123456789!@#$%^&*()";

    srand(time(0));  //Generar valor aleatoria basada en el tiempo actual

    for (int i = 0; i < longitud; i++){
        int indice = rand() % caracteres.length();  //El valor INDICE se obtendra de un numero aleatorio junto y el resto de la division de la longitud de la cadena caracteres
        *pContrasena += caracteres[indice];     //Por cada iteracion, agregar el caracter resultante a la cadena, fruto del numero generado anteriormente
    }
}

//Función para establecer el codigo en el archivo
void EstablecerCodigo(const string& RutaArchivo, const string& contrasena){
    string comando = "cipher /E /A \"" + RutaArchivo + "\"";  //Comando para habilitar cifrado de archivo en el sistema operativo

    //Comprobar si la ejecucion del siguiente comando en el sistema operativo es exitoso
    if (system(comando.c_str()) == 0){  //Ejecutar el comando en el sistema operativo y verificar el resultado
        comando = "echo " + contrasena + " > \"" + RutaArchivo + ":Encryption.txt\"";  //Comando para escribir la contraseña en un archivo

        //Si no hubieron fallos, se le notifica al usuario
        if (system(comando.c_str()) == 0){
            cout<<"Código establecido correctamente en el archivo.\n"<<endl;
            return; //Se vuelve a la funcion principal
        }
    }

    //En caso contrario mostrar un error
    cout<<"No se pudo establecer proteccion en el archivo.\n"<<endl;
}

int main(){

    int longitud;
    cout<<"Ingrese la longitud deseada del codigo: ";
    cin>>longitud;

    //Funcion WHILE para exigir que se introduzca un valor entre 10 y 30
    while (longitud <= 10 || longitud > 30){
        cout<<"El codigo debe contener entre 10 y 30 caracteres: ";
        cin>>longitud;
    }

    string contrasena;
    GenerarCodigo(longitud, &contrasena);  //Llamada a la funcion para crear un codigo con la longitud especificada
    cout<<"------------------------------------------------------"<<endl;
    cout<<"**IMPORTANTE**"<<endl;
    cout<<"Es crucial que el codigo sea guardado de forma segura."<<endl;
    cout<<"------------------------------------------------------\n"<<endl;
    cout<<"Codigo generado: "<<contrasena<<endl<<endl;

    string RutaArchivo;
    cout<<"Ingrese la ruta del archivo: ";
    cin.ignore();  //Ignorar el salto de línea anterior (\n)
    getline(cin, RutaArchivo);  //Leer la ruta del archivo completa

    EstablecerCodigo(RutaArchivo, contrasena);  //Establecer el codigo en el archivo especificado

    return 0;
}
