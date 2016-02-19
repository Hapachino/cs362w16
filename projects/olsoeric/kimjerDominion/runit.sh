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
	if [[ -f cardFunctions ]]
	then 
		rm cardFunctions
	fi

	if [[ -f adventurertest ]]
	then
		rm adventurertest
	fi

	if [[ -f villagetest ]]
	then
		rm villagetest
	fi

	if [[ -f testDrawCard ]]
	then
		rm badTestDrawCard
	fi

	if [[ -f smithytest ]]
	then
		rm smithytest
	fi

	if [[ -f testDrawCard ]]
	then 
		rm testDrawCard
	fi

	if [[ -f unittest1 ]]
		then
		rm unittest1
	fi
fi
