# Trabalho Prático de Ordenação em C

**Disciplina:** Algoritmos e Estruturas de Dados I • UFMA • Terceira Unidade  
**Dupla:** Matheus Victor de Assis Costa e [nome completo do colega]  
**Repositório público:** [preencher]  
**Vídeo:** [preencher depois da gravação]

Esta base acompanha o laboratório do professor. O Bubble Sort funciona como exemplo de implementação, teste e contagem. Os outros cinco algoritmos têm arquivos próprios com instruções para a dupla completar. Os relatórios devem ser preenchidos com as medições feitas pela dupla.

## Primeira sessão

1. Na máquina Windows, use o Ubuntu pelo WSL. Se ainda precisar instalar, execute `wsl --install` no PowerShell como administrador e abra o Ubuntu. Todo o restante roda no terminal Linux.
2. No Ubuntu, rode `sudo apt update` e `sudo apt install git build-essential cppcheck`.
3. Um integrante cria **um** repositório público no GitHub e adiciona o colega como colaborador. Os dois clonam esse mesmo repositório para o diretório pessoal do Linux. Confiram `git config user.name` e `git config user.email` em cada máquina. Usem o e-mail vinculado à própria conta do GitHub.
4. Copiem os arquivos **de dentro** da pasta deste projeto para o clone, incluindo `.gitignore` e preservando o `.git` do clone.
5. Na raiz, rodem os comandos abaixo. Em seguida, abram `src/basicos/bubble.c` e simulem manualmente o vetor `[3, 1, 2]`. Expliquem por que há três comparações e duas trocas.

```bash
make
make test
./sort_main 5000 bubble
```

A suíte inicial deve mostrar seis linhas `PASSOU` para o Bubble, contando o teste das métricas. Na demonstração, esperem valores de tempo diferentes entre máquinas. Quando a dupla entender o exemplo e verificar a estrutura, registre o trabalho que efetivamente fez.

## Divisão sugerida para duas semanas

| Sessão | Matheus | Colega | Resultado da sessão |
|---|---|---|---|
| 1 | Configurar o projeto e simular o Bubble | Configurar acesso e revisar os testes do Bubble | Clones funcionam e ambos explicam o exemplo |
| 2 | Selection e testes | Insertion e testes | Três básicos disponíveis no programa |
| 3 e 4 | Merge e testes | Quick, Heap e testes | Seis algoritmos corretos, com revisão cruzada |
| 5 | Montar e executar o benchmark | Rodar gcov, gprof e cppcheck | CSV e saídas reais das ferramentas |
| 6 | Comparar medições com a teoria | Completar relatórios e conferir o clone | Ambos sabem explicar código e resultados |
| 7 | Ensaiar e gravar | Ensaiar e gravar | Tag, vídeo e comentário no SIGAA |

O tutorial sugere duas semanas. A data de entrega deve ser conferida no SIGAA.

## Como acrescentar cada algoritmo

1. Implemente no seu arquivo em `src/basicos/` ou `src/avancados/`. Mantenha a assinatura `void algoritmoSort(int v[], int n, Metricas *m)`.
2. Em `tests/test_basic.c`, chame `verifica` com pelo menos dois vetores e respectivos resultados esperados. Cada chamada altera o vetor de entrada. Use uma cópia nova para cada teste. Inclua casos de borda como vazio e unitário, além de negativos e duplicatas.
3. Em `src/main.c`, troque o `NULL` pelo nome da função implementada na tabela `algoritmos`. Rode `make test` e, por exemplo, `./sort_main 1000 selection`.
4. Com os seis integrados, `./sort_main 1000` deve rodar os seis sobre cópias do mesmo vetor.

| Algoritmo | O que deve permanecer verdadeiro a cada etapa |
|---|---|
| Bubble | Ao fim de cada passada, o maior do trecho ativo está no final desse trecho. |
| Selection | O prefixo já contém, em ordem, os menores valores encontrados. |
| Insertion | Antes de inserir a chave, o prefixo anterior já está ordenado. |
| Merge | Intercale duas metades já ordenadas. Use `malloc` com verificação e libere o auxiliar com `free`. |
| Quick | Particione e recurse em intervalos menores. Use pivô do meio ou mediana de três e explique a escolha no código. |
| Heap | Durante a extração, o trecho ativo mantém um max-heap, com o maior na raiz. |

