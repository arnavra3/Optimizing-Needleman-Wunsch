import matplotlib.pyplot as plt

for file in ["data.txt", "data1.txt", "data2.txt", "data3.txt", "data4.txt", "data5.txt", "data6.txt", "data7.txt"]:
    with open(file, "r") as f:
        lines = f.readlines()

        x = []
        y = []
        for line in lines:
            y.append(float(line.split(" ")[1]))
            x.append(float(line.split(" ")[0]))

        plt.plot(x, y)

plt.xlabel("n")
plt.ylabel("Execution speed")
plt.title("Execution speed vs n")
plt.legend(["column", "row", "Anti-Diagonal", "Parallelized Anti-Diagonal unroll", "Tiling", "Tiling with parallelization inside tile", "Tiling with parallelization for choosing tile", "Tiling with double parallelization"])

plt.show()
