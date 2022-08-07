import matplotlib.pyplot as plt

iteration = []
score = []

s=''

while True:
    s = str(input())
    s.strip()
    if s == '':
        break
    vals = s.split(' ')
    iteration.append(float(vals[0]))
    score.append(float(vals[1]))

plt.plot(iteration, score)
plt.grid(color='green', linestyle='--', linewidth = 0.5)
plt.ylim((0, 7000))
plt.show()

