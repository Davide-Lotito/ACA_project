with open("inputtext.txt", "r") as f:
    s = f.read().replace("\n", "")

with open("inputtext_no_nl.txt", "w+") as f:
    f.write(s)
