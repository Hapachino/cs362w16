{\rtf1\ansi\ansicpg1252\cocoartf1404\cocoasubrtf340
{\fonttbl\f0\fmodern\fcharset0 Courier;\f1\fnil\fcharset0 Monaco;}
{\colortbl;\red255\green255\blue255;\red106\green62\blue62;\red127\green0\blue85;\red42\green0\blue255;
}
\margl1440\margr1440\vieww15540\viewh17840\viewkind0
\deftab720
\pard\pardeftab720\partightenfactor0

\f0\fs26 \cf0 \expnd0\expndtw0\kerning0
Title:    URL Validator Port can\'92t accept value of 4 or greater.\
\
Class:	 Serious Bug\
e.g. "Feature Request", "System Error", "Serious Bug"\
\
Date:           3/1/16\
Reported By:    Myles Chatman\
Email:      	  chatmanm@oregonstate.edu\
\
\
Product: DomainValidator                  Version:\
Platform: Java                      		 Version:\
Browser:                        			 Version:\
URL:        \
\
Is it reproducible: Yes\
\
Description\
===========\
Testing a port number that is equal to 4 or greater failed an assertion test\
returning false where it was expected to return true.\
\
\
Steps to Produce/Reproduce\
--------------------------\
1. Validate an existing URL i.e.: http://www.google.com . Assert that the URL returns true.\
2. Create a class object and assign a port value with four digits or greater\
	
\f1\fs22 \kerning1\expnd0\expndtw0 ResultPair[] \cf2 testUrlPort = \cf3 new\cf0  ResultPair(\cf4 ":8000"\cf0 , \cf3 true\cf0 ),\
3. Print expected and actual results to console and Assert the results.
\f0\fs26 \expnd0\expndtw0\kerning0
\
\
\
Expected Results\
----------------\
\pard\pardeftab720\partightenfactor0

\f1\fs22 \cf0 \kerning1\expnd0\expndtw0 http://www.google.com:65535 \
Expected: true
\f0\fs26 \expnd0\expndtw0\kerning0
\
\pard\pardeftab720\partightenfactor0
\cf0 \
\
Actual Results\
--------------\

\f1\fs22 \kerning1\expnd0\expndtw0 http://www.google.com:65535 
\f0\fs26 \expnd0\expndtw0\kerning0
\
\pard\pardeftab720\partightenfactor0

\f1\fs22 \cf0 \kerning1\expnd0\expndtw0 Actual: false
\f0\fs26 \expnd0\expndtw0\kerning0
\
\pard\pardeftab720\partightenfactor0
\cf0 \
\
Workarounds\
-----------\
Currently researching.\
\
\
Attachments\
-----------\
none.\
\
\
Other Information\
-----------------\
none.}