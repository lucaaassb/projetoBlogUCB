#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define LIMPA_TELA system("clear");

//**************************************STRUCTS**************************************
typedef struct Usuarios { 
    int idUsuario;
    char nomeUsuario[50];
    char login[50];
    char senha[50];
} Usuario; 

typedef struct Posts{
    int idPost;
    char titulo[250];
    char postagem[5000];
    struct Usuarios *usuarios;
} Post;

typedef struct Comentarios {
    int idComentarios;
    char comentario[500];
		Usuario *usuarios;
    Post *post;
} Comentario;

//**************************************FUNÇÕES**************************************

/**
 * Recebe os dados para login
 *
 * @Usuario[]: A struct de usuarios.
 * @*qtdUsuarios: Quantidade de usuarios cadastrados no arquivo
 */
Usuario *login(Usuario usuarios[], int *qtdUsuarios);

/**
 * Realiza a validação do login
 *
 * @Usuario[]: A struct de usuarios.
 * @*qtdUsuarios: Quantidade de usuarios cadastrados no arquivo
 * @*login: Ponteiro com o valor do login
 * @*senha: Ponteiro com o valor da senha
 */
Usuario *validaLogin(char *login, char *senha, Usuario usuarios[] ,int *qtdUsuarios);

/**
 * Realiza a busca por usuários no blog
 *
 * @Usuario[]: A struct de usuarios.
 * @*qtdUsuarios: Quantidade de usuarios cadastrados no arquivo
 * @idUsuario: Id gerado para cada usuario
 */
Usuario *procuraUsuario(Usuario usuarios[], int *qtdUsuarios, int idUsuario);

/**
 * Realiza a busca pelos posts no blog
 *
 * @Post[]: A struct de usuarios.
 * @*qtdposts: Quantidade de posts cadastrados no arquivo
 * @idPost: Inteiro com o ID de cada post 
 */
Post *procuraPost(Post posts[], int *qtdposts, int idPost);

/**
 * Carrega os dados do Arquivo para a struct de usuarios
 *
 * @Usuario[]: A struct de usuarios.
 * @*qtdUsuarios: Quantidade de usuarios cadastrados no arquivo
 * @*arqUsuario: Arquivo de usuários.
 */
int carregaUsuarios(FILE *arqUsuario, Usuario usuarios[], int *qtdUsuarios);

/**
 * Realiza o cadastro dos usuários no blog
 *
 * @Usuario[]: A struct de usuarios.
 * @*qtdUsuarios: Quantidade de usuarios cadastrados no arquivo
 * @*arqUsuario: Arquivo de usuários.
 */
void cadastraUsuarios(FILE *arqUsuario, Usuario usuarios[], int *qtdUsuarios);

/**
 * Insere os dados necessários para a realização do cadastro do usuário no blog
 *
 * @Usuario[]: A struct de usuarios.
 * @*qtdUsuarios: Quantidade de usuarios cadastrados no arquivo
 * @idUsuario: Id gerado para cada usuário
 */
void insereDadosUsuario(Usuario usuarios[], int *qtdUsuario, int idUsuario);

/**
 * Realiza a impressão de usuários na tela
 *
 * @Usuario[]: A struct de usuarios.
 * @*qtdUsuarios: Quantidade de usuarios cadastrados no arquivo
 */
void imprimeUsuarios(Usuario usuarios[], int *qtdUsuario);

/**
 * Deleta usuários do sistema
 *
 * @Usuario[]: A struct de usuarios.
 * @*qtdUsuarios: Quantidade de usuarios cadastrados no arquivo
 * @*arqUsuario: Arquivo de usuarios
 */
void deletaUsuario(FILE *arqUsuario, Usuario usuarios[], int *qtdUsuario);

/**
 * Realiza a alteração dos dados dos usuários no sistema
 *
 * @Usuario[]: A struct de usuarios.
 * @*qtdUsuarios: Quantidade de usuarios cadastrados no arquivo
 * @*arq: Arquivo de usuarios
 */
void alteraUsuario(FILE *arq, Usuario usuarios[], int *qtdUsuario);

/**
 * Realiza a inserção de dados nos posts, como titulo, conteúdo, etc.
 *
 * @Usuario[]: A struct de usuarios.
 * @Post[]: A struct de posts.
 * @validaUsuario: Validação dos dados de usuário
 * @*qtdPost: Quantidade de posts cadastrados no arquivo
 * @*qtdUsuarios: Quantidade de usuarios cadastrados no arquivo
 * @idPost: Id gerado para cada post do blog
 */
void insereDadosPost(Post posts[], Usuario usuarios[], Usuario validaUsuario, int *qtdPost, int *qtdUsuarios, int idPost);

