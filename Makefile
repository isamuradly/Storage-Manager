# CS525: Advanced Database Organization
# Fall 2021 | Group 22
# Isa Muradli           (imuradli@hawk.iit.edu)       (Section 01)
# Andrew Petravicius    (apetravicius@hawk.iit.edu)   (Section 01)
# Christopher Sherman   (csherman1@hawk.iit.edu)      (Section 02)

.PHONY: default
default: test_assign1

test_assign1: storage_mgr.c dberror.c test_assign1_1.c
	gcc -Wall -o test_assign1 storage_mgr.c dberror.c test_assign1_1.c

my_test1.out: storage_mgr.c dberror.c my_test1.c
	gcc -Wall -o my_test1.out storage_mgr.c dberror.c my_test1.c

.PHONY: my_test
my_test: my_test1.out

.PHONY: tests
tests: test_assign1 my_test1.out
	echo "\n===== GIVEN TEST =====\n"
	./test_assign1
	echo "\n===== MY TEST =====\n"
	./my_test1.out
	echo "\n===== TESTS COMPLETE =====\n"

.PHONY: all
all: tests clean

.PHONY: clean
clean:
	rm -f test_assign1
	rm -f *.bin
	rm -f *.out
