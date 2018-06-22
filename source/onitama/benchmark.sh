mkdir benchmark/
cp * benchmark 2> null

# g++ doesn't support Unicode variable identifiers
# so we have to substitute them.
for filename in benchmark/*; do
    sed -i -e 's/🔵/BLUE/g' $filename
    sed -i -e 's/🔴/RED/g' $filename
done

# Compile with debug and gprof flags.
cd benchmark
g++ -g -pg benchmark.cc Board.cc Card.cc Move.cc State.cc Random.cc Agent.cc

# Execute the program and generate profiling report.
./a && gprof a.exe 2> null | gprof2dot | dot -T pdf > ../report.pdf
cd ..

# Clean up.
rm -r benchmark/
rm null