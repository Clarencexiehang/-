<template>
  <div>
      <div id="topbox">
          <div class="left">
              ZhouJun
          </div>
          <div class="right">
              <router-link to='/home' active-class="on" class='items'>首页</router-link>
              <router-link to='/movies' class='items' active-class="on">电影</router-link>
              <router-link to='/rating' class='items' active-class="on">评分</router-link>
              <router-link to='/word' class='items' active-class="on">词云</router-link>
              <router-link to='/us' class='items' active-class="on">团队</router-link>
          </div>
      </div>
  </div>
</template>

<script>
export default {
    name:'top',
    data(){
        return{
            width:window.screen.width
        }
    }
}
</script>

<style lang='scss'>
#topbox{
    margin-top: 20px;
    width:100%;
    height: 50px;
    display: flex;
    justify-content: space-around;
    .right{
        display: flex;
        width: 40%;
        justify-content: center;
        .items{
            height: 50px;
            line-height: 50px;
            text-align: center;
            color: #2c3e50;
            font-size: 16px;
            width: 25%;
            text-decoration: none;
        }
        .on{
            color: #02a774;
            border: none;
            text-decoration: none;
            font-size: 18px;
        }
    }
    .left{
        width: 20%;
        height: 50px;
        line-height: 50px;
        font-size: 30px;
        text-align: center;
        color: #2c3e50;
        margin-left:-50px;
    }
}
#topbox2{
    margin-top: 10px;
    width:100%;
    height: 50px;
    display: flex;
    justify-content: space-around;
    .right{
        display: flex;
        width: 60%;
        justify-content: center;
        .items{
            height: 50px;
            line-height: 50px;
            text-align: center;
            color: #2c3e50;
            font-size: 16px;
            width: 25%;
            text-decoration: none;
        }
        .on{
            color: #02a774;
            border: none;
            text-decoration: none;
            font-size: 18px;
        }
    }
    .left{
        width: 20%;
        height: 50px;
        line-height: 50px;
        font-size: 20px;
        text-align: center;
        color: #2c3e50;
        margin-left: 10px;
    }
}
</style>