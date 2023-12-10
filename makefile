SRC=$(wildcard *.c) 
OBJ=$(SRC:.c=.o) 
INC=$(wildcard *.h) 
LIBRARY=liblaliz.so
EXECUTABLE=execlib 

all: $(LIBRARY) $(EXECUTABLE) 
debug: 
	@echo $(SRC) 
	@echo $(OBJ) 
	@echo $(INC) 

%.o: %.c $(INC) 
	gcc -c $< -o $@ 

$(LIBRARY): $(OBJ) 
	gcc -shared -o $@ $^ 

$(EXECUTABLE): main.o $(LIBRARY) 
	gcc -fsanitize=address $< -L. -llaliz -o $@ 

run: $(EXECUTABLE) 
	@export LD_LIBRARY_PATH=.; \
	./$(EXECUTABLE) 
	
doc: doxygen Doxyfile 

clean: 
	rm -f *.o 
	rm -f $(LIBRARY) $(EXECUTABLE) 
	rm -rf doc exec
