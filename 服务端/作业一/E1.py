# @Time : 2022/10/28 11:57

a = input()
b = input()

#测试输入的合法性
if not a.isnumeric() or not b.isnumeric():
    print("输入不合法！")
    exit()

class Dfs:
    operators = ['+', '-', '']
    count = 0
    resulta = None
    def __init__(self, stra, strb):
        self.lista = list(stra) #转化为列表方便进行操作符的增加和删除
        self.listb = list(strb)
        self.numa = len(stra)-1 #第一个数字能插入操作符的个数
        self.numb = len(strb)-1 #第二个数字能插入操作符的个数

    def dfsa(self): #利用回溯算法查找所有的可能性
        if self.numa == 0: #代表操作符插入完毕 可以进行下一步比值操作
            stra = ''.join(self.lista) #完成字符串拼接
            self.resulta = eval(stra) #利用eval函数计算拼接的字符串的值
            self.dfsb() #对第二个字符串进行同样的操作
            return
        for operator in self.operators:
            self.lista.insert(self.numa, operator)
            self.numa = self.numa - 1
            self.dfsa()  # 递归
            # 恢复现场
            self.numa = self.numa + 1
            del self.lista[self.numa]

    def dfsb(self):
        if self.numb == 0:
            strb = ''.join(self.listb)
            if eval(strb) == self.resulta:
                stra = ''.join(self.lista)
                self.count = self.count + 1
                print(stra,"=",strb,"=",self.resulta)
            return
        for operator in self.operators:
            self.listb.insert(self.numb, operator)
            self.numb = self.numb - 1
            self.dfsb()  # 递归
            # 恢复现场
            self.numb = self.numb + 1
            del self.listb[self.numb]

obj = Dfs(a, b)
obj.dfsa()
if obj.count == 0:
    print('无解！')
else:
    print(f"一共{obj.count}种解法")

# list1 = ['',1,3,4,5,' ',7]
# list1.insert(2,'')
# list2 = [item for item in list1 if item!=' ']
# print(list1)