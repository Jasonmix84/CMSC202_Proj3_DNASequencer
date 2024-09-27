CXX = g++
CXXFLAGS = -Wall

proj3: Strand.o Sequencer.o proj3.cpp
	$(CXX) $(CXXFLAGS) Strand.o Sequencer.o proj3.cpp -o proj3

Sequencer.o: Strand.o Sequencer.h Sequencer.cpp
	$(CXX) $(CXXFLAGS) -c Sequencer.cpp

Strand.o: Strand.h Strand.cpp
	$(CXX) $(CXXFLAGS) -c Strand.cpp

clean:
	rm *.o*
	rm *~

run:
	./proj3

run1:
	./proj3 proj3_data1.txt

run2:
	./proj3 proj3_data2.txt

run3:
	./proj3 proj3_data3.txt

run4:
	./proj3 proj3_data4.txt

val:
	valgrind ./proj3