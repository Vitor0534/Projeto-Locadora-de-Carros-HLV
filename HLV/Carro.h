#ifndef CARRO_H
#define CARRO_H
#include "Marca.h"
#include "Categoria.h"
#include "Modelo.h"
#include "Imagem.h"
#include <TransformarDados.h>
namespace TP2 {

class Carro : public TransformarDados
{
private:
    int idModelo;
    int idMarca;
    int idCategoria;
    QString cor;
    QString estadoDeConservacao;
    double valorCompra;
    double kmInicial;
    double kmFinal;
    QString placa;
    QString nome;
    Categoria categoria;
    Marca marca;
    Modelo modelo;
    int estadoAtual; //0 disponivel 1 Locado
    Imagem foto;
public:
    Carro();
    Carro(int idMarca, int idCategoria, QString cor, QString estadoDeConservacao, double valorCompra
          , double kmInicial, double kmFinal, QString placa, Categoria categoria, Marca marca, Modelo modelo, QString nome,
          int estadoAtual, Imagem foto);
    void setIdMarca(int id){this->idMarca=id;}
    void setIdCategoria(int id){this->idCategoria=id;}
    void setCor(QString cor){this->cor=cor;}
    void setEstadoDeConservacao(QString estado){this->estadoDeConservacao=estado;}

    int getIdMarca()const {return this->idMarca;}
    int getIdCategoria()const{return this->idCategoria;}
    QString getCor()const{return this->cor;}
    QString getEstadoDeConservacao()const{return this->estadoDeConservacao;}

    void montarObjeto(QString & str);
    QString desmontarObjeto()const;

    double getKmInicial() const;
    void setKmInicial(double);

    double getKmFinal() const;
    void setKmFinal(double);

    QString getPlaca() const;
    void setPlaca(const QString &);

    double getValorCompra() const;
    void setValorCompra(double);

    int getIdModelo() const;
    void setIdModelo(int idModelo);

    Categoria getCategoria() const;
    void setCategoria(const Categoria);

    Marca getMarca() const;
    void setMarca(const Marca);

    Modelo getModelo() const;
    void setModelo(const Modelo);

    QString getNome() const;
    void setNome(const QString &);
    int getEstadoAtual() const;
    void setEstadoAtual(int estadoAtual);

    Imagem getFoto() const;
    void setFoto(const Imagem &value);
};

}

#endif // CARRO_H
