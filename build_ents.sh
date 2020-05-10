#!/usr/local/bin/zsh

if ! hash yaml2json 2>/dev/null; then
    echo "you need yaml2json for this script"
    exit
fi

echo "building"

for e in ents/*.yaml
do
    echo $e
    yaml_filen=`echo $e | awk -F/ '{print $NF}'`
    json_filen=`echo $yaml_filen | sed 's/\.yaml/\.json/g'`
    yaml2json < ents/$yaml_filen > ents/$json_filen
done
