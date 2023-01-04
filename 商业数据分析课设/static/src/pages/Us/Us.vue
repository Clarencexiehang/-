<template>
	<div class="box2">
		<div class="title">不同收入的网页浏览情况占比</div>
		<div class="box">
			<div class="header">
				<div :class="{activecss:type == index}" class="item" v-for="item,index in typedata" :key='index'
					@click="clickItem(index)">{{item}}</div>
			</div>
			<div class="echartBox">
				<div id="bingtu"></div>
				<div id="zhutu"></div>
			</div>

		</div>
	</div>

</template>

<script>
	import * as echarts from 'echarts';
	import axios from 'axios'
	export default {
		data() {
			return {
				typedata: ['三千', '三千到八千', '八千以上', ],
				type: 0,
				myChart: null,
				data: []
			}
		},
		methods: {
			clickItem(index) {
				this.type = index
				this.getdata()
			},
			async getdata() {
				let params = this.type
				await axios.get('http://127.0.0.1:5000/show/income_condition', {
					params: {
						type: params
					}
				}).then((res) => {
					// console.log(res.data.data)
					this.data = res.data.data
				}).catch((x) => {
					console.log(x)
				})
				this.createChart1()
				this.createChart2()
			},
			createChart1() {
				var myChart = echarts.init(document.getElementById("bingtu"));
				// 绘制图表

				var option;
				option = {

					title: {
						text: 'Referer of a Website',
						subtext: 'Fake Data',
						left: 'center'
					},
					tooltip: {
						trigger: 'item'
					},
					legend: {
						orient: 'vertical',
						left: 'left'
					},
					series: [{
						name: 'Access From',
						type: 'pie',
						radius: '50%',
						data: this.data,
						emphasis: {
							itemStyle: {
								shadowBlur: 10,
								shadowOffsetX: 0,
								shadowColor: 'rgba(0, 0, 0, 0.5)'
							}
						}
					}]
				};

				option && myChart.setOption(option);

			},
			createChart2() {
				var myChart = echarts.init(document.getElementById("zhutu"));
				var option;
				let x_data = []
				let y_data = []
				this.data.forEach(item => {
					var r = Math.floor(Math.random() * 256);
					var g = Math.floor(Math.random() * 256);
					var b = Math.floor(Math.random() * 256);
					var color = '#' + r.toString(16) + g.toString(16) + b
						.toString(16);
					x_data.push(item.name)
					let yObj = {
						value: item.value,
						itemStyle: {
							color: color
						}
					}
					y_data.push(yObj)
				})
				
				option = {
					xAxis: {
						type: 'category',
						data: x_data
					},
					yAxis: {
						type: 'value'
					},
					series: [{
						data: y_data,
						type: 'bar'
					}]
				};
				console.log(option)
				option && myChart.setOption(option);
			}
		},
		mounted() {
			this.getdata()
		}
	}
</script>

<style lang='scss' scoped>
	.title {
		margin: 10px 0;
		font-size: 25px;
		color: #00749B;
	}

	.box {
		width: 80%;
		margin: 0 auto;
		/* 		margin: 300px auto; */
		display: flex;
		/* flex-direction: column; */
		/* align-items: center; */

		.header {

			width: 200px;
			display: flex;
			flex-direction: column;
			justify-content: space-around;
			align-items: center;
			/* background-color: wheat; */
			margin-top: 30px;
			height: 300px;

			.item {
				line-height: 25px;
				height: 25px;
				padding-left: 50px;
				cursor: pointer;
			}

			.item:hover {
				color: #11C48B
			}

			.activecss {
				color: #11C48B
			}
		}
		.echartBox{
			height: 500px;
			width: 80%;
		}
		#bingtu {
			width: 80%;
			margin: 30px auto;
			height: 500px;
		}

		#zhutu {
			width: 80%;
			margin: 30px auto;
			height: 500px;
		}
	}
</style>
