# Rapid Ball
Projeto do segundo período de Ciência da Computação na Cesar School da matéria de Programação Imperativa Funcional.

## Requisitos
- Este jogo funciona com o sistema operacional a seguir:
   - Linux based (Ubuntu, etc)
   - MacOS
- É necessário ter o GCC instalado.

## Passos para jogar o Rapid Ball

Primeiro é necessário verificar que as bibliotecas e o arquivo main.c que estão presentes no GitHub estão no mesmo arquivo diretório da sua máquina e rodar a seguinte linha de comando:
```
gcc -o rapidball main.c screen.c keyboard.c timer.c -lm

```
Logo em seguida, digitar essa segunda linha:
```
./rapidball

```
To use this library to create your own apps, simply add source and header files to your project and compile it together with your own code, 
replacing the main.c file to your own.

## Iniciando o Jogo
1 - Aperte em enter para iniciar
## Objetivos
- Ficar Vivo: O jogador deve evitar colidir com o topo da tela para permanecer vivo. Cada colisão com o topo resulta na perda de uma vida.
- Vidas: O jogador começa com 3 vidas. Quando todas as vidas são perdidas, o jogo termina.
- Pontuação: O jogador ganha pontos resgatando e colidindo com diferentes blocos que aparecem no jogo. O score é exibido no canto superior direito da tela.
