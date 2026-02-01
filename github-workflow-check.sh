#!/bin/bash

mkdir -p bin
REPORT="audit_report.txt"
echo "--- Build & Audit Report ($(date)) ---" > $REPORT

for file in *.cpp; do
    if [[ "$file" == "peoutput.cpp" ]]; then continue; fi
    
    filename="${file%.*}"
    echo "[Building] $file ..."
    
    g++ -std=c++17 "$file" -o "bin/$filename" 2>> $REPORT
    
    if [ $? -eq 0 ]; then
        echo "  - Success: bin/$filename created."
    else
        echo "  - Failed: Check $REPORT for details."
    fi
done

echo -e "\n--- Execution Audit ---" >> $REPORT

for cmd in bin/*; do
    echo "[Executing] $cmd ..."
    "./$cmd" 2>> $REPORT
done

echo "Audit complete. Errors saved to: $REPORT"
