
git add -A
git commit -m "aaaa"
git push origin master:master

if [ $# -eq 0 ]
then
    make -C box/src
    make
else
    make -C box/src $1
    make $1
fi