/**
 * Realiza o cadastro de posts no blog
 *
 * @Post[]: A struct de posts.
 * @*qtdPost: Quantidade de posts cadastrados no arquivo
 * @*arq: Arquivo de usuarios
 */
void cadastraPosts(FILE *arq, Post posts[], int *qtdPost);

/**
 * Carrega os dados do Arquivo para a struct de Postagens
 *
 * @Usuario[]: A struct de usuarios.
 * @Post[]: A struct de posts.
 * @*qtdUsuarios: Quantidade de usuarios cadastrados no arquivo
 * @*qtdPosts: Quantidade de posts cadastrados no arquivo
 * @*arqPosts: Arquivo dos posts
 */
int carregaPostagens(FILE *arqPosts, Post posts[], Usuario usuarios[], int *qtdPosts, int *qtdUsuarios);

/**
 * Realiza a impressão das postagens feitas
 *
 * @Post[]: A struct de posts.
 * @*qtdPosts: Quantidade de posts cadastrados no arquivo
 */
void imprimePostagens(Post posts[], int *qtdPosts);

/**
 * Deleta postagens feitas no blog
 *
 * @Usuario[]: A struct de usuarios.
 * @Post[]: A struct de posts.
 * @*arqPosts: Arquivo dos posts
 * @*qtdPosts: Quantidade de posts cadastrados no arquivo
 * @*qtdUsuarios: Quantidade de usuarios cadastrados no arquivo
 */
void deletaPostagem(FILE *arqPosts, Post posts[], Usuario usuarios[], int *qtdPosts, int *qtdUsuarios );

/**
 * Realiza a alteração das postagens feitas no blog
 *
 * @Usuario[]: A struct de usuarios.
 * @Post[]: A struct de posts.
 * @*arqPost: Arquivo dos posts
 * @validaUsuario: Validação de dados do usuario
 * @*qtdPosts: Quantidade de posts cadastrados no arquivo
 * @*qtdUsuarios: Quantidade de usuarios cadastrados no arquivo
 * @idPost: Id gerado para cada post feito no blog
 */
void alteraPostagem(FILE *arqPost, Post posts[], Usuario usuarios[], Usuario validaUsuario, int *qtdPosts, int *qtdUsuarios, int idPost);

/**
 * Realiza a impressão da lista de todas as postagens existentes no blog
 *
 * @Post[]: A struct de posts.
 * @*qtdPosts: Quantidade de posts cadastrados no arquivo
 */
int listaPostagem(Post posts[], int *qtdPosts);

/**
* Exibe o post completo com seus respectivos título, conteúdo e comentarios
*
* @Post[]: A struct dos posts
* @Comentario[]: A struct dos comentarios
* @*qtdPosts: Quantidade de posts cadastrados no arquivo
* @*qtdComent: Quantidade de comentarios cadastrados no arquivo
* @op: Variável para possibilitar a navegação do usuário pelos menus
*/
int detalhaPostagem(Post posts[], Comentario comentarios[], int *qtdPosts, int *qtdComent, int op);

/**
* Realiza o inserção dos comentarios nos posts do blog
*
* @validaUsuario: Validação de dados do usuarios
* @Post[]: A struct dos posts
* @Comentario[]: A struct dos comentarios
* @*qtdComent: Quantidade de comentarios cadastrados no arquivo
* @*qtdPosts: Quantidade de posts cadastrados no arquivo
* @idPost: Id gerado para cada post feito no blog
* @idComent: Id gerado para cada comentario nos posts
*/
void insereComentarios(Usuario validaUsuario, Post posts[], Comentario comentarios[], int *qtdComent, int *qtdPosts, int idPost, int idComent);

/**
* Realiza o cadastro dos comentarios nos posts do blog
*
* @*arq: Arquivo de usuarios
* @Comentario[]: A struct dos comentarios
* @*qtdComent: Quantidade de comentarios cadastrados no arquivo
*/
void cadastraComentarios(FILE *arq, Comentario comentarios[], int *qtdComent);

/**
 * Realiza o carregamento e a impressão dos comentarios feitos no blog
 *
 * @*arqComent: Arquivo dos comentarios
 * @Post[]: A struct dos posts
 * @Usuario[]: A struct dos usuarios
 * @Comentario[]: A struct dos comentarios
 * @*qtdUsuarios: Quantidade de usuarios cadastrados no arquivo
 * @*qtdPosts: Quantidade de posts cadastrados no arquivo
 * @*qtdComent: Quantidade de comentarios cadastrados no arquivo
 */
int carregaComentarios(FILE *arqComent, Post posts[], Usuario usuarios[], Comentario comentarios[], int *qtdUsuarios,int *qtdPosts, int *qtdComent);

