# 🎮 Jogo da Forca Multiplayer em C++

Projeto acadêmico de **Jogo da Forca Multiplayer** desenvolvido em C++,
com suporte para dois jogadores, comunicação em rede e uso de memória
compartilhada entre processos no Windows.

O projeto evolui a versão tradicional do Jogo da Forca para uma
arquitetura **cliente/servidor**, mantendo o estado da partida
sincronizado entre os jogadores.

## 👨‍💻 Autores

-   **João Victor Dalbem**
-   **Guilherme Duque**

------------------------------------------------------------------------

# 📌 Objetivo do projeto

O objetivo é demonstrar, de forma prática, dois conceitos principais:

1.  **Memória compartilhada entre processos**
2.  **Comunicação entre processos**

Para isso, o projeto utiliza uma abordagem híbrida:

``` text
                     JOGO DA FORCA
                           │
             ┌─────────────┴─────────────┐
             │                           │
      MEMÓRIA COMPARTILHADA         COMUNICAÇÃO TCP
             │                           │
      Windows / Processos            Winsock / Rede
             │                           │
             └─────────────┬─────────────┘
                           │
                    SERVIDOR + CLIENTE
```

------------------------------------------------------------------------

# 🧠 Memória compartilhada

No Windows, o projeto utiliza uma região nomeada de memória
compartilhada através de:

``` cpp
CreateFileMappingA()
MapViewOfFile()
OpenFileMappingA()
```

O acesso à memória é protegido por um mutex nomeado utilizando:

``` cpp
CreateMutexA()
OpenMutexA()
WaitForSingleObject()
ReleaseMutex()
```

A memória compartilhada contém o **estado público da partida**, como:

-   Palavra mascarada
-   Letras utilizadas
-   Turno atual
-   Pontuação dos jogadores
-   Quantidade de erros
-   Nomes dos jogadores
-   Estado final da partida

### Mesmo computador

Quando os dois processos são executados no mesmo PC, o servidor cria a
região de memória e o cliente pode abrir a mesma região nomeada.

``` text
┌──────────────────────┐
│ Processo Servidor    │
│                      │
│  Memória Compartilhada
└──────────┬───────────┘
           │
           │ mesma região
           │
┌──────────▼───────────┐
│ Processo Cliente     │
└──────────────────────┘
```

### Dois computadores

Uma região de memória física não pode ser compartilhada diretamente
entre dois computadores diferentes.

Por isso, quando a partida ocorre em dois PCs:

``` text
PC 1                          PC 2
Servidor                      Cliente
   │                             │
   │ Memória local               │ Memória local
   │                             │
   └────────── TCP/IP ───────────┘
            sincronização
```

Cada computador mantém sua memória local e o estado entre as máquinas é
sincronizado por TCP/IP.

------------------------------------------------------------------------

# 🌐 Comunicação entre processos

A comunicação cliente/servidor utiliza **TCP/IP com Winsock**.

Principais funções utilizadas:

``` cpp
socket()
bind()
listen()
accept()
connect()
send()
recv()
```

O modelo é:

``` text
              TCP/IP
                │
       ┌────────┴────────┐
       │                 │
   🖥️ PC 1             🖥️ PC 2
   SERVIDOR             CLIENTE
       │                 │
       └───────┬─────────┘
               │
          Estado do jogo
```

O servidor é responsável por manter o estado oficial da partida e
processar as jogadas.

------------------------------------------------------------------------

# 🎮 Regras do jogo

## 👥 Jogadores

A versão multiplayer possui dois jogadores:

-   **Time 1:** servidor
-   **Time 2:** cliente

Cada jogador realiza uma jogada por turno.

------------------------------------------------------------------------

## 🔤 Letras

O jogador informa uma letra por vez.

Letras maiúsculas são automaticamente convertidas para minúsculas:

``` text
A → a
B → b
C → c
```

Assim:

``` text
A = a
```

Uma letra que já foi utilizada não pode ser escolhida novamente e **não
consome o turno**.

------------------------------------------------------------------------

## 🏆 Pontuação

### Acerto normal

``` text
+3 pontos
```

### Erro

``` text
-1 ponto
+1 erro
```

Na fase final:

``` text
Letra correta: +3 pontos
Palavra inteira correta: +5 pontos
```

------------------------------------------------------------------------

# 🔥 Fase final

Quando restam **2 letras diferentes ou menos** para descobrir, começa a
fase final.

O jogador da vez recebe duas opções:

``` text
1 - Chutar a palavra inteira
2 - Chutar uma letra
```

### Palavra inteira

Se acertar:

``` text
+5 pontos
```

A rodada termina imediatamente.

Se errar:

``` text
-1 ponto
+1 erro
```

### Letra

Se acertar:

``` text
+3 pontos
```

Se errar:

``` text
-1 ponto
+1 erro
```

------------------------------------------------------------------------

# ☠️ Sistema de erros

Cada time possui seu **próprio contador de erros** e seu próprio desenho
de personagem.

``` text
TIME 1
Erros: 3/8

TIME 2
Erros: 5/8
```

O contador não é compartilhado como uma única quantidade global.

O desenho do personagem evolui conforme os erros aumentam.

Cada time possui um desenho diferente para facilitar a identificação
visual durante a partida.

------------------------------------------------------------------------

# 🔒 Palavra secreta

Durante a partida, a palavra verdadeira permanece escondida.

O estado enviado aos jogadores contém apenas a palavra mascarada:

``` text
_ _ _ _ _ _ _
```

Exemplo após alguns acertos:

``` text
p r _ g r a m a
```

A palavra completa é revelada apenas quando a rodada termina.

