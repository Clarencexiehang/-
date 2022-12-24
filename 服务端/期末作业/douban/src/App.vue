<template>
  <div id="app">
    <TopGuilder/>
    <router-view></router-view>
  </div>
</template>

<script>
import TopGuilder from './components/TopGuilder'

export default {
  name: 'App',
  components: {
    TopGuilder
  }
}
</script>

<style>
	
#app {
  text-align: center;
  margin: 0;
  text-decoration: none;
  width: 100%;
  height: 100%;
  margin:0px;
}
body {
/* 	color: white; */
/* 加载背景图 */
/* background-image: url('assets/sonos-sub-mini-3840x2160-abstract-dark-speakers-4k-24312.jpg'); */
/* 背景图垂直、水平均居中 */
background-position: center center;
/* 背景图不平铺 */
background-repeat: no-repeat;
/* 当内容高度大于图片高度时，背景图像的位置相对于viewport固定 */
background-attachment: fixed;
/* 让背景图基于容器大小伸缩 */
background-size: cover;
/* 设置背景颜色，背景图加载过程中会显示背景色 */

    /* opacity: 0.5; */
}
</style>
