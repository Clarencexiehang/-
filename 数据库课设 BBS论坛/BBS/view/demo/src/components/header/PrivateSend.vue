<template>
	<div>
		<router-view></router-view>
	</div>
</template>

<script>
	import MsgList from './MsgList.vue'
	export default{
		name:'PrivateSend',
		data() {
			return{}
		}
	}
</script>

<style scoped>
	div{
		display: flex;
		flex-direction: row;
		justify-content: center;
		align-items: center;
		
		width: 60%;
		height: 100%;
	}
	
</style>