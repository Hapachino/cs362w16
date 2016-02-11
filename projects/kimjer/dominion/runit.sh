make unittests 
RET=$?
make clean
if [ $RET -eq 0 ]
then
	echo ""
	echo ""
	echo ""
	echo ""
	echo ""
	echo ""
	echo ""
	./randomtestcard
	rm randomtestcard 

fi
