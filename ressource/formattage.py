with open("oneUpMario.wav", "rb") as fEntree:
    dataL = fEntree.readlines()
data = dataL[0]
for i in range(1,len (dataL)):
    data+=dataL[i]
sortie = "const unsigned char sample [{}] =".format(len(data)) +"{\n "
c = 0
for octet in data:
    sortie += " {},".format(hex(int(octet)))
    if c == 11:
        sortie += "\n "
        c = 0
    else:
        c+=1
sortie+="\n};\n"
print (sortie)