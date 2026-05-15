CC = gcc
SRC = src/gf.c src/poly.c src/rs_encoder.c src/rs_decode.c
TEST = tests/rs_tests.c

rs_tests: $(SRC) $(TEST)
	$(CC) $(SRC) $(TEST) -o rs_tests

clean:
	rm -f rs_tests
