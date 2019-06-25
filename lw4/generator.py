import sys
import random

# следующее значение
def get_next(last):
    ch = ord('b')
    limit = [ch for i in range(4)]
    if last[0] == ch:
        if last == limit:
            return []
    last[3] += 1
    for i in reversed(range(1,4)):
        if last[i] > ch:
            last[i-1] += 1
            last[i] = ord('a')
    return last
    
# переводим список аски в буквочки
def to_str(lst):
    return [chr(x) for x in lst]

# записываем lst в перемешку с переводами строк в файл 
def wr_rand(file, lst):
    lc = 0
    wc = 0
    for word in lst:
        file.write(word)
        file.write(' ')
        wc += 1
        m = random.randrange(0, 10)
        if m == 0:
            c = random.randint(1, 6)
            for i in range(c):
                file.write('\n')
                lc += 1
            wc = 0
        else:
            file.write(' ')
    # возвращаем сколько переводов строки произошло и сколько слов уже на последней строке
    return (lc, wc)

s = init = [ord('a') for i in range(4)]

test = open(sys.argv[1], "w")
ans = open(sys.argv[2], "w")
count = int(sys.argv[3])

line_num = 1    # число строк в файле
word_num = 0    # число слов от начала строки
c = 0           # длина паттерна

# генерируем паттерн
lst = []
while True:
    c += 1
    lst.append(''.join(to_str(s)))
    s = get_next(s)
    if s == []:
        break

# пишем паттерн в начало файла
for word in lst:
    test.write(word)
    if(word != lst[-1]):
        test.write(' ')
    else:
        test.write('\n')

for i in range(count):
    flag = False
    while True:
        s = init
        r = random.randrange(0, 9)
        if r == 0:
            # пишем весь паттерн
            if not flag:
                flag = True
                # записываем в файл ответов координаты вхождения
                ans.write(str(line_num) + ', ' + str(word_num + 1) + '\n')
                (lc, wc) = wr_rand(test, lst)
                if(lc == 0):
                    word_num += wc
                else:
                    word_num = wc
                line_num += lc
            else:
                break
        else:
            # пишем куски паттерна
            q = random.randrange(0,c)
            temp = lst[0:q]
            (lc, wc) = wr_rand(test, temp)
            if(lc == 0):
                word_num += wc
            else:
                word_num = wc
            line_num += lc

test.close()
ans.close()
