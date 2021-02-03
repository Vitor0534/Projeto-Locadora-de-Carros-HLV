#include "ModeloPersistencia.h"
namespace TP2 {
ModeloPersistencia::ModeloPersistencia():
    arquivoModelo("")
{

}

ModeloPersistencia::ModeloPersistencia(QString arquivoModelo):
    arquivoModelo(arquivoModelo)
{

}

void ModeloPersistencia::incluir(Modelo & obj) const
{
    try {
       std::ofstream arquivo;
       QString saida("");

       arquivo.open(arquivoModelo.toStdString().c_str(), std::ios::out|std::ios::app);
       if (!arquivo.is_open()){
           arquivo.close();
           throw QString ("Erro, arquivo de modelo não encontrado");
       }

       saida = obj.desmontarObjeto();
       arquivo<<saida.toStdString().c_str();
       arquivo.close();

    } catch (QString &erro) {
        throw erro;
    }
}

bool operator <(Modelo &obj1, Modelo &obj2){
    if (obj1.getDescricao() < obj2.getDescricao())
            return true;
    return false;
}

std::list<Modelo> *ModeloPersistencia::listar() const
{
    try {
        std::ifstream arquivo;
        std::list<TP2::Modelo> * lista = new std::list<TP2::Modelo>();
        std::string linha;

        arquivo.open(arquivoModelo.toStdString().c_str());
        if (!arquivo.is_open()){
            arquivo.close();
            throw QString ("Erro, arquivo de modelos não encontrado");
        }

        getline (arquivo, linha);
        while (!arquivo.eof()){
            TP2::Modelo obj;
            QString montarModelo = QString::fromStdString(linha);
            obj.montarObjeto(montarModelo);
            lista->push_back(obj);
            lista->sort();
            getline (arquivo, linha);
        }
        arquivo.close();
        return lista;

    } catch (QString &erro) {
        throw erro;
    }
    catch (std::bad_alloc &){
        throw QString ("Erro, falta de memoria");
    }
}

void ModeloPersistencia::alterar(Modelo &str)
{
    try {
//        bool ok = false;
//        std::queue<TP2::Modelo> * fila = new std::queue<TP2::Modelo>();
//        std::ifstream arquivo;
//        std::ofstream arquivoS;
//        std::string linha;

//        arquivo.open(arquivoModelo.toStdString().c_str());
//        if (!arquivo.is_open()){
//            arquivo.close();
//            throw QString ("Erro, arquivo de modelos não encontrado");
//        }

//        getline(arquivo, linha);
//        while (!arquivo.eof()){
//            TP2::Modelo modelo;
//            QString montarModelo = QString::fromStdString(linha);
//            modelo.montarObjeto(montarModelo);
//            if (modelo.getId == str.getId()){
//                ok = true;
//                modelo = str;
//                fila->push(modelo);
//            }
//            else{
//                fila->push(modelo);
//            }
//            getline(arquivo, linha);
//        }
//        arquivo.close();
//        if (ok == false){
//            while (!fila->empty()){
//                fila->pop();
//            }
//            throw QString ("Erro, modelo não encontrado");
//        }
//        arquivoS.open(arquivoModelo.toStdString().c_str());
//        if (!arquivoS.is_open()){
//            arquivoS.close();
//            throw QString ("Erro, arquivo de modelos não encontrado");
//        }

//        while (!fila->empty()){
//            TP2::Modelo obj;
//            obj = fila->front();
//            QString saida = obj.desmontarObjeto();
//            arquivoS<<saida.toStdString().c_str();
//            fila->pop();
//        }

//        arquivoS.close();
    } catch (QString &erro) {
        throw erro;
    }
    catch (std::bad_alloc &){
        throw QString ("Erro, falta de memoria");
    }
}

void ModeloPersistencia::excluir(QString & str) const
{
    try {
        std::queue<TP2::Modelo> * fila = new std::queue<TP2::Modelo>();
        std::ifstream arquivo;
        std::ofstream arquivoS;
        std::string linha;

        arquivo.open(arquivoModelo.toStdString().c_str());
        if(!arquivo.is_open()){
            arquivo.close();
            throw QString ("Erro, arquivo de modelo não encontrado");
        }

        getline(arquivo, linha);
        while (!arquivo.eof()){
            QString montarModelo = QString::fromStdString(linha);
            TP2::Modelo modelo;
            modelo.montarObjeto(montarModelo);
            if (modelo.getDescricao() != str){
                fila->push(modelo);
            }
            getline(arquivo,linha);
        }
        arquivo.close();

        arquivoS.open(arquivoModelo.toStdString().c_str());

        if (!arquivoS.is_open()){
            arquivoS.close();
            throw QString ("Erro, arquivo de modelos não encontrado");
        }
        while(!fila->empty()){
            TP2::Modelo modelo;
            modelo = fila->front();
            fila->pop();
            QString saida = modelo.desmontarObjeto();
            arquivoS<<saida.toStdString().c_str();
        }
        arquivoS.close();
    } catch (QString &erro) {
        throw erro;
    }
    catch (std::bad_alloc &){
        throw QString ("Erro, falta de memoria");
    }
}

}
