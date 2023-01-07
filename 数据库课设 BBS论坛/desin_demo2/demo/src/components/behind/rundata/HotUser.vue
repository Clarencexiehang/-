<template>
	<div class="artRg">
		<div class="d2">
			<div id="userRegNum" style="width: 100%; height: 100%;">
			</div>
		</div>
		<div class="d1">
			<div id="userHotbar" style="width: 50%; height: 100%;">
			</div>
			<div id="userHotpie" style="width: 50%; height: 100%;">
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
			
			var usrHt = document.getElementById('userHotbar');
			var myChart = echarts.init(usrHt);
			var option1;
			
			option1 = {
			  color: ['#0950c2','#03541e'],
			  title: {
			    text: '文章热度'
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
			    data: ['用户1', '用户2', '用户3', '用户4', '用户5', '用户6']
			  },
			  series: [
			    {
			      name: '关注量',
			      type: 'bar',
			      data: [18, 23, 29, 10, 13, 63]
			    },
			    {
			      name: '粉丝量',
			      type: 'bar',
			      data: [19, 23, 31, 12, 13, 68]
			    }
			  ]
			};
			
			option1 && myChart.setOption(option1);
			
			
			var usrPie = document.getElementById('userHotpie');
			var myChart2 = echarts.init(usrPie);
			var option2;
			
			option2 = {
			  color: ['#c20521','#0b5449','#00ffff','#0000ff','#aaaa00','#03541e'],
			  title: {
			    text: '关注量比'
			  },
			  tooltip: {
			    trigger: 'item'
			  },
			  legend: {
			    top: '5%',
			    left: 'center'
			  },
			  series: [
			    {
			      name: '关注比',
			      type: 'pie',
			      radius: ['40%', '70%'],
			      avoidLabelOverlap: false,
			      itemStyle: {
			        borderRadius: 10,
			        borderColor: '#fff',
			        borderWidth: 2
			      },
			      label: {
			        show: false,
			        position: 'center'
			      },
			      emphasis: {
			        label: {
			          show: true,
			          fontSize: 40,
			          fontWeight: 'bold'
			        }
			      },
			      labelLine: {
			        show: false
			      },
			      data: [
			        { value: 0.1, name: '用户1' },
			        { value: 0.3, name: '用户2' },
			        { value: 0.2, name: '用户3' },
			        { value: 0.1, name: '用户4' },
			        { value: 0.1, name: '用户5' },
					{ value: 0.2, name: '用户6' }
			      ]
			    }
			  ]
			};
			
			option2 && myChart2.setOption(option2);
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
	#userHotpie{
		flex: 1;
	}
	#userFanpie{
	
	}
	
	.d2{
		display: flex;
		flex-direction: row;
		justify-content: flex-start;
		
		width: 100%;
		height: 50%;
	}
</style>