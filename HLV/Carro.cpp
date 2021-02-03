#include "Carro.h"

namespace TP2 {
int Carro::getEstadoAtual() const
{
    return estadoAtual;
}

void Carro::setEstadoAtual(int estadoAtual)
{
    this->estadoAtual = estadoAtual;
}

Imagem Carro::getFoto() const
{
    return foto;
}

void Carro::setFoto(const Imagem &value)
{
    foto = value;
}

Carro::Carro():
    idMarca(0),
    idCategoria(0),
    cor(""),
    estadoDeConservacao(""),
    placa(""),
    kmInicial(0),
    kmFinal(0),
    valorCompra(0),
    categoria(),
    marca(),
    modelo(),
    nome(""),
    estadoAtual(0),
    foto()
{

}

Carro::Carro(int idMarca, int idCategoria, QString cor, QString estadoDeConservacao,
             double valorCompra, double kmInicial, double kmFinal, QString placa, Categoria categoria, Marca marca, Modelo modelo, QString nome , int estadoAtual, Imagem foto):
    idMarca(idMarca),
    idCategoria(idCategoria),
    cor(cor),
    estadoDeConservacao(estadoDeConservacao),
    valorCompra(valorCompra),
    kmInicial(kmInicial),
    kmFinal(kmFinal),
    placa(placa),
    categoria(categoria),
    marca(marca),
    modelo(modelo),
    nome(nome),
    estadoAtual(estadoAtual),
    foto(foto)
{

}

QString Carro::getNome() const
{
    return nome;
}

void Carro::setNome(const QString &nome)
{
    this->nome = nome;
}

int Carro::getIdModelo() const
{
    return idModelo;
}

void Carro::setIdModelo(int idModelo)
{
    this->idModelo = idModelo;
}

Categoria Carro::getCategoria() const
{
    return categoria;
}

void Carro::setCategoria(const Categoria categoria)
{
    this->categoria = categoria;
}

Marca Carro::getMarca() const
{
    return marca;
}

void Carro::setMarca(const Marca marca)
{
    this->marca = marca;
}

Modelo Carro::getModelo() const
{
    return modelo;
}

void Carro::setModelo(const Modelo modelo)
{
    this->modelo = modelo;
}



double Carro::getValorCompra() const
{
    return valorCompra;
}

void Carro::setValorCompra(double valorCompra)
{
    this->valorCompra = valorCompra;
}

double Carro::getKmInicial() const
{
    return kmInicial;
}

void Carro::setKmInicial(double kmInicial)
{
    this->kmInicial = kmInicial;
}

double Carro::getKmFinal() const
{
    return kmFinal;
}

void Carro::setKmFinal(double kmFinal)
{
    this->kmFinal = kmFinal;
}

QString Carro::getPlaca() const
{
    return placa;
}

void Carro::setPlaca(const QString & placa)
{
    this->placa = placa;
}

void Carro::montarObjeto(QString &str)
{
    try {

        QStringList strList = str.split(';');
        if(strList.length()!=11)
            throw QString("Erro, faltam informações no carro");
        placa = strList[0];
        nome = strList[1];
        idMarca=strList[2].toInt();
        idCategoria=strList[3].toInt();
        idModelo=strList[4].toInt();
        cor = strList[5];
        estadoDeConservacao = strList[6];
        valorCompra = strList[7].toDouble();
        kmInicial = strList[8].toDouble();
        kmFinal = strList[9].toDouble();
        estadoAtual = strList[10].toInt();
    }catch (QString &erro) {
        throw QString("Erro no metodo montar Carro!");
    }


}

QString Carro::desmontarObjeto() const
{

    try{
        QString saida = placa;
        saida += ";";
        saida += nome;
        saida += ";";
        saida += QString::number(idMarca);
        saida += ";";
        saida += QString::number(idCategoria);
        saida += ";";
        saida += QString::number(idModelo);
        saida += ";";
        saida += cor;
        saida += ";";
        saida += estadoDeConservacao;
        saida += ";";
        saida +=  QString::number(valorCompra);
        saida += ";";
        saida += QString::number(kmInicial);
        saida += ";";
        saida += QString::number(kmFinal);
        saida += ";";
        saida += QString::number(estadoAtual);
        saida +="\n";
        return saida;
    }catch (...){
        throw QString("Erro no metodo desmontar categoria!");
    }
}

}
