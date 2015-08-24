Compiler=gcc


hq9+c: hq9+c.c
	$(Compiler) hq9+c.c -O2 -o hq9+c

clean:
	rm -f hq9+c