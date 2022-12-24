<template>
	<div>
		<div class="box" v-if="width>600">
			<div class="left">
				<img src="../../assets/wordcloud_text4_好压看图.jpg">
			</div>
			<div class="right">
				<span class="title">
					词云树
				</span>
				<span class="text">
					通过对电影的评价生成的词云树。可以直观的看到大多数电影的风评
				</span>
			</div>
		</div>
		<div class="box2" v-else>
			<div class="left">
				<img src="../../assets/wordcloud_text4_好压看图.jpg">
			</div>
			<div class="right">
				<span class="title">
					词云树
				</span>
				<span class="text">
					通过对电影的评价生成的词云树。可以直观的看到大多数电影的风评
				</span>
			</div>
		</div>
		<div id="main1"></div>
	</div>
</template>

<script>
	export default {
		data() {
			return {
				width: window.screen.width
			}
		},
		methods: {
			
		},
		mounted() {
			
		}
	}
</script>

<style lang='scss' scoped>
	.box {
		width: 80%;
		height: 500px;
		margin: 50px auto;
		overflow: hidden;
		display: flex;

		.left {
			height: 500px;
			width: 50%;

			img {
				width: 100%;
				// height: 500px;
			}
		}

		.right {
			padding: 20px;

			.title {
				font-size: 30px;
				color: #2c3e50;
				text-align: center;
				display: block;
				margin-left: -100px;
			}

			.text {
				display: block;
				margin: 40px;
				font-size: 20px;
				line-height: 30px;
			}
		}
	}

	.box2 {
		width: 80%;
		margin: 10px auto;

		// overflow: hidden;
		.left {
			height: 250px;
			width: 100%;
			margin-bottom: 50px;

			img {
				width: 100%;
			}
		}

		.right {
			.title {
				font-size: 20px;
				color: #2c3e50;
				text-align: center;
				display: block;
				margin-left: -100px;
			}

			.text {
				display: block;
				margin: 40px;
				font-size: 16px;
				line-height: 20px;

			}
		}
	}
</style>
