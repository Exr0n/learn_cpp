#!/bin/zsh
cache="./.template_state/last.txt"

dateformat="+%a %d %b %Y @ %R (%Z)";

mkdir -p $1

[[ -s "$1/main_$(basename $1).cpp" ]] ||\
    cat ./.template_state/defines_test.cpp\
    | sed "s/\[\!meta\:pid\!\]/$(basename $1)/g"\
    | sed "s/\[\!meta\:srcpath\!\]/${1//\//\\/}/g"\
    | sed "s/\[\!meta\:beg\!\]/$(date "$dateformat")/g"\
    >> "$1/main_$(basename $1).cpp"
echo "$1" > "$cache"
./list_completed.sh

cat ./.template_state/Makefile\
    | sed "s/\[\!meta\:pid\!\]/$(basename $1)/g"\
    >> "$1/Makefile"

tmux new-window -n "$(basename $1)" "cd $1 && tmux split-window -h && tmux selectp -L && nvim 'main_$(basename $1).cpp' -c 'normal 58G15l'"

#[[ -s "$1/main_$(basename $1).cpp" ]] && printf "File exists!\n" | exit 1
