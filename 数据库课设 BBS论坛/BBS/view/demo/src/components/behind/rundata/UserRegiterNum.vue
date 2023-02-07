<template>
	<div class="userRg">
		<div class="d1">
			<div id="userHotbar" style="width: 50%; height: 100%;">
			</div>
			<div id="userHotpie" style="width: 50%; height: 100%;">
			</div>
		</div>
		<div class="d2">
			<div id="userRegNum" style="width: 100%; height: 100%;">
			</div>
		</div>
	</div>
</template>

<script>
	import axios from 'axios';
	import * as echarts from 'echarts'
	
	export default{
		name:'UserRegiterNum',
		data() {
			return {};
		},
		beforeMount() {
			//  **************************** 用户热度请求
			axios({
				url:'http://127.0.0.1:5000/admin/userdata',
				method:'post',
				data:{
					type:'usehot'
				}
			}).then((response)=>{
				console.log(response.data.userHot);	
				
				//  *********** 用户粉丝数、文章数
				var userHotList=response.data.userHot;
				
				var usrHt = document.getElementById('userHotbar');
				var myChart = echarts.init(usrHt);
				var option1;
				
				var nicknameList=[];
				var carenumList=[];
				var articlenumList=[];
				for(var i=0;i<userHotList.length;i++){
					nicknameList.push(userHotList[i].nickname);
					carenumList.push(userHotList[i].carenum);
					articlenumList.push(userHotList[i].articlenum);
				}
				
				option1 = {
				  color: ['#0950c2','#03541e'],
				  title: {
				    text: '用户热度'
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
				    data: nicknameList
				  },
				  series: [
				    {
				      name: '文章数',
				      type: 'bar',
				      data: articlenumList
				    },
				    {
				      name: '粉丝量',
				      type: 'bar',
				      data: carenumList
				    }
				  ]
				};
				
				option1 && myChart.setOption(option1);
			
			
				//  *********** 用户粉丝占比
				var fanSum=0;
				for(var i=0;i<userHotList.length;i++){
					fanSum=fanSum+userHotList[i].carenum;
				}
				var data=[];
				for(var i=0;i<userHotList.length;i++){
					var v=(userHotList[i].carenum)/fanSum;
					
					var ud={ 
							value: Math.round(v*Math.pow(10,2))/Math.pow(10,2), //将小数保留2位
							name: userHotList[i].nickname
						}
					data.push(ud);
				}
				
				var usrPie = document.getElementById('userHotpie');
				var myChart2 = echarts.init(usrPie);
				var option2;
				
				option2 = {
				  color: ['#c20521','#0b5449','#00ffff','#0000ff','#aaaa00','#03541e'],
				  title: {
				    text: '粉丝占比'
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
				      name: '粉丝占比',
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
				      data: data
				    }
				  ]
				};
				
				option2 && myChart2.setOption(option2);
			}).catch((error)=>{
				
			})
		},
		mounted() {
			//  **************************** 月用户注册量请求
			axios({
				url:'http://127.0.0.1:5000/admin/userdata',
				method:'post',
				data:{
					type:'regNumOfMonth'
				}
			}).then((response)=>{
				var regNumOfMonth=response.data.regN;
				
				var usrRgNum = document.getElementById('userRegNum');
				var myChart3 = echarts.init(usrRgNum);
				var option3;
				
				var data=[]
				for(var i=1;i<=regNumOfMonth.length;i++){
					data.push(regNumOfMonth[i]);
				}
				
				option3 = {
				  title:{
					text:'用户注册时间'	
				  },
				  color:['#0000ff'],
				  xAxis: {
				    type: 'category',
				    data: ['1月', '2月', '3月', '4月', '5月', '6月', '7月','8月','9月','10月','11月','12月']
				  },
				  yAxis: {
				    type: 'value'
				  },
				  series: [
				    {
				      data: data,
				      type: 'line'
				    }
				  ]
				};
				
				option3 && myChart3.setOption(option3);
				
			}).catch((error)=>{
				
			})
		}
		  
	}
</script>

<style scoped>
	.userRg{
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