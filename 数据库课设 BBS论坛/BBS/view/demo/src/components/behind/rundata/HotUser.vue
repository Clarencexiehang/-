<template>
	<div class="artRg">
		<div class="d2">
			<div id="userRegNum" style="width: 100%; height: 100%;">
			</div>
		</div>
		<div class="d1">
			<div id="userHotbar" style="width: 50%; height: 100%;">
			</div>
		</div>
	</div>
</template>

<script>
	import * as echarts from 'echarts'
	import axios from 'axios'
	
	export default{
		name:'HotUser',
		data() {
			return{}
		},
		mounted() {
			axios({
				url:'http://127.0.0.1:5000/admin/hotuser',
				method:'post'
			}).then((response)=>{
				var hotUser=response.data.hotUser;
				console.log(hotUser);
				
				var usename=Object.keys(hotUser);
				var hotn=[];
				for(var i=0;i<Object.values(hotUser).length;i++){
					hotn.push(Object.values(hotUser)[i].hotN);
				}

				var usrRgNum = document.getElementById('userRegNum');
				var myChart3 = echarts.init(usrRgNum);
				var option3;
				
				option3 = {
				  title:{
					text:'今日文章数'	
				  },
				  color:['#0000ff'],
				  xAxis: {
				    type: 'category',
				    data: usename
				  },
				  yAxis: {
				    type: 'value'
				  },
				  series: [
				    {
				      data: hotn,
				      type: 'line'
				    }
				  ]
				};
				
				option3 && myChart3.setOption(option3);
				
			}).catch((error)=>{
				
			})
			
			
			
			axios({
				url:'http://127.0.0.1:5000/admin/sumofreply',
				method:'get'
			}).then((response)=>{
				console.log('---------------- sumofreply ----------------');
				console.log(response.data);
				var userAct=response.data.userAct;
				
				var acc=[];
				var repNum=[];
				var colleNum=[];
				for(var i=0;i<userAct.length;i++){
					acc.push(userAct[i].accountname);
					repNum.push(userAct[i].repNum);
					colleNum.push(userAct[i].colleNum);
				}
				
				var usrHt = document.getElementById('userHotbar');
				var myChart = echarts.init(usrHt);
				var option1;
				
				option1 = {
				  color: ['#0950c2','#03541e'],
				  title: {
				    text: '用户今日活跃度'
				  },
				  tooltip: {
				    trigger: 'axis',
				    axisPointer: {
				      type: 'shadow'
				    }
				  },
				  legend: {},
				  grid: {
				    left: '3%',
				    right: '4%',
				    bottom: '3%',
				    containLabel: true
				  },
				  xAxis: {
				    type: 'value',
				    boundaryGap: [0, 0.01]
				  },
				  yAxis: {
				    type: 'category',
				    data: acc
				  },
				  series: [
				    {
				      name: '收藏量',
				      type: 'bar',
				      data: repNum
				    },
				    {
				      name: '评论量',
				      type: 'bar',
				      data: colleNum
				    }
				  ]
				};
				
				option1 && myChart.setOption(option1);
				
			}).catch((error)=>{
				
			})
		}
	}
</script>

<style scoped>
	.artRg{
		display: flex;
		flex-direction: row;
		justify-content: flex-start;
		align-items: flex-start;
		flex-wrap: wrap;
		
		width: 100%;
		height: 100%;
		background-color: white;
		
		border: 0.7px solid rgb(235, 235, 235);
		border-radius: 5px 5px;
		box-shadow: -2px -2px 0.5em gray;
	}
	.d1{
		display: flex;
		flex-direction: row;
		justify-content: flex-start;
		
		width: 100%;
		height: 50%;
	}
	#userHotbar{
		flex: 1;
	}
	#userallHotbar{
		flex: 1;
	}
	
	.d2{
		display: flex;
		flex-direction: row;
		justify-content: flex-start;
		
		width: 100%;
		height: 50%;
	}
</style>