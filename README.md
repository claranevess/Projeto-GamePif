# Rapid Ball
Projeto do segundo período de Ciência da Computação na Cesar School da matéria de Programação Imperativa Funcional.

## Requisitos
- Este jogo funciona com os sistemas operacionais a seguir:
   - Linux based (Ubuntu, etc)
   - MacOS
- É necessário ter o GCC instalado.

## Passos para jogar o Rapid Ball

Primeiro é necessário verificar se as bibliotecas e o arquivo main.c que estão presentes no GitHub estão no mesmo arquivo diretório da sua máquina e rodar a seguinte linha de comando:
```
gcc -Wall -Iinclude -c src/main.c -o src/main.o
gcc -Wall -Iinclude -c src/game.c -o src/game.o
gcc -Wall -Iinclude -c src/player.c -o src/player.o
gcc -Wall -Iinclude -c src/platform.c -o src/platform.o
gcc -Wall -Iinclude -c src/sprint.c -o src/sprint.o
gcc -Wall -Iinclude -c src/life.c -o src/life.o
gcc -Wall -Iinclude -c src/score.c -o src/score.o
gcc -Wall -Iinclude -c src/screen.c -o src/screen.o
gcc -Wall -Iinclude -c src/keyboard.c -o src/keyboard.o
gcc -Wall -Iinclude -c src/timer.c -o src/timer.o
```
Logo em seguida, digitar essa segunda linha:
```
gcc src/*.o -o rapidball
```
para, finalmente, executar o jogo: 
````
./rapidball
````

## Iniciando o Jogo
1 - Aperte em enter para iniciar
## Objetivos do Jogo
- Ficar Vivo: O jogador deve evitar colidir com o topo da tela para permanecer vivo. Cada colisão com o topo resulta na perda de uma vida.
- Vidas: O jogador começa com 3 vidas. Quando todas as vidas são perdidas, o jogo termina.
- Pontuação: O jogador ganha pontos colidindo com diferentes blocos que aparecem no jogo. O score é exibido no canto superior direito da tela.
