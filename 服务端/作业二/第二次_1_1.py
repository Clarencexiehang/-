import copy

a = input('data 1:')
b = input('data 2:')
c = input('data 3:')
d = input('data 4:')
global count
count=0
datalist = [a,b,c,d]

# print(not a.isnumeric(), not b.isnumeric() , not c.isnumeric() , not d.isnumeric())
# #测试输入的合法性
# if not a.isnumeric() or not b.isnumeric() or not c.isnumeric() or not d.isnumeric():
#     print("输入不合法")
#     exit()

try:
    # 检查小数,和整数
    float(a)
    float(b)
    float(c)
    float(d)
except:
    print("输入不合法")
    exit()

class Dfs:
    operators = ['+','-','*','/']
    global count
    def __init__(self, datalist):
        self.lista = datalist #转化为列表方便进行操作符的增加和删除
        self.numa = 3 #第一个数字能插入操作符的个数

    def dfsa(self): #利用回溯算法查找所有的可能性
        global count
        if self.numa == 0: #代表操作符插入完毕 可以进行下一步比值操作
            stra = ''.join(self.lista) #完成字符串拼接
            print(stra)
            try:
                result = eval(stra) #利用eval函数计算拼接的字符串的值
                if result == 24:
                    count = count + 1
                    print(stra,'=',24)
            except:
                pass
            #插入括号
            self.insertBracket()
            return
        for operator in self.operators:
            self.lista.insert(self.numa, operator)
            str1 = "".join(self.lista)
            print(str1)
            self.numa = self.numa - 1
            self.dfsa()  # 递归
            # 恢复现场
            self.numa = self.numa + 1
            del self.lista[self.numa]
    def insertBracket(self):
        global count
        #有四个数 插入括号的位置情况  如：list4=[ 12 , +, 0, +, 0, +, 2 ]
        list4 = [
            [0,4],   # ( 12 + 0 )+ 0 + 2
            [0,6],   # ( 12 + 0 + 0 ) + 2
            [2,6],   # 12 + ( 0 + 0 )+ 2
            [2,8],   # 12 + ( 0 + 0 + 2 )
            [4,8],   # 12 + 0 + ( 0 + 2 )
            [0,4,6,10],# ( 12 + 0 ) + 0 + 2    ( 12 + 0 ) + ( 0 + 2 )
            [0,4,1,8], # ( 12 + 0 ) + 0 + 2    ( ( 12 + 0 ) + 0 ) + 2
            [0,6,3,7], # ( 12 + 0  + 0 ) + 2   ( 12 + ( 0  + 0  ) ) + 2
            [2,8,3,7], #  12 + ( 0 + 0 + 2 )   12 + ( ( 0 + 0 ) + 2 )
            [2,8,5,9]  # 12 + ( 0 + 0 + 2 )    12 + ( 0 + ( 0 + 2 ) )
        ]
        for i in list4:
            listTemp = self.lista #python 默认是浅拷贝
            # len(i) == 2 表示插入一个括号
            if len(i) == 2:
                listTemp.insert(i[0],'(')
                listTemp.insert(i[1],')')
                res = ''.join(listTemp)
                print(res)
                try:
                    if eval(res) == 24:
                        count = count+1
                        print(res,'= 24')
                except Exception as e:
                    pass
                    # print("除零异常")
                del listTemp[i[1]]
                del listTemp[i[0]]
            # 表示插入两个个括号
            else:
                listTemp.insert(i[0],'(')
                listTemp.insert(i[1],')')
                listTemp.insert(i[2],'(')
                listTemp.insert(i[3],')')
                res = ''.join(listTemp)
                print(res)
                try:
                    if eval(res) == 24:
                        count = count+1
                        print(res,'= 24')
                except Exception as e:
                    pass
                del listTemp[i[3]]
                del listTemp[i[2]]
                del listTemp[i[1]]
                del listTemp[i[0]]

#让列表全排列
def allPermutation(arr, next):
    # 当next=len(arr)-1时,此时只剩下一个数要排列,直接就是结果
    if next == len(arr) - 1:
        obj = Dfs(arr)
        obj.dfsa()
    else:
        # 从第next+1个数开始,每个数与第next+1的数进行一次交换(包括自己)    12 ， 0 ， 0 ， 2
        for i in range(next, len(arr)):
            # 深拷贝,避免影响到原来的排列情况
            update_permutation = copy.deepcopy(arr)
            update_permutation[i], update_permutation[next] = update_permutation[next], update_permutation[i]
            allPermutation(update_permutation, next + 1)


allPermutation(datalist, 0)
if count == 0:
    print('无解！')
else:
    print(f"一共{count}种解法")


