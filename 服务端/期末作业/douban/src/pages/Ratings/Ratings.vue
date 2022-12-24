<template>
  <div>
    <div class="header">Top50电影的评分分布图</div>
    <div id="echart1"></div>
    <div id="echart2"></div>
  </div>
</template>

<script>
import axios from "axios";
import * as echarts from "echarts";
export default {
  name: "Rating",
  data() {
    return {
      data: [],
    };
  },
  methods: {
    async getData() {
      console.log("请求中。。。");
      await axios
        .get("http://127.0.0.1:5000/movie")
        .then((response) => {
          this.data = response.data.data;
          console.log(this.data);
        })
        .catch((err) => {
          console.log(err);
        });
      console.log("请求完成");
      this.createChart();
    },
    createChart() {
      var myChart = echarts.init(document.getElementById("echart1"));
      var myChart1 = echarts.init(document.getElementById("echart2"));
      let x = [];
      let y = [];
      for (let i of this.data) {
        x.push(i[0]);
        y.push(i[3]);
      }
      let option = {
        title:{
          text:'电影评分表'
        },
        tooltip: {
          trigger: "axis",
          axisPointer: {
            type: "line",
            lineStyle: {
              color: "red",
            },
          },
        },
        xAxis: {
          type: "category",
          data: x,
        },
        yAxis: {
          type: "value",
        },
        series: [
          {
            data: y,
            type: "line",
          },
        ],
      };
      let option2 = {
          tooltip: {
          trigger: "axis",
          axisPointer: {
            type: "line",
            lineStyle: {
              color: "red",
            },
          },
        },
        xAxis: {
          type: "category",
          data: x,
        },
        yAxis: {
          type: "value",
        },
        series: [
          {
            data: y,
            type: "bar",
            showBackground: true,
            backgroundStyle: {
              color: "rgba(180, 180, 180, 0.2)",
            },
          },
        ],
      };
      myChart.setOption(option);
      myChart1.setOption(option2)
    },
  },
  mounted() {
    this.getData();
  },
};
</script>

<style lang='scss' scoped>
.header {
  height: 50px;
  width: 100%;
  line-height: 50px;
  font-size: 30px;
  text-align: center;
  font-weight: 600;
}
#echart1 {
  width: 80%;
  margin: 10px auto;
  height: 500px;
}
#echart2{
  width: 80%;
  margin: 10px auto;
  height: 500px;
}
</style>