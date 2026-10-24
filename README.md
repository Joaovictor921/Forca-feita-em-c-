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
Letra correta: +5 pontos
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

# 🖥️ Como executar em um computador sem ferramentas instaladas

## Requisitos para jogar

- **Windows 10 de 64 bits (versão 1809 ou mais recente) ou Windows 11**.
- O arquivo `jogo_forca.exe` já compilado, ou o código-fonte `jogo_forca_multiplayer.cpp` para compilar seguindo as instruções abaixo.
- Para instalar o compilador pela primeira vez: conexão com a internet e o comando `winget` disponível no Windows.
- Para jogar em dois computadores: ambos devem estar conectados à mesma rede local (Wi-Fi ou cabo), e o firewall pode precisar liberar a porta TCP `54000`.

**Não é necessário baixar o Winsock separadamente.** A biblioteca `ws2_32` faz parte do Windows. O código usa C++11.

## Opção 1: apenas jogar, sem instalar um compilador

Se você recebeu um `jogo_forca.exe` compilado com as opções estáticas mostradas abaixo, basta copiar esse arquivo para o PC com Windows e executá-lo. Não é necessário instalar Dev-C++, MinGW ou MSYS2 nesse computador.

> **Atenção:** o pacote de código-fonte contém o arquivo `.cpp`, mas não inclui um executável `.exe` pronto. Para criar o executável, siga a Opção 2 em um PC com Windows. Depois, o `.exe` poderá ser copiado para os computadores em que o jogo será executado.

## Opção 2: baixar e instalar o compilador usando o CMD

Os comandos seguintes são para o **Prompt de Comando (CMD)** do Windows. Execute-os um por vez. É necessário ter internet durante a instalação.

### 1. Verificar se o WinGet está disponível

Abra o menu Iniciar, procure **Prompt de Comando**, abra-o e execute:

```cmd
winget --version
```