/**
 * Realiza a impressão da Menu Geral do blog
 *
 * @*arqUsuario: Arquivo dos usuarios
 * @*arqPosts: Arquivo dos posts
 * @*arqComent: Arquivo dos comentarios
 * @Post[]: A struct de posts.
 * @Usuario[]: A struct de usuarios.
 * @Comentario[]: A struct de comentarios.
 * @validaUsuario: Validação de dados do usuario
 * @*qtdUsuarios: Quantidade de usuarios cadastrados no arquivo
 * @*qtdPosts: Quantidade de posts cadastrados no arquivo
 * @*qtdComent: Quantidade de comentarios ncadastrados no arquivo
 * @idUsuario: Id gerado para cada usuario
 * @idPost: Id gerado para cada post feito no blog
 * @idComent: Id gerado para cada comentario nos posts
 */
int menuGeral(FILE *arqUsuario, FILE *arqPosts, FILE *arqComent, Post posts[], Usuario usuarios[], Comentario comentarios[], Usuario validaUsuario, int *qtdUsuarios, int *qtdPosts, int *qtdComent, int idUsuario, int idPost, int idComent);

/**
 * Realiza a impressão da Menu para as postagens do blog
 *
 * @*arqUsuario: Arquivo dos usuarios
 * @*arqPosts: Arquivo dos posts
 * @*arqComent: Arquivo dos comentarios
 * @Post[]: A struct de posts.
 * @Usuario[]: A struct de usuarios.
 * @Comentario[]: A struct de comentarios.
 * @validaUsuario: Validação de dados do usuario
 * @*qtdUsuarios: Quantidade de usuarios cadastrados no arquivo
 * @*qtdPosts: Quantidade de posts cadastrados no arquivo
 * @*qtdComent: Quantidade de comentarios ncadastrados no arquivo
 * @idUsuario: Id gerado para cada usuario
 * @idPost: Id gerado para cada post feito no blog
 * @idComent: Id gerado para cada comentario nos posts
 */
void menuPostagem(FILE *arqUsuario, FILE *arqPosts, FILE *arqComent, Post posts[], Usuario usuarios[], Comentario comentarios[], Usuario validaUsuario, int *qtdUsuarios, int *qtdPosts, int *qtdComent, int idUsuario, int idPost, int idComent);

/**
 * Realiza a impressão da Menu do Usuario do blog
 *
 * @*arqUsuario: Arquivo dos usuarios
 * @*arqPosts: Arquivo dos posts
 * @*arqComent: Arquivo dos comentarios
 * @Post[]: A struct de posts.
 * @Usuario[]: A struct de usuarios.
 * @Comentario[]: A struct de comentarios.
 * @validaUsuario: Validação de dados do usuario
 * @*qtdUsuarios: Quantidade de usuarios cadastrados no arquivo
 * @*qtdPosts: Quantidade de posts cadastrados no arquivo
 * @*qtdComent: Quantidade de comentarios ncadastrados no arquivo
 * @idUsuario: Id gerado para cada usuario
 * @idPost: Id gerado para cada post feito no blog
 * @idComent: Id gerado para cada comentario nos posts
 */
void menuUsuario(FILE *arqUsuario, FILE *arqPosts, FILE *arqComent, Post posts[], Usuario usuarios[], Comentario comentarios[], Usuario validaUsuario, int *qtdUsuarios, int *qtdPosts, int *qtdComent, int idUsuario, int idPost, int idComent);

//**************************************MAIN**************************************
int main(void) {
    int qtdUsuarios = 0, qtdPosts = 0, qtdComent = 0, idUsuario, idPost, idComent, op;
    Usuario usuarios[1000];
		Post posts[1000];
		Comentario comentarios[1000];
		Usuario *validaUsuario;

    FILE *arqUsuario;
    arqUsuario = fopen("usuarios.txt", "a+");
    assert(arqUsuario != NULL);

    FILE *arqPosts;
    arqPosts = fopen("posts.txt", "a+");
    assert(arqPosts != NULL);

		FILE *arqComent;
    arqComent = fopen("comentarios.txt", "a+");
    assert(arqComent != NULL);

		idUsuario = carregaUsuarios(arqUsuario, usuarios, &qtdUsuarios);
		idPost = carregaPostagens(arqPosts, posts, usuarios, &qtdPosts, &qtdUsuarios);
		idComent = carregaComentarios(arqComent, posts,  usuarios, comentarios, &qtdUsuarios, &qtdPosts, &qtdComent);

		do{
			validaUsuario =	login(usuarios, &qtdUsuarios);
			
		} while(validaUsuario == NULL);

		do{
			op = menuGeral(arqUsuario, arqPosts, arqComent, posts, usuarios, comentarios, *validaUsuario, &qtdUsuarios, &qtdPosts,&qtdComent, idUsuario, idPost, idComent);
		} while (op != 0);
		

    fclose(arqUsuario);
    fclose(arqPosts);
		fclose(arqComent);

    return 0;
}
//**************************************USUARIOS**************************************
void insereDadosUsuario(Usuario usuarios[], int *qtdUsuario, int id){
	LIMPA_TELA
	printf("*** CADASTRO DE USUARIOS ***\n\n");
	printf("Entre com o nome do Usuario: ");
	scanf(" %[^\n]", usuarios[*qtdUsuario].nomeUsuario);
	
	printf("\nEntre com o login do Usuario: ");
	scanf(" %[^\n]", usuarios[*qtdUsuario].login);
	
	printf("\nEntre com a senha do Usuario: ");
	scanf(" %[^\n]", usuarios[*qtdUsuario].senha);
	
	usuarios[*qtdUsuario].idUsuario = id + 1;
	(*qtdUsuario)++;

  printf("\nUsuário Cadastrado com sucesso!\n\n");
  
}

