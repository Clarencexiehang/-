<template>
	<div class="rdd">
		<router-view></router-view>
	</div>
</template>

<script>
	
	export default{
		name:'RunDataDetail',
		data() {
			return{}
		}
	}
</script>

<style scoped>
	.rdd{
		flex: 5;
		flex-direction: row;
		justify-content: center;
		align-items: center;
		
		height: 100%;
		margin-left: 0.625rem;
		
	
	}
</style>