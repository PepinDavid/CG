Array=()
read N
for (( i=0; i<N; i++ )); do
    read Pi
    Array+=($Pi)
done
sorted=( $( printf "%s\n" "${Array[@]}" | sort -n ) )
echo "${sorted[@]}">&2

min=1000000
for(( i=1; i<${#sorted[*]}; i++)); do
    a=${sorted[i-1]}
    b=${sorted[i]}
    c=$(($b-$a))
    if  [ "$c" -lt "$min" ]; then
        min=$c
    fi
done
# Write an action using echo
# To debug: echo "Debug messages..." >&2

echo $min