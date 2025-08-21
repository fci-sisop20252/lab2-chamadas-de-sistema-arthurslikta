# Relatório do Laboratório 2 - Chamadas de Sistema

---

## Exercício 1a - Observação printf() vs 1b - write()

### Comandos executados:
```bash
strace -e write ./ex1a_printf
strace -e write ./ex1b_write
```

### Análise

**1. Quantas syscalls write() cada programa gerou?**
- ex1a_printf: 9 syscalls
- ex1b_write: 7 syscalls

**2. Por que há diferença entre printf() e write()?**

```
Pois o printf() aciona mais syscalls enquanto o write() chama direto do kernel.
```

**3. Qual implementação você acha que é mais eficiente? Por quê?**

```
O printf é mais eficiente pois ele consegue acumular em buffers e evitar diversas syscalls.
```

---

## Exercício 2 - Leitura de Arquivo

### Resultados da execução:
- File descriptor: 3
- Bytes lidos: 127

### Comando strace:
```bash
strace -e open,read,close ./ex2_leitura
```

### Análise

**1. Por que o file descriptor não foi 0, 1 ou 2?**

```
Pois o 0, 1 e 2 ja estão sendo usados respectivamente pela entrada, saída e erros.
```

**2. Como você sabe que o arquivo foi lido completamente?**

```
Pois o tamanho definido do buffer é de 127 bytes, o mesmo valor que o programa deu como lido.
```

---

## Exercício 3 - Contador com Loop

### Resultados (BUFFER_SIZE = 64):
- Linhas: 24 (esperado: 25)
- Caracteres: 1299
- Chamadas read(): 21
- Tempo: 0.000122 segundos

### Experimentos com buffer:

| Buffer Size | Chamadas read() | Tempo (s) |
|-------------|-----------------|-----------|
| 16          |  82             | 0.000230  |
| 64          |  21             | 0.000122  |
| 256         |  6              | 0.000063  |
| 1024        |  2              | 0.000060  |

### Análise

**1. Como o tamanho do buffer afeta o número de syscalls?**

```
Quanto maior for o tamanho do buffer menos chamadas de sistemas é ocorrido.
```

**2. Como você detecta o fim do arquivo?**

```
Enquanto o read() não retorna 0, o arquivo continua sendo executado até que não há mais bytes a ser lidos.
```

---

## Exercício 4 - Cópia de Arquivo

### Resultados:
- Bytes copiados: _____
- Operações: _____
- Tempo: _____ segundos
- Throughput: _____ KB/s

### Verificação:
```bash
diff dados/origem.txt dados/destino.txt
```
Resultado: [ ] Idênticos [ ] Diferentes

### Análise

**1. Por que devemos verificar que bytes_escritos == bytes_lidos?**

```
[Sua análise aqui]
```

**2. Que flags são essenciais no open() do destino?**

```
[Sua análise aqui]
```

---

## Análise Geral

### Conceitos Fundamentais

**1. Como as syscalls demonstram a transição usuário → kernel?**

```
[Sua análise aqui]
```

**2. Qual é o seu entendimento sobre a importância dos file descriptors?**

```
[Sua análise aqui]
```

**3. Discorra sobre a relação entre o tamanho do buffer e performance:**

```
[Sua análise aqui]
```

### Comparação de Performance

```bash
# Teste seu programa vs cp do sistema
time ./ex4_copia
time cp dados/origem.txt dados/destino_cp.txt
```

**Qual foi mais rápido?** _____

**Por que você acha que foi mais rápido?**

```
[Sua análise aqui]
```

---

## Entrega

Certifique-se de ter:
- [ ] Todos os códigos com TODOs completados
- [ ] Traces salvos em `traces/`
- [ ] Este relatório preenchido como `RELATORIO.md`

```bash
strace -e write -o traces/ex1a_trace.txt ./ex1a_printf
strace -e write -o traces/ex1b_trace.txt ./ex1b_write
strace -o traces/ex2_trace.txt ./ex2_leitura
strace -c -o traces/ex3_stats.txt ./ex3_contador
strace -o traces/ex4_trace.txt ./ex4_copia
```