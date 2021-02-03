#include "MarcaPersistencia.h"

namespace TP2 {

MarcaPersistencia::MarcaPersistencia() :
    arquivoMarca(""),
    arquivoModelo("")
{

}

MarcaPersistencia::MarcaPersistencia(QString arquivoMarca, QString arquivoModelo):
    arquivoMarca(arquivoMarca),
    arquivoModelo(arquivoModelo)
{

}

void MarcaPersistencia::incluir(TP2::Marca & marca) const{
    std::ofstream arquivoMarcas;
    arquivoMarcas.open(arquivoMarca.toStdString().c_str(),
                       std::ios::out|std::ios::app);
    if(!arquivoMarcas.is_open()){
        throw QString("Arquivo de Marcas nao foi aberto - Metodo incluir");
    }
    arquivoMarcas<<marca.desmontarObjeto().toStdString();
    arquivoMarcas.close();
}


void MarcaPersistencia::excluir(QString & nome) const{
    try {
        std::queue<TP2::Marca> fila;

        std::ifstream arquivoMarcas;
        arquivoMarcas.open(arquivoMarca.toStdString().c_str());
        if(!arquivoMarcas.is_open()){
            throw QString("Arquivo de Marcas nao foi aberto metodo excluir");
        }

        std::string linha;
        bool cheq=false;
        int id;
        getline(arquivoMarcas,linha);
        while(!arquivoMarcas.eof()){
            TP2::Marca Marca;
            QString str = QString::fromStdString(linha);
            Marca.montarObjeto(str);

            if(Marca.getDescricaoMarca()!=nome)
                fila.push(Marca);
            else{
                id = Marca.getIdMarca();
                cheq=true;
            }

            getline(arquivoMarcas,linha);
        }
        arquivoMarcas.close();
        if(!cheq){
            throw QString("ERRO: Marca nÃ£o encontrada");
        }

        std::ofstream arquivoMarcas2;
        arquivoMarcas2.open(arquivoMarca.toStdString().c_str());
        if(!arquivoMarcas2.is_open()){
            arquivoMarcas2.close();
            throw QString("Arquivo de Marca nao foi aberto metodo excluir");
        }

        while(!fila.empty()){
            TP2::Marca marca = fila.front();
            arquivoMarcas2<<marca.desmontarObjeto().toStdString();
            fila.pop();
        }

        arquivoMarcas2.close();


        std::ifstream arquivoModelos;

        arquivoModelos.open(arquivoModelo.toStdString().c_str());
        if(arquivoModelos.is_open()){
            std::queue<TP2::Modelo> filaModelo;
            std::string linhaModelo;
            getline(arquivoModelos,linhaModelo);
            while (!arquivoModelos.eof()){
                TP2::Modelo modelo;
                QString montarModelo = QString::fromStdString(linhaModelo);
                modelo.montarObjeto(montarModelo);
                if(modelo.getIdMarca() != id){
                    filaModelo.push(modelo);
                }
                getline(arquivoModelos,linhaModelo);
            }

            std::ofstream arquivoModelos2;
            arquivoModelos2.open(arquivoModelo.toStdString().c_str());
            while(!filaModelo.empty()){
                TP2::Modelo modelo = filaModelo.front();
                filaModelo.pop();
                arquivoModelos2<<modelo.desmontarObjeto().toStdString();
            }
            arquivoMarcas2.close();
        }
        arquivoModelos.close();
        arquivoMarcas2.close();
    } catch (QString &erro) {
        throw(erro);
    }
}

// Metodo para comparaÃ§Ã£o dos objetos Cateogoria a ser
// utilizado pelo metodo sort da list para ordenar
bool operator < (TP2::Marca & p1, TP2::Marca & p2)
{
    if (p1.getDescricaoMarca()<p2.getDescricaoMarca())
        return true;
    else return false;
}



std::list<Marca> * MarcaPersistencia::listar() const{
    try {
        std::ifstream arquivoMarcas;
        arquivoMarcas.open(arquivoMarca.toStdString().c_str());
        if(!arquivoMarcas.is_open()){
            throw QString("Arquivo de Marca nao foi aberto metodo Listar");
        }
        std::vector<TP2::Modelo> * modelos = new std::vector<Modelo>;
        std::list<TP2::Modelo> * modelosAux = new std::list<Modelo>;
        std::ifstream arquivoModelos;
        arquivoModelos.open(arquivoModelo.toStdString().c_str());
        if (arquivoModelos.is_open()){
            std::string linhaModelo;
            getline(arquivoModelos,linhaModelo);
            while(!arquivoModelos.eof()){
                TP2::Modelo objModelo;
                QString montarModelo = QString::fromStdString(linhaModelo);
                objModelo.montarObjeto(montarModelo);
                modelos->push_back(objModelo);
                getline(arquivoModelos,linhaModelo);
            }
        }
        arquivoModelos.close();
        std::list<TP2::Marca> *lista = new std::list<Marca>();
        std::string linha;
        getline(arquivoMarcas,linha);
        while(!arquivoMarcas.eof()){
            TP2::Marca marca;
            QString str = QString::fromStdString(linha);
            marca.montarObjeto(str);

            for (int i = 0; i < (int) modelos->size(); i++){
                TP2::Modelo modelo = modelos->operator [](i);
                if(modelo.getIdMarca() == marca.getIdMarca()){
                    modelosAux->push_back(modelo);
                    modelos->erase(modelos->begin()+i);
                    i--;
                }
            }

            marca.setModelos(modelosAux);
            lista->push_back(marca);
            lista->sort();

            modelosAux = new std::list<Modelo>();

            getline(arquivoMarcas,linha);
        }
        arquivoMarcas.close();
        return lista;
    } catch (QString &erro) {
        throw(erro);
    }
}

void MarcaPersistencia::alterar(Marca &str)
{
    try {
//        bool ok = false;
//        std::queue<TP2::Marca> * fila = new std::queue<TP2::Marca>();
//        std::ifstream arquivo;
//        std::ofstream arquivoS;
//        std::string linha;
//        QStringList strList = str.split(";");
//        if (strList.length()!=1){
//            throw QString ("Erro, faltam informaÃ§Ãµes, impossivel alterar");
//        }

//        arquivo.open(arquivoMarca.toStdString().c_str());
//        if (!arquivo.is_open()){
//            arquivo.close();
//            throw QString ("Erro, arquivo de Marcas nÃ£o encontrado");
//        }

//        getline (arquivo, linha);
//        while (!arquivo.eof()){
//            TP2::Marca marca;
//            QString montarMarca = QString::fromStdString(linha);
//            marca.montarObjeto(montarMarca);
//            if (marca.getDescricaoMarca() == strList[0]){
//                ok = true;
//                str = QString::number(marca.getIdMarca()) + ";" + str;
//                marca.montarObjeto(str);
//                fila->push(marca);
//            }
//            else{
//                fila->push(marca);
//            }
//            getline(arquivo,linha);
//        }
//        arquivo.close();
//        if (ok == false){
//            while (!fila->empty()){
//                fila->pop();
//            }
//            throw QString ("Erro, marca nÃ£o encontrada");
//        }

//        arquivoS.open(arquivoMarca.toStdString().c_str());
//        if (!arquivoS.is_open()){
//            arquivoS.close();
//            throw QString ("Erro, arquivo de modelos nÃ£o encontrado");
//        }

//        while (!fila->empty()){
//            TP2::Marca obj;
//            obj = fila->front();
//            QString saida = obj.desmontarObjeto();
//            arquivoS<<saida.toStdString().c_str();
//            fila->pop();
//        }

        //arquivoS.close();
    } catch (QString &erro) {
        throw erro;
    }
}


}
