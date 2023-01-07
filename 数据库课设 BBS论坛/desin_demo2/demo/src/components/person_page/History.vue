<template>
	<div id="hist_item">
		<div class="hist_data" v-for="(value,index) in historyNum" :key="index">
			<h3>历史文章标题 {{ value }}</h3>
			<div>
				<p>文章内容</p>
			</div>
		</div>
	</div>
</template>

<script>
	import pubsub from 'pubsub-js'
	export default{
		name:'History',
		mounted() {
			pubsub.publish('clickIndex',4);
		},
		data() {
			return{
				historyNum:[1,2,3,4,5,6,7,8,9,10]
			}
		}
	}
</script>

<style scoped>
	#hist_item{
		width: 70%;
		height: 100%;
		overflow-y: auto;
		overflow: scroll;
	}
	.hist_data{
		width: 98%;
		height: 15.125rem;
		margin-top: 0.625rem;
		border: 0.7px solid rgb(235, 235, 235);
		border-radius: 5px 5px;
	}
</style>