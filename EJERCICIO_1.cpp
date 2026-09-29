#include <iostream>
#include <string>
#include <cstdlib>
#include <locale.h>
#include <cmath>
#include <string>
#include <string.h>
#include <cctype>
#include <ctype.h>
#include <vector>
using namespace std;

class Juego
{
protected:
    string titulo = "";
    int precioBase = 0;
public:
    Juego(string parametroTipoJuego = "") {
        cout << "Ingrese el titulo del juego " << parametroTipoJuego;
        getline(cin,titulo);
        if (titulo == "") {
            getline(cin,titulo);
        }
        cout << "Ingrese el precio base del juego " << parametroTipoJuego;
        cin >> precioBase;
    }
    //GETTERS
    string getTitulo() {
        return titulo;
    }
    int getPrecioBase() {
        return precioBase;
    }
    //LO OTRO
    void aplicarDescuento(float parametroPorcentaje) {
        if (parametroPorcentaje < 0)
        {
            parametroPorcentaje = 0;
        }
        if (parametroPorcentaje > 100)
        {
            parametroPorcentaje = 100;
        }
        precioBase -= precioBase * (parametroPorcentaje / 100.0);
    }
    void aplicarDescuento(float parametroPorcentaje, float parametroCuponFijo) {
        if (parametroPorcentaje < 0)
        {
            parametroPorcentaje = 0;
        }
        if (parametroPorcentaje > 100)
        {
            parametroPorcentaje = 100;
        }
        precioBase -= precioBase * (parametroPorcentaje / 100.0);
        precioBase -= parametroCuponFijo;
        if (precioBase < 0)
        {
            precioBase = 0;
        }
    }
    ~Juego() {}
};

class JuegoFisico: public Juego
{
private:
   float costoEnvio = 0;
public:
    JuegoFisico():Juego("fisico ") {
        cout << "Ingrese el costo del envio del juego fisico ";
        cin >> costoEnvio;
    }
    //GETTERS
    float getCostoEnvio() {
        return costoEnvio;
    }
    //LO OTRO
    float calcularPrecioFinal() {
        return precioBase + costoEnvio;
    }
    ~JuegoFisico() {}
};

class JuegoDigital: public Juego
{
private:
   float descuentoDigital = 0;
public:
    JuegoDigital():Juego("digital ") {
        cout << "Ingrese el descuento del juego digital ";
        cin >> descuentoDigital;
        while (descuentoDigital < 0 || descuentoDigital > 100)
        {
            cout << "Lo siento, el descuento tiene que ser un rango del 0 al 100, ingreselo de nuevo ";
            cin >> descuentoDigital;
        }
    }
    //GETTERS
    float getDescuentoDigital() {
        return descuentoDigital;
    }
    //LO OTRO
    float calcularPrecioFinal() {
        return precioBase;
    }
    ~JuegoDigital() {}
};

class Cliente
{
private:
    string nombre = "";
    vector <JuegoFisico> juegosFisicos;
    vector <JuegoDigital> juegosDigitales;
public:
    Cliente() {
        cout << "Ingrese su nombre de cliente ";
        getline(cin,nombre);
        if (nombre == "") {
            getline(cin,nombre);
        }
    }
    //GETTERS
    string getNombre() {
        return nombre;
    }
    //LO OTRO
    void comprarJuegoFisico(JuegoFisico parametroJuegoFisico) {
        juegosFisicos.push_back(parametroJuegoFisico);
        cout << "juego fisico comprado!!\n";
    }
    void comprarJuegoDigital(JuegoDigital parametroJuegoDigital) {
        juegosDigitales.push_back(parametroJuegoDigital);
        cout << "juego digital comprado!!\n";
    }
    void mostrarResumenCompra() {
        if (juegosFisicos.size() == 0 && juegosDigitales.size() == 0) {
            cout << "Aun no tiene compras, COMPRE\n";
        }
        for (int i = 0; i < juegosFisicos.size(); i++)
        {
            cout << "Juego fisico " << juegosFisicos[i].getTitulo() << " Precio Total: " << juegosFisicos[i].calcularPrecioFinal();
        }
        for (int i = 0; i < juegosDigitales.size(); i++)
        {
            cout << "Juego digital " << juegosDigitales[i].getTitulo() << " Precio Total: " << juegosDigitales[i].calcularPrecioFinal();
        }
    }
    float comprarProductos() {
        if (juegosFisicos.size() == 0 && juegosDigitales.size() == 0) {
            return -1;
        }
        float totalAbonar = 0;
        for (int i = 0; i < juegosFisicos.size(); i++)
        {
            totalAbonar += juegosFisicos[i].calcularPrecioFinal();
        }
        for (int i = 0; i < juegosDigitales.size(); i++)
        {
            totalAbonar += juegosDigitales[i].calcularPrecioFinal();
        }
        return totalAbonar;
    }
    ~Cliente() {}
};

