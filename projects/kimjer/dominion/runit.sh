RET=$?
make clean
make cleanprogs
make dominion.o
make adventurertest
if [ $RET -eq 0 ]
then
	echo ""
	echo ""
	echo ""
	echo ""
	echo ""
	echo ""
	echo ""
	./adventurertest
	 rm adventurertest
	# if [[ -f cardFunctions ]]
	# then 
	# 	rm cardFunctions
	# fi

	# if [[ -f adventurertest ]]
	# then
	# 	rm adventurertest
	# fi

	# if [[ -f villagetest ]]
	# then
	# 	rm villagetest
	# fi

	# if [[ -f testDrawCard ]]
	# then
	# 	rm badTestDrawCard
	# fi

	# if [[ -f smithytest ]]
	# then
	# 	rm smithytest
	# fi

	# if [[ -f testDrawCard ]]
	# then 
	# 	rm testDrawCard
	# fi

	# if [[ -f unittest1 ]]
	# 	then
	# 	rm unittest1
	# fi
fi
