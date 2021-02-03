#include "Cliente.h"
namespace TP2 {
Cliente::Cliente():
    CPF(0),
    identidade(0),
    numeroDoCartao(0)
{
    email = new std::vector<TP2::Email>;
    Endereco = new std::vector<TP2::Endereco>;
    telefone = new std::vector<TP2::Telefone>;
}

Cliente::Cliente(unsigned long long identidade, unsigned long long numeroDoCartao, Pessoa pessoa
              ,std::vector<TP2::Telefone> * telefone, std::vector<TP2::Email> * email,std::vector<TP2::Endereco> * Endereco,
              long long int CPF):
    identidade(identidade),
    numeroDoCartao(numeroDoCartao),
    pessoa(pessoa),
    email(email),
    Endereco(Endereco),
    telefone(telefone),
    CPF(CPF)
{

}

long long Cliente::getCPF() const
{
    return CPF;
}

void Cliente::setCPF(long long CPF)
{
    this->CPF = CPF;
}

Pessoa Cliente::getPessoa() const
{
    return pessoa;
}

void Cliente::setPessoa(Pessoa pessoa)
{
    this->pessoa = pessoa;
}

std::vector<Telefone> const* const Cliente::getTelefone() const
{
    return telefone;
}

void Cliente::setTelefone(std::vector<TP2::Telefone> *telefone)
{
    if(this->telefone)
        delete this->telefone;
    this->telefone = telefone;
}

std::vector<TP2::Email> const * const Cliente::getEmail() const
{
    return email;
}

void Cliente::setEmail(std::vector<TP2::Email> *email)
{
    if(this->email)
        delete this->email;
    this->email = email;
}

std::vector<TP2::Endereco> const * const Cliente::getEndereco() const
{
    return Endereco;
}

void Cliente::setEndereco(std::vector<TP2::Endereco> * Endereco)
{
    if(this->Endereco)
        delete this->Endereco;
    this->Endereco = Endereco;
}

void Cliente::montarObjeto(QString &str)
{
    try {

        QStringList strList = str.split(';');
        if(strList.length()!=3)
            throw QString("Faltam informações na categoria");
        CPF = strList[0].toLongLong();
        identidade = strList[1].toInt();
        numeroDoCartao = strList[2].toInt();

    } catch (...) {
        throw QString("Erro no metodo montar Categoria!");
    }
}

QString Cliente::desmontarObjeto() const
{
    try{

        QString saida = QString::number(CPF);
        saida += ";";
        saida += QString::number(identidade);
        saida += ";";
        saida += QString::number(numeroDoCartao) + "\n";
        return saida;

    }catch (...){
        throw QString("Erro no metodo desmontar categoria!");
    }
}


}
