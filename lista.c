#include<stdio.h>
#include<stdlib.h>
#include<time.h>

typedef struct Pessoa{
    char nome[50];
    int idade;
    int id;
    struct Pessoa *prox; //ponteiro que armazena o endereço do proxima Pessoa
}Pessoa;

//função para criar um novo registro
Pessoa* criarPessoa() {
    Pessoa *novaPessoa = (Pessoa*)malloc(sizeof(Pessoa));

    if(novaPessoa == NULL) {
        printf("Erro de alocacao de memoria");
        exit(EXIT_FAILURE);
    }

    novaPessoa->prox = NULL;
    return novaPessoa;
}

Pessoa* cadastrar(Pessoa *lista) {
    srand(time(NULL));
    Pessoa *novaPessoa = criarPessoa();
    novaPessoa->id = rand() % 100;

    printf("\n Digite o nome: \n");
    fgets(novaPessoa->nome, sizeof(novaPessoa->nome), stdin);
    fflush(stdin);

    printf("\n Digite a idade: \n");
    scanf("%d", &novaPessoa->idade);

    //verificar se a lista é nula
    if (lista == NULL) {
        return novaPessoa;
    } else {
        Pessoa *atual = lista;
        
        while(atual->prox != NULL) {
            atual = atual->prox;
            //sai da repetição quando encontrar o elemento que aponta para NULL
        }
        atual->prox = novaPessoa;
        
        return lista; //atualizar a lista
    }
}

void mostrarLista(Pessoa *lista){
    Pessoa *atual = lista;
    while(atual != NULL) {
        printf("\n Nome: %s", atual->nome);
        printf("\n Idade: %d", atual->idade);
        printf("\n ID: %d", atual->id);
        printf("\n");
        atual = atual->prox;
    }
}

void buscarPessoa(Pessoa *lista, int idBusca){
    Pessoa *atual = lista;
    if(lista == NULL){
        print("\n Lista nula");
        return;
    }
    
    while(atual != NULL){
        if (atual->id == idBusca) {
            printf("\n Nome: %s", atual->nome);
            printf("\n Idade: %d", atual->idade);
            printf("\n ID: %d", atual->id);
            printf("\n");
            return atual;
        }

        atual = atual->prox;
    } 
    
    printf("\n Pessoa nao encontrada");
    return NULL;
        
}

void alterar(Pessoa *pessoa) {
    printf("\n Digite o novo nome: \n");
    fflush(stdin);
    fgets(pessoa->nome, sizeof(pessoa->nome), stdin);
    fflush(stdin);

    printf("\n Digite a nova idade \n");
    fflush(stdin);
    scanf("%d", &pessoa->idade);    
}

Pessoa* excluir(Pessoa *lista, int idBusca) {
    Pessoa *atual = lista;
    Pessoa *anterior = NULL;

    while (atual != NULL && atual->id != idBusca) {
        atual = atual->prox;
        anterior = atual;
    }

    if (atual != NULL) {
        if(anterior != NULL){
        //excluindo alguem depois da maria
        anterior->prox = atual->prox;
        } else {
        //excluir a maria (primeiro da lista)
        lista = atual->prox;
        }
        
        free(atual);
        printf("\n Removido com sucesso");
    } else {
        printf("\n Pessoa nao encontrada");
    }
    
    return lista;

}

void liberarLista(Pessoa *lista) {
    Pessoa *atual = lista;
    Pessoa *prox;

    while(atual != NULL){
        prox = atual->prox;
        free(atual);
        atual = prox;
    }
}


int main() {

    int opcao;
    int idBusca;
    Pessoa *encontrada; //armazenar a pessoa encontrada para excluir ou alterar
    Pessoa *lista = NULL; //sempre vai ser o primeiro da lista

    do {
        printf("\n Digite 1 para cadastrar");
        printf("\n Digite 2 para mostrar");
        printf("\n Digite 3 para buscar");
        printf("\n Digite 4 para alterar");
        printf("\n Digite 5 para excluir");
        printf("\n Digite 0 para sair \n");
        scanf("%d", &opcao);

        switch (opcao) {
            case 1:
                lista = cadastrar(lista);
            break;


            case 2:
                mostrarLista(lista);
            break;


            case 3:
                printf("\n Digite o id para busca \n");
                scanf("%d", &idBusca);
                buscarPessoa(lista, idBusca);
            break;


            case 4:
                printf("\n Digite o id para alteracao \n");
                scanf("%d", &idBusca);
                encontrada = buscarPessoa(lista, idBusca);
                if (encontrada != NULL) {
                    alterar(encontrada);
                }
            break;


            case 5:
                printf("\n Digite o id para exclusao \n");
                scanf("%d", &idBusca);
                lista = excluir(lista, encontrada);
            break;
        }

    } while(opcao != 0);

    liberarLista(lista);

    return 0;

}