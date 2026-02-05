for r in {0..255..5}; do
    for g in {0..255..5}; do
        echo -en "\e[38;2;${r};${g};150m█"
    done
    echo
done
