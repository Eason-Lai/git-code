i = 1
sum1 = 0
sum2 = 0
sum3 = 0
sum4 = 0
while i <= 100 :
    sum1 = sum1 + i
    if i % 2 == 1:
        sum2 = sum2 + i
    if i % 2 == 0:
        sum3 = sum3 + i
    if i % 3 == 0:
        sum4 = sum4 + i
    i = i + 1
print('[1,100]所有数字和为',sum1)
print('[1,100]所有奇数和为',sum2)
print('[1,100]所有偶数和为',sum3)
print('[1,100]所有能被3整除的数和为',sum4)
