import sys
sys.path.append("../../lib")

import libcaffparser

def test():
    #f = open("../../example/1.caff", "rb")
    #print(type(f.read()))
    """
    with open("../../example/2.caff", "rb") as f:
        lis = list(f.read())
        for a in lis:
            print(type((a)))
            break
            byte_list = []
            while True:
                byte = f.read(1)
                if not byte:
                    break
                byte_list.append(byte)
    """
    with open("../../example/2.caff", "rb") as f:
        contents = f.read()
        length = len(contents)
        caff = libcaffparser.parse(contents, length,  False)
        print("Python: ")
        if caff.getCode() == libcaffparser.ERROR:
            print("Error in CAFF file!")
            return 1
        print("year: " + str(caff.getYear()) + " month: " + str(caff.getMonth()) + " day: " + str(caff.getDay()) + " hour: " + str(caff.getHour()) + " min: " + str(caff.getMin()))
        print("Creator: " + caff.getCreator())
        print("Captions:")
        print(caff.getCaptions())
        print("Tags:")
        print(caff.getTags())
        print("Width: " + str(caff.getWidth()) + " Height: " + str(caff.getHeight()))

        caff.saveToFile("test.tga")
        return 0

test()
