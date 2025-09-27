from random import randint
import os

FILE = "maxNum.txt"
MAXNUMS = 10**8
MAXGEN = 2**63
#! to generate 10e8 64bits numbers and find the max took 2mins and 13s, 1.85gb file, using hdd, i5-4690, 16gb of ram and using Linux

if not os.path.exists(FILE):
    with open(FILE, "w") as f:
        for _ in range(MAXNUMS):
            f.write(f"{randint(1, MAXGEN)}\n")

maior = 0
with open(FILE, "r") as f:
    for line in f:
        n = int(line)
        if n > maior:
            maior = n

print("O maior número desse .txt é:", maior)