void cadastraUsuarios(FILE *arqUsuario, Usuario usuarios[], int *qtdUsuarios){
	
  	fprintf(arqUsuario, "%d|%s|%s|%s\n", usuarios[*qtdUsuarios-1].idUsuario, usuarios[*qtdUsuarios-1].nomeUsuario, usuarios[*qtdUsuarios-1].login, usuarios[*qtdUsuarios-1].senha);
		fflush(arqUsuario);

}

void imprimeUsuarios(Usuario usuarios[], int *qtdUsuario){
  	int i; 
		LIMPA_TELA
  	printf("*** LISTA DE USUARIOS DO SISTEMA: ***\n\n");
  	for (i = 0; i < *qtdUsuario; i++ ){
    	printf("#%d - %s - %s - %s\n", usuarios[i].idUsuario, usuarios[i].nomeUsuario, usuarios[i].login, usuarios[i].senha);
	}
  	printf("\n\n");
}

int carregaUsuarios(FILE *arqUsuario, Usuario usuarios[], int *qtdUsuarios){
	int id;
  	while(!feof(arqUsuario)){
    	fscanf(arqUsuario, "%d|%[^|]|%[^|]|%[^\n]\n", &usuarios[*qtdUsuarios].idUsuario, usuarios[*qtdUsuarios].nomeUsuario, usuarios[*qtdUsuarios].login, usuarios[*qtdUsuarios].senha);
    	(*qtdUsuarios)++;
  	}
  	id = usuarios[*qtdUsuarios - 1].idUsuario;
  	
  	return id;
}

void deletaUsuario(FILE *arqUsuario, Usuario usuarios[], int *qtdUsuario){
	FILE *arqNovo; 
	int id, i = 0;

	arqNovo = fopen("usuariosNovo.txt", "a+");
	assert(arqNovo != NULL);
	
	imprimeUsuarios(usuarios, qtdUsuario);
	printf("Entre com o id a ser apagado: ");
	scanf("%d", &id);
	
	for(i = 0; i < *qtdUsuario; i++){
		if(id != usuarios[i].idUsuario){
			fprintf(arqNovo, "%d|%s|%s|%s\n", usuarios[i].idUsuario, usuarios[i].nomeUsuario, usuarios[i].login, usuarios[i].senha);
		}
	}
	
	fclose(arqNovo);
	fclose(arqUsuario);
	remove("usuarios.txt");
	rename("usuariosNovo.txt", "usuarios.txt");
	
	arqUsuario = fopen("usuarios.txt", "a+");
	printf("\nUSUARIO DELETADO COM SUCESSO!\n\n\n");		
}

void alteraUsuario(FILE *arq, Usuario usuarios[], int *qtdUsuario){
	FILE *arqNovo; 
	int id, i = 0;
	
	arqNovo = fopen("usuariosNovo.txt", "a+");
	assert(arqNovo != NULL);
	
	imprimeUsuarios(usuarios, qtdUsuario);

	printf("Entre com o id a ser atualizado: ");
	scanf("%d", &id);
	LIMPA_TELA
	printf("*** INSIRA OS NOVOS DADOS DO USUARIO ***");
	for(i = 0; i < *qtdUsuario; i++){
		if(id == usuarios[i].idUsuario){
			printf("\n\nEntre com o novo nome do Usuario: ");
			scanf(" %[^\n]", usuarios[i].nomeUsuario);
			
			printf("\nEntre com o novo login do Usuario: ");
			scanf(" %[^\n]", usuarios[i].login);
			
			printf("\nEntre com a nova senha do Usuario: ");
			scanf(" %[^\n]", usuarios[i].senha);
			
			usuarios[i].idUsuario = id;
			printf("\nUSUARIO ALTERADO COM SUCESSO!\n\n\n");
		}
	}
	
	for(i = 0; i < *qtdUsuario; i++){
		fprintf(arqNovo, "%d|%s|%s|%s\n", usuarios[i].idUsuario, usuarios[i].nomeUsuario, usuarios[i].login, usuarios[i].senha);
	}
	
	fclose(arqNovo);
	fclose(arq);

	remove("usuarios.txt");
	rename("usuariosNovo.txt", "usuarios.txt");

	arq = fopen("usuarios.txt", "a+");

	
}

