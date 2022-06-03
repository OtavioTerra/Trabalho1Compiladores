#include <stdio.h>
#include <stdlib.h>
#include <string.h>


#define NUM_RESERVADAS 17
#define MAX_TAMANHO 50


// Definindo as palavras reservadas
char reservadas [NUM_RESERVADAS][MAX_TAMANHO] = {""};
void salvaReservadas(){
    strcpy(reservadas[0],"program");
    strcpy(reservadas[1],"var");
    strcpy(reservadas[2],"integer");
    strcpy(reservadas[3],"real");
    strcpy(reservadas[4],"begin");
    strcpy(reservadas[5],"end");
    strcpy(reservadas[6],"if");
    strcpy(reservadas[7],"else");
    strcpy(reservadas[8],"then");
    strcpy(reservadas[9],"for");
    strcpy(reservadas[10],"do");
    strcpy(reservadas[11],"to");
    strcpy(reservadas[12],"while");
    strcpy(reservadas[13],"write");
    strcpy(reservadas[14],"read");
    strcpy(reservadas[15],"const");
    strcpy(reservadas[16],"procedure");
}


void automatoNumeros(char palavra[]){

    //Abre o arquivo de saida
    FILE *ponteiro_saida;
    ponteiro_saida = fopen("saida.txt", "a+");
    if(ponteiro_saida == NULL){
        printf("Erro na leitura de arquivo\n");
        return;
    }

    //Variaveis
    int i = 0, j;
    int flag = 0;
    char c = palavra[i];
    

    do
    {
        switch (flag)
        {
        // primeiro caracter
        case 1:
            if(c == '+' || c == '-' || (c > '0' && c < '9')){
                flag = 3;
            }
            else{
                flag = 2;
            }

            break;
        
        // caracter invalido
        case 2:
            printf("Numero invalido");
            break;

        // caracter numero ou inicio da parte decimal
        case 3:
            if((c > '0' && c < '9'))flag = 3;
            else if(c == '.') flag = 4;
            else flag = 2;
            break;
        
        //parte decimal
        case 4:
            if((c > '0' && c < '9')) flag = 4;
            else flag = 2;
         
        default:
            break;
        }
        c = palavra[i++];
    } while (i < strlen(palavra));
    
    // TODO: implementar a string de saida 

}

// Automato dos identificadores
// Recebe uma palavra(token)
// Verifica se a palavra é valida e se é uma palavra reservada
void automatoIdentificadores(char palavra[], FILE *ponteiro_saida){

    //Abre o arquivo de saida
   /* FILE *ponteiro_saida;
    ponteiro_saida = fopen("saida.txt", "a+");
    if(ponteiro_saida == NULL){
        printf("Erro na leitura de arquivo\n");
        return;
    }
    */

    //Variaveis
    int j, i = 0, flag = 0, flag_reservada = 0;
    char tipo_palavra[MAX_TAMANHO] = "";
    char c = palavra[i];


    //Começa o processo de ler a palavra
    do 
    {
        switch (flag)
        {
        case 0: // verifica a primeira letra
            if((c > 'a' && c < 'z') || (c > 'A' && c < 'Z')){
                flag = 1; // caso a primeira letra esteja ok
            }
            else{
                flag = 2; // caso seja invalido
            }
            break;
        
        case 1: // verifica o restante das letras
            if((c > 'a' && c < 'z') || (c > 'A' && c < 'Z') || (c > '0' && c < '9') || (c != '_')){
                flag = 1; // caso o simbolo esteja OK, continua
            }
            else{
                flag = 2; // caso seja invalido
            }
        default:
            break;
        }

        c = palavra[i++];
    } while (i <= strlen(palavra));

    //Verifica se é reservada ou não
    if(flag != 2){
        for(j = 0; j < NUM_RESERVADAS; j++){
            if(strcmp(palavra,reservadas[j]) == 0){
                flag_reservada = 1;
                strcpy(tipo_palavra, palavra);
                strcat(tipo_palavra, " -> ");
                strcat(tipo_palavra, reservadas[j]);
                strcat(tipo_palavra, "_simb\n");
            }
        }
        if(flag_reservada != 1){
            strcpy(tipo_palavra, palavra);
            strcat(tipo_palavra, " -> ");
            strcat(tipo_palavra,"identificador");
            strcat(tipo_palavra, "_simb\n");
        }

    }
    else{
        strcpy(tipo_palavra, palavra);
        strcat(tipo_palavra, " -> ");
        strcat(tipo_palavra, "(ERRO, PALAVRA INVALIDA) ");
        strcat(tipo_palavra, "invalida");
        strcat(tipo_palavra, "_simb\n");
    }
    
    // grava no arquivo a palavra e fecha o arquivo
    printf("toda palavra consumida\n\n\n");
    fputs(tipo_palavra,ponteiro_saida);
    fclose(ponteiro_saida);
}


int main(int argc, char **argv){
    FILE *ponteiro_saida;
    ponteiro_saida = fopen("saida.txt", "a+");
    if(ponteiro_saida == NULL){
        printf("Erro na leitura de arquivo\n");
        return;
    }

    salvaReservadas();
    automatoIdentificadores("var", ponteiro_saida);

    return 0;
}