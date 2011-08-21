
rope: scoped_timer.hpp example/rope.cpp
	@echo "GNU rope"
	g++ -I. -O3 -o rope example/rope.cpp
	./rope
	@echo "STLPort rope"
	@rm rope
	g++ -I. -O3 -DSTLP_ROPE -I/usr/include/stlport -lstlport -o rope example/rope.cpp
	./rope
	@rm rope

