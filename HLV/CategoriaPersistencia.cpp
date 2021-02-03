#include "CategoriaPersistencia.h"

namespace TP2 {

CategoriaPersistencia::CategoriaPersistencia():
    nomeDoArquivoNoDisco("")
{

}

CategoriaPersistencia::CategoriaPersistencia(QString nomeDoArquivoNoDisco):
    nomeDoArquivoNoDisco(nomeDoArquivoNoDisco)
{

}

void CategoriaPersistencia::incluir(Categoria &categoria) const{
    std::ofstream arquivoCategoria;
    arquivoCategoria.open(nomeDoArquivoNoDisco.toStdString().c_str(),
                                   std::ios::out|std::ios::app);
    if(!arquivoCategoria.is_open()){
        throw QString("Arquivo de Categorias nao foi aberto - Metodo incluir");
    }

    arquivoCategoria<<categoria.desmontarObjeto().toStdString();
    arquivoCategoria.close();
}


void CategoriaPersistencia::excluir(QString &nome) const{
    try {

        std::stack<TP2::Categoria> pilha;

        std::ifstream arquivoCategoria;
        arquivoCategoria.open(nomeDoArquivoNoDisco.toStdString().c_str());
        if(!arquivoCategoria.is_open()){
            throw QString("Arquivo de Categoria nao foi aberto metodo excluir");
        }

        std::string linha;
        getline(arquivoCategoria,linha);
        while(!arquivoCategoria.eof()){
            TP2::Categoria categoria;
            QString str = QString::fromStdString(linha);
            categoria.montarObjeto(str);
            if(categoria.getDescricaoCat()!=nome){
                pilha.push(categoria);
            }
            getline(arquivoCategoria,linha);
        }
        arquivoCategoria.close();


        std::ofstream arquivoCategoria2;
        arquivoCategoria2.open(nomeDoArquivoNoDisco.toStdString().c_str());
        if(!arquivoCategoria2.is_open()){
            throw QString("Arquivo de Categoria nao foi aberto metodo excluir");
        }

        std::list<Categoria> list;
        int tam=pilha.size();
        for(int i=0;i<tam;i++){
            Categoria aux;
            aux=pilha.top();
            list.push_back(aux);
            pilha.pop();
        }

        while(!list.empty()){
            TP2::Categoria categoria = list.back();

            arquivoCategoria2<<categoria.desmontarObjeto().toStdString();
            list.pop_back();
        }

        arquivoCategoria2.close();
    } catch (QString &erro) {
        throw(erro);
    }
}

bool operator < (TP2::Categoria &p1, TP2::Categoria &p2)
{
    if (p1.getIdCategoria()<p2.getIdCategoria())
        return true;
    else return false;
}



std::list<TP2::Categoria>* CategoriaPersistencia::listar() const{
    try {

        std::ifstream arquivoCategoria;
        arquivoCategoria.open(nomeDoArquivoNoDisco.toStdString().c_str());
        if(!arquivoCategoria.is_open()){
            throw QString("Arquivo de Categoria nao foi aberto metodo Listar");
        }
        std::list<TP2::Categoria> *lista = new std::list<TP2::Categoria>();
        std::string linha;
        getline(arquivoCategoria,linha);
        while(!arquivoCategoria.eof()){
            TP2::Categoria categoria;
            QString str = QString::fromStdString(linha);
            categoria.montarObjeto(str);
            lista->push_back(categoria);
            getline(arquivoCategoria,linha);
        }
        arquivoCategoria.close();
        return lista;
    } catch (QString &erro) {
        throw(erro);
    }
}

void CategoriaPersistencia::alterar(Categoria &)
{

}


}
