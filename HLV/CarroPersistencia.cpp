#include "CarroPersistencia.h"
#include <iostream>
using namespace std;
namespace TP2{


CarroPersistencia::CarroPersistencia():
    nomeDoArquivoDeCarros(""),
    nomeDoArquivoDeMarcas(""),
    nomedoArquivoDeCategorias(""),
    nomeDoArquivoDeModelos("")
{

}

CarroPersistencia::CarroPersistencia(QString nomeDoArquivoDeCarros):
    nomeDoArquivoDeCarros(nomeDoArquivoDeCarros)
{

}

CarroPersistencia::CarroPersistencia(QString nomeDoArquivoDeCarros, QString nomeDoArquivoDeMarcas, QString nomedoArquivoDeCategorias, QString nomeDoArquivoDeModelos):
    nomeDoArquivoDeCarros(nomeDoArquivoDeCarros),
    nomeDoArquivoDeMarcas(nomeDoArquivoDeMarcas),
    nomedoArquivoDeCategorias(nomedoArquivoDeCategorias),
    nomeDoArquivoDeModelos(nomeDoArquivoDeModelos)
{

}

void CarroPersistencia::incluir(Carro &carro) const
{
    try {
        std::ofstream arquivoCarros;
        arquivoCarros.open(nomeDoArquivoDeCarros.toStdString().c_str(),
                           std::ios::out|std::ios::app);
        if(!arquivoCarros.is_open()){
            throw QString("Arquivo de carros nao foi aberto - Metodo incluir");
        }
        std::ofstream arquivoMarcas;
        arquivoMarcas.open(nomeDoArquivoDeMarcas.toStdString().c_str(),
                           std::ios::out|std::ios::app);
        if(!arquivoMarcas.is_open()){
            arquivoCarros.close();
            throw QString("Arquivo de carros nao foi aberto - Metodo incluir");
        }
        std::ofstream arquivoCategorias;
        arquivoCategorias.open(nomedoArquivoDeCategorias.toStdString().c_str(),
                               std::ios::out|std::ios::app);
        if(!arquivoCategorias.is_open()){
            arquivoCarros.close();
            arquivoMarcas.close();
            throw QString("Arquivo de carros nao foi aberto - Metodo incluir");
        }

        arquivoCarros<<carro.desmontarObjeto().toStdString();
        arquivoCarros.close();

    } catch (QString &erro) {
        throw erro;
    }
}

void CarroPersistencia::excluir(QString &placa) const
{
    try {

        std::queue<TP2::Carro> fila;

        std::ifstream arquivoCarros;
        arquivoCarros.open(nomeDoArquivoDeCarros.toStdString().c_str());
        if(!arquivoCarros.is_open()){
            throw QString("Arquivo de Carros nao foi aberto metodo excluir");
        }

        std::string linha;
        bool cheq=false;
        getline(arquivoCarros,linha);
        while(!arquivoCarros.eof()){
            TP2::Carro Carro;
            QString str = QString::fromStdString(linha);
            Carro.montarObjeto(str);
            if(Carro.getPlaca()!= placa)
                fila.push(Carro);
            else{
                cheq=true;
            }

            getline(arquivoCarros,linha);
        }
        arquivoCarros.close();
        if(!cheq)
            throw QString("Erro, Carro não encontrado");

        std::ofstream arquivoCarros2;
        arquivoCarros2.open(nomeDoArquivoDeCarros.toStdString().c_str());
        if(!arquivoCarros2.is_open()){
            throw QString("Arquivo de Carros nao foi aberto metodo excluir");
        }

        while(!fila.empty()){
            TP2::Carro Carro = fila.front();
            arquivoCarros2<<Carro.desmontarObjeto().toStdString();
            fila.pop();

        }

        arquivoCarros2.close();

    } catch (QString &erro) {
        throw(erro);
    }

}

std::list<Carro> *CarroPersistencia::listar() const
{
    try {

        std::ifstream arquivoCarros;
        arquivoCarros.open(nomeDoArquivoDeCarros.toStdString().c_str());
        if(!arquivoCarros.is_open()){
            throw QString("Arquivo de Carros nao foi aberto metodo Listar");
        }
        TP2::CategoriaPersistencia objDaoCat(nomedoArquivoDeCategorias);
        TP2::MarcaPersistencia objDaoMarca(nomeDoArquivoDeMarcas, nomeDoArquivoDeModelos);
        TP2::ModeloPersistencia objDaoModelo(nomeDoArquivoDeModelos);

        std::list<TP2::Modelo> * listaModelo = new std::list<Modelo>;
        listaModelo = objDaoModelo.listar();
        std::list<TP2::Carro> * lista = new std::list<Carro>();
        std::list<TP2::Marca> * listaMarca = new std::list<TP2::Marca>;
        listaMarca = objDaoMarca.listar();
        std::list<TP2::Categoria> * listaCategria = new std::list<TP2::Categoria>;
        listaCategria = objDaoCat.listar();
        std::list<TP2::Marca> * listaMarcaAux = new std::list<Marca>;
        std::list<TP2::Categoria> * listaCategriaAux = new std::list<TP2::Categoria>;
        std::list<TP2::Modelo> * listaModeloAux = new std::list<Modelo>;

        std::string linha;
        getline(arquivoCarros,linha);
        while(!arquivoCarros.eof()){
            *listaMarcaAux = *listaMarca;
            *listaCategriaAux = *listaCategria;
            *listaModeloAux = *listaModelo;
            TP2::Carro Carro;
            QString str = QString::fromStdString(linha);
            Carro.montarObjeto(str);

            while (!listaCategriaAux->empty()) {
                TP2::Categoria obj = listaCategriaAux->back();
                if (Carro.getIdCategoria() == obj.getIdCategoria()){
                    Carro.setCategoria(obj);
                }
                listaCategriaAux->pop_back();
            }

            while(!listaMarcaAux->empty()){
                TP2::Marca obj = listaMarcaAux->back();
                if (Carro.getIdMarca() == obj.getIdMarca()){
                    Carro.setMarca(obj);
                }
                listaMarcaAux->pop_back();
            }

            while (!listaModeloAux->empty()){
                TP2::Modelo obj = listaModeloAux->back();
                if(Carro.getIdModelo() == obj.getId()){
                    Carro.setModelo(obj);
                }
                listaModeloAux->pop_back();
            }
            lista->push_back(Carro);

//            listaMarcaAux = new std::list<Marca>;
//            listaCategriaAux = new std::list<TP2::Categoria>;
//            listaModeloAux = new std::list<Modelo>;
            getline(arquivoCarros,linha);
        }
        arquivoCarros.close();

        return lista;
    } catch (QString &erro) {
        throw(erro);
    }
}

void CarroPersistencia::alterar(Carro &placa)
{
    try {

        std::queue<TP2::Carro> fila;

        std::ifstream arquivoCarros;
        arquivoCarros.open(nomeDoArquivoDeCarros.toStdString().c_str());
        if(!arquivoCarros.is_open()){
            throw QString("Arquivo de Carros nao foi aberto metodo excluir");
        }

        std::string linha;
        getline(arquivoCarros,linha);
        while(!arquivoCarros.eof()){
            TP2::Carro Carro;
            QString str = QString::fromStdString(linha);
            Carro.montarObjeto(str);
            if(Carro.getPlaca()!= placa.getPlaca())
                fila.push(Carro);
            else{
                fila.push(placa);
            }

            getline(arquivoCarros,linha);
        }

        std::ofstream arquivoCarros2;
        arquivoCarros2.open(nomeDoArquivoDeCarros.toStdString().c_str());
        if(!arquivoCarros2.is_open()){
            throw QString("Arquivo de Carros nao foi aberto metodo excluir");
        }

        while(!fila.empty()){
            TP2::Carro Carro = fila.front();
            arquivoCarros2<<Carro.desmontarObjeto().toStdString();
            fila.pop();
        }

        arquivoCarros2.close();

    } catch (QString &erro) {
        throw(erro);
    }
}

Carro CarroPersistencia::pesquisar(QString &key)
{
    try {

//        std::list<TP2::Carro> * lista = new std::list<TP2::Carro>;
//        lista = listar();


//        while(!lista->empty()){
//            TP2::Carro obj = lista->back();
//            lista->pop_back();
//            if(obj.getPlaca() == key){
//                return obj;
//            }
//        }
        std::ifstream arquivo;
        arquivo.open(nomeDoArquivoDeCarros.toStdString().c_str());
        if(!arquivo.is_open()){
            arquivo.close();
            throw QString("Não existem Carros cadastrados");
        }
        std::string linha;
        getline(arquivo, linha);
        while (!arquivo.eof()){
            TP2::Carro obj;
            QString str = QString::fromStdString(linha);
            obj.montarObjeto(str);
            if(obj.getPlaca() == key){
                return obj;
            }
            getline(arquivo, linha);
        }
        throw QString("Carro locado não encontrado");
    } catch (QString &erro) {
        throw erro;
    }
}


}
