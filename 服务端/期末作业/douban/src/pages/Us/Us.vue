<template>
	<div class="box">
		<div class="header">
			<div :class="{activecss:type == index}" class="item" v-for="item,index in typedata" :key='index'
				@click="clickItem(index)">{{item}}</div>
		</div>
		<div id="main"></div>
	</div>

</template>

<script>
	import * as echarts from 'echarts';
	import $ from 'jquery'
	export default {
		data() {
			return {
				typedata: ['品牌', '机型', '分辨率', '操作系统', '运营商', '网络'],
				type: 0,
				myChart: null
			}
		},
		methods: {
			clickItem(index) {
				this.type = index
				this.getdata()
			},
			getdata() {
				// var ROOT_PATH = 'https://echarts.apache.org/examples';
				// this.$forceUpdate()
				if (this.myChart)
					this.myChart.dispose()
				var chartDom = document.getElementById('main');
				this.myChart = echarts.init(chartDom);
				let myChart = this.myChart
				var option;
				const updateFrequency = 2000;
				const dimension = 0;
				const countryColors = {};
				$.when(
					// $.getJSON('https://fastly.jsdelivr.net/npm/emoji-flags@1.3.0/data.json'),
					$.getJSON('http://127.0.0.1:5000/PhoneSalesVolumeData?type=' + this.type)
				).done(function(res0) {
					// const flags = res0[0];
					const data = res0['data'];
					// console.log(flags)
					// console.log(data)
					const years = [];
					for (let i = 0; i < data.length; ++i) {
						if (years.length === 0 || years[years.length - 1] !== data[i][4]) {
							years.push(data[i][4]);
						}
					}
					let startIndex = 0;
					let startYear = years[startIndex];
					option = {
						grid: {
							top: 10,
							bottom: 30,
							left: 150,
							right: 80
						},
						xAxis: {
							max: 'dataMax',
							axisLabel: {
								formatter: function(n) {
									return Math.round(n) + '';
									// return n;
								}
							}
						},
						dataset: {
							source: data.slice(1).filter(function(d) {
								return d[4] === startYear;
							})
						},
						yAxis: {
							type: 'category',
							inverse: true,
							max: 10,
							axisLabel: {
								show: true,
								fontSize: 14,
								formatter: function(value) {
									// return value + '{flag|' + getFlag(value) + '}';
									// console.log(value)
									return value;
								},
								rich: {
									flag: {
										fontSize: 25,
										padding: 5
									}
								}
							},
							animationDuration: 300,
							animationDurationUpdate: 300
						},
						series: [{
							realtimeSort: true,
							seriesLayoutBy: 'column',
							type: 'bar',
							itemStyle: {
								color: function(param) {
									//十六进制颜色随机
									var r = Math.floor(Math.random() * 256);
									var g = Math.floor(Math.random() * 256);
									var b = Math.floor(Math.random() * 256);
									var color = '#' + r.toString(16) + g.toString(16) + b
										.toString(16);
									if(!countryColors[param.value[3]]) countryColors[param.value[3]] = color
									return countryColors[param.value[3]];
								}
							},
							encode: {
								x: dimension,
								y: 3
							},
							label: {
								show: true,
								precision: 1,
								position: 'right',
								valueAnimation: true,
								fontFamily: 'monospace'
							}
						}],
						// Disable init animation.
						animationDuration: 0,
						animationDurationUpdate: updateFrequency,
						animationEasing: 'linear',
						animationEasingUpdate: 'linear',
						graphic: {
							elements: [{
								type: 'text',
								right: 160,
								bottom: 60,
								style: {
									text: startYear,
									font: 'bolder 80px monospace',
									fill: 'rgba(100, 100, 100, 0.25)'
								},
								z: 100
							}]
						}
					};
					// console.log(option);
					myChart.setOption(option);
					for (let i = startIndex; i < years.length - 1; ++i) {
						(function(i) {
							setTimeout(function() {
								updateYear(years[i + 1]);
							}, (i - startIndex) * updateFrequency);
						})(i);
					}

					function updateYear(year) {
						let source = data.slice(1).filter(function(d) {
							return d[4] === year;
						});
						// console.log(option.series)

						option.series[0].data = source;
						option.graphic.elements[0].style.text = year;
						myChart.setOption(option);
					}
				});

				option && myChart.setOption(option);

			}
		},
		mounted() {
			this.getdata()
		}
	}
</script>

<style lang='scss' scoped>
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

		.echartsBox {
			width: 80%;
			margin: 10px auto;
			height: 500px;
		}
	}

	#main {
		width: 80%;
		margin: 10px auto;
		height: 500px;
	}
</style>
