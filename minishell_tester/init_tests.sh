#! /bin/bash

declare -a cmd_bash
declare -a fileout

export cmd_bash
export fileout

cmd_bash+=("")
fileout+=("fileout")

cmd_bash+=("only_one_wrong_command")
fileout+=("fileout")

cmd_bash+=("< filein cat")
fileout+=("fileout")

cmd_bash+=("< wrong_infile@àà# cat | wc > fileout")
fileout+=("fileout")

cmd_bash+=("< filein cat | wc > fileout_invalid_çàç@\\/&%")
fileout+=("fileout_invalid_çàç@\\/&%")

cmd_bash+=("< filein cmd_invalid | wc > fileout")
fileout+=("fileout")

cmd_bash+=("< file_not_exist cat | wc > fileout")
fileout+=("fileout")

cmd_bash+=("< empty_file cat | cat > empty_file")
fileout+=("empty_file")

cmd_bash+=("< filein2 cat | cat > filein2")
fileout+=("filein2")

cmd_bash+=("< filein cat | wc > fileout")
fileout+=("fileout")

cmd_bash+=("< ls_info cat | grep .sh > fileout")
fileout+=("fileout")

cmd_bash+=("< filein cat | wc > fileout")
fileout+=("fileout")

cmd_bash+=("< filein ls -l | wc -l > fileout")
fileout+=("fileout")

cmd_bash+=("< filein ls -l | cat -e > fileout")
fileout+=("fileout")

cmd_bash+=("< infile_grep grep a1 | wc -w > fileout")
fileout+=("fileout")

cmd_bash+=("< ls_info cat | grep .sh | wc -l > fileout")
fileout+=("fileout")

cmd_bash+=("< ls_info cat | grep .sh | sort -r | cat > fileout")
fileout+=("fileout")
