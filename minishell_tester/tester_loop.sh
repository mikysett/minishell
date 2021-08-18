#! /bin/bash

nb_tests=${#cmd_bash[@]}

for (( i=0; i < $nb_tests; i++ )); do
	expected_out=$(eval ${cmd_bash[$i]} 2>&1)
	test -e ${fileout[$i]} && expected_fileout=$(< ${fileout[$i]} cat) || expected_fileout=""
	if [ "${filein[$i]}" != "${fileout[$i]}" ]; then
		rm -f ${fileout[$i]}
	fi;
	test_out=$(eval ${prog_pathname} ${cmd_pipex[$i]} 2>&1)
	test -e ${fileout[$i]} && test_fileout=$(< ${fileout[$i]} cat) || test_fileout=""
	rm -f ${fileout[$i]}
	
	TEST_CLR="$GRN"
	OK_OUT=1
	OK_FILEOUT=1
	
	if [ "$expected_out" != "$test_out" ]; then
		TEST_CLR="$YEL"
		OK_OUT=0
	fi;
	if [ "$expected_fileout" != "$test_fileout" ]; then
		TEST_CLR="$RED"
		OK_FILEOUT=0
	fi;
	
	echo -e "\n-----------------------------------------"
	echo -e "$TEST_CLR Test    $i:$WHT ${cmd_bash[$i]}"
	if [ $OK_OUT == 0 ]; then
		echo -e "$YEL Differences in program output:$WHT"
		echo -e "$BLU bash output :$WHT"
		echo "$expected_out"
		echo -e "$BLU pipex output:$WHT"
		echo "$test_out"
	fi;
	if [ $OK_FILEOUT == 0 ]; then
		echo -e "$RED Differences in final file:$WHT"
		echo -e "${BLU}bash file :${WHT}"
		echo "$expected_fileout"
		echo -e "${BLU}test file :${WHT}"
		echo "$test_fileout"
	fi;
done
