#make smithytest
make unittest4
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
	# ./smithytest
	# rm smithytest
	./unittest4
	rm unittest4

fi
