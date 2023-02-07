<template>
	<div class="right">
		<router-view></router-view>
	</div>
</template>

<script>
	export default{
		name:'Right',
		data() {
			return{}
		}
	}
</script>

<style scoped>
	.right{
		flex: 4;
		margin-left: 10px;
	}
</style>