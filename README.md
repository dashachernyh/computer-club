# computer-club
## Инструкция по сборке
### main:
$ g++ -o main main.cpp time.cpp work.cpp  
$ ./main input.txt
### google test:
$ g++ -o test test_main.cpp time.cpp work.cpp -lgtest -lgtest_main -pthread  
$ ./test input.txt
