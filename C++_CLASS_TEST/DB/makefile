OBJS1 = ./obj/server.o ./obj/AirManager.o
OBJS2 = ./obj/client.o
inc_path = ./inc

myArgs = -Wall -g

All: server client

server: $(OBJS1)
	g++ $^ -o $@ $(myArgs)
client: $(OBJS2)
	g++ $^ -o $@ $(myArgs)
$(OBJS1): ./obj/%.o: ./src/%.cpp
	g++ -c $< -o $@ $(myArgs) -I $(inc_path)
$(OBJS2): ./obj/%.o: ./src/%.cpp
	g++ -c $< -o $@ $(myArgs) -I $(inc_path)
clean:
	rm -rf $(OBJS1) $(OBJS2) server client

.PHONY: ALL clean
