TARGET:=bmpreader

all:
	gcc main.c -o $(TARGET)

run:
	./$(TARGET) img/wf.bmp wf_output.bmp

showpic:
	eog wf_output.bmp

clean:
	rm *output.bmp $(TARGET)
