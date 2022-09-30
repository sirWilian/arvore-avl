# arvore-avl

###### O trabalho busca implementar uma AVL em linguagem C

para compilar o projeto, você deve instalar o compilador gcc, mas caso esteja utilizando algum sistema UNIX, tudo que você deve fazer é utilizar o comando "**make**" dentro do diretório.

para executar o programa:

``` bash
 ./myavl < entrada.txt > saida.txt
```
onde o arquivo "entrada.txt" (ou qualquer formato simples de texto) deve conter a operação a ser feita e o número a ser guardado:
```
i 10
i 20
i 30
i 40
i 50
i 45
i 48

```
o arquivo "saida.txt" mostrará a chave, tabela e posição em que o número ficou armazenado.
no exemplo acima, a saída será:
```
10,2
20,1
30,2
40,0
45,2
48,1
50,2

```

para limpar os arquivos criados ao compilar o programa, utilize:

``` bash
make purge
```