Usuario *procuraUsuario(Usuario usuarios[], int *qtdUsuarios, int idUsuario) {
    int i;

    for (i = 0; i < *qtdUsuarios; i++) {	
        if (usuarios[i].idUsuario == idUsuario) {
            return &usuarios[i];
        }
    }
    return NULL;
}

//**************************************POSTS**************************************
void insereDadosPost(Post posts[], Usuario usuarios[], Usuario validaUsuario, int *qtdPost, int *qtdUsuarios, int idPost){
	LIMPA_TELA
	printf("*** CADASTRO DE POSTAGENS ***\n\n");
	printf("Titulo da postagem: ");
	scanf(" %[^\n]", posts[*qtdPost].titulo);
	
	printf("\nEntre com o conteúdo da postagem:\n\n ");
	scanf(" %[^\n]", posts[*qtdPost].postagem);
	do {
		posts[*qtdPost].usuarios = &validaUsuario;
	}while(posts[*qtdPost].usuarios == NULL);
	
	posts[*qtdPost].idPost = idPost + 1;
	*qtdPost = *qtdPost + 1;

  printf("\nPostagem feita com sucesso!\n\n");
  
} 

void cadastraPosts(FILE *arq, Post posts[], int *qtdPost){
	
  	fprintf(arq, "%d|%s|%s|%d\n", posts[*qtdPost-1].idPost, posts[*qtdPost-1].titulo, posts[*qtdPost-1].postagem, posts[*qtdPost-1].usuarios->idUsuario);
		fflush(arq);
}

int carregaPostagens(FILE *arqPosts, Post posts[], Usuario usuarios[], int *qtdPosts, int *qtdUsuarios){
	int id, idUsuario;
  	while(!feof(arqPosts)){
    	fscanf(arqPosts, "%d|%[^|]|%[^|]|%d\n", &posts[*qtdPosts].idPost, posts[*qtdPosts].titulo, posts[*qtdPosts].postagem, &idUsuario);

			posts[*qtdPosts].usuarios = procuraUsuario(usuarios, qtdUsuarios, idUsuario);
    	(*qtdPosts)++;
  	}
  	id = posts[*qtdPosts - 1].idPost;
  	
  	return id;
}

void imprimePostagens(Post posts[], int *qtdPosts){
	int i;
	LIMPA_TELA
  printf("*** LISTA DE POSTAGENS DO SISTEMA: ***\n\n");
	for(i = 0; i < *qtdPosts; i++){
		printf("#%d - %s - %s\n\n", posts[i].idPost, posts[i].titulo, posts[i].usuarios->nomeUsuario);
	}
}

void deletaPostagem(FILE *arqPosts, Post posts[], Usuario usuarios[], int *qtdPosts, int *qtdUsuarios ){
	FILE *arqNovo; 
	int id, i = 0;
	Usuario *idUsuario;

	arqNovo = fopen("postsNovo.txt", "a+");
	assert(arqNovo != NULL);
	
	imprimePostagens(posts, qtdPosts);
	printf("Entre com o id a ser apagado: ");
	scanf("%d", &id);

	for(i = 0; i < *qtdPosts; i++){
		if(id != posts[i].idPost){
				fprintf(arqNovo, "%d|%s|%s|%d\n", posts[i].idPost, posts[i].titulo, posts[i].postagem, posts[i].usuarios->idUsuario);
		}
	}
	
	fclose(arqNovo);
	fclose(arqPosts);
	remove("posts.txt");
	rename("postsNovo.txt", "posts.txt");

	arqPosts = fopen("posts.txt", "a+");
	printf("\nPOSTAGEM DELETADA COM SUCESSO!\n\n\n");
}

