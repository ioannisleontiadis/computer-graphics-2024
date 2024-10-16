CC = clang

CFLAGS = -I /opt/homebrew/include

LDFLAGS = -L /opt/homebrew/lib \
	  -lglew -lglfw \
	  -framework Cocoa \
	  -framework OpenGL \
	  -framework IOKit 

all:
	clang-format -style=llvm -i triangle.c utils.c
	$(CC) $(CFLAGS) $(LDFLAGS) triangle.c utils.c -o triangle
