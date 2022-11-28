a = input()

#测试输入的合法性
if not a.isnumeric():
    print("输入不合法")
    exit()

class Dfs:
    operators = ['+','-','*','/','']
    count = 0
    def __init__(self, stra):
        self.lista = list(stra) #转化为列表方便进行操作符的增加和删除
        self.numa = len(stra)-1 #第一个数字能插入操作符的个数

    def dfsa(self): #利用回溯算法查找所有的可能性
        if self.numa == 0: #代表操作符插入完毕 可以进行下一步比值操作
            stra = ''.join(self.lista) #完成字符串拼接
            result = eval(stra) #利用eval函数计算拼接的字符串的值
            if result == 24:
                self.count = self.count + 1
                print(stra,'=',24)
            #插入括号
            self.insertBracket()
            return
        for operator in self.operators:
            self.lista.insert(self.numa, operator)
            self.numa = self.numa - 1
            self.dfsa()  # 递归
            # 恢复现场
            self.numa = self.numa + 1
            del self.lista[self.numa]


    def insertBracket(self):
        #有四个数 插入括号的位置情况
        list4 = [
            [0,4],
            [0,6],
            [2,6],
            [2,8],
            [4,8],
            [0,4,6,10],
            [0,4,1,8],
            [0,6,3,7],
            [2,8,3,7],
            [2,8,5,9]
        ]
        if len(''.join(self.lista)) == 7:
            for i in list4:
                listTemp = self.lista #python 默认是浅拷贝
                # len(i) == 2 表示插入一个括号
                if len(i) == 2:
                    listTemp.insert(i[0],'(')
                    listTemp.insert(i[1],')')
                    res = ''.join(listTemp)
                    # print(res)
                    if eval(res) == 24:
                        self.count = self.count+1
                        print(res,'= 24')
                    del listTemp[i[1]]
                    del listTemp[i[0]]
                # 表示插入两个个括号
                else:
                    listTemp.insert(i[0],'(')
                    listTemp.insert(i[1],')')
                    listTemp.insert(i[2],'(')
                    listTemp.insert(i[3],')')
                    res = ''.join(listTemp)
                    # print(res)
                    if eval(res) == 24:
                        self.count = self.count + 1
                        print(res,'= 24')
                    del listTemp[i[3]]
                    del listTemp[i[2]]
                    del listTemp[i[1]]
                    del listTemp[i[0]]

        if len(''.join(self.lista)) == 6:
            #只有三个数的情况 如 12+3+4
            #分三种情况对应插入括号的位置
            dict = {
                1: [0, 6, 4, 8],
                3: [0, 6, 2, 8],
                5: [0, 4, 2, 8]
            }
            listTemp = self.lista
            #通过 '' 字符的位置来取对应插入括号的位置
            list3 = dict[listTemp.index('')]
            for i in [0,2]:
                listTemp.insert(list3[0+i], '(')
                listTemp.insert(list3[1+i], ')')
                res = ''.join(listTemp)
                if eval(res) == 24:
                    self.count = self.count + 1
                    print(res, '= 24')
                del listTemp[list3[1+i]]
                del listTemp[list3[0+i]]
obj = Dfs(a)
obj.dfsa()
if obj.count == 0:
    print('无解！')
else:
    print(f"一共{obj.count}种解法")
