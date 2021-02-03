#include "VendaPersistencia.h"

namespace TP2 {
VendaPersistencia::VendaPersistencia(QString arquivoVenda):
    arquivoVenda(arquivoVenda)
{

}

VendaPersistencia::VendaPersistencia():
    arquivoVenda("")
{

}

void VendaPersistencia::incluir(Venda & obj) const
{
    try {
       std::ofstream arquivo;
       arquivo.open(arquivoVenda.toStdString().c_str(), std::ios::out|std::ios::app);

       if(!arquivo.is_open()){
           arquivo.close();
           throw QString ("Erro, arquivo de venda nÃ£o encontrado");
       }

       arquivo<<obj.desmontarObjeto().toStdString().c_str();
       arquivo.close();
    } catch (QString &erro) {
        throw erro;
    }
}

std::list<Venda> *VendaPersistencia::listar() const
{
    try {
        std::ifstream arquivo;
        arquivo.open(arquivoVenda.toStdString().c_str());
        if (!arquivo.is_open()){
            arquivo.close();
            throw ("Erro, arquivo de vendas nÃ£o encontrado");
        }

        std::list<TP2::Venda> * lista = new std::list<TP2::Venda>;

        std::string linhaVenda;

        getline(arquivo,linhaVenda);

        while(!arquivo.eof()){
            QString montarVenda = QString::fromStdString(linhaVenda);
            TP2::Venda obj;
            obj.montarObjeto(montarVenda);
            lista->push_back(obj);
            getline(arquivo,linhaVenda);
        }
        arquivo.close();
        return lista;


    } catch (QString &erro) {
        throw erro;
    }
}

void VendaPersistencia::excluir(QString & str) const
{
    try {
        std::ifstream arquivoLeitura;
        arquivoLeitura.open(arquivoVenda.toStdString().c_str());
        if(!arquivoLeitura.is_open()){
            arquivoLeitura.close();
            throw QString ("Erro, arquivo de vendas nÃ£o encontrado, impossivel excluir venda");
        }

        std::string linhaVenda;
        std::queue<TP2::Venda> fila;
        bool ok = false;

        getline(arquivoLeitura,linhaVenda);
        while(!arquivoLeitura.eof()){
            QString montarVenda = QString::fromStdString(linhaVenda);
            TP2::Venda obj;
            obj.montarObjeto(montarVenda);
            if (obj.getPlaca()!=str){
                fila.push(obj);
            }
            else{
                ok = true;
            }
            getline(arquivoLeitura,linhaVenda);
        }
        arquivoLeitura.close();
        if(!ok){
            while (!fila.empty()){
                fila.pop();
            }
            throw QString ("Erro, venda informada nÃ£o encontrada");
        }

        std::ofstream arquivoSaida;
        arquivoSaida.open(arquivoVenda.toStdString().c_str());
        if (!arquivoSaida.is_open()){
            arquivoSaida.close();
            throw QString("Erro, arquivo de vendas nÃ£o encontrado");
        }

        while(!fila.empty()){
            TP2::Venda obj = fila.front();
            QString saida = obj.desmontarObjeto();
            arquivoSaida<<saida.toStdString().c_str();
            fila.pop();
        }
        arquivoSaida.close();
    } catch (QString &erro) {
        throw erro;
    }
}

void VendaPersistencia::alterar(Venda &)
{

}
}
