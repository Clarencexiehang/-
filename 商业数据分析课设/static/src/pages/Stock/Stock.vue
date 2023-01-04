<template>
	<div class="hello">
		<div id="header">
			<input type="text" class="input" placeholder="请输入用户UID" v-model="value" />
			<button class="btn" @click="get_data1">搜索</button>
		</div>
		<div id="mystock"></div>
		<div id="showBox">
			<div class="header">
				<div :class="{activecss:type == index}" class="item" v-for="item,index in typedata" :key='index'
					@click="clickItem(index)">{{item}}</div>
			</div>
			<div id="timezutu"></div>
		</div>
	</div>
</template>

<script>
	import * as echarts from 'echarts';
	import axios from 'axios'
	export default {
		name: "Data",
		props: {
			msg: String,
		},
		data() {
			return {
				typedata: ['00-02', '02-04', '04-06', '06-08', '08-10', '10-12', '12-14', '14-16', '16-18', '18-20',
					'20-22', '22-24'
				],
				value: '',
				UserActiveData: [],
				data: [],
				timeData:[],
				type: 0,
			}
		},
		methods: {
			clickItem(index) {
				this.type = index
				this.timeData = this.data[this.typedata[index]]
				this.createChart2()
			},
			async getdata() {
				let params = this.value
				await axios.get('http://127.0.0.1:5000/show/time', {
					params: {
						uid: params
					}
				}).then((res) => {
					console.log(res.data, '=====')
					this.data = res.data
					this.timeData = this.data[this.typedata[0]]
				}).catch((x) => {
					console.log(x)
				})
				this.createChart2()
			},
			async get_data1() {
				let params = this.value
				await axios.get('http://127.0.0.1:5000/show/activePeriod', {
					params: {
						uid: params
					}
				}).then((res) => {
					console.log(res.data)
					this.UserActiveData = res.data
				}).catch((x) => {
					console.log(x)
				})
				this.createChart()
				this.getdata()
			},
			createChart2() {
				var myChart = echarts.init(document.getElementById("timezutu"));
				let optionData = [
					['time', 'amount', 'web'],
				]
				// let all = 10
				this.timeData.forEach(item => {
					let list = []
					let title = item.web
					// if (title.length > 10) {
					// 	title = title.slice(0, 10) + "..."
					// }
					list.push(item.visit_time/10)
					list.push(item.visit_time)
					list.push(title)
					optionData.push(list)
				})

				let option = {
					title: {
						text: '用户各时间段网站的浏览情况',
					},
					dataset: {
						source: optionData
					},
					grid: {
						containLabel: true
					},
					xAxis: {
						name: 'hitsMount'
					},
					yAxis: {
						type: 'category'
					},
					visualMap: {
						orient: 'horizontal',
						left: 'center',
						min: 10,
						max: 100,
						text: ['High time', 'Low time'],
						// Map the score column to color
						dimension: 0,
						inRange: {
							color: ['#65B581', '#FFCE34', '#FD665F']
						}
					},
					series: [{
						type: 'bar',
						encode: {
							// Map the "amount" column to X axis.
							x: 'amount',
							// Map the "product" column to Y axis
							y: 'web'
						}
					}]
				};
				console.log(option)
				option && myChart.setOption(option);
			},
			createChart() {
				var myChart = echarts.init(document.getElementById("mystock"));
				var option;
				let x_data = []
				let y_data = []

				for (let key in this.UserActiveData) {
					// console.log(item)
					var r = Math.floor(Math.random() * 256);
					var g = Math.floor(Math.random() * 256);
					var b = Math.floor(Math.random() * 256);
					var color = '#' + r.toString(16) + g.toString(16) + b
						.toString(16);
					x_data.push(key)
					let yObj = {
						value: this.UserActiveData[key],
						itemStyle: {
							color: color
						}
					}
					y_data.push(yObj)
				}

				option = {
					title: {
						text: '用户各时间段活跃情况',
					},
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
			this.createChart()
			this.createChart2()
		}
	};
</script>

<style scoped lang="scss">
	.titleText {
		font-size: 20px;
		color: #02a774;
	}

	.hello {
		display: flex;
		flex-direction: column;
		align-items: center;
	}

	#header {
		width: 80%;
		height: 60px;
		/* background-color:rgb(24, 168, 108); */
		margin: 10px 0 10px 0;
		overflow: hidden;
		display: flex;
		justify-content: center;
	}

	.input {
		height: 42px;
		width: 800px;
		border-radius: 5px;
		border: 1px rgb(16, 26, 163) solid;
		font-size: 20px;
		padding: 5px;
		padding-left: 10px;
		margin: 2px 0 0 0;
		outline: none;
	}

	.btn {
		cursor: pointer;
		width: 100px;
		height: 50px;
		background-color: #02a774;
		opacity: 0.8;
		border: none;
		border-radius: 5px;
		margin: 3px;
	}

	#mystock {
		width: 1200px;
		height: 500px;
		/* background-color: aqua; */
		margin: 30px auto;
	}

	#timezutu {
		width: 80%;
		margin: 30px auto;
		height: 500px;
	}

	#showBox {
		width: 80%;
		margin: 0 auto;
		height: 500px;
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
	}
</style>
