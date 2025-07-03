# indicate how the object files are to be created
CC         := g++
CFLAGS     := -g -O3 -fopenmp
# CFLAGS     := -g -O3 
OBJECT_FILES := driver.o helper.o column.o row.o Anti-Diagonal.o unroll.o tiling.o Anti-DiagonalTiling.o AntiDiagonalTiles.o AntiDiagonalTilesNested.o

driver: $(OBJECT_FILES)
	$(CC) $(CFLAGS) $(OBJECT_FILES) -o driver

helper: $(OBJECT_FILES)
	$(CC) $(CFLAGS) $(OBJECT_FILES) -o helper

column: $(OBJECT_FILES)
	$(CC) $(CFLAGS) $(OBJECT_FILES) -o column

row: $(OBJECT_FILES)
	$(CC) $(CFLAGS) $(OBJECT_FILES) -o row

Anti-Diagonal: $(OBJECT_FILES)
	$(CC) $(CFLAGS) $(OBJECT_FILES) -o Anti-Diagonal

unroll: $(OBJECT_FILES)
	$(CC) $(CFLAGS) $(OBJECT_FILES) -o unroll

tiling: $(OBJECT_FILES)
	$(CC) $(CFLAGS) $(OBJECT_FILES) -o tiling

Anti-DiagonalTiling: $(OBJECT_FILES)
	$(CC) $(CFLAGS) $(OBJECT_FILES) -o Anti-DiagonalTiling

AntiDiagonalTiles: $(OBJECT_FILES)
	$(CC) $(CFLAGS) $(OBJECT_FILES) -o AntiDiagonalTiles

AntiDiagonalTilesNested: $(OBJECT_FILES)
	$(CC) $(CFLAGS) $(OBJECT_FILES) -o AntiDiagonalTilesNested

driver.o : driver.cpp
	$(CC) $(CFLAGS) -c driver.cpp

helper.o : helper.cpp
	$(CC) $(CFLAGS) -c helper.cpp

column.o : column.cpp
	$(CC) $(CFLAGS) -c column.cpp

row.o : row.cpp
	$(CC) $(CFLAGS) -c row.cpp

Anti-Diagonal.o : Anti-Diagonal.cpp
	$(CC) $(CFLAGS) -c Anti-Diagonal.cpp

unroll.o : unroll.cpp
	$(CC) $(CFLAGS) -c unroll.cpp

tiling.o : tiling.cpp
	$(CC) $(CFLAGS) -c tiling.cpp

Anti-DiagonalTiling.o : Anti-DiagonalTiling.cpp
	$(CC) $(CFLAGS) -c Anti-DiagonalTiling.cpp

AntiDiagonalTiles.o : AntiDiagonalTiles.cpp
	$(CC) $(CFLAGS) -c AntiDiagonalTiles.cpp

AntiDiagonalTilesNested.o : AntiDiagonalTilesNested.cpp
	$(CC) $(CFLAGS) -c AntiDiagonalTilesNested.cpp

clean:
	rm *.o
