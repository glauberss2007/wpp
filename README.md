# W++ - Web Framework

## Configurando o projeto

### Instalando bibliotecas (Ubuntu)

```
sudo apt-get install llvm
sudo apt-get install build-essential
sudo apt-get install clang++
sudo apt-get install git
sudo apt-get install cmake
sudo apt-get install openssl
sudo apt-get install libboost-all-dev
sudo apt-get install libpoco-dev
```

Além destas, você precisa das bibliotecas `Tcmalloc`, `Threads` e `OpenSSL`, que normalmente vêm instaladas pelo sistema operacional.


### Instalando bibliotecas (MacOSX)

```
/usr/bin/ruby -e "$(curl -fsSL https://raw.githubusercontent.com/Homebrew/install/master/install)"
brew update
brew install conan
brew install git
brew install cmake
brew install boost
brew install openssl
brew install libiodbc
brew install mysql
# brew install poco
tar xvfz poco-1.7.8p2.tar
cd poco-1.7.8p2

```

Além destas, você precisa das bibliotecas `Tcmalloc`, `Threads` e `OpenSSL`, que normalmente vêm instaladas pelo sistema operacional.


### Configurando Gitlab no CLion


#### Clonando o projeto

No menu do CLion escolher: `VCS` / `Checkout from Version Control` / `Git`

GitRepository URL: `https://gitlab.com/alandefreitas/wpp.git`

Parent Directory: `/home/seu_nome/CLionProjects` (ou qualquer outro diretório onde queira guardar o projeto)

Directory Name: `wpp`

#### Criando um branch

`VCS` ou `clique direito em uma pasta` / `Git` / `Branches`

#### Definindo tipo de arquivo tipo .pop

`File` / `Import Settings...`

Abrir o arquivo `resources/highlighter/settings.jar`

### Informações do projeto

 Informações do projeto podem ser vistas na aba `Version Control`.

 Coisas a fazer no projeto podem ser vistas na aba `TODO`.