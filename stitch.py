import os

mode = "new"

if(mode == "new"):
	# print("asdasdasdasd"[-2:])
	os.chdir("./c")
	files = os.listdir(os.getcwd())
	whole = open("../toComp.c", "w")
	for i in files:
		if(i[-2:] == ".c"):
			tmp = open(i, "r")
			whole.write(tmp.read())
			tmp.close()
	whole.close()
	exit()
    

whole = open("toComp.c", "w")
try:
    headers = open("c/headers.c","r")
except:
    pass
try:
    meat = open("c/main.c","r")
except:
    pass
try:
    drivers = open("c/drivers.c", "r")
except:
    pass
try:
    utils = open("c/utils.c", "r")
except:
    pass
try:
    interupts = open("c/text.c", "r")
except:
    pass
try:
    picstuff = open("c/pic.c", "r")
except:
    pass

#whole.write(headers.read())
whole.write(meat.read())
whole.write(drivers.read())
whole.write(interupts.read())
whole.write(utils.read())
whole.write(picstuff.read())
whole.close()
meat.close()
#headers.close()
drivers.close()
interupts.close()
utils.close()
picstuff.close()
