import random as rd
def gendata(n:int,m:int,online:bool=False)->tuple[str,str]:
    """
    生成一份测试数据，返回输入输出字符串
    online:是否为强制在线，为未来保留
    输出数据暂时为None，为保留的功能
    """
    input_str=""
    input_str+=f"{n} {m}\n"
    arr=[i for i in range(1,n+1)]
    rd.shuffle(arr)
    input_str+=" ".join(map(str,arr))+"\n"
    for _ in range(m):
        l,r=rd.randint(1,n),rd.randint(1,n)
        input_str+=f"{min(l,r)} {max(l,r)}\n"
    return (input_str,None)

if __name__=="__main__":
    print(gendata(int(1e5),int(1e5))[0])