#ifndef MODULO1_OBJETO_HPP
#define MODULO1_OBJETO_HPP


class Objeto {
    public:
        Objeto(int id, double x, double y, double largura);
        Objeto();

        void movimentar(double x, double y);
        bool estaNoIntervalo(Objeto objeto);

        Objeto& operator = (const Objeto& objeto);

        int getId();
        double getX();
        double getY();
        double getInicio();
        void setInicio(double inicio);
        double getFim();
        void setFim(double fim);

    private:
        int _id;
        double _x, _y;
        double _largura;
        
        // NOTA: atributos para verficar onde começa e termina um objeto no eixo x
        double _inicio, _fim;

        // NOTA: calcula inicio e fim do objeto sempre que ele é criado/movimentado
        void _calcularIntervalo();
};

#endif