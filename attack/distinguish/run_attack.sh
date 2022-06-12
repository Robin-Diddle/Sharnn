make
python3 ./random_generate.py > distinguish.input
./distinguish_attack
python3 distinguish_analysis.py