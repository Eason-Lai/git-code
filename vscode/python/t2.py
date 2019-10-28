
USD_VS_RMB = 6.7

currency_str_value = input("请输入带单位的货币金额（退出程序请输入Q）：")

while currency_str_value != 'Q':
    unit = currency_str_value[-3:]
    if unit == 'CNY':
        rmb_str_value = currency_str_value[0:-3]
        rmb_value = eval(rmb_str_value)
        usd_value = rmb_value/USD_VS_RMB
        print('美元（USD）金额是：',usd_value)
    elif unit == 'USD':
        usd_str_value = currency_str_value[0:-3]
        usd_value = eval(usd_str_value)
        rmb_value = usd_value*USD_VS_RMB
        print('人民币（RMB）金额是：',rmb_value)
    else :
        print('目前版本尚不支持的功能')
    currency_str_value = input("请输入带单位的货币金额（退出程序请输入Q）：")
print('程序已退出!')