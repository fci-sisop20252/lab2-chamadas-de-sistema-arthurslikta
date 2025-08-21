/*
 * Exercício 4 - Cópia de Arquivo
 * 
 * OBJETIVO: Implementar programa de cópia usando syscalls
 * 
 * TAREFA: Complete todos os TODOs
 * 1. Compile: gcc src/ex4_copia.c -o ex4_copia
 * 2. Execute: ./ex4_copia
 * 3. Verifique: diff dados/origem.txt dados/destino.txt
 * 4. Analise: strace -e open,read,write,close ./ex4_copia
 */

#include <fcntl.h>
#include <unistd.h>
#include <stdio.h>
#include <time.h>

#define BUFFER_SIZE 256

int main() {
    char buffer[BUFFER_SIZE];
    ssize_t bytes_lidos, bytes_escritos;
    int fd_origem, fd_destino;
    long total_bytes = 0;
    int total_operacoes = 0;
    
    clock_t inicio = clock();
    
    printf("=== Exercício 4: Cópia de Arquivo ===\n");
    printf("Copiando: dados/origem.txt -> dados/destino.txt\n\n");
    
   
    fd_origem = open ("dados/origem.txt", O_RDONLY);
    
    if (fd_origem < 0) {
        perror("Erro ao abrir origem");
        return 1;
    }
    
    
    fd_destino = open("dados/destino.txt", O_WRONLY | O_CREAT | O_TRUNC, 0644);
    
    if (fd_destino < 0) {
        perror("Erro ao criar destino");
        close(fd_origem);
        return 1;
    }
    
    
    while ((bytes_lidos = read(fd_origem, buffer, BUFFER_SIZE)) > 0) {
        total_operacoes++;
        
        
        bytes_escritos = write(fd_destino, buffer, bytes_lidos);
        
        
        if (bytes_escritos != bytes_lidos) {
            perror("Erro na escrita");
            break;
        }
        
        
        total_bytes += bytes_lidos;
        
        if (total_operacoes % 20 == 0) {
            printf("Progresso: %ld bytes...\n", total_bytes);
        }
    }
    
    if (bytes_lidos < 0) {
        perror("Erro na leitura");
    }
    
   
    if (close(fd_origem) < 0) { };
    if (close(fd_destino) < 0) { };
    
    clock_t fim = clock();
    double tempo = ((double)(fim - inicio)) / CLOCKS_PER_SEC;
    
    printf("\n=== Estatísticas ===\n");
    printf("Bytes copiados: %ld\n", total_bytes);
    printf("Operações: %d\n", total_operacoes);
    printf("Tempo: %.6f segundos\n", tempo);
    
    if (tempo > 0) {
        printf("Throughput: %.2f KB/s\n", (total_bytes / 1024.0) / tempo);
    }
    
    printf("\nVerificação: diff dados/origem.txt dados/destino.txt\n");
    
    return 0;
}