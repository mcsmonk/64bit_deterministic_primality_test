OBJECTS = main.o deterministic_mr_64bit_prime_test.o simple_prime_test.o

TARGET = isprime
test : $(OBJECTS)
	gcc -o $(TARGET) $(OBJECTS) -I /home/SH_Jin/deterministic_primality_test/gmp/include -L/home/SH_Jin/deterministic_primality_test/gmp/lib -lgmp
	rm -rf $(OBJECTS)

main.o : deterministic_mr_64bit_prime_test.h main.c
	gcc -c -O2 main.c
deterministic_mr_64bit_prime_test.o : gmp.h deterministic_mr_64bit_prime_test.c
	gcc -c -O2 -lgmp deterministic_mr_64bit_prime_test.c
simple_prime_test.o : simple_prime_test.c
	gcc -c -O2 simple_prime_test.c
clean :
	rm -rf $(OBJECTS) $(isprime).exe
