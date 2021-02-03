#include "ClientePersistencia.h"
#include <iostream>
using namespace std;
namespace TP2 {


ClientePersistencia::ClientePersistencia():
    arquivoCliente(""),
    arquivoPessoa(""),
    arquivoEmail(""),
    arquivoEndereco(""),
    arquivoTelefone("")
{
}

ClientePersistencia::ClientePersistencia(QString arquivoCliente):
    arquivoCliente(arquivoCliente)
{

}

ClientePersistencia::ClientePersistencia(QString arquivoCliente, QString arquivoPessoa,
                                         QString arquivoTelefone,
                                         QString arquivoEndereco, QString arquivoEmail):
    arquivoCliente(arquivoCliente),
    arquivoPessoa(arquivoPessoa),
    arquivoEmail(arquivoEmail),
    arquivoEndereco(arquivoEndereco),
    arquivoTelefone(arquivoTelefone)
{
}


void ClientePersistencia::incluir(Cliente &cliente) const
{
    try {
        std::ofstream arquivoClientes;
        arquivoClientes.open(arquivoCliente.toStdString().c_str(),
                             std::ios::out|std::ios::app);
        if(!arquivoClientes.is_open()){
            throw QString("Arquivo de clientes nao foi aberto - Metodo incluir");
        }

        arquivoClientes<<cliente.desmontarObjeto().toStdString();
        arquivoClientes.close();

        std::ofstream arquivoEmails(arquivoEmail.toStdString().c_str(),
                                    std::ios::out|std::ios::app );
        if(!arquivoEmails.is_open()){
            arquivoEmails.close();
            throw QString ("Erro, arquivo de E-mails não encontrado");
        }

        std::vector<TP2::Email> const * const vectorEmail = cliente.getEmail();

        TP2::Email email;

        for (int i = 0; i < (int)vectorEmail->size(); i++){
            email = vectorEmail->at(i);
            arquivoEmails<<email.desmontarObjeto().toStdString().c_str();
        }
        delete vectorEmail;
        arquivoEmails.close();

        std::ofstream arquivoEnderecos(arquivoEndereco.toStdString().c_str(),
                                       std::ios::out|std::ios::app );
        if(!arquivoEnderecos.is_open()){
            arquivoEmails.close();
            throw QString ("Erro, arquivo de Endereços não encontrado");
        }

        std::vector<TP2::Endereco> const * const vectorEnd = cliente.getEndereco();

        TP2::Endereco end;

        for (int i = 0; i < (int)vectorEnd->size(); i++){
            end = vectorEnd->at(i);
            arquivoEnderecos<<end.desmontarObjeto().toStdString().c_str();
        }
        delete vectorEnd;
        arquivoEnderecos.close();

        std::ofstream arquivoTelefones(arquivoTelefone.toStdString().c_str(),
                                       std::ios::out|std::ios::app );
        if(!arquivoTelefones.is_open()){
            arquivoEmails.close();
            throw QString ("Erro, arquivo de Telefones não encontrado");
        }

        std::vector<TP2::Telefone> const * const vectorTel = cliente.getTelefone();

        TP2::Telefone tel;

        for (int i = 0; i < (int)vectorTel->size(); i++){
            tel = vectorTel->at(i);
            arquivoTelefones<<tel.desmontarObjeto().toStdString().c_str();
        }
        delete vectorTel;
        arquivoTelefones.close();

        TP2::PessoaPersistencia objPessoaDAO(arquivoPessoa);
        TP2::Pessoa pessoa = cliente.getPessoa();
        objPessoaDAO.incluir(pessoa);
    } catch (QString &erro) {
        throw erro;
    }
}

void ClientePersistencia::excluir(QString & CPF) const
{
    try {

        std::stack<TP2::Cliente> pilha;

        std::ifstream arquivoClientes;
        arquivoClientes.open(arquivoCliente.toStdString().c_str());
        if(!arquivoClientes.is_open()){
            throw QString("Arquivo de Categoria nao foi aberto metodo excluir");
        }

        std::string linha;
        bool cheq=false;
        getline(arquivoClientes,linha);
        while(!arquivoClientes.eof()){
            TP2::Cliente cliente;
            QString str = QString::fromStdString(linha);
            cliente.montarObjeto(str);

            if(cliente.getCPF()!= CPF.toLongLong())
                pilha.push(cliente);
            else{
                cheq=true;
            }

            getline(arquivoClientes,linha);
        }
        arquivoClientes.close();
        if(!cheq)
            throw QString("Erro, cliente não encontrado");

        TP2::PessoaPersistencia objDAO(arquivoPessoa);
        objDAO.excluir(CPF);

        std::ofstream arquivoClientes2;
        arquivoClientes2.open(arquivoCliente.toStdString().c_str());
        if(!arquivoClientes2.is_open()){
            throw QString("Arquivo de Categoria nao foi aberto metodo excluir");
        }

        std::list<Cliente> list;
        int tam=pilha.size();

        for(int i=0;i<tam;i++){
            Cliente aux;
            aux=pilha.top();
            list.push_back(aux);
            pilha.pop();
        }

        while(!list.empty()){
            TP2::Cliente cliente = list.back();
            arquivoClientes2<<cliente.desmontarObjeto().toStdString();
            list.pop_back();
        }
        arquivoClientes2.close();

        std::queue<TP2::Endereco> filaEnd;
        std::ifstream arquivoEnd;
        arquivoEnd.open(arquivoEndereco.toStdString().c_str());
        if (!arquivoEnd.is_open()){
            throw QString ("Erro, arquivo de endereços não encontrado");
        }

        std::string linhaEnd;
        getline(arquivoEnd, linhaEnd);
        while (!arquivoEnd.eof()){
            TP2::Endereco obj;
            QString montarObj = QString::fromStdString(linhaEnd);
            obj.montarObjeto(montarObj);
            if(obj.getCPF() != CPF.toLongLong()){
                filaEnd.push(obj);
            }
            getline(arquivoEnd, linhaEnd);
        }
        arquivoEnd.close();

        std::queue<TP2::Email> filaEmail;
        std::ifstream arquivoEmails;
        arquivoEmails.open(arquivoEmail.toStdString().c_str());
        if (!arquivoEmails.is_open()){
            throw QString ("Erro, arquivo de E-mails não encontrado");
        }

        std::string linhaEmail;
        getline(arquivoEmails, linhaEmail);
        while (!arquivoEmails.eof()){
            TP2::Email obj;
            QString montarObj = QString::fromStdString(linhaEmail);
            obj.montarObjeto(montarObj);
            if(obj.getCPF() != CPF.toLongLong()){
                filaEmail.push(obj);
            }
            getline(arquivoEmails, linhaEmail);
        }
        arquivoEmails.close();

        std::queue<TP2::Telefone> filaTelefone;
        std::ifstream arquivoTelefones;
        arquivoTelefones.open(arquivoTelefone.toStdString().c_str());
        if (!arquivoTelefones.is_open()){
            throw QString ("Erro, arquivo de endereços não encontrado");
        }

        std::string linhaTelefone;
        getline(arquivoTelefones, linhaTelefone);
        while (!arquivoTelefones.eof()){
            TP2::Telefone obj;
            QString montarObj = QString::fromStdString(linhaTelefone);
            obj.montarObjeto(montarObj);
            if(obj.getCPF() != CPF.toLongLong()){
                filaTelefone.push(obj);
            }
            getline(arquivoTelefones, linhaTelefone);
        }
        arquivoTelefones.close();

        std::ofstream arquivoTelS;
        arquivoTelS.open(arquivoTelefone.toStdString().c_str());
        if(!arquivoTelS.is_open()){
            arquivoTelS.close();
            throw QString ("Erro, arquivo de telefones não encontrado");
        }
        while (!filaTelefone.empty()){
            TP2::Telefone obj = filaTelefone.front();
            arquivoTelS<<obj.desmontarObjeto().toStdString().c_str();
            filaTelefone.pop();
        }

        std::ofstream arquivoEndS;
        arquivoEndS.open(arquivoEndereco.toStdString().c_str());
        if(!arquivoEndS.is_open()){
            arquivoEndS.close();
            throw QString ("Erro, arquivo de telefones não encontrado");
        }
        while (!filaEnd.empty()){
            TP2::Endereco obj = filaEnd.front();
            arquivoEndS<<obj.desmontarObjeto().toStdString().c_str();
            filaEnd.pop();
        }

        std::ofstream arquivoEmailS;
        arquivoEmailS.open(arquivoEmail.toStdString().c_str());
        if(!arquivoEmailS.is_open()){
            arquivoEmailS.close();
            throw QString ("Erro, arquivo de telefones não encontrado");
        }
        while (!filaEmail.empty()){
            TP2::Email obj = filaEmail.front();
            arquivoEmailS<<obj.desmontarObjeto().toStdString().c_str();
            filaEmail.pop();
        }


    } catch (QString &erro) {
        throw(erro);
    }

}

bool ClientePersistencia::verificar(QString &cpf)
{
    try {
        std::ifstream arquivo;
        arquivo.open(arquivoCliente.toStdString().c_str());
        if(!arquivo.is_open()){
            arquivo.close();
            throw QString ("Erro, arquivo de condutores não encontrado");
        }
        std::string linha;
        getline(arquivo,linha);
        while(!arquivo.eof()){
            TP2::Cliente obj;
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

void ClientePersistencia::alterar(Cliente &)
{
    try {

    } catch (...) {
    }
}

bool operator <(TP2::Cliente &obj1, TP2::Cliente &obj2){
    if (obj1.getPessoa().getNome() < obj2.getPessoa().getNome())
        return true;
    return false;
}

std::list<Cliente> *ClientePersistencia::listar() const
{
    try {
        std::ifstream arquivoClientes;
        arquivoClientes.open(arquivoCliente.toStdString().c_str());
        if(!arquivoClientes.is_open()){
            arquivoClientes.close();
            throw QString("Arquivo de Clientes nao foi aberto metodo Listar");
        }
        std::list<TP2::Cliente> *lista = new std::list<Cliente>();

        std::vector<TP2::Pessoa> * pessoa = new std::vector<TP2::Pessoa>;
        std::vector<TP2::Email> * email = new std::vector<TP2::Email>;
        std::vector<TP2::Endereco> * end = new std::vector<TP2::Endereco>;
        std::vector<TP2::Telefone> * tel = new std::vector<TP2::Telefone>;

        std::vector<TP2::Pessoa> * pessoaAux = new std::vector<TP2::Pessoa>;
        std::vector<TP2::Email> * emailAux = new std::vector<TP2::Email>;
        std::vector<TP2::Endereco> * endAux = new std::vector<TP2::Endereco>;
        std::vector<TP2::Telefone> * telAux = new std::vector<TP2::Telefone>;

        std::string linhaPessoa;
        std::ifstream arquivoPessoas;
        arquivoPessoas.open(arquivoPessoa.toStdString().c_str());
        if(!arquivoPessoas.is_open()){
            arquivoPessoas.close();
            throw QString("Erro, arquivo de pessoas não encontrado");
        }

        getline(arquivoPessoas,linhaPessoa);
        while(!arquivoPessoas.eof()){
            TP2::Pessoa obj;
            QString str = QString::fromStdString(linhaPessoa);
            obj.montarObjeto(str);
            pessoa->push_back(obj);
            getline(arquivoPessoas,linhaPessoa);
        }
        arquivoPessoas.close();

        std::string linhaEmail;
        std::ifstream arquivoEmails;
        arquivoEmails.open(arquivoEmail.toStdString().c_str());
        if(!arquivoEmails.is_open()){
            arquivoEmails.close();
            throw QString ("Erro, arquivo de E-mails não encontrado");
        }

        getline(arquivoEmails, linhaEmail);
        while (!arquivoEmails.eof()){
            TP2::Email obj;
            QString montarObj = QString::fromStdString(linhaEmail);
            obj.montarObjeto(montarObj);
            email->push_back(obj);
            getline(arquivoEmails, linhaEmail);
        }
        arquivoEmails.close();


        std::string linhaTelefone;
        std::ifstream arquivolinhaTelefones;
        arquivolinhaTelefones.open(arquivoTelefone.toStdString().c_str());
        if(!arquivolinhaTelefones.is_open()){
            arquivolinhaTelefones.close();
            throw QString ("Erro, arquivo de Telefones não encontrado");
        }

        getline(arquivolinhaTelefones, linhaTelefone);
        while (!arquivolinhaTelefones.eof()){
            TP2::Telefone obj;
            QString montarObj = QString::fromStdString(linhaTelefone);
            obj.montarObjeto(montarObj);
            tel->push_back(obj);
            getline(arquivolinhaTelefones, linhaTelefone);
        }
        arquivolinhaTelefones.close();

        std::string linhaEndereco;
        std::ifstream arquivoEnderecos;
        arquivoEnderecos.open(arquivoEndereco.toStdString().c_str());
        if(!arquivoEnderecos.is_open()){
            arquivoEnderecos.close();
            throw QString ("Erro, arquivo de Endereços não encontrado");
        }

        getline(arquivoEnderecos, linhaEndereco);
        while (!arquivoEnderecos.eof()){
            TP2::Endereco obj;
            QString montarObj = QString::fromStdString(linhaEndereco);
            obj.montarObjeto(montarObj);
            end->push_back(obj);
            getline(arquivoEnderecos, linhaEndereco);
        }
        arquivoEnderecos.close();

        std::string linha;
        getline(arquivoClientes,linha);
        while(!arquivoClientes.eof()){
            TP2::Cliente cliente;
            QString str = QString::fromStdString(linha);
            cliente.montarObjeto(str);

            for(int i = 0; i < (int) pessoa->size(); i++){
                TP2::Pessoa elemento = pessoa->operator [](i);
                if(cliente.getCPF() == elemento.getCPF()){
                    cliente.setPessoa(elemento);
                    pessoa->erase(pessoa->begin()+i);
                    i--;
                }
            }

            for (int i=0; i<(int) email->size(); i++){
                TP2::Email elemento = email->operator [](i);
                if (cliente.getCPF() == elemento.getCPF()){
                    emailAux->push_back(elemento);
                    email->erase(email->begin()+i);
                    i--;
                }
            }

            for (int i=0; i<(int) end->size(); i++){
                TP2::Endereco elemento = end->operator [](i);
                if (cliente.getCPF() == elemento.getCPF()){
                    endAux->push_back(elemento);
                    end->erase(end->begin()+i);
                    i--;
                }
            }

            for (int i=0; i<(int) tel->size(); i++){
                TP2::Telefone elemento = tel->operator [](i);
                if (cliente.getCPF() == elemento.getCPF()){
                    telAux->push_back(elemento);
                    tel->erase(tel->begin()+i);
                    i--;
                }
            }

            cliente.setEmail(emailAux);
            cliente.setTelefone(telAux);
            cliente.setEndereco(endAux);
            lista->push_back(cliente);

            pessoaAux = new std::vector<TP2::Pessoa>;
            emailAux = new std::vector<TP2::Email>;
            endAux = new std::vector<TP2::Endereco>;
            telAux = new std::vector<TP2::Telefone>;
            lista->sort();
            getline(arquivoClientes,linha);
        }
        arquivoClientes.close();
        return lista;
    } catch (QString &erro) {
        throw(erro);
    }
}
}
