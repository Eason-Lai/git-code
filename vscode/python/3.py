dict = {'河北':'石家庄','江苏':'南京','吉林':'长春','江西':'南昌'}
str = input('请输入省名:（如：河北，江苏，吉林，江西)【输入0退出】')
while str != '0':
    print(str+'的省会为：'+dict[str])
    str = input('请输入省名:（如：河北，江苏，吉林，江西)【输入0退出】')
