class WebSite:
    def __init__(self, site, visit_num):
        self.site = site
        self.visit_num = visit_num


class TimeBucket:
    def initFun(self, uid, day, period, site, visit_time,lastTime):
        self.uid=uid
        self.day = day
        self.period=period
        self.site=site
        self.visit_time=visit_time
        self.lastTime=lastTime          #上一次加入的t

    def __init__(self,site, visit_time):
        self.site=site
        self.visit_time=visit_time

class DecisionNode:
    def __init__(self, web,num,isVisit,maxPeriod):
        self.web=web
        self.num=num
        self.isVisited=isVisit
        self.maxPeriod=maxPeriod