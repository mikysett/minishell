#! /bin/bash

declare -a cmd_bash
declare -a fileout

export cmd_bash
export fileout

cmd_bash+=("tests/basic_1")
fileout+=("fileout")

cmd_bash+=("tests/basic_2")
fileout+=("fileout")
