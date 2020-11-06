import sys
sys.path.append("../../lib")

import libcaffparser

def test():
    with open("../../example/1.caff", "rb") as f:
        contents = f.read()
        length = len(contents)
        caff = libcaffparser.parse(contents, length,  False)
        print("Python: ")
        if caff.getCode() == libcaffparser.ERROR_HEADER:
            print("Error in header!")
            return 1
        if caff.getCode() == libcaffparser.ERROR_CREDITS:
            print("Error in credits!")
            return 2
        if caff.getCode() == libcaffparser.ERROR_CAFF:
            print("Error in animation block!")
            return 3
        if caff.getCode() == libcaffparser.ERROR_CIFF:
            print("Error in ciff!")
            return 4
        if caff.getCode() == libcaffparser.ERROR:
            print("Unknown error!")
            return 5
        print("year: " + str(caff.getYear()) + " month: " + str(caff.getMonth()) + " day: " + str(caff.getDay()) + " hour: " + str(caff.getHour()) + " min: " + str(caff.getMin()))
        print("Creator: " + caff.getCreator())
        print("Captions:")
        print(caff.getCaptions())
        print("Tags:")
        print(caff.getTags())
        print("Width: " + str(caff.getWidth()) + " Height: " + str(caff.getHeight()))

        caff.saveToFile("output/test.tga")
        return 0

test()
