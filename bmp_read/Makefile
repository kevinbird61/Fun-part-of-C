TARGET:=bmpreader

all:
	gcc main.c -o $(TARGET)

split:
	gcc main.c -DSPLIT=3 -o $(TARGET)

run:
	# img/wf.bmp => has the 4 element(alpha value)
	./$(TARGET) img/input.bmp output.bmp

showpic:
	eog output.bmp

clean:
	rm *output.bmp $(TARGET)
