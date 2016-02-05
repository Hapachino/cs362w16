#make smithytest
make villagetest
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
	./villagetest
	rm villagetest

fi
