xiaohan zeng Random Testing Quiz 2

1:For char inputChar() function: the possible code coverage is 256 different chars, since the number of possible char is fixed, we can just randomly pick the char from these 256 choices. That way we will cover all the possible case.

2:For inputString() function: If we do the black box test, there could be infinite possible string to test, such as, empty string, string length from 1-infinit with all 256 possible char. Since the scope is too large to test, we can hardly use this test in this function. We need to resonablely reduce this scope.
There are several possible ways to reduce the testing scope:
	1: reduce the length of the string
	2: reduce the possible char show in the string
	3: use common sense to reduce the possiblity. If we know the input will all be word, 		the testing scope will not include no meaning combination.

Because this function gives no info about how to reduce the scope, I choose to reduce the length of string to reduce the scope by only using string length smaller or equal than 100. After one night running, no error message shows. 

I choose to read the code inorder to reduce the scope. By reading the code, I decide the reasonable scope will be choosing char only from these 5 chars show in the function. 

