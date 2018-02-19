import matplotlib.pyplot as plt

lines = open('data1/data.txt').readlines()[:50]
lines_1 = open('data1/data_1_proc.txt').readlines()[:50]
data = [] # [] of [time_taken, pi calculated, error, time_taken_1_proc]  
for i in range(len(lines)):
    l = lines[i]
    data.append([100*(i+1)] + [float(x) for x in l.strip("\n").split("++")] + [[float(x) for x in lines_1[i].strip("\n").split("++")][0]] )

# Error estimate
plt.plot([x[0] for x in data], [ x[3]*100 for x in data])
#plt.axis([0, 500000, float("1e-13"), float("1e-09")])
plt.ylabel('error estimate in %')
plt.xlabel('number of trapezoids')
plt.show()


# Time taken
plt.plot([x[0] for x in data], [x[1] for x in data])
plt.plot([x[0] for x in data], [x[-1] for x in data])
#plt.axis([0, 500000, 0, 0.75])
plt.ylabel('time taken (s)')
plt.xlabel('number of trapezoids')
plt.show()
