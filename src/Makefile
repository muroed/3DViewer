CC=	gcc
CFLAG:= -Wall -Werror -Wextra
DEBAGFLAG:= -g
HEADER:= 	CPart/s21_Viewer.h
SOURCES:= 	CPart/s21_parser.c \
						CPart/s21_models_struct.c \
						CPart/s21_afin.c

LCHECK:= -lcheck -lm -lpthread
PROJECT_DIR=	3D_Viewer
TEST_DIR=			test_obj/
TEST_TAR_NAME= 		test_obj.tar
TEST_TAR=  $(addsuffix $(TEST_TAR_NAME), $(TEST_DIR))
TEST_FILE= UnitTests/s21_test.check
OS = $(shell uname)

ifeq (${OS}, Linux)
	LCHECK += -lsubunit -lrt
endif
ifeq ($(filter arm%,${OS}),)
	LCHECK += -I/opt/homebrew/include  -L/opt/homebrew/lib
endif

all: install open

s21_tests.c:
	checkmk $(TEST_FILE) > UnitTests/s21_tests.c

obj:
	tar xf $(TEST_TAR) -C $(TEST_DIR)

tests: s21_tests.c obj
	$(CC) $(CFLAG) $(LCHECK) $(SOURCES) UnitTests/s21_tests.c -o test.out
	./test.out

gcov_report: s21_tests.c obj
	$(CC) $(CFLAGS) --coverage $(LCHECK) $(SOURCES) UnitTests/s21_tests.c -o gcov_test
	chmod +x *
	./gcov_test
	lcov -t "gcov_test" -o gcov_test.info --no-external -c -d .
	genhtml -o report/ gcov_test.info
	open ./report/index.html
	rm -rf ./*.gcno ./*.gcda ./gcov*

install: obj
	mkdir -p $(PROJECT_DIR)/build
	cd $(PROJECT_DIR) && cmake --no-warn-unused-cli -DCMAKE_EXPORT_COMPILE_COMMANDS:BOOL=TRUE -DCMAKE_BUILD_TYPE:STRING=Debug -DCMAKE_C_COMPILER:FILEPATH=/usr/bin/clang -DCMAKE_CXX_COMPILER:FILEPATH=/usr/bin/clang++ -S. -Bbuild && cmake --build build --config Debug --target 3D_Viewer --

open:
	open $(PROJECT_DIR)/build/3D_Viewer.app

build:
	$(CC) $(CFLAG) $(DEBAGFLAG) $(SOURCES) CPart/main.c -o main.out

dvi: 
	makeinfo --html 3D_C8.texi
	open 3D_C8_manual/index.html

dist:
	cd ../ && tar cvf 3D_Viewer.tar src/
	

uninstall: 
	rm -rf $(PROJECT_DIR)/app
	rm -rf $(PROJECT_DIR)/3D_Viewer.app
	rm -rf build*
	rm -f test_obj/*.obj
	rm -f $(PROJECT_DIR)/CmakeLists.txt.user
	rm -rf $(PROJECT_DIR)/build


clean:
	rm -f .clang-format CPart/.clang-format
	rm -f *.out
	rm -f test_obj/*.obj
	rm -rf report 
	rm -f UnitTests/s21_tests.c
	rm -rf 3D_C8_manual ../3D_Viewer.tar
	rm -rf ./*.gcno ./*.gcda ./gcov*

leaks:
	./main
	leaks --atExit -- ./main

style: 
	cp ../materials/linters/.clang-format ./CPart
	clang-format -n $(SOURCES)

rebuild: uninstall clean install 