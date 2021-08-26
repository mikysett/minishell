# Here are some nice cases to test the bash:

< Makefile << EOF wc -l
	Stay on the prompt, discard the Makefile input and take into account the direct input
<< EOF < Makefile wc -l
	Stay on the prompt but also take into account the content of Makefile
	and discard the direct input

< Makefile wc -l >out1 >>out2
	Create both out1 and out2 but only writes in out2

< Makefile wc -l >>out2 >out1
	Create both out1 and out2 but only writes in out1

(wc -l) <Makefile
	Works just fine
((wc -l)) <Makefile
	Doesn't print any output (but doesn't gives any error neither)
>out1 (wc <Makefile)
	bash: syntax error near unexpected token `('

(wc -l <Makefile)<other_file
	WC will take input from Makefile
	(direct command redirection operator has priority over group redirection operator)

echo 'small string' | wc -l <Makefile
	WC will take input from Makefile
	(direct command redirection operator has priority over pipes)

wc <file_not_exist >out1
	Bash prints an error and do not create the file out1
wc >out1 <file_not_exist
	Bash prints an error but create the out1 file
	Redirections position in the instructions matters!!!

bash test1
bash test1 test1
bash test1 test2
	test1 and test2 are two files with some bash commands (like echo and wc)
	only test1 is executed (and only once)
	This is maybe why they speak about interactive and non interactive modes