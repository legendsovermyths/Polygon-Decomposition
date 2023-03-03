i=1
while [ $i -le 500 ]
do
    python3 polygon.py
    ./main
    python3 checkpolygon.py
    i=$(($i+1))
done