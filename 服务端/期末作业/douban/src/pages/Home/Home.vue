<template>
  <div id="box">
    <p class="title">豆瓣Top50数据分析</p>
    <div class="footer">
      应用Vue前端框架，python爬虫，Flask框架，Echarts，WorldCloud等技术
    </div>
    <div class="content" v-if="width>600">
      <ul>
        <li @click="gomovies">
          <span>
            <i class="iconfont icon-dianying items" style="color: #16a287"> </i>
          </span>
          <span class="text" style="color: #16a287">经典电影</span>
        </li>
        <li @click="goratings">
          <span>
            <i class="iconfont icon-tongji1 items" style="color: #c85cff"> </i>
          </span>
          <span class="text" style="color: #c85cff">评分统计</span>
        </li>
        <li @click="goword">
          <span>
            <i class="iconfont icon-tongji items" style="color: #ffb75a"> </i>
          </span>
          <span class="text" style="color: #ffb75a">词汇统计</span>
        </li>
        <li @click="gous">
          <span>
            <i class="iconfont icon-tuandui1 items" style="color: #43c6fe"> </i>
          </span>
          <span class="text" style="color: #43c6fe">团队</span>
        </li>
      </ul>
    
    </div>
    <div class="content1" v-else>
      <ul>
        <li @click="gomovies">
          <span>
            <i class="iconfont icon-dianying items" style="color: #16a287"> </i>
          </span>
          <span class="text" style="color: #16a287">经典电影</span>
        </li>
        <li @click="goratings">
          <span>
            <i class="iconfont icon-tongji1 items" style="color: #c85cff"> </i>
          </span>
          <span class="text" style="color: #c85cff">评分统计</span>
        </li>
        <li @click="goword">
          <span>
            <i class="iconfont icon-tongji items" style="color: #ffb75a"> </i>
          </span>
          <span class="text" style="color: #ffb75a">词汇统计</span>
        </li>
        <li @click="gous">
          <span>
            <i class="iconfont icon-tuandui1 items" style="color: #43c6fe"> </i>
          </span>
          <span class="text" style="color: #43c6fe">团队</span>
        </li>
      </ul>
    
    </div>
    
  </div>
</template>

<script>
export default {
  name: "home",
  data(){
    return{
      width:window.screen.width
    }
  },
  methods: {
    gomovies() {
      this.$router.push("/movies");
    },
    goratings() {
      this.$router.push("/rating");
    },
    goword() {
      this.$router.push("/word");
    },
    gous() {
      this.$router.push("/us");
    },
  },
};
</script>

<style lang='scss'>
#box {
  .title {
    color: #2c3e50;
    font-size: 30px;
    font-weight: 600;
    margin-top: 80px;
  }
  .footer {
    color: #2c3e50;
    width: 100%;
    height: 30px;
    line-height: 30px;
    text-align: center;
    font-size: 16px;
    margin-top: 20px;
  }
  .content {
    width: 80%;
    margin: 10px auto;
    ul {
      width: 100%;
      display: flex;
      background-color: #efefef;
      border-radius: 10px;
      margin-top: 30px;
      // min-width: 800px;
      flex-wrap: wrap;
      li {
        cursor: pointer;
        width: 16%;
        // min-width: 200px;
        height: 250px;
        margin: 50px;
        background-color: #fff;
        border-radius: 10px;
        .items {
          display: block;
          font-size: 70px;
          margin-top: 50px;
        }
        .text {
          font-size: 25px;
          display: block;
          margin-top: 20px;
          color: #2c3e50;
        }
      }
    }
  }
  .content1 {
    width: 80%;
    margin: 10px auto;
    ul {
      width: 100%;
      display: flex;
      background-color: #efefef;
      border-radius: 10px;
      margin-top: 50px;
      // min-width: 800px;
      flex-wrap: wrap;
      li {
        cursor: pointer;
        width: 43%;
        // min-width: 200px;
        height: 100px;
        margin: 10px ;
        background-color: #fff;
        border-radius: 10px;
        .items {
          display: block;
          font-size: 40px;
          margin-top: 10px;
        }
        .text {
          font-size: 20px;
          display: block;
          margin-top: 20px;
          color: #2c3e50;
        }
      }
    }
  }
}
</style>