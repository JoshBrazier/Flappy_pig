flappy_pig:
	@g++ -c flappy_pig_v8.cpp -I/usr/local/Cellar/sfml/2.5.1_2/include
	@g++ flappy_pig_v8.o -o sfml-app -L/usr/local/Cellar/sfml/2.5.1_2/lib -lsfml-graphics -lsfml-window -lsfml-system
	@./sfml-app