void alteraPostagem(FILE *arqPost, Post posts[], Usuario usuarios[], Usuario validaUsuario, int *qtdPost, int *qtdUsuarios, int idPost){
	FILE *arqNovo; 
	int id, i = 0;
	Usuario *idUsuario;
	
	arqNovo = fopen("postsNovo.txt", "a+");
	assert(arqNovo != NULL);

	imprimePostagens(posts, qtdPost);

	printf("Entre com o id a ser atualizado: ");
	scanf("%d", &id);
	
	idUsuario = &validaUsuario;
	LIMPA_TELA
	printf("*** INSIRA OS NOVOS DADOS DA POSTAGEM ***");
	for(i = 0; i < *qtdPost; i++){
		if(id == posts[i].idPost && posts[i].usuarios->idUsuario == idUsuario->idUsuario){
			printf("\n\nNovo titulo da postagem: ");
			scanf(" %[^\n]", posts[i].titulo);
			
			printf("\nEntre com o novo conteúdo da postagem:\n\n ");
			scanf(" %[^\n]", posts[i].postagem);

			printf("\nPostagem Alterada com sucesso!\n\n\n");
		}
	}
	
	for(i = 0; i < *qtdPost; i++){
		fprintf(arqNovo, "%d|%s|%s|%d\n", posts[i].idPost, posts[i].titulo, posts[i].postagem, posts[i].usuarios->idUsuario);
	}
	
	fclose(arqNovo);
	fclose(arqPost);

	remove("posts.txt");
	rename("postsNovo.txt", "posts.txt");

	arqPost = fopen("posts.txt", "a+");
}

int listaPostagem(Post posts[], int *qtdPosts){
		int i, op;
		printf("LISTA DE POSTS DO BLOG: \n\n\n");
		for(i = 0; i < *qtdPosts; i++){
			printf("#%d - %s - %s\n\n", posts[i].idPost, posts[i].titulo, posts[i].usuarios->nomeUsuario);
		}
		printf("Entre com o ID da postagem que queira ler: ");
		scanf("%d", &op);
		return op;
}

int detalhaPostagem(Post posts[], Comentario comentarios[], int *qtdPosts, int *qtdComent, int op){
	int i, j, cont = 1;
	for(i = 0; i < *qtdPosts; i++){
		if(op == posts[i].idPost){
			LIMPA_TELA
			printf("		%s\n\n", posts[i].titulo);
			printf("			%s\n\n", posts[i].postagem);
			printf("Escrito por: %s\n\n", posts[i].usuarios->nomeUsuario);
			printf("COMENTARIOS:\n");

			for(j = 0; j < *qtdComent; j++){
				if(comentarios[j].post){
					if(comentarios[j].post -> idPost == posts[i].idPost){
						printf("\n	%d  -  %s   - Por %s\n",cont, comentarios[j].comentario, comentarios[j].usuarios ->nomeUsuario);
						cont++;
					} 
				}
				
			}
			printf("\n\n\n1 - Para entrar com comentario\n");
			printf("0 - Para voltar ao menu Inicial\n");
			scanf("%d", &op);			
		}	
		
	}
	return op;
}
Post *procuraPost(Post posts[], int *qtdposts, int idPost) {
    int i;

    for (i = 0; i < *qtdposts; i++) {	
        if (posts[i].idPost == idPost) {
            return &posts[i];
        }
    }
    return NULL;
}
//**************************************COMENTARIOS**************************************
void insereComentarios(Usuario usuarios, Post posts[], Comentario comentarios[], int *qtdComent, int *qtdPosts, int idPost, int idComent){
	printf("\n\nEntre com  o comentario: ");
	scanf(" %[^\n]", comentarios[*qtdComent].comentario);
	
	do {
		comentarios[*qtdComent].usuarios = &usuarios;
	}while(comentarios[*qtdComent].usuarios == NULL);
	do{
		comentarios[*qtdComent].post = procuraPost(posts, 
		 qtdPosts, idPost);
	}while(comentarios[*qtdComent].post == NULL);

	comentarios[*qtdComent].idComentarios = idComent + 1;
	*qtdComent = *qtdComent + 1;
	printf("\n\n Comentario cadastrado com sucesso");
	
} 

void cadastraComentarios(FILE *arq, Comentario Comentarios[], int *qtdComent){
	
  	fprintf(arq, "%d|%s|%d|%d\n", Comentarios[*qtdComent-1].idComentarios, Comentarios[*qtdComent-1].comentario, Comentarios[*qtdComent-1].usuarios->idUsuario, Comentarios[*qtdComent-1].post->idPost);
		fflush(arq);
}

