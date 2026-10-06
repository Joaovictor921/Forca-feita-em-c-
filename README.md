# 🎮 Jogo da Forca em C++

Projetos de **Jogo da Forca** desenvolvidos em C++, com uma versão
tradicional para terminal e uma versão **multiplayer em rede**,
permitindo que dois jogadores utilizem computadores ou terminais
diferentes.

O projeto foi desenvolvido como prática de lógica de programação,
estruturas de dados, entrada e saída no terminal e, na versão
multiplayer, comunicação entre computadores por sockets TCP.

## 👨‍💻 Autores

-   **João Victor Dalbem**
-   **Guilherme Duque**

------------------------------------------------------------------------

# 📚 Versões do projeto

  -----------------------------------------------------------------------
  Versão                              Descrição
  ----------------------------------- -----------------------------------
  🎯 **Normal**                       Jogo da Forca tradicional executado
                                      em um único terminal

  🌐 **Multiplayer**                  Jogo da Forca para dois jogadores
                                      usando comunicação em rede
  -----------------------------------------------------------------------

------------------------------------------------------------------------

# 🎯 Jogo da Forca Normal

A versão normal é baseada no jogo da forca tradicional.

## ✨ Recursos

-   Seleção aleatória de palavras
-   Palavra inicialmente escondida
-   Entrada de letras pelo terminal
-   Controle das letras já utilizadas
-   Até **8 tentativas**
-   Sistema de pontuação
-   Possibilidade de jogar novamente
-   Suporte ao modo com até **3 jogadores**
-   Lista de palavras relacionada a tecnologia, animais, frutas, países,
    profissões, cores e outros temas

## 🏆 Pontuação

A pontuação segue a lógica do projeto original:

-   ✅ Letra correta: **+3 pontos**
-   ❌ Letra incorreta: **-1 ponto**

## 🕹️ Como jogar

Compile o arquivo da versão normal e execute pelo terminal.

Exemplo:

``` bash
g++ jogo_da_forca.cpp -std=c++11 -o forca
```

No Windows, utilizando MinGW:

``` bash
g++ jogo_da_forca.cpp -std=c++11 -o forca.exe
```

Depois:

``` bash
./forca
```

No Windows:

``` bash
forca.exe
```

> O nome do arquivo pode variar conforme a organização do projeto.

------------------------------------------------------------------------

# 🌐 Jogo da Forca Multiplayer

A versão multiplayer transforma o jogo em uma partida entre **dois
terminais ou dois computadores**.

Um computador funciona como **servidor** e o outro como **cliente**.

``` text
                 🌐 REDE LOCAL
                      │
          ┌───────────┴───────────┐
          │                       │
     🖥️ PC 1                  🖥️ PC 2
     SERVIDOR                  CLIENTE
          │                       │
          └───────────┬───────────┘
                      │
                ESTADO DO JOGO
                      │
        ┌─────────────┼─────────────┐
        │             │             │
     Palavra       Pontuação      Turno
     oculta        compartilhada   atual
```

## ✨ Recursos

-   👥 Dois jogadores
-   🖥️ Dois computadores ou dois terminais
-   🌐 Comunicação por TCP
-   🔄 Estado da partida sincronizado
-   🔤 Uma letra por turno
-   🏆 Pontuação compartilhada
-   ❤️ Controle de tentativas
-   📝 Controle das letras utilizadas
-   🔒 Palavra não é exibida durante a partida
-   🏁 Resultado da partida ao final
-   💻 Compatibilidade com Windows/MinGW

## 🔄 Como funciona

### 1. Servidor

O primeiro jogador inicia o programa e escolhe:

``` text
1 - Criar servidor
```

O servidor aguarda a conexão do segundo jogador.

### 2. Cliente

O segundo jogador inicia o programa e escolhe:

``` text
2 - Entrar no servidor
```

Depois informa o endereço IP do computador que está executando o
servidor.

Exemplo:

``` text
IP do servidor: 10.7.11.22
```

### 3. Partida

Depois da conexão, os dois jogadores recebem o mesmo estado da partida.

Cada jogador joga **uma letra por turno**.

Exemplo:

``` text
=============================================
             JOGO DA FORCA ONLINE
=============================================

Palavra: _ _ _ _ _ _ _ _

Letras usadas: A E R

Tentativas restantes: 6

---------------- PLACAR ----------------
Time 1: 6 pontos
Time 2: 3 pontos

Turno: Time 2
Digite uma letra:
```