int main() {
    vector <JuegoFisico> juegosFisicosExistentes;
    vector <JuegoDigital> juegosDigitalesExistentes;
    int juegosCargar = 0;

    cout << "Este programa carga juegos tanto fisicos como digitales y luego te hace pasar a cliente para comprar estos juegos\n";
    cout << "Ingrese los juegos a cargar ";
    cin >> juegosCargar;

    for (int i = 0; i < juegosCargar; i++)
    {
        int fisicoDigital = 0;
        cout << "Ingrese si el juego a cargar es fisico (0) o digital (1) ";
        cin >> fisicoDigital;
        while (fisicoDigital < 0 || fisicoDigital > 1)
        {
            cout << "Lo siento, debera poner 0 para un juego fisico o 1 para un juego digital, ingreselo de nuevo ";
            cin >> fisicoDigital;
        }
        if (fisicoDigital == 0)
        {
            juegosFisicosExistentes.push_back(JuegoFisico());
        }
        else if (fisicoDigital == 1) {
            juegosDigitalesExistentes.push_back(JuegoDigital());
        }
    }

    int tipoDeOperacion = 0;

    Cliente cliente1;

    cout << "Cliente " << cliente1.getNombre() << " A COMPRAR!!!\n";

    cout << "Ingrese 0 para comprar un juego\n";
    cout << "Ingrese 1 para ver los juegos existentes\n";
    cout << "Ingrese 2 para ver sus compras\n";
    cout << "Ingrese 3 para comprar si tiene productos\n";
    cout << "Ingrese 4 para aplicar un descuento y/o un cupon\n";
    cout << "Ingrese 5 para mas informacion\n";

    while (1 != 0)
    {
        string nombreJuego = "";
        cin >> tipoDeOperacion;
        switch (tipoDeOperacion)
        {
        case 0: {
            if (juegosFisicosExistentes.size() == 0 && juegosDigitalesExistentes.size() == 0) {
                cout << "Lo siento, tiene tanta plata que compro todos los juegos :C. Guardela para seguirla gastando en los siguientes juegos que tendremos \n";
                break;
            }
            cout << "Ingrese el nombre del juego a comprar \n";
            getline(cin,nombreJuego);
            if (nombreJuego == "") {
                getline(cin,nombreJuego);
            }
            if (juegosFisicosExistentes.size() != 0)
            {
                for (int i = 0; i < juegosFisicosExistentes.size(); i++)
                {
                    if (nombreJuego == juegosFisicosExistentes[i].getTitulo())
                    {
                        cliente1.comprarJuegoFisico(juegosFisicosExistentes[i]);
                        cout << "Juego comprado exitosamente!!\n";
                    }
                }
            }
            if (juegosDigitalesExistentes.size() != 0)
            {
                for (int i = 0; i < juegosDigitalesExistentes.size(); i++)
                {
                    if (nombreJuego == juegosDigitalesExistentes[i].getTitulo())
                    {
                        cliente1.comprarJuegoDigital(juegosDigitalesExistentes[i]);
                        cout << "Juego comprado exitosamente!!\n";
                    }
                }
            }
        }
        break;
        case 1: {
            if (juegosFisicosExistentes.size() == 0 && juegosDigitalesExistentes.size() == 0) {
                cout << "Lo siento, tiene tanta plata que compro todos los juegos :C. Guardela para seguirla gastando en los siguientes juegos que tendremos \n";
                break;
            }
            cout << "Estos son los juegos existentes:\n";
            for (int i = 0; i < juegosFisicosExistentes.size(); i++)
            {
                cout << "Titulo juego fisico: " << juegosFisicosExistentes[i].getTitulo() << " Precio Total: " << juegosFisicosExistentes[i].calcularPrecioFinal() << endl;
            }
            for (int i = 0; i < juegosDigitalesExistentes.size(); i++)
            {
                cout << "Titulo juego digital: " << juegosDigitalesExistentes[i].getTitulo() << " Precio Total: " << juegosDigitalesExistentes[i].calcularPrecioFinal() << endl;
            }
        }
        break;
        case 2: {
            cliente1.mostrarResumenCompra();
        }
        break;
        case 3: {
            if (cliente1.comprarProductos() == -1)
            {
                cout << "Lo siento, aun no ha comprado productos, por favor, COMPRE\n";
                break;
            }
            cout << "Compra exitosa de $" << cliente1.comprarProductos(); 
            return 0;
        }
        break;
        case 4: {
            if (juegosFisicosExistentes.size() == 0 && juegosDigitalesExistentes.size() == 0) {
                cout << "Lo siento, tiene tanta plata que compro todos los juegos :C. Guardela para seguirla gastando en los siguientes juegos que tendremos \n";
                break;
            }
            int descuentoODescuentoYCupon = 0, descuento = 0;
            float cupon = 0;
            cout << "Ingrese 0 para aplicar un descuento\n";
            cout << "Ingrese 1 para aplicar un descuento y un cupon\n";
            cin >> descuentoODescuentoYCupon;
            while (descuentoODescuentoYCupon < 0 || descuentoODescuentoYCupon > 1)
            {
                cout << "Ingrese 0 para aplicar un descuento\n";
                cout << "Ingrese 1 para aplicar un descuento y un cupon\n";
                cin >> descuentoODescuentoYCupon;
            }
            cout << "Ingrese el descuento a aplicar en el juego ";
            cin >> descuento;
            if (descuentoODescuentoYCupon == 1)
            {
                cout << "Ingrese el cupon a aplicar en el juego ";
                cin >> cupon;
            }
            cout << "Ingrese el nombre del juego a aplicar el descuento y/o cupon \n";
            getline(cin,nombreJuego);
            if (nombreJuego == "") {
                getline(cin,nombreJuego);
            }
            if (juegosFisicosExistentes.size() != 0)
            {
                for (int i = 0; i < juegosFisicosExistentes.size(); i++)
                {
                    if (nombreJuego == juegosFisicosExistentes[i].getTitulo())
                    {
                        if (descuentoODescuentoYCupon == 0)
                        {
                            juegosFisicosExistentes[i].aplicarDescuento(descuento);
                        }
                        if (descuentoODescuentoYCupon == 1)
                        {
                            juegosFisicosExistentes[i].aplicarDescuento(descuento,cupon);
                        }
                        
                    }
                }
            }
            if (juegosDigitalesExistentes.size() != 0)
            {
                for (int i = 0; i < juegosDigitalesExistentes.size(); i++)
                {
                    if (nombreJuego == juegosDigitalesExistentes[i].getTitulo())
                    {
                        if (descuentoODescuentoYCupon == 0)
                        {
                            juegosFisicosExistentes[i].aplicarDescuento(descuento);
                        }
                        if (descuentoODescuentoYCupon == 1)
                        {
                            juegosFisicosExistentes[i].aplicarDescuento(descuento,cupon);
                        }
                    }
                }
            }
        }
        break;
        case 5: {
            cout << "Ingrese 0 para comprar un juego\n";
            cout << "Ingrese 1 para ver los juegos existentes\n";
            cout << "Ingrese 2 para ver sus compras\n";
            cout << "Ingrese 3 para comprar si tiene productos\n";
            cout << "Ingrese 4 para mas informacion\n";
        }
        break;
        default:
            cout << "Cliente " << cliente1.getNombre();
            cout << "Ha habido un error en la solicitud o ingreso un dato erroneo";
            cout << "Para mas informacion ingrese 3";
        }
    }
    return 0;
}