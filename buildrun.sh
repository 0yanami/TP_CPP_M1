mkdir build ;
cd build    ;
cmake .. -G "Unix Makefiles" ;
make ;
./test/calculator_test ; # tests unitaires google test
./src/calculator_run # la calculatrice 
