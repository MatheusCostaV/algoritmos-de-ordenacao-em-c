CC = gcc
CPPFLAGS = -Isrc
WARN = -std=c11 -Wall -Wextra
CFLAGS = $(WARN) -O2

ALG_SRCS = src/basicos/bubble.c src/basicos/selection.c src/basicos/insertion.c \
           src/avancados/merge.c src/avancados/quick.c src/avancados/heap.c
ALG_OBJS = $(ALG_SRCS:%.c=build/normal/%.o)
MAIN_OBJ = build/normal/src/main.o
TEST_OBJ = build/normal/tests/test_basic.o
BENCH_OBJ = build/normal/src/bench.o
COV_ALG_OBJS = $(ALG_SRCS:%.c=build/coverage/%.o)
COV_TEST_OBJ = build/coverage/tests/test_basic.o

all: sort_main

sort_main: $(MAIN_OBJ) $(ALG_OBJS)
	$(CC) $(CFLAGS) $^ -o $@

test_basic: $(TEST_OBJ) $(ALG_OBJS)
	$(CC) $(CFLAGS) $^ -o $@

bench_sort: $(BENCH_OBJ) $(ALG_OBJS)
	$(CC) $(CFLAGS) $^ -o $@

build/normal/%.o: %.c
	@mkdir -p $(@D)
	$(CC) $(CPPFLAGS) $(CFLAGS) -MMD -MP -c $< -o $@

build/coverage/%.o: %.c
	@mkdir -p $(@D)
	$(CC) $(CPPFLAGS) $(WARN) -O0 -g --coverage -MMD -MP -c $< -o $@

build/coverage/test_basic: $(COV_TEST_OBJ) $(COV_ALG_OBJS)
	$(CC) --coverage $^ -o $@

test: test_basic
	./test_basic

coverage: build/coverage/test_basic
	@mkdir -p docs/gcov
	find build/coverage -name '*.gcda' -delete
	./build/coverage/test_basic
	gcov $(COV_ALG_OBJS) > docs/gcov/resumo.txt
	mv -f ./*.c.gcov docs/gcov/
	cat docs/gcov/resumo.txt

sort_profile: src/main.c $(ALG_SRCS) src/algoritmos.h src/metricas.h
	$(CC) $(CPPFLAGS) $(WARN) -O0 -g -pg $(filter %.c,$^) -o $@

profile: sort_profile
	./sort_profile 50000
	gprof ./sort_profile gmon.out > docs/perfil_bruto.txt

cppcheck:
	cppcheck --enable=warning,style,performance,portability --std=c11 \
	    --error-exitcode=1 -I src src tests > docs/cppcheck_bruto.txt 2>&1

bench: bench_sort
	@mkdir -p build
	./bench_sort > build/resultados.csv
	mv build/resultados.csv docs/resultados.csv

clean:
	rm -rf build
	rm -f sort_main test_basic bench_sort sort_profile gmon.out ./*.gcov

-include $(ALG_OBJS:.o=.d) $(MAIN_OBJ:.o=.d) $(TEST_OBJ:.o=.d) $(BENCH_OBJ:.o=.d)
-include $(COV_ALG_OBJS:.o=.d) $(COV_TEST_OBJ:.o=.d)

.PHONY: all test coverage profile cppcheck bench clean

