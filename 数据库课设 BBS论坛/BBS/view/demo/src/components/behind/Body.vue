<template>
	<div class="body">
		<Left></Left>
		<Right></Right>
	</div>
</template>

<script>
	import Left from './Left.vue'	
	import Right from './Right.vue'	
	
	export default{
		name:'Body',
		data() {
			return{
			}
		},
		components:{
			Left,
			Right
		}
	}
</script>

<style scoped>
	.body{
		display: flex;
		flex-direction: row;
		align-content: flex-start;
		
		height: 90%;
		width: 100%;
		margin-top: 0.625rem;
	}
</style>