//BIBLIOTECA
//stdio.h: Permite o I/O dos dados (printf, scanf, fgets, getchar).
#include <stdio.h>

//Matriz para armazenamento dos nomes dos meses. O primeiro índice indica a quantidade de meses. O Segundo índice indica a quantidade de caracteres máximos para os nomes.
char meses[12][20]={"Janeiro", "Fevereiro", "Março", "Abril", "Maio", "Junho", "Julho", "Agosto", "Setembro", "Outubro", "Novembro", "Dezembro"};
//Vetor que guarda o último dia de cada mês.
int ultimoDiaDoMes[12]={31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};
//Matriz para guardar anotações. Segue a ordem de índices: dia, mês, texto.
char informacoes[31][12][101];
//Variável para armazenar o ano.
int ano;

//Função que utiliza o algoritmo de Sakamoto para calcular o dia da semana de determinada data.
//O algoritmo de Tomohiko Sakamoto calcula o dia da semana para qualquer data do calendário gregoriano. Ele retorna um número de 0 (domingo) a 6 (sábado).
//PARÂMETROS: dia, mês e ano da data.
int diaSemana(int dia,int mes,int ano) {
    //Cada posição representa um mês e contém um valor utilizado no cálculo para compensar a quantidade de dias de cada mês.
    int tabela[]={0,3,2,5,0,3,5,1,4,6,2,4};
    //Se o mês for janeiro ou fevereiro, o algoritmo considera o ano anterior.
    if (mes<3){
        ano--;
    }
    return(ano+ano/4-ano/100+ano/400+tabela[mes-1] + dia) % 7; //Realiza o cálculo de Sakamoto, retornando um número que representa o dia da semana.
}

//FUNÇÃO PRINCIPAL
int main(){
    //solicita o ano
    printf("Digite o ano atual:");
    scanf("%i", &ano);
    //se o ano for bissexto, altera o último dia de fevereiro para 29.
    if((ano%400==0) || (ano%4==0 && ano%100!=0)){
        ultimoDiaDoMes[1]=29;
    }
    //Variáveis. Op armazena a opção escolhida do menu. O dia e o mes armazenam a data.
    int op, dia, mes;
    //Laço de repetição do-while: obrigatório passar pelo menos uma vez. Continua sendo executada enquanto op for diferente de 0.
    do{
        printf("\n===== MENU - Ano %i =====\n", ano);
        printf("1 - Verificar calendário completo\n");
        printf("2 - Verificar calendário de um mês específico\n");
        printf("3 - Adicionar nota em uma data\n");
        printf("4 - Verificar todas as notas disponíveis \n");
        printf("0 - Finalizar programa\n Opção:");
        scanf("%i", &op);
        //Verifica se a opção escolhida foi inválida e pede novo valor até ser digitado um número válido.
        while(op<0 || op>4){
            printf("Digite um número válido do menu! \nDigite novamente: ");
            scanf("%i", &op);
        }
        //estrutura condicional de múltipla escolha para valores de variáveis
        switch(op){
            //caso op tenha valor 1
            case 1:
            //percorre todos os meses
                for (int i = 0; i < 12; i++) {
                printf("\n\n========= %-9s =========\n", meses[i]); //Formata o cabeçalho do mês do calendário
                printf(" Dom Seg Ter Qua Qui Sex Sab\n"); //Imprime os dias da semana
                int inicio=diaSemana(1,i+1,ano); //Chama a função que retorna o dia da semana do primeiro dia do mês
                for(int j=0;j<inicio;j++) {
                    printf("    ");  //Define espaçamentos antes do dia 1
                }
                //Percorre os dias do mês
                for(int dia=1; dia<=ultimoDiaDoMes[i]; dia++){
                    //Formata os números do calendário. Caso tenha uma anotação naquele dia, imprime junto uma bolinha ao lado do dia.
                    printf("%3i%s", dia, informacoes[dia-1][i][0] != '\0' ? "·" : " ");
                    //Verifica se o dia é sábado, e se sim, pula linha
                    if((inicio+dia)%7==0) {
                        printf("\n");
                    }
                }
                printf("\n");
            }
            break;
            case 2:
                //Solicita o mês
                printf("Digite o mês em formato númerico (Ex.: 1, 2, 3...):\n");
                scanf("%i", &mes);
                //Verifica se o mês é inválido
                while(mes<=0 || mes>12){
                    printf("Número inválido\n Digite novamente: ");
                    scanf("%i", &op);
                }
                //Imprime somente o mês - mesmo esquema do case 1
                printf("\n\n========= %-9s =========\n", meses[mes-1]);
                printf(" Dom Seg Ter Qua Qui Sex Sab\n");
                int inicio=diaSemana(1,mes,ano);
                for(int j=0;j<inicio;j++) {
                    printf("    ");
                }
                for(int dia=1; dia<=ultimoDiaDoMes[mes-1]; dia++){
                    printf("%3d%s", dia, informacoes[dia-1][mes-1][0] != '\0' ? "·" : " ");
                    if((inicio+dia)%7==0) {
                        printf("\n");
                    }
                }
            break;
        case 3:
            //Solicita o dia e requer que seja um dia válido
            printf("Digite o dia:");
            scanf("%i",&dia);
            while(dia<=0 || dia>31){
                printf("Dia inválido!\n Digite novamente:");
                scanf("%i",&dia);
            }
            //Solicita o mês e requer que seja um mês válido
            printf("Digite o mês:");
            scanf("%i",&mes);
            while(mes<=0 || mes>12){
                printf("Mês inválido!\n Digite novamente:");
                scanf("%i",&mes);
            }
            //Verifica se o dia ultrapassa o último dia do mês (Ex.: Escrever dia 31 em um mês que tem só 30 dias)
            if(dia > ultimoDiaDoMes[mes-1]){
                printf("Data inválida! O último dia do mês é dia %i", ultimoDiaDoMes[mes-1]);
            }else{ //Se a data estiver no limite certo
                printf("Digite a informação a ser inserida:");
                getchar(); //Limpa o \n: Quando o usuário digita um número e clica em ENTER, um \n continua no buffer de entrada
                fgets(informacoes[dia-1][mes-1], 101, stdin); //Realiza a leitura dos dados digitados do teclado, permitindo a escrita de 100 caracteres.
            }
            break;
            case 4:
                //Percorre todos os meses
                for(int i=0; i<12; i++){
                    //Variável verificadora
                    int encontrou = 0;
                    //Percorre os dias desse mês
                    for(int j=0; j<ultimoDiaDoMes[i]; j++){
                        //Se houver alguma informação na data, a variável verificadora passa a valer 1 e sai da iteração
                        if(informacoes[j][i][0] != '\0'){
                            encontrou = 1;
                            break;
                        }
                    }
                    if(encontrou == 1){
                        //Imprime o nome do mês e percorre os dias, exibindo na tela os que possuem informações
                        printf("\n%s\n", meses[i]);
                        for(int j=0; j<ultimoDiaDoMes[i]; j++){
                            if(informacoes[j][i][0] != '\0'){
                                printf("%d - %s", j+1, informacoes[j][i]);
                            }
                        }
                    }
                }
            break;
        }
    }while(op!=0);
    return 0; //indica ao sistema operacional que o programa terminou sua execução com sucesso e sem erros
}