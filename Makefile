build:
	gcc main.c -o lanParty

run:
	./lanParty ./date/t1/c.in ./date/t1/d.in ./out/out1.out

clean:
	rm lanParty