Se aparecer um número de versão, continue. Se o Windows disser que `winget` não é reconhecido, instale/atualize o **Instalador de Aplicativo (App Installer)** pela Microsoft Store e tente novamente. Como alternativa, baixe o instalador oficial em [msys2.org](https://www.msys2.org/).

### 2. Baixar o MSYS2 pelo CMD

```cmd
winget install --id MSYS2.MSYS2 -e --source winget --accept-source-agreements --accept-package-agreements
```

Quando o instalador abrir, mantenha o caminho padrão `C:\msys64` e conclua a instalação. Aguarde o instalador terminar antes de executar os próximos comandos.

### 3. Atualizar os pacotes do MSYS2

No mesmo CMD, execute:

```cmd
C:\msys64\usr\bin\bash.exe -lc "pacman -Syu --noconfirm"
```

Se o processo informar que é necessário fechar/reabrir o terminal ou reiniciar a atualização, execute o mesmo comando novamente até que não haja atualizações pendentes.

### 4. Instalar o compilador C++

```cmd
C:\msys64\usr\bin\bash.exe -lc "pacman -S --needed --noconfirm mingw-w64-ucrt-x86_64-gcc"
```

Confirme que o compilador foi instalado:

```cmd
C:\msys64\ucrt64\bin\g++.exe --version
```

Esses passos instalam o GCC/G++ por meio do gerenciador de pacotes oficial do MSYS2. Consulte também as instruções do [MSYS2](https://www.msys2.org/) e do projeto [mingw-w64](https://www.mingw-w64.org/getting-started/msys2/).

### 5. Compilar o jogo

Extraia os arquivos do projeto para uma pasta. O arquivo `jogo_forca_multiplayer.cpp` precisa estar na pasta em que o CMD está aberto.

Uma forma fácil de abrir o CMD na pasta correta:

1. Abra a pasta do projeto no Explorador de Arquivos.
2. Clique na barra de endereço, digite `cmd` e pressione **Enter**.
3. Na janela que abrir, execute:

```cmd
C:\msys64\ucrt64\bin\g++.exe jogo_forca_multiplayer.cpp -std=c++11 -O2 -static -static-libgcc -static-libstdc++ -o jogo_forca.exe -lws2_32
```

As opções estáticas incluem as bibliotecas de execução do C++ no executável, tornando-o mais adequado para copiar para outro PC sem instalar o compilador. As APIs de rede usadas pelo jogo continuam sendo fornecidas pelo próprio Windows.

Se a compilação terminar sem mensagens de erro, o arquivo `jogo_forca.exe` será criado na pasta. Para conferir:

```cmd
dir jogo_forca.exe
```

### 6. Iniciar o jogo

Na mesma pasta, execute:

```cmd
jogo_forca.exe
```

Siga o menu. No primeiro computador, escolha **1 - Criar servidor**. No segundo, escolha **2 - Entrar no servidor** e informe o IPv4 do computador servidor.

---

## Problemas comuns

- **`winget` não é reconhecido:** instale/atualize o App Installer pela Microsoft Store ou use o instalador oficial do MSYS2 em [msys2.org](https://www.msys2.org/).
- **`g++.exe` não encontrado:** confirme que o MSYS2 foi instalado em `C:\msys64` e que o pacote `mingw-w64-ucrt-x86_64-gcc` terminou de instalar.
- **O arquivo `.cpp` não foi encontrado:** abra o CMD na pasta onde está `jogo_forca_multiplayer.cpp` ou use `cd /d "CAMINHO_DA_PASTA"` para entrar nela.
- **O antivírus ou SmartScreen avisa sobre o `.exe`:** confira se você compilou o executável a partir do código-fonte do projeto e só execute arquivos de origem confiável.

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

Se o Windows bloquear a conexão, permita o jogo em **redes privadas** no alerta do Firewall. Como alternativa, no PC que hospeda o servidor, abra o CMD **como administrador** e execute:

```cmd
netsh advfirewall firewall add rule name="JogoForcaTCP54000" dir=in action=allow protocol=TCP localport=54000 profile=private
```

Use essa regra apenas em uma rede privada confiável. Para removê-la depois do teste:

```cmd
netsh advfirewall firewall delete rule name="JogoForcaTCP54000"
```

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

```text
JogoForcaMultiplayer_CORRIGIDO/
├── jogo_forca_multiplayer.cpp
├── compilar.bat
├── LEIA-ME.txt
├── REQUISITOS.md
├── ALTERACOES_CORRECAO.txt
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

## 🚀 Possíveis melhorias

### 🎮 Jogabilidade
- [ ] **Modo cooperativo**: todos contra a forca, com uma única forca compartilhada
- [ ] **Morte súbita**: a cada erro, o tempo da jogada diminui
- [ ] **Bots**: jogadores controlados pelo computador, para completar a sala
- [ ] **Votação para pular palavra** que ninguém conhece
- [ ] **Torneios** com chaveamento entre várias salas
- [ ] **Categorias e palavras personalizadas por sala**
- [ ] **Não repetir palavras** já usadas, mesmo entre sessões

### 🌐 Salas e rede
- [ ] **Descoberta automática de servidores** na rede local, sem digitar IP
- [ ] **Servidor público** na internet
- [ ] **Senha na sala**, além do código
- [ ] **Conexão criptografada**

### 🏆 Ranking e contas
- [ ] **Identificação mais segura** do jogador (PIN), já que hoje o ranking vale pelo nome
- [ ] **Ranking por período** (semanal e mensal)
- [ ] **Estatísticas por jogador**: taxa de acerto, letras mais usadas
- [ ] **Conquistas**: "venceu sem errar", "acertou na fase final" etc.

### 🎨 Interface
- [ ] **Janela gráfica** (SDL2 ou Win32), com forca desenhada e cliques
- [ ] **Versão web**, jogável no navegador
- [ ] **Temas de cores** e **modo acessível** (mais contraste, sem depender só de cor)

### 💬 Interação
- [ ] **Mensagem privada** entre jogadores (`/p nome texto`)
- [ ] **Comando `/regras`** mostrando a configuração atual da sala
- [ ] **Aviso sonoro** quando faltarem 5 segundos para acabar a vez

### 🎬 Extras
- [ ] **Replay** da partida

### 🛠️ Técnico
- [ ] **Build automático do `.exe`** no GitHub a cada release
- [ ] **Testes automáticos** no repositório
- [ ] **Código dividido em vários arquivos** (servidor, cliente, palavras)
- [ ] **Arquivo de configuração** com nome, último IP e preferências de som, animação e cor
- [ ] **Salvar e retomar partidas**

------------------------------------------------------------------------

## 🎮 Status do projeto

**Versão multiplayer funcional para Windows.**

O projeto foi desenvolvido para demonstrar, na prática, o uso conjunto
de **memória compartilhada, sincronização e comunicação por sockets
TCP/IP** em uma aplicação multiplayer.
