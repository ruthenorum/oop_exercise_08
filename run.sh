#!/bin/bash
g++ -pthread main.cpp -o main && ./main 8 < test_01.txt
