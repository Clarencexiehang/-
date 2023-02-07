<template>
	<div class="rund">
		<RunDataItem></RunDataItem>
		<RunDataDetail></RunDataDetail>
	</div>
</template>

<script>
	import RunDataItem from './RunDataItem.vue'
	import RunDataDetail from './RunDataDetail.vue'
	
	export default{
		name:'RunData',
		data() {
			return{}
		},
		components:{
			RunDataItem,
			RunDataDetail
		}
	}
</script>

<style scoped>
	.rund{
		display: flex;
		flex-direction: row;
		justify-content: flex-start;
		align-items: center;
		
		width: 90%;
		height: 100%;
	}
</style>