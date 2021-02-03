#include "OcorrenciaPersistencia.h"
namespace TP2 {
OcorrenciaPersistencia::OcorrenciaPersistencia():
    arquivoOcorrencia("")
{

}

OcorrenciaPersistencia::OcorrenciaPersistencia(QString arquivoOcorrencia):
    arquivoOcorrencia(arquivoOcorrencia)
{

}

void OcorrenciaPersistencia::incluir(Ocorrencia & obj) const
{
    try{
        std::ofstream arquivo;
        arquivo.open(arquivoOcorrencia.toStdString().c_str(), std::ios::out|std::ios::app);

        if (!arquivo.is_open()){
            arquivo.close();
            throw QString ("Erro, arquivo de ocorrencias nÃ£o encontrado");
        }
        arquivo<<obj.desmontarObjeto().toStdString().c_str();
        arquivo.close();
    } catch (QString &erro) {
        throw(erro);
    }
}

bool operator <(Ocorrencia &obj1, Ocorrencia &obj2){
    if (obj1.getIdLocacao() < obj2.getIdLocacao())
        return true;
    return false;
}

std::list<Ocorrencia> *OcorrenciaPersistencia::listar() const
{
    try{
        std::ifstream arquivo;
        arquivo.open(arquivoOcorrencia.toStdString().c_str());
        if (!arquivo.is_open()){
            arquivo.close();
            throw QString ("Erro, arquivo de ocorrencia nÃ£o encontrado");
        }
        std::list<TP2::Ocorrencia> * lista = new std::list<TP2::Ocorrencia>;
        std::string linhaOcorrencia;
        getline(arquivo,linhaOcorrencia);
        while(!arquivo.eof()){
            QString montarOcorrencia = QString::fromStdString(linhaOcorrencia);
            TP2::Ocorrencia obj;
            obj.montarObjeto(montarOcorrencia);
            lista->push_back(obj);
            lista->sort();
            getline(arquivo, linhaOcorrencia);
        }
        arquivo.close();
        return lista;
    } catch (QString &erro) {
        throw(erro);
    }
}

void OcorrenciaPersistencia::excluir(QString & id) const
{
    try{
        std::ifstream arquivo;
        arquivo.open(arquivoOcorrencia.toStdString().c_str());
        if (!arquivo.is_open()){
            arquivo.close();
            throw QString ("Erro, arquivo de ocorrÃªncias bÃ£o encontrado");
        }
        std::queue<Ocorrencia> fila;
        std::string linhaOcorrencia;
        bool ok = false;
        getline(arquivo,linhaOcorrencia);
        while(!arquivo.eof()){
            TP2::Ocorrencia obj;
            QString montarOcorrencia = QString::fromStdString(linhaOcorrencia);
            obj.montarObjeto(montarOcorrencia);
            if (obj.getIdLocacao() != id.toInt()){
                fila.push(obj);
            }
            else {
                ok = true;
            }
            getline(arquivo,linhaOcorrencia);
        }
        if (!ok){
            throw QString ("Erro, ocorrencia nÃ£o encontrada");
        }

        std::ofstream arquivoS;
        arquivoS.open(arquivoOcorrencia.toStdString().c_str());
        if (!arquivoS.is_open()){
            arquivoS.close();
            throw QString ("Erro, arquivo de ocorrencias nÃ£o encontrada");
        }

        while (!fila.empty()){
            QString saida;
            TP2::Ocorrencia obj = fila.front();
            saida = obj.desmontarObjeto();
            arquivoS<<saida.toStdString().c_str();
            fila.pop();
        }

        arquivoS.close();
    } catch (QString &erro) {
        throw(erro);
    }
}

void OcorrenciaPersistencia::alterar(Ocorrencia &)
{
    try {

    } catch (...) {
    }
}
}