Quando o jogador acerta:

``` text
+3 pontos
```

Quando erra:

``` text
-1 ponto
```

Uma tentativa é perdida quando a letra escolhida não pertence à palavra.

------------------------------------------------------------------------

# 🔌 Testando no mesmo computador

É possível testar o multiplayer sem dois computadores.

Abra **dois terminais**.

### Terminal 1

Inicie o programa e escolha:

``` text
1 - Criar servidor
```

### Terminal 2

Inicie outra cópia do programa e escolha:

``` text
2 - Entrar no servidor
```

Utilize:

``` text
127.0.0.1
```

como endereço do servidor.

`127.0.0.1` representa o próprio computador e é útil para testar a
comunicação antes de utilizar uma rede real.

------------------------------------------------------------------------

# 🖥️ Jogando em dois computadores

Os dois computadores precisam conseguir se comunicar pela mesma rede
local.

No computador que executa o servidor, descubra o IPv4 com:

``` cmd
ipconfig
```

Procure algo semelhante a:

``` text
Endereço IPv4 . . . . . . . . . . : 10.7.11.22
```

No segundo computador, informe esse endereço quando o jogo solicitar o
IP do servidor.

Exemplo:

``` text
10.7.11.22
```

> Se o Windows Firewall solicitar permissão para o programa, permita o
> acesso à rede privada para que os computadores possam estabelecer a
> conexão.

------------------------------------------------------------------------

# ⚙️ Tecnologias utilizadas

## Versão normal

-   C++
-   Terminal
-   `stdio.h`
-   `string.h`
-   `ctype.h`
-   `stdlib.h`
-   `time.h`
-   `locale.h`

## Versão multiplayer

Além dos recursos básicos de C++, utiliza:

-   C++
-   C++11
-   TCP/IP
-   Windows Sockets (Winsock)
-   `winsock2.h`
-   `ws2tcpip.h`
-   Comunicação cliente/servidor

No Windows, a biblioteca de sockets utilizada é:

``` text
ws2_32
```

------------------------------------------------------------------------

# 🧠 Conceitos praticados

O projeto foi desenvolvido para praticar conceitos importantes de
programação:

-   Variáveis
-   Vetores
-   Strings
-   Estruturas (`struct`)
-   Funções
-   Ponteiros
-   Loops
-   Condicionais
-   Geração de números aleatórios
-   Manipulação de caracteres
-   Controle de estado do jogo
-   Entrada e saída pelo terminal
-   Comunicação em rede
-   Arquitetura cliente/servidor
-   Sincronização de informações entre jogadores

------------------------------------------------------------------------

# 📁 Estrutura sugerida do repositório

``` text
Jogo-da-Forca/
│
├── normal/
│   └── jogo_da_forca.cpp
│
├── multiplayer/
│   ├── jogo_forca_multiplayer.cpp
│   └── JogoForca.dev
│
└── README.md
```

------------------------------------------------------------------------

# 🚀 Possíveis melhorias

Algumas ideias para futuras versões:

-   [ ] Interface gráfica
-   [ ] Sistema de categorias
-   [ ] Banco de palavras maior
-   [ ] Sistema de ranking
-   [ ] Salvar pontuações
-   [ ] Mais jogadores online
-   [ ] Criar salas privadas
-   [ ] Código de sala para conexão
-   [ ] Chat entre jogadores
-   [ ] Efeitos sonoros
-   [ ] Animação da forca
-   [ ] Reconexão automática
-   [ ] Versão multiplataforma
-   [ ] Interface web

------------------------------------------------------------------------

# 📜 Objetivo acadêmico

O projeto foi desenvolvido como uma aplicação prática de conceitos de
programação em C++, evoluindo de uma implementação tradicional do jogo
da forca para uma arquitetura cliente/servidor capaz de compartilhar o
estado de uma partida entre dois jogadores.

A versão multiplayer amplia o projeto original ao introduzir conceitos
de **redes de computadores e comunicação por sockets**, mantendo a
mecânica principal do jogo.

------------------------------------------------------------------------

## ⭐ Sobre o projeto

Este repositório reúne as duas versões do jogo:

**🎯 Normal:** simples, direto e executado localmente.

**🌐 Multiplayer:** dois jogadores, dois terminais e uma única partida
compartilhada pela rede.

Divirta-se e bom jogo! 🎮
