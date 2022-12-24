<template>
  <div>
    <div class="header">Top50的电影</div>
      <div class="box">
        <ul>
          <li v-for="(item,index) in data" :key="index" class="content">
            <a :href="item[1]">
              <span class="text">{{item[0]}}</span>
              <!-- <img :src="item[2]"> -->
              <span class="text">{{item[4]}}</span>
            </a>
          </li>
        </ul>
      </div>
  </div>
</template>

<script>
import axios from 'axios'
export default {
    name:'movie',
    data(){
      return {
        data:[]
      }
    },
    mounted(){
        this.getData()
    },
    methods:{
     async getData(){
          console.log("请求中。。。")
          await  axios.get('http://127.0.0.1:5000/movie')
                  .then((response)=>{
                    this.data=response.data.data
                    console.log(this.data)
                  })
                  .catch((err)=>{
                    console.log(err)
                  })
          console.log("请求完成")
      }
    }
}
</script>

<style lang='scss' scoped>
.header{
  height: 50px;
  width: 100%;
  line-height: 50px;
  font-size: 30px;
  text-align: center;
  font-weight: 600;
}
.box{
  margin: 50px auto;
  width: 80%;
  ul{
    width: 100%;
     display: flex;
     justify-content: space-between;
     flex-wrap: wrap;
    .content{
      display: block;
      width: 23%;
      margin: 5px;
      height: 200px;
      text-align: center;

      a{ 
        border-radius: 10px;
        cursor: pointer;
        display: block;
        width: 100%;
        height: 200px;
        box-shadow: 0 0 5px #ccc;
        overflow: hidden;
        .text{
          display: block;
          width: 100%;
          height: 20px;
          line-height: 20px;
          text-align: center;
          margin:30px 0;
        }
      }
    }
  }
}
</style>