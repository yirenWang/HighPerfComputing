import matplotlib.pyplot as plt

lines = open('data.txt').readlines()
lines_1 = open('data_1_proc.txt').readlines()
data = [] # [] of [time_taken, pi calculated, error, time_taken_1_proc]  
for i in range(len(lines)):
    l = lines[i]
    data.append([10000*i] + [float(x) for x in l.strip("\n").split("++")] + [[float(x) for x in lines_1[i].strip("\n").split("++")][0]] )

# Pi estimate
plt.plot([x[0] for x in data], [x[2] for x in data])
plt.plot([x[0] for x in data], [3.14159265359 for x in data])
plt.axis([0, 5000000, 3.14, 3.142])
plt.ylabel('pi estimate')
plt.xlabel('number of trapezoids')
plt.show()

# Pi estimate zoomed in
plt.plot([x[0] for x in data], [x[2] for x in data])
plt.plot([x[0] for x in data], [3.14159265359 for x in data])
plt.axis([0, 1000000, 3.14, 3.142])
plt.ylabel('pi estimate')
plt.xlabel('number of trapezoids')
plt.show()


# Time taken
plt.plot([x[0] for x in data], [x[1] for x in data])
plt.plot([x[0] for x in data], [x[-1] for x in data])
plt.axis([0, 7600000, 0, 0.75])
plt.ylabel('time taken (s)')
plt.xlabel('number of trapezoids')
plt.show()
