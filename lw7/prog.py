import numpy as np

def nums(n, m, l):
    vals = []
    for i in range(n, m+1):
        if i%l == 0:
            vals.append(i)
    print(vals)
    return len(vals)

def naive_solution(n, m):
    nums = 0
    for i in range(1,n):
        if str(i) < str(n) and i%m == 0:
            nums += 1
    return nums

for i in range(250):
    x = np.random.randint(100, 10**5)
    y = np.random.randint(1, 10**3)
    f=open("tests.txt", "a+")
    f.write(str(x))
    f.write(' ' + str(y) + '\n')
    f.close()
    ans = naive_solution(x, y)
    f=open("ans.txt", "a+")
    f.write(str(ans) + '\n')
    f.close()