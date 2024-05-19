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
gcc -o rapidball main.c screen.c keyboard.c timer.c -lm

```
Logo em seguida, digitar essa segunda linha:
```
./rapidball

```

## Iniciando o Jogo
1 - Aperte em enter para iniciar
## Objetivos do Jogo
- Ficar Vivo: O jogador deve evitar colidir com o topo da tela para permanecer vivo. Cada colisão com o topo resulta na perda de uma vida.
- Vidas: O jogador começa com 3 vidas. Quando todas as vidas são perdidas, o jogo termina.
- Pontuação: O jogador ganha pontos colidindo com diferentes blocos que aparecem no jogo. O score é exibido no canto superior direito da tela.