Conte apenas comparações entre valores usados na ordenação. Bubble, Selection, Quick e Heap contam trocas entre elementos. Insertion e Merge contam deslocamentos ou cópias. Registre a convenção em [docs/analise.md](docs/analise.md).

## Benchmark e ferramentas

Em `src/bench.c`, implemente primeiro uma combinação e confira o CSV. Depois amplie para todos os tamanhos e cenários. Use `srand(42)` e entradas equivalentes entre algoritmos. Cronometre apenas a função de ordenação com `clock()`. Faça a cópia, a validação e a impressão fora do cronômetro. Faça cinco repetições por combinação e registre a média dos tempos e as métricas de uma repetição consistente.

| Entradas | Tamanhos | Repetições |
|---|---|---|
| Aleatória, crescente, decrescente | 1.000, 5.000, 10.000 e 50.000 para os seis | 5 por combinação |
| As mesmas três | 500.000 apenas para Merge, Quick e Heap | 5 por combinação |

O CSV final tem **81 resultados e um cabeçalho**. Use nomes de cenário sem acentos no CSV e preservem a ordem destas colunas:

```text
algoritmo,tipo,n,tempo_ms,comparacoes,trocas
```

| Comando | Saída e critério |
|---|---|
| `make test` | Ao menos 2 casos por algoritmo e saída diferente de zero se algum falhar. |
| `make coverage` | `docs/gcov/` e `docs/cobertura.md`. Meta de 70% ou mais na soma das linhas executáveis dos seis arquivos de algoritmos. |
| `make profile` | `docs/perfil_bruto.txt` e `docs/perfil.md`. Use a compilação com `-O0 -pg` e explique o perfil. |
| `make cppcheck` | `docs/cppcheck_bruto.txt` e `docs/cppcheck.md`. A entrega fica sem erros reportados pelo analisador. |
| `make bench` | `docs/resultados.csv` e `docs/analise.md`. O alvo depende da implementação pendente de `src/bench.c` e usa `-O2`. |

O Makefile inicial já tem os alvos. Cobertura e profiling da base descrevem apenas o código inicial e devem ser refeitos após implementar e testar tudo. Os arquivos brutos e o CSV são gerados pelas ferramentas.

## Git, defesa e envio

- Antes de editar, façam `git pull`. Depois de testar, revisem `git diff`, preparem os arquivos da mudança com `git add`, façam um commit descritivo e usem `git push`.
- Façam commits frequentes e relevantes, no mínimo um a cada dois ou três dias de trabalho. Exemplos de mensagens, somente quando descreverem trabalho real: `feat: implementa selection sort` e `test: cobre duplicatas no quick sort`.
- Confiram `git shortlog -sn` e o conteúdo dos commits. Cada integrante registra a própria contribuição. Se a participação for equilibrada, os dois apresentam. Se um tiver participação mínima ou superficial, ele apresenta o vídeo inteiro sozinho. Em qualquer formato, os dois precisam dominar todo o projeto.
- Gravem no máximo **20 minutos**, mostrando editor e terminal. Um roteiro de cerca de 13 minutos: 1 min de apresentação, 3 min de código, 2 min de execução, 3 min de resultados, 3 min das ferramentas e 1 min de conclusão. Mostrem dados reais, uma comparação com a teoria e a explicação de uma dificuldade.
- Em um clone novo, verifiquem `make clean && make all && make test && make coverage && make bench && make profile && make cppcheck`. Confiram também o README e os relatórios versionados.
- Na versão final, criem `git tag -a v1.0 -m "Entrega final do trabalho de ordenação"` e enviem com `git push origin main --tags`. Publiquem o vídeo no YouTube como público ou não listado. Enviem um comentário único no SIGAA com os dois nomes completos, o link público do GitHub e o link do vídeo.

## Materiais da disciplina

- [Especificação e tutorial do trabalho](https://lambdageo-edu.github.io/book-estrutura-de-dados/laboratorios/02_trabalho_pratico_ordenacao/)
- [Ordenação básica](https://lambdageo-edu.github.io/book-estrutura-de-dados/aulas/12_ordenacao_basica/)
- [Ordenação avançada](https://lambdageo-edu.github.io/book-estrutura-de-dados/aulas/13_ordenacao_avancada/)
- [Análise experimental e ferramentas](https://lambdageo-edu.github.io/book-estrutura-de-dados/aulas/14_analise_experimental/)

