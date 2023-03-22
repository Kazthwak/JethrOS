#this is garbage, am not going to use
filename = "toComp.c"

#syntax for preprocessing is {name}:pp

fileo = open("strings.txt", "r")
file = fileo.readlines()
fileo.close()
i = 0
while i < (len(file)):
	if(file[i][0] == "#"):
		file.pop(i)
	else:
		file[i] = file[i].rstrip("	 \n")
		if(file[i] == ""):
				file.pop[i]
		else:
			i +=1
if(len(file)%2 != 0):
	print("FILE NOT EVEN")
	exit()

strs = []

for i in range(int(len(file)/2)):
	strs.append([file[2*i],file[2*i+1]])
# print(strs)

outp = "dd "
for i inrange