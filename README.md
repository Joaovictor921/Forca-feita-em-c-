# 🎮 Jogo da Forca Multiplayer em C++

Jogo da forca em rede, no terminal, para **2 a 6 jogadores**: salas com código, ranking global, chat,
equipes, espectadores, partidas por rodadas e reconexão. Começou como uma forca local em C++ e virou
um projeto acadêmico de **comunicação entre processos** (sockets TCP), **memória compartilhada** e
**concorrência** (threads e mutex).

**Autores:** João Victor Dalbem e Guilherme Duque

[![Releases](https://img.shields.io/github/v/release/Joaovictor921/Forca-feita-em-c-?label=release)](https://github.com/Joaovictor921/Forca-feita-em-c-/releases)
![C++11](https://img.shields.io/badge/C%2B%2B-11-blue)
![Windows | Linux](https://img.shields.io/badge/plataforma-Windows%20%7C%20Linux-lightgrey)

---

## 📥 Baixar e jogar

As versões prontas ficam na página de **[Releases](https://github.com/Joaovictor921/Forca-feita-em-c-/releases)**.

| Quero... | Baixe |
|---|---|
| Só jogar (Windows) | o `forca.exe` da release **Multplayer V2.2** ou **Forca em C Trabalho Maurilio**. Dê duplo clique, não precisa instalar nada. |
| O código-fonte para compilar | o `.rar`/`.zip` da mesma release. Dentro dele, o `JOGAR.bat` compila e abre o jogo. |

> Todos os jogadores precisam usar **a mesma versão** (o protocolo muda entre as versões).

### Como jogar uma partida

1. **Uma pessoa hospeda:** abre o jogo e escolhe `1 - Hospedar`. Ela vira o servidor e também joga.
   Para só hospedar, sem jogar, use `3 - Servidor dedicado` ou `forca --servidor`.
2. **Os outros conectam:** `2 - Conectar` e digitam o IP de quem hospedou.
   - No mesmo PC, para testar: `127.0.0.1`.
   - Na mesma rede (Wi-Fi ou cabo): o IPv4 de quem hospeda (veja com `ipconfig`).
   - Em redes diferentes: é preciso uma VPN de jogos (ex.: Radmin VPN) ou abrir a porta no roteador.
3. **No lobby:** crie uma sala ou entre com o código de 4 letras (ex.: `K7QD`). Também dá para listar as salas públicas e ver o ranking.
4. **O dono da sala** ajusta a configuração e digita `/iniciar`.

A porta usada é a **TCP 54000**. Na primeira vez que hospedar, o Windows pergunta sobre o Firewall: clique em **Permitir acesso**.

---

## ✨ Recursos (v2.2 e Trabalho Maurilio)

- 🚪 **Salas com código**, públicas ou privadas, de 2 a 6 jogadores. O servidor aguenta várias salas ao mesmo tempo.
- 🏆 **Ranking global** salvo no servidor (`ranking.txt`).
- 💬 **Chat** na sala, reações rápidas (`/gg`, `/boa`, `/rs`...) e histórico.
- 🎯 **Chute da palavra** a qualquer momento da sua vez.
- ⏱️ **Tempo por jogada**: quem estoura perde a vez; 3 vezes seguidas e está fora da rodada.
- 🥇 **Partidas por rodadas**: "melhor de N" ou "primeiro a N pontos", com tela de campeão.
- 🎭 **Palavra do jogador**: um mestre escolhe a palavra em segredo e ganha +10 se ninguém acertar.
- 📊 **Dificuldade** por tamanho da palavra: fácil (até 6), médio (7 a 9), difícil (10+).
- 👥 **Equipes** 2x2 e 3x3, com pontos somados.
- 👀 **Espectadores** (até 8) assistem e conversam no chat.
- 🛠️ **Controle da sala**: o dono expulsa jogadores e passa o comando.
- 🔄 **Reconexão**: quem cai tem 2 minutos para voltar sem perder pontos nem lugar.
- 🔤 **13 categorias e mais de 650 palavras com acento** (pêssego, São Paulo), além do arquivo opcional `palavras.txt`.
- 🎨 Interface colorida em modo texto, com sons e animações.

---

## 📏 Regras e pontuação

| Jogada | Resultado |
|---|---|
| Letra certa | **+3** pontos (**+5** na fase final) |
| Letra errada | **−1** ponto e +1 erro |
| Palavra inteira certa | **+5**, mais **+2** por letra diferente que ainda faltava além das 2 últimas |
| Palavra inteira errada | **−3** e +2 erros (na fase final: −1 e +1 erro) |
| Chute com tamanho errado | nada é descontado |

- A **fase final** começa quando restam 2 letras diferentes ou menos.
- Cada jogador tem **sua própria forca**. Com **8 erros** ele está fora da rodada.
- A rodada acaba quando alguém completa a palavra, acerta o chute ou todos são eliminados.
- Letras com acento valem pela letra base: digitar `a` revela `á`, `ã`, `â`...
- Os pontos acumulam entre as rodadas e entram no ranking global.

### Comandos dentro da sala

| Comando | O que faz |
|---|---|
| `/iniciar` | (dono) começa a rodada ou uma nova partida |
| `/config` | (dono) mostra a configuração; para mudar: `/tempo N\|off`, `/dif facil\|medio\|dificil\|todas`, `/partida livre\|melhor N\|pontos N`, `/equipes on\|off`, `/modo sorteada\|mestre`, `/max N`, `/cat X`, `/publica`, `/privada` |
| `/time A` / `/time B` | troca de time (modo equipes) |
| `/assistir` / `/jogar` | alterna entre espectador e jogador (fora da rodada) |
| `/expulsar nome` / `/dono nome` | (dono) expulsa e bane da sala / passa o comando |
| `/c texto` | chat durante a sua vez (fora dela é só digitar) |
| `/gg` `/boa` `/ops` `/rs` `/uau` `/f` `/vamos` `/calma` `/sorte` `/ufa` | reações rápidas (`/reacoes` lista todas) |
| `/historico`, `/chatlinhas N`, `/ranking`, `/sair`, `/ajuda` | outros comandos |
| `/som`, `/anim`, `/cor`, `/acentos` | liga e desliga efeitos (use `/acentos` se aparecerem símbolos estranhos) |

---

## 🛠️ Compilar

**Windows (mais fácil):** extraia o pacote da release e dê duplo clique em `JOGAR.bat`.
Ele procura o compilador (inclusive o do Dev-C++), instala o MinGW pelo `winget` se faltar, compila e abre o jogo.
No Dev-C++, abra `JogoForca.dev` e aperte F11.

**Windows (manual, MinGW-w64):**

```bash
g++ jogo_forca_multiplayer.cpp -std=c++11 -O2 -static -static-libgcc -static-libstdc++ -o forca.exe -lws2_32
```

**Linux / macOS:**

```bash
g++ jogo_forca_multiplayer.cpp -std=c++11 -O2 -o forca
```

> Na versão **Trabalho Maurilio** (servidor com threads), acrescente **`-pthread`** aos comandos acima.
> O `JOGAR.bat` e o `JogoForca.dev` dessa versão já incluem a flag.

Opções de linha de comando: `forca --servidor`, `--porta 55000`, `--sem-som`, `--sem-anim`, `--sem-cor`, `--sem-acento`.

---

## 🧩 Como funciona

```text
   Jogador 1         Jogador 2   ...   Jogador 6
  (cliente TCP)     (cliente TCP)     (cliente TCP)
        \                 |                 /
         \                |                /
          +------- SERVIDOR (porta 54000) -------+
          |  salas, vez, pontos, ranking.txt     |
          |  estado oficial da partida           |
          +--------------------------------------+
```

- **Cliente/servidor em TCP** (Winsock no Windows, sockets POSIX no Linux). O servidor guarda o estado
  oficial: só ele sorteia a palavra, valida as jogadas e calcula os pontos. Os clientes recebem apenas
  a **palavra mascarada**, que é revelada no fim da rodada.
- **Protocolo de texto**, uma mensagem por linha com campos separados por `|`. Exemplos:
  `HELLO|nome|versao`, `JOIN|K7QD`, `LETTER|a`, `WORD|palavra`, e do servidor:
  `STATE|...`, `EVENT|hit|...`, `CHATMSG|nome|texto`, `RANK|pos|nome|pontos|...`.
- **v2.2:** o servidor atende todas as conexões num laço único com `select()`.
- **Trabalho Maurilio:** servidor **concorrente com pthreads**: uma thread por jogador, uma para aceitar
  conexões e uma de relógio (tempo por jogada, ping e quedas). O estado compartilhado (salas, vez,
  pontos, ranking) é protegido por `pthread_mutex_t`. Testado com 4 e 6 jogadores simultâneos e
  verificado com o ThreadSanitizer, sem corridas de dados.
- **Multiplayer v1.0:** a primeira versão em rede usava **memória compartilhada nomeada do Windows**
  (`CreateFileMappingA`, `MapViewOfFile`) protegida por **mutex nomeado** (`CreateMutexA`,
  `WaitForSingleObject`) quando os dois processos rodavam no mesmo PC, e TCP entre PCs diferentes.

---

## 📈 Histórico de versões

| Versão | Data | O que mudou |
|---|---|---|
| [v1.5](https://github.com/Joaovictor921/Forca-feita-em-c-/releases/tag/v1.5) | mar/2026 | Forca local no terminal |
| [v1.6](https://github.com/Joaovictor921/Forca-feita-em-c-/releases/tag/v1.6) | abr/2026 | Primeira versão estável: até 3 jogadores, pontuação, 8 tentativas, categorias |
| [Multiplayer v1.0](https://github.com/Joaovictor921/Forca-feita-em-c-/releases/tag/Multplayer) | out/2026 | Dois jogadores em rede (servidor + cliente), memória compartilhada e TCP |
| [Multplayer V2.0](https://github.com/Joaovictor921/Forca-feita-em-c-/releases/tag/Multplayer_V2.0) | out/2026 | Salas com código, 2 a 6 jogadores, ranking global, chat, sons e animações |
| [Multplayer V2.1](https://github.com/Joaovictor921/Forca-feita-em-c-/releases/tag/Multplayer_V2.1) | out/2026 | `forca.exe` independente (sem DLLs) para baixar e jogar |
| [Multplayer V2.2](https://github.com/Joaovictor921/Forca-feita-em-c-/releases/tag/Multplayer_V2.2) | out/2026 | Chute a qualquer momento, tempo por jogada, rodadas, mestre, equipes, espectadores, reconexão |
| [Trabalho Maurilio](https://github.com/Joaovictor921/Forca-feita-em-c-/releases/tag/TrabalhoMaurilio) | nov/2026 | Servidor concorrente com pthreads e mutex |

### 📁 O que há neste repositório

Os arquivos da branch principal são das **primeiras versões**. O código das versões multiplayer está
dentro dos pacotes de cada **[release](https://github.com/Joaovictor921/Forca-feita-em-c-/releases)**.

| Arquivo | Conteúdo |
|---|---|
| `jogo da forca premiun.cpp` | primeira versão local |
| `jogo da forca premiun v1.5.cpp` | versão local 1.5 |
| `jogo da forca premiun v1.6.cpp` | versão local 1.6 (estável) |
| `JogoForcaMultplayer.zip` | multiplayer v1.0 (2 jogadores) |

---

## 🚀 Próximos passos

- [ ] **Interface gráfica** (janela no Windows, com botões e desenho da forca) *(em desenvolvimento)*
- [ ] **Servidor online** ligado 24h, sem precisar de VPN, com ranking sempre atualizado *(em desenvolvimento)*
- [ ] Descoberta automática de servidores na rede local
- [ ] Identificação mais segura no ranking (hoje vale pelo nome, sem senha)
- [ ] Ranking por período e estatísticas por jogador
- [ ] Build automático do `.exe` a cada release e testes automáticos
- [ ] Código dividido em vários arquivos (servidor, cliente, palavras)

---

## 🎓 Sobre o projeto

Projeto acadêmico do curso de **Engenharia de Software** que aplica, na prática, conceitos de
programação em C++ (structs, strings, vetores, funções), **sockets TCP/IP**, **arquitetura
cliente/servidor**, **comunicação entre processos**, **memória compartilhada**, **threads** e
**sincronização com mutex**.
