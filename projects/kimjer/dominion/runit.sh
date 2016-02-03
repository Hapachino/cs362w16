#make smithytest
make adventurertest
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
	./adventurertest
	rm adventurertest

fi
