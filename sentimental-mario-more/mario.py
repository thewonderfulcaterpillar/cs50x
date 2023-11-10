def getHeight():
    height="!"
    while not height.isdigit() or 0>=int(height) or int(height)>8:
        height=input("Enter an integer between 1-8 : ")
    return height

height=int(getHeight())
for level in range(1,height+1):
    layer=""
    for _ in range(height-level):
        layer+=" "
    for _ in range(level):
        layer+="#"
    layer+="  "
    for _ in range(level):
        layer+="#"
    print(layer)



