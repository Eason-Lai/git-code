arr1 = [int(n) for n in input('请输入同学一的三门成绩').split()]
arr2 = [int(n) for n in input('请输入同学二的三门成绩').split()]
arr3 = [int(n) for n in input('请输入同学三的三门成绩').split()]
sum = 0
for n in arr1:
    sum = sum + n
print('同学一的成绩为:',sum)
sum = 0
for n in arr2:
    sum = sum + n
print('同学二的成绩为:',sum)
sum = 0
for n in arr3:
    sum = sum + n
print('同学三的成绩为:',sum)
i = 0
subject = [0,0,0]
while i < 3:
    subject[i] = (arr1[i] + arr2[i] + arr3[i]) / 3
    i = i + 1
print('三门课程平均分别为:',subject[0],subject[1],subject[2])