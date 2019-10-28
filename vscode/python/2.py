arr1 = [int(n) for n in input('请输入向量一').split()]
arr2 = [int(n) for n in input('请输入向量二').split()]
sum = 0
result = 0
i = 0
while i < len(arr1):
    sum = sum + (arr1[i]-arr2[i])**2
    i = i + 1
result = sum**0.5
print(result)