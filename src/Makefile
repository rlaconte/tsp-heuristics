main: *cpp
	g++ *.cpp -o ejec 

%.o: %.cpp
	g++ -lm -no-pie -c -o $@ $<

clean:
	-rm -f *.o ejec