import sys
import os

fout_list = []
for i in range(int(sys.argv[1])):
    fout_list.append(open(str(i) + ".txt", "w"))

idx = 0
file_num = int(sys.argv[1])
for line in sys.stdin:    
    fout_list[idx % file_num].write(line)
    idx += 1
