#include "CondutorPersistencia.h"

namespace TP2 {

CondutorPersistencia::CondutorPersistencia():
    arquivoCNH(""),
    arquivoCondutor(""),
    arquivoPessoa("")
{
}

CondutorPersistencia::CondutorPersistencia(QString arquivoCondutor):
    arquivoCondutor(arquivoCondutor)
{

}

CondutorPersistencia::CondutorPersistencia(QString arquivoCondutor, QString arquivoCNH, QString arquivoPessoa):
    arquivoCNH(arquivoCNH),
    arquivoCondutor(arquivoCondutor),
    arquivoPessoa(arquivoPessoa)
{
}

void CondutorPersistencia::incluir(Condutor &condutor) const
{
    try {
        std::ofstream arquivo;
        arquivo.open(arquivoCondutor.toStdString().c_str(),
                     std::ios::out|std::ios::app);
        if(!arquivo.is_open()){
            arquivo.close();
            throw QString("Arquivo de Condutor  nao foi aberto - Metodo incluir");
        }

        std::ofstream arquivoCnh;
        arquivoCnh.open(arquivoCNH.toStdString().c_str(),
                        std::ios::out|std::ios::app);
        if(!arquivoCnh .is_open()){
            arquivo.close();
            arquivoCnh.close();
            throw QString("Arquivo de cnh  nao foi aberto - Metodo incluir");
        }

        arquivo<<condutor.desmontarObjeto().toStdString();
        arquivo.close();

        TP2::Pessoa objPessoa;
        TP2::PessoaPersistencia objPessoaDAO(arquivoPessoa);
        objPessoa = condutor.getPessoa();
        objPessoaDAO.incluir(objPessoa);

        TP2::CNH objCNH = condutor.getCnh();
        arquivoCnh<<objCNH.desmontarObjeto().toStdString();
        arquivoCnh.close();
    } catch (QString &erro) {
        throw erro;
    }
}

void CondutorPersistencia::excluir(QString & CPF) const
{
    try {
        std::stack<TP2::Condutor> pilha;
        std::list<TP2::CNH> lista;

        //***********(abre os arquivos para leitura)*******************************//

        std::ifstream arquivo;
        arquivo.open(arquivoCondutor.toStdString().c_str());
        if(!arquivo.is_open()){
            arquivo.close();
            throw QString("Arquivo de condutores nao foi aberto metodo excluir");
        }



        std::ifstream arquivoCnh ;
        arquivoCnh .open(arquivoCNH.toStdString().c_str());
        if(!arquivoCnh .is_open()){
            arquivo.close();
            arquivoCnh.close();
            throw QString("Arquivo de cnh nao foi aberto metodo excluir");
        }

        std::string linha;
        bool cheq=false;
        getline(arquivo ,linha);
        while(!arquivo.eof()){
            TP2::Condutor condutor;
            QString str = QString::fromStdString(linha);
            condutor.montarObjeto(str);

            if(condutor.getCPF()!=CPF.toLongLong())
                pilha.push(condutor);
            else
                cheq=true;

            getline(arquivo ,linha);
        }
        if(!cheq)
            throw QString("Erro, condutor nao encontrado");

        std::string linha2;
        bool cheq2=false;
        getline(arquivoCnh ,linha2);
        while(!arquivoCnh .eof()){
            TP2::CNH cnh;
            QString str = QString::fromStdString(linha2);
            cnh.montarObjeto(str);

            if(cnh.getCPF()!=CPF.toLongLong())
                lista.push_front(cnh);
            else
                cheq2=true;

            getline(arquivoCnh ,linha2);
        }
        if(!cheq2)
            throw QString("Erro, cliete nao encontrado");

        arquivo.close();
        arquivoCnh.close();

        //*****************(abre arquivos para insercao de forma a excluir oque havia  dentro deles)**********************//

        std::ofstream arquivoCondutor2;
        arquivoCondutor2.open(arquivoCondutor.toStdString().c_str());
        if(!arquivoCondutor2.is_open()){
            arquivoCondutor2.close();
            throw QString("Arquivo de Condutor nao foi aberto metodo excluir");
        }

        std::ofstream arquivoCnh2 ;
        arquivoCnh2.open(arquivoCNH.toStdString().c_str());
        if(!arquivoCnh2.is_open()){
            arquivoCnh2.close();
            arquivoCondutor2.close();
            throw QString("Arquivo de cnh nao foi aberto metodo excluir");
        }

        while(!pilha.empty()){
            TP2::Condutor condutor = pilha.top();
            arquivoCondutor2<<condutor.desmontarObjeto().toStdString();
            pilha.pop();
        }

        while(!lista.empty()){
            TP2::CNH cnh = lista.front();
            arquivoCnh2<<cnh.desmontarObjeto().toStdString();
            lista.pop_front();
        }

        TP2::PessoaPersistencia objDAO(arquivoPessoa);
        objDAO.excluir(CPF);
        arquivoCondutor2.close();
        arquivoCnh2.close();

    } catch (QString &erro) {
        throw(erro);
    }
}

void CondutorPersistencia::alterar(Condutor &)
{
    try {

    } catch (...) {
    }
}

bool CondutorPersistencia::verificar(QString & cpf)
{
    try {
        std::ifstream arquivo;
        arquivo.open(arquivoCondutor.toStdString().c_str());
        if(!arquivo.is_open()){
            arquivo.close();
            throw QString ("Erro, arquivo de condutores não encontrado");
        }
        std::string linha;
        getline(arquivo,linha);
        while(!arquivo.eof()){
            TP2::Condutor obj;
            QString str = QString::fromStdString(linha);
            obj.montarObjeto(str);

            if(obj.getCPF()==cpf.toLongLong())
                return true;

            getline(arquivo,linha);
        }

        arquivo.close();


        return false;

    } catch (QString &erro) {
        throw erro;
    }
}

bool operator <(TP2::Condutor & obj1, TP2::Condutor & obj2){
    if(obj1.getPessoa().getNome()<obj2.getPessoa().getNome())
        return true;
    return false;
}

std::list<Condutor> *CondutorPersistencia::listar() const
{
    try {
        std::ifstream arquivo;
        arquivo.open(arquivoCondutor.toStdString().c_str());
        if(!arquivo.is_open()){
            arquivo.close();
            throw QString("Arquivo de condutor nao foi aberto metodo Listar");
        }

        std::ifstream arquivoCnh;
        arquivoCnh.open(arquivoCNH.toStdString().c_str());
        if(!arquivoCnh.is_open()){
            arquivo.close();
            arquivoCnh.close();
            throw QString("Arquivo de cnh nao foi aberto metodo Listar");
        }

        std::ifstream arquivoPessoas;
        arquivoPessoas.open(arquivoPessoa.toStdString().c_str());
        if (!arquivoPessoas.is_open()){
            arquivo.close();
            arquivoCnh.close();
            arquivoPessoas.close();
            throw QString ("Arquivo de Pessoas nÃ£o foi encontrado");
        }
        std::string cnh;
        getline(arquivoCnh,cnh);
        for(;!arquivoCnh.eof();){
            std::string pou;
            getline(arquivoCnh,pou);
            if(pou!="")
                cnh+=";"+pou;
        }
        arquivoCnh.close();

        std::string linhaPessoa;
        getline(arquivoPessoas,linhaPessoa);

        while (!arquivoPessoas.eof()){
            std::string linhaPessoaAux;
            getline(arquivoPessoas,linhaPessoaAux);
            if(linhaPessoaAux!="")
                linhaPessoa += ";" + linhaPessoaAux;
        }


        std::list<TP2::Condutor> *lista = new std::list<TP2::Condutor>();
        std::string linha;
        getline(arquivo,linha);
        while(!arquivo.eof()){
            TP2::Condutor condutor;
            QString str = QString::fromStdString(linha);
            condutor.montarObjeto(str);

            QStringList list = QString::fromStdString(cnh).split(';');
            for(int i=0;i<list.size();i+=5){
                if(condutor.getCPF()==list[i].toLongLong()){
                    TP2::CNH cnh;
                    cnh.setCPF(list[i].toLong());
                    cnh.setNumeroCnh(list[i+1].toLong());
                    cnh.setDataDaPrimeiraCnh(list[i+2].toLong());
                    cnh.setDataDeVencimento(list[i+3].toLong());
                    cnh.setEnumCnh(list[i+4].toLong());
                    condutor.setCnh(cnh);
                    i=list.size()+1;
                }
            }

            QStringList listPessoas = QString::fromStdString(linhaPessoa).split(";");
            for (int i = 0; i < listPessoas.size(); i+= 3){
                if (condutor.getCPF() == listPessoas[i].toLongLong()){
                    TP2::Pessoa pessoa;
                    pessoa.setCPF(listPessoas[i].toLongLong());
                    pessoa.setNome(listPessoas[i+1]);
                    pessoa.setDataDeNascimento(listPessoas[i+2].toLongLong());
                    condutor.setPessoa(pessoa);
                    i = listPessoas.size()+1;
                }
            }

            lista->push_back(condutor);
            lista->sort();
            getline(arquivo ,linha);
        }
        arquivo.close();
        return lista;
    } catch (QString &erro) {
        throw(erro);
    }
}


}//fim de tudo
