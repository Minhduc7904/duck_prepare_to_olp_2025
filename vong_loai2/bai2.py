BASE = 1000000
DIGIT = 6
MAXN = 160

class BigNum:
    def __init__(self):
        self.a = [0] * 31

a = [BigNum() for _ in range(MAXN + 1)]

def multi(i):
    mem = 0
    x = 4 * i - 2
    a[i].a[0] = a[i-1].a[0]
    for j in range(1, a[i].a[0] + 1):
        t = a[i-1].a[j] * x + mem
        a[i].a[j] = t % BASE
        mem = t // BASE
    if mem > 0:
        a[i].a[0] += 1
        a[i].a[a[i].a[0]] = mem

def divide(i):
    mem = 0
    k = i + 1
    t = BigNum()
    for j in range(a[i].a[0], 0, -1):
        x = a[i].a[j] + mem * BASE
        if x < k:
            mem = x
        else:
            t.a[j] = x // k
            mem = x % k
    
    j = a[i].a[0]
    while j >= 1:
        if t.a[j] > 0:
            break
        j -= 1
    
    a[i].a[0] = j
    for j in range(1, a[i].a[0] + 1):
        a[i].a[j] = t.a[j]

def init():
    a[0].a[0] = 1
    a[0].a[1] = 1
    for i in range(1, MAXN + 1):
        multi(i)
        divide(i)

def print_out(re):
    for i in range(re.a[0], 0, -1):
        if i < re.a[0]:
            print(str(re.a[i]).zfill(DIGIT), end='')
        else:
            print(re.a[i], end='')
    print()

def main():
    init()
    while True:
        n = int(input())
        if n == -1:
            break
        print_out(a[n])

if __name__ == "__main__":
    main()