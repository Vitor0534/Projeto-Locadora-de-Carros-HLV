#include "Validacoes.h"

namespace TP2 {
//*******************************************************************************************************
/* Estrutura para representar uma DataHora */
typedef struct _MinhaDataHora {
    int hora;
    int minuto;
    int segundo;
    int dia;
    int mes;
    int ano;
} MinhaDataHora;


 /* FunÃ§Ã£o auxiliar para definir os valores da estrutura DataHora */
void defineDataHora(MinhaDataHora *pd, int hora, int minuto, int segundo, int dia, int mes, int ano)
{
    pd->hora = hora;
    pd->minuto = minuto;
    pd->segundo = segundo;
    pd->dia = dia;
    pd->mes = mes;
    pd->ano = ano;
}

/* FunÃ§Ã£o para verificaÃ§Ã£o se um ano Ã© bissexto */
bool ehBissexto(int ano)
{
    /*
      Um ano sÃ³ Ã© bissexto se ele for divisÃ­vel por 4 e NÃƒO FOR divisÃ­vel por 100
      (a nÃ£o ser que ele seja divisÃ­vel por 100 E TAMBÃ‰M divisÃ­vel por 400).
    */
    return (ano % 4 == 0) && (ano % 100 != 0 || ano % 400 == 0);
}

/* FunÃ§Ã£o para contar quantos anos bissextos tem entre o ano 1/1/1 e o ano dado */
int contaBissextos(int ano)
{
    return (ano / 4) - (ano / 100) + (ano / 400);
}

/* FunÃ§Ã£o para converter a DataHora dada para segundos */
unsigned long long dataParaSegundos(MinhaDataHora d)
{
    unsigned long long total = 0LL;

    /*
     Primeiro, calcula o tempo decorrido em segundos atÃ© a data
     sem contar os anos bissextos, considerando:

     31536000 = nÃºmero de segundos em um ano nÃ£o bissexto (365 dias)
     86400 = nÃºmero de segundos em um dia (24 horas)
     3600 = nÃºmero de segundos em 1 hora (60 minutos)
     60 = nÃºmero de segundos em 1 minuto (60 segundos)
    */

    total += (d.ano - 1) * 31536000LL;

    int meses[] = { 31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31 };
    for(int mes = 1; mes < d.mes; mes++)
        total += meses[mes-1] * 86400LL;

    total += (d.dia - 1) * 86400LL;

    total += d.hora * 3600LL;

    total += d.minuto * 60LL;

    total += d.segundo;

    /*
     EntÃ£o, adiciona segundos para cada dia adicional dos anos bissextos
    */

    /* NÃºmero de dias adicionais, para os anos bissextos anteriores ao ano atual */
    int diasExtras = contaBissextos(d.ano - 1);
    total += diasExtras * 86400LL;

    /* Se o mÃªs da data jÃ¡ passou de fereveiro e o ano atual Ã© bissexto, adiciona mais um dia */
    if(ehBissexto(d.ano) && (d.mes - 1) >= 2)
        total += 86400LL;

    return total;
}

/* FunÃ§Ã£o para o cÃ¡lculo da diferenÃ§a em segundos entre duas datas */
unsigned long long calculaDiferencaEmSegundos(MinhaDataHora d1, MinhaDataHora d2)
{
    unsigned long long segundosd1 = dataParaSegundos(d1);
    unsigned long long segundosd2 = dataParaSegundos(d2);

    if(segundosd1 > segundosd2)
        return segundosd1 - segundosd2;
    else
        return segundosd2 - segundosd1;
}

/* FunÃ§Ã£o para o cÃ¡lculo da diferenÃ§a em dias entre duas datas */
unsigned long long calculaDiferencaEmDias(MinhaDataHora d1, MinhaDataHora d2)
{
    unsigned long long segundos = calculaDiferencaEmSegundos(d1, d2);
    return segundos / 86400LL;
}

int Validacoes::diferencaDatas(int dia1,int mes1,int ano1,int dia2,int mes2,int ano2)
{

        MinhaDataHora d1, d2;
        defineDataHora(&d1, 0, 0, 0,dia1, mes1, ano1);
        defineDataHora(&d2, 0, 0, 0,dia2, mes2, ano2);

       return calculaDiferencaEmDias(d1, d2);


}

//******************************************************************************************
}
