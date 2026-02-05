find . -type f -exec sh -c 'echo "---"; stat {} | sed -n "1p;\$p"' \;
