#!/bin/zsh
todays_date=`date +%m-%d-%Y`
newfile=.notes/$1-$todays_date
vim $newfile