int carregaComentarios(FILE *arqComent, Post posts[], Usuario usuarios[], Comentario comentarios[], int* qtdUsuarios,int *qtdPosts, int *qtdComent){
		int id, idUsuario, idPost;
  	while(!feof(arqComent)){
    	fscanf(arqComent, "%d|%[^|]|%d|%d\n", &comentarios[*qtdComent].idComentarios, comentarios[*qtdComent].comentario, &idUsuario, &idPost);
			comentarios[*qtdComent].usuarios = procuraUsuario(usuarios, qtdUsuarios, idUsuario);
			comentarios[*qtdComent].post = procuraPost(posts, qtdPosts, idPost);
    	(*qtdComent)++;
  	}
  	id = posts[*qtdComent - 1].idPost;
  	
  	return id;

}
//**************************************LOGIN**************************************
Usuario *login(Usuario usuarios[], int *qtdUsuarios){
    char login[50], senha[50];
    printf("-----------------------------------\n");
    printf("Entre com o login: ");
    scanf(" %[^\n]", login);
    printf("-----------------------------------\n");
    printf("Entre com a senha:");
    scanf(" %[^\n]", senha);
    printf("-----------------------------------\n");

		return validaLogin(login, senha, usuarios, qtdUsuarios);
}

Usuario *validaLogin(char *login, char *senha, Usuario usuarios[] ,int *qtdUsuarios){
		int i;
		for(i = 0; i < *qtdUsuarios; i++ ){
			if(strcmp(login, usuarios[i].login)== 0 && strcmp(senha, usuarios[i].senha)==0){
				LIMPA_TELA
				printf("\nLogado com Sucesso!\n\n");

				return &usuarios[i];	
			}
		}
		LIMPA_TELA
		printf("\nFalha ao logar\n!");
	return NULL;
}


//**************************************MENUS**************************************
int menuGeral(FILE *arqUsuario, FILE *arqPosts, FILE *arqComent, Post posts[], Usuario usuarios[], Comentario comentarios[], Usuario validaUsuario, int *qtdUsuarios, int *qtdPosts, int *qtdComent, int idUsuario, int idPost, int idComent) {
	int op, opc;
	printf("\n\n*** MENU GERAL***\n\n");
	printf("1. Ir para o Blog \n");
	printf("2. Menu dos Usuários\n");
  printf("3. Menu das Postagens\n");
	printf("\n");
	printf("0. Sair\n\n");
	printf("Digite sua opcao: ");
	scanf("%d", &op);
	LIMPA_TELA
	switch(op){
		case 1:
	    	opc = listaPostagem(posts, qtdPosts);
				op = detalhaPostagem(posts, comentarios, qtdPosts, qtdComent, opc);
				
				if(op == 0){
					LIMPA_TELA
					menuGeral(arqUsuario, arqPosts, arqComent, posts, usuarios, comentarios, validaUsuario, qtdUsuarios, qtdPosts, qtdComent, idUsuario, idPost, idComent);
				} else {
					insereComentarios(validaUsuario, posts, comentarios, qtdComent, qtdPosts, opc, idComent);
					cadastraComentarios(arqComent, comentarios, qtdComent);
					printf("\n\n\nPressione qualquer tecla para voltar ao menu\n");
					getchar();
					opc = getchar();
					LIMPA_TELA
					menuPostagem(arqUsuario, arqPosts, arqComent, posts, usuarios, comentarios, validaUsuario, qtdUsuarios, qtdPosts, qtdComent, idUsuario, idPost, idComent);
				}
				
	    	break;
	  	case 2:
					menuUsuario(arqUsuario, arqPosts, arqComent, posts, usuarios, comentarios, validaUsuario, qtdUsuarios, qtdPosts, qtdComent, idUsuario, idPost, idComent);
	      	break;
	  	case 3:
					menuPostagem(arqUsuario, arqPosts, arqComent, posts, usuarios, comentarios, validaUsuario, qtdUsuarios, qtdPosts, qtdComent, idUsuario, idPost, idComent);
	      	break;
			case 0:
					printf("Programa Finalizado com sucesso");
					return 0;
					break;
	  	default:
	  		printf("Opção invalida!");
	}
	return 0;
}

