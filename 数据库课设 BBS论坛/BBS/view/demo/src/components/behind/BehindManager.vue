<template>
	<div class="manager">
		<bHeader></bHeader>
		<Body></Body>
	</div>
</template>

<script>
	
	import bHeader from './bHeader.vue'
	import Body from './Body.vue'	
	
	export default {
		name:'BehindManager',
		data() {
			return{
				
			}
		},
		methods:{
			
		},
		components:{
			bHeader,
			Body
		}
		
	}

</script>

<style scoped>
	.manager{
		height: 100%;
		width: 100%;
		background-image: url('../../assets/backimg/behind_bac.png');
	}
</style>