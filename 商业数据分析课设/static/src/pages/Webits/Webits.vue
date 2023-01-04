<template>
	<div class="hello">
		<div id="header">
			<input type="text" class="input" placeholder="请输入用户UID" v-model="value" />
			<button class="btn" @click="get_data1">搜索</button>
		</div>
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
				timeData: [],
				type: 0,
			}
		},
		methods: {
			clickItem(index) {
				this.type = index
				this.timeData = this.data[this.typedata[index]]
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
		},
		mounted() {
			
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
