CFLAGS = -Wall -g  -std=c99 # gerar "warnings" detalhados e infos de depuração

objs = myavl.o libAvl.o

# regra default (primeira regra)
all: myavl

# regras de ligacao
myavl: $(objs)

# regras de compilação 
# devido à declaração implícita 
# o nome do .o deve ser igual ao .c 

myavl.o:   myavl.c libAvl.h
libAvl.o: libAvl.c libAvl.h

# remove arquivos temporários
clean:
	-rm -f $(objs) *~

# remove tudo o que não for o código-fonte
purge: clean
	-rm -f myavl
