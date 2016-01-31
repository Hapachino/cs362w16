#!/bin/bash

gcc testme.c -o testme
if [ $? -eq 0 ]
then 
	./testme
fi
