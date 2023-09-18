#include <iostream>
#include <string>
using namespace std;

class Alquilable
{
public:
    virtual ~Alquilable(){};
    virtual string getDescripcion() const = 0;
    virtual string getTipo() const = 0;
    virtual float obtenerPresupuesto() const = 0;
};

class Hotel : public Alquilable
{
private:
    double coste_base;
    string tipo;
    string descripcion;

public:
    Hotel(string desc) : coste_base(100), tipo("Hotel")
    {
        descripcion = desc;
    }

    virtual string getDescripcion() const
    {
        return descripcion;
    }

    virtual string getTipo() const
    {
        return tipo;
    }

    virtual float obtenerPresupuesto() const
    {
        return static_cast<float>(coste_base);
    }
};

class AlquilableDecorador : public Alquilable
{
protected:
    Alquilable *alquilable_;

public:
    AlquilableDecorador(Alquilable *alquilable) : alquilable_(alquilable)
    {
        alquilable_ = alquilable;
    }

    const Alquilable &getAlquilable() const
    {
        return *alquilable_;
    }

    void setAlquilable(Alquilable *alquilable)
    {
        alquilable_ = alquilable;
    }

    string getDescripcion() const
    {
        return getAlquilable().getDescripcion();
    }

    string getTipo() const
    {
        return getAlquilable().getTipo();
    }

    float obtenerPresupuesto() const
    {
        return getAlquilable().obtenerPresupuesto();
    }
};

class PrimeraLineaDePlaya : public AlquilableDecorador
{
public:
    PrimeraLineaDePlaya(Alquilable *alquilable) : AlquilableDecorador(alquilable){

                                                  };
    string getDescripcion() const
    {
        string descripcion = getAlquilable().getDescripcion();
        descripcion += " - Vistas al mar";
        return descripcion;
    }

    float obtenerPresupuesto() const
    {
        float presupuesto = getAlquilable().obtenerPresupuesto();
        presupuesto += 100;
        return presupuesto;
    }
};

class PensionCompleta : public AlquilableDecorador
{
public:
    PensionCompleta(Alquilable *alquilable) : AlquilableDecorador(alquilable){

                                              };
    string getDescripcion() const
    {
        string descripcion = getAlquilable().getDescripcion();
        descripcion += " - Pension completa";
        return descripcion;
    }

    float obtenerPresupuesto() const
    {
        float presupuesto = getAlquilable().obtenerPresupuesto();
        presupuesto += 65;
        return presupuesto;
    }
};

class DescuentoClienteVIP : public AlquilableDecorador
{
public:
    DescuentoClienteVIP(Alquilable *alquilable) : AlquilableDecorador(alquilable){

                                                  };
    string getDescripcion() const
    {
        string descripcion = getAlquilable().getDescripcion();
        descripcion += " - Descuento cliente VIP";
        return descripcion;
    }

    float obtenerPresupuesto() const
    {
        float presupuesto = getAlquilable().obtenerPresupuesto();
        presupuesto *= 0.85;
        return presupuesto;
    }
};

void ClientCode(Alquilable *alquilable)
{

    cout << "RESULTADO: " << alquilable->getTipo() << endl;
    cout << alquilable->getDescripcion() << endl;
    cout << alquilable->obtenerPresupuesto() << " $" << endl;
};

int main()
{
    Alquilable *hotel_torremolinos = new Hotel("Torremolinos");
    ClientCode(hotel_torremolinos);
    Alquilable *decorador1 = new PrimeraLineaDePlaya(hotel_torremolinos);
    cout << "Componente decorado: " << endl;
    ClientCode(decorador1);

    cout << "----------------------------" << endl;

    Alquilable *hotel_denia = new Hotel("Denia");
    ClientCode(hotel_denia);
    Alquilable *decorador2 = new DescuentoClienteVIP(hotel_denia);
    cout << "Componente decorado: " << endl;
    ClientCode(decorador2);
    cout << endl;

    delete hotel_torremolinos;
    delete hotel_denia;
    delete decorador1;
    delete decorador2;

    return 0;
}
