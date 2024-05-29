# Rapid Ball 🔴
Projeto do segundo período de Ciência da Computação na Cesar School da matéria de Programação Imperativa Funcional.

## Requisitos
- Este jogo funciona com os sistemas operacionais a seguir:
   - Linux based (Ubuntu, etc)
   - MacOS
- É necessário ter o GCC instalado.

## Passos para jogar o Rapid Ball

Primeiro é necessário verificar se as bibliotecas e o arquivo main.c que estão presentes no GitHub estão no mesmo arquivo diretório da sua máquina e rodar a seguinte linha de comando:
```
make
```
Logo em seguida, digitar essa segunda linha para executar "jogo.exe":
```
make run
```
## Iniciando o Jogo:

1 - Ao iniciar o jogo o player digita o seu user;

2 - O player se depara com a tela de menu que contém as seguintes opções:
- teclar ENTER para iniciar a partida;
- teclar "T" para exibir a tela de "top scores", onde é exibido as 10 melhores pontuações;
- teclar "ESC" para parar de executar o jogo;
- teclar "A" para movimentar o player para esquerda e "D" para direita;
  
## Objetivos do Jogo

Ao iniciar a partida o player que é representado por "🔴" está localizado no chão enquanto plataformas aleatórias e flutuantes vão em direção ao topo da tela. 
Para aumentar sua pontuação o jogador sobe nas plataformas e tenta pegar o máximo de moedas "🪙" que conseguir. A cada 50 moedas a velocidade com que as plataformas
e os sprints se movem são aumentados, assim dificultando a jogabilidade proporcionalmente. Caso o jogador colida com o topo da tela,ele perde uma vida "❤️" 
(inicialmente ele obtém três vidas). Ao perder todas as vidas a tela de "Game Over" é mostrada e em seguida ele volta ao menu. 
Caso sua pontuação seja uma das 10 melhores, será exibida na tela de Top Scores, ao lado de seu user digitado inicialmente.

- Screncast do Jogo Finalizado:

https://github.com/paulo-rago/Projeto-GamePif/assets/149490954/72cf89d8-ae0e-41d9-9354-eec9908c2565



