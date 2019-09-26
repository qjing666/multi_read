num_thread = 8
total_num = 1<<24
num_per_file = total_num/num_thread
for i in range(num_thread):
	filename = "8/{}.txt".format(i)
        f = open(filename,'w')
	for j in range(num_per_file):
		print>>f, j+i*num_per_file

	f.close()



