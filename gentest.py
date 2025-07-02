import random

with open ("build/test.in", 'w') as f:
    num_inputs = 10
    d = 0
    f.write(str(d))
    f.write("\n")
    f.write(str(num_inputs))
    f.write("\n")
    if d == 0:
        for i in range(num_inputs):
            f.write(str(random.randint(0, 10000)))
            f.write(" ")
    else:
        for i in range(num_inputs):
            for j in range(d):
                f.write(str(random.uniform(0.0, 10000.0)))
                f.write(" ")