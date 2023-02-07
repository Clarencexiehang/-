<template>
	<div id="main_div">
		<MainContent></MainContent>
	</div>
</template>

<script>
	import MainContent from './MainContent.vue'
	export default {
		name:'Main',
		components:{
			MainContent
		}
	}
</script>

<style scoped>
	
	#main_div{
		position: relative;
		width: 100%;
		height: 100%;
		background-size: 100%;
		/* border: solid red 3px; */
	}
</style>