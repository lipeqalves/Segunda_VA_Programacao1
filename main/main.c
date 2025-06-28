/***************************************************************
 * Programa: Segunda VA de Programação I
 * BSI - UFRPE - 2025.1
 * Professora Sônia Virginia Alves França
 * Programador: Filipe Quirino Alves
 * Data Inicio: 28/06/2025
 * Programa para controlar os atendimentos diários
 * Copilador: VScode
 * https://github.com/lipeqalves/Primeira_VA_Programacao1.git
 ***************************************************************/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <conio.h>
#include <locale.h>
#include <windows.h>

void linha()
{
    int i;
    for (i = 1; i <= 80; i++)
        printf("_");
    printf("\n");
}

void cabec()
{
    system("cls");
    printf("Clinica Sorriso Legal\n");
    linha();
}
typedef struct{
    int codigo;
    char nome[20]; // Nome do paciente
    int sexo; // 1-Feminino, 2-Masculino
    int tratamento; // 1-Extração, 2-Restauração, 3-Canal, 4-Limpeza
    int convenio; // 1-Sim, 0-Não
    float valorDoTratamento; // Valor do tratamento
    float percentualMulheresCanal;
    int homensConvenio;
    float valorArrecadadoExtracao;
}TPaciente;

FILE *fparquivo,*frelatorio;
TPaciente paciente_aux, paciente_nulo;
// Função para inicializar o paciente nulo
void abre_arquivo()
{
    fparquivo = fopen("pacientes.dat", "r+b");
    if (fparquivo == NULL)
    {
        fparquivo = fopen("pacientes.dat", "w+b");
        if (fparquivo == NULL)
        {
            printf("Erro ao abrir o arquivo!\n");
            exit(1);
        }
    }
    frelatorio = fopen("relatorio.dat", "r+b");
    if (fparquivo == NULL)
    {
        fparquivo = fopen("relatorio.dat", "w+b");
        if (fparquivo == NULL)
        {
            printf("Erro ao abrir o arquivo!\n");
            exit(1);
        }
    }
}

float tratamentoValor(int tratamento, int covenio)
{
    float valorTratamento = 0.0;
    float desconto = 0.15; // Desconto de 15% para conveniados
    switch (tratamento)
    {
    case 1:
        valorTratamento = 110.0;
        break; // Extração
    case 2:
        valorTratamento = 135.0;
        break; // Restauração
    case 3:
        valorTratamento = 460.0;
        break; // Canal
    case 4:
        valorTratamento = 290.0;
        break; // Limpeza
    default:
        valorTratamento = 0.0;
        break; // Tratamento inválido
    }
    if (covenio == 1)
    {
        valorTratamento -= valorTratamento * desconto;
    }
    return valorTratamento;
}

void cadastrarPaciente()
{
    int escolha;
    do{
        cabec();
        printf("Cadastrar Paciente\n");
        // Coletar os dados do paciente
        printf("Codigo: ");
        scanf("%d", &paciente_aux.codigo);
        getchar();
        printf("Nome: ");
        fgets(paciente_aux.nome, sizeof(paciente_aux.nome), stdin);
        paciente_aux.nome[strcspn(paciente_aux.nome, "\n")] = '\0';
        printf("Sexo(1-Fem / 2-Mas): ");
        scanf("%d", &paciente_aux.sexo);
        printf("Tratamento(1-extração/2-restauração/3-canal/4-limpeza): ");
        scanf("%d", &paciente_aux.tratamento);
        printf("Trabalha em empresa conveniada (1-sim/0-não): ");
        scanf("%d", &paciente_aux.convenio);
        paciente_aux.valorDoTratamento = tratamentoValor(paciente_aux.tratamento, paciente_aux.convenio);

        fseek(fparquivo, 0, SEEK_END);
        fwrite(&paciente_aux, sizeof(TPaciente), 1, fparquivo);

        printf("Paciente cadastrado com sucesso!\n");
        linha();
        printf("\nDeseja cadastrar outro(1-sim/0-não)? ");
        scanf("%d", &escolha);
    }while (escolha == 1);
}
void listarPacientes()
{
    cabec();
    
   TPaciente paciente;
   fseek(fparquivo,0,SEEK_SET);

    printf("Listagem Geral de Pacientes\n");
    linha();
    printf("Código  | Nome                 | Sexo | Tratamento   | Convênio | Valor (R$)\n");
    linha();
    while (fread(&paciente, sizeof(TPaciente), 1, fparquivo) == 1)
    {
    
        printf("%-7d | %-20s | %-4d | %-13d | %-8d | %-10.2f\n",
               paciente.codigo,
               paciente.nome,
               paciente.sexo,
               paciente.tratamento,
               paciente.convenio,
               paciente.valorDoTratamento);
    }
    linha();

    printf("\nPressione Enter para voltar ao menu...");
    while (getchar() != '\n'); 
    getchar();
}
   main()
   {
       int opcao;
       system("chcp 65001 > nul"); // Configura o console para UTF-8
       setlocale(LC_ALL, "pt_BR.UTF-8"); // Configura o locale para português do Brasil
       abre_arquivo();
       do
       {
           cabec();
           printf("Menu de Opcoes:\n");
           printf("1 - Cadastrar Paciente\n");
           printf("2 - Listagem Geral\n");
           printf("3 - Relatorio Estatistico\n");
           printf("0 - Sair\n");
           printf("Escolha uma opcao: ");
           scanf("%d", &opcao);

           switch (opcao)
           {
           case 1:
               cadastrarPaciente();
               break;
           case 2:
               listarPacientes();
               break;
           case 3:
               printf("Relatorio Estatistico.\n");
               break;
           case 0:
               fclose(fparquivo);
               break;
           default:
               printf("Opcao invalida. Tente novamente.\n");
           }
       } while (opcao != 0);
       printf("Pressione Enter para Finalizar..."); // aguarda o usuário pressionar "Enter", criando a pausa desejada
       while (getchar() != '\n'); // Limpa o buffer de entrada
       getchar();
   }