------------------------------------------------------------------------

# 🔄 Jogar novamente

Depois que a rodada termina, os jogadores recebem a opção:

``` text
Deseja jogar novamente?

1 - Sim
2 - Nao
```

A nova rodada só começa quando os dois jogadores concordarem.

A pontuação acumulada permanece entre as rodadas e uma nova palavra é
sorteada.

------------------------------------------------------------------------

# 🖥️ Como executar

## Requisitos

-   Windows
-   Dev-C++ ou MinGW
-   C++11
-   Winsock
-   Biblioteca `ws2_32`

------------------------------------------------------------------------

## ⚙️ Compilação

Com MinGW:

``` bash
g++ jogo_forca_multiplayer.cpp -std=c++11 -O2 -o forca.exe -lws2_32
```

No Dev-C++, o projeto `.dev` já pode ser usado para facilitar a
configuração.

------------------------------------------------------------------------

# 🌐 Como jogar em dois computadores

## PC 1

Abra o programa e escolha:

``` text
1 - Criar servidor
```

Digite o nome do Time 1.

O servidor ficará aguardando a conexão.

## PC 2

Abra o programa e escolha:

``` text
2 - Entrar no servidor
```

Digite o nome do Time 2.

Depois informe o endereço IPv4 do PC 1.

Para descobrir o IP do servidor:

``` cmd
ipconfig
```

Exemplo:

``` text
Endereço IPv4: 10.7.11.22
```

No PC 2:

``` text
IP do servidor: 10.7.11.22
```

A porta utilizada pelo jogo é:

``` text
54000
```

### ⚠️ Firewall

Caso o Windows bloqueie a conexão, permita o programa na rede privada ou
libere a porta TCP `54000` no firewall.

------------------------------------------------------------------------

# 🧪 Teste no mesmo computador

Também é possível testar o multiplayer sem dois PCs.

Abra dois terminais.

### Terminal 1

``` text
1 - Criar servidor
```

### Terminal 2

``` text
2 - Entrar no servidor
```

Use:

``` text
127.0.0.1
```

como endereço do servidor.

------------------------------------------------------------------------

# 📁 Estrutura do projeto

``` text
JogoDaForca/
│
├── jogo_forca_multiplayer.cpp
├── JogoForca.dev
├── compilar.bat
├── LEIA-ME.txt
├── REQUISITOS.md
└── README.md
```

------------------------------------------------------------------------

# 🧩 Arquitetura

## Servidor

O servidor:

1.  Inicializa o Winsock
2.  Cria o socket
3.  Abre a porta `54000`
4.  Aguarda a conexão do cliente
5.  Recebe o nome do Time 2
6.  Sorteia a palavra
7.  Mantém o estado oficial da partida
8.  Processa as jogadas
9.  Atualiza a memória compartilhada
10. Envia o estado ao cliente
11. Controla o encerramento e o replay

## Cliente

O cliente:

1.  Inicializa o Winsock
2.  Cria o socket
3.  Informa o IP do servidor
4.  Conecta ao servidor
5.  Envia o nome do Time 2
6.  Recebe o estado da partida
7.  Atualiza a memória local
8.  Mostra a palavra mascarada
9.  Envia a jogada quando for seu turno
10. Aguarda a atualização do servidor

------------------------------------------------------------------------

# 📚 Conceitos utilizados

Este projeto trabalha conceitos de:

-   C++
-   Structs
-   Strings
-   Vetores
-   Funções
-   Condicionais
-   Loops
-   Aleatoriedade
-   Tratamento de entrada
-   Sockets
-   TCP/IP
-   Winsock
-   Cliente/servidor
-   Comunicação entre processos
-   Memória compartilhada
-   Mutex
-   Sincronização de estado

------------------------------------------------------------------------

# 📈 Evolução do projeto

O projeto começou com uma versão tradicional do Jogo da Forca executada
localmente.

A evolução foi:

``` text
🎯 Jogo da Forca Normal
          ↓
👥 Sistema de jogadores
          ↓
🏆 Sistema de pontuação
          ↓
🔤 Controle de letras
          ↓
🌐 Comunicação cliente/servidor
          ↓
🧠 Memória compartilhada
          ↓
🎮 Jogo da Forca Multiplayer
```

------------------------------------------------------------------------

# 🎓 Objetivo acadêmico

O projeto foi desenvolvido como uma aplicação prática de conceitos de
**programação em C++**, **comunicação entre processos** e **memória
compartilhada**.

A versão multiplayer foi estruturada para demonstrar:

``` text
MEMÓRIA COMPARTILHADA
          +
COMUNICAÇÃO TCP/IP
          =
PARTIDA MULTIPLAYER
```

A implementação utiliza memória compartilhada real entre processos
quando os processos estão no mesmo computador e utiliza TCP/IP para
sincronizar os estados quando os jogadores estão em computadores
diferentes.

------------------------------------------------------------------------

# 🚀 Possíveis melhorias

-   [ ] Sistema de salas
-   [ ] Código de sala
-   [ ] Mais jogadores
-   [ ] Ranking
-   [ ] Chat
-   [ ] Categorias
-   [ ] Banco maior de palavras
-   [ ] Interface gráfica
-   [ ] Sons
-   [ ] Animações
-   [ ] Reconexão automática
-   [ ] Histórico de partidas

------------------------------------------------------------------------

## 🎮 Status do projeto

**Versão multiplayer funcional para Windows.**

O projeto foi desenvolvido para demonstrar, na prática, o uso conjunto
de **memória compartilhada, sincronização e comunicação por sockets
TCP/IP** em uma aplicação multiplayer.