void menuPostagem(FILE *arqUsuario, FILE *arqPosts, FILE *arqComent, Post posts[], Usuario usuarios[], Comentario comentarios[], Usuario validaUsuario, int *qtdUsuarios, int *qtdPosts, int *qtdComent, int idUsuario, int idPost, int idComent) {
	int op;
	char opc;
	printf("\n\n*** MENU DAS POSTAGENS***\n\n");
	printf("1. Criar uma postagem\n");
	printf("2. Atualizar postagens\n");
	printf("3. Deletar uma postagem\n");
	printf("\n");
	printf("0. Voltar\n\n");
	printf("Digite sua opcao: ");
	scanf("%d", &op);
	switch(op){
		case 1:
			insereDadosPost(posts, usuarios, validaUsuario, qtdPosts, qtdUsuarios, idPost);
			cadastraPosts(arqPosts, posts, qtdPosts);
			printf("\n\n\nPressione qualquer tecla para voltar ao menu\n");
			getchar();
			opc = getchar();
			LIMPA_TELA
			menuPostagem(arqUsuario, arqPosts, arqComent, posts, usuarios, comentarios, validaUsuario, qtdUsuarios, qtdPosts, qtdComent, idUsuario, idPost, idComent);
			break;
	  case 2:
			alteraPostagem(arqPosts, posts, usuarios, validaUsuario, qtdPosts, qtdUsuarios, idPost);
			printf("\n\n\nPressione qualquer tecla para voltar ao menu\n");
			getchar();
			opc = getchar();
			LIMPA_TELA
			menuPostagem(arqUsuario, arqPosts, arqComent, posts, usuarios, comentarios, validaUsuario, qtdUsuarios, qtdPosts, qtdComent, idUsuario, idPost, idComent);
			break;
	  case 3:
			deletaPostagem(arqPosts, posts, usuarios, qtdPosts, qtdUsuarios);
			printf("\n\n\nPressione qualquer tecla para voltar ao menu\n");
			getchar();
			opc = getchar();
			LIMPA_TELA
			menuPostagem(arqUsuario, arqPosts, arqComent, posts, usuarios, comentarios, validaUsuario, qtdUsuarios, qtdPosts, qtdComent, idUsuario, idPost, idComent);
			break;
		case 0:
			LIMPA_TELA
			menuGeral(arqUsuario, arqPosts, arqComent, posts, usuarios, comentarios, validaUsuario, qtdUsuarios, qtdPosts, qtdComent, idUsuario, idPost, idComent);
			break;
		default:
	    	printf("Opção invalida!");
	}
}
		
void menuUsuario(FILE *arqUsuario, FILE *arqPosts, FILE *arqComent, Post posts[], Usuario usuarios[], Comentario comentarios[], Usuario validaUsuario, int *qtdUsuarios, int *qtdPosts, int *qtdComent, int idUsuario, int idPost, int idComent) {
	int op;
	char opc;
	printf("\n\n*** MENU DOS USUÁRIOS***\n\n");
	printf("1. Cadastro de Usuarios\n");
	printf("2. Consulta de Usuarios\n");
	printf("3. Atualização de Usuarios \n");
	printf("4. Deletar Usuario \n");
  	printf("\n");
	printf("0. Voltar\n\n");
	printf("Digite sua opcao: ");
	scanf("%d", &op);
	switch(op){
		case 1:
			insereDadosUsuario(usuarios, qtdUsuarios, idUsuario);
    	cadastraUsuarios(arqUsuario, usuarios, qtdUsuarios);
			printf("\n\n\nPressione qualquer tecla para voltar ao menu\n");
			getchar();
			opc = getchar();
			LIMPA_TELA
			menuUsuario(arqUsuario, arqPosts, arqComent, posts, usuarios, comentarios, validaUsuario, qtdUsuarios, qtdPosts, qtdComent, idUsuario, idPost, idComent);
	    	break;
	  case 2:
	    	imprimeUsuarios(usuarios, qtdUsuarios);
			printf("\n\n\nPressione qualquer tecla para voltar ao menu\n");
			getchar();
			opc = getchar();
			LIMPA_TELA
			menuUsuario(arqUsuario, arqPosts, arqComent, posts, usuarios, comentarios, validaUsuario, qtdUsuarios, qtdPosts, qtdComent, idUsuario, idPost, idComent);
	      break; 
	  case 3:	
	    alteraUsuario(arqUsuario, usuarios, qtdUsuarios);
			printf("\n\n\nPressione qualquer tecla para voltar ao menu\n");
			getchar();
			opc = getchar();
			LIMPA_TELA
			menuUsuario(arqUsuario, arqPosts, arqComent, posts, usuarios, comentarios, validaUsuario, qtdUsuarios, qtdPosts, qtdComent, idUsuario, idPost, idComent);
	      break;
	  case 4:
	      	deletaUsuario(arqUsuario, usuarios, qtdUsuarios);
			printf("\n\n\nPressione qualquer tecla para voltar ao menu\n");
			getchar();
			opc = getchar();
			LIMPA_TELA
			menuUsuario(arqUsuario, arqPosts, arqComent, posts, usuarios, comentarios, validaUsuario, qtdUsuarios, qtdPosts, qtdComent, idUsuario, idPost, idComent);
	      	break;
		case 0:
			LIMPA_TELA
			menuGeral(arqUsuario, arqPosts, arqComent, posts, usuarios, comentarios, validaUsuario, qtdUsuarios, qtdPosts, qtdComent, idUsuario, idPost, idComent);
			break;
	  default:
	    printf("Opção invalida!");
	}
}
